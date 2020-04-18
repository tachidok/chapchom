#include "cc_factory_linear_solver.tpl.h"

namespace chapchom
{
 
 // ===================================================================
 // Empty constructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCFactoryLinearSolver<MAT_TYPE,VEC_TYPE>::CCFactoryLinearSolver()
 {
  
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCFactoryLinearSolver<MAT_TYPE,VEC_TYPE>::~CCFactoryLinearSolver()
 { 

 }

 // ===================================================================
 // Returns the specified linear solver
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 ACLinearSolver<MAT_TYPE,VEC_TYPE>* CCFactoryLinearSolver<MAT_TYPE,VEC_TYPE>::
 create_linear_solver(std::string linear_solver_name)
 {
  // Get the string and change it to lower case 
  std::transform(linear_solver_name.begin(), linear_solver_name.end(),
                 linear_solver_name.begin(), ::tolower);
  
  // ------------------------------------------------------
  // Check what linear solver we need to create
  // ------------------------------------------------------
#ifdef CHAPCHOM_USES_ARMADILLO
  // Linear solver from Armadillo
  if (linear_solver_name.compare("armadillo")==0)
   {
    return new CCSolverArmadillo<Real>();
   }
#else
  // LU solver from numerical recipes
  else if (linear_solver_name.compare("numerical_recipes")==0)
   {
    return new CCLUSolverNumericalRecipes<Real>();
   }
#endif
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

