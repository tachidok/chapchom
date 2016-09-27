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
  : NValues(0), Is_transposed(false), Is_empty(true), Delete_vector(true)
 { }
 
 // ===================================================================
 // Constructor to create an n size zero vector
 // ===================================================================
 template<class T>
 ACVector<T>::ACVector(const unsigned long n, bool is_transposed)
  : NValues(n), Is_empty(true), Delete_vector(true),
    Is_transposed(is_transposed)
 { }
 
 // ===================================================================
 // Destructor
 // ===================================================================
 template<class T>
 ACVector<T>::~ACVector()
 { }
 
}
