#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Double Linked List Node structure with an alias name - 'dnode' */
typedef struct node{
  struct node *prev;
  int data;
  struct node *next;
}dnode;

/* Contains "Head" and "Tail" Pointers of the newList */
typedef struct{
  dnode *head;
  dnode *tail;
}newList;

/* Create a Brand New list of a integer from a string and returns */
newList createList(char *num);

/* Print the list from tail towards head */
void printList(newList print);

/* Free the Entire List */
void freeList(newList f);

/* Perform addition operation and returns resultList, Expected argv[0], and argv[2] as an arguments */
newList sum(char *num1, char *num2);

/* Perform subtraction operation and returns resultList, Expected argv[0] and argv[2] as an arguments */
newList sub(char *num1, char *num2);

#endif