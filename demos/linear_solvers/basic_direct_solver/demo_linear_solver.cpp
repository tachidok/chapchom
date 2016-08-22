#include <iostream>
#include <cmath>

// The class to solve linear systems using numerical recipes
// implementation
#include "../../../src/linear_solvers/cc_lu_solver_numerical_recipes.h"
// The class to represent matrices in CHAPCHOM

// TODO. Do the same example but using the matrix representation of
// chapchom

int main(int argc, char *argv[])
{
 // Create a matrix
 const unsigned nrows = 10;
 
 double **A = new double*[nrows];
 for (unsigned i = 0; i < nrows; i++)
  {
   A[i] = new double[nrows];
  }
 
 double **b = new double*[nrows];
 for (unsigned i = 0; i < nrows; i++)
  {
   b[i] = new double[1];
  }
 
 // Create a linear solver with the matrix A (pass it size)
 //ACLinearSolver *linear_solver_pt = new CCLUSolverNumericalRecipes(A, n, n);
 ACLinearSolver *linear_solver_pt = new CCLUSolverNumericalRecipes();
 
 // Free memory
 for (unsigned i = 0; i < nrows; i++)
  {
   delete A[i];
   delete b[i];
  }
 delete [] A;
 A = 0;
 
 delete [] b;
 b = 0;
 
 delete linear_solver_pt;
 linear_solver_pt = 0;
 
 return 0;
 
}
