#include<stdio.h>
#include<stdlib.h>

/* Worked */

int main(){
  void* p;

  p = new short[10];

  for(int i=0;i<10;i++){
    reinterpret_cast<short*>(p)[i]=i;
  }


  for(int i=0;i<10;i++){
    printf("%d\n",reinterpret_cast<short*>(p)[i]);
  }

  return 0;
}
