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
 // Solve a system of equations with input A. We specify the
 // right-hand side B and the X matrices where the results are
 // returned. We assume that the input/output matrices have the
 // correct dimensions: A.ncolumns() x A.nrows() for B, and A.nrows()
 // x A.ncolumns() for X.
 // ===================================================================
 template<class T>
 void CCSolverArmadillo<T>::solve(const CCMatrixArmadillo<T> &A,
                                  const CCMatrixArmadillo<T> &B,
                                  CCMatrixArmadillo<T> &X)
 {
  // Set the matrix and its size
  this->set_matrix_A(A);

  // Get pointers to the Armadillo's matrices
  arma::Mat<T> *arma_A_pt = A.arma_matrix_pt();
  arma::Mat<T> *arma_B_pt = B.arma_matrix_pt();
  arma::Mat<T> *arma_X_pt = X.arma_matrix_pt();
  
  // Solve
  bool could_solve = arma::solve(*arma_X_pt, *arma_A_pt, *arma_B_pt);
  //bool could_solve = arma::solve(*arma_X_pt, *arma_A_pt, *arma_B_pt, arma::solve_opts::equilibrate);
  //bool could_solve = arma::solve(*arma_X_pt, *arma_A_pt, *arma_B_pt, arma::solve_opts::equilibrate + arma::solve_opts::no_approx);
  //bool could_solve = arma::solve(*arma_X_pt, *arma_A_pt, *arma_B_pt, arma::solve_opts::fast);
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

 // ===================================================================
 // Solve a system of equations with input A. We specify the
 // right-hand side b and the x vector where the result is
 // returned. We assume that the input/output vectors have the
 // correct dimensions: A.ncolumns() for b, and A.nrows() for x.
 // ===================================================================
 template<class T>
 void CCSolverArmadillo<T>::solve(const CCMatrixArmadillo<T> &A,
                                  const CCVectorArmadillo<T> &b,
                                  CCVectorArmadillo<T> &x)
 {
  
 }
 
 // ===================================================================
 // Solve a system of equations with the already stored matrix A. We
 // specify the right-hand side B and the X matrices where the results
 // are returned. We assume that the input/output matrices have the
 // correct dimensions: A.ncolumns() x A.nrows() for B, and A.nrows()
 // x A.ncolumns() for X.
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
    if (this->A.ncolumns() != B.nrows())
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The number of columns of the matrix and the number "
                    << "of rows of the rhs matrix are not the same:\n"
                    << "A.ncolumns() = (" << this->A.ncolumns() << ")\n"
                    << "B.nrows() = (" << B.nrows() << ")\n" << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }
    else if (this->A.nrows() != X.nrows())
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The number of rows of the matrix and the number "
                    << "of rows of the solution matrix are not the same:\n"
                    << "A.nrows() = (" << this->A.nrows() << ")\n"
                    << "X.nrows() = (" << X.nrows() << ")\n" << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
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

 // ===================================================================
 // Solve a system of equations with the already stored matrix A. We
 // specify the right-hand side b and the x vectors where the result
 // is returned. We assume that the input/output vectors have the
 // correct dimensions: A.ncolumns() for b, and A.nrows() for x.
 // ===================================================================
 template<class T>
 void CCSolverArmadillo<T>::solve(const CCVectorArmadillo<T> &b,
                                  CCVectorArmadillo<T> &x)
 {
  
 }
 
}

