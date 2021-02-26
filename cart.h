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
  int actualNode;
} CartStack;

// Definicion de funciones
CartNode* createCartNode(Cart n);

void push(CartStack* stack, Cart n);

Cart pop(CartStack* stack);

void printCartStack(CartStack* stack);

#endif