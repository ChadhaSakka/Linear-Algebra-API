/* --------------------------------
Chadha SAKKA 
N° 22205770 
M1 CHPS 
POOCS Project
----------------------------------*/

#ifndef LOCALLINEARALGEBRA_H
#define LOCALLINEARALGEBRA_H

#include <iostream>

#include <vector>

namespace LocalLinearAlgebra {

	class Matrix {	
    public:
        	Matrix(int const& r, int const& c, double const& initialisation): rows(r), columns(c)
            {
        	    auto size=r*c;
                matrix.reserve(size);
                for( int i=0; i<size; ++i) 
                {
                    matrix.push_back(initialisation);            
                }
            }

            int rows;
            int columns;

            void add_value(int row_index, int column_index,double const& x);

            std::vector<double> matrix{};
    };
            
    using Vector = std::vector<double>;

	void copy(Vector const& tmp, Vector& r);                     //copier tmp dans r 
  
	void mult(Matrix const& A, Vector const& x,Vector& tmp);      //produit matrice * Vecteur

	void axpy(double a,Vector const& b,Vector& r);               // r= a*b + r

	double norm2(Vector const&r);                               // sqrt(sum(r_i²))
    
    struct ResidualNorms{
        double residu;
        double residu_local;   
    };
};
#endif

