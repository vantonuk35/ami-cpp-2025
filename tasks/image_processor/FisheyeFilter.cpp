#include "FisheyeFilter.h"
#include "FilterFabric.h"
#include <iostream>

const std::string FILTER_NAME = "fish";

[[maybe_unused]] const FilterFabric::Registrator<FisheyeFilter> REGISTRATOR(FILTER_NAME);

void FisheyeFilter::PrintManual() {
    std::cout << "\n";
    std::cout << "Filter name: fish\n";
    std::cout << "Applies fisheye filter\n";
    std::cout << "Filter args: \n";
    std::cout << "Filter strength: real value. Experiment with it";
    std::cout << "Example: -fish 2 \n";
    std::cout << "\n";
}
void FisheyeFilter::Process(CImage &image, const std::vector<std::string> &args) {
    constexpr double MagicConstantNeededToDivideByTwoAndGetCenterPosOfImage = 2.0;
    float strength = 0;
    try {
        if (args.size() != 1) {
            throw std::exception();
        }
        strength = std::stof(args[0]);
    } catch (...) {
        throw std::runtime_error("Invalid arguments passed into filter " + FILTER_NAME);
    }
    CImage res(image.GetWidth(), image.GetHeight());
    double center_x = image.GetWidth() / MagicConstantNeededToDivideByTwoAndGetCenterPosOfImage;
    double center_y = image.GetHeight() / MagicConstantNeededToDivideByTwoAndGetCenterPosOfImage;
    double max_radius = std::sqrt(center_x * center_x + center_y * center_y);

    for (int32_t y = 0; y < image.GetHeight(); ++y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {
            const double dx = x - center_x;
            const double dy = y - center_y;
            const double r = std::sqrt(dx * dx + dy * dy);
            const double r_norm = r / max_radius;
            const double r_distorted = max_radius * std::sin(strength * r_norm) / std::sin(strength);
            const double scale = r / r_distorted;
            const int32_t src_x = static_cast<int32_t>(center_x + dx * scale);
            const int32_t src_y = static_cast<int32_t>(center_y + dy * scale);
            res.GetPixel(x, y) = image.GetNearestPixel(src_x, src_y);
        }
    }
    image = std::move(res);
}