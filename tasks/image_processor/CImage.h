#ifndef IMAGE_H
#define IMAGE_H
#include <array>
#include <cstdint>
#include <vector>
#include <valarray>
class CImage {
public:
    class CPixel {
        static constexpr float MaxUint8 = 255.f;

    public:
        std::valarray<float> colors;
        explicit CPixel(std::array<float, 3> colors);
        explicit CPixel(std::array<uint8_t, 3> colors = {0, 0, 0});
        void Normalize();
        std::array<uint8_t, 3> ToR888();
    };

private:
    int32_t width_;
    int32_t height_;
    std::vector<CPixel> image_data_;

public:
    CImage(const int32_t width, const int32_t height);
    CPixel& GetPixel(const int32_t x, const int32_t y);
    CPixel GetPixel(const int32_t x, const int32_t y) const;
    CPixel GetNearestPixel(int32_t x, int32_t y) const;
    int32_t GetWidth() const;
    int32_t GetHeight() const;
};

#endif  // IMAGE_H
