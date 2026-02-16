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

void test_add_positive_numbers() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    stringToBigInteger("100100100", bi1);
    stringToBigInteger("899899900", bi2);
    
    BigInteger* result = add(bi1, bi2);
    assert(result != NULL);
    char* str = toString(result);
    assert(str != NULL);
    assert(strcmp(str, "1000000000") == 0);
    free(str);
    
    Done(&bi1);
    Done(&bi2);
    Done(&result);
    printf("[X] test_add_positive_numbers passed\n");
}

void test_add_negative_numbers() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    stringToBigInteger("-3584148", bi1);
    stringToBigInteger("-200", bi2);
    
    BigInteger* result = add(bi1, bi2);
    assert(result != NULL);
    char* str = toString(result);
    assert(str != NULL);
    assert(strcmp(str, "-3584348") == 0);
    free(str);
    
    Done(&bi1);
    Done(&bi2);
    Done(&result);
    printf("[X] test_add_negative_numbers passed\n");
}

void test_add_mixed_signs() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    stringToBigInteger("100", bi1);
    stringToBigInteger("-200", bi2);
    
    BigInteger* result = add(bi1, bi2);
    assert(result != NULL);
    char* str = toString(result);
    assert(str != NULL);
    assert(strcmp(str, "-100") == 0);
    free(str);
    
    Done(&bi1);
    Done(&bi2);
    Done(&result);
    printf("[X] test_add_mixed_signs passed\n");
}

void test_add_zero() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    stringToBigInteger("0", bi1);
    stringToBigInteger("789", bi2);
    
    BigInteger* result = add(bi1, bi2);
    assert(result != NULL);
    char* str = toString(result);
    assert(str != NULL);
    assert(strcmp(str, "789") == 0);
    free(str);
    
    Done(&bi1);
    Done(&bi2);
    Done(&result);
    printf("[X] test_add_zero passed\n");
}

void test_add_last_zero() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    stringToBigInteger("1000000000", bi1);
    stringToBigInteger("-2", bi2);
    
    BigInteger* result = add(bi1, bi2);
    assert(result != NULL);
    char* str = toString(result);
    assert(str != NULL);
    assert(strcmp(str, "999999998") == 0);
    free(str);
    
    Done(&bi1);
    Done(&bi2);
    Done(&result);
    printf("[X] test_add_last_zero passed\n");
}

void test_sub_positive_numbers() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    stringToBigInteger("1000000000", bi1);
    stringToBigInteger("100100100", bi2);
    
    BigInteger* result = sub(bi1, bi2);
    assert(result != NULL);
    char* str = toString(result);
    assert(str != NULL);
    assert(strcmp(str, "899899900") == 0);
    free(str);
    
    Done(&bi1);
    Done(&bi2);
    Done(&result);
    printf("[X] test_sub_positive_numbers passed\n");
}

void test_sub_negative_numbers() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    stringToBigInteger("-3584348", bi1);
    stringToBigInteger("-200", bi2);
    
    BigInteger* result = sub(bi1, bi2);
    assert(result != NULL);
    char* str = toString(result);
    assert(str != NULL);
    assert(strcmp(str, "-3584148") == 0);
    free(str);
    
    Done(&bi1);
    Done(&bi2);
    Done(&result);
    printf("[X] test_sub_negative_numbers passed\n");
}

void test_sub_mixed_signs() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    stringToBigInteger("100", bi1);
    stringToBigInteger("-200", bi2);
    
    BigInteger* result = sub(bi1, bi2);
    assert(result != NULL);
    char* str = toString(result);
    assert(str != NULL);
    assert(strcmp(str, "300") == 0);
    free(str);
    
    Done(&bi1);
    Done(&bi2);
    Done(&result);
    printf("[X] test_sub_mixed_signs passed\n");
}

void test_sub_zero() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    stringToBigInteger("789", bi1);
    stringToBigInteger("0", bi2);
    
    BigInteger* result = sub(bi1, bi2);
    assert(result != NULL);
    char* str = toString(result);
    assert(str != NULL);
    assert(strcmp(str, "789") == 0);
    free(str);
    
    Done(&bi1);
    Done(&bi2);
    Done(&result);
    printf("[X] test_sub_zero passed\n");
}

void test_sub_same_numbers() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    stringToBigInteger("12345", bi1);
    stringToBigInteger("12345", bi2);
    
    BigInteger* result = sub(bi1, bi2);
    assert(result != NULL);
    char* str = toString(result);
    assert(str != NULL);
    assert(strcmp(str, "0") == 0);
    free(str);
    
    Done(&bi1);
    Done(&bi2);
    Done(&result);
    printf("[X] test_sub_same_numbers passed\n");
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

    // Add
    test_add_positive_numbers();
    test_add_negative_numbers();
    test_add_mixed_signs();
    test_add_zero();
    test_add_last_zero();

    // Sub 
    test_sub_positive_numbers();
    test_sub_negative_numbers();
    test_sub_mixed_signs();
    test_sub_zero();
    test_sub_same_numbers();
    
    printf("\n[X] All tests passed!\n");
    return 0;
}