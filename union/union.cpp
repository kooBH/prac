#include <stdio.h>
#include <stdlib.h>



/* FAIL */
int main(){

union{
  short* s;
  float* f;
}buf;

 buf =(short*)malloc(sizeof(short)*10);
 for(int i=0;i<10;i++)
  buf[i] = i;


 for(int i=0;i<10;i++)
  printf("%d\n",reinterpret_cast<short*>buf[i]);

  return 0;
}
