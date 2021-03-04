
#include <stdio.h>
#include <stdlib.h>


int main() {

  FILE* fp;

//X.bin is 575x257x6 complex double of MATLAB    
  fp = fopen("../X.bin","rb");

  double** data;

  data = new double* [];
  while (!feof(fp)) {
  
  }

  fclose(fp);

  return 0;
}