#include <iostream>
#include <cmath>

// The class to create a matrix
#include "../../../src/matrices/cc_matrix.h"

int main(int argc, char *argv[])
{
 // Show matrix manipulation for addition, multiplication and
 // transpose
 
 // Size of the matrix (number of rowns and columns)
 const unsigned n_rows = 10;
 const unsigned n_columns = 10;
 
 CCMatrix I(n_rows, n_columns);
 
 // Feed some data to the matrix (the identity)
 for (unsigned i = 0; i < n_rows; i++)
  {
   I(i,i) = 1;
  }
 
 std::cout << std::endl << "The identity matrix (I)" << std::endl << std::endl;
 I.output();
 
 // Create an array to initialise another matrix with it
 double *matrix_pt = new double[n_rows*n_columns];
 
 // Add some data to the array
 for (unsigned i = 0; i < n_rows; i++)
  {
   for (unsigned j = 0; j < n_columns; j++)
    {
     if (i==j)
      {
       matrix_pt[i*n_columns+j] = i;
      }
     else 
      {
       matrix_pt[i*n_columns+j] = j;
      }
    }
  }
 
 // Now create a new CCMatrix object using the A matrix
 CCMatrix B(matrix_pt, n_rows, n_columns);
 
 std::cout << std::endl << "Another matrix" << std::endl << std::endl;
 B.output();
 
 // Result matrix
 CCMatrix C(n_rows, n_columns);
 
 // Add up the matrices (I+B)
 for (unsigned i = 0; i < n_rows; i++)
  {
   for (unsigned j = 0; j < n_columns; j++)
    {
     C(i,j) = I(i,j) + B(i,j);
    }
  }
 
 std::cout << std::endl << "The addition of the matrices is:"
           << std::endl << std::endl;
 C.output();
 
 // Multiply the matrices
 
 // Zeroe the result matrix
 for (unsigned i = 0; i < n_rows; i++)
  {
   for (unsigned j = 0; j < n_columns; j++)
    {
     C(i,j) = 0;
    }
  }
 
 for (unsigned i = 0; i < n_rows; i++)
  {
   for (unsigned j = 0; j < n_columns; j++)
    {
     for (unsigned k = 0; k < n_columns; k++)
      {
       C(i,j)+= I(i,k) * B(k,j);
      }
    }
  }
 
 std::cout << std::endl << "The multiplication of the matrices is:"
           << std::endl << std::endl;
 C.output();
 
 // Free memory 
 delete [] matrix_pt;
 matrix_pt = 0;
 
 return 0;
 
}
