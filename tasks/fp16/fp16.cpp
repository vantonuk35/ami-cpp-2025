#include "fp16.h"

#include <algorithm>
#include <limits>
#include <cmath>

float ConvertFloat16ToFloat(uint16_t float16_bits) {
    static constexpr int32_t MantissaSize = 10;
    static constexpr int32_t ExponentSize = 5;
    static constexpr int32_t ExponentBias = 15;
    static constexpr int32_t MantissaMask = (1 << MantissaSize) - 1;
    static constexpr int32_t ExponentMask = (1 << MantissaSize) - 1;
    static constexpr float MantissaMax = 1024.f;
    static constexpr uint32_t NanExponent = 0b11111;

    const int32_t mantissa = float16_bits & MantissaMask;
    float16_bits >>= MantissaSize;
    const int32_t exponent = float16_bits & ExponentMask;
    float16_bits >>= ExponentSize;
    const float sign = (float16_bits ? -1.f : 1.f);

    if (exponent == NanExponent) {
        if (mantissa) {
            return std::numeric_limits<float>::quiet_NaN();
        }
        return std::numeric_limits<float>::infinity() * sign;
    }

    const float mantissa_32 = static_cast<float>(mantissa) / MantissaMax + static_cast<float>(exponent != 0);
    return sign * std::ldexp(mantissa_32, std::max(exponent, 1) - ExponentBias);
}
