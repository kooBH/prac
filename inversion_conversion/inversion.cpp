#define SIZE 2

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct CTYPE{
  double re;
  double im;
} CTYPE;


void cinvert_2by2(double* _X, double* _Y) {

  CTYPE *X,*Y;
  CTYPE det;
  double t;

  // test
  X = reinterpret_cast<CTYPE*>(_X);
  Y = reinterpret_cast<CTYPE*>(_Y);

  det.re = (X[0].re * X[3].re - X[0].im * X[3].im) -
           (X[2].re * X[1].re - X[2].im * X[1].im);
  det.im = (X[0].re * X[3].im + X[0].im * X[3].re) -
           (X[2].re * X[1].im + X[2].im * X[1].re);

  t = det.re;
  det.re = (det.re) / (det.re * det.re + det.im * det.im);
  det.im = -(det.im) / (t * t + det.im * det.im);
  Y[0].re = (X[3].re * det.re - X[3].im * det.im);
  Y[0].im = (X[3].re * det.im + X[3].im * det.re);

  Y[3].re = (X[0].re * det.re - X[0].im * det.im);
  Y[3].im = (X[0].re * det.im + X[0].im * det.re);

  Y[1].re = -(X[1].re * det.re - X[1].im * det.im);
  Y[1].im = -(X[1].re * det.im + X[1].im * det.re);


  Y[2].re = -(X[2].re * det.re - X[2].im * det.im);
  Y[2].im = -(X[2].re * det.im + X[2].im * det.re);
}

inline void print_mat(double *x){
  int idx=0;
  for(int i=0;i<SIZE;i++){
    for(int j=0;j<SIZE;j++){
      printf("(%lf + %lfi)",x[idx],x[idx+1]);
      idx+=2;
    }
    printf("\n");
  }

}

int main(){
  double *in,*out;

  in= new double[2*SIZE*SIZE];
  out= new double[2*SIZE*SIZE];

//  srand(NULL);
  for(int i=0;i<2*SIZE*SIZE;i++)
   in[i] = (double)rand()/RAND_MAX;

  cinvert_2by2(in,out);
  print_mat(in);
  printf("\n");
  print_mat(out);

  return 0;
}
