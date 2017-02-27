#include <iostream>
#include <cmath>

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"

// The class to create a matrix
#include "../../../src/matrices/cc_matrix.h"

using namespace chapchom;

// ===================================================================
// Rotate
// ===================================================================
void rotate(double *input_vector,
            double *rotated_vector,
            const double roll, const double pitch, const double yaw,
            bool inverse_rotation = false)
{
 // The number of elements in the input vector is three
 const unsigned DIM = 3;
 
 // Create the rotation matrix
 CCMatrix<double> R(DIM, DIM);
 R.create_zero_matrix();
 
 const double sin_theta_x = sin(roll);
 const double sin_theta_y = sin(pitch);
 const double sin_theta_z = sin(yaw);
 const double cos_theta_x = cos(roll);
 const double cos_theta_y = cos(pitch);
 const double cos_theta_z = cos(yaw);
 
 R(0,0) = cos_theta_y*cos_theta_z;
 R(0,1) = cos_theta_y*sin_theta_z;
 R(0,2) = -sin_theta_y;
 
 R(1,0) = sin_theta_x*sin_theta_y*cos_theta_z - cos_theta_x*sin_theta_z;
 R(1,1) = sin_theta_x*sin_theta_y*sin_theta_z+cos_theta_x*cos_theta_z;
 R(1,2) = sin_theta_x*cos_theta_y;
 
 R(2,0) = cos_theta_x*sin_theta_y*cos_theta_z + sin_theta_x*sin_theta_z;
 R(2,1) = cos_theta_x*sin_theta_y*sin_theta_z-sin_theta_x*cos_theta_z;
 R(2,2) = cos_theta_x*cos_theta_y;

 if (inverse_rotation)
  {
   // Tranpose the matrix to perform inverse rotation
   R.transpose();
  }
 
 // ----------------------------------
 // Perform the actual transformation
 
 // Create a vector to representation and copy there the input data
 CCVector<double> b(input_vector, DIM);
 // A vector for the output (rotated) data
 CCVector<double> r(DIM);
 // Apply rotation
 multiply_matrix_times_vector(R, b, r);
 // Copy back result in output structure
 rotated_vector[0]=r(0);
 rotated_vector[1]=r(1);
 rotated_vector[2]=r(2);
 
}

int main(int argc, char *argv[])
{
 // Initialise chapcom
 initialise_chapchom();
 
 // Output for testing/validation
 std::ofstream output_test("output_test.dat", std::ios_base::out);
 
 {
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
  // Create a vector (using Matrix structure) to multiply with the non
  // square matrix
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
  // the matrix b, the times
  // operation (*) takes
  // care of the allocation
  // if it is required
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
  
  // Free memory
  delete [] matrix_pt;
  matrix_pt = 0;
  delete [] matrix_A_pt;
  matrix_A_pt = 0;
  delete [] matrix_x_pt;
  matrix_x_pt = 0;
  
 }

 {
  // ##############################################################################
  // Matrix vector operations
  // ##############################################################################
  std::cout << std::endl << ""
            << "##############################################################################\n"
            << "Matrix vector operations\n"
            << "##############################################################################"
            << std::endl;
 
  // --------------------------------------------
  // Rotations to test matrix vector operations
  // --------------------------------------------
  const unsigned DIM = 3;
  // The gravity vector
  double gravity[] ={0.0, 0.0, -9.81};
  // The rotated gravity vector
  double rotated_gravity[DIM];
  // Roll, pitch and yaw Euluer angles
  const double roll = M_PI/4.0;
  const double pitch = M_PI/3.0;
  const double yaw = -M_PI/8.0;
  rotate(gravity, rotated_gravity, roll, pitch, yaw);
 
  // Create vectors to output the data
  CCVector<double> g(gravity, DIM);
  g.output();
  g.output(output_test);
  CCVector<double> rg(rotated_gravity, DIM);
  rg.output();
  rg.output(output_test);
  
  // Rotate the vector again to validate matrix vector operations and
  // rotations
  double double_rotated_gravity[DIM];
  rotate(rotated_gravity, double_rotated_gravity, roll, pitch, yaw, true);
  // Create a vector to output the data
  CCVector<double> drg(double_rotated_gravity, DIM);
  drg.output();
  drg.output(output_test);
  
  // Get the difference between the ORIGINAL gravity vector and the
  // DOUBLE rotated gravity
  CCVector<double> diff = g - drg;
  // Get the norm
  const double norm = diff.norm_2();
  output_test << norm << std::endl;
  std::cout << norm << std::endl;
  
 }
 
 // Close the output for test
 output_test.close();
 
 // Finalise chapcom
 finalise_chapchom();
 
 return 0;
 
}
