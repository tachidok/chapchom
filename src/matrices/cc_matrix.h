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
 CCMatrix(const unsigned long n);
 
 // Constructor to create an m X n zero matrix
 CCMatrix(const unsigned long m, const unsigned long n);
 
 // Constructor where we pass the data for the matrix of size m X n
 CCMatrix(double *matrix_pt, const unsigned long m, const unsigned long n);
 
 // Copy constructor (we require to define this if we want to use
 // operators overloading as sum and assignment)
 CCMatrix(const CCMatrix &copy);
 
 // Destructor
 virtual ~CCMatrix();
 
 // += operator
 CCMatrix& operator+=(const CCMatrix &matrix);
 
 // -= operator
 CCMatrix& operator-=(const CCMatrix &matrix);
 
 // Assignment operator
 CCMatrix& operator=(const CCMatrix &source_matrix);
 
 // Add operator
 CCMatrix operator+(const CCMatrix &matrix);
 
 // Substraction operator
 CCMatrix operator-(const CCMatrix &matrix);
 
 // Multiplication operator
 CCMatrix operator*(const CCMatrix &right_matrix);
  
 // Transforms the input vector to a matrix class type (virtual such
 // that each derived class has to implement it)
 void set_matrix(const double *matrix_pt,
                 const unsigned long m,
                 const unsigned long n);
 
 // Clean up for any dynamically stored data
 void clean_up();
 
 // Free allocated memory for matrix
 void free_memory_for_matrix();
 
 // Performs sum of matrices
 void add_matrix(const CCMatrix &matrix, const CCMatrix &solution_matrix);
 
 // Performs substraction of matrices
 void substract_matrix(const CCMatrix &matrix, const CCMatrix &solution_matrix);
 
 // Performs multiplication of matrices
 void multiply_by_matrix(const CCMatrix &right_matrix, const CCMatrix &solution_matrix);
 
 // Computes the transpose and store it in the solution matrix
 void transpose(const CCMatrix &transpose_matrix);
  
 // Get the specified value from the matrix (read-only)
 const double value(const unsigned long i, const unsigned long j) const;
 
 // Set values in the matrix (write version)
 double &value(const unsigned long i, const unsigned long j);
 
 // Output the matrix
 void output();
 
 // Get access to the Matrix_pt
 inline double *matrix_pt() const {return Matrix_pt;}
 
 protected:
 
 // Creates a zero matrix with the given rows and columns
 void create_zero_matrix();
 
 // The matrix
 double *Matrix_pt;
 
};

#endif // #ifndef CCMATRIX_H
