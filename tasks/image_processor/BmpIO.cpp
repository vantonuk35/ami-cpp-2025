#include "BmpIO.h"

void BmpIO::Save(const CImage& image, const std::string& filename) {
    const int32_t width = image.GetWidth();
    const int32_t height = image.GetHeight();
    const int32_t stride = ((((width * BmpBitCount) + 31) & ~31) >> 3);  // MSDN wiki does it this way
    const uint32_t pixel_array_size = stride * height;
    const uint32_t file_size = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + pixel_array_size;

    BITMAPFILEHEADER file_header{};
    file_header.bfType = BmpHexSignature;
    file_header.bfSize = file_size;
    file_header.bfReserved1 = 0;
    file_header.bfReserved2 = 0;
    file_header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    BITMAPINFOHEADER info_header{};
    info_header.biSize = sizeof(BITMAPINFOHEADER);
    info_header.biWidth = width;
    info_header.biHeight = height;
    info_header.biPlanes = 1;
    info_header.biBitCount = BmpBitCount;
    info_header.biCompression = 0;
    info_header.biSizeImage = pixel_array_size;

    // Set about 72 DPI. Default value btw.
    static constexpr uint16_t Dpi72Magic = 2835;
    info_header.biXPelsPerMeter = Dpi72Magic;
    info_header.biYPelsPerMeter = Dpi72Magic;

    info_header.biClrUsed = 0;
    info_header.biClrImportant = 0;

    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }

    file.write(reinterpret_cast<const char*>(&file_header), sizeof(BITMAPFILEHEADER));
    file.write(reinterpret_cast<const char*>(&info_header), sizeof(BITMAPINFOHEADER));

    std::vector<uint8_t> row(stride, 0);

    for (int32_t y = height - 1; y >= 0; --y) {
        for (int32_t x = 0; x < width; ++x) {
            const auto& [B, G, R] = image.GetPixel(x, y).ToR888();
            row[x * 3] = B;
            row[x * 3 + 1] = G;
            row[x * 3 + 2] = R;
        }
        file.write(reinterpret_cast<const char*>(row.data()), stride);
    }

    if (!file) {
        throw std::runtime_error("Error occurred while writing BMP file");
    }
}

CImage BmpIO::Load(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    BITMAPFILEHEADER file_header{};
    BITMAPINFOHEADER info_header{};

    file.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    file.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    if (file_header.bfType != BmpHexSignature) {
        throw std::runtime_error("Bad Bitmap File Header. Not a BMP file");
    }

    if (file_header.bfReserved1 || file_header.bfReserved2) {
        throw std::runtime_error("Bad Bitmap File Header. Reserved fields must be zeroes");
    }

    if (file_header.bfOffBits < sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)) {
        throw std::runtime_error("Bad Bitmap File Header. Pixel array offset too small");
    }

    if (info_header.biSize != sizeof(BITMAPINFOHEADER)) {
        throw std::runtime_error("Unsupported Bitmap. Unsupported DIB header (must be BITMAPINFOHEADER)");
    }

    if (info_header.biBitCount != BmpBitCount) {
        throw std::runtime_error("Unsupported Bitmap. Only 24-bit BMP supported");
    }

    if (info_header.biCompression != 0) {  // BI_RGB = 0
        throw std::runtime_error("Unsupported Bitmap. Compressed BMP not supported");
    }

    if (info_header.biWidth < 0) {
        throw std::runtime_error("Bad Bitmap. Width can't be less than 0");
    }

    file.seekg(file_header.bfOffBits, std::ios::beg);

    const auto stride = ((((info_header.biWidth * info_header.biBitCount) + 31) & ~31) >> 3);

    CImage result(info_header.biWidth, abs(info_header.biHeight));
    std::vector<uint8_t> row(stride);

    for (int32_t row_index = 0; row_index < abs(info_header.biHeight); ++row_index) {
        file.read(reinterpret_cast<char*>(row.data()), static_cast<std::streamsize>(stride));
        if (!file) {
            throw std::runtime_error("File reading error or unexpected EOF");
        }
        int32_t y = (info_header.biHeight > 0 ? info_header.biHeight - 1 - row_index : row_index);
        for (int32_t x = 0; x < info_header.biWidth; ++x) {
            result.GetPixel(x, y) = CImage::CPixel{std::array<uint8_t, 3>{row[x * 3], row[x * 3 + 1], row[x * 3 + 2]}};
        }
    }
    return result;
}
