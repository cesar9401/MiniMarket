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

// Agregar informacion de los carritos en archivo .dot
void printCartStackInDot(FILE* file, CartStack* stack, int n) {
  fprintf(file, "subgraph cluster_%d {\n", n);
  fprintf(file, "label = \"Carritos %d\";\n\n", n);

  if(stack->root) {
    CartNode* node = stack->root;
    // shape = record
    fprintf(file, "\"carrito%d\" [\n", n);
    fprintf(file, "label = \"");
    // shape = record

    do {
      // shape = record
      fprintf(file, "%d", node->id);
      if(node->next) {
        fprintf(file, "|", node->id);
      }
      // shape = record

      //fprintf(file, "carrito%d[label=\"%d\"];\n", node->id, node->id);
      node = node->next;
    } while(node);
    // shape = record
    fprintf(file, "\"\n");
    fprintf(file, "shape = \"record\"\n");
    fprintf(file, "];\n");
    // shape = record

    fprintf(file, "\n");
    node = stack->root;
    // while(node->next) {
    //   fprintf(file, "carrito%d -> carrito%d;\n", node->id, node->next->id);
    //   node = node->next;
    // }
  } else {
    // shape = record
    fprintf(file, "\"carrito%d\" [\n", n);
    fprintf(file, "label = \"Pila Vacia\"\n");
    fprintf(file, "shape = \"record\"\n");
    fprintf(file, "];\n");
    // shape = record

    //fprintf(file, "carrito%d[label =\"Pila vacia\"];\n", n);
  }

  fprintf(file, "}\n\n");
}

// Imprimir carritos en la pila
void printCartStack(CartStack* stack) {
  if(stack->root != NULL) {
    CartNode* node = stack->root;
    printf("Carritos en pila:\n");
    do {
      printf("Carreta no: %d\n", node->id);
      node = node->next;
    } while(node != NULL);

  } else {
    printf("Pila de carretas vacia\n");
  }
  printf("\n");
}