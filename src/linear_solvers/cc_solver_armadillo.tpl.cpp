// IN THIS FILE: Implementation of the concrete class
// CCSolverArmadillo to solve systems of equations. This class calls
// the methods solve() or spsolve() from Armadillo to perform the
// solution of the system of equations.

#include "cc_solver_armadillo.tpl.h"

namespace chapchom
{

 // ===================================================================
 // Empty constructor
 // ===================================================================
 template<class T>
 CCSolverArmadillo<T>::CCSolverArmadillo()
  : ACLinearSolver<CCMatrixArmadillo<T>, CCVectorArmadillo<T> >()
 { }

 // ===================================================================
 // Constructor where we specify the matrix A of size m X n
 // ===================================================================
 template<class T>
 CCSolverArmadillo<T>::CCSolverArmadillo(const CCMatrixArmadillo<T> &A)
  : ACLinearSolver<CCMatrixArmadillo<T>, CCVectorArmadillo<T> >(A)
 { }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class T>
 CCSolverArmadillo<T>::~CCSolverArmadillo() { }

 // ===================================================================
 // Solves a system of equations with input A_mat. We specify the
 // right-hand side B and the X matrices where the results are
 // returned. We assume that the input/output matrices have the
 // correct dimensions: A_mat.n_columns() x A_mat.n_rows() for B, and
 // A_mat.n_rows() x A_mat.n_columns() for X.
 // ===================================================================
 template<class T>
 void CCSolverArmadillo<T>::solve(const CCMatrixArmadillo<T> &A_mat,
                                  const CCMatrixArmadillo<T> &B,
                                  CCMatrixArmadillo<T> &X)
 {
  // Set the matrix and its size
  this->set_matrix_A(A_mat);
  // Call the solving method
  this->solve(B, X);
 }
 
 // ===================================================================
 // Solves a system of equations with input A_mat. We specify the
 // right-hand side b and the x vector where the result is
 // returned. We assume that the input/output vectors have the correct
 // dimensions: A_mat.n_columns() for b, and A_mat.n_rows() for x.
 // ===================================================================
 template<class T>
 void CCSolverArmadillo<T>::solve(const CCMatrixArmadillo<T> &A_mat,
                                  const CCVectorArmadillo<T> &b,
                                  CCVectorArmadillo<T> &x)
 {
  // Set the matrix and its size
  this->set_matrix_A(A_mat);
  // Call the solving method
  this->solve(b, x);
 }
 
 // ===================================================================
 // Solve a system of equations with the already stored matrix A. We
 // specify the right-hand side B and the X matrices where the results
 // are returned. We assume that the input/output matrices have the
 // correct dimensions: A.n_columns() x A.n_rows() for B, and A.n_rows()
 // x A.n_columns() for X.
 // ===================================================================
  template<class T>
    void CCSolverArmadillo<T>::solve(const CCMatrixArmadillo<T> &B,
                                     CCMatrixArmadillo<T> &X)
  {
   // We can only call solve if the matrix A has been set
   if (this->Matrix_A_has_been_set)
    {
     // Check correct size of the matrix, right hand side and solution
     // vector    
     if (this->A.n_columns() != B.n_rows())
      {
       // Error message
       std::ostringstream error_message;
       error_message << "The number of columns of the matrix and the number "
                     << "of rows of the rhs matrix are not the same:\n"
                     << "A.n_columns() = (" << this->A.n_columns() << ")\n"
                     << "B.n_rows() = (" << B.n_rows() << ")\n" << std::endl;
       throw ChapchomLibError(error_message.str(),
                              CHAPCHOM_CURRENT_FUNCTION,
                              CHAPCHOM_EXCEPTION_LOCATION);
      }
     else if (this->A.n_rows() != X.n_rows())
      {
       // Error message
       std::ostringstream error_message;
       error_message << "The number of rows of the matrix and the number "
                     << "of rows of the solution matrix are not the same:\n"
                     << "A.n_rows() = (" << this->A.n_rows() << ")\n"
                     << "X.n_rows() = (" << X.n_rows() << ")\n" << std::endl;
       throw ChapchomLibError(error_message.str(),
                              CHAPCHOM_CURRENT_FUNCTION,
                              CHAPCHOM_EXCEPTION_LOCATION);
      }
     
     // Check whether the solution matrix has allocated memory,
     // otherwise allocate it here!!!
     if (!X.is_own_memory_allocated())
      {
       // Allocate memory
       X.allocate_memory();
      }
     
     // Get pointers to the Armadillo's matrices
     arma::Mat<T> *arma_A_pt = this->A.arma_matrix_pt();
     arma::Mat<T> *arma_B_pt = B.arma_matrix_pt();
     arma::Mat<T> *arma_X_pt = X.arma_matrix_pt();
     
     // Solve
     bool could_solve = arma::solve(*arma_X_pt, *arma_A_pt, *arma_B_pt);
     //bool could_solve = arma::solve(*arma_x_pt, *arma_A_pt, *arma_B_pt, arma::solve_opts::equilibrate);
     //bool could_solve = arma::solve(*arma_x_pt, *arma_A_pt, *arma_B_pt, arma::solve_opts::equilibrate + arma::solve_opts::no_approx);
     //bool could_solve = arma::solve(*arma_x_pt, *arma_A_pt, *arma_B_pt, arma::solve_opts::fast);
     if (!could_solve)
      {
       // Error message
       std::ostringstream error_message;
       error_message << "The systems of equations could not be solve. Please check\n"
                     << "additional parameters for solving in Armadillo's documentation\n"
                     << "solve_opts::fast\n"
                     << "solve_opts::equilibrate\n"
                     << "solve_opts::no_approx\n"
                     << std::endl;
       throw ChapchomLibError(error_message.str(),
                              CHAPCHOM_CURRENT_FUNCTION,
                              CHAPCHOM_EXCEPTION_LOCATION);
      
      }
    
    }
   else
    {
     // Error message
     std::ostringstream error_message;
     error_message << "You have not specified any matrix for the system of\n"
                   << "equations. Set one matrix first by calling the\n"
                   << "set_matrix() method or use the solve() method where\n"
                   << "you can specify the matrix associated to the system\n"
                   << "of equations." << std::endl;
     throw ChapchomLibError(error_message.str(),
                            CHAPCHOM_CURRENT_FUNCTION,
                            CHAPCHOM_EXCEPTION_LOCATION);
    }
  
  }
 
 // ===================================================================
 // Solve a system of equations with the already stored matrix A. We
 // specify the right-hand side b and the x vectors where the result
 // is returned. We assume that the input/output vectors have the
 // correct dimensions: A.n_columns() for b, and A.n_rows() for x.
 // ===================================================================
 template<class T>
 void CCSolverArmadillo<T>::solve(const CCVectorArmadillo<T> &b,
                                  CCVectorArmadillo<T> &x)
 {
  // We can only call solve if the matrix A has been set
  if (this->Matrix_A_has_been_set)
   {
    // The vectors b and x must be column vectors
    if (!b.is_column_vector())
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The vector b must be a column vector and it is not!" << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }

    if (!x.is_column_vector())
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The vector x (solution) must be a column vector and it is not!" << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }
    
    // Check correct size of the matrix, right hand side and solution
    // vector
    if (this->A.n_columns() != b.n_values())
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The number of columns of the matrix and the number "
                    << "of rows of the rhs vector are not the same:\n"
                    << "A.n_columns() = (" << this->A.n_columns() << ")\n"
                    << "b.n_values() = (" << b.n_values() << ")\n" << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }
    else if (this->A.n_rows() != x.n_values())
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The number of rows of the matrix and the number "
                    << "of rows of the solution vector are not the same:\n"
                    << "A.n_rows() = (" << this->A.n_rows() << ")\n"
                    << "x.n_values() = (" << x.n_values() << ")\n" << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }
    
    // Check whether the solution vector has allocated memory,
    // otherwise allocate it here!!!
    if (!x.is_own_memory_allocated())
     {
      // Allocate memory
      x.allocate_memory();
     }
    
    // Get pointers to the Armadillo's matrices
    arma::Mat<T> *arma_A_pt = this->A.arma_matrix_pt();
    arma::Mat<T> *arma_b_pt = b.arma_vector_pt();
    arma::Mat<T> *arma_x_pt = x.arma_vector_pt();
    
    // Solve
    bool could_solve = arma::solve(*arma_x_pt, *arma_A_pt, *arma_b_pt);
    //bool could_solve = arma::solve(*arma_x_pt, *arma_A_pt, *arma_B_pt, arma::solve_opts::equilibrate);
    //bool could_solve = arma::solve(*arma_x_pt, *arma_A_pt, *arma_B_pt, arma::solve_opts::equilibrate + arma::solve_opts::no_approx);
    //bool could_solve = arma::solve(*arma_x_pt, *arma_A_pt, *arma_B_pt, arma::solve_opts::fast);
    if (!could_solve)
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The systems of equations could not be solve. Please check\n"
                    << "additional parameters for solving in Armadillo's documentation\n"
                    << "solve_opts::fast\n"
                    << "solve_opts::equilibrate\n"
                    << "solve_opts::no_approx\n"
                    << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
      
     }
    
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
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
 }
 
}

