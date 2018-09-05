// IN THIS FILE: The definition of a class to represent data

// Check whether the class has been already defined
#ifndef CCDATA_TPL_H
#define CCDATA_TPL_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

namespace chapchom
{
 
 // Enumerator to indicate whether the associated value is pinned or
 // not. Pinned status represents known values, ex. initial or
 // boundary conditions
 enum Data_status {UNDEFINED, UNPINNED, PINNED};
 
 /// @class CCData cc_data.tpl.h
 
 // Concrete class to represent data
 template<class T>
  class CCData
 {
  
 public:
  
  // Constructor. Allocates memory for the values. Initialise them to
  // zero
  CCData(const unsigned n_values, const unsigned n_history_values=0);
  
  // Constructor. Allocates memory for values and copy them from the
  // input vector
  CCData(T *values_pt,
         const unsigned n_values,
         const unsigned n_history_values=0);
  
  // Copy constructor
  CCData(const CCData<T> &copy);
  
  // Destructor
  ~CCData();
  
  // Assignment operator
  CCData &operator=(const CCData<T> &source_values);
  
  /// Get access using brackets as data(i). Read-only version
  inline virtual T operator()(const unsigned &i) const
  {return value(i,0);}
  
  /// Get access using brackets as data(i). Read-write version
  inline virtual T &operator()(const unsigned &i)
  {return value(i,0);}
  
  /// Get access using brackets as data(i,j). Read-only version
  inline virtual T operator()(const unsigned &i, 
                              const unsigned &t) const
  {return value(i, t);}
  
  /// Get access using brackets as data(i,j). Read-write version
  inline virtual T &operator()(const unsigned &i, 
                               const unsigned &t)
  {return value(i,t);}
  
  // Transforms the input values vector to a Data class type
  void set_values(const T *values_pt);
  
  // Clean up for any dynamically stored data
  void clean_up();
  
  // Free allocated memory
  void free_memory_of_values();
  
  // Get the specified value (read-only)
  const T value(const unsigned &i, const unsigned t=0) const;
  
  // Set values (write version)
  T &value(const unsigned &i, const unsigned t=0);
  
  // Output the values vector (matrix)
  void output(bool output_indexes) const;
  
  // Output the matrix
  void output(std::ofstream &outfile,
              bool output_indexes) const;
  
  // Creates a zero Values_pt and Status_pt vectors with the given
  // number of elements
  void create_zero_values_and_status_vectors();
  
  inline void pin(const unsigned &i)
  {return Status_pt[i]=PINNED;}
  
  inline void unpin(const unsigned &i)
  {return Status_pt[i]=UNPINNED;}
  
  inline void undefine(const unsigned &i)
  {return Status_pt[i]=UNDEFINED;}
  
  // Pins all the values associated with this data
  void pin_all();
  
  // Unpins all the values associated with this data
  void unpin_all();
  
  // Get access to the Values_pt
  inline T *values_pt() const {return Values_pt;}
  
  // Get access to the Status_pt
  inline Data_status *status_pt() const {return Status_pt;}
  
  inline bool is_pinned(const unsigned i) const
  {return (Status_pt[i]==PINNED);}
  
  inline bool is_unpinned(const unsigned i) const
  {return (Status_pt[i]==UNPINNED);}
  
  inline bool is_undefined(const unsigned i) const
  {return (Status_pt[i]==UNDEFINED);}
  
  // Gets the number of values
  inline unsigned n_values() const {return N_values;}
  
  // Gets the number of history values
  inline unsigned n_history_values() const {return N_history_values-1;}
  
  // Checks whether values have been set, or allocated
  inline bool is_empty() const {return (Is_values_empty && Is_status_empty);}
  
  // Checks whether the values storage is allowed to be deleted
  inline bool delete_values_storage() const {return Delete_values_storage;}
  
  // Enables the deletion of values storage
  inline void enable_delete_values_storage() {Delete_values_storage=true;}
  
  // Disables the deletion of values storage
  inline void disable_delete_values_storage() {Delete_values_storage=false;}
  
 protected:
  
  // Flag to indicate whether values vector is empty
  bool Is_values_empty;
  // Flag to indicate whether status vector is empty
  bool Is_status_empty;
  
  // Flag to indicate whether to delete (free) the allocated memory
  // for values. The deletion is true by default.
  bool Delete_values_storage;
  
 private:
  
  // The number of values
  const unsigned N_values;
  
  const unsigned N_history_values;
  
  // Store the values of the i-th data at th t-th history
  // Values_pt[i*N_history_values+t];
  T *Values_pt;
  
  // Indicates the status of the current (0 index history) Value
  Data_status *Status_pt;
  
 };
 
}

#endif // #ifndef CCDATA_TPL_H
