#include<stdio.h>
#include<string.h>

int main(){
  int ans = strcmp("1312", "1412");
  printf("%d\n",ans);
}

int maxi(int a, int b){
  if(a > b) return a;
  else return b;
}

int main(){

  int n, num, maxi;
  scanf("%d", &n);
  
  for(int i=0; i<4; i++){
    scanf("%d", &num);
    if(i == 0) maxi = num;
    maxi = max(maxi, num);
  }


}