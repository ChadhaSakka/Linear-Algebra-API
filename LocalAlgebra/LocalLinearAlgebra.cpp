/* --------------------------------
Chadha SAKKA 
N° 22205770 
M1 CHPS 
POOCS Project
----------------------------------*/

#include <iostream>
#include <cmath>
#include "LocalLinearAlgebra.h"

void LocalLinearAlgebra::Matrix::add_value( int row_index, int column_index, double const& x)
{
	matrix[rows * row_index + column_index] += x;
}

// "r_local = tmp";
void LocalLinearAlgebra::copy(LocalLinearAlgebra::Vector const& tmp, LocalLinearAlgebra::Vector& r) 
{
	auto tmp_size=tmp.size();
	
	for( int i=0; i< tmp_size; ++i )
	{
		r[i]=tmp[i];
	}
}

// "t = A_local*x_local";

void LocalLinearAlgebra::mult(LocalLinearAlgebra::Matrix const& A, LocalLinearAlgebra::Vector const& x, LocalLinearAlgebra::Vector& tmp){
	auto r_A = A.rows;
	auto c_A = A.columns;
	for(int i=0; i<r_A; ++i)
	{
		tmp[i]=0;
		for( int j=0; j<c_A; ++j )
		{
			tmp[i] += A.matrix[r_A*i+j]*x[j];
		}
	}
}

// "r_local -= b_local";
void LocalLinearAlgebra::axpy(double a, LocalLinearAlgebra::Vector const& b,LocalLinearAlgebra::Vector& r)
{
	auto b_size=b.size();
	for(int i=0; i<b_size; ++i)
	{
		r[i]+=a*b[i];
	}
}
// norm_local = ||r_local||
double LocalLinearAlgebra::norm2(LocalLinearAlgebra::Vector const& r){
	double norm = 0.0;
	int r_size=r.size();
	for(long unsigned int i=0; i<r_size; ++i)
	{
		norm+=pow(r[i],2);
	}
	norm=sqrt(norm);
	return norm;
}


