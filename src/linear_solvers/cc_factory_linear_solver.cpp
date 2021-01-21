/// IN THIS FILE: The implementation of the factory for the creation
/// of linear solvers

#include "cc_factory_linear_solver.h"

namespace chapchom
{
 
 // ===================================================================
 /// Empty constructor
 // ===================================================================
 CCFactoryLinearSolver::CCFactoryLinearSolver()
 {
  
 }
 
 // ===================================================================
 /// Empty destructor
 // ===================================================================
 CCFactoryLinearSolver::~CCFactoryLinearSolver()
 { 
  
 }

 // ===================================================================
 /// Returns the corresponding linear solver (based on compilation
 /// options)
 //===================================================================
 ACLinearSolver* CCFactoryLinearSolver::create_linear_solver()
 {
  // ------------------------------------------------------
  // Check what linear solver we need to create
  // ------------------------------------------------------
#ifdef SCICELLXX_USES_ARMADILLO
  return new CCSolverArmadillo();
#else
  return new CCLUSolverNumericalRecipes();
#endif // #ifdef SCICELLXX_USES_ARMADILLO
 }
 
 // ===================================================================
 /// Returns the specified linear solver
 // ===================================================================
 ACLinearSolver* CCFactoryLinearSolver::create_linear_solver(std::string linear_solver_name)
 {
  // Get the string and change it to lower case 
  std::transform(linear_solver_name.begin(), linear_solver_name.end(),
                 linear_solver_name.begin(), ::tolower);
  
  // ------------------------------------------------------
  // Check what linear solver we need to create
  // ------------------------------------------------------
  // LU solver from numerical recipes
  if (linear_solver_name.compare("numerical_recipes")==0)
   {
    return new CCLUSolverNumericalRecipes();
   }
#ifdef SCICELLXX_USES_ARMADILLO
  // Linear solver from Armadillo
  else if (linear_solver_name.compare("armadillo")==0)
   {
    return new CCSolverArmadillo();
   }
#endif // #ifdef SCICELLXX_USES_ARMADILLO
  else
   {
    std::ostringstream error_message;
    error_message << "The linear solver you want to use is not implemented yet.\n"
                  << "Please implement it yourself or select another one\n\n"
                  << "Availables ones\n"
                  << "- LU linear solver from Numerical Recipes (numerical_recipes)\n"
                  << "- Armadillo Linear Solver (armadillo) - only if support for armadiilo library is enabled\n"
                  << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
  
 }
 
}

