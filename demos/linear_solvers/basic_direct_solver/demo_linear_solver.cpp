#include <iostream>
#include <cmath>

// The class to create a solver object
#include "../../src/LinearSolver/CCLUSolverNumericalRecipes.h"
#include "../../src/Matrix/CCMatrix.h"

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
