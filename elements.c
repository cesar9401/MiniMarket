#include <stdlib.h>
#include <stdio.h>
#include "elements.h"

NodeCart* newNodeCart(int n) {
  NodeCart* tmp = (NodeCart*)malloc(sizeof(NodeCart));
  tmp->id = n;
  tmp->next = NULL;

  return tmp;
}

void push(CartStack* stack, int n) {
  NodeCart* node = newNodeCart(n);
  node->next = stack->root;
  stack->root = node;
  stack->actualNode++;
}

Cart pop(CartStack* stack) {
  if(stack->root != NULL) {
    NodeCart* node = stack->root;
    stack->root = node->next;
    stack->actualNode--;

    Cart id = node->id;

    free(node);

    return id;
  }

  return -1;
}

void printCartStack(CartStack* stack) {
  if(stack->root != NULL) {
    NodeCart* node = stack->root;
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
