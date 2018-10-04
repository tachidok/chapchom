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
  : Is_values_empty(true), Is_status_empty(true), Delete_values_storage(true),
    N_values(n_values), N_history_values(n_history_values+1)
 {
  // Delete any data in memory
  clean_up();
  
  // Initialise with zeros and UNPINNED status
  create_zero_values_and_status_vectors();
  
 }
 
 // ===================================================================
 // Constructor. Allocates memory for values and copy them from the
 // input vector
 // ===================================================================
 template<class T>
 CCData<T>::CCData(T *values_pt,
                   const unsigned n_values,
                   const unsigned n_history_values)
  : Is_values_empty(true), Is_status_empty(true), Delete_values_storage(true),
    N_values(n_values), N_history_values(n_history_values+1)
 {
  // Delete any data in memory
  clean_up();
  // Copy the data from the input vector to the values_pt vector
  set_values(values_pt);
  // Allocate memory for Status_pt
  Status_pt = new Data_status[N_values];
  // ... and set them to undefined
  for (unsigned i = 0; i < N_values; i++)
   {
    Status_pt[i] = UNPINNED;
   }

  // Mark status as having something
  Is_status_empty=false;
  
 }
 
 // ===================================================================
 // Copy constructor
 // ===================================================================
 template<class T>
 CCData<T>::CCData(const CCData<T> &copy)
  : Is_values_empty(true), Is_status_empty(true), Delete_values_storage(true),
    N_values(copy.n_values()), N_history_values(copy.n_history_values())
 {
  // Copy the data from the copy object to the Values_pt vector
  set_values(copy.values_pt());
  
  // Allocate memory for Status_pt
  Status_pt = new Data_status[N_values];
  
  // Copy the status
  std::memcpy(Status_pt, copy.status_pt(), N_values*sizeof(Data_status));
  
  // Mark status as having something
  Is_status_empty=false;
  
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
  set_values(source_values.values_pt());
  
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
  Is_values_empty = false;
  
 }
 
 // ===================================================================
 // Clean up for any dynamically stored data
 // ===================================================================
 template<class T>
 void CCData<T>::clean_up()
 {
  // Check whether the Values_pt vector has got something in it
  if (!Is_values_empty)
   {
    // Mark as deleteable
    Delete_values_storage = true;
    // Free memory
    free_memory_of_values();
   }
  
  // Set the pointer to NULL
  Values_pt = 0;
  
  if (!Is_status_empty)
   {
    // Free memory for pin status
    delete [] Status_pt;
    // Mark the Status_pt vector as having no elements
    Is_status_empty = true;
   }
  
  // Set the pointer to NULL
  Status_pt = 0;
  
 }
 
 // ===================================================================
 // Free allocated memory
 // ===================================================================
 template<class T>
 void CCData<T>::free_memory_of_values()
 {
  // Is the Values_pt vector allowed for deletion. If this method is
  // called from an external source we need to check whether the
  // values has been marked for deletion
  if (Delete_values_storage)
   {
    delete [] Values_pt;
    Values_pt = 0;
    
    // Mark as empty
    Is_values_empty=true;
    
   } // if (Delete_values_storage)
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
 // Shift history values (mostly used for time integration)
 // ===================================================================
 template<class T>
 void CCData<T>::shift_history_values(const unsigned n_shift_positions)
 {
  const unsigned cache_n_values = n_values();
  const unsigned cache_n_history_values = n_history_values();
  // Loop over the number of values
  for (unsigned i = 0; i < cache_n_values; i++)
   {
    // Loop over the history values
    for (unsigned j = 0; j <= cache_n_history_values-n_shift_positions; j++)
     {
      value(i,j) = value(i,j+n_shift_positions);
     }
   }
 }

 // ===================================================================
 // Extract history values column
 // ===================================================================
 template<class T>
 void CCData<T>::extract_history_values(T *extracted_column_pt,
                                        const unsigned n_column_history_values)
 {
  // Verify that the requested column is within the data storage
  if (n_column_history_values + 1 > N_history_values)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The history values column number you asked for is out of range\n"
                  << "Requested column: " << n_column_history_values + 1
                  << "Number of history values: " << N_history_values
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  const unsigned cache_n_values = n_values(); 
  // Loop over the data and store them in the output vector
  for (unsigned i = 0; i < cache_n_values; i++)
   {
    extracted_column_pt[i] = value(i, n_column_history_values);
   }
  
 }
 
 // ===================================================================
 // Get the specified value (read-only)
 // ===================================================================
 template<class T>
 const T CCData<T>::value(const unsigned &i, const unsigned t) const
 {
  // TODO: Julio - Implement range check access
  return Values_pt[i*N_history_values+t];
 }
 
 // ===================================================================
 // Set values (write version)
 // ===================================================================
 template<class T>
 T &CCData<T>::value(const unsigned &i, const unsigned t)
 {
  // TODO: Julio - Implement range check access
  return Values_pt[i*N_history_values+t];
 }
 
 // ===================================================================
 // Output the values vector (matrix)
 // ===================================================================
 template<class T>
 void CCData<T>::output(bool output_indexes) const
 {
  if (Is_values_empty)
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
      for (unsigned i = 0; i < N_values; i++)
       {
        for (unsigned j = 0; j < N_history_values; j++)
         {
          std::cout << "(" << i << ", " << j << "): "
                    << Values_pt[i*N_history_values+j]
                    << std::endl; 
         } // for (j < N_history_values)
       } // for (i < N_values)
     } // if (output_indexes)
    else
     {
      for (unsigned i = 0; i < N_values; i++)
       {
        for (unsigned j = 0; j < N_history_values; j++)
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
  if (Is_values_empty)
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
      for (unsigned i = 0; i < N_values; i++)
       {
        for (unsigned j = 0; j < N_history_values; j++)
         {
          outfile << "(" << i << ", " << j << "): "
                  << Values_pt[i*N_history_values+j]
                  << std::endl; 
         } // for (j < N_history_values)
       } // for (i < N_values)
     } // if (output_indexes)
    else
     {
      for (unsigned i = 0; i < N_values; i++)
       {
        for (unsigned j = 0; j < N_history_values; j++)
         {
          outfile << Values_pt[i*N_history_values+j] << " ";
         } // for (j < N_history_values)
        outfile << std::endl;
       } // for (i < N_values)
     } // else if (output_indexes)
    
   }
  
 }
 
 // ===================================================================
 // Creates a zero Values_pt and Status_pt vectors with the given
 // number of elements
 // ===================================================================
 template<class T>
 void CCData<T>::create_zero_values_and_status_vectors()
 {
  // Delete any Values_pt in memory
  clean_up();
  
  // Allocate memory for Values_pt
  Values_pt = new T[N_values*N_history_values];
  // Allocate memory for Status_pt
  Status_pt = new Data_status[N_values];
  // Set status as undefined
  for (unsigned i = 0; i < N_values; i++)
   {
    Status_pt[i] = UNPINNED;
   }
  
  // Mark the vectors as having something
  Is_values_empty=false;
  Is_status_empty=false;
  
 }
 
 // ===================================================================
 // Pins all the values associated with this data
 // ===================================================================
 template<class T>
 void CCData<T>::pin_all()
 {
  if (!Is_status_empty)
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
  if (!Is_status_empty)
   {
    for (unsigned i = 0; i < N_values; i++)
     {
      Status_pt[i] = UNPINNED;
     }
   }
 }
 
}

