// IN THIS FILE: Implementation of a concrete class to represent
// matrices. This is the simplest implementation

#include "cc_matrix.h"

// ===================================================================
// Empty constructor
// ===================================================================
CCMatrix::CCMatrix() 
 : ACMatrix()
{
 // Set the pointer to the matrix to NULL
 Matrix_pt = 0;
}

// ===================================================================
// Constructor to create an n X n zero matrix
// ===================================================================
CCMatrix::CCMatrix(const unsigned n)
 : ACMatrix(n)
{ 
 create_zero_matrix();
}

// ===================================================================
// Constructor to create a zero matrix
// ===================================================================
CCMatrix::CCMatrix(const unsigned m, const unsigned n)
 : ACMatrix(m, n)
{  
 create_zero_matrix();
}

// ===================================================================
// Constructor where we pass the data for the matrix of size m X n
// ===================================================================
CCMatrix::CCMatrix(double *matrix_pt,
                   const unsigned m,
                   const unsigned n)
 : ACMatrix(m, n)
{
 // Copy the data from the input vector to the Matrix_pt vector
 set_matrix(matrix_pt, m, n);
}

// ===================================================================
// Empty destructor
// ===================================================================
CCMatrix::~CCMatrix()
{
 // Deallocate memory
 clean_up();
}

// ===================================================================
// Transforms the input vector to a matrix class type (virtual such
// that each derived class has to implement it)
// ===================================================================
void CCMatrix::set_matrix(const double *matrix_pt,
                          const unsigned m,
                          const unsigned n)
{
 // Clean any possible previously allocated memory
 clean_up();
 
 // Set the number of rows and columns
 NRows = m;
 NColumns = n;
 
 // Set the pointer to the matrix to NULL
 Matrix_pt = 0;
 
 // Allocate memory for the matrix
 Matrix_pt = new double[m*n];
 // Copy the matrix (an element by element copy, uff!!)
 std::memcpy(Matrix_pt, matrix_pt, m*n*sizeof(double));
 
 // Mark the matrix as having elements
 Is_empty = false;
 
}

// ===================================================================
// Clean up for any dynamically stored data
// ===================================================================
void CCMatrix::clean_up()
{
 // Check whether the Matrix has elements
 if (!Is_empty)
  {
   // Make the matrix as deleteable
   Delete_matrix = true;
   // Free the memory allocated for the matrix
   free_memory_for_matrix();
  }
 
}

// ===================================================================
// Free allocated memory for matrix
// ===================================================================
void CCMatrix::free_memory_for_matrix()
{
 // Is the matrix allowed for deletion. If this method is called from
 // an external source we need to check whether the matrix has been
 // marked for deletion
 if (Delete_matrix)
  {
   delete Matrix_pt;
   Matrix_pt = 0; 
   
   // Mark the matrix as empty
   Is_empty=true;
   
  } // if (Delete_matrix)
 else
  {
   // Error message
   std::ostringstream error_message;
   error_message << "You are trying to free the memory of a matrix that is\n"
                 << "not marked as deletable" << std::endl;
   throw ChapchomLibError(error_message.str(),
			  CHAPCHOM_CURRENT_FUNCTION,
			  CHAPCHOM_EXCEPTION_LOCATION);
  }
 
}

// Get the specified value from the matrix (read-only)
const double CCMatrix::value(const unsigned i, const unsigned j) const
{
 // TODO: Julio - Implement range check access
 // Return the value at row i and column j
 return Matrix_pt[i*NColumns+j];
}

// ===================================================================
// Set values in the matrix (write version)
// ===================================================================
double &CCMatrix::value(const unsigned i, const unsigned j)
{
 // TODO: Julio - Implement range check access
 // Return the value at row i and column j
 return Matrix_pt[i*NColumns+j];
}

// Output the matrix
void CCMatrix::output()
{
 if (Is_empty)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "The matrix is empty" << std::endl;
   throw ChapchomLibError(error_message.str(),
			  CHAPCHOM_CURRENT_FUNCTION,
			  CHAPCHOM_EXCEPTION_LOCATION);
  }
 else
  {
   for (unsigned i = 0; i < NRows; i++)
    {
     for (unsigned j = 0; j < NColumns; j++)
      {
       std::cout << Matrix_pt[i*NColumns+j] << " ";
      }
     std::cout << std::endl;
    }
  }
 
}

// ===================================================================
// Creates a zero matrix with the given rows and columns
// ===================================================================
void CCMatrix::create_zero_matrix()
{
 // Delete any possible stored matrix
 clean_up();
 
 // Allocate memory for the matrix
 Matrix_pt = new double[NRows*NColumns];
 
 // ... and set the matrix to zero
 std::memset(Matrix_pt, 0, sizeof(double*)*NColumns*NRows);
 
 // Mark the matrix as having elements
 Is_empty = false;
}

