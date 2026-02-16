#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "BigInteger.h"

void test_Create() {
    BigInteger* bi = Create();
    assert(bi != NULL);
    assert(isEmpty(bi) == 1);
    Done(&bi);
    assert(bi == NULL);
    printf("[X] test_Create passed\n");
}

void test_isEmpty() {
    BigInteger* bi = Create();
    assert(isEmpty(bi) == 1);
    stringToBigInteger("123", bi);
    assert(isEmpty(bi) == 0);
    Done(&bi);
    printf("[X] test_isEmpty passed\n");
}

void test_stringToBigInteger_positive() {
    BigInteger* bi = Create();
    int result = stringToBigInteger("12345", bi);
    assert(result == 1);
    assert(bi->sign == 0);
    assert(isEmpty(bi) == 0);
    char* str = toString(bi);
    assert(str != NULL);
    assert(strcmp(str, "12345") == 0);
    free(str);
    Done(&bi);
    printf("[X] test_stringToBigInteger_positive passed\n");
}

void test_stringToBigInteger_negative() {
    BigInteger* bi = Create();
    int result = stringToBigInteger("-9876", bi);
    assert(result == 1);
    assert(bi->sign == 1);
    char* str = toString(bi);
    assert(str != NULL);
    assert(strcmp(str, "-9876") == 0);
    free(str);
    Done(&bi);
    printf("[X] test_stringToBigInteger_negative passed\n");
}

void test_toString() {
    BigInteger* bi = Create();
    stringToBigInteger("999999999", bi);
    char* str = toString(bi);
    assert(str != NULL);
    assert(strcmp(str, "999999999") == 0);
    free(str);
    Done(&bi);
    printf("[X] test_toString passed\n");
}

void test_clone() {
    BigInteger* bi1 = Create();
    stringToBigInteger("-42", bi1);
    
    BigInteger* bi2 = clone(bi1);
    assert(bi2 != NULL);
    assert(bi2->sign == bi1->sign);
    
    char* str1 = toString(bi1);
    char* str2 = toString(bi2);
    assert(strcmp(str1, str2) == 0);
    
    free(str1);
    free(str2);
    Done(&bi1);
    Done(&bi2);
    printf("[X] test_clone passed\n");
}

void test_count() {
    BigInteger* bi = Create();
    assert(count(bi) == 0);
    stringToBigInteger("123456789012345", bi);
    int cnt = count(bi);
    assert(cnt > 0);
    assert(cnt == 2);
    Done(&bi);
    printf("[X] test_count passed\n");
}

void test_isFull() {
    BigInteger* bi = Create();
    assert(isFull(bi) == 0);
    Done(&bi);
    printf("[X] test_isFull passed\n");
}

void test_makeEmpty() {
    BigInteger* bi = Create();
    stringToBigInteger("555", bi);
    assert(isEmpty(bi) == 0);
    int result = makeEmpty(bi);
    assert(result == 1);
    assert(isEmpty(bi) == 1);
    Done(&bi);
    printf("[X] test_makeEmpty passed\n");
}

void test_stringToBigInteger_largeNumber() {
    BigInteger* bi = Create();
    int result = stringToBigInteger("123456789123456789", bi);
    assert(result == 1);
    char* str = toString(bi);
    assert(str != NULL);
    assert(strcmp(str, "123456789123456789") == 0);
    free(str);
    Done(&bi);
    printf("[X] test_stringToBigInteger_largeNumber passed\n");
}

int main() {
    printf("Running BigInteger ADT tests...\n\n");
    
    test_Create();
    test_isEmpty();
    test_stringToBigInteger_positive();
    test_stringToBigInteger_negative();
    test_toString();
    test_clone();
    test_count();
    test_isFull();
    test_makeEmpty();
    test_stringToBigInteger_largeNumber();
    
    printf("\n[X] All tests passed!\n");
    return 0;
}