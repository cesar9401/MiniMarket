//
// Elementos a utilizar en miniMarket
//

#ifndef elements_h
#define elements_h

// ------------------------------------------------------ Carretas
// Numero para carretas
typedef int Cart;

// Nodo para las pilas de carritos
typedef struct CartNode {
  Cart id;
  struct CartNode* next;
} CartNode;

// Pila de carritos
typedef struct CartStack {
  CartNode* root;
  int size;
  int actualNode;
} CartStack;

// ------------------------------------------------------ Clientes
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

// ------------------------------------------------------ Compras
// Nodo para lista circular enlazada de compras
typedef struct BuyersNode {
  Client client;
  Cart cart;
  struct BuyersNode* next;
} BuyersNode;

// Lista circular de compras
typedef struct BuyersList {
  BuyersNode* root;
  int buyersCount;
} BuyersList;

// ------------------------------------------------------ Definicion de Funciones

// definicion de funciones para pilas de carritos
CartNode* createCartNode(Cart n);

void push(CartStack* stack, Cart n);

Cart pop(CartStack* stack);

void printCartStack(CartStack* stack);

// definicion de funciones para colas de en espera clientes
WaitingNode* createWaitingNodeQueue(Client client);

void enqueue(WaitingQueue* queue, Client client);

Client dequeue(WaitingQueue* queue);

void printWaitingQueue(WaitingQueue* queue);

// definicion de funciones para lista circular simplemente enlazada de compradores

BuyersNode* createBuyersNode(Client client, Cart cart);

void insertAfter(BuyersList* list, Client client, Cart cart);

#endif