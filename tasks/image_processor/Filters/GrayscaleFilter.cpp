#include "GrayscaleFilter.h"
#include "../FilterFabric.h"
#include <iostream>

const std::string FILTER_NAME = "gs";

[[maybe_unused]] const FilterFabric::Registrator<GrayscaleFilter> REGISTRATOR(FILTER_NAME);

void GrayscaleFilter::PrintManual() {
    std::cout << "\n";
    std::cout << "Filter name: gs\n";
    std::cout << "Changes every pixel to its grayscale\n";
    std::cout << "Filter args: None\n";
    std::cout << "Example: -gs \n";
    std::cout << "\n";
}
void GrayscaleFilter::Process(CImage& image, const std::vector<std::string>& args) {
    static const std::valarray<float> GRAYSCALE_COEFFICIENTS({0.114, 0.587f, 0.299f});
    if (!args.empty()) {
        throw std::runtime_error("Invalid arguments passed into filter " + FILTER_NAME);
    }
    for (int32_t y = 0; y < image.GetHeight(); ++y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {
            auto& pixel = image.GetPixel(x, y);
            float color = (pixel.colors * GRAYSCALE_COEFFICIENTS).sum();
            for (auto& o : pixel.colors) {
                o = color;
            }
        }
    }
}