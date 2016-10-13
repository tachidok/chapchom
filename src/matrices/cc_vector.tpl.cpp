// IN THIS FILE: Implementation of a concrete class to represent
// vectors. This is the simplest implementation

#include "cc_vector.tpl.h"

namespace chapchom
{

 // ===================================================================
 // Empty constructor
 // ===================================================================
 template<class T>
 CCVector<T>::CCVector() 
  : ACVector<T>()
 {
  // Delete any data in memory
  clean_up();
 }
 
 // ===================================================================
 // Constructor to create an n size zero vector (we assume vectors
 // are created as column vectors, if you need a row vector then
 // pass "true" as the second parameter).
 // ===================================================================
 template<class T>
 CCVector<T>::CCVector(const unsigned long n, bool is_transposed)
  : ACVector<T>(n, is_transposed)
 {
  // Delete any data in memory
  clean_up();
 }
 
 // ===================================================================
 // Constructor where we pass the data for the vector of size n
 // ===================================================================
 template<class T>
 CCVector<T>::CCVector(T *vector_pt, const unsigned long n,
                       bool is_transposed)
  : ACVector<T>(n, is_transposed)
 {
  // Copy the data from the input vector to the Vector_pt vector
  set_vector(vector_pt, n);
 }
 
 // ===================================================================
 // Copy constructor
 // ===================================================================
 template<class T>
 CCVector<T>::CCVector(const CCVector<T> &copy)
  : ACVector<T>(copy.nvalues(), copy.is_transposed())
 {
  // Copy the data from the input vector to the Vector_pt vector
  set_vector(copy.vector_pt(), this->NValues);
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class T>
 CCVector<T>::~CCVector()
 {
  // Deallocate memory
  clean_up();
 }
 
 // ===================================================================
 // Assignment operator
 // ===================================================================
 template<class T>
 CCVector<T>& CCVector<T>::operator=(const CCVector<T> &source_vector)
 {
  // Clean-up and set values
  set_vector(source_vector.vector_pt(), source_vector.nvalues());
  // Set the transposed status
  set_transpose(source_vector.is_transposed());
  // Return this (de-referenced pointer)
  return *this;
  
 }
 
 // ===================================================================
 // += operator
 // ===================================================================
 template<class T>
 CCVector<T>& CCVector<T>::operator+=(const CCVector<T> &vector)
 {  
  // Call the method to perform the addition
  add_vector(vector, *this);
  // Return the solution vector
  return *this;
 }
 
 // ===================================================================
 // -= operator
 // ===================================================================
 template<class T>
 CCVector<T>& CCVector<T>::operator-=(const CCVector<T> &vector)
 {
  // Call the method to perform the operation
  substract_vector(vector, *this);
  // Return the solution vector
  return *this; 
 }
 
 // ===================================================================
 // Add operator
 // ===================================================================
 template<class T>
 CCVector<T> CCVector<T>::operator+(const CCVector<T> &vector)
 {
  // Create a zero vector where to store the result
  CCVector<T> solution(this->NValues);
  // Call the method to perform the addition
  add_vector(vector, solution);
  // Return the solution vector
  return solution;
 }
 
 // ===================================================================
 // Substraction operator
 // ===================================================================
 template<class T>
 CCVector<T> CCVector<T>::operator-(const CCVector<T> &vector)
 {
  // Create a zero vector where to store the result
  CCVector<T> solution(this->NValues);
  // Call the method to perform the operation
  substract_vector(vector, solution);
  return solution;
 }
 
 //HERE HERE RE-IMPLEMENT TO RETURN A MATRIX USING THE OPERATION FOR MATRIX MULTIPLICATION
 
 // ===================================================================
 // Multiplication operator (it returns a matrix with the
 // corresponding size, if you require a dot product operation use the
 // dot() method instead
 // ===================================================================
 template<class T>
 CCMatrix<T> CCVector<T>::operator*(const CCVector<T> &vector)
 {
  // Create two matrices, one from each vector
  CCMatrix<T> left_matrix(*this);
  CCMatrix<T> right_matrix(vector);
  // Create a zero vector where to store the result
  CCVector<T> solution(this->NValues);
  // Perform the multiplication
  multiply_matrices(left_matrix,right_matrix, solution);
  // Return the solution vector
  return solution;
 }
 
 // ===================================================================
 // Performs dot product with the current vector
 // ===================================================================
 template<class T>
 T CCVector<T>::dot(const CCVector &right_vector)
 {
  // Check that THIS and the right vector have entries to operate
  // with
  if (this->Is_empty || right_vector.is_empty())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the vectors to operate with has no entries\n"
                  << "this->Is_empty = "
                  << this->Is_empty << "\n"
                  << "right_vector.is_empty() = "
                  << right_vector.is_empty() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vectors allow the operation
  const unsigned long n_values_right_vector = right_vector.nvalues();
  const unsigned long n_values_this_vector = this->nvalues();
  if (n_values_this_vector != n_values_right_vector)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the vectors is not the same:\n"
                  << "dim(right_vector) = (" << n_values_right_vector << ")\n"
                  << "dim(this) = (" << n_values_this_vector << ")\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check that THIS vector is a row vector and that the right vector
  // is a column vector
  if (this->is_transposed())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "THIS vector should be a row vector\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  if (!right_vector.is_transposed())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The right vector should be a column vector\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the vector pointer of the right vector
  T *right_vector_pt = right_vector.vector_pt();
  
  // Store the dot product of the vectors
  T dot_product = 0.0;
  
  // Compute the dot product
  for (unsigned long i = 0; i < n_values_this_vector; i++)
   {
    dot_product+= Vector_pt[i] * right_vector_pt[i];
   }
  
  return dot_product;
  
 }
 
 // ===================================================================
 // Transforms the input vector to a vector class type (virtual such
 // that each derived class has to implement it)
 // ===================================================================
 template<class T>
 void CCVector<T>::set_vector(const T *vector_pt,
                              const unsigned long n)
 {
  // Clean any possible previously allocated memory
  clean_up();
  
  // Set the number of values
  this->NValues = n;
  
  // Allocate memory for the vector
  Vector_pt = new T[n];
  
  // Copy the vector (an element by element copy, uff!!)
  std::memcpy(Vector_pt, vector_pt, n*sizeof(T));
  
  // Mark the vector as having elements
  this->Is_empty = false;
  
 }
 
 // ===================================================================
 // Clean up for any dynamically stored data
 // ===================================================================
 template<class T>
 void CCVector<T>::clean_up()
 {
  // Check whether the Vector has elements
  if (!this->Is_empty)
   {
    // Mark the vector as deleteable
    this->Delete_vector = true;
    // Free the memory allocated for the vector
    free_memory_for_vector();
   }
  else // if empty
   {
    // Set the pointer of the vector to NULL
    Vector_pt = 0;
   }
  
 }
 
 // ===================================================================
 // Free allocated memory for vector
 // ===================================================================
 template<class T>
 void CCVector<T>::free_memory_for_vector()
 {
  // Is the vector allowed for deletion. If this method is called from
  // an external source we need to check whether the vector has been
  // marked for deletion
  if (this->Delete_vector)
   {
    delete Vector_pt;
    Vector_pt = 0; 
    
    // Mark the vector as empty
    this->Is_empty=true;
    
   } // if (Delete_vector)
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You are trying to free the memory of a vector that is\n"
                  << "not marked as deletable" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
 
 }

 // ===================================================================
 // Performs sum of vectors
 // ===================================================================
 template<class T>
 void CCVector<T>::add_vector(const CCVector<T> &vector,
                              CCVector<T> &solution_vector)
 {
  // Check that THIS and the other vector have entries to operate with
  if (this->Is_empty || vector.is_empty())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the vectors to operate with has no entries\n"
                  << "this->Is_empty = "
                  << this->Is_empty << "\n"
                  << "vector.is_empty() = "
                  << vector.is_empty() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vectors are the same
  const unsigned long n_values_input_vector = vector.nvalues();
  const unsigned long n_values_this_vector = this->nvalues();
  if (n_values_this_vector != n_values_input_vector)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the vectors is not the same:\n"
                  << "dim(vector) = (" << n_values_input_vector << ")\n"
                  << "dim(this) = (" << n_values_this_vector << ")\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check that both vectors have the same transposed status (both are
  // columns vectors or both are row vectors)
  if (this->is_transposed() != vector.is_transposed())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Both vectors MUST BE either column or row vectors\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the vector pointer of the solution vector
  T *solution_vector_pt = solution_vector.vector_pt();
  
  // Check whether the solution vector has allocated memory, otherwise
  // allocate it here!!!
  if (solution_vector.is_empty())
   {
    // Create a zero vector with the given size to allocate memory
    solution_vector.create_zero_vector();
    // Get the new vector pointer
    solution_vector_pt = solution_vector.vector_pt();
   }
  
  // Get the vector pointer of the input vector
  T *vector_pt = vector.vector_pt();
  // Perform the addition
  for (unsigned long i = 0; i < n_values_this_vector; i++)
   {
    solution_vector_pt[i] = Vector_pt[i] + vector_pt[i];
   }
  
 }
 
 // ===================================================================
 // Performs substraction of vectors
 // ===================================================================
 template<class T>
 void CCVector<T>::substract_vector(const CCVector<T> &vector,
                                    CCVector<T> &solution_vector)
 {
  // Check that THIS and the other vector have entries to operate with
  if (this->Is_empty || vector.is_empty())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the vectors to operate with has no entries\n"
                  << "this->Is_empty = "
                  << this->Is_empty << "\n"
                  << "vector.is_empty() = "
                  << vector.is_empty() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vectors are the same
  const unsigned long n_values_input_vector = vector.nvalues();
  const unsigned long n_values_this_vector = this->nvalues();
  if (n_values_this_vector != n_values_input_vector)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the vectors is not the same:\n"
                  << "dim(vector) = (" << n_values_input_vector << ")\n"
                  << "dim(this) = (" << n_values_this_vector << ")\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check that both vectors have the same transposed status (both are
  // columns vectors or both are row vectors)
  if (this->is_transposed() != vector.is_transposed())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Both vectors MUST BE either column or row vectors\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the vector pointer of the solution vector
  T *solution_vector_pt = solution_vector.vector_pt();
  
  // Check whether the solution vector has allocated memory, otherwise
  // allocate it here!!!
  if (solution_vector.is_empty())
   {
    // Create a zero vector with the given size to allocate memory
    solution_vector.create_zero_vector();
    // Get the new vector pointer
    solution_vector_pt = solution_vector.vector_pt();
   }
  
  // Get the vector pointer of the input vector
  T *vector_pt = vector.vector_pt();
  // Perform the addition
  for (unsigned long i = 0; i < n_values_this_vector; i++)
   {
    solution_vector_pt[i] = Vector_pt[i] - vector_pt[i];
   }
  
 }
 
 // ===================================================================
 // Performs multiplication of vectors (element by element)
 // ===================================================================
 template<class T>
 void CCVector<T>::
 multiply_element_by_element_vector(const CCVector<T> &vector,
                                    CCVector<T> &solution_vector)
 {
  // Check that THIS and the other vector have entries to operate with
  if (this->Is_empty || vector.is_empty())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the vectors to operate with has no entries\n"
                  << "this->Is_empty = "
                  << this->Is_empty << "\n"
                  << "vector.is_empty() = "
                  << vector.is_empty() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vectors are the same
  const unsigned long n_values_input_vector = vector.nvalues();
  const unsigned long n_values_this_vector = this->nvalues();
  if (n_values_this_vector != n_values_input_vector)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the vectors is not the same:\n"
                  << "dim(vector) = (" << n_values_input_vector << ")\n"
                  << "dim(this) = (" << n_values_this_vector << ")\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check that both vectors have the same transposed status (both are
  // columns vectors or both are row vectors)
  if (this->is_transposed() != vector.is_transposed())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Both vectors MUST BE either column or row vectors\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the vector pointer of the solution vector
  T *solution_vector_pt = solution_vector.vector_pt();
  
  // Check whether the solution vector has allocated memory, otherwise
  // allocate it here!!!
  if (solution_vector.is_empty())
   {
    // Create a zero vector with the given size to allocate memory
    solution_vector.create_zero_vector();
    // Get the new vector pointer
    solution_vector_pt = solution_vector.vector_pt();
   }
  
  // Get the vector pointer of the input vector
  T *vector_pt = vector.vector_pt();
  // Perform the addition
  for (unsigned long i = 0; i < n_values_this_vector; i++)
   {
    solution_vector_pt[i] = Vector_pt[i] * vector_pt[i];
   }
  
 }
 
 // ===================================================================
 // Computes the transpose and store in the solution vector
 // ===================================================================
 template<class T>
 void CCVector<T>::transpose(CCVector<T> &transposed_vector)
 {
  // Check that THIS vector has entries to operate with
  if (this->Is_empty)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "THIS vector has no entries to operate with\n"
                  << "this->Is_empty = "
                  << this->Is_empty << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Copy the vector into the tranposed vector
  transposed_vector = (*this);
  // .. and mark it as transposed
  transposed_vector.transpose();
 }
 
 // ===================================================================
 // Get the specified value from the vector (read-only)
 // ===================================================================
 template<class T>
 const T CCVector<T>::value(const unsigned long i) const
 {
  // TODO: Julio - Implement range check access
  // Return the value at position i
  return Vector_pt[i];
 }
 
 // ===================================================================
 // Set values in the vector (write version)
 // ===================================================================
 template<class T>
 T &CCVector<T>::value(const unsigned long i)
 {
  // TODO: Julio - Implement range check access
  // Return the value at row i and column j
  return Vector_pt[i];
 }

 // ===================================================================
 // Output the vector
 // ===================================================================
 template<class T>
 void CCVector<T>::output(bool output_indexes) const
 {
  if (this->Is_empty)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The vector is empty" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  else
   {
    // Check whether we should output the indexes
    if (output_indexes)
     {
      for (unsigned long i = 0; i < this->NValues; i++)
       {
        std::cout << "(" << i << "): " << Vector_pt[i]
                  << std::endl; 
       } // for (i < this->NValues)
     } // if (output_indexes)
    else
     {
      for (unsigned long i = 0; i < this->NValues; i++)
       {
        std::cout << Vector_pt[i] << " ";
       } // for (i < this->NValues)
      std::cout << std::endl;
     } // else if (output_indexes)
    
   }
  
 }
 
 // ===================================================================
 // Output the vector
 // ===================================================================
 template<class T>
 void CCVector<T>::output(std::ofstream &outfile, bool output_indexes) const
 {
  if (this->Is_empty)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The vector is empty" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  else
   {
    // Check whether we should output the indexes
    if (output_indexes)
     {
      for (unsigned long i = 0; i < this->NValues; i++)
       {
        outfile << "(" << i << "): " << Vector_pt[i]
                << std::endl; 
       } // for (i < this->NValues)
     } // if (output_indexes)
    else
     {
      for (unsigned long i = 0; i < this->NValues; i++)
       {
        outfile << Vector_pt[i] << " ";
       } // for (i < this->NValues)
      outfile << std::endl;
     } // else if (output_indexes)
    
   }
  
 }
 
 // ===================================================================
 // Creates a zero vector with the already defined number of entries
 // (allocates memory to store entries of the matrix)
 // ===================================================================
 template<class T>
 void CCVector<T>::create_zero_vector()
 {
  // Delete any data in memory
  clean_up();
  
  // Allocate memory for the vector
  Vector_pt = new T[this->NValues];
  
  // Mark the vector as having something
  this->Is_empty=false;  
 }
 
 // ================================================================
 // Extra methods to work with vectors, we do not need them to be
 // friends of the class since all their operations are performed
 // using the class methods
 // ================================================================
 
 // ================================================================
 // Dot product of vectors
 // ================================================================
 template<class T>
 T dot_vectors(const CCVector<T> &left_vector, const CCVector<T> &right_vector)
 {
  // Check that the left and the right vectors have entries to operate
  // with
  if (left_vector.is_empty() || right_vector.is_empty())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the vectors to operate with has no entries\n"
                  << "left_vector.is_empty() = "
                  << left_vector.is_empty() << "\n"
                  << "right_vector.is_empty() = "
                  << right_vector.is_empty() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vectors allow the operation
  const unsigned long n_values_left_vector = left_vector.nvalues();
  const unsigned long n_values_right_vector = right_vector.nvalues();
  if (n_values_left_vector != n_values_right_vector)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the vectors is not the same:\n"
                  << "dim(left_vector) = (" << n_values_left_vector << ")\n"
                  << "dim(right_vector) = (" << n_values_right_vector << ")\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check that the left vector is a row vector and that the right
  // vector is a column vector
  if (left_vector.transposed())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The left vector should be a row vector\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  if (!right_vector.is_transposed())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The right vector should be a column vector\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the vector pointer of the left vector
  T *left_vector_pt = left_vector.vector_pt();
  // Get the vector pointer of the right vector
  T *right_vector_pt = right_vector.vector_pt();
  
  // Store the dot product of the vectors
  T dot_product = 0.0;
  
  // Compute the dot product
  for (unsigned long i = 0; i < n_values_left_vector; i++)
   {
    dot_product+= left_vector_pt[i] * right_vector_pt[i];
   }
  
  return dot_product;
  
 }

 // ================================================================
 // Addition of vectors
 // ================================================================
 template<class T>
 void add_vectors(const CCVector<T> &vector_one,
                  const CCVector<T> &vector_two,
                  CCVector<T> &solution_vector)
 {
  // Check that the vectors have entries to operate with
  if (vector_one.is_empty() || vector_two.is_empty())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the vectors to operate with has no entries\n"
                  << "vector_one.is_empty() = "
                  << vector_one.is_empty() << "\n"
                  << "vector_two.is_empty() = "
                  << vector_two.is_empty() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vectors are the same
  const unsigned long n_values_vector_one = vector_one.nvalues();
  const unsigned long n_values_vector_two = vector_two.nvalues();
  if (n_values_vector_one != n_values_vector_two)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the vectors is not the same:\n"
                  << "dim(vector_one) = (" << n_values_vector_one << ")\n"
                  << "dim(vector_two) = (" << n_values_vector_two << ")\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check that both vectors have the same transposed status (both are
  // columns vectors or both are row vectors)
  if (vector_one.is_transposed() != vector_two.is_transposed())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Both vectors MUST BE either column or row vectors\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the vector pointer of the solution vector
  T *solution_vector_pt = solution_vector.vector_pt();
  
  // Check whether the solution vector has allocated memory, otherwise
  // allocate it here!!!
  if (solution_vector.is_empty())
   {
    // Create a zero vector with the given size to allocate memory
    solution_vector.create_zero_vector();
    // Get the new vector pointer
    solution_vector_pt = solution_vector.vector_pt();
   }
  
  // Get the vector pointer of the vector one
  T *vector_one_pt = vector_one.vector_pt();
  // Get the vector pointer of the vector two
  T *vector_two_pt = vector_two.vector_pt();
  
  // Perform the addition
  for (unsigned long i = 0; i < n_values_vector_one; i++)
   {
    solution_vector_pt[i] = vector_one_pt[i] + vector_two_pt[i];
   }
  
 }

 // ================================================================
 // Substraction of vectors
 // ================================================================
 template<class T>
 void substract_vectors(const CCVector<T> &vector_one,
                        const CCVector<T> &vector_two,
                        CCVector<T> &solution_vector)
 {
  // Check that the vectors have entries to operate with
  if (vector_one.is_empty() || vector_two.is_empty())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the vectors to operate with has no entries\n"
                  << "vector_one.is_empty() = "
                  << vector_one.is_empty() << "\n"
                  << "vector_two.is_empty() = "
                  << vector_two.is_empty() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vectors are the same
  const unsigned long n_values_vector_one = vector_one.nvalues();
  const unsigned long n_values_vector_two = vector_two.nvalues();
  if (n_values_vector_one != n_values_vector_two)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the vectors is not the same:\n"
                  << "dim(vector_one) = (" << n_values_vector_one << ")\n"
                  << "dim(vector_two) = (" << n_values_vector_two << ")\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check that both vectors have the same transposed status (both are
  // columns vectors or both are row vectors)
  if (vector_one.is_transposed() != vector_two.is_transposed())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Both vectors MUST BE either column or row vectors\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the vector pointer of the solution vector
  T *solution_vector_pt = solution_vector.vector_pt();
  
  // Check whether the solution vector has allocated memory, otherwise
  // allocate it here!!!
  if (solution_vector.is_empty())
   {
    // Create a zero vector with the given size to allocate memory
    solution_vector.create_zero_vector();
    // Get the new vector pointer
    solution_vector_pt = solution_vector.vector_pt();
   }
  
  // Get the vector pointer of the vector one
  T *vector_one_pt = vector_one.vector_pt();
  // Get the vector pointer of the vector two
  T *vector_two_pt = vector_two.vector_pt();
  
  // Perform the substraction of vectors
  for (unsigned long i = 0; i < n_values_vector_one; i++)
   {
    solution_vector_pt[i] = vector_one_pt[i] - vector_two_pt[i];
   }
  
 }

 // ================================================================
 // Performs multiplication of vectors (one by one entries)
 // ================================================================
 template<class T>
 void multiply_element_by_element_vectors(const CCVector<T> &vector_one,
                                          const CCVector<T> &vector_two,
                                          CCVector<T> &solution_vector)
 {
  // Check that the vectors have entries to operate with
  if (vector_one.is_empty() || vector_two.is_empty())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the vectors to operate with has no entries\n"
                  << "vector_one.is_empty() = "
                  << vector_one.is_empty() << "\n"
                  << "vector_two.is_empty() = "
                  << vector_two.is_empty() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vectors are the same
  const unsigned long n_values_vector_one = vector_one.nvalues();
  const unsigned long n_values_vector_two = vector_two.nvalues();
  if (n_values_vector_one != n_values_vector_two)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the vectors is not the same:\n"
                  << "dim(vector_one) = (" << n_values_vector_one << ")\n"
                  << "dim(vector_two) = (" << n_values_vector_two << ")\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check that both vectors have the same transposed status (both are
  // columns vectors or both are row vectors)
  if (vector_one.is_transposed() != vector_two.is_transposed())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Both vectors MUST BE either column or row vectors\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the vector pointer of the solution vector
  T *solution_vector_pt = solution_vector.vector_pt();
  
  // Check whether the solution vector has allocated memory, otherwise
  // allocate it here!!!
  if (solution_vector.is_empty())
   {
    // Create a zero vector with the given size to allocate memory
    solution_vector.create_zero_vector();
    // Get the new vector pointer
    solution_vector_pt = solution_vector.vector_pt();
   }
  
  // Get the vector pointer of the vector one
  T *vector_one_pt = vector_one.vector_pt();
  // Get the vector pointer of the vector two
  T *vector_two_pt = vector_two.vector_pt();
  
  // Perform the substraction of vectors
  for (unsigned long i = 0; i < n_values_vector_one; i++)
   {
    solution_vector_pt[i] = vector_one_pt[i] * vector_two_pt[i];
   }
  
 }
 
}
