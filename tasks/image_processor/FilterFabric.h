#ifndef CPP_HSE_FILTERFABRIC_H
#define CPP_HSE_FILTERFABRIC_H

#include <map>
#include <memory>
#include <vector>
#include "IFilter.h"
template <typename T>
concept DerivedFromIFilter = std::is_base_of_v<IFilter, T>;

class FilterFabric {
    static std::map<std::string, std::shared_ptr<IFilter>> registered_filters;

public:
    static void RegisterFilter(const std::string& filter_name, std::shared_ptr<IFilter> filter_instance);
    static std::shared_ptr<IFilter> Create(const std::string& filter_name);
    static void PrintManual();
    template <DerivedFromIFilter T>
    class Registrator {
    public:
        explicit Registrator(const std::string& filter_name) {
            FilterFabric::RegisterFilter(filter_name, std::make_shared<T>());
        }
    };
};

#endif  // CPP_HSE_FILTERFABRIC_H
