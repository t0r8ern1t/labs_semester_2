#include <BMP.hpp>

using namespace std;

namespace mt::images
{
    bool Pixel::operator==(const Pixel& pix)
    {
        return ((pix.b == b) && (pix.g == g) && (pix.r == r));
    }

    bool Pixel::operator!=(const Pixel& pix)
    {
        return ((pix.b != b) || (pix.g != g) || (pix.r != r));
    }

    BMP::BMP()
    {
        m_width = 0;
        m_height = 0;
    }

    BMP::BMP(int width, int height)
    {
        m_width = width;
        m_height = height;
        m_pixels = new Pixel * [m_height];
        for (int i = 0; i < m_height; i++)
            m_pixels[i] = new Pixel[m_width];

        m_coordinates = new Vec2d * [m_height];
        for (int i = 0; i < m_height; i++)
            m_coordinates[i] = new Vec2d[m_width];

        for (int i = 0; i < m_height; i++)
            for (int j = 0; j < m_width; j++)
                m_pixels[i][j] = { 0,0,0 };

        for (int i = 0; i < m_height; i++)
            for (int j = 0; j < m_width; j++)
            {
                m_coordinates[i][j].set(0, 0, j);
                m_coordinates[i][j].set(1, 0, i);
            }
    }

    // TODO
    BMP::BMP(const BMP& bmp)
    {
        if (m_pixels != nullptr)
        {
            for (int i = 0; i < m_height; i++)
                delete[] m_pixels[i];
            delete[] m_pixels;
        }

        m_width = bmp.m_width;
        m_height = bmp.m_height;

        m_pixels = new Pixel * [m_height];
        for (int i = 0; i < m_height; i++)
            m_pixels[i] = new Pixel[m_width];

        for (int i = 0; i < m_height; i++)
            for (int j = 0; j < m_width; j++)
                m_pixels[i][j] = bmp.m_pixels[i][j];
    }

    // TODO
    BMP& BMP::operator=(const BMP& bmp)
    {
        if (m_pixels != nullptr)
        {
            for (int i = 0; i < m_height; i++)
                delete[] m_pixels[i];
            delete[] m_pixels;
        }

        m_width = bmp.m_width;
        m_height = bmp.m_height;

        m_pixels = new Pixel * [m_height];
        for (int i = 0; i < m_height; i++)
            m_pixels[i] = new Pixel[m_width];

        for (int i = 0; i < m_height; i++)
            for (int j = 0; j < m_width; j++)
                m_pixels[i][j] = bmp.m_pixels[i][j];

        return *this;
    }

    BMP::~BMP()
    {
        for (int i = 0; i < m_height; i++)
            delete[] m_pixels[i];
        delete[] m_pixels;

        for (int i = 0; i < m_height; i++)
            delete[] m_coordinates[i];
        delete[] m_coordinates;
    }

    void BMP::Fill(Pixel pixel)
    {
        for (int i = 0; i < m_height; i++)
            for (int j = 0; j < m_width; j++)
                m_pixels[i][j] = pixel;
    }

    void BMP::Brightness()
    {
        for (int i = 0; i < m_height; i++)
            for (int j = 0; j < m_width; j++)
            {
                if (m_pixels[i][j].b + 50 < 256)
                    m_pixels[i][j].b += 50;
                if (m_pixels[i][j].g + 50 < 256)
                    m_pixels[i][j].g += 50;
                if (m_pixels[i][j].r + 50 < 256)
                    m_pixels[i][j].r += 50;
            }
    }

    // TODO
    void BMP::Open(const std::string& filename)
    {
        //  
        std::ifstream in(filename, std::ios::binary); //     

        BMPHEADER bmpHeader;
        //  14      BMPHEADER
        in.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHEADER));

        BMPINFO bmpInfo;
        in.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BMPINFO));

        if (m_pixels != nullptr)
        {
            for (int i = 0; i < m_height; i++)
                delete[] m_pixels[i];
            delete[] m_pixels;
        }

        m_width = bmpInfo.Width;
        m_height = bmpInfo.Height;

        m_pixels = new Pixel * [m_height];
        for (int i = 0; i < m_height; i++)
            m_pixels[i] = new Pixel[m_width];

        for (int i = 0; i < bmpInfo.Height; i++)
        {
            for (int j = 0; j < bmpInfo.Width; j++)
                in.read(reinterpret_cast<char*>(&m_pixels[i][j]), sizeof(Pixel));

            if ((3 * bmpInfo.Width) % 4 != 0)
                for (int j = 0; j < 4 - (3 * bmpInfo.Width) % 4; j++)
                {
                    char c;
                    in.read(&c, 1);
                }
        }
    }

    void BMP::Save(const std::string& filename)
    {
        if (m_width == 0 || m_height == 0)
            throw std::exception("Zero height or width");

        //  
        std::ofstream out(filename, std::ios::binary);

        //  
        BMPHEADER bmpHeader_new;
        bmpHeader_new.Type = 0x4D42; //   BMP
        bmpHeader_new.Size = 14 + 40 + (3 * m_width * m_height);
        if (m_width % 4 != 0)
            bmpHeader_new.Size += (4 - (3 * m_width) % 4) * m_height;
        bmpHeader_new.OffBits = 54;
        bmpHeader_new.Reserved1 = 0;
        bmpHeader_new.Reserved2 = 0;

        out.write(reinterpret_cast<char*>(&bmpHeader_new), sizeof(BMPHEADER));

        //    
        BMPINFO bmpInfo_new;
        bmpInfo_new.BitCount = 24;
        bmpInfo_new.ClrImportant = 0;
        bmpInfo_new.ClrUsed = 0;
        bmpInfo_new.Compression = 0;
        bmpInfo_new.Height = m_height;
        bmpInfo_new.Planes = 1;
        bmpInfo_new.Size = 40;
        bmpInfo_new.SizeImage = bmpHeader_new.Size - 54;
        bmpInfo_new.Width = m_width;
        bmpInfo_new.XPelsPerMeter = 0;
        bmpInfo_new.YPelsPerMeter = 0;

        out.write(reinterpret_cast<char*>(&bmpInfo_new), sizeof(BMPINFO));

        //  
        for (int i = 0; i < bmpInfo_new.Height; i++)
        {
            for (int j = 0; j < bmpInfo_new.Width; j++)
                out.write(reinterpret_cast<char*>(&m_pixels[i][j]), sizeof(Pixel));

            if ((3 * bmpInfo_new.Width) % 4 != 0)
                for (int j = 0; j < 4 - (3 * bmpInfo_new.Width) % 4; j++)
                {
                    char c = 0;
                    out.write(&c, 1);
                }
        }
    }

    void BMP::Rotate(double angle)
    {
        // 1.   
        Vec2d T({ {
            {(double)(m_width / 2)},
            {(double)(m_height / 2)}
        } });

        for (int i = 0; i < m_height; i++)
            for (int j = 0; j < m_width; j++)
                m_coordinates[i][j] = m_coordinates[i][j] - T;

        // 2. 
        Mat22d R({ {
            {cos(angle), sin(angle)},
            {-sin(angle), cos(angle)}
        } });

        for (int i = 0; i < m_height; i++)
            for (int j = 0; j < m_width; j++)
            {
                m_coordinates[i][j] = R * m_coordinates[i][j];
                //std::cout << m_coordinates[i][j] << std::endl;
            }

        // 3.      
        int maxX = INT_MIN;
        int minX = INT_MAX;
        int maxY = INT_MIN;
        int minY = INT_MAX;
        for (int i = 0; i < m_height; i++)
            for (int j = 0; j < m_width; j++)
            {
                if (maxX < m_coordinates[i][j].get(0, 0))
                    maxX = m_coordinates[i][j].get(0, 0);
                if (minX > m_coordinates[i][j].get(0, 0))
                    minX = m_coordinates[i][j].get(0, 0);
                if (maxY < m_coordinates[i][j].get(1, 0))
                    maxY = m_coordinates[i][j].get(1, 0);
                if (minY > m_coordinates[i][j].get(1, 0))
                    minY = m_coordinates[i][j].get(1, 0);
            }

        //       -  
        maxX++;
        minX--;
        maxY++;
        minY--;

        int width = maxX - minX;
        int height = maxY - minY;

        //     
        Vec2d shift({ {
            {(double)(width / 2)},
            {(double)(height / 2)}
        } });

        for (int i = 0; i < m_height; i++)
            for (int j = 0; j < m_width; j++)
                m_coordinates[i][j] = m_coordinates[i][j] + shift;

        //   
        Pixel** new_pixels = new Pixel * [height];
        for (int i = 0; i < height; i++)
            new_pixels[i] = new Pixel[width];

        Vec2d** new_coordinates = new Vec2d * [height];
        for (int i = 0; i < height; i++)
            new_coordinates[i] = new Vec2d[width];

        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                new_pixels[i][j] = { 0, 0, 0 };

        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
            {
                new_coordinates[i][j].set(0, 0, j);
                new_coordinates[i][j].set(0, 0, i);
            }

        //  
        for (int i = 0; i < m_height; i++)
            for (int j = 0; j < m_width; j++)
            {
                int x = (int)(m_coordinates[i][j].get(0, 0));
                int y = (int)(m_coordinates[i][j].get(1, 0));
                new_pixels[y][x] = m_pixels[i][j];
            }

        //   
        for (int i = 0; i < m_height; i++)
            delete[] m_pixels[i];
        delete[] m_pixels;

        for (int i = 0; i < m_height; i++)
            delete[] m_coordinates[i];
        delete[] m_coordinates;

        m_pixels = new_pixels;
        m_coordinates = new_coordinates;

        m_width = width;
        m_height = height;
    }

    void BMP::Artefacts()
      {
          for (int j = 1; j < m_width - 1; ++j) {
              for (int i = 1; i < m_height - 1; ++i) {
                  int blue = 0, green = 0, red = 0;
                  int len = 8;
                  int bcount = 0, gcount = 0, rcount = 0, samecount = 0;
                  Pixel ex = { 0, 0, 0 };
                  Pixel* surroundings = new Pixel[len] { m_pixels[i][j - 1], m_pixels[i + 1][j - 1], m_pixels[i + 1][j], m_pixels[i + 1][j + 1], m_pixels[i][j + 1], m_pixels[i - 1][j + 1], m_pixels[i - 1][j], m_pixels[i - 1][j - 1] };
                  for (int k = 0; k < len; ++k) {
                      if (m_pixels[i][j] == surroundings[k]) samecount += 1;
                      if (surroundings[k] != ex) {
                          if (surroundings[k].b != 0) {
                              blue += surroundings[k].b;
                              bcount += 1;
                          }
                          if (surroundings[k].g != 0) {
                              green += surroundings[k].g;
                              gcount += 1;
                          }
                          if (surroundings[k].r != 0) {
                              red += surroundings[k].r;
                              rcount += 1;
                          }
                      }
                  }
                  if ((m_pixels[i][j] == ex) && (samecount < 4)) {
                      if (bcount != 0)
                          m_pixels[i][j].b = (blue / bcount);
                      else m_pixels[i][j].b = blue;
                      if (gcount != 0)
                          m_pixels[i][j].g = (green / gcount);
                      else m_pixels[i][j].g = green;
                      if (rcount != 0)
                          m_pixels[i][j].r = (red / rcount);
                      else m_pixels[i][j].r = red;
                  }
                  delete[] surroundings;
              }
          }
          std::cout << "done" << std::endl;
      }
}