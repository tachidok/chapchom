// IN THIS FILE: The definition of a concrete class to store and work
// with matrices. This is the simplest implementation

// Check whether the class has been already defined
#ifndef CCMATRIX_H
#define CCMATRIX_H

#include "CAMatrix.h"

// Concrete class to represent matrices
class CCMatrix : public virtual CAMatrix
{

 public:
 
 // Empty constructor
 CCMatrix();
 
 // Constructor to create an n X n zero matrix
 CCMatrix(const unsigned n);
 
 // Constructor to create an m X n zero matrix
 CCMatrix(const unsigned m, const unsigned n);
 
 // Constructor where we pass the data for the matrix of size m X n
 CCMatrix(double **_matrix, const unsigned m, const unsigned n);
 
 // Destructor
 virtual ~CCMatrix();
 
 // Set the matrix
 void set_matrix(const double **_matrix,
                 const unsigned m,
                 const unsigned n);
 
 // Clean up for any dynamically stored data
 void clean_up();
 
 // Free allocated memory for matrix
 void free_memory_for_matrix();
 
 // Set values in the matrix
 void set_value(const unsigned i, const unsigned j, double value);
 
 // Get the specified value from the matrix (read-only)
 double get_value(const unsigned i, const unsigned j) const;
 
 // Returns the value from the matrix (read-write version). It can be
 // modified outside
 double &value(const unsigned i, const unsigned j) const;
 
 // Output the matrix
 void output();
 
 protected:
 
 // Creates a zero matrix with the given rows and columns
 void create_zero_matrix();
 
 // The matrix
 double **Matrix_pt;
 
 private:
 
 // Copy constructor (we do not want this class to be copiable because
 // it contains dynamically allocated variables; the matrix. Check
 // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCMatrix(const CCMatrix &copy);
 
 // Copy constructor (we do not want this class to be copiable because
 // it contains dynamically allocated variables; the matrix. Check
 // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCMatrix& operator=(const CCMatrix &copy);
 
};

#endif // #ifndef CCMATRIX_H
