#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Mis librerias
#include "lib/cart.h"
#include "lib/client.h"
#include "lib/buyer.h"
#include "lib/cash-register.h"

// Graphviz
#include "graphviz/gvc.h"

// Archivo para escribir dot
FILE* file;

// Numero de carritos y cajas
int cartsCount;
int registerCount;
int clients;

// Estructuras para elementos de la tienda
WaitingQueue* waitingQueue;
CartStack* stack1;
CartStack* stack2;
BuyersList* buyersList;
PaymentQueue* paymentQueue;
RegisterList* registerList;

// Definir funciones
void menu();
void setElements();
void printStatus();
void takeCart();
void goToPaymentQueue();
void goToCashRegister();
void exitSystem();
void writeDot();
void createPngFromDot();
void startSimulation(int turn);

int main() {
  // Write your code here
  srand(time(NULL));

  menu();

  return 0;
}

// menu principal
void menu() {
  int turn = 0;
  int opcion;

  setElements();

  do {
    printf("\nMiniMarket - Turno %d\n", turn);
    printf("1 - Ver diagrama del turno\n");
    printf("2 - Siguiente turno\n");
    printf("3 - Ir al final de la simulacion\n");
    printf("4 - Salir\n");
    printf("Opcion: ");
    scanf("%d", &opcion);

    switch (opcion) {
    case 1:
      writeDot(turn);
      break;

    case 2:
      turn++;
      startSimulation(turn);
      break;

    case 3:
      while(waitingQueue->top || buyersList->root || paymentQueue->top || registerList->busy > 0) {
        turn++;
        startSimulation(turn);
      }
      break;

    case 4:
      printf("\nAdios\n");
      break;

    default:
      printf("\nOpcion no valida\n");
      break;
    }
  }while(opcion != 4);
}

// Ejecuta el turno actual de la simulacion
void startSimulation(int turn) {
  if(waitingQueue->top || buyersList->root || paymentQueue->top || registerList->busy > 0) {
    printf("\n------------------------ Turno %d -----------------------\n", turn);

    while((stack1->root || stack2->root) && waitingQueue->top) {
      takeCart();
    }

    for(int i = 0; i < 3; i++) {
      goToPaymentQueue();
    }

    for(int i = 0; i < registerCount; i++) {
      exitSystem();
    }

    while(registerList->busy < registerList->count && paymentQueue->top) {
      goToCashRegister();
    }
  } else {
    printf("\nLa simulacion ha terminado\n");
  }
}

// Iniializar los elementos de miniMarket
void setElements() {
  int a, b, c, d, count, n, p;
  // registerCount = 6;
  // a = 10;
  // b = 20;
  // c = 25;
  // d = 30;

  printf("Defina el numero de cajas para pagos: ");
  scanf("%d", &registerCount);

  printf("Defina la cantidad de clientes en la cola de pagos: ");
  scanf("%d", &a);

  printf("Defina la cantidad de clientes comprando: ");
  scanf("%d", &b);

  /* Se deben tomar en cuenta los carritos con los clientes que estan comprando y los clientes en la cola de pagos */
  do {
    printf("Defina la cantidad de carretas por pila: ");
    scanf("%d", &c);
    if(2*c < a + b) {
      printf("La cantidad de carritos totales, debe ser mayor o igual a la cantidad de clientes en la cola de pagos y clientes comprando\n");
    }
  }while(2*c < a + b);

  printf("Defina la cantidad de clientes en la cola de espera de carretas: ");
  scanf("%d", &d);

  cartsCount = 2 * c;

  //inicializar elementos
  registerList = initRegisterList(registerCount);
  paymentQueue = initPaymentQueue(a);
  buyersList = initBuyersList(b, a);

  count = a + b;
  if(count % 2 == 0) {
    n = c - (a + b) / 2;
    p = n;
  } else {
    n = c - (a + b - 1) / 2;
    p = c - (a + b + 1) / 2;
  }

  stack1 = initCartStack(c, n, count);
  stack2 = initCartStack(c, p, count + n);
  waitingQueue = initWaitinQueue(d, count);

  clients = a + b + d;
}

// Imprimir en consola el estado actual de los componentes de miniMarket
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
}

// Mover a comprador a la cola de pagos
void goToPaymentQueue() {
  if(buyersList->root) {
    int n = rand() % (clients + 1);
    BuyersNode* node = removeBuyer(buyersList, n);
    if(node) {
      enqueuePaymentQueue(paymentQueue, node);
      printf("Se ha agregado a cliente -> %d con carrito -> %d a cola de pagos\n", node->client, node->cart);
    } else {
      //printf("No se ha retidaro ningun cliente de la lista de compradores\n");
    }
  } else {
    //printf("La lista de compradores esta vacia\n");
  }
}

// Pasar a caja registradora
void goToCashRegister() {
  if(paymentQueue->top) {
    RegisterNode* registerNode = availableRegisterNode(registerList);
    if(registerNode) {
      //printf("Caja disponible: %d\n", registerNode->id);
      BuyersNode* buyer = dequeuePaymentQueue(paymentQueue);
      registerNode->buyer = buyer;
      registerNode->status = "Ocupado";
      registerList->busy++;
      printf("Cliente -> %d con carrito -> %d ha pasado a caja -> %d\n", registerNode->buyer->client, registerNode->buyer->cart, registerNode->id);
    } else {
      printf("No hay cajas registradoras disponibles\n");
    }
  } else {
    printf("La cola de pagos esta vacia\n");
  }
}

// Terminar de pagar y salida del sistema
void exitSystem() {
  Register id = rand() % registerCount;
  // printf("id -> %d\n", id);
  BuyersNode* node = finishPaying(registerList, id);
  if(node) {
    Cart cart = node->cart;
    int n = rand() % 2;
    if(n) {
      if(stack1->count < stack1->size) {
        push(stack1, cart);
      } else {
        push(stack2, cart);
      }
    } else {
      if(stack2->count < stack2->size) {
        push(stack2, cart);
      } else {
        push(stack1, cart);
      }
    }

    printf("El cliente -> %d sale del sistema, libera carrito -> %d y caja -> %d\n", node->client, node->cart, id);
    registerList->busy--;
    //goToCashRegister();
    free(node);
  }
}

// Escribir archivo .dot
void writeDot(int turn) {
  file = fopen("diagram.dot", "w");
  fprintf(file, "digraph diagram {\n");
  fprintf(file, "label = \"Turno %d\";\n", turn);
  fprintf(file, "rankdir = LR;\n");
  fprintf(file, "node [\n");
  fprintf(file, "shape = \"box\";\n");
  fprintf(file, "]\n\n");

  // insertar informacion de estructuras aqui
  printWaitingQueueInDot(file, waitingQueue);
  printCartStackInDot(file, stack1, 1);
  printCartStackInDot(file, stack2, 2);
  printBuyersListInDot(file, buyersList);
  printPaymentQueueInDot(file, paymentQueue);
  printRegisterListInDot(file, registerList);

  fprintf(file, "}\n");
  fclose(file);

  // crear png
  createPngFromDot();

  printf("\n\nEl diagrama del turno %d ha sido generado\n\n", turn);
}

// Crear archivo .png desde archivo .dot
void createPngFromDot() {
  GVC_t* gvc;
  graph_t* g;
  FILE* file;

  gvc = gvContext();

  file = fopen("diagram.dot", "r");

  g = agread(file, 0);

  gvLayout(gvc, g, "dot");

  //gvRender(gvc, g, "plain", stdout);
  //gvRender(gvc, g, "png", file);
  gvRenderFilename(gvc, g, "png", "diagram.png");

  gvFreeLayout(gvc, g);

  agclose(g);

  gvFreeContext(gvc);
}
