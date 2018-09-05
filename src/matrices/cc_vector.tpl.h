// IN THIS FILE: The definition of a concrete class to store and work
// with vectors. This is the simplest implementation

// Check whether the class has been already defined
#ifndef CCVECTOR_TPL_H
#define CCVECTOR_TPL_H

// The parent class
#include "ac_vector.h"

namespace chapchom
{
 
 // forward CCMatrix class declaration, required for vector
 // overloading operation *
 template<class T>
  class CCMatrix;
 
 // extern method to perform vectors multiplication
 // Performs multiplication of matrices
 template<class T>
  extern void multiply_matrices(const CCMatrix<T> &left_matrix,
                                const CCMatrix<T> &right_matrix,
                                CCMatrix<T> &solution_matrix);
 
 // Concrete class to represent vectors
 template<class T>
  class CCVector : public virtual ACVector<T>
  {
   
  public:
   
   // Empty constructor
   CCVector();
   
   // Constructor to create an n size zero vector (we assume vectors
   // are created as column vectors, if you need a row vector then
   // pass "false" as the second parameter)
   CCVector(const unsigned long n, bool is_column_vector = true);
   
   // Constructor where we pass the data for the vector of size n.
   CCVector(T *vector_pt, const unsigned long n, bool is_column_vector = true);
   
   // Copy constructor (we require to define this if we want to use
   // operators overloading as sum and assignment)
   CCVector(const CCVector &copy);
   
   // Destructor
   virtual ~CCVector();
   
   // Assignment operator
   CCVector& operator=(const CCVector &source_vector);
   
   // += operator
   CCVector& operator+=(const CCVector &vector);
   
   // -= operator
   CCVector& operator-=(const CCVector &vector);
   
   // Add operator
   CCVector operator+(const CCVector &vector);
   
   // Substraction operator
   CCVector operator-(const CCVector &vector);

   // Multiplication operator (it returns a matrix with the
   // corresponding size, if you require a dot product operation use
   // the dot() method instead
   CCMatrix<T> operator*(const CCVector &vector);

   // Allocates memory to store entries of the vector
   void allocate_memory();
   
   // Fills the vector with zeroes
   void fill_with_zeroes();
   
   // Performs dot product with the current vector
   T dot(const CCVector &right_vector);
   
   // Transforms the input vector to a vector class type
   void set_vector(const T *vector_pt,
                   const unsigned long n,
                   bool is_column_vector = true);
   
   // Clean up for any dynamically stored data
   void clean_up();
   
   // Free allocated memory for vector
   void free_memory_for_vector();
   
   // Performs sum of vectors
   void add_vector(const CCVector &vector, CCVector &solution_vector);
   
   // Performs substraction of vectors
   void substract_vector(const CCVector &vector,
                         CCVector &solution_vector);
   
   // Performs multiplication of vectors (one by one entries)
   void multiply_element_by_element_vector(const CCVector &vector,
                                           CCVector &solution_vector);
   
   // Computes the transpose and store it in the transpose vector
   void transpose(CCVector &transposed_vector);
   
   // Transpose the vector
   inline void transpose()
   {
    this->Is_column_vector=!(this->Is_column_vector);
   }
   
   // Get the specified value from the vector (read-only)
   const T value(const unsigned long i) const;
   
   // Set values in the vector (write version)
   T &value(const unsigned long i);
   
   // Output the vector
   void output(bool output_indexes = false) const ;
   
   // Output to file
   void output(std::ofstream &outfile, bool output_indexes = false) const;
   
   // Get access to the Vector_pt
   inline T *vector_pt() const {return Vector_pt;}
   
   // Computes the norm-1 of the vector
   double norm_1();
   
   // Computes the norm-2 of the vector
   double norm_2();
   
  protected:
      
   // The vector
   T *Vector_pt;
   
  };
 
 // ================================================================
 // Extra methods to work with vectors, we do not need them to be
 // friends of the class since all their operations are performed
 // using the class methods
 // ================================================================
 
 // Dot product of vectors
 template<class T>
  T dot_vectors(const CCVector<T> &left_vector, const CCVector<T> &right_vector);
 
 // Addition of vectors
 template<class T>
  void add_vectors(const CCVector<T> &vector_one,
                   const CCVector<T> &vector_two,
                   CCVector<T> &solution_vector);
 
 // Substraction of vectors
 template<class T>
  void substract_vectors(const CCVector<T> &vector_one,
                         const CCVector<T> &vector_two,
                         CCVector<T> &solution_vector);
 
 // Performs multiplication of vectors (one by one entries)
 template<class T>
  void multiply_element_by_element_vectors(const CCVector<T> &vector_one,
                                           const CCVector<T> &vector_two,
                                           CCVector<T> &solution_vector);
 
}

#endif // #ifndef CCVECTOR_TPL_H
