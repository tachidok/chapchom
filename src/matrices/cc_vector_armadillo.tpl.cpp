// IN THIS FILE: The implementation of a concrete class to store and
// work with vector. This implementation makes use of Armadillo's
// library, thus this is only a wrap for Armadillo's methods

#include "cc_vector_armadillo.tpl.h"

namespace chapchom
{

 // ===================================================================
 // Empty constructor
 // ===================================================================
 template<class T>
 CCVectorArmadillo<T>::CCVectorArmadillo() 
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
 CCVectorArmadillo<T>::CCVectorArmadillo(const unsigned long n, bool is_transposed)
  : ACVector<T>(n, is_transposed)
 {
  // Delete any data in memory
  clean_up();

  Arma_vector_pt = new arma::Col<T>(n);
 }
 
 // ===================================================================
 // Constructor where we pass the data for the vector of size n
 // ===================================================================
 template<class T>
 CCVectorArmadillo<T>::CCVectorArmadillo(T *vector_pt, const unsigned long n,
                       bool is_transposed)
  : ACVector<T>(n, is_transposed)
 {
  // Copy the data from the input vector to the Vector_pt vector
  set_vector(vector_pt, n);
 }
 
 // ===================================================================
 // Constructor that creates an Armadillo's vector from a CCVector
 // ===================================================================
 template<class T>
 CCVectorArmadillo<T>::CCVectorArmadillo(CCVector<T> &vector)
 {
  // Get the pointer to the vector data
  T *vector_pt = vector.vector_pt();
  // Get the dimension of the new vector
  unsigned long n = vector.nvalues();
  
  // Copy the data from the vector to the Matrix_pt vector
  set_vector(vector_pt, n);
 }
 
 // ===================================================================
 // Copy constructor
 // ===================================================================
 template<class T>
 CCVectorArmadillo<T>::CCVectorArmadillo(const CCVectorArmadillo<T> &copy)
  : ACVector<T>(copy.nvalues(), copy.is_column_vector())
 {
  // Clean any possible previously allocated memory
  clean_up();
  
  // Call the copy constructor of Armadillo
  Arma_vector_pt = new arma::Col<T>(*(copy.arma_vector_pt())); 
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class T>
 CCVectorArmadillo<T>::~CCVectorArmadillo()
 {
  // Deallocate memory
  clean_up();
 }
 
 // ===================================================================
 // Assignment operator
 // =================================================================== 
 template<class T>
 CCVectorArmadillo<T>& CCVectorArmadillo<T>::operator=(const CCVectorArmadillo<T> &source_vector)
 {
  // Clean-up and set values
  set_vector(source_vector.arma_vector_pt(), source_vector.nvalues());
  // Set the transposed status
  this->set_as_column_vector(source_vector.is_column_vector());
  // Return this (de-referenced pointer)
  return *this;
  
 }
 
 // ===================================================================
 // += operator
 // ===================================================================
 template<class T>
 CCVectorArmadillo<T>& CCVectorArmadillo<T>::operator+=(const CCVectorArmadillo<T> &vector)
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
 CCVectorArmadillo<T>& CCVectorArmadillo<T>::operator-=(const CCVectorArmadillo<T> &vector)
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
 CCVectorArmadillo<T> CCVectorArmadillo<T>::operator+(const CCVectorArmadillo<T> &vector)
 {
  // Create a zero vector where to store the result
  CCVectorArmadillo<T> solution(this->NValues);
  // Call the method to perform the addition
  add_vector(vector, solution);
  // Return the solution vector
  return solution;
 }
 
 // ===================================================================
 // Substraction operator
 // ===================================================================
 template<class T>
 CCVectorArmadillo<T> CCVectorArmadillo<T>::operator-(const CCVectorArmadillo<T> &vector)
 {
  // Create a zero vector where to store the result
  CCVectorArmadillo<T> solution(this->NValues);
  // Call the method to perform the operation
  substract_vector(vector, solution);
  return solution;
 }
 
 // HERE HERE HERE Working on this
 
 // ===================================================================
 // Multiplication operator (it returns a matrix with the
 // corresponding size, if you require a dot product operation use the
 // dot() method instead
 // ===================================================================
 template<class T>
 CCMatrixArmadillo<T> CCVectorArmadillo<T>::operator*(const CCVectorArmadillo<T> &vector)
 {
  // Create two matrices, one from each vector
  CCMatrixArmadillo<T> left_matrix(*this);
  CCMatrixArmadillo<T> right_matrix(vector);
  
  // Store the size of both vectors to create a solution matrix with
  // the corresponding sizes
  // (First dimension for the left vector)
  long unsigned n_values_left_vector = this->NValues;
  if (!vector.is_column_vector())
   {
    n_values_left_vector = 1;
   }
  // (Second dimension for the right vector)
  long unsigned n_values_right_vector = vector.nvalues();
  if (vector.is_column_vector())
   {
    n_values_right_vector = 1;
   }
  // Create a zero vector where to store the result
  CCMatrixArmadillo<T> solution(n_values_left_vector, n_values_right_vector);
  // Perform the multiplication (this method is in charge of verifying
  // whether the matrices fulfill the requirements for matrix
  // multiplication)
  multiply_matrices(left_matrix, right_matrix, solution);
  // Return the solution vector
  return solution;
 }
 
 // ===================================================================
 // Performs dot product with the current vector
 // ===================================================================
 template<class T>
 T CCVectorArmadillo<T>::dot(const CCVectorArmadillo &right_vector)
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
  
  // Store the dot product of the vectors
  const T dot_product = arma::dot(*Arma_vector_pt, *(right_vector.arma_vector_pt()));
  // Return the dot product
  return dot_product;
  
 }
 
 // ===================================================================
 // Transforms the input vector to an armadillo vector class type
 // (virtual such that each derived class has to implement it)
 // ===================================================================
 template<class T>
 void CCVectorArmadillo<T>::set_vector(const T *vector_pt,
                                       const unsigned long n)
 {
  // Clean any possible previously allocated memory
  clean_up();
  
  // Set the number of values
  this->NValues = n;
  
  // Create an Armadillo's matrix (makes an own copy of the data,
  // therefore 'matrix_pt' may be deleted safely)
  Arma_vector_pt = new arma::Col<T>(vector_pt, n);
  
  // Mark the vector as allocated its own memory
  this->Is_own_memory_allocated = true;
  
 }
 
 // ===================================================================
 // Receives an armadillo type column vector
 // ===================================================================
 template<class T>
 void CCVectorArmadillo<T>::set_vector(arma::Col<T> *arma_vector_pt,
                                       const unsigned long n)
 {
  // Clean any possible previously allocated memory
  clean_up();
  
  // Set the number of values
  this->NValues = n;
  
  // Call the copy constructor of Armadillo
  Arma_vector_pt = new arma::Col<T>(*arma_vector_pt);
  
  // Mark the matrix as having its own memory
  this->Is_own_memory_allocated = true;
  
 }
 
 // ===================================================================
 // Clean up for any dynamically stored data
 // ===================================================================
 template<class T>
 void CCVectorArmadillo<T>::clean_up()
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
    Arma_vector_pt = 0;
   }
  
 }
 
 // ===================================================================
 // Free allocated memory for vector
 // ===================================================================
 template<class T>
 void CCVectorArmadillo<T>::free_memory_for_vector()
 {
  // Is the vector allowed for deletion. If this method is called from
  // an external source we need to check whether the vector has been
  // marked for deletion
  if (this->Delete_vector)
   {
    delete Arma_vector_pt;
    Arma_vector_pt = 0; 
    
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
 void CCVectorArmadillo<T>::add_vector(const CCVectorArmadillo<T> &vector,
                                       CCVectorArmadillo<T> &solution_vector)
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
  arma::Col<T> *arma_solution_vector_pt = solution_vector.arma_vector_pt();
  
  // Check whether the solution vector has allocated memory, otherwise
  // allocate it here!!!
  if (!solution_vector.is_own_memory_allocated())
   {
    // Allocate memory for the vector
    solution_vector.allocate_memory();
    // Get the new vector pointer
    arma_solution_vector_pt = solution_vector.arma_vector_pt();
   }
  
  // Get the vector pointer of the input vector
  arma::Col<T> *arma_vector_pt = vector.arma_vector_pt();
  
  // Perform the addition
  (*arma_solution_vector_pt) = (*Arma_vector_pt) + (*arma_vector_pt);
  
 }
 
 // ===================================================================
 // Performs substraction of vectors
 // ===================================================================
 template<class T>
 void CCVectorArmadillo<T>::substract_vector(const CCVectorArmadillo<T> &vector,
                                    CCVectorArmadillo<T> &solution_vector)
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
  arma::Col<T> *arma_solution_vector_pt = solution_vector.arma_vector_pt();
  
  // Check whether the solution vector has allocated memory, otherwise
  // allocate it here!!!
  if (!solution_vector.is_own_memory_allocated())
   {
    // Allocate memory for the vector
    solution_vector.allocate_memory();
    // Get the new vector pointer
    arma_solution_vector_pt = solution_vector.arma_vector_pt();
   }
  
  // Get the vector pointer of the input vector
  arma::Col<T> *arma_vector_pt = vector.arma_vector_pt();
  
  // Perform the substraction
  (*arma_solution_vector_pt) = (*Arma_vector_pt) - (*arma_vector_pt);
    
 }
 
 // ===================================================================
 // Performs multiplication of vectors (element by element)
 // ===================================================================
 template<class T>
 void CCVectorArmadillo<T>::
 multiply_element_by_element_vector(const CCVectorArmadillo<T> &vector,
                                    CCVectorArmadillo<T> &solution_vector)
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
  arma::Col<T> *arma_solution_vector_pt = solution_vector.arma_vector_pt();
  
  // Check whether the solution vector has allocated memory, otherwise
  // allocate it here!!!
  if (!solution_vector.is_own_memory_allocated())
   {
    // Allocate memory for the vector
    solution_vector.allocate_memory();
    // Get the new vector pointer
    arma_solution_vector_pt = solution_vector.arma_vector_pt();
   }
  
  // Get the vector pointer of the input vector
  arma::Col<T> *arma_vector_pt = vector.arma_vector_pt();
  
  // Perform the operation
  for (unsigned long i = 0; i < this->NValues; i++)
   {
    (*arma_solution_vector_pt)(i) = (*Arma_vector_pt)(i) * (*arma_vector_pt)(i);
   }
  
 }
 
 // ===================================================================
 // Computes the transpose and store in the solution vector
 // ===================================================================
 template<class T>
 void CCVectorArmadillo<T>::transpose(CCVectorArmadillo<T> &transposed_vector)
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
  transposed_vector.arma_vector_pt() = &(arma::trans(*(this->Arma_vector_pt)));
  // Get the current "transpose" status of the vector and set the
  // transposed status of the new vector
  transposed_vector.set_transposed_status(~(this->Is_transposed));
 }
 
 // ===================================================================
 // Transpose the vector
 // ===================================================================
 template<class T>
 void CCVectorArmadillo<T>::transpose()
 {
  // Change the status
  this->Is_column_vector=!(this->Is_column_vector);
  // Performs the operation
  arma::inplace_trans(*Arma_vector_pt);
 }
 
 // ===================================================================
 // Get the specified value from the vector (read-only)
 // ===================================================================
 template<class T>
 const T CCVectorArmadillo<T>::value(const unsigned long i) const
 {
  // Return the value at position i
  return (*Arma_vector_pt)(i);
 }
 
 // ===================================================================
 // Set values in the vector (write version)
 // ===================================================================
 template<class T>
 T &CCVectorArmadillo<T>::value(const unsigned long i)
 {
  // Return the value at row i and column j
  return (*Arma_vector_pt)(i);
 }

 // ===================================================================
 // Output the vector
 // ===================================================================
 template<class T>
 void CCVectorArmadillo<T>::output(bool output_indexes) const
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
        std::cout << "(" << i << "): " << (*Arma_vector_pt)(i)
                  << std::endl; 
       } // for (i < this->NValues)
     } // if (output_indexes)
    else
     {
      Arma_vector_pt->print();
     } // else if (output_indexes)
    
   }
  
 }
 
 // ===================================================================
 // Output the vector
 // ===================================================================
 template<class T>
 void CCVectorArmadillo<T>::output(std::ofstream &outfile, bool output_indexes) const
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
        outfile << "(" << i << "): " << (*Arma_vector_pt)(i)
                << std::endl; 
       } // for (i < this->NValues)
     } // if (output_indexes)
    else
     {
      Arma_vector_pt->print(outfile);
     } // else if (output_indexes)
    
   }
  
 }

 // ===================================================================
 // Computes the norm-1 of the vector
 // ===================================================================
 template<class T>
 const double CCVectorArmadillo<T>::norm_1()
 {
  // Sum
  double sum = 0.0;
  // Check whether the vector has memory allocated
  if (this->Is_own_memory_allocated)
   {
    // Compute the norm
    sum = arma::norm((*Arma_vector_pt), 1);
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
 const double CCVectorArmadillo<T>::norm_2()
 {
  // Sum
  double sum = 0.0;
  // Check whether the vector has memory allocated
  if (this->Is_own_memory_allocated)
   {
    // Compute the norm
    sum = arma::norm((*Arma_vector_pt), 2);
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
 // Allocates memory to store entries of the vector
 // ===================================================================
 template<class T>
 void CCVectorArmadillo<T>::allocate_memory()
 {
  // Delete any data in memory
  clean_up();
  
  // Allocate memory for the vector
  Arma_vector_pt = new arma::Col<T>(this->NValues);
  
  // Mark the vector as allocated its own memory
  this->Is_own_memory_allocated=true;
 }

 // ===================================================================
 // Fills the vector with zeroes
 // ===================================================================
 template<class T>
 void CCVectorArmadillo<T>::fill_with_zeroes()
 {
  // Check that the vector has memory allocated
  if (this->Is_own_memory_allocated)
   {
    // Fill the vector with zeroes
    Arma_vector_pt->zeros();
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
 T dot_vectors(const CCVectorArmadillo<T> &left_vector, const CCVectorArmadillo<T> &right_vector)
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
  
  // Store the dot product of the vectors
  const T dot_product = arma::dot(*(left_vector.arma_vector_pt()), *(right_vector.arma_vector_pt()));
  // Return the dot product
  return dot_product;
  
 }

 // ================================================================
 // Addition of vectors
 // ================================================================
 template<class T>
 void add_vectors(const CCVectorArmadillo<T> &vector_one,
                  const CCVectorArmadillo<T> &vector_two,
                  CCVectorArmadillo<T> &solution_vector)
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
  arma::Col<T> *arma_solution_vector_pt = solution_vector.arma_vector_pt();
  
  // Check whether the solution vector has allocated memory, otherwise
  // allocate it here!!!
  if (!solution_vector.is_own_memory_allocated())
   {
    // Allocate memory for the vector
    solution_vector.allocate_memory();
    // Get the new vector pointer
    arma_solution_vector_pt = solution_vector.arma_vector_pt();
   }
  
  // Get the vector pointer of the input vectors
  arma::Col<T> *arma_vector_one_pt = vector_one.arma_vector_pt();
  arma::Col<T> *arma_vector_two_pt = vector_two.arma_vector_pt();
  
  // Perform the addition
  (*arma_solution_vector_pt) = (*arma_vector_one_pt) + (*arma_vector_two_pt);
  
 }

 // ================================================================
 // Substraction of vectors
 // ================================================================
 template<class T>
 void substract_vectors(const CCVectorArmadillo<T> &vector_one,
                        const CCVectorArmadillo<T> &vector_two,
                        CCVectorArmadillo<T> &solution_vector)
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
  arma::Col<T> *arma_solution_vector_pt = solution_vector.arma_vector_pt();
  
  // Check whether the solution vector has allocated memory, otherwise
  // allocate it here!!!
  if (!solution_vector.is_own_memory_allocated())
   {
    // Allocate memory for the vector
    solution_vector.allocate_memory();
    // Get the new vector pointer
    arma_solution_vector_pt = solution_vector.arma_vector_pt();
   }
  
  // Get the vector pointer of the input vectors
  arma::Col<T> *arma_vector_one_pt = vector_one.arma_vector_pt();
  arma::Col<T> *arma_vector_two_pt = vector_two.arma_vector_pt();
  
  // Perform the addition
  (*arma_solution_vector_pt) = (*arma_vector_one_pt) + (*arma_vector_two_pt);
  
 }

 // ================================================================
 // Performs multiplication of vectors (one by one entries)
 // ================================================================
 template<class T>
 void multiply_element_by_element_vectors(const CCVectorArmadillo<T> &vector_one,
                                          const CCVectorArmadillo<T> &vector_two,
                                          CCVectorArmadillo<T> &solution_vector)
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
  arma::Col<T> *arma_solution_vector_pt = solution_vector.arma_vector_pt();
  
  // Check whether the solution vector has allocated memory, otherwise
  // allocate it here!!!
  if (!solution_vector.is_own_memory_allocated())
   {
    // Allocate memory for the vector
    solution_vector.allocate_memory();
    // Get the new vector pointer
    arma_solution_vector_pt = solution_vector.arma_vector_pt();
   }

  // Get the vector pointer of the input vectors
  arma::Col<T> *arma_vector_one_pt = vector_one.arma_vector_pt();
  arma::Col<T> *arma_vector_two_pt = vector_two.arma_vector_pt();

  // Perform the operation
  for (unsigned long i = 0; i < n_values_vector_one; i++)
   {
    (*arma_solution_vector_pt)(i) = (*arma_vector_one_pt)(i) * (*arma_vector_two_pt)(i);
   }
  
 }
 
}

