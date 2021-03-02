#include <stdio.h>
#include <stdlib.h>
#include "buyer.h"

// ---------------------------------------- Lista circular simplemente enlazada de compras
// inicializar lista circular de compras
BuyersList* initBuyersList(int count, int cartCount) {
  BuyersList* list = (BuyersList*)malloc(sizeof(BuyersList));
  list->root = NULL;
  list->count = 0;

  for(int i = cartCount; i < count + cartCount; i++) {
    insertAfter(list, i, i);
  }

  return list;
}

// Crear nuevo nodo
BuyersNode* createBuyersNode(Client client, Cart cart) {
  BuyersNode* tmp = (BuyersNode*)malloc(sizeof(BuyersNode));
  tmp->client = client;
  tmp->cart = cart;
  tmp->next = NULL;

  return tmp;
}

// Insertar nodo al final de la lista
void insertAfter(BuyersList* list, Client client, Cart cart) {
  BuyersNode* tmp = createBuyersNode(client, cart);

  if(!list->root) {
    list->root = tmp;
    tmp->next = tmp;
  } else {
    BuyersNode* node = list->root;
    while(node->next != list->root) {
      node = node->next;
    }
    node->next = tmp;
    tmp->next = list->root;
  }
  list->count++;
}

// Eliminar cliente de la lista segun id
BuyersNode* removeBuyer(BuyersList* list, Client client) {
  if(list->root) {
    BuyersNode* node = list->root;
    if(node->client == client) {
      if(node->next != list->root) {
        BuyersNode* tmp = node;
        while(tmp->next != list->root) {
          tmp = tmp->next;
        }
        list->root = node->next;
        tmp->next = list->root;
        node->next = NULL;
      } else {
        list->root = NULL;
        node->next = NULL;
      }

      list->count--;
      return node;

    } else {
      while(node->next != list->root) {
        if(node->next->client == client) {
          BuyersNode* tmp = node->next;
          node->next = tmp->next;
          tmp->next = NULL;
          list->count--;
          return tmp;
        }
        node = node->next;
      }
      //printf("Cliente %d, no encontrado.\n", client);
    }
  } else {
    //printf("Listado vacio\n");
  }

  return NULL;
}

// Imprimir informacion de compradores en archivo .dot
void printBuyersListInDot(FILE* file, BuyersList* list) {
  fprintf(file, "subgraph cluster_3 {\n");
  fprintf(file, "label = \"Compradores\";\n\n");

  if(list->root) {
    BuyersNode* node = list->root;
    do {
      fprintf(file, "comprador%d[label=\"Cliente %d\\nCarrito %d\"];\n", node->client, node->client, node->cart);
      node = node->next;
    } while(node != list->root);
    fprintf(file, "\n");
    node = list->root;
    do {
      if(node->next != list->root) {
        fprintf(file, "comprador%d -> comprador%d;\n", node->client, node->next->client);
      } else {
        fprintf(file, "comprador%d -> comprador%d;\n", node->client, node->next->client);
      }

      node = node->next;
    } while(node != list->root);
  } else {
    fprintf(file, "comprador[label=\"Lista Vacia\"];\n");
  }

  fprintf(file, "}\n\n");
}

// Imprimir listado de compradores
void printBuyersList(BuyersList* list) {
  if(!list->root) {
    printf("Listado vacio\n");
  } else{
    BuyersNode* node = list->root;
    printf("Listado de clientes:\n");
    do {
      printf("Cliente ->  %d, Carrito -> %d\n", node->client, node->cart);
      node = node->next;
    }while(node != list->root);
    //printf("Cliente ->  %d, Carrito -> %d\n", node->client, node->cart);
  }
  printf("\n");
}

// ---------------------------------------- Cola de pagos
// Inicializar cola de pagos
PaymentQueue* initPaymentQueue(int count) {
  PaymentQueue* queue = (PaymentQueue*)malloc(sizeof(PaymentQueue));
  queue->top = NULL;
  queue->bottom = NULL;
  queue->count = 0;

  for(int i = 0; i < count; i++) {
    BuyersNode* node = createBuyersNode(i, i);
    enqueuePaymentQueue(queue, node);
  }

  return queue;
}

// Encolar nuevo comprador a la cola de pagos
void enqueuePaymentQueue(PaymentQueue* queue, BuyersNode* node) {
  if(!queue->top) {
    queue->top = node;
    queue->bottom = node;
  } else {
    queue->bottom->next = node;
    queue->bottom = node;
  }
  queue->count++;
}

// Desencolar nodo de PaymentQueue
BuyersNode* dequeuePaymentQueue(PaymentQueue* queue) {
  if(queue->top) {
    BuyersNode* first = queue->top;
    queue->top = first->next;
    queue->count--;

    if(!queue->top) {
      queue->bottom = NULL;
    }
    return first;
  }

  return NULL;
}

// Imprimir cola de pagos
void printPaymentQueue(PaymentQueue* queue) {
  if(queue->top) {
    BuyersNode* node = queue->top;
    printf("Compradores en cola de pago\n");
    do {
      printf("Comprador -> %d, Carrito -> %d\n", node->client, node->cart);
      node = node->next;
    }while(node);
  }else {
    printf("La cola de pagos esta vacia\n");
  }
  printf("\n");
}
