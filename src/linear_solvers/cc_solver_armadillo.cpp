/// IN THIS FILE: Implementation of the concrete class
/// CCSolverArmadillo to solve systems of equations. This class calls
/// the methods solve() or spsolve() from Armadillo to perform the
/// solution of the system of equations.

#include "cc_solver_armadillo.h"

namespace chapchom
{
 
 // ===================================================================
 /// Empty constructor
 // ===================================================================
 CCSolverArmadillo::CCSolverArmadillo()
  : ACLinearSolver()
 { }
 
 // ===================================================================
 /// Constructor where we specify the matrix A of size m X n
 // ===================================================================
 CCSolverArmadillo::CCSolverArmadillo(ACMatrix<Real> *const A_mat_pt)
  : ACLinearSolver(A_mat_pt)
 { }
 
 // ===================================================================
 /// Empty destructor
 // ===================================================================
 CCSolverArmadillo::~CCSolverArmadillo() { }
 
 // ===================================================================
 /// Solves a system of equations with input A_mat. We specify the
 /// right-hand side B and the X matrices where the results are
 /// returned. We assume that the input/output matrices have the
 /// correct dimensions: A_mat.n_columns() x A_mat.n_rows() for B, and
 /// A_mat.n_rows() x A_mat.n_columns() for X.
 // ===================================================================
 void CCSolverArmadillo::solve(ACMatrix<Real> *const A_mat_pt,
                               const ACMatrix<Real> *const B_pt,
                               ACMatrix<Real> *const X_pt)
 {
  // Set the matrix and its size
  this->set_matrix_A(A_mat_pt);
  // Call the solving method
  this->solve(B_pt, X_pt);
 }
 
 // ===================================================================
 /// Solves a system of equations with input A_mat. We specify the
 /// right-hand side b and the x vector where the result is
 /// returned. We assume that the input/output vectors have the correct
 /// dimensions: A_mat.n_columns() for b, and A_mat.n_rows() for x.
 // ===================================================================
 void CCSolverArmadillo::solve(ACMatrix<Real> *const A_mat_pt,
                               const ACVector<Real> *const b_pt,
                               ACVector<Real> *const x_pt)
 {
  // Set the matrix and its size
  this->set_matrix_A(A_mat_pt);
  // Call the solving method
  this->solve(b_pt, x_pt);
 }
 
 // ===================================================================
 /// Solve a system of equations with the already stored matrix A. We
 /// specify the right-hand side B and the X matrices where the results
 /// are returned. We assume that the input/output matrices have the
 /// correct dimensions: A.n_columns() x A.n_rows() for B, and A.n_rows()
 /// x A.n_columns() for X.
 // ===================================================================
 void CCSolverArmadillo::solve(const ACMatrix<Real> *const B_pt,
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
         error_message << "The number of columns of the rhs matrix and the number\n"
                       << "of columns of the solution matrix are not the same:\n"
                       << "n_rhs = (" << B_pt->n_columns() << ")\n"
                       << "X_pt->n_columns() = (" << X_pt->n_columns() << ")\n"
                       << std::endl;
         throw SciCellxxLibError(error_message.str(),
                                SCICELLXX_CURRENT_FUNCTION,
                                SCICELLXX_EXCEPTION_LOCATION);
        }
       
      }
     
     // Get pointers to the Armadillo's matrices
     arma::Mat<Real> *arma_A_pt = this->A_pt->arma_matrix_pt();
     arma::Mat<Real> *arma_B_pt = B_pt->arma_matrix_pt();
     arma::Mat<Real> *arma_X_pt = X_pt->arma_matrix_pt();
     
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
       throw SciCellxxLibError(error_message.str(),
                              SCICELLXX_CURRENT_FUNCTION,
                              SCICELLXX_EXCEPTION_LOCATION);
      
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
 void CCSolverArmadillo::solve(const ACVector<Real> *const b_pt,
                               ACVector<Real> *const x_pt)
 {
  // We can only call solve if the matrix A has been set
  if (this->Matrix_A_has_been_set)
   {
    // The vectors b and x must be column vectors
    if (!b_pt->is_column_vector())
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The vector b must be a column vector" << std::endl;
      throw SciCellxxLibError(error_message.str(),
                             SCICELLXX_CURRENT_FUNCTION,
                             SCICELLXX_EXCEPTION_LOCATION);
     }
    
    if (!x_pt->is_column_vector())
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The vector x (solution) must be a column vector" << std::endl;
      throw SciCellxxLibError(error_message.str(),
                             SCICELLXX_CURRENT_FUNCTION,
                             SCICELLXX_EXCEPTION_LOCATION);
     }
    
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
    
    // Check whether the solution vector has allocated memory,
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
    
    // Get pointers to the Armadillo's matrices
    arma::Mat<Real> *arma_A_pt = this->A_pt->arma_matrix_pt();
    arma::Mat<Real> *arma_b_pt = b_pt->arma_vector_pt();
    arma::Mat<Real> *arma_x_pt = x_pt->arma_vector_pt();
    
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
      throw SciCellxxLibError(error_message.str(),
                             SCICELLXX_CURRENT_FUNCTION,
                             SCICELLXX_EXCEPTION_LOCATION);
      
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
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
  
 }
 
}
