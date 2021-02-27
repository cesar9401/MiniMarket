#include <stdio.h>
#include <stdlib.h>
#include "cash-register.h"

// Inicializar listado de cajas registradoras
RegisterList* initRegisterList(int count) {
  RegisterList* list = (RegisterList*)malloc(sizeof(RegisterList));
  list->top = NULL;
  list->bottom = NULL;
  list->count = 0;

  for(int i = 0; i < count; i++) {
    insertAfterRegisterList(list, i);
  }

  return list;
}

// Crear nodo de caja registradora
RegisterNode* createRegisterNode(Register id) {
  RegisterNode* node = (RegisterNode*)malloc(sizeof(RegisterNode));
  node->id = id;
  node->time = 0;
  node->status = "Libre";
  node->buyer = NULL;

  node->next = NULL;
  node->previous = NULL;

  return node;
}

// Insertar nodo de caja registradora en lista
void insertAfterRegisterList(RegisterList* list, Register id) {
  RegisterNode* node = createRegisterNode(id);
  if(!list->top) {
    list->top = node;
  } else {
    list->bottom->next = node;
    node->previous = list->bottom;
  }
  list->bottom = node;
  list->count++;
}

// Imprimir listado de cajas registradoras
void printRegisterList(RegisterList* list) {
  if(list->top) {
    RegisterNode* node = list->top;
    printf("Listado de cajas\n");
    do {
      printf("Caja -> %d, time -> %d, estado ->%s\n", node->id, node->time, node->status);
      node = node->next;
    } while(node);
  } else {
    printf("Lista de cajas vacia\n");
  }
  printf("\n");
}