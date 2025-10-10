#include "NegativeFilter.h"
#include "FilterFabric.h"
#include <iostream>

const std::string FILTER_NAME = "neg";

[[maybe_unused]] const FilterFabric::Registrator<NegativeFilter> REGISTRATOR(FILTER_NAME);

void NegativeFilter::PrintManual() {
    std::cout << "\n";
    std::cout << "Filter name: neg\n";
    std::cout << "Changes every pixel to its negative\n";
    std::cout << "Filter args: None\n";
    std::cout << "Example: -neg \n";
    std::cout << "\n";
}
void NegativeFilter::Process(CImage &image, const std::vector<std::string> &args) {
    if (!args.empty()) {
        throw std::runtime_error("Invalid arguments passed into filter " + FILTER_NAME);
    }
    for (int32_t y = 0; y < image.GetHeight(); ++y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {
            auto &pixel = image.GetPixel(x, y);
            pixel.colors = 1 - pixel.colors;
        }
    }
}