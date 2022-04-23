#include "bmp.hpp"

namespace ssh
{
    bool Pixel::operator==(const Pixel& pix)
    {
        return ((pix.b == b) && (pix.g == g) && (pix.r == r));
    }

    bool Pixel::operator!=(const Pixel& pix)
    {
        return ((pix.b != b) || (pix.g != g) || (pix.r != r));
    }

    BMP::BMP(int width, int height)
    {
        m_width = width;
        m_height = height;
        m_pixels = new Pixel * [m_height];
        for (int i = 0; i < m_height; ++i) {
            m_pixels[i] = new Pixel[m_width];
        }
    }

    BMP::~BMP()
    {
        for (int i = 0; i < m_height; i++)
            delete[] m_pixels[i];
        delete[] m_pixels;
    }

    void BMP::Write(const std::string& filename)
    {
        // Записать файл
        std::ofstream out(filename, std::ios::binary);

        // Формирование заголовка
        BMPHEADER bmpHeader_new;
        bmpHeader_new.Type = 0x4D42; // Тип данных BMP
        bmpHeader_new.Size = 14 + 40 + (3 * m_width * m_height);
        if (m_width % 4 != 0)
            bmpHeader_new.Size += (4 - (3 * m_width) % 4) * m_height;
        bmpHeader_new.OffBits = 54;
        bmpHeader_new.Reserved1 = 0;
        bmpHeader_new.Reserved2 = 0;

        out.write(reinterpret_cast<char*>(&bmpHeader_new), sizeof(BMPHEADER));

        // Формирование информации об изображении
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

        // Записать пиксели
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

    void BMP::Read(const std::string& filename)
    {
        // Чтение файла
        std::ifstream in(filename, std::ios::binary); // открыть файл для бинарного чтения

        BMPHEADER bmpHeader;
        // Считать 14 байтов побайтово и заполнить структуру BMPHEADER
        in.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHEADER));

        BMPINFO bmpInfo;
        in.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BMPINFO));

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

    void BMP::Decrypt()
    {
        Pixel back = m_pixels[0][0];
        for (int i = 0; i < m_height; ++i) {
            for (int j = 0; j < m_width; ++j) {
                if (m_pixels[i][j] == back) {
                    m_pixels[i][j].b = 255 - m_pixels[i][j].b;
                    m_pixels[i][j].g = 255 - m_pixels[i][j].g;
                    m_pixels[i][j].r = 255 - m_pixels[i][j].r;
                }
            }
        }
    }

    void BMP::Encrypt()
    {
        Pixel back = m_pixels[0][0];
        for (int i = 0; i < m_height; ++i) {
            for (int j = 0; j < m_width; ++j) {
                if (m_pixels[i][j] != back) {
                    m_pixels[i][j].g = back.g;
                    m_pixels[i][j].r = back.r;

                    if (back.b + 1 <= 255)
                        m_pixels[i][j].b = back.b + 1;
                    else m_pixels[i][j].b = back.b - 1;
                }
            }
        }
    }
}