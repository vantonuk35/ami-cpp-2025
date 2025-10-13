#include "EdgeFilter.h"
#include "FilterFabric.h"
#include <iostream>

const std::string FILTER_NAME = "edge";

[[maybe_unused]] const FilterFabric::Registrator<EdgeFilter> REGISTRATOR(FILTER_NAME);

void EdgeFilter::PrintManual() {
    std::cout << "\n";
    std::cout << "Filter name: edge\n";
    std::cout << "Applies edge-finding filter to image\n";
    std::cout << "Filter args:\n";
    std::cout << "Threshold: real value in range [0;1]\n";
    std::cout << "Example: -edge 0.1 \n";
    std::cout << "\n";
}
void EdgeFilter::Process(CImage& image, const std::vector<std::string>& args) {
    static std::shared_ptr<IFilter> grayscale_filter;
    if (!grayscale_filter) {
        grayscale_filter = FilterFabric::Create("gs");
    }
    float threshold = 0;
    try {
        if (args.size() != 1) {
            throw std::exception();
        }
        threshold = std::stof(args[0]);
        if (threshold < 0 || threshold > 1) {
            throw std::exception();
        }
    } catch (...) {
        throw std::runtime_error("Invalid arguments passed into filter " + FILTER_NAME);
    }
    grayscale_filter->Process(image, {});
    ApplyMatrix(image, EdgeMatrix);
    for (int32_t y = 0; y < image.GetHeight(); ++y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {
            auto& pixel = image.GetPixel(x, y);
            if (pixel.colors[0] < threshold) {
                pixel.colors = {0, 0, 0};
            } else {
                pixel.colors = {1, 1, 1};
            }
        }
    }
}