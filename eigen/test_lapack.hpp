/*** STD ***/
#include <iostream>
using std::cout;
using std::endl;

#include <cstdio>

#include <fstream>
using std::fstream;

#include <vector>
using std::vector;

#include <algorithm>

#include <chrono> 
#include <stdio.h>

/* LAPACK */
//http://www.netlib.org/lapack/explore-html/d9/de3/group__complex_h_eeigen.html
#include "lapacke.h"

void test_lapack(){

  vector<int>size = {2,6,8,16};

  FILE *input;
  string file_input;

  char JOBS='V'; // values and vectors 
  char UPLO = 'U'; // U,L doesn't matter
  int N ; //2-D
  double* A;
  int LDA; // Leading Dimension of A
  double *W; // EigenValues
  double *WORK; // work
  int LWORK; // length of WORK
  double *RWORK;
  int INFO;

  /*
   * LAPACK_zheev( &jobz, &uplo, &n, a, &lda, w, work, &lwork, rwork,
                      &info );
   * */
  for(int i : size){
    N = i;
    LDA = N;
    LWORK = std::max(1,2*i-1);  // length of WORK
    /* Data Read*/
    file_input = "../data/A_" + std::to_string(i) + ".b";
    cout<<"open " << file_input<<" | ";
    input = fopen(file_input.c_str(),"rb");
    if(!input)
      exit(-1);

    A = new double[2*i*i];
    W = new double[i];
    WORK = new double[2*LWORK];
    RWORK = new double[std::max(1,3*i-1)];


    double real,imag;
    int idx = 0;
    /* matlab binary output은 col major */
    for(int w=0;w<i;w++){
      for(int h=0;h<i;h++){
        fread(&real,sizeof(double),1,input);
        fread(&imag,sizeof(double),1,input);
        A[idx] = real;
        idx++;
        A[idx] = imag;
        idx++;
        //cout<<real << " "<<imag<<endl;
      }
    }

   if(i == 6){
      std::cout<<"\n";
    for(int w=0;w<i;w++){
      for(int h=0;h<i;h++){
        printf("%.2lf %.2lf | ",A[idx],A[idx+1]);
        idx+=2;
      }
      printf("\n");
    }
    }

    /* Compute & Time */
    auto start = std::chrono::high_resolution_clock::now();
    for(int iter =0;iter<1000;iter++){
      LAPACK_zheev(&JOBS,&UPLO,&N,(__complex__ double*)A,&LDA,
          W,
          (__complex__ double*)WORK,&LWORK,RWORK,&INFO);
    }
    auto finish= std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count()/1000 << " s\n";

    idx =0;
    if(i == 6){
    std::cout<<"======================"<<std::endl;
    for(int w=0;w<i;w++){
      for(int h=0;h<i;h++){
        printf("%.2lf %.2lf | ",A[idx],A[idx+1]);
        idx+=2;
      }
      printf("\n");
    }
    }

    
    delete[] A,W,WORK,RWORK;
    fclose(input);
  }




}



