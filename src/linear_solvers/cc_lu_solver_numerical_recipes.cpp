/// IN THIS FILE: Implementation of a concrete class to solve systems
/// of equations by LU decomposition. This class calls the methods
/// ludcmp() and lubksb() from numerical recipes to perform the LU
/// decomposition and back-substitution, respectively.

#include "cc_lu_solver_numerical_recipes.h"

namespace chapchom
{
 
 // ===================================================================
 /// Empty constructor
 // ===================================================================
 CCLUSolverNumericalRecipes::CCLUSolverNumericalRecipes()
  : ACLinearSolver(), Resolve_enabled(false) { }
 
 // ===================================================================
 /// Constructor where we specify the matrix A of size m X n
 // ===================================================================
 CCLUSolverNumericalRecipes::CCLUSolverNumericalRecipes(ACMatrix<Real> *const A_mat_pt)
  : ACLinearSolver(A_mat_pt), Resolve_enabled(false) { }
 
 // ===================================================================
 /// Empty destructor
 // ===================================================================
 CCLUSolverNumericalRecipes::~CCLUSolverNumericalRecipes() { }
 
 // ===================================================================
 /// Solves a system of equations with input A_mat. We specify the
 /// right-hand side B and the X matrices where the results are
 /// returned. We assume that the input/output matrices have the
 /// correct dimensions: A_mat.n_columns() x A_mat.n_rows() for B, and
 /// A_mat.n_rows() x A_mat.n_columns() for X.
 // ===================================================================
 void CCLUSolverNumericalRecipes::solve(ACMatrix<Real> *const A_mat_pt,
                                        const ACMatrix<Real> *const B_pt,
                                        ACMatrix<Real> *const X_pt)
 {
  // Set the matrix and its size
  set_matrix_A(A_mat_pt);
  
  // Solve
  solve(B_pt, X_pt);
  
 }
 
 // ===================================================================
 /// Solves a system of equations with input A_mat. We specify the
 /// right-hand side b and the x vector where the result is
 /// returned. We assume that the input/output vectors have the correct
 /// dimensions: A_mat.n_columns() for b, and A_mat.n_rows() for x.
 // ===================================================================
 void CCLUSolverNumericalRecipes::solve(ACMatrix<Real> *const A_mat_pt,
                                        const ACVector<Real> *const b_pt,
                                        ACVector<Real> *const x_pt)
 {
  // Set the matrix and its size
  set_matrix_A(A_mat_pt);
  
  // Solve
  solve(b_pt, x_pt);
 }
 
 // ===================================================================
 /// Solve a system of equations with the already stored matrix A. We
 /// specify the right-hand side B and the X matrices where the results
 /// are returned. We assume that the input/output matrices have the
 /// correct dimensions: A.n_columns() x A.n_rows() for B, and A.n_rows()
 /// x A.n_columns() for X.
 // ===================================================================
 void CCLUSolverNumericalRecipes::solve(const ACMatrix<Real> *const B_pt,
                                        ACMatrix<Real> *const X_pt)
 {
  // We can only call solve if the matrix A has been set
  if (this->Matrix_A_has_been_set)
   {
    // Check correct size of the matrix, right hand side and solution
    // vector    
    if (this->A_pt->n_columns() != B_pt->n_rows())
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The number of columns of the matrix and the number "
                    << "of rows of the rhs matrix are not the same:\n"
                    << "A_pt->n_columns() = (" << this->A_pt->n_columns() << ")\n"
                    << "B_pt->n_rows() = (" << B_pt->n_rows() << ")\n" << std::endl;
      throw SciCellxxLibError(error_message.str(),
                             SCICELLXX_CURRENT_FUNCTION,
                             SCICELLXX_EXCEPTION_LOCATION);
     }
    
    // Check whether the solution matrix has allocated memory,
    // otherwise allocate it here!!!
    if (!X_pt->is_own_memory_allocated())
     {
      // Allocate memory
      X_pt->allocate_memory(this->A_pt->n_rows(), B_pt->n_columns());
     }
    else
     {
      if (this->A_pt->n_rows() != X_pt->n_rows())
       {
        // Error message
        std::ostringstream error_message;
        error_message << "The number of rows of the matrix and the number "
                      << "of rows of the solution matrix are not the same:\n"
                      << "A_pt->n_rows() = (" << this->A_pt->n_rows() << ")\n"
                      << "X_pt->n_rows() = (" << X_pt->n_rows() << ")\n" << std::endl;
        throw SciCellxxLibError(error_message.str(),
                               SCICELLXX_CURRENT_FUNCTION,
                               SCICELLXX_EXCEPTION_LOCATION);
       }
      
      if (B_pt->n_columns() != X_pt->n_columns())
       {
        // Error message
        std::ostringstream error_message;
        error_message << "The number of columns of the rhs matrix and the number"
                      << "of columns of the solution matrix are not the same:\n"
                      << "n_rhs = (" << B_pt->n_columns() << ")\n"
                      << "X_pt->n_columns() = (" << X_pt->n_columns() << ")\n"
                      << std::endl;
        throw SciCellxxLibError(error_message.str(),
                               SCICELLXX_CURRENT_FUNCTION,
                               SCICELLXX_EXCEPTION_LOCATION);
       }
      
     }
    
    // The case for the same number of columns on the rhs vector and
    // the solution vector is tested in the back_substitution() method
    
    // Factorise
    factorise();
   
    // ... and do back substitution
    back_substitution(B_pt, X_pt);
    
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not specified any matrix for the system of\n"
                  << "equations. Set one matrix first by calling the/"
                  << "set_matrix() method or use the solve() method where\n"
                  << "you can specify the matrix associated to the system\n"
                  << "of equations." << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
  
 }
 
 // ===================================================================
 /// Solve a system of equations with the already stored matrix A. We
 /// specify the right-hand side b and the x vectors where the result
 /// is returned. We assume that the input/output vectors have the
 /// correct dimensions: A.n_columns() for b, and A.n_rows() for x.
 // ===================================================================
 void CCLUSolverNumericalRecipes::solve(const ACVector<Real> *const b_pt,
                                        ACVector<Real> *const x_pt)
 {
  // We can only call solve if the matrix A has been set
  if (this->Matrix_A_has_been_set)
   {
    // Check correct size of the matrix, right hand side and solution
    // vector
    if (this->A_pt->n_columns() != b_pt->n_values())
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The number of columns of the matrix and the number "
                    << "of rows of the rhs vector are not the same:\n"
                    << "A_pt->n_columns() = (" << this->A_pt->n_columns() << ")\n"
                    << "b_pt->n_values() = (" << b_pt->n_values() << ")\n" << std::endl;
      throw SciCellxxLibError(error_message.str(),
                             SCICELLXX_CURRENT_FUNCTION,
                             SCICELLXX_EXCEPTION_LOCATION);
     }
    
    // Check whether the solution vector is a column vector
    if (!x_pt->is_column_vector())
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The solution vector is not a column vector\n"
                    << std::endl;
      throw SciCellxxLibError(error_message.str(),
                             SCICELLXX_CURRENT_FUNCTION,
                             SCICELLXX_EXCEPTION_LOCATION);
     }
    
    // Check whether the solution matrix has allocated memory,
    // otherwise allocate it here!!!
    if (!x_pt->is_own_memory_allocated())
     {
      // Allocate memory
      x_pt->allocate_memory(this->A_pt->n_rows());
     }
    else
     {
      if (this->A_pt->n_rows() != x_pt->n_values())
       {
        // Error message
        std::ostringstream error_message;
        error_message << "The number of rows of the matrix and the number "
                      << "of rows of the solution vector are not the same:\n"
                      << "A_pt->n_rows() = (" << this->A_pt->n_rows() << ")\n"
                      << "x_pt->n_values() = (" << x_pt->n_values() << ")\n" << std::endl;
        throw SciCellxxLibError(error_message.str(),
                               SCICELLXX_CURRENT_FUNCTION,
                               SCICELLXX_EXCEPTION_LOCATION);
       }
      
     }
    
    // Factorise
    factorise();
    
    // ... and do back substitution
    back_substitution(b_pt, x_pt);
    
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not specific any matrix for the system of\n"
                  << "equations. Set one matrix first by calling the/"
                  << "set_matrix() method or use the solve() method where\n"
                  << "you can specify the matrix associated to the system\n"
                  << "of equations." << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
  
 }
 
 // ===================================================================
 /// Re-solve a system of equations with the already stored matrix
 /// A. Reusing the LU decomposition. We specify the right-hand side B
 /// and the X matrices where the results are returned. We assume that
 /// the input/output vectors have the correct dimensions: A.n_columns()
 /// x A.n_rows() for B, and A.n_rows() x A.n_columns() for X.
 // ===================================================================
 void CCLUSolverNumericalRecipes::resolve(const ACMatrix<Real> *const B_pt,
                                          ACMatrix<Real> *const X_pt)
 {
  // We can only do back-substitution if a matrix has been factorised
  if (Resolve_enabled)
   {
    // Check whether the solution matrix has allocated memory,
    // otherwise allocate it here!!!
    if (!X_pt->is_own_memory_allocated())
     {
      // Allocate memory
      X_pt->allocate_memory(this->A_pt->n_rows(), B_pt->n_columns());
     }
    else
     {
      if (this->A_pt->n_rows() != X_pt->n_rows())
       {
        // Error message
        std::ostringstream error_message;
        error_message << "The number of rows of the matrix and the number "
                      << "of rows of the solution matrix are not the same:\n"
                      << "A_pt->n_rows() = (" << this->A_pt->n_rows() << ")\n"
                      << "X_pt->n_rows() = (" << X_pt->n_rows() << ")\n" << std::endl;
        throw SciCellxxLibError(error_message.str(),
                               SCICELLXX_CURRENT_FUNCTION,
                               SCICELLXX_EXCEPTION_LOCATION);
       }
      
      if (B_pt->n_columns() != X_pt->n_columns())
       {
        // Error message
        std::ostringstream error_message;
        error_message << "The number of columns of the rhs matrix and the number"
                      << "of columns of the solution matrix are not the same:\n"
                      << "n_rhs = (" << B_pt->n_columns() << ")\n"
                      << "X_pt->n_columns() = (" << X_pt->n_columns() << ")\n"
                      << std::endl;
        throw SciCellxxLibError(error_message.str(),
                               SCICELLXX_CURRENT_FUNCTION,
                               SCICELLXX_EXCEPTION_LOCATION);
       }
      
     }
    
    // Do the back substitution
    back_substitution(B_pt, X_pt);
    
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Resolve is not enabled.\n" << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
  
 }
 
 // ===================================================================
 /// Re-solve a system of equations with the already stored matrix A
 /// (re-use of the LU decomposition or call the solve method for an
 /// iterative solver). BROKEN beacuse iterative solvers may not
 /// implement it. We specify the right-hand side b and the x vector
 /// where the result is returned. We assume that the input/output
 /// vectors have the correct dimensions: A.n_columns() for b, and
 /// A.n_rows() for x.
 // ===================================================================
 void CCLUSolverNumericalRecipes::resolve(const ACVector<Real> *const b_pt,
                                          ACVector<Real> *const x_pt)
 {
  // We can only do back-substitution if a matrix has been factorised
  if (Resolve_enabled)
   {
    // Check whether the solution vector is a column vector
    if (!x_pt->is_column_vector())
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The solution vector is not a column vector\n"
                    << std::endl;
      throw SciCellxxLibError(error_message.str(),
                             SCICELLXX_CURRENT_FUNCTION,
                             SCICELLXX_EXCEPTION_LOCATION);
     }
    
    // Check whether the solution matrix has allocated memory,
    // otherwise allocate it here!!!
    if (!x_pt->is_own_memory_allocated())
     {
      // Allocate memory
      x_pt->allocate_memory(this->A_pt->n_rows());
     }
    else
     {
      if (this->A_pt->n_rows() != x_pt->n_values())
       {
        // Error message
        std::ostringstream error_message;
        error_message << "The number of rows of the matrix and the number "
                      << "of rows of the solution vector are not the same:\n"
                      << "A_pt->n_rows() = (" << this->A_pt->n_rows() << ")\n"
                      << "x_pt->n_values() = (" << x_pt->n_values() << ")\n" << std::endl;
        throw SciCellxxLibError(error_message.str(),
                               SCICELLXX_CURRENT_FUNCTION,
                               SCICELLXX_EXCEPTION_LOCATION);
       }

     }
    
    // Do the back substitution
    back_substitution(b_pt, x_pt);
    
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Resolve is not enabled.\n" << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
  
 }
 
 // ===================================================================
 /// Performs LU factorisation of the input matrix, the factorisation is
 /// internally stored such that it can be re-used when calling resolve
 // ===================================================================
 void CCLUSolverNumericalRecipes::factorise(ACMatrix<Real> *const A_mat_pt)
 {
  // Set the matrix and its size
  set_matrix_A(A_mat_pt);
  
  // Factorise
  factorise();
  
 }
 
 // ===================================================================
 /// Performs LU factorisation of already stored matrix A, the
 /// factorisation is internally stored such that it can be re-used when
 /// calling resolve
 // ===================================================================
 void CCLUSolverNumericalRecipes::factorise()
 {
  // Prepare the matrix to call ludcmp() from Numerical Recipes
 
  // Check that we are working with an square matrix, otherwise this
  // will not work
  const unsigned long n_rows = this->A_pt->n_rows();
  const unsigned long n_columns = this->A_pt->n_columns();
  if (n_rows!=n_columns)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The matrix is not square." << std::endl
                  << "The matrix is of size: " << n_rows << " x "
                  << n_columns << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
  
  // The matrix used as input and output, after calling ludcmp it has
  // the LU factorisation
  lu_a = new Mat_DP(this->A_pt->matrix_pt(), n_rows, n_columns);
  
  // Output vector of size n x 1 that records the row permutations
  // performed by partial pivoting.
  lu_indx = new Vec_INT(n_rows);
  
  // An output indicating whether the number of rows interchanges was
  // even or odd (+1 or -1, respectively)
  DP dummy;
  
#if 0
  // Copy the matrix A to the representation required by ludcmp()
  for (unsigned i = 0; i < nrows; i++)
   {
    for (unsigned j = 0; j < ncolumns; j++)
     {
      *(*(lu_a)[i])[j] = this->(*A_pt)(i,j);
     }
   }
#endif // #if 0
  
  // Do the factorisation
  NR::ludcmp(*lu_a, *lu_indx, dummy);
  
  // Set the flag to indicate that resolve is enabled since we have
  // computed the LU decomposition
  Resolve_enabled = true; 
  
 }
 
 // ===================================================================
 /// Performs the back substitution with the LU decomposed matrix
 // ===================================================================
 void CCLUSolverNumericalRecipes::back_substitution(const ACMatrix<Real> *const B_pt,
                                                    ACMatrix<Real> *const X_output_pt)
 {
  // Prepare the data to call lubksb()
  
  // The size of the right-hand side
  const unsigned n_rows = B_pt->n_rows();
  
  // Number of right hand sizes (same as the number of output
  // X-vectors)
  const unsigned n_rhs = B_pt->n_columns();
  
  // The solution vector size n x 1 (Numerical Recipes definition)
  Vec_DP x(n_rows);
 
  // Copy the right-hand side into the solution vectors
  for (unsigned j = 0; j < n_rhs; j++)
   {
    for (unsigned i = 0; i < n_rows; i++)
     {
      x[i] = (*B_pt)(i,j);
     }
   
    // Back-substitution
    NR::lubksb(*lu_a, *lu_indx, x);
   
    // Copy the solution into the output vector
    for (unsigned i = 0; i < n_rows; i++)
     {
      (*X_output_pt)(i, j) =  x[i];
     }
    
   }
  
 }
 
 // ===================================================================
 /// Performs the back substitution with the LU decomposed matrix
 // ===================================================================
 void CCLUSolverNumericalRecipes::back_substitution(const ACVector<Real> *const b_pt,
                                                    ACVector<Real> *const x_output_pt)
 {
  // Prepare the data to call lubksb()
  
  // The size of the right-hand side
  const unsigned n_rows = b_pt->n_values();
  
  // The solution vector size n x 1 (Numerical Recipes definition)
  Vec_DP x(n_rows);
  
  // Copy the right-hand side into the solution vector
  for (unsigned i = 0; i < n_rows; i++)
   {
    x[i] = (*b_pt)(i);
   }
   
  // Back-substitution
  NR::lubksb(*lu_a, *lu_indx, x);
  
  // Copy the solution into the output vector
  for (unsigned i = 0; i < n_rows; i++)
   {
    (*x_output_pt)(i) =  x[i];
   }
  
 }
 
}
