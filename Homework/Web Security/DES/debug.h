#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

#include "type.h"

void print_x(uint64_t value, int li, int lj);

void print_uint4(uint4_t value);
void print_uint6(uint6_t value);
void print_uint32(uint32_t value);
void print_uint48(uint48_t value);
void print_uint56(uint56_t value);
void print_uint64(uint64_t value);

void print_unsigned_chars(unsigned char* value);

#endif // __DEBUG_H__
