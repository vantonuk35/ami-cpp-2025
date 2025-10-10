#ifndef CPP_HSE_EDGEFILTER_H
#define CPP_HSE_EDGEFILTER_H

#include "IFilter.h"

class EdgeFilter : virtual public IFilter {
    constexpr const static Matrix<3> EdgeMatrix= { {
        std::array<float, 3>{0, -1, 0},
        std::array<float, 3>{-1, 4, -1},
        std::array<float, 3>{0, -1, 0}}
    };
    void PrintManual() override;
    void Process(CImage& image, const std::vector<std::string>& args) override;
};

#endif  // CPP_HSE_EDGEFILTER_H
