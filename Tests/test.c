#include "apc.h"
#include <assert.h>

int main(){

  newList t = createList("1234567");
  newList summ = sum("9", "99999999");
  printList(summ);
  newList subtract = sub("1999", "999");
  printList(subtract);

  freeList(t);
  freeList(summ);
  freeList(subtract);

}