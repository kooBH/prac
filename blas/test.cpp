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
  double **a1,**a2;
  double **b1,**b2;
  double **c1;
  double **c2;

  int i,j;

std::cout<<"iteration : "<<num_iter<<"\n";
/* alloc */
  a1 = new double*[Nfreq*2];
  for(i=0;i<Nfreq*2;i++)a1[i]= new double[Nch*NT];
  b1 = new double*[Nfreq*2];
  for(i=0;i<Nfreq*2;i++)b1[i]= new double[NT];

  a2 = new double*[Nfreq];
  for(i=0;i<Nfreq;i++)a2[i]= new double[Nch*NT*2];
  b2 = new double*[Nfreq];
  for(i=0;i<Nfreq;i++)b2[i]= new double[NT*2];


  c1 = new double*[Nfreq*2];
  for(i=0;i<Nfreq*2;i++)c1[i]= new double[Nch];

  c2 = new double*[Nfreq];
  for(i=0;i<Nfreq;i++)c2[i]= new double[Nch*2];

  /* init */
  for(i=0;i<Nfreq*2;i++){
    for(j=0;j<Nch*NT;j++)
      a1[i][j] = 1;
    for(j=0;j<NT;j++)
      b1[i][j] = 1;
  }
  for(i=0;i<Nfreq*2;i++)
    for(j=0;j<Nch;j++)
      c1[i][j]=0.0;


  for(i=0;i<Nfreq;i++){
    for(j=0;j<Nch*NT*2;j++)
      a2[i][j] = 1;
    for(j=0;j<NT*2;j++)
      b2[i][j] = 1;
  }

  for(i=0;i<Nfreq;i++)
    for(j=0;j<Nch*2;j++)
      c2[i][j]=0.0;

  

auto start = std::chrono::high_resolution_clock::now();
for(i=0;i<num_iter;i++)  test_omp(a1,b1,c1);
auto elapsed = std::chrono::high_resolution_clock::now() - start;
long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
std::cout<<"omp  : "<<microseconds<<"("<<(double)microseconds/1000000<<")\n";

start = std::chrono::high_resolution_clock::now();
for(i=0;i<num_iter;i++)  test_blas(a2,b2,c2);

elapsed = std::chrono::high_resolution_clock::now() - start;
microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
std::cout<<"blas : "<<microseconds<<"("<<(double)microseconds/1000000<<")\n";

double diff_r = 0.0;
double diff_i = 0.0;
  for(i=0;i<Nfreq;i++){
    for(j=0;j<Nch;j++){
      diff_r+=fabs(c1[2*i][j] - c2[i][2*j]);
      diff_i+=fabs(c1[2*i+1][j] - c2[i][2*j+1]);
//      std::cout<<c1[2*i][j]<<" "<<c2[i][2*j]<<"\n";
    }
  }
  std::cout<<diff_r<<"\n";
  std::cout<<diff_i<<"\n";
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
  CMP alpha(1.0,0.0);
  CMP beta(0.0,0.0);
#pragma omp parallel for
  for(int i=0;i<Nfreq;i++)
cblas_zgemm(CblasColMajor,CblasNoTrans,CblasConjNoTrans,
    Nch,1,NT,&alpha,a[i],Nch,b[i],NT,&beta,c[i],Nch);

}

