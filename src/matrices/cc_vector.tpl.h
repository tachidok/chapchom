// IN THIS FILE: The definition of a concrete class to store and work
// with vectors. This is the simplest implementation

// Check whether the class has been already defined
#ifndef CCVECTOR_H
#define CCVECTOR_H

// The parent class
#include "ac_vector.h"

namespace chapchom
{

 // Concrete class to represent vectors
 template<class T>
 class CCVector : public virtual ACVector<T>
 {

 public:
 
  // Empty constructor
  CCVector();
  
  // Constructor to create an n size zero vector (we assume vectors
  // are created as column vectors, if you require a row vector then
  // transpose it)
  CCVector(const unsigned long n);
  
  // Constructor where we pass the data for the vector of size n
  CCVector(T *vector_pt, const unsigned long n);
  
  // Copy constructor (we require to define this if we want to use
  // operators overloading as sum and assignment)
  CCVector(const CCVector &copy);
  
  // Destructor
  virtual ~CCVector();
  
  // += operator
  CCVector& operator+=(const CCVector &vector);
  
  // -= operator
  CCVector& operator-=(const CCVector &vector);
  
  // Assignment operator
  CCVector& operator=(const CCVector &source_vector);
  
  // Add operator
  CCVector operator+(const CCVector &vector);
  
  // Substraction operator
  CCVector operator-(const CCVector &vector);
  
  // Multiplication operator (element by element)
  CCVector operator*(const CCVector &vector);
  
  // Performs dot product with the current vector
  T dot(const CCVector &right_vector);
  
  // Friend method that allows to perform dot product of vectors
  friend
   T dot(const CCVector &left_vector, const CCVector &right_vector);
  
  ADD FRIENDS FOR ADDITION/SUBSTRACTION AND MULTIPLICATION OF VECTORS AND MATRICES
  
  // Transforms the input vector to a vector class type (virtual such
  // that each derived class has to implement it)
  void set_vector(const T *vector_pt,
                  const unsigned long n);
  
  // Clean up for any dynamically stored data
  void clean_up();
  
  // Free allocated memory for vector
  void free_memory_for_vector();
  
  // Performs sum of vectors
  void add_vector(const CCVector &vector, const CCVector &solution_vector);
  
  // Performs substraction of vectors
  void substract_vector(const CCVector &vector,
                        const CCVector &solution_vector);
  
  // Performs multiplication of vectors (one by one entries)
  void multiply_by_vector(const CCVector &vector,
                          const CCVector &solution_vector);
  
  // Computes the transpose and store it in the transpose vector
  void transpose(const CCVector &transpose_vector);
  
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
 
 protected:
  
  // Creates a zero vector with the given number of entries
  void create_zero_vector();
  
  // The vector
  T *Vector_pt;
  
 };
 
}

#endif // #ifndef CCVECTOR_H
