#include <stdlib.h>
#include <stdio.h>
#include "cart.h"

// inicializar pila de carritos
CartStack* initCartStack(int size, int n, int count) {
  CartStack* stack = (CartStack*)malloc(sizeof(CartStack));
  stack->root = NULL;
  stack->count = 0;
  stack->size = size;

  for(int i = count; i < n + count; i++) {
    push(stack, i);
  }

  return stack;
}

// Crear nuevo carrito
CartNode* createCartNode(Cart n) {
  CartNode* tmp = (CartNode*)malloc(sizeof(CartNode));
  tmp->id = n;
  tmp->next = NULL;

  return tmp;
}

// Insertar carrito a la pila
void push(CartStack* stack, Cart n) {
  CartNode* node = createCartNode(n);
  node->next = stack->root;
  stack->root = node;
  stack->count++;
}

// Eliminar carrito de la pila
Cart pop(CartStack* stack) {
  if(stack->root != NULL) {
    CartNode* node = stack->root;
    stack->root = node->next;
    stack->count--;

    Cart id = node->id;

    free(node);

    return id;
  }

  return -1;
}

// Imprimir carritos en la pila
void printCartStack(CartStack* stack) {
  if(stack->root != NULL) {
    CartNode* node = stack->root;
    printf("Valores en pila:\n");
    do {
      printf("Carreta no: %d\n", node->id);
      node = node->next;
    } while(node != NULL);

  } else {
    printf("Pila de carretas vacia\n");
  }
  printf("\n");
}