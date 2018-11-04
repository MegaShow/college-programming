#include <string.h>

#include "des.h"
#include "table.h"

uint64_t ip_permute(uint64_t value) {
    uint64_t res = 0;
    for (int i = 0; i < 64; i++) {
        res |= (value >> (IP_TABLE[i] - 1) & 1) << i;
    }
    return res;
}

uint64_t ip_inverse_permute(uint64_t value) {
    uint64_t res = 0;
    for (int i = 0; i < 64; i++) {
        res |= (value >> (IP_INVERSE_TABLE[i] - 1) & 1) << i;
    }
    return res;
}

uint32_t p_permute(uint32_t value) {
    uint32_t res = 0;
    for (int i = 0; i < 32; i++) {
        res |= (value >> (P_TABLE[i] - 1) & 1) << i;
    }
    return res;
}

uint56_t pc1_permute(uint64_t value) {
    uint56_t res = 0;
    for (int i = 0; i < 56; i++) {
        res |= (value >> (PC1_TABLE[i] - 1) & 1) << i;
    }
    return res;
}

uint48_t pc2_permute(uint56_t value) {
    uint48_t res = 0;
    for (int i = 0; i < 48; i++) {
        res |= (value >> (PC2_TABLE[i] - 1) & 1) << i;
    }
    return res;
}

uint48_t e_extend(uint32_t value) {
    uint48_t res = 0;
    for (size_t i = 0; i < 48; i++) {
        res |= ((uint48_t)value >> (EXTEND_TABLE[i] - 1) & 1) << i;
    }
    return res;
}

uint4_t s_box(uint6_t b, size_t s) {
    size_t n = (b & 1) << 1 | (b >> 5 & 1);
    size_t m = (b >> 1 & 1) << 3 | (b >> 2 & 1) << 2 | (b >> 3 & 1) << 1 | (b >> 4 & 1);
    return S_BOX[s][n][m];
}

uint64_t iterate(uint64_t value, uint48_t k) {
    uint64_t res = value >> 32;
    res |= ((value & 0xffffffffL) ^ feistel(res, k)) << 32;
    return res;
}

uint32_t feistel(uint32_t r, uint48_t k) {
    uint48_t s = e_extend(r) ^ k;
    uint32_t res = 0;
    for (int i = 0; i < 8; i++) {
        res |= (uint32_t)s_box(s >> i * 6 & 0x3f, i) << i * 4;
    }
    return p_permute(res);
}

void swap_left_right(uint64_t* value_p) {
    uint64_t tmp = *value_p >> 32;
    *value_p <<= 32;
    *value_p |= tmp;
}

void left_shift(uint56_t* value_p) {
    uint56_t c_lm = *value_p & 1, r_lm = *value_p >> 28 & 1;
    *value_p = (*value_p >> 1 & 0x7fffffff7ffffffL) | c_lm << 27 | r_lm << 55;
}

uint64_t block_encrypt(uint64_t value, uint64_t key) {
    value = ip_permute(value);
    uint56_t k0 = pc1_permute(key);
    for (int i = 1; i <= 16; i++) {
        if (i != 1 && i != 2 && i != 9 && i != 16) {
            left_shift(&k0);
        }
        left_shift(&k0);
        uint48_t k = pc2_permute(k0);
        value = iterate(value, k);
    }
    swap_left_right(&value);
    value = ip_inverse_permute(value);
    return value;
}

uint64_t block_decrypt(uint64_t value, uint64_t key) {
    value = ip_permute(value);
    uint56_t k0 = pc1_permute(key);
    uint48_t k[16] = {0};
    for (int i = 1; i <= 16; i++) {
        if (i != 1 && i != 2 && i != 9 && i != 16) {
            left_shift(&k0);
        }
        left_shift(&k0);
        k[i-1] = pc2_permute(k0);
    }
    for (int i = 1; i <= 16; i++) {
        value = iterate(value, k[16-i]);
    }
    swap_left_right(&value);
    value = ip_inverse_permute(value);
    return value;
}

uint64_t to_int64(unsigned char* src) {
    uint64_t dst;
    for (size_t i = 0; i < 8; i++) {
        dst <<= 8;
        dst |= src[i];
    }
    return dst;
}

void to_unsigned_char_4(unsigned char* dst, uint64_t src) {
    for (size_t i = 0; i < 8; i++) {
        dst[7 - i] = src & 0xff;
        src >>= 8;
    }
}

size_t encrypt(unsigned char* dst, unsigned char* src, size_t len, uint64_t key) {
    unsigned char copy[len + 8];
    memmove(copy, src, len);
    if (len % 8 == 0) {
        len += 8;
        memset(copy + len, 0x08, 8);
    } else {
        size_t rest = 8 - len % 8;
        memset(copy + len, rest, rest);
        len += rest;
    }
    for (size_t i = 0; i < len; i += 8) {
        uint64_t value = to_int64(copy + i);
        value = block_encrypt(value, key);
        to_unsigned_char_4(dst + i, value);
    }
    dst[len] = 0;
    return len;
}

size_t decrypt(unsigned char* dst, unsigned char* src, size_t len, uint64_t key) {
    for (size_t i = 0; i < len; i += 8) {
        uint64_t value = to_int64(src + i);
        value = block_decrypt(value, key);
        to_unsigned_char_4(dst + i, value);
    }
    len -= dst[len - 1];
    dst[len] = 0;
    return len;
}
