#include <stdio.h>
#include <stdlib.h>
#include "cash-register.h"

// Inicializar listado de cajas registradoras
RegisterList* initRegisterList(int count) {
  RegisterList* list = (RegisterList*)malloc(sizeof(RegisterList));
  list->top = NULL;
  list->bottom = NULL;
  list->count = 0;
  list->busy = 0;

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

// Verificar si alguna caja registradora esta disponible
RegisterNode* availableRegisterNode(RegisterList* list) {
  if(list->top) {
    RegisterNode* node = list->top;
    while(node) {
      if(!node->buyer) {
        return node;
      }
      node =  node->next;
    }
  }
  return NULL;
}

// Liberar cliente del sistema
BuyersNode* finishPaying(RegisterList* list, Register id) {
  if(list->top) {
    RegisterNode* tmp = list->top;
    while(tmp) {
      if(tmp->id == id) {
        if(tmp->buyer) {
          BuyersNode* node = tmp->buyer;
          tmp->buyer = NULL;
          tmp->time++;
          tmp->status = "Libre";

          return node;
        }
      }
      tmp = tmp->next;
    }

  } else {
    printf("No hay cajas en MiniMarket\n");
  }
  return NULL;
}

// Mover a cliente a caja registradora segun id
// void insertBuyerInRegisterNode(RegisterList* list, Register id, BuyersNode* node) {
//   if(list->top) {
//     RegisterNode* registerNode = list->top;
//     while(registerNode->id != id) {
//       registerNode = registerNode->next;
//     }
//     registerNode->buyer = node;
//   }
// }

// Imprimir informacion de listado de cajas registradoras en archivo .dot
void printRegisterListInDot(FILE* file, RegisterList* list) {
  fprintf(file, "subgraph cluster_5 {\n");
  fprintf(file, "label = \"Cajas\";\n");
  fprintf(file, "node [\n");
  fprintf(file, "shape = \"ellipse\";\n");
  fprintf(file, "]\n\n");

  if(list->top) {
    RegisterNode* node = list->top;
    do {
      fprintf(file, "caja%d[label=\"Caja %d\\n%d Turnos\\n%s", node->id, node->id, node->time, node->status);
      if(node->buyer) {
        fprintf(file, "\\nCliente %d\\nCarrito %d", node->buyer->client, node->buyer->cart);
      }
      fprintf(file, "\"];\n");
      node = node->next;
    } while(node);
    node = list->top;
    while(node->next) {
      fprintf(file, "caja%d -> caja%d;\n", node->id, node->next->id);
      node = node->next;
      fprintf(file, "caja%d -> caja%d;\n", node->id, node->previous->id);
    }
  } else {
    fprintf(file, "caja%[label=\"Sin Cajas\"");
  }

  fprintf(file, "}\n\n");
}

// Imprimir listado de cajas registradoras
void printRegisterList(RegisterList* list) {
  if(list->top) {
    RegisterNode* node = list->top;
    printf("Listado de cajas\n");
    do {
      printf("Caja -> %d, time -> %d, estado -> %s", node->id, node->time, node->status);
      if(node->buyer) {
        printf(", cliente -> %d, carrito %d", node->buyer->client, node->buyer->cart);
      }
      printf("\n");
      node = node->next;
    } while(node);
  } else {
    printf("Lista de cajas vacia\n");
  }
  printf("\n");
}