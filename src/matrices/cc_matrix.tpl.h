// IN THIS FILE: The definition of a concrete class to store and work
// with matrices. This is the simplest implementation

// Check whether the class has been already defined
#ifndef CCMATRIX_TPL_H
#define CCMATRIX_TPL_H

// The parent class
#include "ac_matrix.h"
// We include the cc_vector class to deal with vector-matrices
// operations
#include "cc_vector.h"

namespace chapchom
{

 // Concrete class to represent matrices
 template<class T>
 class CCMatrix : public virtual ACMatrix<T>
 {
  
 public:
  
  // Empty constructor
  CCMatrix();
  
  // Constructor to create an n X n matrix.
  CCMatrix(const unsigned long n);
  
  // Constructor to create an m X n matrix.
  CCMatrix(const unsigned long m, const unsigned long n);
  
  // Constructor where we pass the data for the matrix of size m X n
  CCMatrix(T *matrix_pt, const unsigned long m, const unsigned long n);
  
  // Constructor that creates a matrix from a vector
  CCMatrix(CCVector<T> &vector);
  
  // Copy constructor (we require to define this if we want to use
  // operators overloading as sum and assignment)
  CCMatrix(const CCMatrix &copy);
  
  // Destructor
  virtual ~CCMatrix();
  
  // Assignment operator
  CCMatrix &operator=(const CCMatrix &source_matrix);
  
  // += operator
  CCMatrix &operator+=(const CCMatrix &matrix);
  
  // -= operator
  CCMatrix &operator-=(const CCMatrix &matrix);
  
  // Add operator
  CCMatrix operator+(const CCMatrix &matrix);
  
  // Substraction operator
  CCMatrix operator-(const CCMatrix &matrix);
  
  // Multiplication operator
  CCMatrix operator*(const CCMatrix &right_matrix);
  
  // Allocates memory to store entries of the vector
  void allocate_memory();
   
  // Fills the vector with zeroes
  void fill_with_zeroes();
  
  // Transforms the input vector to a matrix class type (virtual such
  // that each derived class has to implement it)
  void set_matrix(const T *matrix_pt,
                  const unsigned long m,
                  const unsigned long n);
  
  // Clean up for any dynamically stored data
  void clean_up();
  
  // Free allocated memory for matrix
  void free_memory_for_matrix();
  
  // Performs sum of matrices
  void add_matrix(const CCMatrix &matrix, CCMatrix &solution_matrix);
  
  // Performs substraction of matrices
  void substract_matrix(const CCMatrix &matrix, CCMatrix &solution_matrix);
  
  // Performs multiplication of matrices
  void multiply_by_matrix(const CCMatrix &right_matrix, CCMatrix &solution_matrix);
  
  // Computes the transpose and store it in the transpose matrix
  void transpose(CCMatrix &transposed_matrix);
  
  // Transpose the matrix
  void transpose();
  
  // Get the specified value from the matrix (read-only)
  const T value(const unsigned long i, const unsigned long j) const;
  
  // Set values in the matrix (write version)
  T &value(const unsigned long i, const unsigned long j);

  /// Permute rows i and j
  void permute_rows(const unsigned long &i, const unsigned long &j);
   
  /// Permute columns i and j
  void permute_columns(const unsigned long &i, const unsigned long &j);
  
  // Output the matrix
  void output(bool output_indexes = false) const;
  
  // Output to file
  void output(std::ofstream &outfile, bool output_indexes = false) const;
  
  // Get access to the Matrix_pt
  inline T *matrix_pt() const {return Matrix_pt;}
  
 protected:
    
  // The matrix
  T *Matrix_pt;
  
 };
 
 // ================================================================
 // Extra methods to work with matrices, we do not need them to be
 // friends of the class since all their operations are performed
 // using the class methods
 // ================================================================
 
 // Performs sum of matrices
 template<class T>
 void add_matrices(const CCMatrix<T> &matrix_one,
                   const CCMatrix<T> &matrix_two,
                   CCMatrix<T> &solution_matrix);
 
 // Performs substraction of matrices
 template<class T>
 void substract_matrices(const CCMatrix<T> &matrix_one,
                         const CCMatrix<T> &matrix_two,
                         CCMatrix<T> &solution_matrix);
 
 // Performs multiplication of matrices
 template<class T>
 void multiply_matrices(const CCMatrix<T> &left_matrix,
                        const CCMatrix<T> &right_matrix,
                        CCMatrix<T> &solution_matrix);
 
 // ================================================================
 // Extra methods to work with vector and matrices operations
 // ================================================================
 // Multiply vector times matrix
 template<class T>
 void multiply_vector_times_matrix(const CCVector<T> &vector, const CCMatrix<T> &matrix,
                                   CCMatrix<T> &solution_matrix);
 
 // Multiply matrix times vector
 template<class T>
 void multiply_matrix_times_vector(const CCMatrix<T> &matrix, const CCVector<T> &vector,
                                   CCVector<T> &solution_vector);
 
}

#endif // #ifndef CCMATRIX_TPL_H
