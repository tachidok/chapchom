// This demo driver is based on the Program 1.2 DistanceMatrixFit.m
// from the book "Meshfree Approximation Methods with MATLAB, Gregory
// E. Fasshauer", World Scientific Publishing, 2007

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"

// Matrices
#include "../../../src/matrices/cc_matrix.h"

using namespace chapchom;

const double test_function(CCVector<double> &x, const unsigned s)
{
 double prod=1.0;
 for (unsigned i = 0; i < s; i++)
  {
   prod*=x(i)*(1.0-x(i));
  }
 return pow(4, s)*prod;
}

void compute_distance_matrix(CCVector &data_sites, CCVector &centers,
                             CCMatrix &distance_matrix)
{
 const unsigned n_rows = data_sites.size();
 const unsigned n_columns = centers.size();
 for (unsigned i = 0; i < n_rows; i++)
  {
   for (unsigned j = 0; j < n_columns; j++)
    {
     const double dsi = data_sites(i);
     const double cj = centers(j);
     distance_matrix(i,j)=(dsi-cj)*(dsi-cj);
    }
  }
}

// ==================================================================
// ==================================================================
// ==================================================================
// Main function
// ==================================================================
// ==================================================================
// ==================================================================
int main(int argc, char *argv[])
{
 // Initialise chapchom
 initialise_chapchom();
 
 // Finalise chapcom
 finalise_chapchom();
 
 return 0;
 
}
