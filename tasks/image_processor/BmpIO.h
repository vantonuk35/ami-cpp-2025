#ifndef BMPIO_H
#define BMPIO_H
#include <cstdint>
#include "CImage.h"
#include <fstream>

class BmpIO {
#pragma pack(push, 1)
    struct BITMAPFILEHEADER {
        uint16_t bfType;
        uint32_t bfSize;
        uint16_t bfReserved1;
        uint16_t bfReserved2;
        uint32_t bfOffBits;
    };
    struct BITMAPINFOHEADER {
        uint32_t biSize;
        int32_t biWidth;
        int32_t biHeight;
        uint16_t biPlanes;
        uint16_t biBitCount;
        uint32_t biCompression;
        uint32_t biSizeImage;
        int32_t biXPelsPerMeter;
        int32_t biYPelsPerMeter;
        uint32_t biClrUsed;
        uint32_t biClrImportant;
    };
#pragma pack(pop)
    static constexpr int16_t BmpHexSignature = 0x4D42;
    static constexpr int16_t BmpBitCount = 24;

public:
    static CImage Load(const std::string& filename);
    static void Save(const CImage& image, const std::string& filename);
};

#endif  // BMPIO_H
