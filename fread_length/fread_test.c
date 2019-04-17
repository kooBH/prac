#include <stdlib.h>
#include <stdio.h>

int main(){
  FILE *fp;
  fp = fopen("input","rb");
  char buf[9];
  printf("%d\n",fread(buf,sizeof(char),8,fp));
  buf[8]='\0';
  printf("%s\n",buf);

  return 0;
}
