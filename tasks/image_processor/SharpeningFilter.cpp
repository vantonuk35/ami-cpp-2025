#include "SharpeningFilter.h"
#include "FilterFabric.h"
#include <iostream>

const std::string FILTER_NAME = "sharp";

[[maybe_unused]] const FilterFabric::Registrator<SharpeningFilter> REGISTRATOR(FILTER_NAME);

void SharpeningFilter::PrintManual() {
    std::cout << "\n";
    std::cout << "Filter name: sharp\n";
    std::cout << "Applies sharpening matrix to image\n";
    std::cout << "Filter args: None\n";
    std::cout << "Example: -sharp \n";
    std::cout << "\n";
}
void SharpeningFilter::Process(CImage &image, const std::vector<std::string> &args) {
    if(!args.empty()) {
        throw std::runtime_error("Invalid arguments passed into filter " + FILTER_NAME);
    }
    ApplyMatrix(image, SharpeningMatrix);
}