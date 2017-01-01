#include <iostream>
#include <cmath>

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"

// The class to create a matrix
#include "../../../src/matrices/cc_matrix.h"

using namespace chapchom;

int main(int argc, char *argv[])
{
 // Initialise chapcom
 initialise_chapchom();
 
 // Output for testing/validation
 std::ofstream output_test("output_test.dat", std::ios_base::out);
 
 // Get the wall and cpu execution time of the program
 time_t initial_wall_time = Timing::wall_time();
 clock_t initial_cpu_clock_time = Timing::cpu_clock_time();
 
 // Show matrix manipulation for addition, multiplication and
 // transpose
 
 // Size of the matrix (number of rows and columns)
 const unsigned long n_rows = 10;
 const unsigned long n_columns = 10;
 
 // ----------------------------------------------------------
 // Identity matrix
 // ----------------------------------------------------------
 // Instantiate double type matrices.
 CCMatrix<double> I(n_rows, n_columns);
 
 // Create a zero matrix such that memory is allocated to store the
 // entries of the matrix. Otherwise we could not use the I(i,i)
 // assignement without previous memory allocation
 I.create_zero_matrix();
 
 // Feed some data to the matrix (the identity)
 for (unsigned i = 0; i < n_rows; i++)
  {
   I(i,i) = 1;
  }
 
 std::cout << std::endl << "The identity matrix (I)" << std::endl << std::endl;
 I.output();
 I.output(output_test);
 
 // ----------------------------------------------------------
 // Matrix from vector
 // ----------------------------------------------------------
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
       // Get the distance to the diagonal
       matrix_pt[i*n_columns+j] = i;
      }
    }
  }

 // ---------------------------------------
 // Create the matrix from the vector data
 // ---------------------------------------
 CCMatrix<double> B(matrix_pt, n_rows, n_columns);
 CCMatrix<double> B_t;
 B.transpose(B_t);
 
 std::cout << std::endl << "Matrix created from vector" << std::endl << std::endl;
 B.output();
 B.output(output_test);

 std::cout << std::endl << "Matrix transposed" << std::endl << std::endl;
 B_t.print();
 B_t.print(output_test);
 
 // ----------------------------------------------------------
 // Create a matrix where to store results
 // ----------------------------------------------------------
 // Solution matrix
 // Instantiate double type matrices.
 CCMatrix<double> C(n_rows, n_columns);
 
 // Create a zero matrix such that memory is allocated to store the
 // entries of the matrix. Otherwise we could not use the C(i,j)
 // assignement without previous memory allocation
 C.create_zero_matrix(); 
 
 std::cout << std::endl
           << "------------------------------------------------------------------------------"
           << std::endl << "Matrix operations\n"
           << "------------------------------------------------------------------------------"
           << std::endl;
 
 // --------------------------------------
 // Sum of matrices C = I + B
 // --------------------------------------
 for (unsigned i = 0; i < n_rows; i++)
  {
   for (unsigned j = 0; j < n_columns; j++)
    {
     C(i,j) = I(i,j) + B(i,j);
    }
  }
 
 std::cout << std::endl << "The sum of the matrices is:"
           << std::endl << std::endl;
 C.output();
 C.output(output_test);
 
 // --------------------------------------
 // Matrix multiplication C = I * B
 // -------------------------------------- 
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
 C.output(output_test); 
 
 // ##############################################################################
 // Now do the same operations but using operator overloading
 // ##############################################################################
 std::cout << std::endl << ""
           << "##############################################################################\n"
           << "Now do the same operations but using operator overloading\n"
           << "##############################################################################"
           << std::endl;
 // --------------------------------------
 // Sum of matrices C = I + B
 // --------------------------------------
 C = I + B;
 
 std::cout << std::endl << "The sum of the matrices is:"
           << std::endl << std::endl;
 C.output();
 C.output(output_test);
 
 // --------------------------------------
 // Matrix multiplication C = I * B
 // --------------------------------------
 C = I * B;
 
 std::cout << std::endl << "The multiplication of the matrices is:"
           << std::endl << std::endl;
 C.output();
 C.output(output_test);
 
 // -----------------------------------------------------------------------------
 // Create a non square matrix
 // -----------------------------------------------------------------------------
 const unsigned long n_rows_A = 5;
 const unsigned long n_columns_A = 10;
 double *matrix_A_pt = new double[n_rows_A*n_columns_A];
 
 // Add some data to the array
 for (unsigned i = 0; i < n_rows_A; i++)
  {
   for (unsigned j = 0; j < n_columns_A; j++)
    {
     if (i==j)
      {
       matrix_A_pt[i*n_columns_A+j] = i;
      }
     else 
      {
       // Get the distance to the diagonal
       matrix_A_pt[i*n_columns_A+j] = i;
      }
    }
  }
 // Create the non square matrix
 CCMatrix<double> A(matrix_A_pt, n_rows_A, n_columns_A);
 std::cout << std::endl << "Non square matrix"
           << std::endl << std::endl;
 A.output();
 A.output(output_test);
 
 // -----------------------------------------------------------------------------
 // Create a vector to multiply with the non square matrix
 // -----------------------------------------------------------------------------
 const unsigned long n_rows_x = 10;
 const unsigned long n_columns_x = 1;
 double *matrix_x_pt = new double[n_rows_x*n_columns_x];
 
 // Add some data to the array
 for (unsigned i = 0; i < n_rows_x; i++)
  {
   for (unsigned j = 0; j < n_columns_x; j++)
    {
     if (i==j)
      {
       matrix_x_pt[i*n_columns_x+j] = i;
      }
     else 
      {
       // Get the distance to the diagonal
       matrix_x_pt[i*n_columns_x+j] = i;
      }
    }
  }
 
 // Create the vector (matrix)
 CCMatrix<double> x(matrix_x_pt, n_rows_x, n_columns_x);
 std::cout << std::endl << "Vector"
           << std::endl << std::endl;
 x.output();
 x.output(output_test);
 
 // --------------------------------------
 // Matrix multiplication A * x = b
 // --------------------------------------
 CCMatrix<double> b(n_rows_A, n_columns_x); // Note that we do not
                                            // need to force the
                                            // allocation of memory to
                                            // store the entries of
                                            // the matrix b, the
                                            // operation* takes care
                                            // of the allocation in
                                            // case it is required
 b = A * x;
 
 std::cout << std::endl << "The multiplication of the matrices is:"
           << std::endl << std::endl;
 b.output();
 b.output(output_test);
 
 // --------------------------------------------------
 // Apply transpose
 // --------------------------------------------------
 CCMatrix<double> b_t(b.ncolumns(), b.nrows());
 b.transpose(b_t);
 std::cout << std::endl << "The transposed matrix:"
           << std::endl << std::endl;
 b_t.output();
 // Output for test
 b_t.output(output_test);
 
 // Get the wall and cpu execution time of the program
 time_t final_wall_time = Timing::wall_time();
 clock_t final_cpu_clock_time = Timing::cpu_clock_time();
 double total_wall_time =
  Timing::diff_wall_time(initial_wall_time, final_wall_time);
 double total_cpu_clock_time =
  Timing::diff_cpu_clock_time(initial_cpu_clock_time, final_cpu_clock_time);
 
 std::cout << "Total wall time: " << total_wall_time << std::endl;
 std::cout << "Total cpu clock time: " << total_cpu_clock_time << std::endl;
 
 // Close the output for test
 output_test.close();
 
 // Free memory
 delete [] matrix_pt;
 matrix_pt = 0;
 delete [] matrix_A_pt;
 matrix_A_pt = 0;
 delete [] matrix_x_pt;
 matrix_x_pt = 0;
 
 // Finalise chapcom
 finalise_chapchom();
 
 return 0;
 
}
