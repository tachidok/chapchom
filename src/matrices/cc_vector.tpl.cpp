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
 // pass "false" as the second parameter)
 // ===================================================================
 template<class T>
 CCVector<T>::CCVector(const unsigned long n, bool is_column_vector)
  : ACVector<T>(n, is_column_vector)
 {
  // Delete any data in memory
  clean_up();
 }
 
 // ===================================================================
 // Constructor where we pass the data for the vector of size n
 // ===================================================================
 template<class T>
 CCVector<T>::CCVector(T *vector_pt, const unsigned long n,
                       bool is_column_vector)
  : ACVector<T>(n, is_column_vector)
 {
  // Copy the data from the input vector to the Vector_pt vector
  set_vector(vector_pt, n, is_column_vector);
 }
 
 // ===================================================================
 // Copy constructor
 // ===================================================================
 template<class T>
 CCVector<T>::CCVector(const CCVector<T> &copy)
  : ACVector<T>(copy.n_values(), copy.is_column_vector())
 {
  // Copy the data from the input vector to the Vector_pt vector
  set_vector(copy.vector_pt(), this->NValues, copy.is_column_vector());
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
  set_vector(source_vector.vector_pt(),
             source_vector.n_values(),
             source_vector.is_column_vector());
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
  // Store the size of both vectors to create a solution matrix with
  // the corresponding sizes
  // (First dimension for the left vector)
  long unsigned n_values_left_vector = this->NValues;
  if (!vector.is_column_vector())
   {
    n_values_left_vector = 1;
   }
  // (Second dimension for the right vector)
  long unsigned n_values_right_vector = vector.n_values();
  if (vector.is_column_vector())
   {
    n_values_right_vector = 1;
   }
  // Create a zero matrix where to store the result
  CCMatrix<T> solution(n_values_left_vector, n_values_right_vector);
  // Perform the multiplication (this method is in charge of verifying
  // whether the matrices fulfill the requirements for matrix
  // multiplication)
  multiply_matrices(left_matrix, right_matrix, solution);
  // Return the solution matrix
  return solution;
 }
 
 // ===================================================================
 // Performs dot product with the current vector
 // ===================================================================
 template<class T>
 T CCVector<T>::dot(const CCVector &right_vector)
 {
  // Check that THIS and the right vector have memory allocated
  if (!this->Is_own_memory_allocated || !right_vector.is_own_memory_allocated())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the vectors to operate with has no memory allocated\n"
                  << "this->Is_own_memory_allocated = "
                  << this->Is_own_memory_allocated << "\n"
                  << "right_vector.is_own_memory_allocated() = "
                  << right_vector.is_own_memory_allocated() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vectors allow the operation
  const unsigned long n_values_right_vector = right_vector.n_values();
  const unsigned long n_values_this_vector = this->n_values();
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
  if (this->is_column_vector())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "THIS vector should be a row vector\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  if (!right_vector.is_column_vector())
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
                              const unsigned long n,
                              bool is_column_vector)
 {
  // Clean any possible previously allocated memory
  clean_up();
  
  // Set the number of values
  this->NValues = n;
  
  // Allocate memory for the vector
  Vector_pt = new T[n];
  
  // Mark the vector as allocated its own memory
  this->Is_own_memory_allocated = true;
  
  // Copy the vector (an element by element copy, uff!!)
  std::memcpy(Vector_pt, vector_pt, n*sizeof(T));
  
  // Set the transposed status
  this->set_as_column_vector(is_column_vector);
  
 }
 
 // ===================================================================
 // Clean up for any dynamically stored data
 // ===================================================================
 template<class T>
 void CCVector<T>::clean_up()
 {
  // Check whether the Vector allocated its own memory
  if (this->Is_own_memory_allocated)
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
    delete [] Vector_pt;
    Vector_pt = 0; 
    
    // Mark the vector as not having memory allocated
    this->Is_own_memory_allocated=false;
    
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
  // Check that THIS and the other vector have memory allocated
  if (!this->Is_own_memory_allocated || !vector.is_own_memory_allocated())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the vectors to operate with has no memory allocated\n"
                  << "this->Is_own_memory_allocated = "
                  << this->Is_own_memory_allocated << "\n"
                  << "vector.is_own_memory_allocated() = "
                  << vector.is_own_memory_allocated() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vectors are the same
  const unsigned long n_values_input_vector = vector.n_values();
  const unsigned long n_values_this_vector = this->n_values();
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
  
  // Check that both vectors have the same column vector status (both
  // are columns vectors or both are row vectors)
  if (this->is_column_vector() != vector.is_column_vector())
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
  if (!solution_vector.is_own_memory_allocated())
   {
    // Allocate memory for the vector
    solution_vector.allocate_memory();
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
  // Check that THIS and the other vector have no memory allocated
  if (!this->Is_own_memory_allocated || !vector.is_own_memory_allocated())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the vectors to operate with has no memory allocated\n"
                  << "this->Is_own_memory_allocated = "
                  << this->Is_own_memory_allocated << "\n"
                  << "vector.is_own_memory_allocated() = "
                  << vector.is_own_memory_allocated() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vectors are the same
  const unsigned long n_values_input_vector = vector.n_values();
  const unsigned long n_values_this_vector = this->n_values();
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
  if (this->is_column_vector() != vector.is_column_vector())
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
  if (!solution_vector.is_own_memory_allocated())
   {
    // Allocate memory for the vector
    solution_vector.allocate_memory();
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
  // Check that THIS and the other vector have memory allocated
  if (!this->Is_own_memory_allocated || !vector.is_own_memory_allocated())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the vectors to operate with has no memory allocated\n"
                  << "this->Is_own_memory_allocated = "
                  << this->Is_own_memory_allocated << "\n"
                  << "vector.is_own_memory_allocated() = "
                  << vector.is_own_memory_allocated() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vectors are the same
  const unsigned long n_values_input_vector = vector.n_values();
  const unsigned long n_values_this_vector = this->n_values();
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
  if (this->is_column_vector() != vector.is_column_vector())
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
  if (!solution_vector.is_own_memory_allocated())
   {
    // Allocate memory for the vector
    solution_vector.allocate_memory();
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
 // Computes the transpose and store in the transposed vector
 // ===================================================================
 template<class T>
 void CCVector<T>::transpose(CCVector<T> &transposed_vector)
 {
  // Check that THIS vector has memory allocated
  if (!this->Is_own_memory_allocated)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "THIS vector has no memory allocated\n"
                  << "this->Is_own_memory_allocated = "
                  << this->Is_own_memory_allocated << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Copy the vector into the tranposed vector
  transposed_vector = (*this);
  // Get the current "column vector" status of the vector and set the
  // transposed status of the new vector
  transposed_vector.set_as_column_vector(~(this->Is_column_vector));
 }
 
 // ===================================================================
 // Get the specified value from the vector (read-only)
 // ===================================================================
 template<class T>
 const T CCVector<T>::value(const unsigned long i) const
 {
#ifdef CHAPCHOM_RANGE_CHECK
  if (!(this->is_own_memory_allocated()))
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The vector has no memory allocated"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  if (i > this->n_values())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The entry you are trying to access is out of range\n"
                  << "Number of values: " << this->n_values() << std::endl
                  << "Requested entry: " << i << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   } 
#endif // #ifdef CHAPCHOM_RANGE_CHECK
  // Return the value at position i
  return Vector_pt[i];
 }
 
 // ===================================================================
 // Set values in the vector (write version)
 // ===================================================================
 template<class T>
 T &CCVector<T>::value(const unsigned long i)
 {
#ifdef CHAPCHOM_RANGE_CHECK
  if (!(this->is_own_memory_allocated()))
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The vector has no memory allocated"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  if (i > this->n_values())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The entry you are trying to access is out of range\n"
                  << "Number of values: " << this->n_values() << std::endl
                  << "Requested entry: " << i << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   } 
#endif // #ifdef CHAPCHOM_RANGE_CHECK
  // Return the value at row i and column j
  return Vector_pt[i];
 }

 // ===================================================================
 // Output the vector
 // ===================================================================
 template<class T>
 void CCVector<T>::output(bool output_indexes) const
 {
  if (!this->Is_own_memory_allocated)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The vector has no memory allocated. It is empty" << std::endl;
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
        std::cout << "(" << i << "): " << value(i)
                  << std::endl; 
       } // for (i < this->NValues)
     } // if (output_indexes)
    else
     {
      for (unsigned long i = 0; i < this->NValues; i++)
       {
        std::cout << value(i) << " ";
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
  if (!this->Is_own_memory_allocated)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The vector has no memory allocated. It is empty" << std::endl;
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
        outfile << "(" << i << "): " << value(i)
                << std::endl; 
       } // for (i < this->NValues)
     } // if (output_indexes)
    else
     {
      for (unsigned long i = 0; i < this->NValues; i++)
       {
        outfile << value(i) << " ";
       } // for (i < this->NValues)
      outfile << std::endl;
     } // else if (output_indexes)
   }
  
 }

 // ===================================================================
 // Computes the norm-1 of the vector
 // ===================================================================
 template<class T>
 T CCVector<T>::norm_1()
 {
  // Sum
  T sum = 0.0;
  // Check whether the vector has memory allocated
  if (this->Is_own_memory_allocated)
   {
    // Compute the norm
    for (unsigned long i = 0; i < this->NValues; i++)
     {
      sum+= Vector_pt[i];
     }
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "We can not compute the norm of a vector with no memory allocated\n"
                  << "this->Is_own_memory_allocated = "
                  << this->Is_own_memory_allocated << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  return sum;
  
 }
 
 // ===================================================================
 // Computes the norm-2 of the vector
 // ===================================================================
 template<class T>
 T CCVector<T>::norm_2()
 {
  // Sum
  T sum = 0.0;
  // Check whether the vector has memory allocated
  if (this->Is_own_memory_allocated)
   {
    // Compute the norm 2
    for (unsigned long i = 0; i < this->NValues; i++)
     {
      sum+= (Vector_pt[i]*Vector_pt[i]);
     }
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "We can not compute the norm of a vector with no memory allocated\n"
                  << "this->Is_own_memory_allocated = "
                  << this->Is_own_memory_allocated << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  return sqrt(sum);
  
 }

 // ===================================================================
 // Computes the maximum value (infinite norm)
 // ===================================================================
 template<class T>
 T CCVector<T>::max()
 {
  // Maximum
  T max = 0.0;
  // Check whether the vector has memory allocated
  if (this->Is_own_memory_allocated)
   {
    // Initialise the maximum with the first value
    max = Vector_pt[0];
    // Compute the norm
    for (unsigned long i = 1; i < this->NValues; i++)
     {
      if (Vector_pt[i] > max)
       max = Vector_pt[i];
     }
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "We can not compute the maximum of a vector with no memory allocated\n"
                  << "this->Is_own_memory_allocated = "
                  << this->Is_own_memory_allocated << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  return max;
  
 }
 
 // ===================================================================
 // Allows to create a vector with the given size but with no data
 // ===================================================================
 template<class T>
 void CCVector<T>::allocate_memory(const unsigned long n)
 {
  // Clean any possibly stored data
  clean_up();
  
  // Set the number of rows and columns of the matrix
  this->NValues = n;
  
  // Allocate memory
  allocate_memory();
 }
 
 // ===================================================================
 // Allocates memory to store entries of the vector
 // ===================================================================
 template<class T>
 void CCVector<T>::allocate_memory()
 {
  // Delete any data in memory
  clean_up();
  
  // Allocate memory for the vector
  Vector_pt = new T[this->NValues];
  
  // Mark the vector as allocated its own memory
  this->Is_own_memory_allocated=true;
 }
 
 // ===================================================================
 // Fills the vector with zeroes
 // ===================================================================
 template<class T>
 void CCVector<T>::fill_with_zeroes()
 {
  // Check that the vector has memory allocated
  if (this->Is_own_memory_allocated)
   {
    // Fill the vector with zeroes
    std::memset(Vector_pt, 0, this->NValues*sizeof(T));
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The vector has no memory allocated\n"
                  << "this->Is_own_memory_allocated = "
                  << this->Is_own_memory_allocated << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);    
   }
  
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
  // Check that the left and the right vectors have memory allocated
  if (!left_vector.is_own_memory_allocated() || !right_vector.is_own_memory_allocated())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the vectors to operate with has no memory allocated\n"
                  << "left_vector.is_own_memory_allocated() = "
                  << left_vector.is_own_memory_allocated() << "\n"
                  << "right_vector.is_own_memory_allocated() = "
                  << right_vector.is_own_memory_allocated() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vectors allow the operation
  const unsigned long n_values_left_vector = left_vector.n_values();
  const unsigned long n_values_right_vector = right_vector.n_values();
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
  if (left_vector.is_column_vector())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The left vector should be a row vector\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  if (!right_vector.is_column_vector())
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
  // Check that the vectors have memory allocated
  if (!vector_one.is_own_memory_allocated() || !vector_two.is_own_memory_allocated())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the vectors to operate with has no memory allocated\n"
                  << "vector_one.is_own_memory_allocated() = "
                  << vector_one.is_own_memory_allocated() << "\n"
                  << "vector_two.is_own_memory_allocated() = "
                  << vector_two.is_own_memory_allocated() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vectors are the same
  const unsigned long n_values_vector_one = vector_one.n_values();
  const unsigned long n_values_vector_two = vector_two.n_values();
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
  
  // Check that both vectors have the same column vector status (both
  // are columns vectors or both are row vectors)
  if (vector_one.is_column_vector() != vector_two.is_column_vector())
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
  if (!solution_vector.is_own_memory_allocated())
   {
    // Allocate memory for the vector
    solution_vector.allocate_memory();
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
  // Check that the vectors have no memory allocated
  if (!vector_one.is_own_memory_allocated() || !vector_two.is_own_memory_allocated())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the vectors to operate with has no memory allocated\n"
                  << "vector_one.is_own_memory_allocated() = "
                  << vector_one.is_own_memory_allocated() << "\n"
                  << "vector_two.is_own_memory_allocated() = "
                  << vector_two.is_own_memory_allocated() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vectors are the same
  const unsigned long n_values_vector_one = vector_one.n_values();
  const unsigned long n_values_vector_two = vector_two.n_values();
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
  
  // Check that both vectors have the same column vector status (both
  // are columns vectors or both are row vectors)
  if (vector_one.is_column_vector() != vector_two.is_column_vector())
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
  if (!solution_vector.is_own_memory_allocated())
   {
    // Allocate memory for the vector
    solution_vector.allocate_memory();
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
  // Check that the vectors have memory allocated
  if (!vector_one.is_own_memory_allocated() || !vector_two.is_own_memory_allocated())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "One of the vectors to operate with has no memory allocated\n"
                  << "vector_one.is_own_memory_allocated() = "
                  << vector_one.is_own_memory_allocated() << "\n"
                  << "vector_two.is_own_memory_allocated() = "
                  << vector_two.is_own_memory_allocated() << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the dimensions of the vectors are the same
  const unsigned long n_values_vector_one = vector_one.n_values();
  const unsigned long n_values_vector_two = vector_two.n_values();
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
  
  // Check that both vectors have the same column vector status (both
  // are columns vectors or both are row vectors)
  if (vector_one.is_column_vector() != vector_two.is_column_vector())
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
  if (!solution_vector.is_own_memory_allocated())
   {
    // Allocate memory for the vector
    solution_vector.allocate_memory();
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
