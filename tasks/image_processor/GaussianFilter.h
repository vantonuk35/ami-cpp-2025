#ifndef CPP_HSE_GAUSSIANFILTER_H
#define CPP_HSE_GAUSSIANFILTER_H

#include "IFilter.h"
class GaussianFilter : virtual public IFilter {
    void PrintManual() override;
    void Process(CImage& image, const std::vector<std::string>& args) override;
};

#endif  // CPP_HSE_GAUSSIANFILTER_H
