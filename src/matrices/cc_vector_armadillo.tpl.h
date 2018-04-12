// IN THIS FILE: The definition of a concrete class to store and work
// with vectors. This implementation makes use of Armadillo's library,
// thus this is only a wrap for Armadillo's methods

// Check whether the class has been already defined
#ifndef CCVECTORARMADILLO_TPL_H
#define CCVECTORARMADILLO_TPL_H

// The parent class
#include "ac_vector.h"

// We include the cc_vector include file to deal with transformations
// from CCVector class to CCVectorArmadillo
#include "cc_vector.h"

// Add Armadillo's includes
#include <armadillo>

namespace chapchom
{
 
 // forward CCMatrixArmadillo class declaration, required for vector
 // overloading operation *
 template<class T>
  class CCMatrixArmadillo;
 
 // extern method to perform vectors multiplication
 // Performs multiplication of matrices
 template<class T>
  extern void multiply_matrices(const CCMatrixArmadillo<T> &left_matrix,
                                const CCMatrixArmadillo<T> &right_matrix,
                                CCMatrixArmadillo<T> &solution_matrix);
 
 // Concrete class to represent vectors
 template<class T>
  class CCVectorArmadillo : public virtual ACVector<T>
  {
   
  public:
   
   // Empty constructor
   CCVectorArmadillo();
   
   // Constructor to create an n size zero vector (we assume vectors
   // are created as column vectors, if you need a row vector then
   // pass "true" as the second parameter).
   CCVectorArmadillo(const unsigned long n, bool is_transposed = false);
   
   // Constructor where we pass the data for the vector of size n.
   CCVectorArmadillo(T *vector_pt, const unsigned long n, bool is_transposed = false);
   
   // Constructor that creates an Armadillo's vector from a CCVector
   CCVectorArmadillo(CCVector<T> &vector);
   
   // Copy constructor (we require to define this if we want to use
   // operators overloading as sum and assignment)
   CCVectorArmadillo(const CCVectorArmadillo &copy);
   
   // Destructor
   virtual ~CCVectorArmadillo();
   
   // Assignment operator
   CCVectorArmadillo& operator=(const CCVectorArmadillo &source_vector);
   
   // += operator
   CCVectorArmadillo& operator+=(const CCVectorArmadillo &vector);
   
   // -= operator
   CCVectorArmadillo& operator-=(const CCVectorArmadillo &vector);
   
   // Add operator
   CCVectorArmadillo operator+(const CCVectorArmadillo &vector);
   
   // Substraction operator
   CCVectorArmadillo operator-(const CCVectorArmadillo &vector);

   // Multiplication operator (it returns a matrix with the
   // corresponding size, if you require a dot product operation use
   // the dot() method instead
   CCMatrixArmadillo<T> operator*(const CCVectorArmadillo &vector);
   
   // Allocates memory to store entries of the vector
   void allocate_memory();
   
   // Fills the vector with zeroes
   void fill_with_zeroes();
   
   // Performs dot product with the current vector
   T dot(const CCVectorArmadillo &right_vector);
   
   // Transforms the input vector to an Armadillo vector class type
   // (virtual such that each derived class has to implement it)
   void set_vector(const T *vector_pt,
                   const unsigned long n);
   
   // Receives an armadillo type column vector
   void set_vector(arma::Col<T> *arma_column_vector_pt,
                   const unsigned long n);
   
   // Receives an armadillo type column vector
   void set_vector(arma::Row<T> *arma_row_vector_pt,
                   const unsigned long n);
   
   // Clean up for any dynamically stored data
   void clean_up();
   
   // Free allocated memory for vector
   void free_memory_for_vector();
   
   // Performs sum of vectors
   void add_vector(const CCVectorArmadillo &vector, CCVectorArmadillo &solution_vector);
   
   // Performs substraction of vectors
   void substract_vector(const CCVectorArmadillo &vector,
                         CCVectorArmadillo &solution_vector);
   
   // Performs multiplication of vectors (one by one entries)
   void multiply_element_by_element_vector(const CCVectorArmadillo &vector,
                                           CCVectorArmadillo &solution_vector);
   
   // Computes the transpose and store it in the transpose vector
   void transpose(CCVectorArmadillo &transposed_vector);
   
   // Transpose the vector
   void transpose();
   //   {
   //    this->Is_transposed=!(this->Is_transposed);
   //  }
   
   // Get the specified value from the vector (read-only)
   const T value(const unsigned long i) const;
   
   // Set values in the vector (write version)
   T &value(const unsigned long i);
   
   // Output the vector
   void output(bool output_indexes = false) const ;
   
   // Output to file
   void output(std::ofstream &outfile, bool output_indexes = false) const;
   
   // Get access to the Armadillo's vector
   inline arma::Col<T> *arma_vector_pt() const {return Arma_vector_pt;}
   
   // Computes the norm-1 of the vector
   const double norm_1();
   
   // Computes the norm-2 of the vector
   const double norm_2();
   
  protected:
   
   // The Armadillo's type vector
   arma::Col<T> *Arma_vector_pt;
   
  };
 
 // ================================================================
 // Extra methods to work with vectors, we do not need them to be
 // friends of the class since all their operations are performed
 // using the class methods
 // ================================================================
 
 // Dot product of vectors
 template<class T>
  T dot_vectors(const CCVectorArmadillo<T> &left_vector, const CCVectorArmadillo<T> &right_vector);
 
 // Addition of vectors
 template<class T>
  void add_vectors(const CCVectorArmadillo<T> &vector_one,
                   const CCVectorArmadillo<T> &vector_two,
                   CCVectorArmadillo<T> &solution_vector);
 
 // Substraction of vectors
 template<class T>
  void substract_vectors(const CCVectorArmadillo<T> &vector_one,
                         const CCVectorArmadillo<T> &vector_two,
                         CCVectorArmadillo<T> &solution_vector);
 
 // Performs multiplication of vectors (one by one entries)
 template<class T>
  void multiply_element_by_element_vectors(const CCVectorArmadillo<T> &vector_one,
                                           const CCVectorArmadillo<T> &vector_two,
                                           CCVectorArmadillo<T> &solution_vector);
 
}

#endif // #ifndef CCVECTORARMADILLO_TPL_H
