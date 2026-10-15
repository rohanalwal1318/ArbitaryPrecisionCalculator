#include "apc.h"
#include <assert.h>

int main(){

  newList t = createList("1234567");
  newList summ = sum("9", "99999999");
  printList(summ);
  newList subtract = sub("1999", "999");
  printList(subtract);
  newList multi = mul("123", "3");
  printList(multi);

  freeList(t);
  freeList(summ);
  freeList(subtract);
  freeList(multi);

}