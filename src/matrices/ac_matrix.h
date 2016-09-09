// IN THIS FILE: The definition of an abstract class to store and work
// with matrices. Most of the matrices implemented in this library use
// this class as the base class

// Check whether the class has been already defined
#ifndef ACMATRIX_H
#define ACMATRIX_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

namespace chapchom
{

 /// @class ACMatrix ac_matrix.h

 // TODO. Julio. Make template matrix to have matrices of integers,
 // doubles and complexes

 // Abstract class to represent matrices
 template<class T>
 class ACMatrix
 {

 public:
 
  // Empty constructor
  ACMatrix();
 
  // Constructor to create an n X n zero matrix
  ACMatrix(const unsigned long n);
 
  // Constructor to create an m X n zero matrix
  ACMatrix(const unsigned long m, const unsigned long n);
  
  // Destructor
  virtual ~ACMatrix();
  
  // Transforms the input vector to a matrix class type (virtual such
  // that each derived class has to implement it)
  virtual void set_matrix(const T *matrix_pt,
                          const unsigned long m,
                          const unsigned long n) = 0;
 
  // Clean up for any dynamically stored data
  virtual void clean_up() = 0;
 
  // Free allocated memory for matrix
  virtual void free_memory_for_matrix() = 0;
  
  // Get the specified value from the matrix (read-only)
  virtual const T value(const unsigned long i, const unsigned long j) const = 0;
  
  // Set values in the matrix (write version)
  virtual T &value(const unsigned long i, const unsigned long j) = 0;
 
  // Get the specified value from the matrix
  inline T get_value(const unsigned long i, const unsigned long j) const
  {return value(i,j);}
 
  // Set values in the matrix
  inline void set_value(const unsigned long i, const unsigned long j, T v)
  {value(i, j) = v;}
 
  /// Get access using brackets as matrix(i,j). Read-only version
  inline virtual T operator()(const unsigned long &i, 
                              const unsigned long &j) const
  {return value(i, j);}
 
  /// Get access using brackets as matrix(i,j). Read-write version
  inline virtual T &operator()(const unsigned long &i, 
                               const unsigned long &j)
  {return value(i,j);}
 
  // Output the matrix
  // TODO Implement output to file version
  //virtual void output(std::string &filename = 0) = 0;
  virtual void output() = 0;
 
  // Return the number of rows of the matrix
  const unsigned long nrows() const {return NRows;}
 
  // Return the number of columns of the matrix
  const unsigned long ncolumns() const {return NColumns;}
 
  // Checks whether the matrix has been set, or allocated
  inline bool is_empty() const {return Is_empty;}
 
  // Checks whether the matrix is allowed to be deleted
  inline bool delete_matrix() const {return Delete_matrix;}
 
  // Enables the deletion of the matrix by this class
  inline void enable_delete_matrix() {Delete_matrix=true;}
 
  // Disables the deletion of the matrix by this class
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
  // the matrix. For example when the matrix is transformed to an
  // specific matrix type (Armadillo matrix, SuperLU matrix, Trilinos
  // matrix) we need to deallocate the memory used for THIS matrix to
  // avoid having multiple copies of the matrix. The deletion of the
  // matrix is true by default.
  bool Delete_matrix;
 
 private:
 
  // Copy constructor (we do not want this class to be copiable). Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  ACMatrix(const ACMatrix &copy)
   {
    BrokenCopy::broken_copy("ACMatrix");
   }
 
  // Assignment operator (we do not want this class to be
  // copiable. Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  ACMatrix& operator=(const ACMatrix &copy)
   {
    BrokenCopy::broken_assign("ACMatrix");
   }
 
 };

}
 
#endif // #ifndef ACMATRIX_H
