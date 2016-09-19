// IN THIS FILE: Implementation of a concrete class to represent
// vectors. This is the simplest implementation

#include "cc_vector.tpl.h"

namespace chapchom
{

 // ===================================================================
 // Empty constructor
 // ===================================================================
 template<class T>
 CCVector<T>::CCVector() 
  : ACVector<T>()
 {
  // Set the pointer to the vector to NULL
  Vector_pt = 0;
 }
 
 // ===================================================================
 // Constructor to create an n size zero vector
 // ===================================================================
 template<class T>
 CCVector<T>::CCVector(const unsigned long n)
 : ACVector<T>(n)
 {
  create_zero_vector();
 }
 
 // ===================================================================
 // Constructor where we pass the data for the vector of size n
 // ===================================================================
 template<class T>
 CCVector<T>::CCVector(T *vector_pt, const unsigned long n)
 : ACVector<T>(n)
 {
  // Copy the data from the input vector to the Vector_pt vector
  set_vector(vector_pt, n);
 }
 
 // ===================================================================
 // Copy constructor
 // ===================================================================
 template<class T>
 CCVector<T>::CCVector(const CCVector<T> &copy)
  : ACVector<T>(copy.nvalues())
 {
  // Copy the data from the input vector to the Matrix_pt vector
  set_matrix(copy.vector_pt(), this->NValues);
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class T>
 CCVector<T>::~CCVector()
 {
  // Deallocate memory
  clean_up();
 }
 
 // ===================================================================
 // Assignment operator
 // ===================================================================
 template<class T>
 CCVector<T>& CCVector<T>::operator=(const CCVector<T> &source_vector)
 {
  // Get the new dimension of the vector
  const unsigned long n_values_vector = source_vector.nvalues();
  // Clean-up and set values
  set_vector(source_vector.vector_pt(), n_values_vector);
  
  // Return this (de-referenced pointer)
  return *this;
  
 }
 
 HERE HERE HERE HERE HERE
 HERHEHREHREHREHRHERHERHERHEHREHREHRH
 
 // ===================================================================
 // += operator
 // ===================================================================
 template<class T>
 CCVector<T>& CCVector<T>::operator+=(const CCVector<T> &vector)
 {
  // Check whether the dimensions of the vectors are the same
  const unsigned long n_values_input_vector = vector.nvalues();
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
 CCVector<T>& CCVector<T>::operator-=(const CCVector<T> &matrix)
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
 CCVector<T> CCVector<T>::operator+(const CCVector<T> &matrix)
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
  CCVector<T> solution(n_rows, n_columns);
  // Call the method to perform the addition
  add_matrix(matrix, solution);
  // Return the solution matrix
  return solution;
 }

 // ===================================================================
 // Substraction operator
 // ===================================================================
 template<class T>
 CCVector<T> CCVector<T>::operator-(const CCVector<T> &matrix)
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
  CCVector<T> solution(n_rows, n_columns);
  // Call the method to perform the addition
  substract_matrix(matrix, solution);
  return solution;
 }

 // ===================================================================
 // Multiplication operator
 // ===================================================================
 template<class T>
 CCVector<T> CCVector<T>::operator*(const CCVector<T> &right_matrix)
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
  CCVector<T> solution(n_rows_left_matrix, n_columns_right_matrix);
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
 void CCVector<T>::set_matrix(const T *matrix_pt,
                              const unsigned long m,
                              const unsigned long n)
 {
  // Clean any possible previously allocated memory
  clean_up();
 
  // Set the number of rows and columns
  this->NRows = m;
  this->NColumns = n;
 
  // Set the pointer to the matrix to NULL
  Matrix_pt = 0;
 
  // Allocate memory for the matrix
  Matrix_pt = new T[m*n];
  // Copy the matrix (an element by element copy, uff!!)
  std::memcpy(Matrix_pt, matrix_pt, m*n*sizeof(T));
  
  // Mark the matrix as having elements
  this->Is_empty = false;
  
 }
 
 // ===================================================================
 // Clean up for any dynamically stored data
 // ===================================================================
 template<class T>
 void CCVector<T>::clean_up()
 {
  // Check whether the Vector has elements
  if (!this->Is_empty)
   {
    // Mark the vector as deleteable
    this->Delete_matrix = true;
    // Free the memory allocated for the vector
    free_memory_for_vector();
   }
 
 }

 // ===================================================================
 // Free allocated memory for vector
 // ===================================================================
 template<class T>
 void CCVector<T>::free_memory_for_vector()
 {
  // Is the vector allowed for deletion. If this method is called from
  // an external source we need to check whether the vector has been
  // marked for deletion
  if (this->Delete_vector)
   {
    delete Vector_pt;
    Vector_pt = 0; 
    
    // Mark the vector as empty
    this->Is_empty=true;
    
   } // if (Delete_vector)
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You are trying to free the memory of a vector that is\n"
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
 void CCVector<T>::add_matrix(const CCVector<T> &matrix, const CCVector<T> &solution_matrix)
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
 void CCVector<T>::substract_matrix(const CCVector<T> &matrix, const CCVector<T> &solution_matrix)
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
 void CCVector<T>::multiply_by_matrix(const CCVector<T> &right_matrix, const CCVector<T> &solution_matrix)
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
 void CCVector<T>::transpose(const CCVector<T> &transpose_matrix)
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
 
  // Get a pointer to the matrix structure of the solution CCVector
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
 // Computes the transpose and returns it
 // ===================================================================
 template<class T>
 CCVector<T> CCVector<T>::transpose()
 {
  // Create a matrix where to store the transposed one
  CCVector<T> tranposed_matrix(this->nrows(), this->ncolumns());
  // Perfomr the tranpose operation
  this->transpose(tranposed_matrix);
  // Return a new object with the tranposed matrix
  return tranposed_matrix;
  
 }
 
 // ===================================================================
 // Get the specified value from the matrix (read-only)
 // ===================================================================
 template<class T>
 const T CCVector<T>::value(const unsigned long i, const unsigned long j) const
 {
  // TODO: Julio - Implement range check access
  // Return the value at row i and column j
  return Matrix_pt[i*this->NColumns+j];
 }

 // ===================================================================
 // Set values in the matrix (write version)
 // ===================================================================
 template<class T>
 T &CCVector<T>::value(const unsigned long i, const unsigned long j)
 {
  // TODO: Julio - Implement range check access
  // Return the value at row i and column j
  return Matrix_pt[i*this->NColumns+j];
 }

 // Output the matrix
 template<class T>
 void CCVector<T>::output()
 {
  if (this->Is_empty)
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
    for (unsigned long i = 0; i < this->NRows; i++)
     {
      for (unsigned long j = 0; j < this->NColumns; j++)
       {
        std::cout << Matrix_pt[i*this->NColumns+j] << " ";
       }
      std::cout << std::endl;
     }
   }
 
 }
 
 // Output the matrix
 template<class T>
 void CCVector<T>::output(std::ofstream &outfile)
 {
  if (this->Is_empty)
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
    for (unsigned long i = 0; i < this->NRows; i++)
     {
      for (unsigned long j = 0; j < this->NColumns; j++)
       {
        outfile << Matrix_pt[i*this->NColumns+j] << " ";
       }
      outfile << std::endl;
     }
   }
  
 }
 
 // ===================================================================
 // Creates a zero matrix with the given rows and columns
 // ===================================================================
 template<class T>
 void CCVector<T>::create_zero_matrix()
 {
  // Delete any possible stored matrix
  clean_up();
 
  // Allocate memory for the matrix
  Matrix_pt = new T[this->NRows*this->NColumns];
 
  // ... and set the matrix to zero
  std::memset(Matrix_pt, 0, sizeof(T*)*this->NColumns*this->NRows);
 
  // Mark the matrix as having elements
  this->Is_empty = false;
 }
 
}
