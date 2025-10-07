#include "CImage.h"

#include <stdexcept>
#include <algorithm>

CImage::CPixel CImage::GetPixel(const int32_t x, const int32_t y) const {
    if (x >= width_) {
        throw std::out_of_range("Requested pixel has invalid X");
    }
    if (y >= height_) {
        throw std::out_of_range("Requested pixel has invalid Y");
    }
    return image_data_[y * width_ + x];
}

CImage::CPixel& CImage::GetPixel(const int32_t x, const int32_t y) {
    if (x >= width_) {
        throw std::out_of_range("Requested pixel has invalid X");
    }
    if (y >= height_) {
        throw std::out_of_range("Requested pixel has invalid Y");
    }
    return image_data_[y * width_ + x];
}

CImage::CImage(const int32_t width, const int32_t height) : width_(width), height_(height) {
    image_data_.resize(width_ * height);
}
int32_t CImage::GetHeight() const {
    return height_;
}
int32_t CImage::GetWidth() const {
    return width_;
}
CImage::CPixel CImage::GetNearestPixel(int32_t x, int32_t y) const {
    x = std::clamp(x, 0, width_ - 1);
    y = std::clamp(y, 0, height_ - 1);
    return GetPixel(x, y);
}

CImage::CPixel::CPixel(std::array<float, 3> colors) {
    this->colors.resize(3);
    for (int i = 0; i < 3; i++) {
        this->colors[i] = colors[i];
    }
}
CImage::CPixel::CPixel(std::array<uint8_t, 3> colors) {
    this->colors.resize(3);
    for (int i = 0; i < 3; i++) {
        this->colors[i] = static_cast<float>(colors[i]) / MaxUint8;
    }
}
void CImage::CPixel::Normalize() {
    for (auto& o : colors) {
        o = std::clamp(o, 0.f, 1.f);
    }
}
std::array<uint8_t, 3> CImage::CPixel::ToR888() {
    Normalize();
    std::array<uint8_t, 3> res;
    for (int i = 0; i < 3; i++) {
        res[i] = static_cast<uint8_t>(colors[i] * MaxUint8);
    }
    return res;
}