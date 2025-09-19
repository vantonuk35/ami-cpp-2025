#include "safe_arithmetic.h"

#include <algorithm>
#include <limits>

bool SafeAdd(int64_t a, int64_t b, int64_t& result) {
    if (std::min(a, b) >= 0 && std::numeric_limits<int64_t>::max() - a < b) {
        return false;
    }
    if (std::max(a, b) <= 0 && std::numeric_limits<int64_t>::min() - b > a) {
        return false;
    }
    result = a + b;
    return true;
}

bool SafeSubtract(int64_t a, int64_t b, int64_t& result) {
    if (a >= 0 && b <= 0 && std::numeric_limits<int64_t>::max() + b < a) {
        return false;
    }
    if (a <= 0 && b >= 0 && std::numeric_limits<int64_t>::min() + b > a) {
        return false;
    }
    result = a - b;
    return true;
}

bool SafeMultiply(int64_t a, int64_t b, int64_t& result) {
    if (a == 0 || b == 0 || a == 1 || b == 1) {
        result = a * b;
        return true;
    }
    if (std::min(a, b) == std::numeric_limits<int64_t>::min()) {
        return false;
    }
    if (a < 0) {
        a = -a;
        b = -b;
    }
    if (b > 0 && std::numeric_limits<int64_t>::max() / b < a) {
        return false;
    }
    if (b < 0 && std::numeric_limits<int64_t>::min() / b < a) {
        return false;
    }
    result = a * b;
    return true;
}

bool SafeDivide(int64_t a, int64_t b, int64_t& result) {
    if (b == 0) {
        return false;
    }
    if (b == -1 && a == std::numeric_limits<int64_t>::min()) {
        return false;
    }
    result = a / b;
    return true;
}
