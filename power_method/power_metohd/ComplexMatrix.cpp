#include <complex>
#include"ComplexMatrix.h"
#include<iostream>

std::complex<double>*Create1dCplx(int FirstDim)
{
	std::complex<double> *v;
	v = new std::complex<double>[FirstDim];
	return v;
}

std::complex<double>**Create2dCplx(int FirstDim, int SecondDim)
{
	int i;
	std::complex<double> **v;
	v = new std::complex<double>*[FirstDim];
	for (i = 0; i < FirstDim; i++)
	{
		v[i] = new std::complex<double>[SecondDim];
	}
	return v;
}

std::complex<double>***Create3dCplx(int FirstDim, int SecondDim, int ThirdDim)
{
	int i, j;

	std::complex<double> ***v;
	v = new std::complex<double>**[FirstDim];
	for (i = 0; i < FirstDim; i++)
	{
		v[i] = new std::complex<double>*[SecondDim];
		for (j = 0; j < SecondDim; j++)
		{
			v[i][j] = new std::complex<double>[ThirdDim];
		}
	}
	return v;
}

void Free1dCplx(std::complex<double> *v)
{
	delete v;
}

void Free2dCplx(std::complex<double> **v, int FirstDim)
{
	int i;
	for (i = 0; i < FirstDim; i++)
		delete[] v[i];
	delete[] v;
}

void Free3dCplx(std::complex<double> ***v, int FirstDim, int SecondDim)
{
	int i, j;

	for (i = 0; i < FirstDim; i++)
	{
		for (j = 0; j < SecondDim; j++)
			delete[] v[i][j];
		delete[] v[i];
	}

	delete[] v;
}

void putZero1dCplx(std::complex<double>* v, int FirstDim)
{
	for (int i = 0; i < FirstDim; i++)
	{
		v[i] = { 0.0, 0.0 };
	}
}


void GetMinorCplx(std::complex<double>**src, std::complex<double>**dest, int row, int col, int order)
{
	int rowCount = 0, colCount = 0;
	for (int i = 0; i < order; i++)
	{
		if (i != row)
		{
			colCount = 0;
			for (int j = 0; j < order; j++)
			{
				// when j is not the element
				if (j != col)
				{
					dest[rowCount][colCount] = src[i][j];
					colCount++;
				}
			}
			rowCount++;
		}
	}
}


std::complex<double> DeterminantCplx_order_tmp(std::complex<double>**mat, int order)
{
	if (order == 2)
		return((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));

	if (order == 3)
	{
		std::complex<double> a = mat[0][0];
		std::complex<double> b = mat[0][1];
		std::complex<double> c = mat[0][2];
		std::complex<double> d = mat[1][0];
		std::complex<double> e = mat[1][1];
		std::complex<double> f = mat[1][2];
		std::complex<double> g = mat[2][0];
		std::complex<double> h = mat[2][1];
		std::complex<double> i = mat[2][2];

		return a * e*i - a * f*h - b * d*i + b * f*g + c * d*h - c * e*g;
	}


	if (order == 4)
	{
		std::complex<double> a = mat[0][0];
		std::complex<double> b = mat[0][1];
		std::complex<double> c = mat[0][2];
		std::complex<double> d = mat[0][3];
		std::complex<double> e = mat[1][0];
		std::complex<double> f = mat[1][1];
		std::complex<double> g = mat[1][2];
		std::complex<double> h = mat[1][3];
		std::complex<double> i = mat[2][0];
		std::complex<double> j = mat[2][1];
		std::complex<double> k = mat[2][2];
		std::complex<double> l = mat[2][3];
		std::complex<double> m = mat[3][0];
		std::complex<double> n = mat[3][1];
		std::complex<double> o = mat[3][2];
		std::complex<double> p = mat[3][3];

		return a * (f*k*p - f * l*o - f * j*p + f * l*n + h * j*o - h * k*n)
			+ b * (e*k*p - e * l*o - g * i*p + g * l*m + h * j*o - h * k*m)
			+ c * (e*j*p - e * l*n - f * i*p + h * i*n - h * j*m)
			+ d * (e*j*o - e * k*n - f * i*o + f * k*m + g * i*n - g * j*m);


	}


}

void LUPDecompose_cplx(std::complex<double>** A, int order, int *P, std::complex<double>* ptr_tmp)
{
	int i, j, k, imax;
	double maxA, absA;
	//std::cout << "A in: " << std::endl;
	//for (int itmp = 0; itmp < order; itmp++)
	//{
	//	for (int ktmp = 0; ktmp < order; ktmp++)
	//	{
	//		std::cout << A[itmp][ktmp];
	//	}
	//	std::cout << std::endl;
	//}
		//std::complex<double>  absA;
	//std::complex<double>* ptr_tmp = Create1dCplx(order);
	//std::complex<double>* ptr_tmp = new std::complex<double>[1];
	//*ptr, 

	for (i = 0; i <= order; i++)
		P[i] = i; //Unit permutation matrix, P[N] initialized with N

	for (i = 0; i < order; i++) {
		maxA = 0.0;
		imax = i;

		for (k = i; k < order; k++)
			if ((absA = abs(A[k][i])) > maxA) {
				maxA = absA;
				imax = k;
			}

		//if (maxA < Tol) return 0; //failure, matrix is degenerate

		if (imax != i) {
			//pivoting P
			j = P[i];
			P[i] = P[imax];
			P[imax] = j;

			//pivoting rows of A
			ptr_tmp = A[i];
			A[i] = A[imax];
			A[imax] = ptr_tmp;

			//counting pivots starting from N (for determinant)
			P[order]++;
		}

		//std::cout << "A pivoting: " << std::endl;
		//for (int itmp = 0; itmp < order; itmp++)
		//{
		//	for (int ktmp = 0; ktmp < order; ktmp++)
		//	{
		//		std::cout << A[itmp][ktmp];
		//	}
		//	std::cout << std::endl;
		//}


		for (j = i + 1; j < order; j++) {
			A[j][i] /= A[i][i];

			for (k = i + 1; k < order; k++)
				A[j][k] -= A[j][i] * A[i][k];
		}
	}


	//std::cout << "A out: " << std::endl;
	//for (int itmp = 0; itmp < order; itmp++)
	//{
	//	for (int ktmp = 0; ktmp < order; ktmp++)
	//	{
	//		std::cout << A[itmp][ktmp];
	//	}
	//	std::cout << std::endl;
	//}


	//delete ptr_tmp;
	//Free1dCplx(ptr_tmp);
	//ptr_tmp = NULL;
}


std::complex<double> determinant_cplx(std::complex<double>** mat_in, int order, std::complex<double>* ptr_tmp, int*P)
{
	//int* P;

	// P = new int[order + 1];

	std::complex<double> det;

	LUPDecompose_cplx(mat_in, order, P, ptr_tmp);
	det = mat_in[0][0];

	for (int i = 1; i < order; i++)
	{
		det *= mat_in[i][i];
	}

	if ((P[order] - order) % 2 == 0)
		return det;
	else
		return -det;

	//delete P;
	//P = NULL;
}


std::complex<double> DeterminantCplx(int order, std::complex<double>**mat)
{
	int k;
	std::complex<double>**submat = Create2dCplx(order, order);


	if (order == 4)
	{
		return DeterminantCplx_order_tmp(mat, order);
	}

	std::complex<double> d;

	if (order == 2)
	{
		return((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
	}

	for (k = 0; k < order; k++)
	{
		GetMinorCplx(mat, submat, 0, k, order);
		d = d + (pow(-1, k) * mat[0][k] * DeterminantCplx(order - 1, submat));
	}

	Free2dCplx(submat, order);

	return d;
}

std::complex<double> cinvert_6by6(std::complex<double>** A) {
	std::complex<double> tmp1(A[4][4] * A[5][5] - A[4][5] * A[5][4]);
	std::complex<double> tmp2(A[4][3] * A[5][5] - A[4][5] * A[5][3]);
	std::complex<double> tmp3(A[4][3] * A[5][4] - A[4][4] * A[5][3]);
	std::complex<double> tmp4(A[4][2] * A[5][5] - A[4][5] * A[5][2]);
	std::complex<double> tmp5(A[4][2] * A[5][4] - A[4][4] * A[5][2]);
	std::complex<double> tmp6(A[4][2] * A[5][3] - A[4][3] * A[5][2]);
	std::complex<double> tmp7(A[4][1] * A[5][5] - A[4][5] * A[5][1]);
	std::complex<double> tmp8(A[4][1] * A[5][4] - A[4][4] * A[5][1]);
	std::complex<double> tmp9(A[4][1] * A[5][3] - A[4][3] * A[5][1]);
	std::complex<double> tmp10(A[4][1] * A[5][2] - A[4][2] * A[5][1]);
	std::complex<double> tmp11(A[4][0] * A[5][5] - A[4][5] * A[5][0]);
	std::complex<double> tmp12(A[4][0] * A[5][4] - A[4][4] * A[5][0]);
	std::complex<double> tmp13(A[4][0] * A[5][3] - A[4][3] * A[5][0]);
	std::complex<double> tmp14(A[4][0] * A[5][2] - A[4][2] * A[5][0]);
	std::complex<double> tmp15(A[4][0] * A[5][1] - A[4][1] * A[5][0]);
	std::complex<double> tmp16(A[3][3] * tmp1 - A[3][4] * tmp2 + A[3][5] * tmp3);
	std::complex<double> tmp17(A[3][2] * tmp1 - A[3][4] * tmp4 + A[3][5] * tmp5);
	std::complex<double> tmp18(A[3][2] * tmp2 - A[3][3] * tmp4 + A[3][5] * tmp6);
	std::complex<double> tmp19(A[3][2] * tmp3 - A[3][3] * tmp5 + A[3][4] * tmp6);
	std::complex<double> tmp20(A[3][1] * tmp1 - A[3][4] * tmp7 + A[3][5] * tmp8);
	std::complex<double> tmp21(A[3][1] * tmp2 - A[3][3] * tmp7 + A[3][5] * tmp9);
	std::complex<double> tmp22(A[3][1] * tmp3 - A[3][3] * tmp8 + A[3][4] * tmp9);
	std::complex<double> tmp23(A[3][1] * tmp4 - A[3][2] * tmp7 + A[3][5] * tmp10);
	std::complex<double> tmp24(A[3][1] * tmp5 - A[3][2] * tmp8 + A[3][4] * tmp10);
	std::complex<double> tmp25(A[3][1] * tmp6 - A[3][2] * tmp9 + A[3][3] * tmp10);
	std::complex<double> tmp26(A[3][0] * tmp1 - A[3][4] * tmp11 + A[3][5] * tmp12);
	std::complex<double> tmp27(A[3][0] * tmp2 - A[3][3] * tmp11 + A[3][5] * tmp13);
	std::complex<double> tmp28(A[3][0] * tmp3 - A[3][3] * tmp12 + A[3][4] * tmp13);
	std::complex<double> tmp29(A[3][0] * tmp4 - A[3][2] * tmp11 + A[3][5] * tmp14);
	std::complex<double> tmp30(A[3][0] * tmp5 - A[3][2] * tmp12 + A[3][4] * tmp14);
	std::complex<double> tmp31(A[3][0] * tmp6 - A[3][2] * tmp13 + A[3][3] * tmp14);
	std::complex<double> tmp32(A[3][0] * tmp7 - A[3][1] * tmp11 + A[3][5] * tmp15);
	std::complex<double> tmp33(A[3][0] * tmp8 - A[3][1] * tmp12 + A[3][4] * tmp15);
	std::complex<double> tmp34(A[3][0] * tmp9 - A[3][1] * tmp13 + A[3][3] * tmp15);
	std::complex<double> tmp35(A[3][0] * tmp10 - A[3][1] * tmp14 + A[3][2] * tmp15);
	std::complex<double> tmp36(A[2][2] * tmp16 - A[2][3] * tmp17 + A[2][4] * tmp18 - A[2][5] * tmp19);
	std::complex<double> tmp37(A[2][1] * tmp16 - A[2][3] * tmp20 + A[2][4] * tmp21 - A[2][5] * tmp22);
	std::complex<double> tmp38(A[2][1] * tmp17 - A[2][2] * tmp20 + A[2][4] * tmp23 - A[2][5] * tmp24);
	std::complex<double> tmp39(A[2][1] * tmp18 - A[2][2] * tmp21 + A[2][3] * tmp23 - A[2][5] * tmp25);
	std::complex<double> tmp40(A[2][1] * tmp19 - A[2][2] * tmp22 + A[2][3] * tmp24 - A[2][4] * tmp25);
	std::complex<double> tmp41(A[2][0] * tmp16 - A[2][3] * tmp26 + A[2][4] * tmp27 - A[2][5] * tmp28);
	std::complex<double> tmp42(A[2][0] * tmp17 - A[2][2] * tmp26 + A[2][4] * tmp29 - A[2][5] * tmp30);
	std::complex<double> tmp43(A[2][0] * tmp18 - A[2][2] * tmp27 + A[2][3] * tmp29 - A[2][5] * tmp31);
	std::complex<double> tmp44(A[2][0] * tmp19 - A[2][2] * tmp28 + A[2][3] * tmp30 - A[2][4] * tmp31);
	std::complex<double> b0 = A[1][1] * tmp36 - A[1][2] * tmp37 + A[1][3] * tmp38 - A[1][4] * tmp39 + A[1][5] * tmp40;
	std::complex<double> b1 = -A[1][0] * tmp36 + A[1][2] * tmp41 - A[1][3] * tmp42 + A[1][4] * tmp43 - A[1][5] * tmp44;
	std::complex<double> tmp45(A[2][0] * tmp20 - A[2][1] * tmp26 + A[2][4] * tmp32 - A[2][5] * tmp33);
	std::complex<double> tmp46(A[2][0] * tmp21 - A[2][1] * tmp27 + A[2][3] * tmp32 - A[2][5] * tmp34);
	std::complex<double> tmp47(A[2][0] * tmp22 - A[2][1] * tmp28 + A[2][3] * tmp33 - A[2][4] * tmp34);
	std::complex<double> tmp48(A[2][0] * tmp23 - A[2][1] * tmp29 + A[2][2] * tmp32 - A[2][5] * tmp35);
	std::complex<double> tmp49(A[2][0] * tmp24 - A[2][1] * tmp30 + A[2][2] * tmp33 - A[2][4] * tmp35);
	std::complex<double> b2 = A[1][0] * tmp37 - A[1][1] * tmp41 + A[1][3] * tmp45 - A[1][4] * tmp46 + A[1][5] * tmp47;
	std::complex<double> b3 = -A[1][0] * tmp38 + A[1][1] * tmp42 - A[1][2] * tmp45 + A[1][4] * tmp48 - A[1][5] * tmp49;
	std::complex<double> tmp50(A[2][0] * tmp25 - A[2][1] * tmp31 + A[2][2] * tmp34 - A[2][3] * tmp35);
	std::complex<double> b4 = A[1][0] * tmp39 - A[1][1] * tmp43 + A[1][2] * tmp46 - A[1][3] * tmp48 + A[1][5] * tmp50;
	std::complex<double> b5 = -A[1][0] * tmp40 + A[1][1] * tmp44 - A[1][2] * tmp47 + A[1][3] * tmp49 - A[1][4] * tmp50;
	//det
	return A[0][0] * b0 + A[0][1] * b1 + A[0][2] * b2 +
		A[0][3] * b3 + A[0][4] * b4 + A[0][5] * b5;
}

//std::complex<double> DeterminantCplx_tmp(int order, std::complex<double>**mat)
//{
//	int k;
//	std::complex<double>**submat = Create2dCplx(order, order);
//
//	std::complex<double> d;
//
//	if (order == 2)
//	{
//		return((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
//	}
//
//	for (k = 0; k < order; k++)
//	{
//		GetMinorCplx(mat, submat, 0, k, order);
//		d = d + (pow(-1, k) * mat[0][k] * DeterminantCplx(order - 1, submat));
//	}
//
//	Free2dCplx(submat, order);
//
//	return d;
//}


//void InverseMatrixCplx_tmp(int order, std::complex<double>**mat, std::complex<double>**mat_out)
//{
//	int i, j;
//	std::complex<double>**minor = Create2dCplx(order - 1, order - 1);
//	//std::complex<double>** Inv = Create2dCplx(order, order);
//	std::complex<double> det = 1.0 / DeterminantCplx(order, mat);
//
//	for (j = 0; j < order; j++)
//	{
//		for (i = 0; i < order; i++)
//		{
//			GetMinorCplx(mat, minor, j, i, order);
//			mat_out[i][j] = det*DeterminantCplx(order - 1, minor);
//			if ((i + j) % 2 == 1)
//				mat_out[i][j] = -mat_out[i][j];
//
//		}
//	}
//	//return Inv;
//
//	Free2dCplx(minor, order - 1);
//	//Free2dCplx(Inv, order);
//
//}

//
//void InverseMatrixCplx_tmp(int order, std::complex<double>**mat, std::complex<double>** matout)
//{
//	int i, j;
//	
//	//std::complex<double>** Inv = Create2dCplx(order, order);
//	//std::complex<double> det = 1.0 / DeterminantCplx(order, mat);
//	std::complex<double> det = 1.0 / DeterminantCplx_order_tmp(mat, order);
//	std::complex<double> tmp = 0;
//
//	std::complex<double>**minor = Create2dCplx(order - 1, order - 1);
//
//	//std::complex<double>**minor = Create2dCplx(order - 1, order - 1);
//	
//
//	for (j = 0; j < order; j++)
//	{
//		for (i = 0; i < order; i++)
//		{
//
//			int rowCount = 0, colCount = 0;
//			for (int i_num = 0; i_num < order; i_num++)
//			{
//				if (i_num != j)
//				{
//					colCount = 0;
//					for (int j_num = 0; j_num < order; j_num++)
//					{
//						// when j_num is not the element
//						if (j_num != i)
//						{
//							minor[rowCount][colCount] = mat[i_num][j_num];
//							colCount++;
//						}
//					}
//					rowCount++;
//				}
//			}
//
//			//GetMinorCplx(mat, minor, j, i, order);
//			//matout[i][j] = det*DeterminantCplx(order - 1, minor);
//			tmp = DeterminantCplx_order_tmp(mat, order);
//			//Inv[i][j] = det*DeterminantCplx_order_tmp(minor, order - 1);
//			if ((i + j) % 2 == 1)
//				matout[i][j] = -matout[i][j];
//
//			
//
//		}
//	}
//	//std::cout << "inv" << std::endl;
//	
//	Free2dCplx(minor, order - 1);
//	
//	//Free2dCplx(Inv, order);
//
//}



void InverseMatrixCplx_Gauss(int Nch, std::complex<double>** mat_in, std::complex<double>**mat_out)
{
	int i = 0, j = 0, k = 0, n = 0;
	std::complex<double>**aug_mat = Create2dCplx(2 * Nch, 2 * Nch);
	std::complex<double> d;

	// Initializing Right-hand side to identity matrix
	for (i = 0; i < Nch; ++i)
	{
		for (j = 0; j < 2 * Nch; ++j)
		{
			if (j < Nch)
			{
				aug_mat[i][j] = mat_in[i][j];
			}
			else if (j == (i + Nch))
			{

				aug_mat[i][j] = { 1.0, 0.0 };

			}
			else
			{
				aug_mat[i][j] = { 0.0, 0.0 };
			}
		}
	}


	// Partial pivoting
	for (i = Nch; i > 1; --i)
	{
		if (abs(aug_mat[i - 1][1]) < abs(aug_mat[i][1]))
		{
			for (j = 0; j < 2 * Nch; ++j)
			{
				d = aug_mat[i][j];
				aug_mat[i][j] = aug_mat[i - 1][j];
				aug_mat[i - 1][j] = d;
			}
		}
	}

	// Reducing To Diagonal Matrix
	for (i = 0; i < Nch; ++i)
	{
		for (j = 0; j < 2 * Nch; ++j)
		{
			if (j != i)
			{
				d = aug_mat[j][i] / aug_mat[i][i];
				for (k = 0; k < Nch * 2; ++k)
				{
					aug_mat[j][k] -= aug_mat[i][k] * d;
				}
			}
		}
	}


	// Reducing To Unit Matrix
	for (i = 0; i < Nch; ++i)
	{
		d = aug_mat[i][i];
		for (j = 0; j < 2 * Nch; ++j)
		{
			aug_mat[i][j] = aug_mat[i][j] / d;
		}
	}


	//extract inverse matrix from augmented matrix
	for (i = 0; i < Nch; ++i)
	{
		for (j = Nch; j < 2 * Nch; ++j)
		{
			mat_out[i][j - Nch] = aug_mat[i][j];

		}

	}


	Free2dCplx(aug_mat, 2 * Nch);
}

//std::complex<double>** InverseMatrixCplx(int order, std::complex<double>**mat)
//{
//	int i, j;
//	std::complex<double>**minor = Create2dCplx(order-1, order-1);
//	std::complex<double>** Inv = Create2dCplx(order, order);
//	//std::complex<double> det = 1.0 / DeterminantCplx(order, mat);
//	std::complex<double> det = 1.0 / DeterminantCplx_order_tmp(mat, order);
//	std::complex<double> tmp = 0;
//
//	for (j = 0; j < order; j++)
//	{
//		for (i = 0; i < order; i++)
//		{
//			GetMinorCplx(mat, minor, j, i, order);
//			//Inv[i][j] = det*DeterminantCplx(order - 1, minor);
//			//tmp = DeterminantCplx_order_tmp(mat, order);
//			//Inv[i][j] = det*DeterminantCplx_order_tmp(minor, order - 1);
//			if ((i + j) % 2 == 1)
//				Inv[i][j] = -Inv[i][j];
//
//		}
//	}
//	std::cout << "inv" << std::endl;
//	return Inv;
//
//	Free2dCplx(minor, order-1);
//	Free2dCplx(Inv, order);	
//
//}

void MatmulCplx_ver2(std::complex<double>**mat1, std::complex<double>**mat2, std::complex<double> **MulMat, int row1, int col1, int row2, int col2)
{
	int i, j, k;

	for (i = 0; i < row1; ++i)
	{
		for (j = 0; j < col2; ++j)
		{
			for (k = 0; k < col1; ++k)
			{
				MulMat[i][j] = 0;
			}
		}
	}

	for (i = 0; i < row1; ++i)
	{
		for (j = 0; j < col2; ++j)
		{
			for (k = 0; k < col1; ++k)
			{
				MulMat[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
}




std::complex<double>** MatmulCplx(std::complex<double>**mat1, std::complex<double>**mat2, int row1, int col1, int row2, int col2)
{
	std::complex<double> **MulMat = Create2dCplx(row1, col2);

	int i, j, k;
	for (i = 0; i < row1; ++i)
	{
		for (j = 0; j < col2; ++j)
		{
			for (k = 0; k < col1; ++k)
			{
				MulMat[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}

	return MulMat;
	Free2dCplx(MulMat, row1);
}

std::complex<double> findmax(std::complex<double> **vec, int row, int col)
{
	int i, j;
	double maximum;
	std::complex<double> result;
	result = vec[0][0];
	maximum = std::abs(result);
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++) {
			if (maximum < std::abs(vec[i][j]))
			{
				result = vec[i][j];
				maximum = std::abs(result);
			}
		}
	}

	return result;
}

bool isEqual(std::complex<double>** mat1, std::complex<double>** mat2, int row, int col)
{
	bool result = true;;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (mat1[i][j] == mat2[i][j])
				result = true;
			else
			{
				result = false;
				break;
			}
		}
		if (result == false)
			break;
	}

	return result;
}


double calculateError(std::complex<double>** mat1, std::complex<double>** mat2, int row, int col)
{
	double error = 0.0;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			error += std::abs(mat1[i][j] - mat2[i][j]);
	}
	return error;
}



void EigenSolver(std::complex<double>** mat, int order, std::complex<double>*EigenVector, std::complex<double>&EigenValue) //find maximum eigen value& eigen vector using power method
{
	std::complex<double>** Mattmp = Create2dCplx(order, 1);
	std::complex<double>** result = Create2dCplx(order, 1);
	std::complex<double> EvalueOld = { 0.0, 0.0 };

	int i, j;
	double tol = 0.00000000000001;
	for (i = 0; i < order; i++)
		Mattmp[i][0] = { 1.0, 1.0 };

	while (1)
	{
		EvalueOld = EigenValue;
		result = MatmulCplx(mat, Mattmp, order, order, order, 1);
		EigenValue = findmax(result, order, 1);

		for (i = 0; i < order; i++)
			result[i][0] /= EigenValue;

		if ((calculateError(Mattmp, result, order, 1) <= tol) && (std::abs(EvalueOld - EigenValue) <= tol))//차이 비교: 이상적인 경우 error = 0
			break;

		for (i = 0; i < order; i++)
			Mattmp[i][0] = result[i][0];
	}

	for (i = 0; i < order; i++)
		EigenVector[i] = result[i][0];

	Free2dCplx(Mattmp, order);
	Free2dCplx(result, order);

}

void EigenSolverCplx(std::complex<double>** mat, int order, std::complex<double>*EigenVector, std::complex<double>&EigenValue) //find maximum eigen value& eigen vector using power method
{
	std::complex<double>** A = Create2dCplx(2 * order, 2 * order);
	std::complex<double>** Mattmp = Create2dCplx(2 * order, 1);
	std::complex<double>** result = Create2dCplx(2 * order, 1);
	std::complex<double>** result_cplx = Create2dCplx(order, 1);
	std::complex<double> EvalueOld = { 0.0, 0.0 };

	std::complex<double> evec_max;

	int i, j;
	int maxIter = 30;
	double tol = 0.00000001;
	//double tol = 1.0e-10;
	for (i = 0; i < 2 * order; i++)
	{
		Mattmp[i][0] = { 1.0, 0.0 };

		for (j = 0; j < 2 * order; j++)
		{
			//if (i<order && j < order)			
			//	A[i][j] = real(mat[i][j]);			
			//else if (i<order &&j>=order)			
			//	A[i][j] = -1*std::imag(mat[i][j - order]);			
			//else if (i>=order && j < order)			
			//	A[i][j] = std::imag(mat[i - order][j]);
			//else if (i >= order && j >= order)
			//	A[i][j] = std::real(mat[i - order][j-order]);
			//else
			//	std::cout << "!! Error in Eigensolvertmp !!" << std::endl;		

			if (i < order && j < order)
				A[i][j] = real(mat[i][j]);
			else if (i < order &&j >= order)
				A[i][j] = std::imag(mat[i][j - order]);
			else if (i >= order && j < order)
				A[i][j] = -1 * std::imag(mat[i - order][j]);
			else if (i >= order && j >= order)
				A[i][j] = std::real(mat[i - order][j - order]);
			else
				std::cout << "!! Error in Eigensolvertmp !!" << std::endl;

		}
	}


	//while (1)
	for (j = 0; j < maxIter; j++)
	{
		EvalueOld = EigenValue;
		//result = MatmulCplx(A, Mattmp, 2*order, 2*order, 2*order, 1);

		MatmulCplx_ver2(A, Mattmp, result, 2 * order, 2 * order, 2 * order, 1);

		EigenValue = findmax(result, 2 * order, 1);
		for (i = 0; i < 2 * order; i++)
			result[i][0] /= EigenValue;

		if ((calculateError(Mattmp, result, 2 * order, 1) <= tol) && (std::abs(EvalueOld - EigenValue) <= tol))//차이 비교: 이상적인 경우 error = 0
			break;

		for (i = 0; i < 2 * order; i++)
			Mattmp[i][0] = result[i][0];
	}


	for (i = 0; i < order; i++)
		result_cplx[i][0] = { std::real(result[i][0]), std::real(result[i + order][0]) };

	evec_max = findmax(result_cplx, order, 1);


	for (i = 0; i < order; i++)
	{
		EigenVector[i] = { std::real(result[i][0]), std::real(result[i + order][0]) };
		//EigenVector[i] /= evec_max;   // (20191128) 
	}

	Free2dCplx(A, 2 * order);
	Free2dCplx(Mattmp, 2 * order);
	Free2dCplx(result, 2 * order);
	Free2dCplx(result_cplx, order);
}


//void EigenSolverCplx(std::complex<double>** mat, int order, std::complex<double>*EigenVector, std::complex<double>&EigenValue) //find maximum eigen value& eigen vector using power method
//{
//	std::complex<double>** A = Create2dCplx(2 * order, 2 * order);
//	std::complex<double>** Mattmp = Create2dCplx(2 * order, 1);
//	std::complex<double>** result = Create2dCplx(2 * order, 1);
//	std::complex<double>** result_cplx = Create2dCplx(order, 1);
//	std::complex<double> EvalueOld = { 0.0, 0.0 };
//
//	std::complex<double> evec_max;
//
//	int i, j;
//	double tol = 0.00000001;
//	//double tol = 1.0e-10;
//	for (i = 0; i < 2 * order; i++)
//	{
//		Mattmp[i][0] = { 1.0, 0.0 };
//
//		for (j = 0; j < 2 * order; j++)
//		{
//			//if (i<order && j < order)			
//			//	A[i][j] = real(mat[i][j]);			
//			//else if (i<order &&j>=order)			
//			//	A[i][j] = -1*std::imag(mat[i][j - order]);			
//			//else if (i>=order && j < order)			
//			//	A[i][j] = std::imag(mat[i - order][j]);
//			//else if (i >= order && j >= order)
//			//	A[i][j] = std::real(mat[i - order][j-order]);
//			//else
//			//	std::cout << "!! Error in Eigensolvertmp !!" << std::endl;		
//
//			if (i < order && j < order)
//				A[i][j] = real(mat[i][j]);
//			else if (i < order &&j >= order)
//				A[i][j] = std::imag(mat[i][j - order]);
//			else if (i >= order && j < order)
//				A[i][j] = -1 * std::imag(mat[i - order][j]);
//			else if (i >= order && j >= order)
//				A[i][j] = std::real(mat[i - order][j - order]);
//			else
//				std::cout << "!! Error in Eigensolvertmp !!" << std::endl;
//
//		}
//	}
//
//
//	while (1)
//	{
//		EvalueOld = EigenValue;
//		//result = MatmulCplx(A, Mattmp, 2*order, 2*order, 2*order, 1);
//
//		MatmulCplx_ver2(A, Mattmp, result, 2 * order, 2 * order, 2 * order, 1);
//
//		EigenValue = findmax(result, 2 * order, 1);
//		for (i = 0; i < 2 * order; i++)
//			result[i][0] /= EigenValue;
//
//		if ((calculateError(Mattmp, result, 2 * order, 1) <= tol) && (std::abs(EvalueOld - EigenValue) <= tol))//차이 비교: 이상적인 경우 error = 0
//			break;
//
//		for (i = 0; i < 2 * order; i++)
//			Mattmp[i][0] = result[i][0];
//	}
//
//
//	for (i = 0; i < order; i++)
//		result_cplx[i][0] = { std::real(result[i][0]), std::real(result[i + order][0]) };
//
//	evec_max = findmax(result_cplx, order, 1);
//
//
//	for (i = 0; i < order; i++)
//	{
//		EigenVector[i] = { std::real(result[i][0]), std::real(result[i + order][0]) };
//		EigenVector[i] /= evec_max;   // (20191128) 
//	}
//
//	Free2dCplx(A, 2 * order);
//	Free2dCplx(Mattmp, 2 * order);
//	Free2dCplx(result, 2 * order);
//	Free2dCplx(result_cplx, order);
//}