#include "apc.h"
#include <ctype.h>

/* Compare two unsigned digit strings (ignoring leading zeros).
   Returns >0 if a > b, 0 if equal, <0 if a < b  (strcmp alone fails for different lengths) */
static int cmpNum(char *a, char *b){

  while(*a == '0' && *(a+1)) a++;
  while(*b == '0' && *(b+1)) b++;

  int la = strlen(a), lb = strlen(b);

  if(la != lb) return la - lb;
  return strcmp(a, b);

}

/* Check the string is [-]digits */
static int isValid(char *s){

  if(*s == '-') s++;
  if(*s == '\0') return 0;

  while(*s){
    if(!isdigit((unsigned char)*s)) return 0;
    s++;
  }
  return 1;

}

int main(int argc, char *argv[]){

  if(argc != 4){
    printf("Enter the Input in the manner -> \n ./a.out op1 operator op2\n");
    return 0;
  }

  char op = argv[2][0];
  char *op1 = argv[1];
  char *op2 = argv[3];

  if(!isValid(op1) || !isValid(op2)){
    printf("Invalid operand, only integers are allowed\n");
    return 0;
  }

  int neg = 0;
  newList ans;

  switch(op){

    case '+' : {

      if(isdigit(op1[0]) && isdigit(op2[0])){
        ans = sum(op1, op2);
      }
      else if(op1[0] == '-' && isdigit(op2[0])){
        if(cmpNum(op1+1, op2) > 0) {
          ans = sub(op1+1, op2);
          neg = 1;
        }
        else if(cmpNum(op1+1, op2) == 0){ printf("0\n"); return 0; }
        else{
          ans = sub(op2, op1+1);
        }
      }
      else if(isdigit(op1[0]) && op2[0] == '-'){
        if(cmpNum(op2+1, op1) > 0) {
          ans = sub(op2+1, op1);
          neg = 1;
        }
        else if(cmpNum(op2+1, op1) == 0){ printf("0\n"); return 0; }
        else{
          ans = sub(op1, op2+1);
        }
      }
      else{
        ans = sum(op1+1, op2+1);
        neg = 1;
      }

      break;

    }

    case '-': {

      if(isdigit(op1[0]) && isdigit(op2[0])){
        /* a - b */
        if(cmpNum(op1, op2) > 0){
          ans = sub(op1, op2);
        }
        else if(cmpNum(op1, op2) == 0){ printf("0\n"); return 0; }
        else{
          ans = sub(op2, op1);
          neg = 1;
        }
      }
      else if(op1[0] == '-' && isdigit(op2[0])){
        /* -a - b = -(a + b) */
        ans = sum(op1+1, op2);
        neg = 1;
      }
      else if(isdigit(op1[0]) && op2[0] == '-'){
        /* a - (-b) = a + b */
        ans = sum(op1, op2+1);
      }
      else{
        /* -a - (-b) = b - a */
        if(cmpNum(op2+1, op1+1) > 0){
          ans = sub(op2+1, op1+1);
        }
        else if(cmpNum(op2+1, op1+1) == 0){ printf("0\n"); return 0; }
        else{
          ans = sub(op1+1, op2+1);
          neg = 1;
        }
      }

      break;

    }

    case 'x':
    case 'X':
    case '*': {

      /* Sign is negative only when exactly one operand is negative */
      int n1 = (op1[0] == '-'), n2 = (op2[0] == '-');
      char *a = n1 ? op1+1 : op1;
      char *b = n2 ? op2+1 : op2;

      ans = mul(a, b);

      /* Result 0 should not get a '-' sign */
      if((n1 != n2) && !(ans.head->data == 0 && ans.head == ans.tail)) neg = 1;

      break;

    }

    case '/': {

      int n1 = (op1[0] == '-'), n2 = (op2[0] == '-');
      char *a = n1 ? op1+1 : op1;
      char *b = n2 ? op2+1 : op2;

      if(atoll(b) == 0){
        printf("Error : Division by zero\n");
        return 0;
      }

      ans = division(a, b);

      if((n1 != n2) && !(ans.head->data == 0 && ans.head == ans.tail)) neg = 1;

      break;

    }

    default : {
      printf("Invalid operator, use + - x (or *) /\n");
      return 0;
    }

  }

  if(neg) printf("-");

  /* sum and sub store the result in reverse (tail is the most significant digit),
     mul and division store it in normal order (head is the most significant digit) */
  if(op == '+' || op == '-') printList(ans);
  else printListHead(ans);

  freeList(ans);

  return 0;

}
