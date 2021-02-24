
//
// Elementos a utilizar en miniMarket
//

#ifndef elements_h
#define elements_h

typedef int Cart;

typedef struct NodeCart {
  Cart id;
  struct NodeCart* next;
} NodeCart;

typedef struct CartStack {
  NodeCart* root;
  int size;
  int actualNode;
} CartStack;

// definicion de funciones
NodeCart* newNodeCart(int n);

void push(CartStack* stack, int n);

Cart pop(CartStack* stack);

void printCartStack(CartStack* stack);

#endif