// IN THIS FILE: The definition of the concrete class CCNewtonsMethod
// to apply Newton's methods for the solution of a given problem

// Check whether the class has been already defined
#ifndef CCNEWTONSMETHOD_TPL_H
#define CCNEWTONSMETHOD_TPL_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "../matrices/cc_matrix.h"
// Includes the abstract class for linear solvers
#include "../linear_solvers/ac_linear_solver.h"
#include "../linear_solvers/cc_lu_solver_numerical_recipes.h"

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo type matrices since the templates may include
// Armadillo type matrices
#include "../matrices/cc_matrix_armadillo.h"
// Linear solver using ARMADILLO matrices
#include "../linear_solvers/cc_solver_armadillo.h"
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

// Includes the abstract class for strategies to compute the Jacobian
// and the residual
#include "../equations/ac_jacobian_and_residual.h"

namespace chapchom
{

#ifdef TYPEDEF_REAL_IS_DOUBLE
#define DEFAULT_NEWTON_ABSOLUTE_SOLVER_TOLERANCE 1.0e-8
#define DEFAULT_NEWTON_RELATIVE_SOLVER_TOLERANCE 1.0e-8
#else
#define DEFAULT_NEWTON_ABSOLUTE_SOLVER_TOLERANCE 1.0e-6
#define DEFAULT_NEWTON_RELATIVE_SOLVER_TOLERANCE 1.0e-6
#endif // #ifdef TYPEDEF_REAL_IS_DOUBLE
#define DEFAULT_MAXIMUM_NEWTON_ITERATIONS 10
#define DEFAULT_MAXIMUM_ALLOWED_RESIDUAL 10.0
 
 // A concrete class for solving a given problem by means of Newton's
 // method
 template<class MAT_TYPE, class VEC_TYPE>
  class CCNewtonsMethod
  {
   
  public:
   
   // Constructor
   CCNewtonsMethod();
   
   // Destructor
   ~CCNewtonsMethod();
   
   // Set the Jacobian and residual computation strategy
   void set_jacobian_and_residual_strategy(ACJacobianAndResidual<MAT_TYPE,VEC_TYPE> *jacobian_and_residual_strategy_pt);
   
   // Set the Linear solver
   void set_linear_solver(ACLinearSolver<MAT_TYPE, VEC_TYPE> *linear_solver_pt);
   
   // Gets access to the Jacobian and residual computation strategy
   ACJacobianAndResidual<MAT_TYPE,VEC_TYPE> *jacobian_and_residual_strategy_pt();
   
   // Gets access to the linear solver
   ACLinearSolver<MAT_TYPE, VEC_TYPE> *linear_solver_pt();
   
   // Set the initial guess. You should override this method if you
   // require to copy the initial guess to some other data structures
   virtual void set_initial_guess(VEC_TYPE &x);
   
   // Gets access to the last stored solution vector
   const VEC_TYPE *x_pt();
   
   // Set default Newton's relative solver tolerance
   inline void set_default_newton_absolute_solver_tolerance()
   {Newton_absolute_solver_tolerance = DEFAULT_NEWTON_ABSOLUTE_SOLVER_TOLERANCE;}
   
   // Set default Newton's relative solver tolerance
   inline void set_default_newton_relative_solver_tolerance()
   {Newton_relative_solver_tolerance = DEFAULT_NEWTON_RELATIVE_SOLVER_TOLERANCE;}
   
   // Enable relative newton solver tolerance
   inline void enable_newton_relative_solver_tolerance()
   {set_default_newton_relative_solver_tolerance();}
   
   // Disable relative newton solver tolerance
   inline void disable_newton_relative_solver_tolerance()
   {Newton_relative_solver_tolerance = 0.0;}
   
   // Set Newton's absolute solver tolerance
   void set_newton_absolute_solver_tolerance(const Real new_newton_absolute_solver_tolerance);
   
   // Set Newton's relative solver tolerance
   void set_newton_relative_solver_tolerance(const Real new_newton_relative_solver_tolerance);
   
   // Set the Maximun number of Newton's iterations
   void set_maximum_newton_iterations(const unsigned new_maximum_newton_iterations);
   
   // Set the Maximum allowed residual
   void set_maximum_allowed_residual(const Real new_maximum_allowed_residual);
   
   // Enables output messages for Newton's method
   inline void enable_output_messages() {Output_messages=true;}
   
   // Disables output messages for Newton's method
   inline void disable_output_messages() {Output_messages=false;}
   
   // Clean up, free allocated memory
   void clean_up();
   
   // Sets default configuration
   void default_configuration();
   
   // Applies Newton's method to solve the problem given by the
   // Jacobian and the residual computed by the estalished strategy.
   // The initial guess is already set by previously calling the
   // function set_initial_guess(). The final solution (if any) is
   // stored in the X_pt vector
   void solve();
   
   // Applies Newton's method to solve the problem given by the
   // Jacobian and the residual computed by the estalished strategy.
   // The initial guess is set in the input/ouptut x vector where the
   // final solution (if any) is returned
   void solve(VEC_TYPE &x);
   
  protected:
   
   // A function that may be overloaded to implement actions before
   // initial converngence check
   virtual void actions_before_initial_convergence_check() { }
   
   // A function that may be overloaded to implement actions before
   // Newton's method step
   virtual void actions_before_newton_step() { }
   
   // A function that may be overloaded to implement actions after
   // Newton's method step
   virtual void actions_after_newton_step() { }
   
   // Newton's absolute solver tolerance
   Real Newton_absolute_solver_tolerance;
   
   // Newton's relative solver tolerance
   Real Newton_relative_solver_tolerance;
   
   // Maximun number of Newton's iterations
   unsigned Maximum_newton_iterations;
   
   // Maximum allowed residual
   Real Maximum_allowed_residual;
   
   // Flag to indicate whether the initial guess has been set or not
   bool Initial_guess_has_been_set;
   
   // Flag to indicate whether the Jacobian and residual computation
   // strategy has been set
   bool Jacobian_and_residual_strategy_has_been_set; 
   
   // Flag to indicate whether a linear solver has been set or not
   bool Linear_solver_has_been_set;
   
   // Flag to indicate whether to free the memory allocated to the
   // linear solver
   bool Free_memory_for_linear_solver;
   
   // Flag to indicate whether to reuse the Jacobian matrix during
   // Newton's method
   bool Reuse_jacobian;
   
  private:
   
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   CCNewtonsMethod(const CCNewtonsMethod<MAT_TYPE, VEC_TYPE> &copy)
    {
     BrokenCopy::broken_copy("CCNewtonsMethod");
    }
   
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   void operator=(const CCNewtonsMethod<MAT_TYPE, VEC_TYPE> &copy)
    {
     BrokenCopy::broken_assign("CCNewtonsMethod");
    }
   
   // -----------------------------------------------------------------
   // There varibles are here to enforce use of access routines by
   // derived classes
   // -----------------------------------------------------------------
   
   // A pointer for the strategy to compute the Jacobian and the residual
   ACJacobianAndResidual<MAT_TYPE,VEC_TYPE> *Jacobian_and_residual_strategy_pt;
   
   // A pointer to the linear solver
   ACLinearSolver<MAT_TYPE, VEC_TYPE> *Linear_solver_pt;
   
   // A pointer to provide access to the current solution during
   // newton steps
   VEC_TYPE *X_pt;
   
   // Flag to indicate whether output messages are enabled or disabled
   // (enabled by default)
   bool Output_messages;
   
  };
 
}

#endif // #ifndef CCNEWTONSMETHOD_TPL_H

