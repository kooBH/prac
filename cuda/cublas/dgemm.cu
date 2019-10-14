
#include "cuda_runtime.h"
#include <cublas_v2.h>
#include <stdio.h>

const int N = 4;

int main(){
  double *x,*y,*c;

  cublasHandle_t handle;
  cublasCreate(&handle); 

  // Allocate Unified Memory – accessible from CPU or GPU
  cudaMallocManaged(&x, N*N*sizeof(double));
  cudaMallocManaged(&y, N*N*sizeof(double));
  cudaMallocManaged(&c, N*N*sizeof(double));

  for(int col=0;col<N;col++){
    for(int row=0;row<N;row++){
      x[col*N + row ] = (col+1)*2 + (row+1);
      y[col*N + row ] = (row+1)*3 - (col+1);
    }
  }


  for(int col=0;col<N;col++){
    for(int row=0;row<N;row++)
      printf("%lf ",x[row*N + col]);
    printf("\n");
  }

    printf("\n");
  for(int col=0;col<N;col++){
    for(int row=0;row<N;row++)
      printf("%lf ",y[row*N + col]);
    printf("\n");
  }

	cublasOperation_t transa,transb;


	transa = CUBLAS_OP_N;
	transb = CUBLAS_OP_N;	

  double alpha = 1;

cublasDgemm(handle,transa,transb,N,N,N,&alpha,x,N,y,N,&alpha,c,N);


  // Wait for GPU to finish before accessing on host
  cudaDeviceSynchronize();

    printf("\n");
  for(int col=0;col<N;col++){
    for(int row=0;row<N;row++)
      printf("%lf ",c[row*N + col]);
    printf("\n");
  }


  // Free memory
  cudaFree(x);
  cudaFree(y);
  cudaFree(c);


  // Undefined Error.. Why? 
  //cublasDestory(handle);

  return 0;
}
