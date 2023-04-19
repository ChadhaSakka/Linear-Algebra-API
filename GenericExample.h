/* --------------------------------
Chadha SAKKA 
N° 22205770 
M1 CHPS 
POOCS Project
----------------------------------*/

#ifndef GENERICEXAMPLE_H_
#define GENERICEXAMPLE_H_

#include "AlienMock.h"

#include "LocalLinearAlgebra.h"

#include <memory>

class GenericExample{
public:
	enum class SolverType {Hypre,PETSc};
  	LocalLinearAlgebra::ResidualNorms run(SolverType const& solver_type);      //SolverType
    template <typename API>
    void info(){
        API example{};
        example.info();
    }
};

class UniqueAPI {
	public:
        virtual std::unique_ptr<Alien::ILinearAlgebra> createAlgebra()=0;
        virtual std::unique_ptr<Alien::ILinearSolver> createSolver()=0;
        virtual ~UniqueAPI() = default;
  	};

    class HypreAPI : public UniqueAPI{
        public:
            std::unique_ptr<Alien::ILinearAlgebra> createAlgebra() override;
            std::unique_ptr<Alien::ILinearSolver> createSolver() override;
            void info();
    };

    class PETScAPI : public UniqueAPI{
        public:
            std::unique_ptr<Alien::ILinearAlgebra> createAlgebra() override;
            std::unique_ptr<Alien::ILinearSolver> createSolver() override;
            void info();
    };

class SolverFabric {
public:
		static std::unique_ptr<UniqueAPI> create(GenericExample::SolverType const& solver_type);
        
};

#endif
