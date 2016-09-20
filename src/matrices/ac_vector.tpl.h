// IN THIS FILE: The definition of an abstract class to store and work
// with vectors. Most of the vectors implemented in this library use
// this class as the base class

// Check whether the class has been already defined
#ifndef ACVECTOR_H
#define ACVECTOR_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

namespace chapchom
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
   // are created as column vectors, if you require a row vector then
   // transpose it)
   ACVector(const unsigned long n);
   
   // Destructor
   virtual ~ACVector();
   
   // Transforms the input vector to a vector class type (virtual such
   // that each derived class has to implement it)
   virtual void set_vector(const T *vector_pt,
                           const unsigned long n) = 0;
   
   // Clean up for any dynamically stored data
   virtual void clean_up() = 0;o
   
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
   inline const unsigned long nvalues() const {return NValues;}
   
   // Return the number of entries of the vector
   inline const unsigned long nentries() const {return nvalues();}
   
   // Return the number of entries of the vector
   inline const unsigned long size() const {return nvalues();}
   
   // Check whether the vector should be treated as transposed (we
   // assume all vectors are created as column vectors)
   inline bool is_transposed() const {return Is_transpose;}
   
   // Set transposed status
   inline bool set_transposed_status(bool status)
   {Is_transpose = status;}
   
   // Transpose the matrix
   inline void transpose(){is_transpose=~is_transpose;}
   
   // Computes the transpose and store it in the transpose vector
   virtual void transpose(const CCVector &transpose_vector) = 0;
   
   // Checks whether the vector has been set, or allocated
   inline bool is_empty() const {return Is_empty;}
   
   // Checks whether the vector is allowed to be deleted
   inline bool delete_vector() const {return Delete_vector;}
   
   // Enables the deletion of the vector by itself
   inline void enable_delete_vector() {Delete_vector=true;}
   
   // Disables the deletion of the vector by itself
   inline void disable_delete_vector() {Delete_vector=false;}
   
  protected:
   
   // Creates a zero vector with the given number of entries
   virtual void create_zero_vector() = 0;
   
   // The size of the vector
   unsigned long NValues;
   
   // Flag to indicate whether the vector is empty or not
   bool Is_empty;
   
   // Flag to indicate whether to delete (free) the allocated memory
   // for the vector. For example when the vector is transformed to an
   // specific vector type (Armadillo vector, SuperLU vector, Trilinos
   // vector) we need to deallocate the memory used for THIS vector to
   // avoid having multiple copies of it. The deletion of the vector
   // is true by default.
   bool Delete_vector;
   
   // Is transposed vector (we assume all vectors are created as
   // column vectors, thus this flag is set to true by default). We
   // check this variable for all its operations such that they are
   // valid according to the vector dimensions
   bool Is_transposed;
   
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

#endif // #ifndef ACVECTOR_H
