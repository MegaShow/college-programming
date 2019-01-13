#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

char* convertInt32ArrayToString(char dst[33], const uint32_t src[4]) {
    for (size_t i = 0; i < 32; i += 2) {
        uint8_t value = (src[i/8] >> (i%8*4)) & 0xff;
        dst[i] = (value / 16 >= 10 ? 'A' - 10 : '0') + value / 16;
        dst[i+1] = (value % 16 >= 10 ? 'A' - 10 : '0') + value % 16;
    }
    dst[32] = 0;
    return dst;
}

uint32_t* convertStringToInt32Array(uint32_t dst[4], const char* src) {
    for (size_t i = 0; i < 4; i++) {
        dst[i] = 0;
        for (size_t j = 0; j < 8; j += 2) {
            if (j != 0) {
                dst[i] <<= 4;
            }
            if (src[i*8+6-j] >= 'A' && src[i*8+6-j] <= 'F') {
                dst[i] += src[i*8+6-j] - 'A' + 10;
            } else {
                dst[i] += src[i*8+6-j] - '0';
            }
            dst[i] <<= 4;
            if (src[i*8+7-j] >= 'A' && src[i*8+7-j] <= 'F') {
                dst[i] += src[i*8+7-j] - 'A' + 10;
            } else {
                dst[i] += src[i*8+7-j] - '0';
            }
        }
    }
    return dst;
}

bool check(const uint32_t expected[4], const uint32_t actual[4]) {
    for (size_t i = 0; i < 4; i++) {
        if (expected[i] != actual[i]) {
            return false;
        }
    }
    return true;
}

void test(int testcase, const char* res, const char* src) {
    uint32_t dst[4], tmpint[4];
    char tmpstr[33];
    md5(dst, (const unsigned char*) src);
    printf("Test %d\n", testcase);
    printf("Message: %s\n", src);
    printf("Expected MD5: %s\n", res);
    printf("Actual MD5: %s\n", convertInt32ArrayToString(tmpstr, dst));
    if (check(convertStringToInt32Array(tmpint, res), dst)) {
        printf("Test Accept\n\n");
    } else {
        printf("Test Wrong Answer\n\n");
        exit(2);
    }
}

void input() {
    unsigned char src[1000];
    char tmpstr[33];
    uint32_t dst[4];
    printf("Please input messages: ");
    fgets((char*)src, 999, stdin);
    size_t len = strlen((char*)src);
    src[len - 1] = 0;
    md5(dst, src);
    printf("MD5: %s\n", convertInt32ArrayToString(tmpstr, dst));
}

int main(void) {
    // Test from https://rosettacode.org/wiki/MD5/Implementation_Debug
    test(1, "D41D8CD98F00B204E9800998ECF8427E", "");
    test(2, "0CC175B9C0F1B6A831C399E269772661", "a");
    test(3, "900150983CD24FB0D6963F7D28E17F72", "abc");
    test(4, "F96B697D7CB7938D525A2F31AAF161D0", "message digest");
    test(5, "C3FCD3D76192E4007DFB496CCA67E13B", "abcdefghijklmnopqrstuvwxyz");
    test(6, "D174AB98D277D9F5A5611C2C9F419D9F", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    test(7, "57EDF4A22BE3C955AC49DA2E2107B67A", "12345678901234567890123456789012345678901234567890123456789012345678901234567890");

    // Standard Test
    test(8, "9476939352B60788B64C6EAC1C504F3F", "MegaShow");
    test(9, "7193551A825044683DA074FAB296950B", "Zhenly is very vegetable.");
    test(10, "CFD15B5BF752AD3CA821C31997AFE577", "The MD5 message-digest algorithm is a widely used hash function producing a 128-bit \
hash value. Although MD5 was initially designed to be used as a cryptographic hash function, it has been found to suffer from \
extensive vulnerabilities. It can still be used as a checksum to verify data integrity, but only against unintentional corruption. \
It remains suitable for other non-cryptographic purposes, for example for determining the partition for a particular key in a \
partitioned database.[3]\r\n\
One basic requirement of any cryptographic hash function is that it should be computationally infeasible to find two distinct messages \
which hash to the same value. MD5 fails this requirement catastrophically; such collisions can be found in seconds on an ordinary home computer.\r\n\
The weaknesses of MD5 have been exploited in the field, most infamously by the Flame malware in 2012. The CMU Software Engineering \
Institute considers MD5 essentially \"cryptographically broken and unsuitable for further use\".[4]\r\n\
MD5 was designed by Ronald Rivest in 1991 to replace an earlier hash function MD4,[5] and was specified in 1992 as RFC 1321.");

    input();
}
