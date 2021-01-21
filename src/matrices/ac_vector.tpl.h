/// IN THIS FILE: The definition of an abstract class to store and work
/// with vectors. Most of the vectors implemented in this library use
/// this class as the base class

// Check whether the class has been already defined
#ifndef ACVECTOR_TPL_H
#define ACVECTOR_TPL_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#ifdef SCICELLXX_USES_ARMADILLO
// Add Armadillo's includes (only for the arma_vector methods)
#include <armadillo>
#endif // #ifdef SCICELLXX_USES_ARMADILLO

namespace scicellxx
{
 
 /// @class ACVector ac_vector.h
 
 // Abstract class to represent vector
 template<class T>
  class ACVector
  {
   
  public:
   
   // Empty constructor
   ACVector();
   
   // Constructor to create an n size zero vector (we assume vectors
   // are created as column vectors, if you need a row vector then
   // pass "false" as the second parameter)
   ACVector(const unsigned long n, bool is_column_vector = true);
   
   // Destructor
   virtual ~ACVector();
   
   // Allows to create a vector with the given size but with no data
   virtual void allocate_memory(const unsigned long n) = 0;
   
   // Allocates memory to store entries of the vector
   //virtual void allocate_memory() = 0;
   
   // Fills the vector with zeroes
   virtual void fill_with_zeroes() = 0;
   
   // Transforms the input vector to a vector class type (virtual such
   // that each derived class has to implement it)
   virtual void set_vector(const T *vector_pt,
                           const unsigned long n,
                           bool is_column_vector = true) = 0;
   
   // Clean up for any dynamically stored data
   virtual void clean_up() = 0;
   
   // Free allocated memory for vector
   virtual void free_memory_for_vector() = 0;
   
   // Get the specified value from the vector (read-only)
   virtual const T value(const unsigned long i) const = 0;
   
   // Set values in the vector (write version)
   virtual T &value(const unsigned long i) = 0;
   
   // Get the specified value from the vector
   inline T get_value(const unsigned long i) const
   {return value(i);}
   
   // Set values in the vector
   inline void set_value(const unsigned long i, T v)
   {value(i) = v;}
   
   /// Get access using brackets as vector(i). Read-only version
   inline virtual T operator()(const unsigned long &i) const
   {return value(i);}
   
   /// Get access using brackets as vector(i). Read-write version
   inline virtual T &operator()(const unsigned long &i)
   {return value(i);}
   
   // Output the vector (output horizontally without indexes by
   // default, otherwise output vertically with indexes)
   virtual void output(bool output_indexes = false) const = 0;
   // Output to file (output horizontally without indexes by default,
   // otherwise output vertically with indexes)
   virtual void output(std::ofstream &outfile,
                       bool output_indexes = false) const = 0;
   
   // Output the vector
   inline void print(bool output_indexes = false) const
   {output(output_indexes);}
   
   // Output to file
   inline void print(std::ofstream &outfile,
                     bool output_indexes = false) const
   {output(outfile, output_indexes);}
   
   // Return the number of entries of the vector
   inline unsigned long n_values() const {return NValues;}
   
   // Return the number of entries of the vector
   inline unsigned long n_entries() const {return NValues;}
   
   // Return the number of entries of the vector
   inline unsigned long size() const {return NValues;}
   
   // Check whether the vector should be treated as "row vector" (we
   // assume all vectors are created as column vectors by default)
   inline bool is_column_vector() const {return Is_column_vector;}
   
   // Set as column vector status
   inline void set_as_column_vector(bool status = true)
   {Is_column_vector = status;}
   
   // Checks whether the memory of the vector has been allocated by
   // this class
   inline bool is_own_memory_allocated() const {return Is_own_memory_allocated;}
   
   // Checks whether the vector is allowed to be deleted
   inline bool delete_vector() const {return Delete_vector;}
   
   // Enables the deletion of the vector by itself
   inline void enable_delete_vector() {Delete_vector=true;}
   
   // Disables the deletion of the vector by itself
   inline void disable_delete_vector() {Delete_vector=false;}
   
   // Computes the norm-1 of the vector
   virtual T norm_1() = 0;
   
   // Computes the norm-2 of the vector
   virtual T norm_2() = 0;
   
   // Computes the infinite norm
   virtual T norm_inf() = 0;
   
   // Computes the maximum value
   virtual T max() = 0;
   
   // Computes the minimum value
   virtual T min() = 0;
   
   // Get access to the Vector_pt
   virtual T *vector_pt() const
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Virtual function to resolve vector pointer, should be\n"
                  << "implemented in derived class" << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
   
#ifdef SCICELLXX_USES_ARMADILLO
   // Get access to the Armadillo's vector
   virtual arma::Mat<T> *arma_vector_pt() const
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Virtual function to resolve armadillo vector pointer, should be\n"
                  << "implemented in derived class if you want to use the armadillo solver\n"
                  << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
#endif // #ifdef SCICELLXX_USES_ARMADILLO
   
  protected:
   
   // The size of the vector
   unsigned long NValues;
   
   // Flag to indicate whether the memory of the vector has been
   // allocated by this class
   bool Is_own_memory_allocated;
   
   // Flag to indicate whether to delete (free) the allocated memory
   // for the vector. For example when the vector is transformed to an
   // specific vector type (Armadillo vector, SuperLU vector, Trilinos
   // vector) we need to deallocate the memory used for THIS vector to
   // avoid having multiple copies of it. The deletion of the vector
   // is true by default.
   bool Delete_vector;
   
   // Is column vector (we assume all vectors are created as column
   // vectors, thus this flag is set to true by default). We check
   // this variable for all its operations such that they are valid
   // according to the vector dimensions
   bool Is_column_vector;
   
  private:
   
   // Copy constructor (we do not want this class to be copiable). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   ACVector(const ACVector &copy)
    {
     BrokenCopy::broken_copy("ACVector");
    }
   
   // Assignment operator (we do not want this class to be
   // copiable. Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   ACVector& operator=(const ACVector &copy)
    {
     BrokenCopy::broken_assign("ACVector");
    }
   
  };
 
}

#endif // #ifndef ACVECTOR_TPL_H
