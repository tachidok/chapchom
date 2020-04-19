/// IN THIS FILE: The implementation of the factory for the creation
/// of linear solvers

#include "cc_factory_linear_solver.h"

namespace chapchom
{
 
 // ===================================================================
 // Empty constructor
 // ===================================================================
 CCFactoryLinearSolver::CCFactoryLinearSolver()
 {
  
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 CCFactoryLinearSolver::~CCFactoryLinearSolver()
 { 
  
 }
 
 // ===================================================================
 // Returns the specified linear solver
 // ===================================================================
 ACLinearSolver* CCFactoryLinearSolver::create_linear_solver(std::string linear_solver_name)
 {
  // Get the string and change it to lower case 
  std::transform(linear_solver_name.begin(), linear_solver_name.end(),
                 linear_solver_name.begin(), ::tolower);
  
  // ------------------------------------------------------
  // Check what linear solver we need to create
  // ------------------------------------------------------
  // Linear solver from Armadillo
  if (linear_solver_name.compare("armadillo")==0)
   {
    return new CCSolverArmadillo();
   }
  // LU solver from numerical recipes
  else if (linear_solver_name.compare("numerical_recipes")==0)
   {
    return new CCLUSolverNumericalRecipes();
   }
  else
   {
    std::ostringstream error_message;
    error_message << "The linear solver you want to use is not implemented yet.\n"
                  << "Please implement it yourself or select another one\n\n"
                  << "Availables ones\n"
                  << "- LU linear solver from Numerical Recipes (numerical_recipes)\n"
                  << "- Armadillo Linear Solver (armadillo) - only if support for armadiilo library is enabled\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
 }
 
}

