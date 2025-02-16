#include <stdio.h>
#include <stdlib.h>
#include "client.h"

// inicializar cola de espera de carritos
WaitingQueue* initWaitinQueue(int n, int count) {
  WaitingQueue* queue = (WaitingQueue*)malloc(sizeof(WaitingQueue));
  queue->top = NULL;
  queue->bottom = NULL;
  queue->count = 0;

  for(int i = count; i < count + n; i++) {
    enqueueWaitingQueue(queue, i);
  }

  return queue;
}

// Crear nuevo nodo de tipo WaitingNode
WaitingNode* createWaitingNodeQueue(Client client) {
  WaitingNode* tmp = (WaitingNode*)malloc(sizeof(WaitingNode));
  tmp->client = client;
  tmp->next = NULL;
  return tmp;
}

// Encolar nuevo nodo de WaitingNode
void enqueueWaitingQueue(WaitingQueue* queue, Client client) {
  WaitingNode* tmp = createWaitingNodeQueue(client);
  if(!queue->top) {
    queue->top = tmp;
    queue->bottom = tmp;
  } else {
    queue->bottom->next = tmp;
    queue->bottom = tmp;
  }
  queue->count++;
}

// Desencolar nodo de WaitingNode
Client dequeueWaitingQueue(WaitingQueue* queue) {
  if(queue->top) {
    WaitingNode* first = queue->top;
    queue->top = first->next;
    queue->count--;

    Client client = first->client;

    free(first);

    if(!queue->top) {
      queue->bottom = NULL;
    }

    return client;
  }

  return -1;
}

void printWaitingQueueInDot(FILE* file, WaitingQueue* queue) {
  fprintf(file, "subgraph cluster_0 {\n");
  fprintf(file, "label = \"Cola de espera\";\n\n");
  if(queue->top) {
    WaitingNode* node = queue->top;
    do {
      fprintf(file, "cliente%d[label =\"Cliente %d\"];\n", node->client, node->client);
      node = node->next;
    } while(node);
    fprintf(file, "\n");
    node = queue->top;
    while(node->next) {
      fprintf(file, "cliente%d -> cliente%d;\n", node->client, node->next->client);
      node = node->next;
    }
  } else {
      fprintf(file, "cliente[label =\"Cola vacia\"];\n");
  }

  fprintf(file, "}\n\n");
}

// Imprimir cola de espera
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
