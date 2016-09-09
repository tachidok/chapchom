// IN THIS FILE: Implementation of a concrete class to represent
// matrices. This is the simplest implementation

#include "cc_matrix.h"

namespace chapchom
{

 // ===================================================================
 // Empty constructor
 // ===================================================================
 template<class T>
 CCMatrix<T>::CCMatrix<T>() 
  : ACMatrix<T>()
 {
  // Set the pointer to the matrix to NULL
  Matrix_pt = 0;
 }

 // ===================================================================
 // Constructor to create an n X n zero matrix
 // ===================================================================
 template<class T>
 CCMatrix<T>::CCMatrix<T>(const unsigned long n)
 : ACMatrix<T>(n)
 { 
  create_zero_matrix();
 }
 
 // ===================================================================
 // Constructor to create a zero matrix
 // ===================================================================
 template<class T>
 CCMatrix<T>::CCMatrix<T>(const unsigned long m, const unsigned long n)
  : ACMatrix<T>(m, n)
 {  
  create_zero_matrix();
 }

 // ===================================================================
 // Constructor where we pass the data for the matrix of size m X n
 // ===================================================================
 template<class T>
 CCMatrix<T>::CCMatrix<T>(T *matrix_pt,
                          const unsigned long m,
                          const unsigned long n)
 : ACMatrix<T>(m, n)
 {
  // Copy the data from the input vector to the Matrix_pt vector
  set_matrix(matrix_pt, m, n);
 }
 
 // ===================================================================
 // Copy constructor
 // ===================================================================
 template<class T>
 CCMatrix<T>::CCMatrix<T>(const CCMatrix &copy)
  : ACMatrix<T>(copy.nrows(), copy.ncolumns())
 {
  // Copy the data from the input vector to the Matrix_pt vector
  set_matrix(copy.matrix_pt(), NRows, NColumns);
 }

 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class T>
 CCMatrix<T>::~CCMatrix<T>()
 {
  // Deallocate memory
  clean_up();
 }

 // ===================================================================
 // Assignment operator
 // ===================================================================
 template<class T>
 CCMatrix<T>& CCMatrix<T>::operator=(const CCMatrix<T> &source_matrix)
 {
  // Check whether the dimensions of the matrices are the same
  const unsigned long n_rows_source_matrix = source_matrix.nrows();
  const unsigned long n_columns_source_matrix = source_matrix.ncolumns();
  const unsigned long n_rows = this->NRows;
  const unsigned long n_columns = this->NColumns;
  if (n_rows != n_rows_source_matrix || n_columns != n_columns_source_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the matrices is not the same:\n"
                  << "dim(source_matrix) = (" << n_rows_source_matrix << ", "
                  << n_columns_source_matrix << ")\n"
                  << "dim(this) = (" << n_rows << ", " << n_columns
                  << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
 
  // Copy the matrix (an element by element copy, uff!!)
  std::memcpy(Matrix_pt, source_matrix.matrix_pt(), n_rows*n_columns*sizeof(T));
 
  // Mark the matrix as having elements
  Is_empty = false;
 
  // Return this (de-referenced pointer)
  return *this;
 
 }

 // ===================================================================
 // += operator
 // ===================================================================
 template<class T>
 CCMatrix<T>& CCMatrix<T>::operator+=(const CCMatrix<T> &matrix)
 {
  // Check whether the dimensions of the matrices are the same
  const unsigned long n_rows_input_matrix = matrix.nrows();
  const unsigned long n_columns_input_matrix = matrix.ncolumns();
  const unsigned long n_rows = this->NRows;
  const unsigned long n_columns = this->NColumns;
  if (n_rows != n_rows_input_matrix || n_columns!= n_columns_input_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the matrices is not the same:\n"
                  << "dim(matrix) = (" << n_rows_input_matrix << ", "
                  << n_columns_input_matrix << ")\n"
                  << "dim(this) = (" << n_rows << ", " << n_columns
                  << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  // Call the method to perform the addition
  add_matrix(matrix, *this);
  // Return the solution matrix
  return *this;
 }

 // ===================================================================
 // -= operator
 // ===================================================================
 template<class T>
 CCMatrix<T>& CCMatrix<T>::operator-=(const CCMatrix<T> &matrix)
 {
  // Check whether the dimensions of the matrices are the same
  const unsigned long n_rows_input_matrix = matrix.nrows();
  const unsigned long n_columns_input_matrix = matrix.ncolumns();
  const unsigned long n_rows = this->NRows;
  const unsigned long n_columns = this->NColumns;
  if (n_rows != n_rows_input_matrix || n_columns!= n_columns_input_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the matrices is not the same:\n"
                  << "dim(matrix) = (" << n_rows_input_matrix << ", "
                  << n_columns_input_matrix << ")\n"
                  << "dim(this) = (" << n_rows << ", " << n_columns
                  << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  // Call the method to perform the addition
  substract_matrix(matrix, *this);
  // Return the solution matrix
  return *this; 
 }

 // ===================================================================
 // Add operator
 // ===================================================================
 template<class T>
 CCMatrix<T> CCMatrix<T>::operator+(const CCMatrix<T> &matrix)
 {
  // Check whether the dimensions of the matrices are the same
  const unsigned long n_rows_input_matrix = matrix.nrows();
  const unsigned long n_columns_input_matrix = matrix.ncolumns();
  const unsigned long n_rows = this->NRows;
  const unsigned long n_columns = this->NColumns;
  if (n_rows != n_rows_input_matrix || n_columns!= n_columns_input_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the matrices is not the same:\n"
                  << "dim(matrix) = (" << n_rows_input_matrix << ", "
                  << n_columns_input_matrix << ")\n"
                  << "dim(this) = (" << n_rows << ", " << n_columns
                  << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  // Create a zero matrix where to store the result
  CCMatrix<T> solution(n_rows, n_columns);
  // Call the method to perform the addition
  add_matrix(matrix, solution);
  // Return the solution matrix
  return solution;
 }

 // ===================================================================
 // Substraction operator
 // ===================================================================
 template<class T>
 CCMatrix<T> CCMatrix<T>::operator-(const CCMatrix<T> &matrix)
 {
  // Check whether the dimensions of the matrices are the same
  const unsigned long n_rows_input_matrix = matrix.nrows();
  const unsigned long n_columns_input_matrix = matrix.ncolumns();
  const unsigned long n_rows = this->NRows;
  const unsigned long n_columns = this->NColumns;
  if (n_rows != n_rows_input_matrix || n_columns!= n_columns_input_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the matrices is not the same:\n"
                  << "dim(matrix) = (" << n_rows_input_matrix << ", "
                  << n_columns_input_matrix << ")\n"
                  << "dim(this) = (" << n_rows << ", " << n_columns
                  << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  // Create a zero matrix where to store the result
  CCMatrix<T> solution(n_rows, n_columns);
  // Call the method to perform the addition
  substract_matrix(matrix, solution);
  return solution;
 }

 // ===================================================================
 // Multiplication operator
 // ===================================================================
 template<class T>
 CCMatrix<T> CCMatrix<T>::operator*(const CCMatrix<T> &right_matrix)
 {
  // Check whether the dimensions of the matrices allow for
  // multiplication
  const unsigned long n_rows_right_matrix = right_matrix.nrows();
  const unsigned long n_columns_right_matrix = right_matrix.ncolumns();
  const unsigned long n_rows_left_matrix = this->NRows;
  const unsigned long n_columns_left_matrix = this->NColumns;
  if (n_columns_left_matrix != n_rows_right_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the matrices does not allow "
                  << "multiplication:\n"
                  << "dim(left_matrix) = (" << n_rows_left_matrix << ", "
                  << n_columns_left_matrix << ")\n"
                  << "dim(right_matrix) = (" << n_rows_right_matrix << ", "
                  << n_columns_right_matrix << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
 
  // Create a zero matrix where to store the result
  CCMatrix<T> solution(n_rows_left_matrix, n_columns_right_matrix);
  // Perform the multiplication
  multiply_by_matrix(right_matrix, solution);
  // Return the solution matrix
  return solution;
 }

 // ===================================================================
 // Transforms the input vector to a matrix class type (virtual such
 // that each derived class has to implement it)
 // ===================================================================
 template<class T>
 void CCMatrix<T>::set_matrix(const T *matrix_pt,
                              const unsigned long m,
                              const unsigned long n)
 {
  // Clean any possible previously allocated memory
  clean_up();
 
  // Set the number of rows and columns
  NRows = m;
  NColumns = n;
 
  // Set the pointer to the matrix to NULL
  Matrix_pt = 0;
 
  // Allocate memory for the matrix
  Matrix_pt = new T[m*n];
  // Copy the matrix (an element by element copy, uff!!)
  std::memcpy(Matrix_pt, matrix_pt, m*n*sizeof(T));
  
  // Mark the matrix as having elements
  Is_empty = false;
  
 }
 
 // ===================================================================
 // Clean up for any dynamically stored data
 // ===================================================================
 template<class T>
 void CCMatrix<T>::clean_up()
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
 template<class T>
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

 // ===================================================================
 // Performs sum of matrices
 // ===================================================================
 template<class T>
 void CCMatrix<T>::add_matrix(const CCMatrix<T> &matrix, const CCMatrix<T> &solution_matrix)
 { 
  // Check whether the dimensions of the matrices are the same
  const unsigned long n_rows_input_matrix = matrix.nrows();
  const unsigned long n_columns_input_matrix = matrix.ncolumns();
  const unsigned long n_rows = this->NRows;
  const unsigned long n_columns = this->NColumns;
  if (n_rows != n_rows_input_matrix || n_columns!= n_columns_input_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the matrices is not the same:\n"
                  << "dim(matrix) = (" << n_rows_input_matrix << ", "
                  << n_columns_input_matrix << ")\n"
                  << "dim(this) = (" << n_rows << ", " << n_columns
                  << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
 
  // Get the matrix pointer of the solution matrix
  T *solution_matrix_pt = solution_matrix.matrix_pt();
  // Get the matrix pointer of the input matrix
  T *matrix_pt = matrix.matrix_pt();
  // Perform the addition
  for (unsigned long i = 0; i < n_rows; i++)
   {
    const unsigned long offset = i*n_columns;
    for (unsigned long j = 0; j < n_columns; j++)
     {
      solution_matrix_pt[offset+j] = Matrix_pt[offset+j] + matrix_pt[offset+j];
     }
   }
 
 }

 // ===================================================================
 // Performs substraction of matrices
 // ===================================================================
 template<class T>
 void CCMatrix<T>::substract_matrix(const CCMatrix<T> &matrix, const CCMatrix<T> &solution_matrix)
 {
  // Check whether the dimensions of the matrices are the same
  const unsigned long n_rows_input_matrix = matrix.nrows();
  const unsigned long n_columns_input_matrix = matrix.ncolumns();
  const unsigned long n_rows = this->NRows;
  const unsigned long n_columns = this->NColumns;
  if (n_rows != n_rows_input_matrix || n_columns!= n_columns_input_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the matrices is not the same:\n"
                  << "dim(matrix) = (" << n_rows_input_matrix << ", "
                  << n_columns_input_matrix << ")\n"
                  << "dim(this) = (" << n_rows << ", " << n_columns
                  << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
 
  // Get the matrix pointer of the solution matrix
  T *solution_matrix_pt = solution_matrix.matrix_pt();
  // Get the matrix pointer of the input matrix
  T *matrix_pt = matrix.matrix_pt();
  // Perform the addition
  for (unsigned long i = 0; i < n_rows; i++)
   {
    const unsigned long offset = i*n_columns;
    for (unsigned long j = 0; j < n_columns; j++)
     {
      solution_matrix_pt[offset+j] = Matrix_pt[offset+j] - matrix_pt[offset+j];
     }
   }
 
 }

 // ===================================================================
 // Performs multiplication of matrices
 // ===================================================================
 template<class T>
 void CCMatrix<T>::multiply_by_matrix(const CCMatrix<T> &right_matrix, const CCMatrix<T> &solution_matrix)
 {
  // Check whether the dimensions of the matrices allow for
  // multiplication
  const unsigned long n_rows_right_matrix = right_matrix.nrows();
  const unsigned long n_columns_right_matrix = right_matrix.ncolumns();
  const unsigned long n_rows_left_matrix = this->NRows;
  const unsigned long n_columns_left_matrix = this->NColumns;
  if (n_columns_left_matrix != n_rows_right_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the matrices does not allow "
                  << "multiplication:\n"
                  << "dim(left_matrix) = (" << n_rows_left_matrix << ", "
                  << n_columns_left_matrix << ")\n"
                  << "dim(right_matrix) = (" << n_rows_right_matrix << ", "
                  << n_columns_right_matrix << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
 
  // Get the matrix pointer of the solution matrix
  T *solution_matrix_pt = solution_matrix.matrix_pt();
  // Get the matrix pointer of the right matrix
  T *right_matrix_pt = right_matrix.matrix_pt();
  // Perform the multiplication
  for (unsigned long i = 0; i < n_rows_left_matrix; i++)
   {
    const unsigned offset_right_matrix = i * n_columns_right_matrix;
    const unsigned offset_left_matrix = i * n_columns_left_matrix;
    for (unsigned long j = 0; j < n_columns_right_matrix; j++)
     {
      // Initialise
      solution_matrix_pt[offset_right_matrix+j] = 0;
      for (unsigned long k = 0; k < n_columns_left_matrix; k++)
       {
        solution_matrix_pt[offset_right_matrix+j]+=
         Matrix_pt[offset_left_matrix+k] * right_matrix_pt[k*n_columns_right_matrix+j];
       }
     }
   }
 
 }

 // ===================================================================
 // Computes the transpose and store in the solution matrix
 // ===================================================================
 template<class T>
 void CCMatrix<T>::transpose(const CCMatrix<T> &transpose_matrix)
 {
  // Check whether the dimensions of the matrices allow for transpose
  const unsigned long n_rows_transpose_matrix = transpose_matrix.nrows();
  const unsigned long n_columns_transpose_matrix = transpose_matrix.ncolumns();
  const unsigned long n_rows = this->NRows;
  const unsigned long n_columns = this->NColumns;
  if (n_rows != n_columns_transpose_matrix || n_columns!= n_rows_transpose_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the matrices does not allow for\n"
                  << "transpose operation.\n"
                  << "dims(transpose_matrix) = (" << n_rows_transpose_matrix
                  << ", " << n_columns_transpose_matrix << ")\n"
                  << "dim(this) = (" << n_rows << ", " << n_columns
                  << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
 
  // Get a pointer to the matrix structure of the solution CCMatrix
  T *transposed_matrix_pt = transpose_matrix.matrix_pt();
  for (unsigned i = 0; i < n_rows; i++)
   {
    for (unsigned j = 0; j < n_columns; j++)
     {    
      transposed_matrix_pt[j*n_rows+i] = Matrix_pt[i*n_columns+j];
     }
   }
  // Change the number of rows and columns of tehe matrix
  this->NRows = n_rows_transpose_matrix;
  this->NColumns = n_columns_transpose_matrix;
 }

 // ===================================================================
 // Get the specified value from the matrix (read-only)
 // ===================================================================
 template<class T>
 const T CCMatrix<T>::value(const unsigned long i, const unsigned long j) const
 {
  // TODO: Julio - Implement range check access
  // Return the value at row i and column j
  return Matrix_pt[i*NColumns+j];
 }

 // ===================================================================
 // Set values in the matrix (write version)
 // ===================================================================
 template<class T>
 T &CCMatrix<T>::value(const unsigned long i, const unsigned long j)
 {
  // TODO: Julio - Implement range check access
  // Return the value at row i and column j
  return Matrix_pt[i*NColumns+j];
 }

 // Output the matrix
 template<class T>
 void CCMatrix<T>::output()
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
    for (unsigned long i = 0; i < NRows; i++)
     {
      for (unsigned long j = 0; j < NColumns; j++)
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
 template<class T>
 void CCMatrix<T>::create_zero_matrix()
 {
  // Delete any possible stored matrix
  clean_up();
 
  // Allocate memory for the matrix
  Matrix_pt = new T[NRows*NColumns];
 
  // ... and set the matrix to zero
  std::memset(Matrix_pt, 0, sizeof(T*)*NColumns*NRows);
 
  // Mark the matrix as having elements
  Is_empty = false;
 }
 
}
