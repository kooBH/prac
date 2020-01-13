#include <stdio.h>

class A{
  public:
  A(){}
  ~A(){
    printf("~A\n");
  }
};

class B{
  public:
  A a;
  B(){}
  ~B(){
    printf("~B\n");
  }
};

int main(){
  B b;
  return 0;
}
