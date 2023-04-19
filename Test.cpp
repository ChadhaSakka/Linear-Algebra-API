/* --------------------------------
Chadha SAKKA 
N° 22205770 
M1 CHPS 
POOCS Project
----------------------------------*/

#include "gtest/gtest.h"

#include "HypreExample.cpp"
#include "PETScExample.cpp"
#include "GenericExample.cpp"


TEST(UnitTest, TestRunTest){ 
	HypreExample h{};
	auto res=h.run();
	EXPECT_NEAR(res.residu,res.residu_local,1e-11);
	
	PETScExample p{};
	 res=p.run();
	EXPECT_NEAR(res.residu,res.residu_local,1e-11);
  	
  	GenericExample g{};
  	 res=g.run(GenericExample::SolverType::Hypre);
  	EXPECT_EQ(res.residu,0);
  	
  	 res=g.run(GenericExample::SolverType::PETSc);
  	EXPECT_EQ(res.residu,0);
  	
}

