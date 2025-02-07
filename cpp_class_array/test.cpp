#include <stdio.h>

class A {
public:
  A(int idx) {
    printf("id : %d\n",idx);
  }
};

int main() {
  int n = 4;
  A** arr = new A * [n];

  for (int i = 0; i < n; i++) {
    arr[i] = new A(i);
  }

  for (int i = 0; i < n; i++)
    delete arr[i];
  delete[] arr;

  return 0;
}