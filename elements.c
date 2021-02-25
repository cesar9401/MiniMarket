#include <stdlib.h>
#include <stdio.h>
#include "elements.h"

// ------------------------------------------------------ Carretas
NodeCart* createNodeCart(Cart n) {
  NodeCart* tmp = (NodeCart*)malloc(sizeof(NodeCart));
  tmp->id = n;
  tmp->next = NULL;

  return tmp;
}

void push(CartStack* stack, Cart n) {
  NodeCart* node = createNodeCart(n);
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

// ------------------------------------------------------ Clientes
// Crear nuevo nodo de tipo NodeWaiting
NodeWaiting* createNodeWaitingQueue(Client client) {
  NodeWaiting* tmp = (NodeWaiting*)malloc(sizeof(NodeWaiting));
  tmp->client = client;
  tmp->next = NULL;
  return tmp;
}

// Encolar nuevo nodo de NodeWaiting
void enqueue(WaitingQueue* queue, Client client) {
  NodeWaiting* tmp = createNodeWaitingQueue(client);
  if(!queue->top) {
    queue->top = tmp;
    queue->bottom = tmp;
  } else {
    queue->bottom->next = tmp;
    queue->bottom = tmp;
  }
  queue->waitingClients++;
}

// Desencolar nodo de NodeWaiting
Client dequeue(WaitingQueue* queue) {
  if(queue->top) {
    NodeWaiting* first = queue->top;
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
    NodeWaiting* tmp = queue->top;
    do {
      printf("Cliente: %d\n", tmp->client);
      tmp = tmp->next;
    }while(tmp);
  } else {
    printf("La cola esta vacia\n");
  }
  printf("\n");
}
