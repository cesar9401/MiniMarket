#include <stdio.h>
#include <stdlib.h>
#include "buyer.h"

// Crear nuevo nodo
BuyersNode* createBuyersNode(Client client, Cart cart) {
  BuyersNode* tmp = (BuyersNode*)malloc(sizeof(BuyersNode));
  tmp->client = client;
  tmp->cart = cart;
  tmp->next = NULL;

  return tmp;
}

// Insertar nodo al final de la lista
void insertAfter(BuyersList* list, Client client, Cart cart) {
  BuyersNode* tmp = createBuyersNode(client, cart);

  if(!list->root) {
    list->root = tmp;
    tmp->next = tmp;
  } else {
    BuyersNode* node = list->root;
    while(node->next != list->root) {
      node = node->next;
    }
    node->next = tmp;
    tmp->next = list->root;
  }
  list->buyersCount++;
}

// Eliminar cliente de la lista segun id
BuyersNode* removeBuyer(BuyersList* list, Client client) {
  if(list->root) {
    BuyersNode* node = list->root;
    if(node->client == client) {
      if(node->next != list->root) {
        BuyersNode* tmp = node;
        while(tmp->next != list->root) {
          tmp = tmp->next;
        }
        list->root = node->next;
        tmp->next = list->root;
        node->next = NULL;
        return node;
      } else {
        list->root = NULL;
        node->next = NULL;
        return node;
      }
    } else {
      while(node->next != list->root) {
        if(node->next->client == client) {
          BuyersNode* tmp = node->next;
          node->next = tmp->next;
          tmp->next = NULL;
          return tmp;
        }
        node = node->next;
      }
      printf("Cliente %d, no encontrado.\n", client);
    }
  } else {
    printf("Listado vacio\n");
  }

  return NULL;
}

// Imprimir listado de compradores
void printBuyersList(BuyersList* list) {
  if(!list->root) {
    printf("Listado vacio\n");
  } else{
    BuyersNode* node = list->root;
    printf("Listado de clientes:\n");
    do {
      printf("Cliente ->  %d, Carrito -> %d\n", node->client, node->cart);
      node = node->next;
    }while(node != list->root);
    //printf("Cliente ->  %d, Carrito -> %d\n", node->client, node->cart);
  }
}