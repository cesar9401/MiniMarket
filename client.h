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
  int waitingClients;
  int size;
} WaitingQueue;

// Definicion de funciones
WaitingNode* createWaitingNodeQueue(Client client);

void enqueue(WaitingQueue* queue, Client client);

Client dequeue(WaitingQueue* queue);

void printWaitingQueue(WaitingQueue* queue);

#endif