/* --------------------------------
Chadha SAKKA 
N° 22205770 
M1 CHPS 
POOCS Project
----------------------------------*/

#include <iostream>
#include "HypreExample.h"
#include "LocalLinearAlgebra.h"
#include "AlienMock.h"

LocalLinearAlgebra::ResidualNorms HypreExample::run(){

  auto* pm = Arccore::MessagePassing::Mpi::StandaloneMpiMessagePassingMng::create(MPI_COMM_WORLD);
  auto* tm = Arccore::arccoreCreateDefaultTraceMng();

  Alien::setTraceMng(tm);
  Alien::setVerbosityLevel(Alien::Verbosity::Debug);

  auto size = 100;

  tm->info() << "Example Alien :";
  tm->info() << "Use of scalar builder (RefSemantic API) for Laplacian problem";
  tm->info() << " => solving linear system Ax = b";
  tm->info() << " * problem size = " << size;
  tm->info() << " ";
  tm->info() << "Start example...";
  tm->info() << " ";
  //local
  LocalLinearAlgebra::Matrix A_local(size,size,0);
  //Alien
  Alien::Matrix A(size, size, pm);

  // Distributions calculée
  const auto& dist = A.distribution();
  int offset = dist.rowOffset();
  int lsize = dist.localRowSize();
  int gsize = dist.globalRowSize();

  tm->info() << "build matrix with direct matrix builder";
  {
    Alien::DirectMatrixBuilder builder(A, Alien::DirectMatrixOptions::eResetValues);
    builder.reserve(3); // Réservation de 3 coefficients par ligne
    builder.allocate(); // Allocation de l'espace mémoire réservé

    for (int irow = offset; irow < offset + lsize; ++irow) {
      builder(irow, irow) = 2.;
      //local
      A_local.add_value(irow,irow,2.);
      if (irow - 1 >= 0){
        builder(irow, irow - 1) = -1.;
        //local
        A_local.add_value(irow,irow - 1,-1.);
       }
      if (irow + 1 < gsize){
        builder(irow, irow + 1) = -1.;
        //local
        A_local.add_value(irow,irow + 1,-1.);
        }
    }
  }

  tm->info() << "* xe = 1";

  Alien::Vector xe = Alien::ones(size, pm);

  tm->info() << "=> Vector Distribution : " << xe.distribution();

  tm->info() << "* b = A * xe";

  Alien::Vector b(size, pm);

  Alien::Hypre::LinearAlgebra algebra;

  algebra.mult(A, xe, b);

  Alien::Vector x(size, pm);

  tm->info() << "* x = A^-1 b";

  //  auto options = Alien::Hypre::Options()
  //          .numIterationsMax(100)
  //          .stopCriteriaValue(1e-10)
  //          .preconditioner(Alien::Hypre::OptionTypes::AMGPC)
  //          .solver(Alien::Hypre::OptionTypes::GMRES);
  //
  //  auto solver = Alien::Hypre::LinearSolver (options);

  auto solver = Alien::Hypre::LinearSolver();

  solver.solve(A, b, x);

  tm->info() << "* r = Ax - b";

  Alien::Vector r(size, pm);

  {
    Alien::Vector tmp(size, pm);
    tm->info() << "t = Ax";
    algebra.mult(A, x, tmp);
    tm->info() << "r = t";
    algebra.copy(tmp, r);
    tm->info() << "r -= b";
    algebra.axpy(-1., b, r);
  }

  auto norm = algebra.norm2(r);

  tm->info() << " => ||r|| = " << norm;

  tm->info() << "* r = || x - xe ||";

  {
    tm->info() << "r = x";
    algebra.copy(x, r);
    tm->info() << "r -= xe";
    algebra.axpy(-1., xe, r);
  }

  tm->info() << " => ||r|| = " << norm;

  tm->info() << " ";
  tm->info() << "... example finished !!!";
  
  
/*****************local Linear algebra*********/

 
  
 /* Alien::LocalVectorReader Reader_x(x);
  LocalLinearAlgebra::Vector x_local(Reader_x.size());
   for (int i=0; i<Reader_x.size(); ++i){
  	x_local[i]=Reader_x[i];
  	}
 
  Alien::LocalVectorReader Reader_b(b);
  LocalLinearAlgebra::Vector b_local(Reader_b.size());
  for (int i=0; i<Reader_b.size(); ++i){
  	b_local[i]=Reader_b[i];
  	}
  */
  //algebra.copy(x,x_local)
  //algebra.copy(b,b_local)
   tm->info() << "Example Local Linear Algebra Hypre :";
  LocalLinearAlgebra::Vector x_local(size,1.);
  LocalLinearAlgebra::Vector b_local(size);
  
  LocalLinearAlgebra::Vector tmp_local(size);
  
  LocalLinearAlgebra::mult(A_local, x_local, tmp_local);
  
  LocalLinearAlgebra::Vector r_local(size);
  LocalLinearAlgebra::copy(tmp_local, r_local);
  
  LocalLinearAlgebra::axpy(-1., b_local, r_local);
  
  auto norm_local = LocalLinearAlgebra::norm2(r_local);
  
  LocalLinearAlgebra::ResidualNorms res;
  res.residu = norm;
  res.residu_local = norm_local;  
   tm->info() << "Example Local Hypre finished";
  return res;
}


