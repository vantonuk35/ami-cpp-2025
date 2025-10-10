#ifndef CPP_HSE_GRAYSCALEFILTER_H
#define CPP_HSE_GRAYSCALEFILTER_H

#include "IFilter.h"
class GrayscaleFilter : virtual public IFilter {
    void PrintManual() override;
    void Process(CImage& image, const std::vector<std::string>& args) override;
};



#endif  // CPP_HSE_GRAYSCALEFILTER_H
