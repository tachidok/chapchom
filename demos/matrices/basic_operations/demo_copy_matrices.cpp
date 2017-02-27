#include <iostream>
#include <cmath>

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"

// The class to create a matrix
#include "../../../src/matrices/cc_matrix.h"

using namespace chapchom;

// -------------------------------------------------------------------
// 1 - Show assignment of data to matrices from arrays and vectors
// 2 - Show COPY contructor matrix
// 3 - Show operations to compute the transpose of matrices
// -------------------------------------------------------------------
int main(int argc, char *argv[])
{
 // Initialise chapcom
 initialise_chapchom();
 
 // Output for testing/validation
 std::ofstream output_test("output_test.dat", std::ios_base::out);
 
 // =============================================================
 // Create matrices from an array and a CCVector
 // =============================================================
 // ------------------------------------------------------------- 
 // Create matrix from array
 // ------------------------------------------------------------- 
 const unsigned n_rows = 5; 
 const unsigned n_columns = 3; 
 // Create the array where the values are stored
 double *matrix_pt = new double[n_rows*n_columns];
 
 // Add some data to the array (represents the distance to the
 // diagonal)
 for (unsigned i = 0; i < n_rows; i++)
  {
   for (unsigned j = 0; j < n_columns; j++)
    {
     if (i==j)
      {
       matrix_pt[i*n_columns+j] = 0;
      }
     else 
      {
       // Get the distance to the diagonal
       matrix_pt[i*n_columns+j] = static_cast<int>(j)-static_cast<int>(i);
      }
    }
  }
 
 // Output array
 std::cout << std::endl << "Array matrix_pt[i]" << std::endl << std::endl;
 for (unsigned i = 0; i < (n_rows * n_columns) - 1; i++)
  {
   std::cout << matrix_pt[i] << " ";
   output_test << matrix_pt[i] << " ";
  }
 std::cout << matrix_pt[(n_rows * n_columns) - 1] << std::endl;
 output_test << matrix_pt[(n_rows * n_columns) - 1] << std::endl;
 
 // Create the matrix from the array data
 CCMatrix<double> A(matrix_pt, n_rows, n_columns);
 std::cout << std::endl << "CCMatrix (A) created from array" << std::endl << std::endl;
 A.output();
 A.output(output_test);
 
 // -------------------------------------------------------------
 // Create a matrix form a CCVector
 // -------------------------------------------------------------  
 // The vector
 CCVector<double> b(n_rows);
 // Create a zero vector such that memory is ALLOCATED to store the
 // entries of the vector. Otherwise we could not use the b(i) = x;
 // assignement without previous memory allocation
 b.create_zero_vector();
 
 // Fill the vector with data
 b(0) = -16.0;
 b(1) = -8.0;
 b(2) = 0.0;
 b(3) = 8.0;
 b(4) = 16.0;
 std::cout << std::endl << "Column CCVector (b)" << std::endl << std::endl;
 b.output();
 b.output(output_test);
 
 // Create a matrix form a vector
 CCMatrix<double> B(b);
 std::cout << std::endl << "CCMatrix (B) created from a CCVector (b)" << std::endl << std::endl;
 B.output();
 B.output(output_test);
 
 // Create a row vector
 bool transposed = true;
 CCVector<double> r(n_columns, transposed);
 // Create a zero vector to allocate memory
 r.create_zero_vector();
 
 // Fill the vector with data
 r(0) = 1.0;
 r(1) = 2.0;
 r(2) = 3.0;
 std::cout << std::endl << "Row CCVector (r)" << std::endl << std::endl;
 bool output_indexes = true;
 r.print(output_indexes);
 r.print(output_test, output_indexes);
 
 // Create matrix from row CCVector
 CCMatrix<double> R(r);
 std::cout << std::endl << "CCMatrix (R) created from row CCVector (r)" << std::endl << std::endl;
 R.output();
 R.output(output_test);
 
 // =============================================================
 // Copy constructor 
 // =============================================================
 std::cout << std::endl << "Copy CCMatrix constructor (from CCMatrix A create CCMatrix C)" << std::endl << std::endl;
 CCMatrix<double> C = A;
 C.output();
 C.output(output_test);
 
 std::cout << std::endl << "Copy CCMatrix constructor (from CCMatrix B create CCMatrix D)" << std::endl << std::endl;
 CCMatrix<double> D = B;
 D.output();
 D.output(output_test);
 
 // =============================================================
 // Transpose operations 
 // =============================================================
 std::cout << std::endl << "========================================" << std::endl;
 std::cout << "Transpose operations" << std::endl;
 std::cout << std::endl << "========================================" << std::endl;
 // Transpose the matrix and print it
 A.transpose();
 std::cout << std::endl<< "Transposed CCMatrix (A)" << std::endl << std::endl;
 A.output();
 A.output(output_test); 
 // Transpose the vector
 CCVector<double> b_t;
 b.transpose(b_t);
 std::cout << std::endl<< "Transposed CCVector (b)" << std::endl << std::endl;
 b_t.output();
 b_t.output(output_test);
 
 // Transpose the matrix but store the result in a new CCMatrix
 CCMatrix<double> B_t;
 B.transpose(B_t);
std::cout << std::endl << "Transposed CCMatrix (B)" << std::endl << std::endl;
 B_t.output();
 B_t.output(output_test);
 
 // Transpose the row vector to generate a column vector
 r.transpose();
 std::cout << std::endl << "Transposed row CCVector (r)" << std::endl << std::endl;
 r.output(output_indexes);
 r.output(output_test, output_indexes);
 
 // Create matrix from column CCVector
 CCMatrix<double> R_t(r);
 std::cout << std::endl << "CCMatrix (R_t) created from transposed row CCVector (r)" << std::endl << std::endl;
 R_t.output();
 R_t.output(output_test);
 
 // Transpose and store in new matrix
 CCMatrix<double> C_t; 
 C.transpose(C_t);
 std::cout << std::endl << "Transposed CCMatrix (C)" << std::endl << std::endl;
 C_t.output();
 C_t.output(output_test);
 
 // Transpose and store in the same CCMatrix
 D.transpose();
 std::cout << std::endl << "Transposed CCMatrix (D)" << std::endl << std::endl;
 D.output();
 D.output(output_test);
 
 // Close the output for test
 output_test.close();
 
 // Free memory
 delete [] matrix_pt;
 matrix_pt = 0;
 
 // Finalise chapcom
 finalise_chapchom();
 
 return 0;
 
}
