// IN THIS FILE: Implementation of a concrete class to represent
// matrices. This is the simplest implementation

#include "CCMatrix.h"

// ===================================================================
// Empty constructor
// ===================================================================
CCMatrix::CCMatrix() 
 : CAMatrix()
{
 // Set the pointer to the matrix to NULL
 Matrix_pt = 0;
}

// ===================================================================
// Constructor to create an n X n zero matrix
// ===================================================================
CCMatrix::CCMatrix(const unsigned n)
 : CAMatrix(n)
{ 
 create_zero_matrix();
}

// ===================================================================
// Constructor to create a zero matrix
// ===================================================================
CCMatrix::CCMatrix(const unsigned m, const unsigned n)
 : CAMatrix(m, n)
{  
 create_zero_matrix();
}

// ===================================================================
// Constructor where we pass the data for the matrix of size m X n
// ===================================================================
CCMatrix::CCMatrix(double **_matrix,
                   const unsigned m,
                   const unsigned n)
 : CAMatrix(_matrix, m, n)
{
 // Set the pointer to the matrix to NULL
 Matrix_pt = 0;
 // Allocate memory for the matrix
 Matrix_pt = new double*[NRows];
 for(unsigned i = 0; i < NRows; i++)
  {
   Matrix_pt[i] = new double[NColumns];
  }
 
 // ... and copy the matrix (an element by element copy, uff!!)
 for (unsigned i = 0; i < NRows; i++)
  {
   for (unsigned j = 0; j < NColumns; j++)
    {
     Matrix_pt[i][j] = _matrix[i][j];
    }
  }
 
 // Mark the matrix as having elements
 Is_empty = false;
 
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
// Set the matrix
// ===================================================================
void CCMatrix::set_matrix(const double **_matrix,
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
 Matrix_pt = new double*[NRows];
 for(unsigned i = 0; i < NRows; i++)
  {
   Matrix_pt[i] = new double[NColumns];
  }
 
 // ... and copy the matrix (an element by element copy, uff!!)
 for (unsigned i = 0; i < NRows; i++)
  {
   for (unsigned j = 0; j < NColumns; j++)
    {
     Matrix_pt[i][j] = _matrix[i][j];
    }
  }
 
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
   // Make the matrix deleteable
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
   for(unsigned i = 0; i < NRows; i++)
    {
     delete Matrix_pt[i];
     Matrix_pt[i] = 0;
    }
   delete Matrix_pt;
   Matrix_pt = 0; 
   
   // Mark the matrix as empty
   Is_empty=true;
   
  } // if (Delete_matrix)
 else
  {   
   // TODO Julio: Implement a class to handle runtime errors and call
   // it here!!!
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << "ERROR in CCMatrix::free_memory_for_matrix() - You are trying to free the memory of a matrix that is not deletable by you" << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   throw(1);
  }
 
}

// ===================================================================
// Set values in the matrix
// ===================================================================
void CCMatrix::set_value(const unsigned i,
                         const unsigned j,
                         double value)
{
 // TODO: Julio - Implement range check access
 
 // Set the value in the Matrix at row i, column j
 Matrix_pt[i][j] = value;
}

// ===================================================================
// Get the specified value from the matrix (read-only)
// ===================================================================
double CCMatrix::get_value(const unsigned i, const unsigned j) const
{
 // TODO: Julio - Implement range check access
 
 // Get the value from the Matrix at row i, column j
 return Matrix_pt[i][j];
}

// ===================================================================
// Returns the value from the matrix (read-write version). It can be
// modified outside
// ===================================================================
double &CCMatrix::value(const unsigned i, const unsigned j) const
{
 // TODO: Julio - Implement range check access
 
 // Get the value from the Matrix at row i, column j
 return Matrix_pt[i][j];
}

// Output the matrix
void CCMatrix::output()
{
 if (Is_empty)
  {
   // TODO Julio: Implement a class to handle runtime errors and call
   // it here!!!
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << "ERROR in CCMatrix::output() - The matrix is empty" << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   throw(1);
  }
 else
  {
   for (unsigned i = 0; i < NRows; i++)
    {
     for (unsigned j = 0; j < NColumns; j++)
      {
       std::cout << Matrix_pt[i][j] << " ";
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
 Matrix_pt = new double*[NRows];
 for(unsigned i = 0; i < NRows; i++)
  {
   Matrix_pt[i] = new double[NColumns];
  }
 
 // ... and set the matrix to zero
 for (unsigned i = 0; i < NRows; i++)
  {
   std::memset(Matrix_pt[i], 0, sizeof(double*)*NColumns);
  }
 
 // Mark the matrix as having elements
 Is_empty = false;
}

// ===================================================================
// Copy constructor (we do not want this class to be copiable because
// it contains dynamically allocated variables; the Matrix). Check
// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
// ===================================================================
CCMatrix::CCMatrix(const CCMatrix &copy)
{
 // TODO Julio: Implement a class to handle runtime errors and call
 // it here!!!
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << "ERROR in CCMatrix::CCMatrix() - Copy constructor called" << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 throw(1);
}

// ===================================================================
// Assignment operator (we do not want this class to be copiable
// because it contains dynamically allocated variables; the
// Matrix). Check
// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
// ===================================================================
CCMatrix& CCMatrix::operator=(const CCMatrix &copy)
{
 // TODO Julio: Implement a class to handle runtime errors and call
 // it here!!!
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << "ERROR in CCMatrix::operator=() - Assignment called" << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 throw(1);
}

