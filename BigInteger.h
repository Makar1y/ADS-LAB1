#ifndef BigInteger_h
#define BigInteger_h

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

int isEmpty(BigInteger* ADT) ;

int isFull(BigInteger* ADT);

char* toString(BigInteger* ADT);

BigInteger* clone(BigInteger* src_ADT);

int makeEmpty(BigInteger* ADT);

int Done(BigInteger** ptr_to_ADT);

#endif