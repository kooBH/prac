//=================================================================================================
/*!
//  Copyright (C) 2012-2019 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================

#include <complex>
#include <iostream>
#include <stdio.h>


std::complex<double> cinvert_6by6(std::complex<double>**A){
  std::complex<double> tmp1 ( A[4][4]*A[5][5] - A[4][5]*A[5][4] );
  std::complex<double> tmp2 ( A[4][3]*A[5][5] - A[4][5]*A[5][3] );
  std::complex<double> tmp3 ( A[4][3]*A[5][4] - A[4][4]*A[5][3] );
  std::complex<double> tmp4 ( A[4][2]*A[5][5] - A[4][5]*A[5][2] );
  std::complex<double> tmp5 ( A[4][2]*A[5][4] - A[4][4]*A[5][2] );
  std::complex<double> tmp6 ( A[4][2]*A[5][3] - A[4][3]*A[5][2] );
  std::complex<double> tmp7 ( A[4][1]*A[5][5] - A[4][5]*A[5][1] );
  std::complex<double> tmp8 ( A[4][1]*A[5][4] - A[4][4]*A[5][1] );
  std::complex<double> tmp9 ( A[4][1]*A[5][3] - A[4][3]*A[5][1] );
  std::complex<double> tmp10( A[4][1]*A[5][2] - A[4][2]*A[5][1] );
  std::complex<double> tmp11( A[4][0]*A[5][5] - A[4][5]*A[5][0] );
  std::complex<double> tmp12( A[4][0]*A[5][4] - A[4][4]*A[5][0] );
  std::complex<double> tmp13( A[4][0]*A[5][3] - A[4][3]*A[5][0] );
  std::complex<double> tmp14( A[4][0]*A[5][2] - A[4][2]*A[5][0] );
  std::complex<double> tmp15( A[4][0]*A[5][1] - A[4][1]*A[5][0] );
  std::complex<double> tmp16( A[3][3]*tmp1  - A[3][4]*tmp2  + A[3][5]*tmp3  );
  std::complex<double> tmp17( A[3][2]*tmp1  - A[3][4]*tmp4  + A[3][5]*tmp5  );
  std::complex<double> tmp18( A[3][2]*tmp2  - A[3][3]*tmp4  + A[3][5]*tmp6  );
  std::complex<double> tmp19( A[3][2]*tmp3  - A[3][3]*tmp5  + A[3][4]*tmp6  );
  std::complex<double> tmp20( A[3][1]*tmp1  - A[3][4]*tmp7  + A[3][5]*tmp8  );
  std::complex<double> tmp21( A[3][1]*tmp2  - A[3][3]*tmp7  + A[3][5]*tmp9  );
  std::complex<double> tmp22( A[3][1]*tmp3  - A[3][3]*tmp8  + A[3][4]*tmp9  );
  std::complex<double> tmp23( A[3][1]*tmp4  - A[3][2]*tmp7  + A[3][5]*tmp10 );
  std::complex<double> tmp24( A[3][1]*tmp5  - A[3][2]*tmp8  + A[3][4]*tmp10 );
  std::complex<double> tmp25( A[3][1]*tmp6  - A[3][2]*tmp9  + A[3][3]*tmp10 );
  std::complex<double> tmp26( A[3][0]*tmp1  - A[3][4]*tmp11 + A[3][5]*tmp12 );
  std::complex<double> tmp27( A[3][0]*tmp2  - A[3][3]*tmp11 + A[3][5]*tmp13 );
  std::complex<double> tmp28( A[3][0]*tmp3  - A[3][3]*tmp12 + A[3][4]*tmp13 );
  std::complex<double> tmp29( A[3][0]*tmp4  - A[3][2]*tmp11 + A[3][5]*tmp14 );
  std::complex<double> tmp30( A[3][0]*tmp5  - A[3][2]*tmp12 + A[3][4]*tmp14 );
  std::complex<double> tmp31( A[3][0]*tmp6  - A[3][2]*tmp13 + A[3][3]*tmp14 );
  std::complex<double> tmp32( A[3][0]*tmp7  - A[3][1]*tmp11 + A[3][5]*tmp15 );
  std::complex<double> tmp33( A[3][0]*tmp8  - A[3][1]*tmp12 + A[3][4]*tmp15 );
  std::complex<double> tmp34( A[3][0]*tmp9  - A[3][1]*tmp13 + A[3][3]*tmp15 );
  std::complex<double> tmp35( A[3][0]*tmp10 - A[3][1]*tmp14 + A[3][2]*tmp15 );
  std::complex<double> tmp36( A[2][2]*tmp16 - A[2][3]*tmp17 + A[2][4]*tmp18 - A[2][5]*tmp19 );
  std::complex<double> tmp37( A[2][1]*tmp16 - A[2][3]*tmp20 + A[2][4]*tmp21 - A[2][5]*tmp22 );
  std::complex<double> tmp38( A[2][1]*tmp17 - A[2][2]*tmp20 + A[2][4]*tmp23 - A[2][5]*tmp24 );
  std::complex<double> tmp39( A[2][1]*tmp18 - A[2][2]*tmp21 + A[2][3]*tmp23 - A[2][5]*tmp25 );
  std::complex<double> tmp40( A[2][1]*tmp19 - A[2][2]*tmp22 + A[2][3]*tmp24 - A[2][4]*tmp25 );
  std::complex<double> tmp41( A[2][0]*tmp16 - A[2][3]*tmp26 + A[2][4]*tmp27 - A[2][5]*tmp28 );
  std::complex<double> tmp42( A[2][0]*tmp17 - A[2][2]*tmp26 + A[2][4]*tmp29 - A[2][5]*tmp30 );
  std::complex<double> tmp43( A[2][0]*tmp18 - A[2][2]*tmp27 + A[2][3]*tmp29 - A[2][5]*tmp31 );
  std::complex<double> tmp44( A[2][0]*tmp19 - A[2][2]*tmp28 + A[2][3]*tmp30 - A[2][4]*tmp31 );
  std::complex<double> b0 =   A[1][1]*tmp36 - A[1][2]*tmp37 + A[1][3]*tmp38 - A[1][4]*tmp39 + A[1][5]*tmp40;
  std::complex<double> b1 = - A[1][0]*tmp36 + A[1][2]*tmp41 - A[1][3]*tmp42 + A[1][4]*tmp43 - A[1][5]*tmp44;
  std::complex<double> tmp45( A[2][0]*tmp20 - A[2][1]*tmp26 + A[2][4]*tmp32 - A[2][5]*tmp33 );
  std::complex<double> tmp46( A[2][0]*tmp21 - A[2][1]*tmp27 + A[2][3]*tmp32 - A[2][5]*tmp34 );
  std::complex<double> tmp47( A[2][0]*tmp22 - A[2][1]*tmp28 + A[2][3]*tmp33 - A[2][4]*tmp34 );
  std::complex<double> tmp48( A[2][0]*tmp23 - A[2][1]*tmp29 + A[2][2]*tmp32 - A[2][5]*tmp35 );
  std::complex<double> tmp49( A[2][0]*tmp24 - A[2][1]*tmp30 + A[2][2]*tmp33 - A[2][4]*tmp35 );
  std::complex<double> b2 =   A[1][0]*tmp37 - A[1][1]*tmp41 + A[1][3]*tmp45 - A[1][4]*tmp46 + A[1][5]*tmp47;
  std::complex<double> b3 = - A[1][0]*tmp38 + A[1][1]*tmp42 - A[1][2]*tmp45 + A[1][4]*tmp48 - A[1][5]*tmp49;
  std::complex<double> tmp50( A[2][0]*tmp25 - A[2][1]*tmp31 + A[2][2]*tmp34 - A[2][3]*tmp35 );
  std::complex<double> b4 =   A[1][0]*tmp39 - A[1][1]*tmp43 + A[1][2]*tmp46 - A[1][3]*tmp48 + A[1][5]*tmp50;
  std::complex<double> b5 = - A[1][0]*tmp40 + A[1][1]*tmp44 - A[1][2]*tmp47 + A[1][3]*tmp49 - A[1][4]*tmp50;
  //det
  return A[0][0]*b0 + A[0][1]*b1 + A[0][2]*b2 +
    A[0][3]*b3 + A[0][4]*b4 + A[0][5]*b5;
}

int main(){
  std::complex<double> **mat;
  mat = new std::complex<double>*[6];
  for(int i=0;i<6;i++)
    mat[i] = new std::complex<double>[6];

  for(int i=0;i<6;i++){
    for(int j=0;j<6;j++){
  //    mat[i][j]={i+1.0 + pow(i+1,j+1),j+1.0 + pow(j+1,i+1)};
      mat[i][j]={i+1.0 + 300*(i+1) ,j+1.0 + pow(j+1,i+1) + 200*(j+1)};
      printf("%.4e + %.4ei ",mat[i][j].real(),mat[i][j].imag() );
    }
    printf("\n");
  }

  std::complex<double>det = cinvert_6by6(mat);
  printf("det : %.4e + %.4ei\n ",det.real(),det.imag() );

//  std::complex<double>a {1.5e06,-2.3e-08};
//  std::complex<double>b {2.1e-07,-4.5e08};
//  std::cout<<a+b<<std::endl;

  return 0;
}
