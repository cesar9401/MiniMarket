#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "elements.h"



int main() {
  CartStack* stack1;
  stack1 = (CartStack*)malloc(sizeof(CartStack));

  stack1->root = NULL;
  stack1->size = 10;
  stack1->actualNode = 0;

  push(stack1, 1);
  push(stack1, 2);
  push(stack1, 3);

  printCartStack(stack1);
  printf("Carreta eliminada: %d\n", pop(stack1));
  printCartStack(stack1);

  push(stack1, 4);
  push(stack1, 5);

  printCartStack(stack1);

  printf("Carreta eliminada: %d\n", pop(stack1));
  printf("Carreta eliminada: %d\n", pop(stack1));

  printCartStack(stack1);

  return 0;
}