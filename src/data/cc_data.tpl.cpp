// IN THIS FILE: Implementation of a concrete class to represent
// data. This is the simplest implementation

#include "cc_data.tpl.h"

namespace chapchom
{
 
 // ===================================================================
 // Constructor. Allocates memory for the values. Initialise them to
 // zero
 // ===================================================================
 template<class T>
 CCData<T>::CCData(const unsigned n_values,
                   const unsigned n_history_values)
  : Is_empty(true), Delete_values(true),
    N_values(n_values), N_history_values(n_history_values)
 {
  // Delete any data in memory
  clean_up();
 }
 
 // ===================================================================
 // Constructor. Allocates memory for values and copy them from the
 // input vector
 // ===================================================================
 template<class T>
 CCData<T>::CCData(T *values_pt,
                   const unsigned n_values,
                   const unsigned n_history_values)
  : Is_empty(true), Delete_values(true),
    N_values(n_values), N_history_values(n_history_values)
 {
  // Delete any data in memory
  clean_up();
  // Copy the data from the input vector to the values_pt vector
  set_values(values_pt);
 }
 
 // ===================================================================
 // Copy constructor
 // ===================================================================
 template<class T>
 CCData<T>::CCData(const CCData<T> &copy)
  : Is_empty(true), Delete_values(true),
    N_values(copy.n_values()), N_history_values(copy.n_history_values())
 {
  // Copy the data from the copy object to the Values_pt vector
  set_values(copy.values_pt());
 }
 
 // ===================================================================
 // Destructor
 // ===================================================================
 template<class T>
 CCData<T>::~CCData()
 {
  // Deallocate memory
  clean_up();
 }
 
 // ===================================================================
 // Assignment operator
 // ===================================================================
 template<class T>
 CCData<T>& CCData<T>::operator=(const CCData<T> &source_values)
 {
  if (N_values != source_values.n_values())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The number of values from the source and the destination\n"
                  << "CCData object are not the same\n"
                  << "N_values: " << N_values << "\n"
                  << "source_values.n_values(): " << source_values.n_values() << "\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  if (N_history_values != source_values.n_history_values())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The number of history values from the source and the destination\n"
                  << "CCData object are not the same\n"
                  << "N_history_values: " << N_history_values << "\n"
                  << "source_values.n_history_values(): " << source_values.n_history_values() << "\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Clean-up and set values
  set_values(source_values.matrix_pt());
  
  // Return this (de-referenced pointer)
  return *this;
 }
 
 // ===================================================================
 // Transforms the input values vector to a Data class type
 // ===================================================================
 template<class T>
 void CCData<T>::set_values(const T *values_pt)
 {
  // Clean any possible previously allocated memory
  clean_up();
  
  // Allocate memory for Values_pt vector
  Values_pt = new T[N_values*N_history_values];
  
  // Copy the values (an element by element copy, uff!!)
  std::memcpy(Values_pt, values_pt, N_values*N_history_values*sizeof(T));
  
  // Mark the Values_pt vector as having elements
  Is_empty = false;
  
 }
 
 // ===================================================================
 // Clean up for any dynamically stored data
 // ===================================================================
 template<class T>
 void CCData<T>::clean_up()
 {
  // Check whether the Values_pt vector has got something in it
  if (!Is_empty)
   {
    // Mark as deleteable
    Delete_values = true;
    // Free memory
    free_memory_for_values();
   }
  else // If empty
   {
    // Set the pointer to NULL
    Values_pt = 0;
   }
  
 }
 
 // ===================================================================
 // Free allocated memory
 // ===================================================================
 template<class T>
 void CCData<T>::free_memory_for_values()
 {
  // Is the Values_pt vector allowed for deletion. If this method is
  // called from an external source we need to check whether the
  // values has been marked for deletion
  if (Delete_values)
   {
    for (unsigned i = 0; i < N_values; i++)
     {
      delete Values_pt[i];
     }
    delete [] Values_pt;
    Values_pt = 0;
    
    // Mark as empty
    Is_empty=true;
    
   } // if (Delete_values)
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You are trying to free the memory of a data object that is\n"
                  << "not marked as deletable" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
 }
 
 // ===================================================================
 // Get the specified value (read-only)
 // ===================================================================
 template<class T>
 const T CCData<T>::value(const unsigned long i, const unsigned long j) const
 {
  // TODO: Julio - Implement range check access
  // Return the value at row i and column j
  return Values_pt[i*N_history_values+j];
 }
 
 // ===================================================================
 // Set values (write version)
 // ===================================================================
 template<class T>
 T &CCData<T>::value(const unsigned long i, const unsigned long j)
 {
  // TODO: Julio - Implement range check access
  // Return the value at row i and column j
  return Values_pt[i*N_history_values+j];
 }
 
 // ===================================================================
 // Output the values vector (matrix)
 // ===================================================================
 template<class T>
 void CCData<T>::output(bool output_indexes) const
 {
  if (Is_empty)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The Values_pt vector is empty" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  else
   {
    // Check whether we should output the indexes
    if (output_indexes)
     {
      for (unsigned long i = 0; i < N_values; i++)
       {
        for (unsigned long j = 0; j < N_history_values; j++)
         {
          std::cout << "(" << i << ", " << j << "): "
                    << Values_pt[i*N_history_values+j]
                    << std::endl; 
         } // for (j < N_history_values)
       } // for (i < N_values)
     } // if (output_indexes)
    else
     {
      for (unsigned long i = 0; i < N_values; i++)
       {
        for (unsigned long j = 0; j < N_history_values; j++)
         {
          std::cout << Values_pt[i*N_history_values+j] << " ";
         } // for (j < N_history_values)
        std::cout << std::endl;
       } // for (i < N_values)
     } // else if (output_indexes)
    
   }
  
 }
 
 // ===================================================================
 // Output the matrix
 // ===================================================================
 template<class T>
 void CCData<T>::output(std::ofstream &outfile,
                          bool output_indexes) const
 {
  if (Is_empty)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The Values_pt vector is empty" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  else
   {
    // Check whether we should output the indexes
    if (output_indexes)
     {
      for (unsigned long i = 0; i < N_values; i++)
       {
        for (unsigned long j = 0; j < N_history_values; j++)
         {
          outfile << "(" << i << ", " << j << "): "
                  << Values_pt[i*N_history_values+j]
                  << std::endl; 
         } // for (j < N_history_values)
       } // for (i < N_values)
     } // if (output_indexes)
    else
     {
      for (unsigned long i = 0; i < N_values; i++)
       {
        for (unsigned long j = 0; j < N_history_values; j++)
         {
          outfile << Values_pt[i*N_history_values+j] << " ";
         } // for (j < N_history_values)
        outfile << std::endl;
       } // for (i < N_values)
     } // else if (output_indexes)
    
   }
  
 }
 
 // ===================================================================
 // Creates a zero Values_pt vector with the given number of elements
 // ===================================================================
 template<class T>
 void CCData<T>::create_zero_values_vector()
 {
  // Delete any Values_pt in memory
  clean_up();
  
  // Allocate memory for Values_pt
  Values_pt = new T*[N_values];
  for (unsigned i = 0; i < N_values; i++)
   {
    Values_pt[i] = new T[N_history_values];
    Status_pt[i] = UNDEFINED;
   }
  
  // Mark the matrix as having something
  Is_empty=false;
 }

 // ===================================================================
 // Pins all the values associated with this data
 // ===================================================================
 template<class T>
 void CCData<T>::pin_all()
 {
  if (!Is_empty)
   {
    for (unsigned i = 0; i < N_values; i++)
     {
      Status_pt[i] = PINNED;
     }
   }
 }

 // ===================================================================
 // Unpins all the values associated with this data
 // ===================================================================
 template<class T>
 void CCData<T>::unpin_all()
 {
  if (!Is_empty)
   {
    for (unsigned i = 0; i < N_values; i++)
     {
      Status_pt[i] = UNPINNED;
     }
   }
 }
 
}
