#ifndef CCFACTORYMATRICES_TPL_H
#define CCFACTORYMATRICES_TPL_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "../matrices/ac_vector.h"
#include "../matrices/ac_matrix.h"

#include "../matrices/cc_vector.h"
#include "../matrices/cc_matrix.h"
#ifdef SCICELLXX_USES_ARMADILLO
#include "../matrices/cc_vector_armadillo.h"
#include "../matrices/cc_matrix_armadillo.h"
#endif // #ifdef SCICELLXX_USES_ARMADILLO

namespace chapchom
{
 
 /// @class CCFactoryMatrices cc_factory_matrices.h
 
 /// This class implements a factory for the instantiation of
 /// matrices, it helps to choose the right matrices types based on
 /// compilation flags
 template<class T>
  class CCFactoryMatrices
  {
   
  public:
   
   /// Empty constructor
   CCFactoryMatrices();
   
   /// Empty destructor
   virtual ~CCFactoryMatrices();
   
   /// Returns a matrix pointer (based on compilation options)
   ACMatrix<T>* create_matrix();
   
   /// Returns a matrix pointer (based on compilation options)
   ACMatrix<T>* create_matrix(const unsigned long m, const unsigned long n);
   
   /// Returns the specified matrix pointer
   ACMatrix<T>* create_matrix(std::string matrix_type_name);
   
   /// Returns the specified matrix pointer
   ACMatrix<T>* create_matrix(std::string matrix_type_name, const unsigned long m, const unsigned long n);
   
   /// Returns a vector pointer (based on compilation options)
   ACVector<T>* create_vector();
   
   /// Returns a vector pointer (based on compilation options)
   ACVector<T>* create_vector(const unsigned long n, bool is_column_vector = true);
   
   /// Returns the specified vector pointer
   ACVector<T>* create_vector(std::string vector_type_name);
   
   /// Returns the specified vector pointer
   ACVector<T>* create_vector(std::string vector_type_name, const unsigned long n, bool is_column_vector = true);
   
  protected:
   
   /// Copy constructor (we do not want this class to be
   /// copiable). Check
   /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   CCFactoryMatrices(const CCFactoryMatrices &copy)
    {
     BrokenCopy::broken_copy("CCFactoryMatrices");
    }
   
   /// Assignment operator (we do not want this class to be
   /// copiable. Check
   /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   void operator=(const CCFactoryMatrices &copy)
    {
     BrokenCopy::broken_assign("CCFactoryMatrices");
    }
   
  };
 
}
 
#endif // #ifndef CCFACTORYMATRICES_TPL_H

