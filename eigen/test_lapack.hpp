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
#include "cblas.h"
#include "lapacke.h"

#define NoTran 111
#define Tran 112
#define CTran 113

inline void print_mat(double *data, int size,const char* name){
    int idx=0;
    printf("====== %s =====\n",name);
    for(int w=0;w<size;w++){
      for(int h=0;h<size;h++){
//        cout<<data[idx]<<" + "<<data[idx+1]<<"i |";
          printf("%-+.4lf %-+.4lfi | ",data[idx],data[idx+1]);
        idx+=2;
      }
      cout<<endl;
    }
    cout<<endl;
}

void test_lapack(){

  cout<<"========= OpenBLAS LAPACK =====\n"<<endl;

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

  double* V,*D;
  double *ans_1,*ans_2;

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

    V = new double[2*i*i];
    D = new double[2*i*i];
    ans_1= new double[2*i*i];
    ans_2= new double[2*i*i];

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
        //       printf("(%lf, %lf) ",real,imag);
        //cout<<real << " "<<imag<<endl;
      }
      // cout<<endl;
    }
/*
    std::cout<<"\n";
    idx = 0;
    for(int w=0;w<i;w++){
      for(int h=0;h<i;h++){
        printf("%lf %lf | ",A[idx],A[idx+1]);
        idx+=2;
      }
      printf("\n");
    }
    */

    memcpy(V,A,sizeof(double)*2*i*i);

    /* Compute & Time */
    auto start = std::chrono::high_resolution_clock::now();
    for(int iter =0;iter<1000;iter++){

      LAPACK_zheev(&JOBS,&UPLO,&N,(__complex__ double*)V,&LDA,
          W,
          (__complex__ double*)WORK,&LWORK,RWORK,&INFO);

    }
    auto finish= std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count()/1000 << " s | ";

//    idx =0;
//    std::cout<<"======================"<<std::endl;
//    for(int w=0;w<i;w++){
//      for(int h=0;h<i;h++){
//        printf("%.2lf %.2lf | ",A[idx],A[idx+1]);
//        idx+=2;
//      }
//      printf("\n");
//    }
//
    cout<<" sum(A*V-V*D) : ";
/*
 *  cplx mat * cplx mat  - cplx mat * real vec
 * */


    memcpy(V,A,sizeof(double)*2*i*i);

      LAPACK_zheev(&JOBS,&UPLO,&N,(__complex__ double*)V,&LDA,
          W,
          (__complex__ double*)WORK,&LWORK,RWORK,&INFO);

    /* A*V */
    struct cplx {double re;double im; };

    struct cplx alpha = {1,0};
    struct cplx beta = {0,0};

    int m,n,k,lda,ldb,ldc;

    m = i;
    n = i;
    k = i;
    lda = i;
    ldb = i;
    ldc = i;

    cblas_zgemm(CblasColMajor, CblasNoTrans,CblasNoTrans , m, n, k, &alpha,
                  A, lda,
                  V, ldb, &beta,
                 ans_1, ldc);

  //  print_mat(A,i,"A");
  //  print_mat(V,i,"V");
   // print_mat(ans_1,i,"A*V");

    /* V*D */

    // Make D
    idx =0;
    for(int w=0;w<i;w++) {
      for(int h=0;h<i;h++){
        if(h==w){
          D[idx]=W[h];
        }
        else{
          D[idx] = 0; 
        }
        D[idx+1] = 0;  //real matrix
        idx+=2;
      }
    }
    
    cblas_zgemm(CblasColMajor, CblasNoTrans,CblasNoTrans , m, n, k, &alpha,
                  V, lda,
                  D, ldb, &beta,
                 ans_2, ldc);

//    print_mat(D,i,"D");
//    print_mat(ans_2,i,"V*D");

   double ans_re = 0;
   double ans_im = 0;
    idx =0;
    for(int w=0;w<i;w++) {
      for(int h=0;h<i;h++){
        ans_re+= ans_1[idx] - ans_2[idx];
        ans_im+= ans_1[idx+1] - ans_2[idx+1];
        idx+=2;
      
      }
    }

    cout<<ans_re <<" + "<< ans_im<<"i"<<endl;




    delete[] A,W,WORK,RWORK,V,D,ans_1,ans_2;
    fclose(input);
  }
}



