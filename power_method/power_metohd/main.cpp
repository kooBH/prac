#include "ComplexMatrix.h"

std::complex<double>* eig_vec;
std::complex<double>* eig_vec_tmp;
std::complex<double>eig_vec_tmp2;

const int N = 4;

int main() {
  eig_vec = Create1dCplx(N);
  eig_vec_tmp = Create1dCplx(N);
  
  int i, j, k;
  for (i = 0; i < 10; i++) {
    // V = diff_Rf_prime * V
    for (j = 0; j < N; j++) {
      eig_vec_tmp2 = { 0.0,0.0 };
      for (k = 0; k < Nch; k++) {
        eig_vec_tmp2[freq] += diff_Rf_prime[freq][j * Nch + k] * eig_vec[freq][k];
        //std::cout <<"+="<< diff_Rf_prime[freq][j * Nch + k] << "\n";
      }
      eig_vec_tmp[freq][j] = eig_vec_tmp2[freq];
      //std::cout << eig_vec[freq][j] << "\n";
    }

    for (j = 0; j < Nch; j++)
      eig_vec[freq][j] = eig_vec_tmp[freq][j];

    // V = V./norm(V)
    eig_vec_tmp2[freq] = { 0.0,0.0 };
    //norm(V)
    for (j = 0; j < Nch; j++)
      eig_vec_tmp2[freq] += (eig_vec[freq][j] * eig_vec[freq][j]);
    eig_vec_tmp2[freq] = std::sqrt(eig_vec_tmp2[freq]);

    //V./norm(V)
    for (j = 0; j < Nch; j++) {
      eig_vec[freq][j] /= (eig_vec_tmp2[freq]);
    }
    // std::cout << eig_vec[freq][0] << "\n";
  }

  return 0;
}