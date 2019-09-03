#ifndef _H_EIGEN_
#define _H_EIGEN_

#include <iostream>
using std::cout;
using std::endl;

#include <cstdio>

#include <fstream>
using std::fstream;

#include <complex>
using std::complex;

#include <Eigen/Dense>

#include <vector>
using std::vector;

#include <chrono> 
#include <stdio.h>

// https://eigen.tuxfamily.org/dox/classEigen_1_1ComplexEigenSolver.html
#include <Eigen/Eigenvalues> 

using Eigen::MatrixXd;
using Eigen::MatrixXcd;
using Eigen::ComplexEigenSolver;
using Eigen::VectorXcd;


using std::string;

void test_eigen()
{
  vector<int>size = {2,6,8,16};
  FILE *input;
  string file_input;

  cout<<"========= EIGEN LIBRARY =====\n"<<endl;

  for(int i : size){
    file_input = "../data/A_" + std::to_string(i) + ".b";
    cout<<"open " << file_input<<" | "<<endl;
    input = fopen(file_input.c_str(),"rb");
    if(!input)
      exit(-1);

    MatrixXcd A(i,i);

    double real,imag;
    /* matlab binary output은 col major */
    for(int w=0;w<i;w++){
      for(int h=0;h<i;h++){
        fread(&real,sizeof(double),1,input);
        fread(&imag,sizeof(double),1,input);
        A(w,h) = {real,imag};
        //    printf("(%lf, %lf) ",real,imag);
        //cout<<real << " "<<imag<<endl;
      }
      // cout<<endl;
    }
/*
    cout<<endl;
    cout<<"\n";
    cout<<A<<endl;
    */

    //    cout << " A " << endl << A << endl << endl;
    ComplexEigenSolver<MatrixXcd> ces;
    ces.compute(A);

    //cout<<"\n*** sum(A*V - V*D )  "<<endl;

    MatrixXcd ans = A*ces.eigenvectors() - ces.eigenvectors() * ces.eigenvalues().asDiagonal();

    //cout<<ans<<endl;

    auto start = std::chrono::high_resolution_clock::now();

    for(int iter =0;iter<1000;iter++)
      ces.compute(A);
    auto finish= std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count()/1000 << " s\n";

    std::cout<<"======================"<<std::endl;
    //std::cout<<A<<std::endl;
    //std::cout<<ces.eigenvectors()<<std::endl;
    /*
       complex<double> lambda = ces.eigenvalues()[0];
       cout << "Consider the first eigenvalue, lambda = " << lambda << endl;
       VectorXcd v = ces.eigenvectors().col(0);

       cout << "If v is the corresponding eigenvector, then lambda * v = " << endl << lambda * v << endl;
       cout << "... and A * v = " << endl << A * v << endl << endl;
       cout << "Finally, V * D * V^(-1) = " << endl
       << ces.eigenvectors() * ces.eigenvalues().asDiagonal() * ces.eigenvectors().inverse() << endl;
       */
    fclose(input);
  }
}

#endif
