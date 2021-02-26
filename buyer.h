//
// Compradores MiniMarket
//

#ifndef __BUYER_H
#define __BUYER_H

#include "cart.h"
#include "client.h"

// Nodo para lista circular enlazada de compras
typedef struct BuyersNode {
  Client client;
  Cart cart;
  struct BuyersNode* next;
} BuyersNode;

// Lista circular de compras
typedef struct BuyersList {
  BuyersNode* root;
  int buyersCount;
} BuyersList;

// Definicion de funciones
BuyersNode* createBuyersNode(Client client, Cart cart);

void insertAfter(BuyersList* list, Client client, Cart cart);

BuyersNode* removeBuyer(BuyersList* list, Client client);

void printBuyersList(BuyersList* list);

#endif