//
// Cajas registradoras de MiniMarket
//

#ifndef __CASH_REGISTER_H
#define __CASH_REGISTER_H

#include "buyer.h"

// Numero de caja
typedef int Register;

// Nodo para lista doblemente enlazada de cajas registradoras
typedef struct RegisterNode {
  Register id;
  int time;
  char* status;
  BuyersNode* buyer;

  // Punteros para lista
  struct RegisterNode* next;
  struct RegisterNode* previous;
} RegisterNode;

typedef struct RegisterList {
  RegisterNode* top;
  RegisterNode* bottom;
  int count;
} RegisterList;

RegisterList* initRegisterList(int count);

RegisterNode* createRegisterNode(Register id);

void insertAfterRegisterList(RegisterList* list, Register id);

RegisterNode* availableRegisterNode(RegisterList* list);

BuyersNode* finishPaying(RegisterList* list, Register id);

void printRegisterList(RegisterList* list);

#endif