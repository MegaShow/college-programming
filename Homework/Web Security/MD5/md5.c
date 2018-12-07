#include <stdio.h>
#include <string.h>

#include "constant.h"
#include "md5.h"

uint64_t getMessageLength(const unsigned char* src) {
    return strlen((const char*)src) * 8;
}

uint64_t getPaddingLength(const size_t k) {
    return (448 + 512 - k % 512) % 512 != 0 ? (448 + 512 - k % 512) % 512 : 512;
}

uint64_t getUint32BlockLength(const uint64_t k, const uint64_t p) {
    return (k + p + 64) / 32;
}

void padding(uint32_t* dst, const uint64_t len, const unsigned char* src, const uint64_t k) {
    uint64_t i, j;
    for (i = 0; src[i*4] && src[i*4+1] && src[i*4+2] && src[i*4+3]; i++) {
        dst[i] = ((uint32_t) src[i*4]) | ((uint32_t) src[i*4+1]) << 8 | ((uint32_t) src[i*4+2]) << 16 | ((uint32_t) src[i*4+3]) << 24;
    }
    dst[i] = 0;
    for (j = 0; src[i*4+j]; j++) {
        dst[i] |= src[i*4+j] << (8 * j);
    }
    dst[i] |= PADDING_1 << (8 * j);
    for (i++; i < len - 2; i++) {
        dst[i] = PADDING_0;
    }
    dst[i] = k & 0xffffffff;
    dst[i+1] = (k >> 32) & 0xffffffff;
}

void initCV(uint32_t dst[4]) {
    dst[0] = IV_A;
    dst[1] = IV_B;
    dst[2] = IV_C;
    dst[3] = IV_D;
}

uint32_t circleLeftShift(uint32_t value, size_t bit) {
    for (size_t i = 0; i < bit; i++) {
        uint32_t lm = (value >> 31) & 1;
        value <<= 1;
        value |= lm;
    }
    return value;
}

void circleSwap(uint32_t dst[4]) {
    uint32_t tmp = dst[3];
    dst[3] = dst[2];
    dst[2] = dst[1];
    dst[1] = dst[0];
    dst[0] = tmp;
}

void hash(uint32_t dst[4], const uint32_t* y) {
    for (size_t i = 0; i < 4; i++) {
        for (size_t k = 0; k < 16; k++) {
            dst[0] = dst[1] + circleLeftShift((dst[0] + FUNC[i](dst[1], dst[2], dst[3]) + y[TABLE_X[i][k]] + TABLE_T[i*16+k]), TABLE_S[i][k]);
            circleSwap(dst);
        }
    }
}

void md5(uint32_t dst[4], const unsigned char* src) {
    uint64_t k = getMessageLength(src);
    uint64_t p = getPaddingLength(k);
    uint64_t len = getUint32BlockLength(k, p);
    uint32_t message[len], prev[4];
    padding(message, len, src, k);
    initCV(dst);
    for (uint64_t i = 0; i < len; i += 16) {
        memmove(prev, dst, 4 * sizeof(uint32_t));
        hash(dst, message + i);
        for (size_t j = 0; j < 4; j++) {
            dst[j] += prev[j];
        }
    }
}
