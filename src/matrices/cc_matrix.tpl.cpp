// IN THIS FILE: Implementation of a concrete class to represent
// matrices. This is the simplest implementation

#include "cc_matrix.tpl.h"

namespace chapchom
{

 // ===================================================================
 // Empty constructor
 // ===================================================================
 template<class T>
 CCMatrix<T>::CCMatrix() 
  : ACMatrix<T>()
 {
  // Delete any data in memory
  clean_up();
 }

 // ===================================================================
 // Constructor to create an n X n matrix.
 // ===================================================================
 template<class T>
 CCMatrix<T>::CCMatrix(const unsigned long n)
 : ACMatrix<T>(n)
 {
  // Delete any data in memory
  clean_up();
 }
 
 // ===================================================================
 // Constructor to create an m X n matrix.
 // ===================================================================
 template<class T>
 CCMatrix<T>::CCMatrix(const unsigned long m, const unsigned long n)
  : ACMatrix<T>(m, n)
 {
  // Delete any data in memory
  clean_up();
 }
 
 // ===================================================================
 // Constructor where we pass the data for the matrix of size m X n
 // ===================================================================
 template<class T>
 CCMatrix<T>::CCMatrix(T *matrix_pt,
                       const unsigned long m,
                       const unsigned long n)
 : ACMatrix<T>(m, n)
 {
  // Copy the data from the input vector to the Matrix_pt vector
  set_matrix(matrix_pt, m, n);
 }
 
 // ===================================================================
 // Constructor a matrix from a CCVector
 // ===================================================================
 template<class T>
 CCMatrix<T>::CCMatrix(CCVector<T> &vector)
  : ACMatrix<T>()
 {
  // Get the pointer to the vector data
  T *vector_pt = vector.vector_pt();
  // Compute the dimension of the new matrix by checking whether the
  // vector is transposed or not
  unsigned long m = 0;
  unsigned long n = 0;
  if (vector.is_transposed()) // a row vector
   {
    m = 1;
    n = vector.nvalues();
   }
  else // a column vector
   {
    m = vector.nvalues();
    n = 1;
   }
  // Copy the data from the vector to the Matrix_pt vector
  set_matrix(vector_pt, m, n);
 }
 
 // ===================================================================
 // Copy constructor
 // ===================================================================
 template<class T>
 CCMatrix<T>::CCMatrix(const CCMatrix<T> &copy)
  : ACMatrix<T>(copy.nrows(), copy.ncolumns())
 {
  // Copy the data from the copy matrix to the Matrix_pt vector
  set_matrix(copy.matrix_pt(), this->NRows, this->NColumns);
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class T>
 CCMatrix<T>::~CCMatrix()
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
  // Clean-up and set values
  set_matrix(source_matrix.matrix_pt(),
             source_matrix.nrows(),
             source_matrix.ncolumns());
  
  // Return this (de-referenced pointer)
  return *this;
 }
 
 // ===================================================================
 // += operator
 // ===================================================================
 template<class T>
 CCMatrix<T>& CCMatrix<T>::operator+=(const CCMatrix<T> &matrix)
 {
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
  // Call the method to perform the operation
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
  // Create a zero matrix where to store the result
  CCMatrix<T> solution(this->NRows, this->NColumns);
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
  // Create a zero matrix where to store the result
  CCMatrix<T> solution(this->NRows, this->NColumns);
  // Call the method to perform the operation
  substract_matrix(matrix, solution);
  return solution;
 }

 // ===================================================================
 // Multiplication operator
 // ===================================================================
 template<class T>
 CCMatrix<T> CCMatrix<T>::operator*(const CCMatrix<T> &right_matrix)
 { 
  // Create a zero matrix where to store the result
  CCMatrix<T> solution(this->NRows, right_matrix.ncolumns());
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
  this->NRows = m;
  this->NColumns = n;
  
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
 void CCMatrix<T>::clean_up()
 {
  // Check whether the Matrix has elements
  if (!this->Is_empty)
   {
    // Mark the matrix as deleteable
    this->Delete_matrix = true;
    // Free the memory allocated for the matrix
    free_memory_for_matrix();
   }
  else // If empty
   {
    // Set the pointer of the matrix to NULL
    Matrix_pt = 0;
   }
  
 }
 
 // ===================================================================
 // Free allocated memory for matrix
 // ===================================================================
 template<class T>
 void CCMatrix<T>::free_memory_for_matrix()
 {
  // Is the matrix allowed for deletion. If this method is called from
  // an external source we need to check whether the matrix has been
  // marked for deletion
  if (this->Delete_matrix)
   {
    delete [] Matrix_pt;
    Matrix_pt = 0; 
   
    // Mark the matrix as empty
    this->Is_empty=true;
   
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
 void CCMatrix<T>::add_matrix(const CCMatrix<T> &matrix,
                              CCMatrix<T> &solution_matrix)
 {
  // Check that THIS and the other matrix have entries to operate with
  if (this->Is_empty || matrix.is_empty())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the matrices to operate with has no entries\n"
                  << "this->Is_empty = "
                  << this->Is_empty << "\n"
                  << "matrix.is_empty() = "
                  << matrix.is_empty() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the matrices are the same
  const unsigned long n_rows_input_matrix = matrix.nrows();
  const unsigned long n_columns_input_matrix = matrix.ncolumns();
  const unsigned long n_rows = this->NRows;
  const unsigned long n_columns = this->NColumns;
  if (n_rows != n_rows_input_matrix || n_columns != n_columns_input_matrix)
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
  
  // Check whether the dimension of the solution matrix are correct
  const unsigned long n_rows_solution_matrix = solution_matrix.nrows();
  const unsigned long n_columns_solution_matrix = solution_matrix.ncolumns();
  if (n_rows != n_rows_solution_matrix || n_columns != n_columns_solution_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the matrices is not the same:\n"
                  << "dim(this) = (" << n_rows << ", "
                  << n_columns << ")\n"
                  << "dim(solution_matrix) = (" << n_rows_solution_matrix
                  << ", " << n_columns_solution_matrix << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the matrix pointer of the solution matrix
  T *solution_matrix_pt = solution_matrix.matrix_pt();
  
  // Check whether the solution matrix has allocated memory, otherwise
  // allocate it here!!!
  if (solution_matrix.is_empty())
   {
    // Create a zero matrix with the given size to allocate memory
    solution_matrix.create_zero_matrix();
    // Get the new matrix pointer
    solution_matrix_pt = solution_matrix.matrix_pt();
   }
  
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
 void CCMatrix<T>::substract_matrix(const CCMatrix<T> &matrix,
                                    CCMatrix<T> &solution_matrix)
 {
  // Check that THIS and the other matrix have entries to operate with
  if (this->Is_empty || matrix.is_empty())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the matrices to operate with has no entries\n"
                  << "this->Is_empty = "
                  << this->Is_empty << "\n"
                  << "matrix.is_empty() = "
                  << matrix.is_empty() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the matrices are the same
  const unsigned long n_rows_input_matrix = matrix.nrows();
  const unsigned long n_columns_input_matrix = matrix.ncolumns();
  const unsigned long n_rows = this->NRows;
  const unsigned long n_columns = this->NColumns;
  if (n_rows != n_rows_input_matrix || n_columns != n_columns_input_matrix)
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
  
  // Check whether the dimension of the solution matrix are correct
  const unsigned long n_rows_solution_matrix = solution_matrix.nrows();
  const unsigned long n_columns_solution_matrix = solution_matrix.ncolumns();
  if (n_rows != n_rows_solution_matrix || n_columns != n_columns_solution_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the matrices is not the same:\n"
                  << "dim(this) = (" << n_rows << ", "
                  << n_columns << ")\n"
                  << "dim(solution_matrix) = (" << n_rows_solution_matrix
                  << ", " << n_columns_solution_matrix << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the matrix pointer of the solution matrix
  T *solution_matrix_pt = solution_matrix.matrix_pt();
  
  // Check whether the solution matrix has allocated memory, otherwise
  // allocate it here!!!
  if (solution_matrix.is_empty())
   {
    // Create a zero matrix with the given size to allocate memory
    solution_matrix.create_zero_matrix();
    // Get the new matrix pointer
    solution_matrix_pt = solution_matrix.matrix_pt();
   }
  
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
 void CCMatrix<T>::multiply_by_matrix(const CCMatrix<T> &right_matrix,
                                      CCMatrix<T> &solution_matrix)
 {
  // Check that THIS and the right matrix have entries to operate with
  if (this->Is_empty || right_matrix.is_empty())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the matrices to operate with has no entries\n"
                  << "this->Is_empty = "
                  << this->Is_empty << "\n"
                  << "right_matrix.is_empty() = "
                  << right_matrix.is_empty() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
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
  
  // Check whether the dimension of the solution matrix are correct
  const unsigned long n_rows_solution_matrix = solution_matrix.nrows();
  const unsigned long n_columns_solution_matrix = solution_matrix.ncolumns();
  if (n_rows_left_matrix != n_rows_solution_matrix ||
      n_columns_right_matrix != n_columns_solution_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the solution matrix is not appropiate for\n"
                  << "the operation:\n"
                  << "dim(left_matrix) = (" << n_rows_left_matrix << ", "
                  << n_columns_left_matrix << ")\n"
                  << "dim(right_matrix) = (" << n_rows_right_matrix << ", "
                  << n_columns_right_matrix << ")\n"
                  << "dim(solution_matrix) = (" << n_rows_solution_matrix
                  << ", " << n_columns_solution_matrix << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the matrix pointer of the solution matrix
  T *solution_matrix_pt = solution_matrix.matrix_pt();
  
  // Check whether the solution matrix has allocated memory, otherwise
  // allocate it here!!!
  if (solution_matrix.is_empty())
   {
    // Create a zero matrix with the given size to allocate memory
    solution_matrix.create_zero_matrix();
    // Get the new matrix pointer
    solution_matrix_pt = solution_matrix.matrix_pt();
   }
  
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
 void CCMatrix<T>::transpose(CCMatrix<T> &transposed_matrix)
 {
  // Get the number of rows and columns of the matrix
  const unsigned long n_rows = this->NRows;
  const unsigned long n_columns = this->NColumns;
  
  // Create a vector to store the transposed matrix
  T *transposed_matrix_pt = new T[n_rows*n_columns];
  // Copy the data in the transposed matrix
  for (unsigned i = 0; i < n_rows; i++)
   {
    for (unsigned j = 0; j < n_columns; j++)
     {    
      transposed_matrix_pt[j*n_rows+i] = Matrix_pt[i*n_columns+j];
     }
   }
  
  // Copy the transposed matrix pointer to the transpose_matrix matrix
  transposed_matrix.set_matrix(transposed_matrix_pt, n_columns, n_rows);
  
  // Delete the temporary transpose matrix pointer
  delete transposed_matrix_pt;
  
 }
 
 // ===================================================================
 // Computes the transpose and returns it
 // ===================================================================
 template<class T>
 void CCMatrix<T>::transpose()
 {
  // Check that THIS matrix has entries to operate with
  if (this->Is_empty)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "THIS matrix has no entries to operate with\n"
                  << "this->Is_empty = "
                  << this->Is_empty << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Transpose itself
  this->transpose(*this);
 }
 
 // ===================================================================
 // Get the specified value from the matrix (read-only)
 // ===================================================================
 template<class T>
 const T CCMatrix<T>::value(const unsigned long i, const unsigned long j) const
 {
  // TODO: Julio - Implement range check access
  // Return the value at row i and column j
  return Matrix_pt[i*this->NColumns+j];
 }

 // ===================================================================
 // Set values in the matrix (write version)
 // ===================================================================
 template<class T>
 T &CCMatrix<T>::value(const unsigned long i, const unsigned long j)
 {
  // TODO: Julio - Implement range check access
  // Return the value at row i and column j
  return Matrix_pt[i*this->NColumns+j];
 }

 // ===================================================================
 // Output the matrix
 // ===================================================================
 template<class T>
 void CCMatrix<T>::output(bool output_indexes) const
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
    // Check whether we should output the indexes
    if (output_indexes)
     {
      for (unsigned long i = 0; i < this->NRows; i++)
       {
        for (unsigned long j = 0; j < this->NColumns; j++)
         {
          std::cout << "(" << i << ", " << j << "): "
                    << Matrix_pt[i*this->NColumns+j]
                    << std::endl; 
         } // for (j < this->NColumns)
       } // for (i < this->NRows)
     } // if (output_indexes)
    else
     {
      for (unsigned long i = 0; i < this->NRows; i++)
       {
        for (unsigned long j = 0; j < this->NColumns; j++)
         {
          std::cout << Matrix_pt[i*this->NColumns+j] << " ";
         } // for (j < this->NColumns)
        std::cout << std::endl;
       } // for (i < this->NRows)
     } // else if (output_indexes)
    
   }
  
 }

 // ===================================================================
 // Output the matrix
 // ===================================================================
 template<class T>
 void CCMatrix<T>::output(std::ofstream &outfile,
                          bool output_indexes) const
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
    // Check whether we should output the indexes
    if (output_indexes)
     {
      for (unsigned long i = 0; i < this->NRows; i++)
       {
        for (unsigned long j = 0; j < this->NColumns; j++)
         {
          outfile << "(" << i << ", " << j << "): "
                  << Matrix_pt[i*this->NColumns+j]
                  << std::endl; 
         } // for (j < this->NColumns)
       } // for (i < this->NRows)
     } // if (output_indexes)
    else
     {
      for (unsigned long i = 0; i < this->NRows; i++)
       {
        for (unsigned long j = 0; j < this->NColumns; j++)
         {
          outfile << Matrix_pt[i*this->NColumns+j] << " ";
         } // for (j < this->NColumns)
        outfile << std::endl;
       } // for (i < this->NRows)
     } // else if (output_indexes)
    
   }
  
 }
 
 // ===================================================================
 // Creates a zero matrix with the given rows and columns (allocates
 // memory to store entries of the matrix)
 // ===================================================================
 template<class T>
 void CCMatrix<T>::create_zero_matrix()
 {
  // Delete any data in memory
  clean_up();
  
  // Allocate memory for the matrix
  Matrix_pt = new T[this->NRows*this->NColumns];
  
  // Mark the matrix as having something
  this->Is_empty=false;
 }
 
 // ================================================================
 // Extra methods to work with matrices, we do not need them to be
 // friends of the class since all their operations are performed
 // using the class methods
 // ================================================================
 
 // ===================================================================
 // Performs sum of matrices
 // ===================================================================
 template<class T>
 void add_matrices(const CCMatrix<T> &matrix_one,
                   const CCMatrix<T> &matrix_two,
                   CCMatrix<T> &solution_matrix)
 {
  // Check that both matrices have entries to operate with
  if (matrix_one.is_empty() || matrix_two.is_empty())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the matrices to operate with has no entries\n"
                  << "matrix_one.is_empty() = "
                  << matrix_one.is_empty() << "\n"
                  << "matrix_two.is_empty() = "
                  << matrix_two.is_empty() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the matrices are the same
  const unsigned long n_rows_matrix_one = matrix_one.nrows();
  const unsigned long n_columns_matrix_one = matrix_one.ncolumns();
  const unsigned long n_rows_matrix_two = matrix_two.nrows();
  const unsigned long n_columns_matrix_two = matrix_two.ncolumns();
  if (n_rows_matrix_one != n_rows_matrix_two ||
      n_columns_matrix_one != n_columns_matrix_two)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the matrices is not the same:\n"
                  << "dim(matrix_one) = (" << n_rows_matrix_one << ", "
                  << n_columns_matrix_one << ")\n"
                  << "dim(matrix_two) = (" << n_rows_matrix_two << ", "
                  << n_columns_matrix_two
                  << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimension of the solution matrix are correct
  const unsigned long n_rows_solution_matrix = solution_matrix.nrows();
  const unsigned long n_columns_solution_matrix = solution_matrix.ncolumns();
  if (n_rows_matrix_one != n_rows_solution_matrix ||
      n_columns_matrix_one != n_columns_solution_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the matrices is not the same:\n"
                  << "dim(matrix_one) = (" << n_rows_matrix_one << ", "
                  << n_columns_matrix_one << ")\n"
                  << "dim(solution_matrix) = (" << n_rows_solution_matrix
                  << ", " << n_columns_solution_matrix << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the matrix pointer of the solution matrix
  T *solution_matrix_pt = solution_matrix.matrix_pt();
  
  // Check whether the solution matrix has allocated memory, otherwise
  // allocate it here!!!
  if (solution_matrix.is_empty())
   {
    // Create a zero matrix with the given size to allocate memory
    solution_matrix.create_zero_matrix();
    // Get the new matrix pointer
    solution_matrix_pt = solution_matrix.matrix_pt();
   }
  
  // Get the matrix pointer of the input matrices
  T *matrix_one_pt = matrix_one.matrix_pt();
  T *matrix_two_pt = matrix_two.matrix_pt();
  // Perform the addition
  for (unsigned long i = 0; i < n_rows_solution_matrix; i++)
   {
    const unsigned long offset = i*n_columns_solution_matrix;
    for (unsigned long j = 0; j < n_columns_solution_matrix; j++)
     {
      solution_matrix_pt[offset+j] =
       matrix_one_pt[offset+j] + matrix_two_pt[offset+j];
     }
   }
  
 }
 
 // ===================================================================
 // Performs substraction of matrices
 // ===================================================================
 template<class T>
 void substract_matrices(const CCMatrix<T> &matrix_one,
                         const CCMatrix<T> &matrix_two,
                         CCMatrix<T> &solution_matrix)
 {
  // Check that both matrices have entries to operate with
  if (matrix_one.is_empty() || matrix_two.is_empty())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the matrices to operate with has no entries\n"
                  << "matrix_one.is_empty() = "
                  << matrix_one.is_empty() << "\n"
                  << "matrix_two.is_empty() = "
                  << matrix_two.is_empty() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the matrices are the same
  const unsigned long n_rows_matrix_one = matrix_one.nrows();
  const unsigned long n_columns_matrix_one = matrix_one.ncolumns();
  const unsigned long n_rows_matrix_two = matrix_two.nrows();
  const unsigned long n_columns_matrix_two = matrix_two.ncolumns();
  if (n_rows_matrix_one != n_rows_matrix_two ||
      n_columns_matrix_one != n_columns_matrix_two)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the matrices is not the same:\n"
                  << "dim(matrix_one) = (" << n_rows_matrix_one << ", "
                  << n_columns_matrix_one << ")\n"
                  << "dim(matrix_two) = (" << n_rows_matrix_two << ", "
                  << n_columns_matrix_two
                  << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimension of the solution matrix are correct
  const unsigned long n_rows_solution_matrix = solution_matrix.nrows();
  const unsigned long n_columns_solution_matrix = solution_matrix.ncolumns();
  if (n_rows_matrix_one != n_rows_solution_matrix ||
      n_columns_matrix_one != n_columns_solution_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the matrices is not the same:\n"
                  << "dim(matrix_one) = (" << n_rows_matrix_one << ", "
                  << n_columns_matrix_one << ")\n"
                  << "dim(solution_matrix) = (" << n_rows_solution_matrix
                  << ", " << n_columns_solution_matrix << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the matrix pointer of the solution matrix
  T *solution_matrix_pt = solution_matrix.matrix_pt();
  
  // Check whether the solution matrix has allocated memory, otherwise
  // allocate it here!!!
  if (solution_matrix.is_empty())
   {
    // Create a zero matrix with the given size to allocate memory
    solution_matrix.create_zero_matrix();
    // Get the new matrix pointer
    solution_matrix_pt = solution_matrix.matrix_pt();
   }
  
  // Get the matrix pointer of the input matrices
  T *matrix_one_pt = matrix_one.matrix_pt();
  T *matrix_two_pt = matrix_two.matrix_pt();
  // Perform the substraction
  for (unsigned long i = 0; i < n_rows_solution_matrix; i++)
   {
    const unsigned long offset = i*n_columns_solution_matrix;
    for (unsigned long j = 0; j < n_columns_solution_matrix; j++)
     {
      solution_matrix_pt[offset+j] =
       matrix_one_pt[offset+j] - matrix_two_pt[offset+j];
     }
   }
  
 }
 
 // ===================================================================
 // Performs multiplication of matrices
 // ===================================================================
 template<class T>
 void multiply_matrices(const CCMatrix<T> &left_matrix,
                        const CCMatrix<T> &right_matrix,
                        CCMatrix<T> &solution_matrix)
 {
  // Check that both matrices have entries to operate with
  if (left_matrix.is_empty() || right_matrix.is_empty())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the matrices to operate with has no entries\n"
                  << "left_matrix.is_empty() = "
                  << left_matrix.is_empty() << "\n"
                  << "right_matrix.is_empty() = "
                  << right_matrix.is_empty() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the matrices allow for
  // multiplication
  const unsigned long n_rows_left_matrix = left_matrix.nrows();
  const unsigned long n_columns_left_matrix = left_matrix.ncolumns();
  const unsigned long n_rows_right_matrix = right_matrix.nrows();
  const unsigned long n_columns_right_matrix = right_matrix.ncolumns();
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
  
  // Check whether the dimension of the solution matrix are correct
  const unsigned long n_rows_solution_matrix = solution_matrix.nrows();
  const unsigned long n_columns_solution_matrix = solution_matrix.ncolumns();
  if (n_rows_left_matrix != n_rows_solution_matrix ||
      n_columns_right_matrix != n_columns_solution_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the solution matrix is not appropiate for\n"
                  << "the operation:\n"
                  << "dim(left_matrix) = (" << n_rows_left_matrix << ", "
                  << n_columns_left_matrix << ")\n"
                  << "dim(right_matrix) = (" << n_rows_right_matrix << ", "
                  << n_columns_right_matrix << ")\n"
                  << "dim(solution_matrix) = (" << n_rows_solution_matrix
                  << ", " << n_columns_solution_matrix << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the matrix pointer of the solution matrix
  T *solution_matrix_pt = solution_matrix.matrix_pt();
  
  // Check whether the solution matrix has allocated memory, otherwise
  // allocate it here!!!
  if (solution_matrix.is_empty())
   {
    // Create a zero matrix with the given size to allocate memory
    solution_matrix.create_zero_matrix();
    // Get the new matrix pointer
    solution_matrix_pt = solution_matrix.matrix_pt();
   }
  
  // Get the matrix pointer of the left matrix
  T *left_matrix_pt = left_matrix.matrix_pt();
  // Get the matrix pointer of the right matrix
  T *right_matrix_pt = right_matrix.matrix_pt();
  // Perform the multiplication
  for (unsigned long i = 0; i < n_rows_left_matrix; i++)
   {
    const unsigned offset_left_matrix = i * n_columns_left_matrix;
    const unsigned offset_right_matrix = i * n_columns_right_matrix;
    for (unsigned long j = 0; j < n_columns_right_matrix; j++)
     {
      // Initialise
      solution_matrix_pt[offset_right_matrix+j] = 0;
      for (unsigned long k = 0; k < n_columns_left_matrix; k++)
       {
        solution_matrix_pt[offset_right_matrix+j]+=
         left_matrix_pt[offset_left_matrix+k] * right_matrix_pt[k*n_columns_right_matrix+j];
       }
     }
   }
 }
 
 // ================================================================
 // Extra methods to work with vector and matrices operations
 // ================================================================

 // ================================================================
 // Multiply vector times vector (if you want to perform dot product
 // use the dot() method defined in the cc_vector.h file instead)
 // ================================================================
 template<class T>
 void multiply_vector_times_vector(const CCVector<T> &left_vector,
                                   const CCVector<T> &right_vector,
                                   CCMatrix<T> &solution_matrix)
 {
  // Check that the left and the right vectors have entries to operate
  // with
  if (left_vector.is_empty() || right_vector.is_empty())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the vectors to operate with has no entries\n"
                  << "left_vector.is_empty() = "
                  << left_vector.is_empty() << "\n"
                  << "right_vector.is_empty() = "
                  << right_vector.is_empty() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vectors allow the operation
  unsigned n_rows_left_vector = 0;
  unsigned n_columns_left_vector = 0;
  if (left_vector.is_transposed()) // a row vector
   {
    n_rows_left_vector = 1;
    n_columns_left_vector = left_vector.nvalues();
   }
  else // a column vector
   {
    n_rows_left_vector = left_vector.nvalues();
    n_columns_left_vector = 1;
   }
  
  unsigned n_rows_right_vector = 0;
  unsigned n_columns_right_vector = 0;
  if (right_vector.is_transposed()) // a row vector
   {
    n_rows_right_vector = 1;
    n_columns_right_vector = right_vector.nvalues();
   }
  else // a column vector
   {
    n_rows_right_vector = right_vector.nvalues();
    n_columns_right_vector = 1;
   }
  
  // Check that the dimension of the vectors allow the operation
  if (n_columns_left_vector != n_rows_right_vector)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the vectors does not allow "
                  << "multiplication:\n"
                  << "dim(left_vector) = (" << n_rows_left_vector << ", "
                  << n_columns_left_vector << ")\n"
                  << "dim(right_vector) = (" << n_rows_right_vector << ", "
                  << n_columns_right_vector << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimension of the solution matrix are correct
  const unsigned long n_rows_solution_matrix = solution_matrix.nrows();
  const unsigned long n_columns_solution_matrix = solution_matrix.ncolumns();
  if (n_rows_left_vector != n_rows_solution_matrix ||
      n_columns_right_vector != n_columns_solution_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the solution matrix is not appropiate for\n"
                  << "the operation:\n"
                  << "dim(left_vector) = (" << n_rows_left_vector << ", "
                  << n_columns_left_vector << ")\n"
                  << "dim(right_vector) = (" << n_rows_right_vector << ", "
                  << n_columns_right_vector << ")\n"
                  << "dim(solution_matrix) = (" << n_rows_solution_matrix
                  << ", " << n_columns_solution_matrix << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the matrix pointer of the solution matrix
  T *solution_matrix_pt = solution_matrix.matrix_pt();
  
  // Check whether the solution matrix has allocated memory, otherwise
  // allocate it here!!!
  if (solution_matrix.is_empty())
   {
    // Create a zero matrix with the given size to allocate memory
    solution_matrix.create_zero_matrix();
    // Get the new matrix pointer
    solution_matrix_pt = solution_matrix.matrix_pt();
   }
  
  // Get both vectors and multiply them
  T *left_vector_pt = left_vector.vector_pt();
  T *right_vector_pt = right_vector.vector_pt();
  
  // Perform the multiplication
  for (unsigned long i = 0; i < n_rows_solution_matrix; i++)
   {
    const unsigned offset_left_vector = i * n_columns_left_vector;
    const unsigned offset_right_vector = i * n_columns_right_vector;
    for (unsigned long j = 0; j < n_columns_solution_matrix; j++)
     {
      // Initialise
      solution_matrix_pt[offset_right_vector+j] = 0;
      for (unsigned long k = 0; k < n_columns_left_vector; k++)
       {
        solution_matrix_pt[offset_right_vector+j]+=
         left_vector_pt[offset_left_vector+k] * right_vector_pt[k*n_columns_right_vector+j];
       }
     }
   }
  
 }
 
 // ================================================================
 // Multiply vector times matrix
 // ================================================================
 template<class T>
 void multiply_vector_times_matrix(const CCVector<T> &vector,
                                   const CCMatrix<T> &matrix,
                                   CCMatrix<T> &solution_matrix)
 {
  // Check that the vector and the matrix have entries to operate with
  if (vector.is_empty() || matrix.is_empty())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Either the vector or the matrix have no entries to\n"
                  << "operate with\n"
                  << "vector.is_empty() = "
                  << vector.is_empty() << "\n"
                  << "matrix.is_empty() = "
                  << matrix.is_empty() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vector and the matrix allow
  // the operation
  unsigned n_rows_vector = 0;
  unsigned n_columns_vector = 0;
  if (vector.is_transposed()) // a row vector
   {
    n_rows_vector = 1;
    n_columns_vector = vector.nvalues();
   }
  else // a column vector
   {
    n_rows_vector = vector.nvalues();
    n_columns_vector = 1;
   }
  
  unsigned n_rows_matrix = matrix.nrows();
  unsigned n_columns_matrix = matrix.ncolumns();
  
  // Check that the dimension of the vector and the matrix allow the
  // operation
  if (n_columns_vector != n_rows_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the vector and the matrix does\n"
                  << "not allow multiplication:\n"
                  << "dim(vector) = (" << n_rows_vector << ", "
                  << n_columns_vector << ")\n"
                  << "dim(matrix) = (" << n_rows_matrix << ", "
                  << n_columns_matrix << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimension of the solution matrix are correct
  const unsigned long n_rows_solution_matrix = solution_matrix.nrows();
  const unsigned long n_columns_solution_matrix = solution_matrix.ncolumns();
  if (n_rows_vector != n_rows_solution_matrix ||
      n_columns_matrix != n_columns_solution_matrix)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the solution matrix is not appropiate for\n"
                  << "the operation:\n"
                  << "dim(vector) = (" << n_rows_vector << ", "
                  << n_columns_vector << ")\n"
                  << "dim(matrix) = (" << n_rows_matrix << ", "
                  << n_columns_matrix << ")\n"
                  << "dim(solution_matrix) = (" << n_rows_solution_matrix
                  << ", " << n_columns_solution_matrix << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the matrix pointer of the solution matrix
  T *solution_matrix_pt = solution_matrix.matrix_pt();
  
  // Check whether the solution matrix has allocated memory, otherwise
  // allocate it here!!!
  if (solution_matrix.is_empty())
   {
    // Create a zero matrix with the given size to allocate memory
    solution_matrix.create_zero_matrix();
    // Get the new matrix pointer
    solution_matrix_pt = solution_matrix.matrix_pt();
   }
  
  // Get both the vector and the matrix pointer
  T *vector_pt = vector.vector_pt();
  T *matrix_pt = matrix.matrix_pt();
  
  // Perform the multiplication
  for (unsigned long i = 0; i < n_rows_solution_matrix; i++)
   {
    const unsigned offset_vector = i * n_columns_vector;
    const unsigned offset_matrix = i * n_columns_matrix;
    for (unsigned long j = 0; j < n_columns_solution_matrix; j++)
     {
      // Initialise
      solution_matrix_pt[offset_matrix+j] = 0;
      for (unsigned long k = 0; k < n_columns_vector; k++)
       {
        solution_matrix_pt[offset_matrix+j]+=
         vector_pt[offset_vector+k] * matrix_pt[k*n_columns_matrix+j];
       }
     }
   }
  
 }
 
 // ================================================================
 // Multiply matrix times vector
 // ================================================================
 template<class T>
 void multiply_matrix_times_vector(const CCMatrix<T> &matrix,
                                   const CCVector<T> &vector,
                                   CCVector<T> &solution_vector)
 {
 // Check that the matrix and the vector have entries to operate with
  if (matrix.is_empty() || vector.is_empty())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Either the matrix or the vector have no entries to\n"
                  << "operate with\n"
                  << "matrix.is_empty() = "
                  << matrix.is_empty() << "\n"
                  << "vector.is_empty() = "
                  << vector.is_empty() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the matrix and the vector allow
  // the operation
  unsigned n_rows_matrix = matrix.nrows();
  unsigned n_columns_matrix = matrix.ncolumns();
  
  unsigned n_rows_vector = 0;
  unsigned n_columns_vector = 0;
  if (vector.is_transposed()) // a row vector
   {
    n_rows_vector = 1;
    n_columns_vector = vector.nvalues();
   }
  else // a column vector
   {
    n_rows_vector = vector.nvalues();
    n_columns_vector = 1;
   }
  
  // Check that the dimension of the vector and the matrix allow the
  // operation
  if (n_columns_matrix != n_rows_vector)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the matrix and the vector does\n"
                  << "not allow multiplication:\n"
                  << "dim(matrix) = (" << n_rows_matrix << ", "
                  << n_columns_matrix << ")\n"
                  << "dim(vector) = (" << n_rows_vector << ", "
                  << n_columns_vector << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimension of the solution vector is correct
  unsigned n_rows_solution_vector = 0;
  unsigned n_columns_solution_vector = 0;
  if (solution_vector.is_transposed()) // a row vector
   {
    n_rows_solution_vector = 1;
    n_columns_solution_vector = solution_vector.nvalues();
   }
  else // a column vector
   {
    n_rows_solution_vector = solution_vector.nvalues();
    n_columns_solution_vector = 1;
   }
  
  if (n_rows_matrix != n_rows_solution_vector ||
      n_columns_vector != n_columns_solution_vector)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the solution vector is not appropiate for\n"
                  << "the operation:\n"
                  << "dim(matrix) = (" << n_rows_matrix << ", "
                  << n_columns_matrix << ")\n"
                  << "dim(vector) = (" << n_rows_vector << ", "
                  << n_columns_vector << ")\n"
                  << "dim(solution_vector) = (" << n_rows_solution_vector
                  << ", " << n_columns_solution_vector << ")\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the vector pointer of the solution vector
  T *solution_vector_pt = solution_vector.vector_pt();
  
  // Check whether the solution vector has allocated memory, otherwise
  // allocate it here!!!
  if (solution_vector.is_empty())
   {
    // Create a zero matrix with the given size to allocate memory
    solution_vector.create_zero_vector();
    // Get the new matrix pointer
    solution_vector_pt = solution_vector.vector_pt();
   }
  
  // Get both the vector and the matrix pointer
  T *matrix_pt = matrix.matrix_pt();
  T *vector_pt = vector.vector_pt();
  
  // Perform the multiplication
  for (unsigned long i = 0; i < n_rows_solution_vector; i++)
   {
    const unsigned offset_matrix = i * n_columns_matrix;
    const unsigned offset_vector = i * n_columns_vector;
    // We can skip one loop since there is only one column
    
    // Initialise
    solution_vector_pt[offset_vector] = 0;
    for (unsigned long k = 0; k < n_columns_matrix; k++)
     {
      solution_vector_pt[offset_vector]+=
       matrix_pt[offset_matrix+k] * vector_pt[k];
     }
   }
  
 }
 
}
