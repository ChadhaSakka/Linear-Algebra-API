/* --------------------------------
Chadha SAKKA 
N° 22205770 
M1 CHPS 
POOCS Project
----------------------------------*/

#include <iostream>

#include "GenericExample.h"

std::unique_ptr<UniqueAPI> SolverFabric::create(GenericExample::SolverType const& solver_type){
	std::unique_ptr<UniqueAPI> unique_api;
	
		switch(solver_type){
			case GenericExample::SolverType::Hypre:
		       	
				unique_api = std::make_unique<HypreAPI>();
		       		
			case GenericExample::SolverType::PETSc:

				unique_api = std::make_unique<PETScAPI>();		
		}
		
	return unique_api;
}

void HypreAPI::info(){
	std::cout << "****HYPRE info : ****\n\n ***Base Options***\n\n" << std::endl;
}

void PETScAPI::info(){
	std::cout << "****PETSc info : ****\n\n ***Base Options***\n\n" << std::endl;
}

std::unique_ptr<Alien::ILinearAlgebra> HypreAPI::createAlgebra() {
	
	std::unique_ptr<Alien::ILinearAlgebra> algebra = std::make_unique<Alien::Hypre::LinearAlgebra>();
	return algebra;
}

std::unique_ptr<Alien::ILinearSolver> HypreAPI::createSolver() {
	
	std::unique_ptr<Alien::ILinearSolver> solver = std::make_unique<Alien::Hypre::LinearSolver>();
	return solver;
}

std::unique_ptr<Alien::ILinearAlgebra> PETScAPI::createAlgebra() {
	
	std::unique_ptr<Alien::ILinearAlgebra> algebra = std::make_unique<Alien::SimpleCSRLinearAlgebra>();
	return algebra;
}

std::unique_ptr<Alien::ILinearSolver> PETScAPI::createSolver() {
	
	Alien::PETSc::Options options;
	options.numIterationsMax(100);
	options.stopCriteriaValue(1e-10);
	options.preconditioner(Alien::PETSc::OptionTypes::Jacobi);
	options.solver(Alien::PETSc::OptionTypes::BiCGstab /*CG*/);
	
	std::unique_ptr<Alien::ILinearSolver> solver = std::make_unique<Alien::PETSc::LinearSolver>(options);
	return solver;
}
	
LocalLinearAlgebra::ResidualNorms GenericExample::run(GenericExample::SolverType const& solver_type){

	
  auto* pm = Arccore::MessagePassing::Mpi::StandaloneMpiMessagePassingMng::create(MPI_COMM_WORLD);
  auto* tm = Arccore::arccoreCreateDefaultTraceMng();

  Alien::setTraceMng(tm);
  Alien::setVerbosityLevel(Alien::Verbosity::Debug);

  auto size = 100;

  tm->info() << "Example Alien Generic  :";
  tm->info() << "Use of scalar builder (RefSemantic API) for Laplacian problem";
  tm->info() << " => solving linear system Ax = b";
  tm->info() << " * problem size = " << size;
  tm->info() << " ";
  tm->info() << "Start example...";
  tm->info() << " ";
  
  Alien::Matrix A(size, size, pm);

  // Distributions calculée
  const auto& dist = A.distribution();
  int offset = dist.rowOffset();
  int lsize = dist.localRowSize();
  int gsize = dist.globalRowSize();

  tm->info() << "offset: " << offset;

  tm->info() << "build matrix with direct matrix builder";
  {
    Alien::DirectMatrixBuilder builder(A, Alien::DirectMatrixOptions::eResetValues);
    builder.reserve(3); // Réservation de 3 coefficients par ligne
    builder.allocate(); // Allocation de l'espace mémoire réservé

    for (int irow = offset; irow < offset + lsize; ++irow) {
      builder(irow, irow) = 2.;
      if (irow - 1 >= 0){
        builder(irow, irow - 1) = -1.;
        }
      if (irow + 1 < gsize){
        builder(irow, irow + 1) = -1.;
        }
    }
  }

  tm->info() << "* xe = 1";

  Alien::Vector xe = Alien::ones(size, pm);

  tm->info() << "=> Vector Distribution : " << xe.distribution();

  tm->info() << "* b = A * xe";

  Alien::Vector b(size, pm);
  
  auto unique_api = SolverFabric::create(solver_type);
  
  //Alien::SimpleCSRLinearAlgebra algebra;
  auto algebra = unique_api->createAlgebra();

  algebra->mult(A, xe, b);

  Alien::Vector x(size, pm);

  tm->info() << "* x = A^-1 b";

  Alien::PETSc::Options options;
  options.numIterationsMax(100);
  options.stopCriteriaValue(1e-10);
  options.preconditioner(Alien::PETSc::OptionTypes::Jacobi);
  options.solver(Alien::PETSc::OptionTypes::BiCGstab /*CG*/);
  
  //auto solver = Alien::PETSc::LinearSolver(options);
  auto solver = unique_api->createSolver();

  solver->solve(A, b, x);

  tm->info() << "* r = Ax - b";

  Alien::Vector r(size, pm);

  {
    Alien::Vector tmp(size, pm);
    tm->info() << "t = Ax";
    algebra->mult(A, x, tmp);
    tm->info() << "r = t";
    algebra->copy(tmp, r);
    tm->info() << "r -= b";
    algebra->axpy(-1., b, r);
  }

  auto norm = algebra->norm2(r);

  tm->info() << " => ||r|| = " << norm;

  tm->info() << "* r = || x - xe ||";

  {
    tm->info() << "r = x";
    algebra->copy(x, r);
    tm->info() << "r -= xe";
    algebra->axpy(-1., xe, r);
  }

  tm->info() << " => ||r|| = " << norm;

  tm->info() << " ";
  tm->info() << "... example with Alien finished !!!";
  
  
  LocalLinearAlgebra::ResidualNorms res{};
  res.residu = norm; 
  return res;
	
}


