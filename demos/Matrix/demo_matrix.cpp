#include <iostream>
#include <cmath>

// The class to create a matrix
#include "../../src/Matrix/CCMatrix.h"

int main(int argc, char *argv[])
{
 // Show matrix manipulation for addition, multiplication and
 // transpose
 
 // Size of the matrix (number of rowns and columns)
 const unsigned n_rows = 10;
 const unsigned n_columns = 10;
 
 CAMatrix *I_pt = new CCMatrix(n_rows, n_columns);
 
 // Feed some data to the matrix (the identity)
 for (unsigned i = 0; i < n_rows; i++)
  {
   (*I_pt)(i,i) = 1;
  }
 
 std::cout << std::endl << "The identity matrix (I)" << std::endl << std::endl;
 I_pt->output();
 
 // Create an array to initialise another matrix with it
 double **matrix_pt = new double*[n_rows];
 for (unsigned i = 0; i < n_rows; i++)
  {
   matrix_pt[i] = new double[n_columns];
  }
 
 // Add some data to the array
 for (unsigned i = 0; i < n_rows; i++)
  {
   for (unsigned j = 0; j < n_columns; j++)
    {
     if (i==j)
      {
       matrix_pt[i][j] = i;
      }
     else 
      {
       matrix_pt[i][j] = j;
      }
    }
  }
 
 // Now create a new CCMatrix object using the A matrix
 CAMatrix *B_pt = new CCMatrix(matrix_pt, n_rows, n_columns);
 
 std::cout << std::endl << "Another matrix" << std::endl << std::endl;
 B_pt->output();
 
 // Result matrix
 CAMatrix *result_pt = new CCMatrix(n_rows, n_columns);
 
 // Add up the matrices (Identity and B_pt)
 for (unsigned i = 0; i < n_rows; i++)
  {
   for (unsigned j = 0; j < n_columns; j++)
    {
     (*result_pt)(i,j) = (*I_pt)(i,j) + (*B_pt)(i,j);
    }
  }
 
 std::cout << std::endl << "The addition of the matrices is:" << std::endl;
 result_pt->output();
 
 // Multiply the matrices
 
 // Zeroe the result matrix
 for (unsigned i = 0; i < n_rows; i++)
  {
   for (unsigned j = 0; j < n_columns; j++)
    {
     (*result_pt)(i,j) = 0;
    }
  }

 for (unsigned i = 0; i < n_rows; i++)
  {
   for (unsigned j = 0; j < n_columns; j++)
    {
     for (unsigned k = 0; k < n_columns; k++)
      {
       (*result_pt)(i,j)+= (*I_pt)(i,k) * (*B_pt)(k,j);
      }
    }
  }
 
 std::cout << std::endl << "The multiplication of the matrices is:"
           << std::endl;
 result_pt->output();
 
 // Free memory
 delete I_pt;
 I_pt = 0;
 
 delete B_pt;
 B_pt = 0;
 
 for (unsigned i = 0; i < n_rows; i++)
  {
   delete matrix_pt[i];
  }
 delete [] matrix_pt;
 matrix_pt = 0;
 
 return 0;
 
}
