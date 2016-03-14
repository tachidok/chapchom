// IN THIS FILE: The definition of an abstract class to store and work
// with matrices. All the matrices implemented in this library
// use this class as the base class

// Check whether the class has been already defined
#ifndef CAMATRIX_H
#define CAMATRIX_H

#include "../General/HCommon_includes.h"

// Abstract class to represent matrices
class CAMatrix
{

 public:
 
 // Empty constructor
 CAMatrix();
 
 // Constructor to create an n X n zero matrix
 CAMatrix(const unsigned n);
 
 // Constructor to create an m X n zero matrix
 CAMatrix(const unsigned m, const unsigned n);
 
 // Constructor where we pass the data for the matrix of size m X n
 CAMatrix(double **_matrix, const unsigned m, const unsigned n);
 
 // Destructor
 virtual ~CAMatrix();
 
 // Set the matrix (virtual such that each derived class has to
 // implement it)
 virtual void set_matrix(const double **_matrix,
                         const unsigned m,
                         const unsigned n) = 0;
 
 // Clean up for any dynamically stored data
 virtual void clean_up();
 
 // Free allocated memory for matrix
 virtual void free_memory_for_matrix() = 0;
 
 // Set values in the matrix
 virtual void set_value(const unsigned i,
                        const unsigned j,
                        double value) = 0;
 
 // Get the specified value from the matrix
 virtual double get_value(const unsigned i, const unsigned j) const = 0;
 
 // Returns the value from the matrix (it can be modified outside)
 virtual double &value(const unsigned i, const unsigned j) const = 0;
 
 /// Get access using brackets as matrix(i,j). Read-only version
 inline virtual double operator()(const unsigned long &i, 
                                  const unsigned long &j) const
 {return get_value(i, j);}
 
 /// Get access using brackets as matrix(i,j). Read-write version
 inline virtual double &operator()(const unsigned long &i, 
                                   const unsigned long &j)
 {return value(i,j);}
 
 // Output the matrix
 virtual void output() = 0;
 
 // Return the number of rows of the matrix
 const unsigned long nrows() const {return NRows;}
 
 // Return the number of columns of the matrix
 const unsigned long ncolumns() const {return NColumns;}
 
 // Checks whether the matrix has been set, or allocated
 inline bool is_empty() const {return Is_empty;}
 
 // Checks whether the matrix is allowed to be deleted
 inline bool can_delete_matrix() const {return Delete_matrix;}
 
 // Enables the deletion of the matrix by another entity than the
 // destructor of the matrix itself
 inline void enable_delete_matrix() {Delete_matrix=true;}
 
 // Disables the deletion of the matrix by another entity than the
 // destructor of the matrix itself
 inline void disable_delete_matrix() {Delete_matrix=false;}
 
 protected:
 
 // Creates a zero matrix with the given rows and columns
 virtual void create_zero_matrix() = 0;
 
 // The size of the matrix
 unsigned long NRows;
 unsigned long NColumns;
 
 // Flag to indicate whether the matrix is empty or not
 bool Is_empty;
 
 // Flag to indicate whether to delete (free) the allocated memory for
 // the matrix by another entity than the destructor of the matrix
 // itself. For example when the matrix is transformed to an specific
 // matrix type (Armadillo matrix, SuperLU matrix, Trilinos
 // matrix). The deletion of the matrix is true by default to avoid
 // having multiple copies of a matrix
 bool Delete_matrix;
 
 private:
 
 // Copy constructor (we do not want this class to be copiable). Check
 // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CAMatrix(const CAMatrix &copy);
 
 // Assignment operator (we do not want this class to be
 // copiable. Check
 // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CAMatrix& operator=(const CAMatrix &copy);
 
};

#endif // #ifndef CAMATRIX_H
