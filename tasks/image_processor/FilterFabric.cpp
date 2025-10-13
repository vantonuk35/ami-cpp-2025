#include "FilterFabric.h"
#include <iostream>
std::map<std::string, std::shared_ptr<IFilter>> FilterFabric::registered_filters;

std::shared_ptr<IFilter> FilterFabric::Create(const std::string &filter_name) {
    if (!registered_filters.contains(filter_name)) {
        throw std::runtime_error("No filter with name " + filter_name);
    }
    return registered_filters[filter_name];
}
void FilterFabric::PrintManual() {
    std::cout << "Available filters: \n";
    for (const auto &[filter_name, filter_instance] : registered_filters) {
        filter_instance->PrintManual();
    }
}
void FilterFabric::RegisterFilter(const std::string &filter_name, std::shared_ptr<IFilter> filter_instance) {
    registered_filters.emplace(filter_name, filter_instance);
}
