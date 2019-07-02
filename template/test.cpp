#include <stdio.h>
#include <stdlib.h>

template<typename T>
class  A{
  public:
 A(){}
 ~A(){}
  void hello(){

    printf("hello\n");
  
  }

};

int main(){

  A<int> t1;

  t1.hello();

  return 0;
}
