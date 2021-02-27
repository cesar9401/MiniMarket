#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "cart.h"
#include "client.h"
#include "buyer.h"
#include "cash-register.h"

// Numero de carritos y cajas
int cartsCount;
int registerCount;

// Estructuras para elementos de la tienda
WaitingQueue* waitingQueue;
CartStack* stack1;
CartStack* stack2;
BuyersList* buyersList;
PaymentQueue* paymentQueue;
RegisterList* registerList;

// Definir funciones
void setElements() {
  int a, b, c, d, count, n, p;

  printf("Defina el numero de cajas para pagos: ");
  scanf("%d", &registerCount);

  printf("Defina la cantidad de clientes en la cola de pagos: ");
  scanf("%d", &a);

  printf("Defina la cantidad de clientes comprando: ");
  scanf("%d", &b);

  printf("Defina la cantidad de carretas por pila: ");
  scanf("%d", &c);

  printf("Defina la cantidad de clientes en la cola de espera de carretas: ");
  scanf("%d", &d);

  cartsCount = 2 * c;

  //inicializar elementos
  registerList = initRegisterList(registerCount);
  paymentQueue = initPaymentQueue(a);
  buyersList = initBuyersList(b, a);

  count = a + b; // 15
  if(count % 2 == 0) {
    n = c - (a + b) / 2;
    p = n;
  } else {
    n = c - (a + b - 1) / 2;// 13
    p = c - (a + b + 1) / 2;// 12
  }

  stack1 = initCartStack(c, n, count);
  stack2 = initCartStack(c, p, count + n);
  waitingQueue = initWaitinQueue(d, count);
}

int main() {
  // Write your code here
  setElements();
  printf("Cajas registradoras: %d\n", registerList->count);
  printRegisterList(registerList);
  printf("Clientes en cola de pagos: %d\n", paymentQueue->count);
  printPaymentQueue(paymentQueue);
  printf("Clientes haciendo compras: %d\n", buyersList->count);
  printBuyersList(buyersList);
  printf("Carritos stack1: %d, Size: %d\n", stack1->count, stack1->size);
  printCartStack(stack1);
  printf("Carritos stack1: %d, Size: %d\n", stack2->count, stack2->size);
  printCartStack(stack2);
  printf("Clientes en cola de espera: %d\n", waitingQueue->count);
  printWaitingQueue(waitingQueue);


  return 0;
}