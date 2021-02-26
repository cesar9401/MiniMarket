#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "cart.h"
#include "client.h"
#include "buyer.h"

  // CartStack* stack1;
  // WaitingQueue* queue;
  BuyersList* list;

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

  BuyersNode* del;

  list = (BuyersList*)malloc(sizeof(BuyersList));
  insertAfter(list, 1, 1);
  insertAfter(list, 2, 2);
  insertAfter(list, 3, 4);
  printBuyersList(list);

  del = removeBuyer(list, 2);
  printf("Eliminado: Cliente -> %d, Carrito -> %d\n", del->client, del->cart);

  del = removeBuyer(list, 1);
  printf("Eliminado: Cliente -> %d, Carrito -> %d\n", del->client, del->cart);

  del = removeBuyer(list, 3);
  printf("Eliminado: Cliente -> %d, Carrito -> %d\n", del->client, del->cart);
  printBuyersList(list);

  del = removeBuyer(list, 7);
  //printf("Eliminado: Cliente -> %d, Carrito -> %d\n", del->client, del->cart);

  insertAfter(list, 4, 5);
  insertAfter(list, 5, 6);
  insertAfter(list, 6, 7);

  printBuyersList(list);

  return 0;
}