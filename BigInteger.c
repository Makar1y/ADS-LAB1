#include <stdlib.h>
#include <string.h>

#define BASE_10 9

/*
Turėtų būti realizuotos matematinės operacijos: add, sub, mul, div, mod.

Turėtų būti realizuotos užklausos:
isFull() dinaminio masyvo atveju tikrina, ar masyvas pilnai užpildytas; tiesinio sąrašo atveju gražina False ???

*/

typedef struct BID {
   long digits;
   struct BID* next;
} BigIntegerData;

typedef struct {
   char sign;
   BigIntegerData* LowerDigits;
} BigInteger;

BigInteger* Create() {
   BigInteger* ADT = callloc(1, sizeof(BigInteger));
   return ADT;
}

int count(BigInteger* ADT) {
   if (NULL != ADT) {
      BigIntegerData* element = ADT->LowerDigits;
      int counter = 0;

      while (NULL != element) {
         ++counter;
         element = element->next;
      }
      return counter;
   }
   return -1;
}

int isEmpty(BigInteger* ADT) {
   if (NULL != ADT) {
      int result = count(ADT);

      switch (result) {
         case 0:
            return 1;
         case -1:
            return -1;
         default:
            return 0;
      }
   }
   return -1;
}

int isFull(BigInteger* ADT) {
   if (NULL != ADT) {
      return 0; // TODO Ask professor
   }
   return -1;
}

char* toString(BigInteger* ADT) {
   if (NULL != ADT) {
      int count_elements = count(ADT);
      if (count_elements <= 0) {
         return NULL;
      }

      int max_length = 1 + (count_elements * BASE_10) + 1; // +1 for \0, +1 for sign
      char* result = malloc(max_length);
      if (NULL == result) {
         return NULL;
      }

      int pos = 0;

      if (1 == ADT->sign) {
         result[pos] = '-';
         ++pos;
      }

      BigIntegerData* elements[count_elements];
      BigIntegerData* current = ADT->LowerDigits;
      int id = 0;
      while (NULL != current) {
         elements[id++] = current;
         current = current->next;
      }

      for (int i = count_elements - 1; i >= 0; i--) {
         pos += sprintf(result + pos, "%0*lu", BASE_10, elements[i]->digits);
      }

      result[pos] = '\0';
      return result;
   }
   return NULL;
}

BigInteger* clone(BigInteger* src_ADT) {
   if (NULL != src_ADT) {
      BigInteger* dest_ADT = malloc(sizeof(BigInteger));
      dest_ADT->sign = src_ADT->sign;

      if (NULL != src_ADT->LowerDigits) {

         BigIntegerData* src_current = src_ADT->LowerDigits;
         dest_ADT->LowerDigits = calloc(1, sizeof(BigIntegerData));
         BigIntegerData* dest_current = dest_ADT->LowerDigits;

         do {
            dest_current->digits = src_current->digits;
            src_current = src_current->next;
            if (NULL != src_current) {
               dest_current->next = calloc(1, sizeof(BigIntegerData));
               dest_current = dest_current->next;
            }
         } while (NULL != src_current);
      } else {
         dest_ADT->LowerDigits = NULL;
      }
      return dest_ADT;
   }
   return NULL;
}

int makeEmpty(BigInteger* ADT) {
   if (NULL != ADT) {
      BigIntegerData* current = ADT->LowerDigits;
      BigIntegerData* temp;

      ADT->sign = 0;

      while (NULL != current) {
         temp = current->next;
         free(current);
         current = temp;
      }

      return 1;
   }
   return -1;
}

int Done(BigInteger** ptr_to_ADT) {
   if (NULL != ptr_to_ADT && NULL != *ptr_to_ADT) {
      makeEmpty(*ptr_to_ADT);
      free(*ptr_to_ADT);
      *ptr_to_ADT = NULL;
      return 1;
   }
   return -1;
}

int stringToBigInteger(char* number, BigInteger* ADT) {
   if (NULL != number && NULL != ADT) {
      
   }
   return -1;
}