#pragma once
#include <complex>

std::complex<double>*Create1dCplx(int FirstDim);
std::complex<double>**Create2dCplx(int FirstDim, int SecondDim);
std::complex<double>***Create3dCplx(int FirstDim, int SecondDim, int ThirdDim);

void Free1dCplx(std::complex<double> *v);
void Free2dCplx(std::complex<double> **v, int FirstDim);
void Free3dCplx(std::complex<double> ***v, int FirstDim, int SecondDim);

void putZero1dCplx(std::complex<double>* v, int FirstDim);

std::complex<double> DeterminantCplx(int order, std::complex<double>**mat);
std::complex<double> DeterminantCplx_order_tmp(std::complex<double>**mat, int order);
std::complex<double> cinvert_6by6(std::complex<double>** A);

//void InverseMatrixCplx_tmp(int order, std::complex<double>**mat, std::complex<double>**mat_out);
std::complex<double>** InverseMatrixCplx(int order, std::complex<double>**mat);
void InverseMatrixCplx_tmp(int order, std::complex<double>**mat, std::complex<double>** matout);
void GetMinorCplx(std::complex<double>**src, std::complex<double>**dest, int row, int col, int order);
std::complex<double>** MatmulCplx(std::complex<double>**mat1, std::complex<double>**mat2, int row1, int col1, int row2, int col2);
void EigenSolver(std::complex<double>** mat, int order, std::complex<double>*EigenVector, std::complex<double>&EigenValue);
bool isEqual(std::complex<double>** mat1, std::complex<double>** mat2, int row, int col);
std::complex<double> findmax(std::complex<double> **vec, int row, int col);
double calculateError(std::complex<double>** mat1, std::complex<double>** mat2, int row, int col);

void EigenSolverCplx(std::complex<double>** mat, int order, std::complex<double>*EigenVector, std::complex<double>&EigenValue);

void InverseMatrixCplx_Gauss(int order, std::complex<double>**mat_in, std::complex<double>**mat_out);
void MatmulCplx_ver2(std::complex<double>**mat1, std::complex<double>**mat2, std::complex<double> **MulMat, int row1, int col1, int row2, int col2);

void LUPDecompose_cplx(std::complex<double>** A, int order, int * P, std::complex<double>* ptr_tmp);
std::complex<double> determinant_cplx(std::complex<double>** mat_in, int order, std::complex<double>* ptr_tmp, int* P);


