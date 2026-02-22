#ifndef BigInteger_h
#define BigInteger_h

#define BASE 10
#define BASE_POW 9
#define true 1
#define false !true

/*
   !!!
   Using functions that returns and accepts BigInteger* types with same 
   BigInteger ptr for argument and return value will lead to a memory leak.
   For example:
      a = BigIntegerAdd(a, b); lead to memory leak(loosing original a pointer).
*/

/// @brief 
typedef struct BID {
   long digits;
   struct BID* next;
   struct BID* previous;
} BigIntegerData;

/// @brief 
typedef struct {
   char sign;
   BigIntegerData* LowerDigits;
   BigIntegerData* HigherDigits;
} BigInteger;

/// @brief 
/// @return 
BigInteger* Create();

/// @brief 
/// @param ADT 
/// @return 
int count(BigInteger* ADT);

/// @brief 
/// @param ADT 
/// @return 
int isEmpty(BigInteger* ADT);

/// @brief 
/// @param ADT 
/// @return 
int isFull(BigInteger* ADT);

/// @brief 
/// @param ADT 
/// @return 
char* toString(BigInteger* ADT);

/// @brief 
/// @param src_ADT 
/// @return 
BigInteger* clone(BigInteger* src_ADT);

/// @brief 
/// @param src_ADT 
/// @param dst_ADT 
/// @return 
int copy(BigInteger* src_ADT, BigInteger* dst_ADT);

/// @brief 
/// @param ADT 
/// @return 
int makeEmpty(BigInteger* ADT);

/// @brief 
/// @param ptr_to_ADT 
/// @return
int Done(BigInteger** ptr_to_ADT);

/// @brief 
/// @param number_string 
/// @param ADT 
/// @return 
int stringToBigInteger(char* number_string, BigInteger* ADT);

/// @brief 
/// @param a 
/// @param b 
/// @return 
int compareADTs(BigInteger* a, BigInteger* b);

/// @brief 
/// @param a 
/// @param b 
/// @return 
BigInteger* BigIntegerAdd(BigInteger* a, BigInteger* b);

/// @brief 
/// @param a 
/// @param b 
/// @return 
BigInteger* BigIntegerSub(BigInteger* a, BigInteger* b);

/// @brief 
/// @param a 
/// @param b 
/// @return 
BigInteger* BigIntegerMul(BigInteger* a, BigInteger* b);

/// @brief 
/// @param a 
/// @param b 
/// @return 
BigInteger* BigIntegerDiv(BigInteger* a, BigInteger* b);

/// @brief 
/// @param a 
/// @param b 
/// @return 
BigInteger* BigIntegerMod(BigInteger* a, BigInteger* b);

#endif