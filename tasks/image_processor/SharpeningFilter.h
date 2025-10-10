#ifndef CPP_HSE_SHARPENINGFILTER_H
#define CPP_HSE_SHARPENINGFILTER_H
#include "IFilter.h"

class SharpeningFilter : virtual public IFilter {
    constexpr const static Matrix<3> SharpeningMatrix= { {
        std::array<float, 3>{0, -1, 0},
        std::array<float, 3>{-1, 5, -1},
        std::array<float, 3>{0, -1, 0}}
    };
    void PrintManual() override;
    void Process(CImage& image, const std::vector<std::string>& args) override;
};


#endif  // CPP_HSE_SHARPENINGFILTER_H
