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

#define ITER 1000

#include "eigen_solver.hpp"

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

void test_zheev(){

  cout<<"========= OpenBLAS LAPACK ZHEEV =====\n"<<endl;

  vector<int>size = {2,4,6,8,16};

  FILE *input;
  string file_input;

  double* A;
  double* V,*D;
  double *ans_1,*ans_2;

  /*
   * LAPACK_zheev( &jobz, &uplo, &n, a, &lda, w, work, &lwork, rwork,
   &info );
   * */
  for(int i : size){


    /* Data Read*/
    file_input = "../data/A_" + std::to_string(i) + ".b";
    input = fopen(file_input.c_str(),"rb");
    cout<<"size["<< i<<"] ";
    if(!input)
      exit(-1);

    A = new double[2*i*i];
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
      }
    }
    fclose(input);

    eigen_ZHEEV ev(i);
    /* Compute & Time */
    auto start = std::chrono::high_resolution_clock::now();
    for(int iter =0;iter<ITER;iter++){
      ev.ZHEEV(A,V,D);
      //COMPUTE
    }
    auto finish= std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "time: " << elapsed.count()/ITER << " s | ";


    //memcpy(V,A,sizeof(double)*2*i*i);


    ev.ZHEEV(A,V,D);
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

    /* V*D */
    cblas_zgemm(CblasColMajor, CblasNoTrans,CblasNoTrans , m, n, k, &alpha,
                  V, lda,
                  D, ldb, &beta,
                 ans_2, ldc);

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
    delete[] A,V,D,ans_1,ans_2;

  }
}


void test_zheevd(){

  cout<<"========= OpenBLAS LAPACK ZHEEVD =====\n"<<endl;

  vector<int>size = {2,4,6,8,16};
  //vector<int>size = {4};

  FILE *input;
  string file_input;

  double* A;
  double* V,*D;
  double *ans_1,*ans_2;

  /*
   * LAPACK_zheev( &jobz, &uplo, &n, a, &lda, w, work, &lwork, rwork,
   &info );
   * */
  for(int i : size){


    /* Data Read*/
    file_input = "../data/A_" + std::to_string(i) + ".b";
    input = fopen(file_input.c_str(),"rb");
    cout<<"size["<< i<<"] ";
    if(!input)
      exit(-1);

    A = new double[2*i*i];
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
      }
    }
    fclose(input);

    eigen_ZHEEVD ev(i);
    /* Compute & Time */
    auto start = std::chrono::high_resolution_clock::now();
    for(int iter =0;iter<ITER;iter++){
      ev.ZHEEVD(A,V,D);
      //COMPUTE
    }
    auto finish= std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "time: " << elapsed.count()/ITER<< " s | ";


    //memcpy(V,A,sizeof(double)*2*i*i);


    ev.ZHEEVD(A,V,D);
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

    /* V*D */
    cblas_zgemm(CblasColMajor, CblasNoTrans,CblasNoTrans , m, n, k, &alpha,
                  V, lda,
                  D, ldb, &beta,
                 ans_2, ldc);

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
    delete[] A,V,D,ans_1,ans_2;

  }
}





void test_zheevd_2stage(){

  cout<<"========= OpenBLAS LAPACK ZHEEVD 2stage =====\n"<<endl;

  vector<int>size = {2,4,6,8,16};
  //vector<int>size = {4};

  FILE *input;
  string file_input;

  double* A;
  double* V,*D;
  double *ans_1,*ans_2;

  /*
   * LAPACK_zheev( &jobz, &uplo, &n, a, &lda, w, work, &lwork, rwork,
   &info );
   * */
  for(int i : size){


    /* Data Read*/
    file_input = "../data/A_" + std::to_string(i) + ".b";
    input = fopen(file_input.c_str(),"rb");
    cout<<"size["<< i<<"] ";
    if(!input)
      exit(-1);

    A = new double[2*i*i];
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
      }
    }
    fclose(input);

    eigen_ZHEEVD ev(i);
    /* Compute & Time */
    auto start = std::chrono::high_resolution_clock::now();
    for(int iter =0;iter<ITER;iter++){
      ev.ZHEEVD_2stage(A,V,D);
      //COMPUTE
    }
    auto finish= std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "time: " << elapsed.count()/ITER<< " s | ";


    //memcpy(V,A,sizeof(double)*2*i*i);


    ev.ZHEEVD_2stage(A,V,D);
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

    /* V*D */
    cblas_zgemm(CblasColMajor, CblasNoTrans,CblasNoTrans , m, n, k, &alpha,
                  V, lda,
                  D, ldb, &beta,
                 ans_2, ldc);

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
    delete[] A,V,D,ans_1,ans_2;

  }
}


