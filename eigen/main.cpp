#include "test_eigen.hpp"
#include "test_plasma.hpp"
#include "test_lapack.hpp"

int main(){

  test_eigen();
  test_plasma();
  test_zheev();
  test_zheevd();
//  test_zheevd_2stage();
  return 0;
}
