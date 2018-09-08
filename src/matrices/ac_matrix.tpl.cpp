// IN THIS FILE: Implementation of an abstract class to represent
// matrices

#include "ac_matrix.tpl.h"

namespace chapchom
{

 // ===================================================================
 // Empty constructor
 // ===================================================================
 template<class T>
 ACMatrix<T>::ACMatrix() 
  : NRows(0), NColumns(0), Is_own_memory_allocated(false), Delete_matrix(true)
 { }
 
 // ===================================================================
 // Constructor to create an m X n zero matrix
 // ===================================================================
 template<class T>
 ACMatrix<T>::ACMatrix(const unsigned long m, const unsigned long n)
  : NRows(m), NColumns(n), Is_own_memory_allocated(false), Delete_matrix(true)
 { }
 
 // ===================================================================
 // Destructor
 // ===================================================================
 template<class T>
 ACMatrix<T>::~ACMatrix()
 { }

 // ===================================================================
 // Allows to create a matrix with the given size but with no data
 // ===================================================================
 template<class T>
 void ACMatrix<T>::allocate_memory(const unsigned long m,
                                   const unsigned long n)
 {
  // Clean any possibly stored data
  clean_up();
  
  // Set the number of rows and columns of the matrix
  NRows = m;
  NColumns = n;
  
  // Allocate memory
  allocate_memory();
  
 }

}
