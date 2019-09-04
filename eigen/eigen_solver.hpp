#include "cblas.h"
#include "lapacke.h"

#define NoTran 111
#define Tran 112
#define CTran 113

#include <algorithm>

/*
http://www.netlib.org/lapack/explore-html/df/d9a/group__complex16_h_eeigen_gaf23fb5b3ae38072ef4890ba43d5cfea2.html#gaf23fb5b3ae38072ef4890ba43d5cfea2
*/



/*** ZHEEV - base class ***/

class eigen_ZHEEV{
  protected: 
    char JOBS; // values and vectors 
    char UPLO; // U,L doesn't matter
    int N ; //2-D
    double* A;
    int LDA; // Leading Dimension of A
    double *W; // EigenValues
    double *WORK; // work
    int LWORK; // length of WORK
    double *RWORK;
    int INFO;

  public :

    inline eigen_ZHEEV(int N);
    // ZHEEVD has different LWORK
    inline eigen_ZHEEV(int N,int LWORK);
    inline ~eigen_ZHEEV();
    inline int ZHEEV( double*X,double *V,double *D );
};

inline eigen_ZHEEV::eigen_ZHEEV(int _N):
  JOBS('V'),
  UPLO('U'),
  N(_N)
{
  N = N;
  LDA = N;
  LWORK = std::max(1,2*N-1);

  A = new double[2*N*N];
  W = new double[N];
  WORK = new double[2*LWORK];
  RWORK = new double[std::max(1,3*N-1)];

}

inline eigen_ZHEEV::eigen_ZHEEV(int _N, int _LWORK):
  JOBS('V'),
  UPLO('U'),
  N(_N)
{
  N = N;
  LDA = N;
  LWORK = _LWORK;

  A = new double[2*N*N];
  W = new double[N];
  WORK = new double[2*LWORK];
  RWORK = new double[std::max(1,3*N-1)];


}


inline eigen_ZHEEV::~eigen_ZHEEV(){
  delete[] A,W,WORK,RWORK;
}


inline int eigen_ZHEEV::ZHEEV(double*_A,double*V,double*D){

  memcpy(A,_A,sizeof(double)*N*N*2);

  LAPACK_zheev(
      &JOBS,
      &UPLO,
      &N,
      (__complex__ double*)A,
      &LDA,
      W,
      (__complex__ double*)WORK,
      &LWORK,
      RWORK,
      &INFO);

  memcpy(V,A,sizeof(double)*N*N*2);

      int idx=0;
      for(int w=0;w<N;w++) {
        for(int h=0;h<N;h++){
          if(h==w)
            D[idx]=W[h];
          else
            D[idx] = 0; 
          D[idx+1] = 0; 
          idx+=2;
        }
      }
  return INFO;
}

/*** ZHEEVD ***/

class eigen_ZHEEVD : public eigen_ZHEEV{
   protected :
     int LRWORK;
     int * IWORK;
     int LIWORK;

   public:
     inline eigen_ZHEEVD(int N);
     inline ~eigen_ZHEEVD( );
     inline int ZHEEVD(  double*X,double *V,double *D );
     inline int ZHEEVD_2stage(  double*X,double *V,double *D );
};

inline eigen_ZHEEVD::eigen_ZHEEVD(int _N):
eigen_ZHEEV(_N, 2*_N+_N*_N){

  LRWORK = 1 + 5*N + 2*N*N;
  LIWORK = 3 + 5*N;
  IWORK = new int[LIWORK ];

}

inline eigen_ZHEEVD::~eigen_ZHEEVD(){
  delete[] IWORK;

}

inline int eigen_ZHEEVD::ZHEEVD( double*_A, double *V, double *D){

  memcpy(A,_A,sizeof(double)*N*N*2);

  LAPACK_zheevd(
      &JOBS,
      &UPLO,
      &N,
      (__complex__ double*)A,
      &LDA,
      W,
      (__complex__ double*)WORK,
      &LWORK,
      RWORK,
      &LRWORK,
      IWORK,
      &LIWORK,
      &INFO);

  memcpy(V,A,sizeof(double)*N*N*2);

       int idx=0;
      for(int w=0;w<N;w++) {
        for(int h=0;h<N;h++){
          if(h==w)
            D[idx]=W[h];
          else
            D[idx] = 0; 
          D[idx+1] = 0; 
          idx+=2;
        }
      }
  return INFO;

}


inline int eigen_ZHEEVD::ZHEEVD_2stage(  double*_A,double *V,double *D ){
  memcpy(A,_A,sizeof(double)*N*N*2);

  LAPACK_zheevd_2stage(
      &JOBS,
      &UPLO,
      &N,
      (__complex__ double*)A,
      &LDA,
      W,
      (__complex__ double*)WORK,
      &LWORK,
      RWORK,
      &LRWORK,
      IWORK,
      &LIWORK,
      &INFO);

  memcpy(V,A,sizeof(double)*N*N*2);

      int idx=0;
      for(int w=0;w<N;w++) {
        for(int h=0;h<N;h++){
          if(h==w)
            D[idx]=W[h];
          else
            D[idx] = 0; 
          D[idx+1] = 0; 
          idx+=2;
        }
      }
  return INFO;


}


