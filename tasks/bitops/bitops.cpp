#include "bitops.h"

#include <limits>
#include <memory>

/*
 * Achieving O(log(word_size)) instead of O(word_size) operations
 * for reverse functions using magic masks
 */
struct ParityTable {
    constexpr ParityTable() : mask() {
        for (size_t i = 0; i < IntegerSizeLog; i++) {
            for (size_t j = 0; j < std::numeric_limits<uint64_t>::digits; j++) {
                if (j & (1ull << i)) {
                    mask[i] |= (1ull << j);
                }
            }
        }
    }
    constexpr static int IntegerSizeLog = 6;
    uint64_t mask[IntegerSizeLog];
    constexpr static int BiggerThanByte = 3;
};
constexpr ParityTable MagicSource;
uint64_t SwapBytes(uint64_t value) {
    for (size_t i = MagicSource.BiggerThanByte; i < MagicSource.IntegerSizeLog; i++) {
        value = ((value & MagicSource.mask[i]) >> (1ull << i)) | ((value & ~MagicSource.mask[i]) << (1 << i));
    }
    return value;
}

uint64_t ReverseBits(uint64_t value) {
    for (size_t i = 0; i < MagicSource.IntegerSizeLog; i++) {
        value = ((value & MagicSource.mask[i]) >> (1ull << i)) | ((value & ~MagicSource.mask[i]) << (1 << i));
    }
    return value;
}

uint64_t ReverseBitsInBytes(uint64_t value) {
    for (size_t i = 0; i < MagicSource.BiggerThanByte; i++) {
        value = ((value & MagicSource.mask[i]) >> (1ull << i)) | ((value & ~MagicSource.mask[i]) << (1 << i));
    }
    return value;
}

uint64_t SetBits(uint64_t value, uint64_t offset, uint64_t count, uint64_t bits) {
    const size_t count_mask = (1ull << count) - 1;
    value = value & ~(count_mask << offset);
    value = value | ((bits & count_mask) << offset);
    return value;
}

uint64_t ExtractBits(uint64_t value, uint64_t offset, uint64_t count) {
    const size_t count_mask = (1ull << count) - 1;
    return (value >> offset) & count_mask;
}

uint32_t CountSetBits(uint64_t value) {
    size_t counter = 0;
    for (; value; value -= (value & -value)) {
        ++counter;
    }
    return counter;
}

uint32_t CountTrailingZeros(uint64_t value) {
    if (value == 0) {
        return std::numeric_limits<uint64_t>::digits;
    }
    int count = 0;
    while ((value & (1ull << count)) == 0) {
        ++count;
    }
    return count;
}

uint32_t CountLeadingZeros(uint64_t value) {
    value = ReverseBits(value);
    return CountTrailingZeros(value);
}

uint64_t RotateLeft(uint64_t value, uint32_t shift) {
    shift %= std::numeric_limits<uint64_t>::digits;
    return (value << shift) |
           (value >> ((std::numeric_limits<uint64_t>::digits - shift)) % std::numeric_limits<uint64_t>::digits);
}

uint64_t RotateRight(uint64_t value, uint32_t shift) {
    shift %= std::numeric_limits<uint64_t>::digits;
    return (value >> shift) |
           (value << ((std::numeric_limits<uint64_t>::digits - shift)) % std::numeric_limits<uint64_t>::digits);
}

bool IsPowerOfTwo(uint64_t value) {
    return CountSetBits(value) == 1;
}

uint64_t RoundUpToPowerOfTwo(uint64_t value) {
    if (CountLeadingZeros(value) == 0 && CountSetBits(value) > 1) {
        return 0;
    }
    int i = 0;
    while ((1ull << i) < value) {
        ++i;
    }
    return (1ull << i);
}

uint64_t AlignDown(uint64_t value, uint64_t alignment) {
    return value - value % alignment;
}

uint64_t AlignUp(uint64_t value, uint64_t alignment) {
    return value + (alignment - value % alignment) % alignment;
}
