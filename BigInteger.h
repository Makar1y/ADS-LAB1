#ifndef BigInteger_h
#define BigInteger_h

#define BASE 10
#define BASE_POW 9
#define true 1
#define false !true

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
BigInteger* add(BigInteger* a, BigInteger* b);

/// @brief 
/// @param a 
/// @param b 
/// @return 
BigInteger* sub(BigInteger* a, BigInteger* b);

/// @brief 
/// @param a 
/// @param b 
/// @return 
BigInteger* mul(BigInteger* a, BigInteger* b);

// Not use a = add(a, b);
#endif