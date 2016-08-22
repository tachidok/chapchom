// IN THIS FILE: The definition of a concrete class to store and work
// with matrices. This is the simplest implementation

// Check whether the class has been already defined
#ifndef CCMATRIX_H
#define CCMATRIX_H

// The parent class
#include "ac_matrix.h"

// Concrete class to represent matrices
class CCMatrix : public virtual ACMatrix
{

 public:
 
 // Empty constructor
 CCMatrix();
 
 // Constructor to create an n X n zero matrix
 CCMatrix(const unsigned n);
 
 // Constructor to create an m X n zero matrix
 CCMatrix(const unsigned m, const unsigned n);
 
 // Constructor where we pass the data for the matrix of size m X n
 CCMatrix(double *matrix_pt, const unsigned m, const unsigned n);
 
 // Destructor
 virtual ~CCMatrix();
 
 // Transforms the input vector to a matrix class type (virtual such
 // that each derived class has to implement it)
 void set_matrix(const double *matrix_pt,
                 const unsigned m,
                 const unsigned n);
 
 // Clean up for any dynamically stored data
 void clean_up();
 
 // Free allocated memory for matrix
 void free_memory_for_matrix();
 
 // Get the specified value from the matrix (read-only)
 const double value(const unsigned i, const unsigned j) const;
 
 // Set values in the matrix (write version)
 double &value(const unsigned i, const unsigned j);
 
 // Output the matrix
 void output();
 
 protected:
 
 // Creates a zero matrix with the given rows and columns
 void create_zero_matrix();
 
 // The matrix
 double *Matrix_pt;
 
 private:
 
 // Copy constructor (we do not want this class to be copiable). Check
 // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCMatrix(const CCMatrix &copy);
 
 // Assignment operator (we do not want this class to be
 // copiable. Check
 // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCMatrix& operator=(const CCMatrix &copy);
 
};

#endif // #ifndef CCMATRIX_H
