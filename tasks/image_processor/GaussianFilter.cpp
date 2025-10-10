#include "GaussianFilter.h"
#include "FilterFabric.h"
#include <iostream>

const std::string FILTER_NAME = "blur";

[[maybe_unused]] const FilterFabric::Registrator<GaussianFilter> REGISTRATOR(FILTER_NAME);

void GaussianFilter::PrintManual() {
    std::cout << "\n";
    std::cout << "Filter name: blur\n";
    std::cout << "Applies Gaussian blue with given sigma to the image\n";
    std::cout << "Filter args:\n";
    std::cout << "Sigma: real number > 0 \n";
    std::cout << "Example: -blur 7.5\n";
    std::cout << "\n";
}
void GaussianFilter::Process(CImage &image, const std::vector<std::string> &args) {
    static constexpr float SigmaLimit = 200;
    float sigma = 0;
    try {
        if (args.size() != 1) {
            throw std::exception();
        }
        sigma = std::stof(args[0]);
        if (sigma <= 0) {
            throw std::exception();
        }
    } catch (...) {
        throw std::runtime_error("Invalid arguments passed into filter " + FILTER_NAME);
    }
    if (sigma > SigmaLimit) {
        throw std::runtime_error("Too big sigma in " + FILTER_NAME);
    }
    int32_t radius = static_cast<int>(std::ceil(sigma * 2));
    std::vector<float> kernel(2 * radius + 1);
    float sum = 0;
    for (int32_t i = -radius; i <= radius; ++i) {
        float value = std::exp(static_cast<float>(-(i * i)) / (2 * sigma * sigma));
        kernel[i + radius] = value;
        sum += value;
    }
    for (auto &v : kernel) {
        v /= sum;
    }
    CImage tmp1(image.GetWidth(), image.GetHeight());
    for (int32_t y = 0; y < image.GetHeight(); ++y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {
            auto &pixel = tmp1.GetPixel(x, y);
            for (int32_t dy = -radius; dy <= radius; dy++) {
                pixel.colors += kernel[dy + radius] * image.GetNearestPixel(x, y + dy).colors;
            }
            pixel.Normalize();
        }
    }
    CImage tmp2(image.GetWidth(), image.GetHeight());
    for (int32_t y = 0; y < image.GetHeight(); ++y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {
            auto &pixel = tmp2.GetPixel(x, y);
            for (int32_t dx = -radius; dx <= radius; dx++) {
                pixel.colors += kernel[dx + radius] * tmp1.GetNearestPixel(x + dx, y).colors;
            }
            pixel.Normalize();
        }
    }
    image = std::move(tmp2);
}