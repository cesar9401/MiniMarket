//
// Clientes de MiniMarket
//

#ifndef __CLIENTE_H
#define __CLIENTE_H

// Numero para clientes
typedef int Client;

// Nodo para cola de espera de carritos
typedef struct WaitingNode {
  Client client;
  struct WaitingNode* next;
} WaitingNode;

// Cola de espera de carritos
typedef struct WaitingQueue {
  WaitingNode* top;
  WaitingNode* bottom;
  int count;
} WaitingQueue;

// Definicion de funciones
WaitingQueue* initWaitinQueue(int n, int count);

WaitingNode* createWaitingNodeQueue(Client client);

void enqueueWaitingQueue(WaitingQueue* queue, Client client);

Client dequeueWaitingQueue(WaitingQueue* queue);

void printWaitingQueueInDot(FILE* file, WaitingQueue* queue);

void printWaitingQueue(WaitingQueue* queue);

#endif