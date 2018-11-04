#include "debug.h"

void print_x(uint64_t value, int li, int lj) {
    for (int i = 0; i < li; i++) {
        for (int j = 0; j < lj; j++) {
            printf("%" PRIu64, value & 1);
            value >>= 1;
        }
        putchar(' ');
    }
    putchar('\n');
}

void print_uint4(uint4_t value) {
    print_x(value, 1, 4);
}

void print_uint6(uint6_t value) {
    print_x(value, 1, 6);
}

void print_uint32(uint32_t value) {
    print_x(value, 4, 8);
}

void print_uint48(uint48_t value) {
    print_x(value, 6, 8);
}

void print_uint56(uint56_t value) {
    print_x(value, 7, 8);
}

void print_uint64(uint64_t value) {
    print_x(value, 8, 8);
}

void print_unsigned_chars(unsigned char* value) {
    size_t i = 0;
    while (value[i]) {
        printf("%02x ", value[i]);
        i++;
        if (i % 24 == 0) {
            putchar('\n');
        }
    }
    if (i % 24 != 0) {
        putchar('\n');
    }
}
