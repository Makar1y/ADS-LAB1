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
    assert(result == 0);
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
    assert(result == 0);
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
    assert(cnt == (strlen("123456789012345") % BASE_POW) == 0 ? (strlen("123456789012345") / BASE_POW) : (strlen("123456789012345") / BASE_POW) + 1);
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
    assert(result == 0);
    assert(isEmpty(bi) == 1);
    Done(&bi);
    printf("[X] test_makeEmpty passed\n");
}

void test_stringToBigInteger_largeNumber() {
    BigInteger* bi = Create();
    int result = stringToBigInteger("1234567891234567895791479245", bi);
    assert(result == 0);
    char* str = toString(bi);
    assert(str != NULL);
    assert(strcmp(str, "1234567891234567895791479245") == 0);
    free(str);
    Done(&bi);
    printf("[X] test_stringToBigInteger_largeNumber passed\n");
}

void test_add_positive_numbers() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    stringToBigInteger("1000000000000000000000000000", bi1);
    stringToBigInteger("9000000000000000000000000000", bi2);
    
    BigInteger* result = add(bi1, bi2);
    assert(result != NULL);
    char* str = toString(result);
    assert(str != NULL);
    assert(strcmp(str, "10000000000000000000000000000") == 0);
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

void test_mul_positive_numbers() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    stringToBigInteger("123", bi1);
    stringToBigInteger("456", bi2);
    
    BigInteger* result = mul(bi1, bi2);
    assert(result != NULL);
    char* str = toString(result);
    assert(str != NULL);
    assert(strcmp(str, "56088") == 0);
    free(str);
    
    Done(&bi1);
    Done(&bi2);
    Done(&result);
    printf("[X] test_mul_positive_numbers passed\n");
}

void test_mul_negative_numbers() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    stringToBigInteger("-50", bi1);
    stringToBigInteger("-20", bi2);
    
    BigInteger* result = mul(bi1, bi2);
    assert(result != NULL);
    char* str = toString(result);
    assert(str != NULL);
    assert(strcmp(str, "1000") == 0);
    free(str);
    
    Done(&bi1);
    Done(&bi2);
    Done(&result);
    printf("[X] test_mul_negative_numbers passed\n");
}

void test_mul_mixed_signs() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    stringToBigInteger("25", bi1);
    stringToBigInteger("-4", bi2);
    
    BigInteger* result = mul(bi1, bi2);
    assert(result != NULL);
    char* str = toString(result);
    assert(str != NULL);
    assert(strcmp(str, "-100") == 0);
    free(str);
    
    Done(&bi1);
    Done(&bi2);
    Done(&result);
    printf("[X] test_mul_mixed_signs passed\n");
}

void test_mul_by_zero() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    stringToBigInteger("999999", bi1);
    stringToBigInteger("0", bi2);
    
    BigInteger* result = mul(bi1, bi2);
    assert(result != NULL);
    char* str = toString(result);
    assert(str != NULL);
    assert(strcmp(str, "0") == 0);
    free(str);
    
    Done(&bi1);
    Done(&bi2);
    Done(&result);
    printf("[X] test_mul_by_zero passed\n");
}

void test_mul_by_one() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    stringToBigInteger("54321", bi1);
    stringToBigInteger("1", bi2);
    
    BigInteger* result = mul(bi1, bi2);
    assert(result != NULL);
    char* str = toString(result);
    assert(str != NULL);
    assert(strcmp(str, "54321") == 0);
    free(str);
    
    Done(&bi1);
    Done(&bi2);
    Done(&result);
    printf("[X] test_mul_by_one passed\n");
}

void test_mul_large_numbers() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    stringToBigInteger("123456789", bi1);
    stringToBigInteger("987654321", bi2);
    
    BigInteger* result = mul(bi1, bi2);
    assert(result != NULL);
    char* str = toString(result);
    assert(str != NULL);
    assert(strcmp(str, "121932631112635269") == 0);
    free(str);
    
    Done(&bi1);
    Done(&bi2);
    Done(&result);
    printf("[X] test_mul_large_numbers passed\n");
}

void test_NULLS() {
    BigInteger* bi1 = Create();
    BigInteger* bi2 = Create();
    BigInteger* resultADT = bi1;


    assert(count(NULL) == -1);

    assert(isEmpty(NULL) == 1);

    assert(isFull(NULL) == 0);

    assert(toString(NULL) == NULL);

    assert(clone(NULL) == NULL);

    assert(makeEmpty(NULL) == -1);

    assert(Done(NULL) == -1);

    assert(stringToBigInteger(NULL, bi1) == -1);

    assert(stringToBigInteger("test", NULL) == -1);

    assert(add(NULL, bi1) == NULL);

    assert(add(bi1, NULL) == NULL);

    assert(mul(NULL, bi1) == NULL);

    assert(mul(bi1, NULL) == NULL);

    stringToBigInteger("25", bi2);
    resultADT = add(bi2, bi1);
    assert( strcmp(toString(resultADT), "25") == 0);

    Done(&bi1);
    Done(&bi2);
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

    // Mul
    test_mul_positive_numbers();
    test_mul_negative_numbers();
    test_mul_mixed_signs();
    test_mul_by_zero();
    test_mul_by_one();
    test_mul_large_numbers();

    // NULLs
    test_NULLS();
    
    printf("\n[X] All tests passed!\n");

    // printf(" %llu, %llu, %llu, %llu", SHRT_MAX, INT_MAX, LONG_MAX, LONG_LONG_MAX);
    return 0;
}