#include "cblas.h"
#include "lapacke.h"

#define NoTran 111
#define Tran 112
#define CTran 113

#include <algorithm>

/*
http://www.netlib.org/lapack/explore-html/df/d9a/group__complex16_h_eeigen_gaf23fb5b3ae38072ef4890ba43d5cfea2.html#gaf23fb5b3ae38072ef4890ba43d5cfea2
*/

class eigen_ZGEEV {
  //http://www.netlib.org/lapack/explore-html/db/d55/group__complex16_g_eeigen_ga0eb4e3d75621a1ce1685064db1ac58f0.html#ga0eb4e3d75621a1ce1685064db1ac58f0
  /* 
    +  JOBVL(R) : 
          = 'N': left(right) eigenvectors of A are not computed;
          = 'V': left(right) eigenvectors of are computed
    + N : The order of the matrix
    + A : On entry, the N-by-N matrix A. On exit, A has been overwritten.
    + LDA : The leading dimension of the array A.  LDA >= max(1,N).
    + W :   W is COMPLEX*16 array, dimension (N). W contains the computed eigenvalues.
    + VL : VL is COMPLEX*16 array, dimension (LDVL,N)
          If JOBVL = 'V', the left eigenvectors u(j) are stored one
          after another in the columns of VL, in the same order
          as their eigenvalues.
          If JOBVL = 'N', VL is not referenced.
          u(j) = VL(:,j), the j-th column of VL.
    + WORK : WORK is COMPLEX*16 array, dimension (MAX(1,LWORK)). 
             On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
    + LWORK : LWORK is INTEGER
          The dimension of the array WORK.  LWORK >= max(1,2*N).
          For good performance, LWORK must generally be larger.

          If LWORK = -1, then a workspace query is assumed; the routine
          only calculates the optimal size of the WORK array, returns
          this value as the first entry of the WORK array, and no error
          message related to LWORK is issued by XERBLA.
    + RWORK : RWORK is DOUBLE PRECISION array, dimension (2*N)
  */
protected : 
  char 	JOBVL;
  char 	JOBVR;
  int 	N; 
  double* A;
  int 	LDA;
  double*	W;
  double*  	VL;
  int 	LDVL;
  double* 	VR;
  int 	LDVR;
  double*  	WORK;
  int 	LWORK;
  double *	RWORK;
  int 	INFO;

public:
  inline eigen_ZGEEV(int N);
  inline ~eigen_ZGEEV();
  inline void ZGEEV(double* X, double* V, double* D);
};

inline eigen_ZGEEV::eigen_ZGEEV(int _N):
  JOBVL('N'),
  JOBVR('Y'){

  N = _N;
  LDA = N;
  LDVL = N;
  LDVR = N;
  LWORK = std::max(1, 2 * N);

  A = new double[2 * N * N];
  W = new double[2 * N];
  WORK = new double[2 * LWORK];
  RWORK = new double[2 * N];

}

inline eigen_ZGEEV::~eigen_ZGEEV() {
  delete[] A;
  delete[] W;
  delete[] WORK;
  delete[] RWORK;
}

inline void ZGEEV(double* X, double* V, double* D) {
  memcpy(A, X, sizeof(double) * N * N * 2);

  LAPACK_zgeev(
    &JOBVL,
    &JOBVR,
    &N,
    (__complex__ double*)A,
    &LDA,
    (__complex__ double*)W,
    (__complex__ double*)VL,
    &LDVL,
    (__complex__ double*)V,
    &LDVR,
    (__complex__ double*)WORK,
    &LWORK,
    RWORK,
    &INFO);

  int idx = 0;
  for (int w = 0; w < N; w++) {
    for (int h = 0; h < N; h++) {
      if (h == w)
        D[idx] = W[h];
      else
        D[idx] = 0;
      D[idx + 1] = 0;
      idx += 2;
    }
  }
  return INFO;
}

/*** ZHEEV - base class for Hermitian ***/

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


