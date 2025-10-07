#ifndef CPP_HSE_FISHEYEFILTER_H
#define CPP_HSE_FISHEYEFILTER_H

#include "../IFilter.h"

class FisheyeFilter : virtual public IFilter {
    void PrintManual() override;
    void Process(CImage& image, const std::vector<std::string>& args) override;
};


#endif  // CPP_HSE_FISHEYEFILTER_H
