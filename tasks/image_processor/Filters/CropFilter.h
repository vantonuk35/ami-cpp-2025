#ifndef CPP_HSE_CROPFILTER_H
#define CPP_HSE_CROPFILTER_H

#include "../IFilter.h"

class CropFilter : virtual public IFilter {
    void PrintManual() override;
    void Process(CImage& image, const std::vector<std::string>& args) override;
};

#endif  // CPP_HSE_CROPFILTER_H
