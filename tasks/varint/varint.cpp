#include "varint.h"

size_t DecodeVarint(const uint8_t* data, size_t size, uint64_t& result) {
    static constexpr size_t BlockSize = 7;
    static constexpr size_t ContinuationBit = (1 << BlockSize);
    static constexpr size_t ValuableMask = ContinuationBit - 1;
    static constexpr size_t CornerOctet = 9;
    uint64_t tmp = 0;
    size_t current_block = 0;
    while (current_block < size) {
        if (current_block == CornerOctet && data[current_block] > 1) {
            return 0;
        }
        tmp |= (data[current_block] & ValuableMask) << (current_block * BlockSize);
        if ((data[current_block++] & ContinuationBit) == 0) {
            break;
        }
        if (current_block == size) {
            return 0;
        }
    }
    result = tmp;
    return current_block;
}
