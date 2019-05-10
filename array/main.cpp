#include <iostream>
#include <initializer_list>
#include "array.h"

template <class T>
class arr{
  private:
    int dim;
    size_t size;
    T* data;
 
 public:
 arr(std::initializer_list<T> l){
   printf("arr constructor\n");
   dim = l.size();
   size = 1;
   for(auto i : l){
     size *=i;
     printf("size : %lu\n",size);
   }
   // 값들의 포인터 메모리 할당
   data = static_cast<T*>(malloc(sizeof(T*)*size));
   printf("array assgined %lu\n",sizeof(T*)*size);
   // 실제 값 메모리 할당
   for (size_t i = 0; i < size; ++i) 
     new (&data[i]) T;
   }

};




int main(){
  simd_array<double,4> d3{1,2,4,5};
  d3[1][2][3][4]=1;
//  printf("%lf\n",d3[1][2][3][4]);
  arr<double>my_d{2,4,5,6};
  return 0;
}
