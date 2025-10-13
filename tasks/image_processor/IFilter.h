#ifndef CPP_HSE_IFILTER_H
#define CPP_HSE_IFILTER_H

#include <vector>
#include <string>
#include "CImage.h"

class IFilter {
public:
    virtual void Process(CImage& image, const std::vector<std::string>& args) = 0;
    virtual void PrintManual() = 0;
    virtual ~IFilter() = default;

protected:
    template <int MatrixSize>
        requires(MatrixSize % 2 != 0 && MatrixSize > 0)
    class Matrix {
    public:
        std::array<std::array<float, MatrixSize>, MatrixSize> data;
    };
    template <int MatrixSize>
        requires(MatrixSize % 2 != 0)
    void ApplyMatrix(CImage& image, Matrix<MatrixSize> mt) {
        CImage res(image.GetWidth(), image.GetHeight());
        for (int32_t y = 0; y < res.GetHeight(); ++y) {
            for (int32_t x = 0; x < res.GetWidth(); ++x) {
                for (int32_t dy = -MatrixSize / 2; dy <= MatrixSize / 2; ++dy) {
                    for (int32_t dx = -MatrixSize / 2; dx <= MatrixSize / 2; ++dx) {
                        res.GetPixel(x, y).colors += mt.data[dy + MatrixSize / 2][dx + MatrixSize / 2] *
                                                     image.GetNearestPixel(x + dx, y + dy).colors;
                    }
                }
                res.GetPixel(x, y).Normalize();
            }
        }
        image = res;
    }
};

#endif  // CPP_HSE_IFILTER_H
