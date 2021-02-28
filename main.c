#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
void setElements();
void printStatus();
void takeCart();
void goToPaymentQueue();
void goToCashRegister();

int main() {
  srand(time(NULL));
  // Write your code here
  setElements();
  printStatus();
  goToPaymentQueue();
  goToPaymentQueue();
  goToPaymentQueue();
  goToPaymentQueue();
  goToPaymentQueue();
  goToPaymentQueue();
  goToPaymentQueue();

  goToCashRegister();
  printStatus();

  return 0;
}

void setElements() {
  int a, b, c, d, count, n, p;
  registerCount = 6;
  a = 10;
  b = 20;
  c = 25;
  d = 40;

  // printf("Defina el numero de cajas para pagos: ");
  // scanf("%d", &registerCount);

  // printf("Defina la cantidad de clientes en la cola de pagos: ");
  // scanf("%d", &a);

  // printf("Defina la cantidad de clientes comprando: ");
  // scanf("%d", &b);

  // /* Se deben tomar en cuenta los carritos con los clientes que estan comprando y los clientes en la cola de pagos */
  // printf("Defina la cantidad de carretas por pila: ");
  // scanf("%d", &c);

  // printf("Defina la cantidad de clientes en la cola de espera de carretas: ");
  // scanf("%d", &d);

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

void printStatus() {
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
}

// Tomar carrito e ingresar cliente a la lista de compras
void takeCart() {
  if(waitingQueue->top) {
    int n = rand() % 2;
    Cart cart = -1;
    if(n) {
      cart = pop(stack1);
      if(cart == -1) {
        cart = pop(stack2);
      }
    } else {
      cart = pop(stack2);
      if(cart == -1) {
        cart = pop(stack1);
      }
    }

    if(cart != -1) {
      Client client = dequeueWaitingQueue(waitingQueue);

      //Agregar a listado circular simplemente enlazado de compradores
      insertAfter(buyersList, client, cart);
      printf("El cliente: %d, con carrito %d ha pasado a la lista de compradores\n", client, cart);
    } else {
      printf("No hay carritos disponibles\n");
    }
  } else {
    printf("No hay clientes en cola de espera\n");
  }
  printf("\n");
}

// Mover a comprador a la cola de pagos
void goToPaymentQueue() {
  if(buyersList->root) {
    int n = rand() % 101;
    BuyersNode* node = removeBuyer(buyersList, n);
    if(node) {
      enqueuePaymentQueue(paymentQueue, node);
      printf("Se ha agregado a cliente -> %d con carrito %d a cola de pagos\n", node->client, node->cart);
    } else {
      printf("No se ha retidaro ningun cliente de la lista de compradores\n");
    }
  } else {
    printf("La lista de compradores esta vacia\n");
  }
  printf("\n");
}

// Pasar a caja registradora
void goToCashRegister() {
  if(paymentQueue->top) {
    Register id = isAvailable(registerList);
    if(id != -1) {
      printf("Caja disponible: %d\n", id);
    } else {
      printf("No hay cajas registradoras disponibles");
    }
  } else {
    printf("La cola de pagos esta vacia\n");
  }
  printf("\n");
}

