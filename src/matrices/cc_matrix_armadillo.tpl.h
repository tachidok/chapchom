// IN THIS FILE: The definition of a concrete class to store and work
// with matrices. This implementation makes use of Armadillo's
// library, thus this is only a wrap for Armadillo's methods

// Check whether the class has been already defined
#ifndef CCMATRIXARMADILLO_TPL_H
#define CCMATRIXARMADILLO_TPL_H

// The parent class
#include "ac_matrix.h"
// We include the cc_matrix and cc_vector include files to deal with
// transformations from CCMatrix and CCVector classes to
// CCMatrixArmadillo
#include "cc_vector.h"
#include "cc_matrix.h"

// Add Armadillo's includes
#include <armadillo>

namespace chapchom
{
 
 // Concrete class to represent matrices
 template<class T>
  class CCMatrixArmadillo : public virtual ACMatrix<T>
  {
   
  public:
   
   // Empty constructor
   CCMatrixArmadillo();
   
   // Constructor to create an n X n matrix.
   CCMatrixArmadillo(const unsigned long n);
  
   // Constructor to create an m X n matrix.
   CCMatrixArmadillo(const unsigned long m, const unsigned long n);
  
   // Constructor where we pass the data for the matrix of size m X n
   CCMatrixArmadillo(T *matrix_pt, const unsigned long m, const unsigned long n);
   
   // Constructor that creates an Armadillo's matrix from a CCMatrix
   CCMatrixArmadillo(CCMatrix<T> &matrix);
   
   // Constructor that creates an Armadillo's matrix from a CCVector
   CCMatrixArmadillo(CCVector<T> &vector);
   
   // Copy constructor (we require to define this if we want to use
   // operators overloading as sum and assignment)
   CCMatrixArmadillo(const CCMatrixArmadillo &copy);
   
   // Destructor
   virtual ~CCMatrixArmadillo();
  
   // Assignment operator
   CCMatrixArmadillo &operator=(const CCMatrixArmadillo &source_matrix);
  
   // += operator
   CCMatrixArmadillo &operator+=(const CCMatrixArmadillo &matrix);
  
   // -= operator
   CCMatrixArmadillo &operator-=(const CCMatrixArmadillo &matrix);
  
   // Add operator
   CCMatrixArmadillo operator+(const CCMatrixArmadillo &matrix);
  
   // Substraction operator
   CCMatrixArmadillo operator-(const CCMatrixArmadillo &matrix);
  
   // Multiplication operator
   CCMatrixArmadillo operator*(const CCMatrixArmadillo &right_matrix);
   
   // Allocates memory to store entries of the vector
   void allocate_memory();
   
   // Fills the vector with zeroes
   void fill_with_zeroes();
   
   // Transforms the input vector to an Armadillo's matrix class type
   void set_matrix(const T *matrix_pt,
                   const unsigned long m,
                   const unsigned long n);
   
   // Transforms the input CCMatrix to an Armadillo's matrix class type
   void set_matrix(CCMatrix<T> &matrix);
   
   // Transforms the input CCVector to an Armadillo's matrix class type
   void set_matrix(CCVector<T> &vector);
   
   // Clean up for any dynamically stored data
   void clean_up();
  
   // Free allocated memory for matrix
   void free_memory_for_matrix();
  
   // Performs sum of matrices
   void add_matrix(const CCMatrixArmadillo &matrix, CCMatrixArmadillo &solution_matrix);
  
   // Performs substraction of matrices
   void substract_matrix(const CCMatrixArmadillo &matrix, CCMatrixArmadillo &solution_matrix);
  
   // Performs multiplication of matrices
   void multiply_by_matrix(const CCMatrixArmadillo &right_matrix, CCMatrixArmadillo &solution_matrix);
   
   // Computes the transpose and store it in the transpose matrix
   void transpose(CCMatrixArmadillo &transposed_matrix);
   
   // Transpose the matrix
   void transpose();
   
   // Get the specified value from the matrix (read-only)
   const T value(const unsigned long i, const unsigned long j) const;
   
   // Set values in the matrix (write version)
   T &value(const unsigned long i, const unsigned long j);
   
   /// Permute the rows in the list
   void permute_rows(std::vector<std::pair<unsigned long, unsigned long> > &permute_list);
  
   /// Permute the columns in the list
   void permute_columns(std::vector<std::pair<unsigned long, unsigned long> > &permute_list);
  
   /// Permute rows i and j
   void permute_rows(const unsigned long &i, const unsigned long &j);
   
   /// Permute columns i and j
   void permute_columns(const unsigned long &i, const unsigned long &j);
  
   // Output the matrix
   void output(bool output_indexes = false) const;
  
   // Output to file
   void output(std::ofstream &outfile, bool output_indexes = false) const;
   
   // Get access to the Armadillo's matrix
   inline arma::Mat<T> *arma_matrix_pt() const {return Arma_matrix_pt;}
   
  protected:
   
   // The Armadillo's type matrix
   arma::Mat<T> *Arma_matrix_pt;
   
  };
 
 // ================================================================
 // Extra methods to work with matrices, we do not need them to be
 // friends of the class since all their operations are performed
 // using the class methods
 // ================================================================
 
 // Performs sum of matrices
 template<class T>
  void add_matrices(const CCMatrixArmadillo<T> &matrix_one,
                    const CCMatrixArmadillo<T> &matrix_two,
                    CCMatrixArmadillo<T> &solution_matrix);
 
 // Performs substraction of matrices
 template<class T>
  void substract_matrices(const CCMatrixArmadillo<T> &matrix_one,
                          const CCMatrixArmadillo<T> &matrix_two,
                          CCMatrixArmadillo<T> &solution_matrix);
 
 // Performs multiplication of matrices
 template<class T>
  void multiply_matrices(const CCMatrixArmadillo<T> &left_matrix,
                         const CCMatrixArmadillo<T> &right_matrix,
                         CCMatrixArmadillo<T> &solution_matrix);
 
 // ================================================================
 // Extra methods to work with vector and matrices operations
 // ================================================================
 // Multiply vector times matrix
 template<class T>
  void multiply_vector_times_matrix(const CCVector<T> &vector, const CCMatrixArmadillo<T> &matrix,
                                    CCMatrixArmadillo<T> &solution_matrix);
 
 // Multiply matrix times vector
 template<class T>
  void multiply_matrix_times_vector(const CCMatrixArmadillo<T> &matrix, const CCVector<T> &vector,
                                    CCVector<T> &solution_vector);
 
}

#endif // #ifndef CCMATRIXARMADILLO_TPL_H
