#include "varint.h"

size_t DecodeVarint(const uint8_t* data, size_t size, uint64_t& result) {
    uint64_t tmp = 0;
    size_t current_block = 0;
    while (current_block < size) {
        for (size_t bit_offset = 0; bit_offset < 7; ++bit_offset) {
            if ((data[current_block] & (1 << bit_offset)) == 0) {
                continue;
            }
            if (bit_offset + current_block * 7 > 63) {
                return 0;
            }
            tmp |= (1ull << (bit_offset + current_block * 7));
        }
        if ((data[current_block++] & (1 << 7)) == 0) {
            break;
        }
        if (current_block == size) {
            return 0;
        }
    }
    result = tmp;
    return current_block;
}
