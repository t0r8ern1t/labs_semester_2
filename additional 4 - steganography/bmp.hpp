#pragma once
#include <string>
#include <fstream>

namespace ssh
{
#pragma pack(1)
	struct Pixel
	{
		unsigned char b;
		unsigned char g;
		unsigned char r;

        bool operator==(const Pixel& pix);
        bool operator!=(const Pixel& pix);
	};

    
#pragma pack()

	class BMP
	{
	public:
        BMP(int width, int height);

        ~BMP();

        void Write(const std::string& filename);

        void Read(const std::string& filename);

        void Encrypt();

        void Decrypt();

	private:
		int m_width, m_height;
		Pixel** m_pixels;

#pragma pack(1)
        struct BMPHEADER
        {
            unsigned short    Type;
            unsigned int      Size;
            unsigned short    Reserved1;
            unsigned short    Reserved2;
            unsigned int      OffBits;
        };
#pragma pack()

#pragma pack(1)
        struct BMPINFO
        {
            unsigned int    Size;
            int             Width;
            int             Height;
            unsigned short  Planes;
            unsigned short  BitCount;
            unsigned int    Compression;
            unsigned int    SizeImage;
            int             XPelsPerMeter;
            int             YPelsPerMeter;
            unsigned int    ClrUsed;
            unsigned int    ClrImportant;
        };
#pragma pack()
	};
}