#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "cart.h"
#include "client.h"
#include "buyer.h"

  // CartStack* stack1;
  // WaitingQueue* queue;
  // BuyersList* list;
  PaymentQueue* queue;

int main() {

  // stack1 = (CartStack*)malloc(sizeof(CartStack));

  // stack1->root = NULL;
  // stack1->size = 10;
  // stack1->actualNode = 0;

  // push(stack1, 1);
  // push(stack1, 2);
  // push(stack1, 3);

  // printCartStack(stack1);
  // printf("Carreta eliminada: %d\n", pop(stack1));
  // printCartStack(stack1);

  // push(stack1, 4);
  // push(stack1, 5);

  // printCartStack(stack1);

  // printf("Carreta eliminada: %d\n", pop(stack1));
  // printf("Carreta eliminada: %d\n", pop(stack1));

  // printCartStack(stack1);

  // queue = (WaitingQueue*)malloc(sizeof(WaitingQueue));
  // queue->bottom = NULL;
  // queue->top = NULL;
  // queue->size = 10;
  // queue->waitingClients = 0;

  // enqueue(queue, 1);
  // enqueue(queue, 2);
  // enqueue(queue, 3);
  // enqueue(queue, 4);
  // enqueue(queue, 5);

  // printWaitingQueue(queue);

  // dequeue(queue);
  // dequeue(queue);

  // printWaitingQueue(queue);
  // enqueue(queue, 6);
  // enqueue(queue, 7);
  // printWaitingQueue(queue);

  // dequeue(queue);
  // dequeue(queue);
  // dequeue(queue);
  // dequeue(queue);
  // dequeue(queue);

  // dequeue(queue);

  // printWaitingQueue(queue);

  // enqueue(queue, 8);
  // enqueue(queue, 9);
  // enqueue(queue, 10);

  // dequeue(queue);

  // printWaitingQueue(queue);

  // dequeue(queue);
  // dequeue(queue);

  // free(queue);

  // BuyersNode* del;

  // list = (BuyersList*)malloc(sizeof(BuyersList));
  // insertAfter(list, 1, 1);
  // insertAfter(list, 2, 2);
  // insertAfter(list, 3, 4);
  // printBuyersList(list);

  // del = removeBuyer(list, 2);
  // printf("Eliminado: Cliente -> %d, Carrito -> %d\n", del->client, del->cart);

  // del = removeBuyer(list, 1);
  // printf("Eliminado: Cliente -> %d, Carrito -> %d\n", del->client, del->cart);

  // del = removeBuyer(list, 3);
  // printf("Eliminado: Cliente -> %d, Carrito -> %d\n", del->client, del->cart);
  // printBuyersList(list);

  // insertAfter(list, 4, 5);
  // insertAfter(list, 5, 6);
  // insertAfter(list, 6, 7);

  // printBuyersList(list);

  queue = (PaymentQueue*)malloc(sizeof(PaymentQueue));
  enqueuePaymentQueue(queue, createBuyersNode(1, 2));
  enqueuePaymentQueue(queue, createBuyersNode(2, 3));
  enqueuePaymentQueue(queue, createBuyersNode(3, 4));
  printPaymentQueue(queue);
  BuyersNode* del = dequeuePaymentQueue(queue);
  printf("Eliminado, cliente -> %d, carrito -> %d\n", del->client, del->cart);
  enqueuePaymentQueue(queue, createBuyersNode(4, 5));
  printPaymentQueue(queue);

  del = dequeuePaymentQueue(queue);
  printf("Eliminado, cliente -> %d, carrito -> %d\n", del->client, del->cart);

  del = dequeuePaymentQueue(queue);
  printf("Eliminado, cliente -> %d, carrito -> %d\n", del->client, del->cart);


  printPaymentQueue(queue);
  del = dequeuePaymentQueue(queue);
  del = dequeuePaymentQueue(queue);
  del = dequeuePaymentQueue(queue);

  printPaymentQueue(queue);

  enqueuePaymentQueue(queue, createBuyersNode(5, 10));
  enqueuePaymentQueue(queue, createBuyersNode(6, 12));
  printPaymentQueue(queue);

  return 0;
}