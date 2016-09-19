// IN THIS FILE: Implementation of an abstract class to represent
// vectors

#include "ac_vector.tpl.h"

namespace chapchom
{

 // ===================================================================
 // Empty constructor
 // ===================================================================
 template<class T>
 ACVector<T>::ACVector() 
  : NValues(0), Is_tranposed(false), Is_empty(true), Delete_vector(true)
 { }
 
 // ===================================================================
 // Constructor to create an n size zero vector
 // ===================================================================
 template<class T>
 ACVector<T>::ACVector(const unsigned long n)
  : NValues(n), Is_tranposed(false), Is_empty(true), Delete_vector(true)
 { }
 
 // ===================================================================
 // Destructor
 // ===================================================================
 template<class T>
 ACVector<T>::~ACVector()
 { }
 
}
