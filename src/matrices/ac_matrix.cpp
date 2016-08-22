// IN THIS FILE: Implementation of an abstract class to represent
// matrices

#include "ac_matrix.h"

// ===================================================================
// Empty constructor
// ===================================================================
ACMatrix::ACMatrix() 
 : NRows(0), NColumns(0), Is_empty(true), Delete_matrix(true)
{ }

// ===================================================================
// Constructor to create an n X n zero matrix
// ===================================================================
ACMatrix::ACMatrix(const unsigned n)
 : NRows(n), NColumns(n), Is_empty(true), Delete_matrix(true)
{ }
 

// ===================================================================
// Constructor to create an m X n zero matrix
// ===================================================================
ACMatrix::ACMatrix(const unsigned m, const unsigned n)
 : NRows(n), NColumns(m), Is_empty(true), Delete_matrix(true)
{ }

// ===================================================================
// Destructor
// ===================================================================
ACMatrix::~ACMatrix()
{ }

