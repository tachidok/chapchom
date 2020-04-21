#include <iostream>
#include <cmath>
#include <fstream>

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"

#include "../../../src/data_structures/cc_data.h"

#include "../../../src/matrices/cc_vector.h"
#include "../../../src/matrices/cc_matrix.h"

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo type matrices in case that the example wants to
// use them
#include "../../../src/matrices/cc_vector_armadillo.h"
#include "../../../src/matrices/cc_matrix_armadillo.h"
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

#include "../../../src/equations/ac_jacobian_and_residual.h"
#include "../../../src/problem/cc_newtons_method.h"

using namespace chapchom;

/// This demo solves the nonlinear problem
/// x^3 = 27
/// using Newton's method

// A concrete class to compute the Jacobian matrix and the residual
// vector for the problem F(x) = x^3 - 27
class CCJacobianAndResidualBasic : virtual public ACJacobianAndResidual
{
 
public:
 
 // Constructor (empty)
 CCJacobianAndResidualBasic()
  : ACJacobianAndResidual()
 { }
 
 // Destructor (empty)
 ~CCJacobianAndResidualBasic() { }
 
 // In charge of computing the Jacobian
 // (virtual function implementation)
 void compute_jacobian()
 {
  Real x = x_value();
  this->Jacobian_pt->allocate_memory(1,1);
  (*this->Jacobian_pt)(0,0) = 3.0*(x*x); // The derivative of F(x)=x^3-27 w.r.t. x
 }
 
 // In charge of computing the residual
 // (virtual function implementation)
 void compute_residual()
 {
  Real x = x_value();
  this->Residual_pt->allocate_memory(1);
  (*this->Residual_pt)(0) = -((x*x*x) - 27.0); // -F(x)
 }
 
 inline void set_x_pt(ACVector<Real> *x_pt) {X_pt = x_pt;}
 
private:
 
 // Copy constructor (we do not want this class to be copiable because
 // it contains dynamically allocated variables, A in this
 // case). Check
 // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCJacobianAndResidualBasic(const CCJacobianAndResidualBasic &copy)
 {
  BrokenCopy::broken_copy("CCJacobianAndResidualBasic");
 }
 
 // Copy constructor (we do not want this class to be copiable because
 // it contains dynamically allocated variables, A in this
 // case). Check
 // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 void operator=(const CCJacobianAndResidualBasic &copy)
 {
  BrokenCopy::broken_assign("CCJacobianAndResidualBasic");
 }
 
 // Access function for X
 inline Real x_value(){return X_pt->value(0);}
 
 // A pointer to the vector where the values are stored
 ACVector<Real> *X_pt;
 
};

// ==================================================================
// ==================================================================
// ==================================================================
// Main function
// ==================================================================
// ==================================================================
// ==================================================================
int main(int argc, char *argv[])
{
 // Initialise chapcom
 initialise_chapchom();
   
 // Output for testing/validation
 std::ofstream output_test("output_test.dat", std::ios_base::out);
   
 // Create an instance of Newton's method
 CCNewtonsMethod newtons_method;
 
 // Create the Jacobian and residual strategy for the problem to solve
 CCJacobianAndResidualBasic jacobian_and_residual;
 
 // Set Jacobian strategy for Newton's method
 newtons_method.set_jacobian_and_residual_strategy(&jacobian_and_residual);
 
 // Number of dofs
 const unsigned n_dof = 1;
 // Initial guess
 const Real initial_guess = 5.0;
 
 // Create a vector with the initial guess
#ifdef CHAPCHOM_USES_ARMADILLO
 CCVectorArmadillo<Real> x(n_dof);
#else 
 CCVector<Real> x(n_dof);
#endif
 //x.allocate_memory();
 x(0) = initial_guess;
 
 // Set initial dofs in Jacobian and residual strategy
 jacobian_and_residual.set_x_pt(&x);
 
 // Change maximum allowed residual
 newtons_method.set_maximum_allowed_residual(100.0);
 
 // Solver using Newton's method
 newtons_method.solve(&x);
 
 // Print result
 x.print();
 x.print(output_test);
 
 // Close the output for test
 output_test.close();
 
 std::cout << "[FINISHING UP] ... " << std::endl;
 
 // Finalise chapcom
 finalise_chapchom();
 
 return 0;
 
}
