//
// Compradores MiniMarket y Cola de pagos
//

#ifndef __BUYER_H
#define __BUYER_H

#include "cart.h"
#include "client.h"

// ---------------------------------------- Lista circular simplemente enlazada de compras
// Nodo para lista circular enlazada de compras
typedef struct BuyersNode {
  Client client;
  Cart cart;
  struct BuyersNode* next;
} BuyersNode;

// Lista circular de compras
typedef struct BuyersList {
  BuyersNode* root;
  int count;
} BuyersList;

// ---------------------------------------- Cola de pagos
// Cola de pagos
typedef struct PaymentQueue {
  BuyersNode* top;
  BuyersNode* bottom;
  int count;
} PaymentQueue;

// Definicion de funciones para lista circular simplemente enlazada de compras
BuyersList* initBuyersList(int count, int cartCount);

BuyersNode* createBuyersNode(Client client, Cart cart);

void insertAfter(BuyersList* list, Client client, Cart cart);

BuyersNode* removeBuyer(BuyersList* list, Client client);

void printBuyersListInDot(FILE* file, BuyersList* list);

void printBuyersList(BuyersList* list);

// Definicion de funciones para cola de pagos
PaymentQueue* initPaymentQueue(int count);

void enqueuePaymentQueue(PaymentQueue* queue, BuyersNode* node);

BuyersNode* dequeuePaymentQueue(PaymentQueue* queue);

void printPaymentQueueInDot(FILE* file, PaymentQueue* queue);

void printPaymentQueue(PaymentQueue* queue);

#endif