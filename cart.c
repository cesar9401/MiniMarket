#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct cart {
  int id;
  struct cart *next;
} Cart;

Cart *carts = NULL;

Cart *newCart(int n) {
  Cart *tmp = (Cart*)malloc(sizeof(Cart));
  tmp->id = n;
  tmp->next = NULL;

  return tmp;
}

void push(int n) {
  Cart *new = newCart(n);
  new->next = carts;
  carts = new;
}

Cart *pop() {
  Cart *tmp = NULL;
  if(carts) {
    tmp = carts;
    carts = carts->next;

    tmp->next = NULL;
  }

  return tmp;
}

void printStack() {
  if(carts) {
    Cart *tmp = carts;
    printf("Valores en pila: \n");
    do {
      printf("id -> %d\n", tmp->id);
      tmp = tmp->next;
    } while(tmp);
  } else {
    printf("La pila esta vacia\n");
  }
  printf("\n");
}

int main() {

  push(1);
  push(2);
  push(3);
  printStack();
  pop();
  push(4);
  printStack();
  pop();
  push(5);
  printStack();
  pop();
  printStack();
  pop();
  printStack();
  pop();
  pop();
  printStack();
  push(6);
  printStack();

  return 0;
}