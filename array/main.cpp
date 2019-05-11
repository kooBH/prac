#include <iostream>
#include <initializer_list>
#include "array.h"
#include <chrono>


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
   switch(dim){
     case 0:break;
   
   }

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

  /********** 2D ************/

  simd_array<long,2> d2{8,512};
  double **c2;
  c2 = new double*[8];
  for(int i=0;i<8;i++)
    c2[i]= new double[512];

  /********* 4D ************/

  /* simd_aray */
  simd_array<long,4> d3{1,2,3,4};
  d3[0][1][2][3]=1;

  /* mine*/
  arr<long>my_d{1,2,3,4};

  /* native */
  long****c;
  c= new long***[1];
  c[0]=new long**[2];
  for(int i=0;i<2;i++)
    c[0][i]= new long*[3];
  for(int i=0;i<2;i++)
    for(int j=0;j<3;j++)
    c[0][i][j]=new long[4];

  
  /** TEST ***/


  const long n1 = 1000;
  long n2Array[6] = {128*8,256*8,512*8,1024*8,2048*8,4096*8};

  std::cout<<"### 4D Acess\n\n";

  std::cout<<"n1|n2|simd_array|native_array\n";
  std::cout<<"---|---|---|---\n";
  for(int k=0;k<6;k++){
      long n2 = n2Array[k];

      std::cout<<n1;
      std::cout<<"|"<<n2;

      auto start = std::chrono::high_resolution_clock::now();
      for(int j=0;j<n1;j++){
          for(long i =0; i<n2;i++){
            d3[0][1][2][3]=i;
          }
      }
      auto elapsed = std::chrono::high_resolution_clock::now() - start;
      long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
      std::cout<<"| "<<microseconds<<"("<<(double)microseconds/1000000<<")";
      
     start = std::chrono::high_resolution_clock::now();
      for(int j=0;j<n1;j++)
          for(long i =0; i<n2;i++)
            c[0][1][2][3]=i;
      elapsed = std::chrono::high_resolution_clock::now() - start;
      microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
      std::cout<<"| "<<microseconds<<"("<<(double)microseconds/1000000<<")\n";
  }

  std::cout<<"\n";

  std::cout<<"### 2D Access\n\n";

  std::cout<<"n1|n2|simd_array|native_array\n";
  std::cout<<"---|---|---|---\n";
  for(int k=0;k<6;k++){
      long n2 = n2Array[k];

      std::cout<<n1;
      std::cout<<"|"<<n2;

      auto start = std::chrono::high_resolution_clock::now();
      for(int j=0;j<n1;j++){
          for(long i =0; i<n2;i++){
            d2[0][1]=i;
          }
      }
      auto elapsed = std::chrono::high_resolution_clock::now() - start;
      long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
      std::cout<<"| "<<microseconds<<"("<<(double)microseconds/1000000<<")";
      
     start = std::chrono::high_resolution_clock::now();
      for(int j=0;j<n1;j++)
          for(long i =0; i<n2;i++)
            c2[0][1]=i;
      elapsed = std::chrono::high_resolution_clock::now() - start;
      microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
      std::cout<<"| "<<microseconds<<"("<<(double)microseconds/1000000<<")\n";
  }

  std::cout<<"\n";



  return 0;
}
