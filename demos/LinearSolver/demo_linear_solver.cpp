#include <iostream>
#include <cmath>

// The class to create a solver object
#include "../../src/LinearSolver/CCLUSolverNumericalRecipes.h"

const unsigned my_function(double *A[], unsigned n)
{
 std::cout << std::endl;
 for (unsigned i = 0; i < n; i++)
  {
   for (unsigned j = 0; j < n; j++)
    {
     std::cout << A[i][j] << " ";
    }
   std::cout << std::endl;
  }
 
 return 0;
 
}

const unsigned my_function2(double b[], unsigned n)
{
 std::cout << std::endl;
 for (unsigned i = 0; i < n; i++)
  {
   std::cout << b[i] << " ";
  }
 std::cout << std::endl;
 
 return 0;
 
}

int main(int argc, char *argv[])
{
 // Create a matrix
 const unsigned n = 10;
 double **A = new double*[n];
 for (unsigned i = 0; i < n; i++)
  {
   A[i] = new double[n];
  }
 
 double *b = new double[n];
 for (unsigned i = 0; i < n; i++)
  {
   b[i] = i;
  }
 
 // Create a linear solver with the matrix A (pass it size)
 //CALinearSolver *linear_solver_pt = new CCLUSolverNumericalRecipes(A, n, n);
 CALinearSolver *linear_solver_pt = new CCLUSolverNumericalRecipes();
 
 std::cout << "Starting ..." << std::endl;
 
 //my_function(A, n);
 //my_function2(b, n);
 
 for (unsigned i = 0; i < n; i++)
  {
   delete A[i];
  }
 delete [] A;
 A = 0;
 
 delete [] b;
 b = 0;
 
 // Free memory
 delete linear_solver_pt;
 linear_solver_pt = 0;
 
 return 0;
 
}
