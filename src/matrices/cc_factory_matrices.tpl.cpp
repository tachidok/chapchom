#include "cc_factory_matrices.tpl.h"

namespace chapchom
{

 // ===================================================================
 /// Empty constructor
 // ===================================================================
 template<class T>
 CCFactoryMatrices<T>::CCFactoryMatrices()
 { 

 }

 // ===================================================================
 /// Empty destructor
 // ===================================================================
 template<class T>
 CCFactoryMatrices<T>::~CCFactoryMatrices()
 { 

 }
 
 // ===================================================================
 /// Returns a matrix pointer (based on compilation options)
 // ===================================================================
 template<class T>
 ACMatrix<T>* CCFactoryMatrices<T>::create_matrix()
 {
  // ------------------------------------------------------
  // Check what matrix type we need to create
  // ------------------------------------------------------
#ifdef CHAPCHOM_USES_ARMADILLO
  return new CCMatrixArmadillo<T>();
#else
  return new CCMatrix<T>();
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 }

 // ===================================================================
 /// Returns a matrix pointer (based on compilation options)
 // ===================================================================
 ACMatrix<T>* create_matrix(const unsigned long m, const unsigned long n);
 {
  
 }
 
 // ===================================================================
 /// Returns the specified matrix pointer
 // ===================================================================
 template<class T>
 ACMatrix<T>* CCFactoryMatrices<T>::create_matrix(std::string matrix_type_name)
 {
  // Get the string and change it to lower case 
  std::transform(matrix_type_name.begin(), matrix_type_name.end(),
                 matrix_type_name.begin(), ::tolower);
  
  // ------------------------------------------------------
  // Check what matrix type we need to create
  // ------------------------------------------------------
  // Default type
  if (matrix_type_name.compare("default")==0)
   {
    return new CCMatrix<T>();
   }
  // Armadillo type
  else if (matrix_type_name.compare("armadillo")==0)
   {
    return new CCMatrixArmadillo<T>();
   }
  else
   {
    std::ostringstream error_message;
    error_message << "The matrix time you want to use is not implemented yet.\n"
                  << "Please implement it yourself or select from the availables ones\n\n"
                  << "- Default (default)\n"
                  << "- Armadillo matrices (armadillo) - only supported when armadillo library is enabled\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
 }

 // ===================================================================
 /// Returns the specified matrix pointer
 // ===================================================================
 ACMatrix<T>* create_matrix(std::string matrix_type_name, const unsigned long m, const unsigned long n)
 {
  
 }
 
 // ===================================================================
 /// Returns a vector pointer (based on compilation options)
 // ===================================================================
 template<class T>
 ACVector<T>* CCFactoryMatrices<T>::create_vector()
 {
#ifdef CHAPCHOM_USES_ARMADILLO
  return new CCVectorArmadillo<T>();
#else
  return new CCVector<T>();
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 }

 // ===================================================================
 /// Returns a vector pointer (based on compilation options)
 // ===================================================================
 ACVector<T>* create_vector(const unsigned long n, bool is_column_vector = true)
 {
  
 }
 
 // ===================================================================
 /// Returns the specified vector pointer
 // ===================================================================
 template<class T>
 ACVector<T>* CCFactoryMatrices<T>::create_vector(std::string vector_type_name)
 {
  // Get the string and change it to lower case 
  std::transform(vector_type_name.begin(), vector_type_name.end(),
                 vector_type_name.begin(), ::tolower);
  
  // ------------------------------------------------------
  // Check what vector type we need to create
  // ------------------------------------------------------
  // Default type
  if (vector_type_name.compare("default")==0)
   {
    return new CCVector<T>();
   }
  // Armadillo type
  else if (vector_type_name.compare("armadillo")==0)
   {
    return new CCVectorArmadillo<T>();
   }
  else
   {
    std::ostringstream error_message;
    error_message << "The vector type you want to use is not implemented yet.\n"
                  << "Please implement it yourself or select from the availables ones\n\n"
                  << "- Default (default)\n"
                  << "- Armadillo matrices (armadillo) - only supported when armadillo library is enabled\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
 }
 
 // ===================================================================
 /// Returns the specified vector pointer
 // ===================================================================
 ACVector<T>* create_vector(std::string vector_type_name, const unsigned long n, bool is_column_vector = true)
 {
  
 }
 
}
