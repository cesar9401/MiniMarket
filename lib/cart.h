//
// Carritos de MiniMarket
//

#ifndef __CARRITO_H
#define __CARRITO_H

// Numero para carretas
typedef int Cart;

// Nodo para las pilas de carritos
typedef struct CartNode {
  Cart id;
  struct CartNode* next;
} CartNode;

// Pila de carritos
typedef struct CartStack {
  CartNode* root;
  int size;
  int count;
} CartStack;

// Definicion de funciones
CartStack* initCartStack(int size, int n, int count);

CartNode* createCartNode(Cart n);

void push(CartStack* stack, Cart n);

Cart pop(CartStack* stack);

void printCartStackInDot(FILE* file, CartStack* stack, int n);

void printCartStack(CartStack* stack);

#endif