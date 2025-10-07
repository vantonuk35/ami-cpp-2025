#include "CropFilter.h"
#include "../FilterFabric.h"
#include <iostream>

const std::string FILTER_NAME = "crop";

[[maybe_unused]] const FilterFabric::Registrator<CropFilter> REGISTRATOR(FILTER_NAME);

void CropFilter::PrintManual() {
    std::cout << "\n";
    std::cout << "Filter name: crop\n";
    std::cout << "Filter crops image up to given dimensions\n";
    std::cout << "Filter args:\n";
    std::cout << "Width: Positive integer\n";
    std::cout << "Height: Positive integer\n";
    std::cout << "If parameter exceeds corresponding dimension, this dimension will stay unchanged\n";
    std::cout << "Example: -crop 800 600 \n";
    std::cout << "\n";
}
void CropFilter::Process(CImage &image, const std::vector<std::string> &args) {
    int32_t new_width = 0;
    int32_t new_height = 0;
    try {
        if (args.size() != 2) {
            throw std::exception();
        }
        new_width = std::min(std::stoi(args[0]), image.GetWidth());
        new_height = std::min(std::stoi(args[1]), image.GetHeight());
        if (new_width <= 0 || new_height <= 0) {
            throw std::exception();
        }
    } catch (...) {
        throw std::runtime_error("Invalid arguments passed into filter " + FILTER_NAME);
    }
    CImage result(new_width, new_height);
    for (int32_t y = 0; y < new_height; ++y) {
        for (int32_t x = 0; x < new_width; ++x) {
            result.GetPixel(x, y) = image.GetPixel(x, y);
        }
    }
    image = std::move(result);
}