#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "BigInteger.h"

/*
Turėtų būti realizuotos matematinės operacijos: add, sub, mul, div, mod.

Turėtų būti realizuotos užklausos:
isFull() dinaminio masyvo atveju tikrina, ar masyvas pilnai užpildytas; tiesinio sąrašo atveju gražina False ???

*/


BigInteger* Create() {
   BigInteger* ADT = calloc(1, sizeof(BigInteger));
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

      int max_length = 1 + (count_elements * BASE_POW) + 1; // +1 for \0, +1 for sign
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
         if (0 == i) {
            pos += sprintf(result + pos, "%lu", elements[i]->digits);
         } else {
            pos += sprintf(result + pos, "%0*lu", BASE_POW, elements[i]->digits);
         }
      }

      result[pos] = '\0';
      return result;
   }
   return NULL;
}

BigInteger* clone(BigInteger* src_ADT) {
   if (NULL != src_ADT) {
      BigInteger* dest_ADT = malloc(sizeof(BigInteger));
      if (NULL == dest_ADT) {
         return NULL;
      }
      dest_ADT->sign = src_ADT->sign;

      if (NULL != src_ADT->LowerDigits) {

         BigIntegerData* src_current = src_ADT->LowerDigits;
         dest_ADT->LowerDigits = calloc(1, sizeof(BigIntegerData));
         if (NULL == dest_ADT->LowerDigits) {
            Done(&dest_ADT);
            return NULL;
         }
         BigIntegerData* dest_current = dest_ADT->LowerDigits;

         do {
            dest_current->digits = src_current->digits;
            src_current = src_current->next;
            if (NULL != src_current) {
               dest_current->next = calloc(1, sizeof(BigIntegerData));
               if (NULL == dest_current->next) {
                  Done(&dest_ADT);
                  return NULL;
               }
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
      ADT->LowerDigits = NULL;

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

int stringToBigInteger(char* number_string, BigInteger* ADT) {
   if (NULL != number_string && NULL != ADT) {
      makeEmpty(ADT);

      size_t num_length = strlen(number_string);
      ADT->LowerDigits = calloc(1, sizeof(BigIntegerData));
      if (NULL == ADT->LowerDigits) {
         return -2;
      }

      if (number_string[0] == '-') {
         ADT->sign = 1;
         --num_length;
         ++number_string;
      }


      BigIntegerData *current = ADT->LowerDigits;

      for (int i = num_length - 1, j = 0; i >= 0; --i, ++j) {
         if (j % BASE_POW == 0 && j != 0) {
            current->next = calloc(1, sizeof(BigIntegerData));
            if (NULL == current->next) {
               makeEmpty(ADT);
               return -2;
            }
            current = current->next; 
         }

         int is_integer = 0 <= number_string[i] - 48 <= 9 ? 1 : 0;

         if ( !is_integer ) {
            return -3;
         }
         current->digits += (number_string[i] - 48) * pow(BASE, j % BASE_POW);
      }
      return 1;
      
   }
   return -1;
}

BigInteger* add(BigInteger* a, BigInteger* b) {
   if (NULL != a && NULL != b) {
      BigInteger* result = calloc(1, sizeof(BigInteger));
      if (NULL == result) {
         return NULL;
      }

      BigIntegerData* aData = a->LowerDigits;
      BigIntegerData* bData = b->LowerDigits;
      result->LowerDigits = calloc(1, sizeof(BigInteger));
      if (NULL ==  result->LowerDigits) {
         Done(&result);
         return NULL;
      }
      BigIntegerData* resultData = result->LowerDigits;
      BigIntegerData* resultDataPrevious = NULL;

      int aSign = a->sign == 1 ? -1 : 1;
      int bSign = b->sign == 1 ? -1 : 1;
      int toNext = 0;
      
      while (aData || bData || toNext) {
         // calculations
         if (aData && bData) {
            resultData->digits = (aData->digits * aSign + bData->digits *bSign) + toNext;
         } else if (aData && !bData) {
            resultData->digits = aData->digits * aSign + toNext;
            if (0 == resultData->digits) {
               free(resultData);
               resultDataPrevious->next = NULL;
               break;
            }
         } else if (!aData && bData) {
            resultData->digits = bData->digits * bSign + toNext;
            if (0 == resultData->digits) {
               free(resultData);
               resultDataPrevious->next = NULL;
               break;
            }
         } else {
            resultData->digits = toNext;
         }

         // next digits
         if (aData) aData = aData->next;
         if (bData) bData = bData->next;

         // cary
         if (resultData->digits < 0) {
            if (aData || bData) {
               toNext = -1;
               resultData->digits += pow(BASE, BASE_POW);
            } else {
               result->sign = 1;
               resultData->digits *= -1;
            }
         } else if (resultData->digits >= pow(BASE, BASE_POW) * BASE) {
            toNext = 1;
            resultData->digits -= pow(BASE, BASE_POW);
         } else {
            toNext = 0;
         }

         // next digits
         if (aData || bData || toNext) {
            resultData->next = calloc(1, sizeof(BigIntegerData));
            resultDataPrevious = resultData;
            resultData = resultData->next;
            if (NULL == resultData) {
               Done(&result);
               return NULL;
            }
         }

      }
      return result;
   }
   return NULL;
}


// sub, mul, div, mod