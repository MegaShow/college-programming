#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "debug.h"
#include "des.h"

bool standard_test_1() {
    printf("\nStandard Test 1:\n");
    unsigned char src[1000] = "Zhenly is very vegetable.";
    unsigned char dst[1000], cache[1000];
    uint64_t key = 0x0102830485860708;
    size_t len = strlen((char*)src) + 1;
    printf("Input plain text: %s (%zu)\n", src, len);
    printf("Input key: ");
    print_uint64(key);
    size_t clen = encrypt(cache, src, len, key);
    printf("Encrypt: (%zu)\n", clen);
    print_unsigned_chars(cache);
    clen = decrypt(dst, cache, clen, key);
    printf("Decrypt: %s (%zu)\n", dst, clen);
    for (size_t i = 0; i < len; i++) {
        if (src[i] != dst[i]) {
            return false;
        }
    }
    return true;
}

bool standard_test_2() {
    printf("\nStandard Test 2:\n");
    unsigned char src[5000] = "The Data Encryption Standard (DES /ˌdiːˌiːˈɛs, dɛz/) is a symmetric-key algorithm for the encryption of electronic data. "
        "Although insecure, it was highly influential in the advancement of modern cryptography.\n"
        "Developed in the early 1970s at IBM and based on an earlier design by Horst Feistel, the algorithm was submitted to the National Bureau of "
        "Standards (NBS) following the agency's invitation to propose a candidate for the protection of sensitive, unclassified electronic government data. "
        "In 1976, after consultation with the National Security Agency (NSA), the NBS eventually selected a slightly modified version (strengthened against "
        "differential cryptanalysis, but weakened against brute-force attacks), which was published as an official Federal Information Processing Standard "
        "(FIPS) for the United States in 1977.\n"
        "The publication of an NSA-approved encryption standard simultaneously resulted in its quick international adoption and widespread academic scrutiny. "
        "Controversies arose out of classified design elements, a relatively short key length of the symmetric-key block cipher design, and the involvement of "
        "the NSA, nourishing suspicions about a backdoor. Today it is known that the S-boxes that had raised those suspicions were in fact designed by the NSA "
        "to actually remove a backdoor they secretly knew (differential cryptanalysis). However, the NSA also ensured that the key size was drastically reduced "
        "such that they could break it by brute force attack.[2] The intense academic scrutiny the algorithm received over time led to the modern understanding "
        "of block ciphers and their cryptanalysis.\n"
        "DES, as stated above, is insecure. This is mainly due to the 56-bit key size being too small. In January 1999, distributed.net and the Electronic "
        "Frontier Foundation collaborated to publicly break a DES key in 22 hours and 15 minutes (see chronology). There are also some analytical results "
        "which demonstrate theoretical weaknesses in the cipher, although they are infeasible to mount in practice. The algorithm is believed to be practically "
        "secure in the form of Triple DES, although there are theoretical attacks. This cipher has been superseded by the Advanced Encryption Standard (AES). "
        "Furthermore, DES has been withdrawn as a standard by the National Institute of Standards and Technology.\n"
        "Some documentation makes a distinction between DES as a standard and as an algorithm, referring to the algorithm as the DEA (Data Encryption Algorithm).\n";
    unsigned char dst[5000], cache[5000];
    uint64_t key = 0x0102830485860708;
    size_t len = strlen((char*)src) + 1;
    printf("Input plain text: %s (%zu)\n", src, len);
    printf("Input key: ");
    print_uint64(key);
    size_t clen = encrypt(cache, src, len, key);
    printf("Encrypt: (%zu)\n", clen);
    print_unsigned_chars(cache);
    clen = decrypt(dst, cache, clen, key);
    printf("Decrypt: %s (%zu)\n", dst, clen);
    for (size_t i = 0; i < len; i++) {
        if (src[i] != dst[i]) {
            return false;
        }
    }
    return true;
}

bool input_test() {
    printf("\nInput Test:\n");
    unsigned char src[1000], dst[1000], cache[1000];
    uint64_t key;
    printf("Input plain text: ");
    fgets((char*)src, 999, stdin);
    size_t len = strlen((char*)src);
    src[len - 1] = 0;
    printf("Len: (%zu)\n", len);
    printf("Input key: ");
    scanf("%" PRIu64, &key);
    printf("Binary key: ");
    print_uint64(key);
    size_t clen = encrypt(cache, src, len, key);
    printf("Encrypt: (%zu)\n", clen);
    print_unsigned_chars(cache);
    clen = decrypt(dst, cache, clen, key);
    printf("Decrypt: %s (%zu)\n", dst, clen);
    for (size_t i = 0; i < len; i++) {
        if (src[i] != dst[i]) {
            return false;
        }
    }
    return true;
}

void check(bool accept) {
    if (accept) {
        printf("Test Accept\n");
    } else {
        printf("Test Fail\n");
    }
}

int main(void) {
    check(standard_test_1());
    check(standard_test_2());
    check(input_test());
}
