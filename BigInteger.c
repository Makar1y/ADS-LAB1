#include <stdlib.h>

/*
Turėtų būti realizuotos matematinės operacijos: add, sub, mul, div, mod.

Turėtų būti realizuotos užklausos:
isFull() dinaminio masyvo atveju tikrina, ar masyvas pilnai užpildytas; tiesinio sąrašo atveju gražina False ???

toString() grąžina ADT atitinkantį tekstą, arba jo pradžią, jei subelementų per daug.
Užklausos nepakeičia ADT būsenos.

*/

typedef struct BID {
   unsigned long integer;
   struct BID* next;
} BigIntegerData;

typedef struct {
   int pow;
   char sign;
   BigIntegerData* integer;
} BigInteger;

BigInteger* Create() {
   BigInteger* ADT = callloc(1, sizeof(BigInteger));
   return ADT;
}

int count(BigInteger* ADT) {
   if (NULL != ADT) {
      BigIntegerData* element = ADT->integer;
      int counter = 0;

      while (NULL != element) {
         ++counter;
         element = element->next;
      }
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
   // TODO Ask professor
   return 0;
}

char* toString(BigInteger* ADT) {
	
   // TODO
}

BigInteger* clone(BigInteger* src_ADT) {
   if (NULL != src_ADT) {
      BigInteger* dest_ADT = malloc(sizeof(BigInteger));

      dest_ADT->pow = src_ADT->pow;
      dest_ADT->sign = src_ADT->sign;

      if (NULL != src_ADT->integer) {
         BigIntegerData* src_current = src_ADT->integer;
         BigIntegerData* dest_current = src_ADT->integer;

         dest_ADT->integer = calloc(1, sizeof(BigIntegerData));

         do {
            dest_current->integer = src_current->integer;
            src_current = src_current->next;
            dest_current = dest_current->next;
         } while (NULL != src_current);
      } else {
         dest_ADT->integer = NULL;
      }
      return dest_ADT;
   }
   return NULL;
}

int makeEmpty(BigInteger* ADT) {
   if (NULL != ADT) {
      BigIntegerData* current = ADT->integer;
      BigIntegerData* temp;

      ADT->pow = 0;
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
