#ifndef __MD5_H__
#define __MD5_H__

#include <inttypes.h>

uint64_t getMessageLength(const unsigned char* src);
uint64_t getPaddingLength(const uint64_t k);
uint64_t getUint32BlockLength(const uint64_t k, const uint64_t p);
void padding(uint32_t* dst, const uint64_t len, const unsigned char* src, const uint64_t k);
void initCV(uint32_t dst[4]);
uint32_t circleLeftShift(uint32_t value, size_t bit);
void circleSwap(uint32_t dst[4]);
void hash(uint32_t dst[4], const uint32_t* y);

void md5(uint32_t dst[4], const unsigned char* src);

#endif // __MD5_H__
