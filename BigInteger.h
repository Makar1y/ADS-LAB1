#ifndef BigInteger_h
#define BigInteger_h

#define BASE 10
#define BASE_POW 9

typedef struct BID {
   long digits;
   struct BID* next;
} BigIntegerData;


typedef struct {
   char sign;
   BigIntegerData* LowerDigits;
} BigInteger;

BigInteger* Create();

int count(BigInteger* ADT);

int isEmpty(BigInteger* ADT);

int isFull(BigInteger* ADT);

char* toString(BigInteger* ADT);

BigInteger* clone(BigInteger* src_ADT);

int makeEmpty(BigInteger* ADT);

int Done(BigInteger** ptr_to_ADT);

int stringToBigInteger(char* number_string, BigInteger* ADT);

#endif