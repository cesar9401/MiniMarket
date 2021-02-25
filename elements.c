#include <stdlib.h>
#include <stdio.h>
#include "elements.h"

// ------------------------------------------------------ Carretas
CartNode* createCartNode(Cart n) {
  CartNode* tmp = (CartNode*)malloc(sizeof(CartNode));
  tmp->id = n;
  tmp->next = NULL;

  return tmp;
}

void push(CartStack* stack, Cart n) {
  CartNode* node = createCartNode(n);
  node->next = stack->root;
  stack->root = node;
  stack->actualNode++;
}

Cart pop(CartStack* stack) {
  if(stack->root != NULL) {
    CartNode* node = stack->root;
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

// ------------------------------------------------------ Clientes
// Crear nuevo nodo de tipo WaitingNode
WaitingNode* createWaitingNodeQueue(Client client) {
  WaitingNode* tmp = (WaitingNode*)malloc(sizeof(WaitingNode));
  tmp->client = client;
  tmp->next = NULL;
  return tmp;
}

// Encolar nuevo nodo de WaitingNode
void enqueue(WaitingQueue* queue, Client client) {
  WaitingNode* tmp = createWaitingNodeQueue(client);
  if(!queue->top) {
    queue->top = tmp;
    queue->bottom = tmp;
  } else {
    queue->bottom->next = tmp;
    queue->bottom = tmp;
  }
  queue->waitingClients++;
}

// Desencolar nodo de WaitingNode
Client dequeue(WaitingQueue* queue) {
  if(queue->top) {
    WaitingNode* first = queue->top;
    queue->top = first->next;
    queue->waitingClients--;

    Client client = first->client;

    free(first);

    if(!queue->top) {
      queue->bottom = NULL;
    }

    return client;
  }

  return -1;
}

void printWaitingQueue(WaitingQueue* queue) {
  if(queue->top) {
    WaitingNode* tmp = queue->top;
    do {
      printf("Cliente: %d\n", tmp->client);
      tmp = tmp->next;
    }while(tmp);
  } else {
    printf("La cola esta vacia\n");
  }
  printf("\n");
}

// ------------------------------------------------------ Compras
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
}