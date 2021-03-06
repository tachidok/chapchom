/// IN THIS FILE: A factory to help us on the creation of linear
/// solvers

#ifndef CCFACTORYLINEARSOLVER_H
#define CCFACTORYLINEARSOLVER_H

// Include the linear solver
#include "ac_linear_solver.h"
#include "cc_lu_solver_numerical_recipes.h"
#ifdef SCICELLXX_USES_ARMADILLO
#include "cc_solver_armadillo.h"
#endif // #ifdef SCICELLXX_USES_ARMADILO

namespace scicellxx
{
 
 /// @class CCFactoryLinearSolver cc_factory_linear_solver.h
 
 /// This class implements a factory for the linear solvers
 class CCFactoryLinearSolver
 {
  
 public:
  
  
  /// Empty constructor
  CCFactoryLinearSolver();
  
  /// Empty destructor
  virtual ~CCFactoryLinearSolver();
  
  /// Returns the corresponding linear solver based on compilation
  /// options
  ACLinearSolver* create_linear_solver();
  
  /// Returns the specified linear solver
  ACLinearSolver* create_linear_solver(std::string linear_solver_name);
  
 protected:
  
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  CCFactoryLinearSolver(const CCFactoryLinearSolver &copy)
   {
    BrokenCopy::broken_copy("CCFactoryLinearSolver");
   }
  
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCFactoryLinearSolver &copy)
   {
    BrokenCopy::broken_assign("CCFactoryLinearSolver");
   }
  
 };
 
}

#endif // #ifndef CCFACTORYLINEARSOLVER_H
