// IN THIS FILE: The definition of the concrete class CCNewtonsMethod
// to apply Newton's methods for the solution of a given problem

// Check whether the class has been already defined
#ifndef CCNEWTONSMETHOD_TPL_H
#define CCNEWTONSMETHOD_TPL_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "../matrices/cc_matrix.h"

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo type matrices since the templates may include
// Armadillo type matrices
#include "../matrices/cc_matrix_armadillo.h"
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

// Includes the abstract class for strategies to compute the Jacobian
// and the residual
#include "../equations/ac_jacobian_and_residual.h"
// Includes the abstract class for linear solvers
#include "../linear_solvers/ac_linear_solver.h"

namespace chapchom
{
 
#define DEFAULT_NEWTON_SOLVER_TOLERANCE 1.0e-8
#define DEFAULT_MAXIMUM_NEWTON_ITERATIONS 10
#define DEFAULT_MAXIMUM_ALLOWED_RESIDUAL 10.0
 
 // A concrete class for solving a given problem by means of Newton's
 // method
 template<class MAT_TYPE, class VEC_TYPE>
  class CCNewtonsMethod
  {
   
  public:
   
   // Empty constructor
   CCNewtonsMethod();
   
   // Empty destructor
   ~CCNewtonsMethod();
   
   // Set the Jacobian and residual computation strategy
   void set_jacobian_and_residual_strategy(ACJacobianAndResidual<MAT_TYPE,VEC_TYPE> *jacobian_and_residual_strategy_pt);
   
   // Set the Linear solver
   void set_linear_solver(ACLinearSolver<MAT_TYPE, VEC_TYPE> *linear_solver_pt);
   
   // Gets access to the Jacobian and residual computation strategy
   ACJacobianAndResidual<MAT_TYPE,VEC_TYPE> *jacobian_and_residual_strategy_pt();
   
   // Gets access to the linear solver
   ACLinearSolver<MAT_TYPE, VEC_TYPE> *linear_solver_pt();
   
   // Gets access to the last stored solution vector
   const VEC_TYPE *x_pt();
   
   // Set the initial guess. You should override this method if you
   // require to copy the initial guess to some other data structures
   virtual void set_initial_guess(VEC_TYPE &x);
   
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
   
   // Set Newton's solver tolerance
   void set_newton_solver_tolerance(const Real new_newton_solver_tolerance);
   
   // Set the Maximun number of Newton's iterations
   void set_maximum_newton_interations(const unsigned new_maximum_newton_iterations);
   
   // Set the Maximum allowed residual
   void set_maximum_allowed_residual(const Real new_maximum_allowed_residual);
   
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
   
   // Newton's solver tolerance
   Real Newton_solver_tolerance;
   
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
   
   // Flag to indicate whether to reuse the Jacobian matrix during Newton's method
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
   
  };
 
}

#endif // #ifndef CCNEWTONSMETHOD_TPL_H

