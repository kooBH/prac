
#include <stdio.h>
#include <stdlib.h>

int main() {

  double** arr_3_by_4;

  // column first
  arr_3_by_4 = new double* [4];

  for (int i = 0; i < 4; i++)
    arr_3_by_4[i] = new double[3];

  FILE* fp = fopen("../3_by_4_double.bin","rb");

  for (int i = 0; i < 4; i++)
    fread(arr_3_by_4[i], sizeof(double), 3,fp);
  fclose(fp);


  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++)
      printf("%lf ", arr_3_by_4[i][j]);
    printf("\n");
  }



  return 0;
}