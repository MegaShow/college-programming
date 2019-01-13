#ifndef __DES_H__
#define __DES_H__

#include "type.h"

uint64_t ip_permute(uint64_t value);
uint64_t ip_inverse_permute(uint64_t value);
uint32_t p_permute(uint32_t value);
uint56_t pc1_permute(uint64_t value);
uint48_t pc2_permute(uint56_t value);
uint48_t e_extend(uint32_t value);
uint4_t s_box(uint6_t b, size_t s);

uint64_t iterate(uint64_t value, uint48_t k);
uint32_t feistel(uint32_t r, uint48_t k);
void swap_left_right(uint64_t* value_p);
void left_shift(uint56_t* value_p);

uint64_t block_encrypt(uint64_t value, uint64_t key);
uint64_t block_decrypt(uint64_t value, uint64_t key);

uint64_t to_int64(unsigned char* src);
void to_unsigned_char_4(unsigned char* dst, uint64_t src);

size_t encrypt(unsigned char* dst, unsigned char* src, size_t len, uint64_t key);
size_t decrypt(unsigned char* dst, unsigned char* src, size_t len, uint64_t key);

#endif // __DES_H__
