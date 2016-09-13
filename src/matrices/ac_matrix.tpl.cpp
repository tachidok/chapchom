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
  : NRows(0), NColumns(0), Is_empty(true), Delete_matrix(true)
 { }

 // ===================================================================
 // Constructor to create an n X n zero matrix
 // ===================================================================
 template<class T>
 ACMatrix<T>::ACMatrix(const unsigned long n)
  : NRows(n), NColumns(n), Is_empty(true), Delete_matrix(true)
 { }
 

 // ===================================================================
 // Constructor to create an m X n zero matrix
 // ===================================================================
 template<class T>
 ACMatrix<T>::ACMatrix(const unsigned long m, const unsigned long n)
  : NRows(m), NColumns(n), Is_empty(true), Delete_matrix(true)
 { }

 // ===================================================================
 // Destructor
 // ===================================================================
 template<class T>
 ACMatrix<T>::~ACMatrix()
 { }

}
