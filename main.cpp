/* --------------------------------
Chadha SAKKA 
N° 22205770 
M1 CHPS 
POOCS Project
----------------------------------*/

#include "AlienMock.h"
#include "MpiMock.h"

#include "GenericExample.h"

#include <iostream>

int main(int argc,char** argv){

  MPI_Init(&argc, &argv);
	//TD2
	
	/*HypreExample hypre{};
	hypre.run();
	PETScExample petsc{};
	petsc.run();*/
	
	
	//TD4
GenericExample generic_example{};	

generic_example.info<HypreAPI>();
generic_example.run(GenericExample::SolverType::Hypre);

std::cout << "\n\n"<< std::endl;

generic_example.info<PETScAPI>();
generic_example.run(GenericExample::SolverType::PETSc);


  MPI_Finalize();

  return 0;

}
