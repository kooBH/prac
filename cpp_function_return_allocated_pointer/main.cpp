
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>

int* f1(int val,int size) {
  int* p=nullptr;

  printf("p : %d\n",p);
  p = new int[size];

  for (int i = 0; i < size; i++)
    p[i] = val;
  printf("p : %d\n",p);

  return p;
}

int** f2(int val,int size) {
  int** p=nullptr;

  p = new int*[size];
  for (int i = 0; i < size; i++)
    p[i] = new int[size];
  printf("p : %d\n",p);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      p[i][j] = val;
  printf("p : %d\n",p);

  return p;
}

int main() {
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  //_CrtSetBreakAlloc(159);

  int* v = f1(3, 10);
  printf("p : %d\n",v);

  for (int i = 0; i < 10; i++)
    printf("arr[%d]=%d\n",i,v[i]);

  delete[] v;

  int** v2 = f2(2, 4);
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      printf("arr[%d][%d]=%d\n",i,j,v2[i][j]);

  for (int i = 0; i < 4; i++)
    delete[] v2[i];
  delete[] v2;

  return 0;
}