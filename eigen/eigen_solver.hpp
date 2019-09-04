#include "cblas.h"
#include "lapacke.h"

#define NoTran 111
#define Tran 112
#define CTran 113

#include <algorithm>

/*
http://www.netlib.org/lapack/explore-html/df/d9a/group__complex16_h_eeigen_gaf23fb5b3ae38072ef4890ba43d5cfea2.html#gaf23fb5b3ae38072ef4890ba43d5cfea2
*/

/*
subroutine zheev	(	character 	JOBZ,
  character 	UPLO,
  integer 	N,
  complex*16, dimension( lda, * ) 	A,
  integer 	LDA,
  double precision, dimension( * ) 	W,
  complex*16, dimension( * ) 	WORK,
  integer 	LWORK,
  double precision, dimension( * ) 	RWORK,
  integer 	INFO 
)	

ZHEEV computes the eigenvalues and, optionally, the left and/or right eigenvectors for HE matrices

Download ZHEEV + dependencies [TGZ] [ZIP] [TXT]

Purpose:
 ZHEEV computes all eigenvalues and, optionally, eigenvectors of a
 complex Hermitian matrix A.
Parameters
[in]	JOBZ	
          JOBZ is CHARACTER*1
          = 'N':  Compute eigenvalues only;
          = 'V':  Compute eigenvalues and eigenvectors.
[in]	UPLO	
          UPLO is CHARACTER*1
          = 'U':  Upper triangle of A is stored;
          = 'L':  Lower triangle of A is stored.
[in]	N	
          N is INTEGER
          The order of the matrix A.  N >= 0.
[in,out]	A	
          A is COMPLEX*16 array, dimension (LDA, N)
          On entry, the Hermitian matrix A.  If UPLO = 'U', the
          leading N-by-N upper triangular part of A contains the
          upper triangular part of the matrix A.  If UPLO = 'L',
          the leading N-by-N lower triangular part of A contains
          the lower triangular part of the matrix A.
          On exit, if JOBZ = 'V', then if INFO = 0, A contains the
          orthonormal eigenvectors of the matrix A.
          If JOBZ = 'N', then on exit the lower triangle (if UPLO='L')
          or the upper triangle (if UPLO='U') of A, including the
          diagonal, is destroyed.
[in]	LDA	
          LDA is INTEGER
          The leading dimension of the array A.  LDA >= max(1,N).
[out]	W	
          W is DOUBLE PRECISION array, dimension (N)
          If INFO = 0, the eigenvalues in ascending order.
[out]	WORK	
          WORK is COMPLEX*16 array, dimension (MAX(1,LWORK))
          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
[in]	LWORK	
          LWORK is INTEGER
          The length of the array WORK.  LWORK >= max(1,2*N-1).
          For optimal efficiency, LWORK >= (NB+1)*N,
          where NB is the blocksize for ZHETRD returned by ILAENV.

          If LWORK = -1, then a workspace query is assumed; the routine
          only calculates the optimal size of the WORK array, returns
          this value as the first entry of the WORK array, and no error
          message related to LWORK is issued by XERBLA.
[out]	RWORK	
          RWORK is DOUBLE PRECISION array, dimension (max(1, 3*N-2))
[out]	INFO	
          INFO is INTEGER
          = 0:  successful exit
          < 0:  if INFO = -i, the i-th argument had an illegal value
          > 0:  if INFO = i, the algorithm failed to converge; i
                off-diagonal elements of an intermediate tridiagonal
                form did not converge to zero.
Author
Univ. of Tennessee
Univ. of California Berkeley
Univ. of Colorado Denver
NAG Ltd.
Date
December 2016
 * */



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

/*

subroutine zheevd	(	character 	JOBZ,
  character 	UPLO,
  integer 	N,
  complex*16, dimension( lda, * ) 	A,
  integer 	LDA,
  double precision, dimension( * ) 	W,
  complex*16, dimension( * ) 	WORK,
  integer 	LWORK,
  double precision, dimension( * ) 	RWORK,
  integer 	LRWORK,
  integer, dimension( * ) 	IWORK,
  integer 	LIWORK,
  integer 	INFO 
)	

Purpose:
 ZHEEVD computes all eigenvalues and, optionally, eigenvectors of a
 complex Hermitian matrix A.  If eigenvectors are desired, it uses a
 divide and conquer algorithm.

 The divide and conquer algorithm makes very mild assumptions about
 floating point arithmetic. It will work on machines with a guard
 digit in add/subtract, or on those binary machines without guard
 digits which subtract like the Cray X-MP, Cray Y-MP, Cray C-90, or
 Cray-2. It could conceivably fail on hexadecimal or decimal machines
 without guard digits, but we know of none.
Parameters
[in]	JOBZ	
          JOBZ is CHARACTER*1
          = 'N':  Compute eigenvalues only;
          = 'V':  Compute eigenvalues and eigenvectors.
[in]	UPLO	
          UPLO is CHARACTER*1
          = 'U':  Upper triangle of A is stored;
          = 'L':  Lower triangle of A is stored.
[in]	N	
          N is INTEGER
          The order of the matrix A.  N >= 0.
[in,out]	A	
          A is COMPLEX*16 array, dimension (LDA, N)
          On entry, the Hermitian matrix A.  If UPLO = 'U', the
          leading N-by-N upper triangular part of A contains the
          upper triangular part of the matrix A.  If UPLO = 'L',
          the leading N-by-N lower triangular part of A contains
          the lower triangular part of the matrix A.
          On exit, if JOBZ = 'V', then if INFO = 0, A contains the
          orthonormal eigenvectors of the matrix A.
          If JOBZ = 'N', then on exit the lower triangle (if UPLO='L')
          or the upper triangle (if UPLO='U') of A, including the
          diagonal, is destroyed.
[in]	LDA	
          LDA is INTEGER
          The leading dimension of the array A.  LDA >= max(1,N).
[out]	W	
          W is DOUBLE PRECISION array, dimension (N)
          If INFO = 0, the eigenvalues in ascending order.
[out]	WORK	
          WORK is COMPLEX*16 array, dimension (MAX(1,LWORK))
          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
[in]	LWORK	
          LWORK is INTEGER
          The length of the array WORK.
          If N <= 1,                LWORK must be at least 1.
          If JOBZ  = 'N' and N > 1, LWORK must be at least N + 1.
          If JOBZ  = 'V' and N > 1, LWORK must be at least 2*N + N**2.

          If LWORK = -1, then a workspace query is assumed; the routine
          only calculates the optimal sizes of the WORK, RWORK and
          IWORK arrays, returns these values as the first entries of
          the WORK, RWORK and IWORK arrays, and no error message
          related to LWORK or LRWORK or LIWORK is issued by XERBLA.
[out]	RWORK	
          RWORK is DOUBLE PRECISION array,
                                         dimension (LRWORK)
          On exit, if INFO = 0, RWORK(1) returns the optimal LRWORK.
[in]	LRWORK	
          LRWORK is INTEGER
          The dimension of the array RWORK.
          If N <= 1,                LRWORK must be at least 1.
          If JOBZ  = 'N' and N > 1, LRWORK must be at least N.
          If JOBZ  = 'V' and N > 1, LRWORK must be at least
                         1 + 5*N + 2*N**2.

          If LRWORK = -1, then a workspace query is assumed; the
          routine only calculates the optimal sizes of the WORK, RWORK
          and IWORK arrays, returns these values as the first entries
          of the WORK, RWORK and IWORK arrays, and no error message
          related to LWORK or LRWORK or LIWORK is issued by XERBLA.
[out]	IWORK	
          IWORK is INTEGER array, dimension (MAX(1,LIWORK))
          On exit, if INFO = 0, IWORK(1) returns the optimal LIWORK.
[in]	LIWORK	
          LIWORK is INTEGER
          The dimension of the array IWORK.
          If N <= 1,                LIWORK must be at least 1.
          If JOBZ  = 'N' and N > 1, LIWORK must be at least 1.
          If JOBZ  = 'V' and N > 1, LIWORK must be at least 3 + 5*N.

          If LIWORK = -1, then a workspace query is assumed; the
          routine only calculates the optimal sizes of the WORK, RWORK
          and IWORK arrays, returns these values as the first entries
          of the WORK, RWORK and IWORK arrays, and no error message
          related to LWORK or LRWORK or LIWORK is issued by XERBLA.
[out]	INFO	
          INFO is INTEGER
          = 0:  successful exit
          < 0:  if INFO = -i, the i-th argument had an illegal value
          > 0:  if INFO = i and JOBZ = 'N', then the algorithm failed
                to converge; i off-diagonal elements of an intermediate
                tridiagonal form did not converge to zero;
                if INFO = i and JOBZ = 'V', then the algorithm failed
                to compute an eigenvalue while working on the submatrix
                lying in rows and columns INFO/(N+1) through
                mod(INFO,N+1).
Author
Univ. of Tennessee
Univ. of California Berkeley
Univ. of Colorado Denver
NAG Ltd.
Date
December 2016
Further Details:
Modified description of INFO. Sven, 16 Feb 05.
Contributors:
Jeff Rutter, Computer Science Division, University of California at Berkeley, USA
 * */

 class eigen_ZHEEVD : public eigen_ZHEEV{
   protected :
     int LRWORK;
     int * IWORK;
     int LIWORK;

   public:
     inline eigen_ZHEEVD(int N);
     inline ~eigen_ZHEEVD( );
     inline int ZHEEVD(  double*X,double *V,double *D );
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
