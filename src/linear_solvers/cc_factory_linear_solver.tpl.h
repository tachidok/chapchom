#ifndef CCFACTORYLINEARSOLVER_TPL_H
#define CCFACTORYLINEARSOLVER_TPL_H

// Include the linear solver
#include "ac_linear_solver.h"
#include "cc_lu_solver_numerical_recipes.h"
#include "cc_solver_armadillo.h"

namespace chapchom
{

 /// @class CCFactoryLinearSolver cc_factory_linear_solver.h
 
 /// This class implements a factory for the linear solvers
 template<class MAT_TYPE, class VEC_TYPE>
  class CCFactoryLinearSolver
 {
  
 public:
  
  /// Empty constructor
  CCFactoryLinearSolver();
  
  /// Empty destructor
  virtual ~CCFactoryLinearSolver();
  
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

#endif // #ifndef CCFACTORYLINEARSOLVER_TPL_H
