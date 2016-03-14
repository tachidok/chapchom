// IN THIS FILE: Implementation of an abstract class to represent
// matrices

#include "CAMatrix.h"

// ===================================================================
// Empty constructor
// ===================================================================
CAMatrix::CAMatrix() 
 : NRows(0), NColumns(0), Is_empty(true), Delete_matrix(true)
{ }

// ===================================================================
// Constructor to create an n X n zero matrix
// ===================================================================
CAMatrix::CAMatrix(const unsigned n)
 : NRows(n), NColumns(n), Is_empty(true), Delete_matrix(true)
{ }
 

// ===================================================================
// Constructor to create an m X n zero matrix
// ===================================================================
CAMatrix::CAMatrix(const unsigned m, const unsigned n)
 : NRows(n), NColumns(m), Is_empty(true), Delete_matrix(true)
{ }

// ===================================================================
// Constructor where we pass the data for the matrix of size m X n
// ===================================================================
CAMatrix::CAMatrix(double **_matrix,
                   const unsigned m,
                   const unsigned n) 
 : NRows(m), NColumns(n), Is_empty(true), Delete_matrix(true)
{ }

// ===================================================================
// Destructor
// ===================================================================
CAMatrix::~CAMatrix()
{
 // Deallocate memory (call the delete memory method of the derived
 // class)
 clean_up();
}

// ===================================================================
// Clean up for any dynamically stored data
// ===================================================================
void CAMatrix::clean_up()
{
 // Do nothing 
}

// ===================================================================
// Copy constructor (we do not want this class to be copiable because
// it contains dynamically allocated variables; the matrix. Check
// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
// ===================================================================
CAMatrix::CAMatrix(const CAMatrix &copy)
{
 // TODO Julio: Implement a class to handle runtime errors and call
 // it here!!!
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << "ERROR in CAMatrix::CAMatrix() - Copy constructor called" << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 throw(1);
}

// ===================================================================
// Assignment operator (we do not want this class to be copiable
// because it contains dynamically allocated variables; the
// matrix. Check
// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
// ===================================================================
CAMatrix& CAMatrix::operator=(const CAMatrix &copy)
{
 // TODO Julio: Implement a class to handle runtime errors and call
 // it here!!!
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << "ERROR in CAMatrix::operator=() - Assignment called" << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 throw(1);
}

