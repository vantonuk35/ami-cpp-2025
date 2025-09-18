#include "fp16.h"

#include <limits>
#include <cmath>

float ConvertFloat16ToFloat(uint16_t float16_bits) {
    const int32_t mantissa_size = 10;
    const int32_t exponent_size = 5;
    const int32_t exponent_bias = 15;
    const int32_t mantissa = float16_bits & ((1 << mantissa_size) - 1);
    float16_bits >>= mantissa_size;
    const int32_t exponent = float16_bits & ((1 << exponent_size) - 1);
    float16_bits >>= exponent_size;
    float sign = (float16_bits ? -1.f : 1.f);
    const uint32_t nan_exponent = 0b11111;
    if (exponent == nan_exponent) {
        if (mantissa) {
            return std::numeric_limits<float>::quiet_NaN();
        }
        return std::numeric_limits<float>::infinity() * sign;
    }
    if (exponent == 0) {
        if (!mantissa) {
            return 0.f * sign;
        }
        return std::ldexp(static_cast<float>(mantissa), -(mantissa_size + exponent_bias - 1)) * sign;
    }
    return sign * static_cast<float>(
                      std::ldexp(static_cast<float>(mantissa) / pow(2, mantissa_size) + 1.f, exponent - exponent_bias));
}
