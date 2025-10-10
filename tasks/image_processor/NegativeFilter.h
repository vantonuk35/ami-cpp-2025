#ifndef CPP_HSE_NEGATIVEFILTER_H
#define CPP_HSE_NEGATIVEFILTER_H

#include "IFilter.h"
class NegativeFilter : virtual public IFilter {
    void PrintManual() override;
    void Process(CImage& image, const std::vector<std::string>& args) override;
};


#endif  // CPP_HSE_NEGATIVEFILTER_H
