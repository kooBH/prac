/*
 * 처음 돌린거, 데이터 구조가 맞지 않다.
 * 결과는 빠른거 확인함. 값은 틀림.
 * */

#include <cblas.h>
#include <chrono>
#include <iostream>
#include <math.h>

#define Nfreq 512
#define Nch 6
#define tap 7
#define NT Nch*tap

#define num_iter 1000

void test_blas(double**,double**,double**);
void test_omp(double**,double**,double**);

typedef struct CMP{
double re,im;
CMP(){
  re = 1.0;
  im = 0.0;
}
CMP(double r,double i){
  re = r;
  im = i;
}
}CMP;

int main(){
  double **a;
  double **b;
  double **c1;
  double **c2;

  int i,j;
/* alloc */
  a = new double*[Nfreq*2];
  for(i=0;i<Nfreq*2;i++)a[i]= new double[Nch*NT];
  b = new double*[Nfreq*2];
  for(i=0;i<Nfreq*2;i++)b[i]= new double[NT];
  c1 = new double*[Nfreq*2];
  for(i=0;i<Nfreq*2;i++)c1[i]= new double[Nch];
  c2 = new double*[Nfreq*2];
  for(i=0;i<Nfreq*2;i++)c2[i]= new double[Nch];

  /* init */
  for(i=0;i<Nfreq*2;i++){
    for(j=0;j<Nch*NT;j++)
      a[i][j] = i+j;
    for(j=0;j<NT;j++)
      b[i][j] = i+j;
  }

auto start = std::chrono::high_resolution_clock::now();
for(i=0;i<num_iter;i++)  test_omp(a,b,c1);
auto elapsed = std::chrono::high_resolution_clock::now() - start;
long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
std::cout<<"omp  : "<<microseconds<<"("<<(double)microseconds/1000000<<")\n";

start = std::chrono::high_resolution_clock::now();
for(i=0;i<num_iter;i++)  test_blas(a,b,c2);

elapsed = std::chrono::high_resolution_clock::now() - start;
microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
std::cout<<"blas : "<<microseconds<<"("<<(double)microseconds/1000000<<")\n";

double diff = 0.0;
  for(i=0;i<Nfreq*2;i++){
    for(j=0;j<Nch;j++){
      diff+=fabs(c1[i][j] - c2[i][j]);
      std::cout<<c1[i][j]<<" "<<c2[i][j]<<"\n";
    }
  }
  std::cout<<diff<<"\n";
}


void test_omp(double**g,double**X_delay,double**x){
double t_re = 0.0;
double t_im = 0.0;
int i,j,k;
#pragma omp parallel for schedule(static,8) private(i,j,t_re,t_im)
  for (k = 0; k < Nfreq; k++){
    const int real = 2 * k;
    const int imag = 2 * k + 1;
      for (i = 0; i < Nch; ++i) {
        t_re = 0.0;
        t_im = 0.0;
        for (j = 0; j < NT; ++j) {
          t_re += g[real][j * Nch + i] * X_delay[real][j] +
            g[imag][j * Nch + i] * X_delay[imag][j];
          t_im += -g[imag][j * Nch + i] * X_delay[real][j] +
            g[real][j * Nch + i] * X_delay[imag][j];
        }
        x[real][i]=t_re;
        x[imag][i]=t_im;
      }
  }
}
void test_blas(double**a,double**b,double**c){
  CMP alpha;
  CMP beta(0,0);
//#pragma omp parallel for
  for(int i=0;i<Nfreq;i++)
cblas_zgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,
    Nch,1,NT,&alpha,a[2*i],Nch,b[2*i],NT,&beta,c[2*i],Nch);
}

