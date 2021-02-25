
//
// Elementos a utilizar en miniMarket
//

#ifndef elements_h
#define elements_h

// ------------------------------------------------------ Carretas
// Numero para carretas
typedef int Cart;

// Nodo para las pilas de carritos
typedef struct NodeCart {
  Cart id;
  struct NodeCart* next;
} NodeCart;

// Pila de carritos
typedef struct CartStack {
  NodeCart* root;
  int size;
  int actualNode;
} CartStack;

// ------------------------------------------------------ Clientes
// Numero para clientes
typedef int Client;

// Nodo para cola de espera de carritos
typedef struct NodeWaiting {
  Client client;
  struct NodeWaiting* next;
} NodeWaiting;

// Cola de espera de carritos
typedef struct WaitingQueue {
  NodeWaiting* top;
  NodeWaiting* bottom;
  int waitingClients;
  int size;
} WaitingQueue;

// Definicion de funciones

// definicion de funciones para pilas de carritos
NodeCart* createNodeCart(Cart n);

void push(CartStack* stack, Cart n);

Cart pop(CartStack* stack);

void printCartStack(CartStack* stack);

// definicion de funciones para colas de en espera clientes
NodeWaiting* createNodeWaitingQueue(Client client);

void enqueue(WaitingQueue* queue, Client client);

Client dequeue(WaitingQueue* queue);

void printWaitingQueue(WaitingQueue* queue);

#endif