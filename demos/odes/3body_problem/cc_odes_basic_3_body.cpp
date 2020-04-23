/** \file This file implements the CCODEsBasic3Body class
 */
#include "cc_odes_basic_3_body.h"

namespace chapchom
{
 // ===================================================================
 // Constructor, sets the number of odes. We currently have 18 odes
 // ===================================================================
 CCODEsBasic3Body::CCODEsBasic3Body(const unsigned n_bodies)
  : ACODEs(n_bodies*DIM*2), // The times 2 is because we are storing
                            // the position and the velocity of each
                            // body
    N_bodies(n_bodies)
 {  
  // Resize the vector storing the masses
  M.resize(N_bodies);
  // Resize the vector storing the gravity
  G.resize(N_bodies);
  
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 CCODEsBasic3Body::~CCODEsBasic3Body()
 { }
 
 // ===================================================================
 /// Evaluates the system of odes at time "t". The values of the i-th
 /// function at previous times are accessible via u(i,1), u(i,2) and
 /// so on. The evaluation produces results in the vector dudt.
 // ===================================================================
 void CCODEsBasic3Body::evaluate_derivatives(const Real t,
                                             CCData &u,
                                             CCData &dudt,
                                             const unsigned k)
 {
  // -----------------
  // u(0,0) Current x-position of the 1st body
  // u(1,0) Current x-velocity of the 1st body
  // u(2,0) Current y-position of the 1st body
  // u(3,0) Current y-velocity of the 1st body
  // u(4,0) Current z-position of the 1st body
  // u(5,0) Current z-velocity of the 1st body
  // u(6,0) Current x-position of the 2nd body
  // u(7,0) Current x-velocity of the 2nd body
  // u(8,0) Current y-position of the 2nd body
  // u(9,0) Current y-velocity of the 2nd body
  // u(10,0) Current z-position of the 2nd body
  // u(11,0) Current z-velocity of the 2nd body
  // u(12,0) Current x-position of the 3rd body
  // u(13,0) Current x-velocity of the 3rd body
  // u(14,0) Current y-position of the 3rd body
  // u(15,0) Current y-velocity of the 3rd body
  // u(16,0) Current z-position of the 3rd body
  // u(17,0) Current z-velocity of the 3rd body
  // -----------------
  // dudt(0) x-velocity of the 1st body
  // dudt(1) x-acceleration of the 1st body
  // dudt(2) y-velocity of the 1st body
  // dudt(3) y-acceleration of the 1st body
  // dudt(4) z-velocity of the 1st body
  // dudt(5) z-acceleration of the 1st body
  // dudt(6) x-velocity of the 2nd body
  // dudt(7) x-acceleration of the 2nd body
  // dudt(8) y-velocity of the 2nd body
  // dudt(9) y-acceleration of the 2nd body
  // dudt(10) z-velocity of the 2nd body
  // dudt(11) z-acceleration of the 2nd body
  // dudt(12) x-velocity of the 3rd body
  // dudt(13) x-acceleration of the 3rd body
  // dudt(14) y-velocity of the 3rd body
  // dudt(15) y-acceleration of the 3rd body
  // dudt(16) z-velocity of the 3rd body
  // dudt(17) z-acceleration of the 3rd body
  
  // A 3D matrix that stores the difference in position of each body
  // within each body for each dimension
  std::vector<std::vector<std::vector<Real> > > diff_positions(N_bodies);
  
  // Resize and compute the difference between each body's position
  for (unsigned i = 0; i < N_bodies; i++)
   {
    diff_positions[i].resize(N_bodies);
    for (unsigned j = 0; j < N_bodies; j++)
     {
      diff_positions[i][j].resize(DIM);
      diff_positions[i][j][0] = u(6*i+0,0) - u(6*j+0,0);
      diff_positions[i][j][1] = u(6*i+2,0) - u(6*j+2,0);
      diff_positions[i][j][2] = u(6*i+4,0) - u(6*j+4,0);
     } // for (j < N_bodies)
   } // for (i < N_bodies)
  
  // Store the sum of the difference between bodies positions
  // multiplied by the masses of each body and the gravitational
  // constant
  // \sum_{j=1}^N, with i!=j G m_{j} (x_i-x_j) / ||x_i-x_j||^3
  
  std::vector<std::vector<Real> > norm_cubed(N_bodies);
  for (unsigned i = 0; i < N_bodies; i++)
   {
    // Resize and initialise norm to zero
    norm_cubed[i].resize(N_bodies, 0);
    for (unsigned j = 0; j < N_bodies; j++)
     {
      if (i != j)
       {
        for (unsigned d = 0; d < DIM; d++)
         {
          norm_cubed[i][j]+=(diff_positions[i][j][d]*diff_positions[i][j][d]);
         } // for (d < DIM)
        norm_cubed[i][j] = sqrt(norm_cubed[i][j]);
        norm_cubed[i][j] = norm_cubed[i][j] * norm_cubed[i][j] * norm_cubed[i][j];
       } // if (i != j)
     } // for (j < N_bodies)
   } // for (i < N_bodies) 

  dudt(0) = u(1,0);
  dudt(1) = (((m(1) * diff_positions[0][1][0]) / norm_cubed[0][1]) + ((m(2) * diff_positions[0][2][0]) / norm_cubed[0][2])) * g(0);
  dudt(2) = u(3,0);
  dudt(3) = (((m(1) * diff_positions[0][1][1]) / norm_cubed[0][1]) + ((m(2) * diff_positions[0][2][1]) / norm_cubed[0][2])) * g(0);
  dudt(4) = u(5,0);
  dudt(5) = (((m(1) * diff_positions[0][1][2]) / norm_cubed[0][1]) + ((m(2) * diff_positions[0][2][2]) / norm_cubed[0][2])) * g(0);
  dudt(6) = u(7,0);
  dudt(7) = (((m(0) * diff_positions[1][0][0]) / norm_cubed[1][0]) + ((m(2) * diff_positions[1][2][0]) / norm_cubed[1][2])) * g(1);
  dudt(8) = u(9,0);
  dudt(9) = (((m(0) * diff_positions[1][0][1]) / norm_cubed[1][0]) + ((m(2) * diff_positions[1][2][1]) / norm_cubed[1][2])) * g(1);
  dudt(10) = u(11,0);
  dudt(11) = (((m(0) * diff_positions[1][0][2]) / norm_cubed[1][0]) + ((m(2) * diff_positions[1][2][2]) / norm_cubed[1][2])) * g(1);
  dudt(12) = u(13,0);
  dudt(13) = (((m(0) * diff_positions[2][0][0]) / norm_cubed[2][0]) + ((m(1) * diff_positions[2][1][0]) / norm_cubed[2][1])) * g(2);
  dudt(14) = u(15,0);
  dudt(15) = (((m(0) * diff_positions[2][0][1]) / norm_cubed[2][0]) + ((m(1) * diff_positions[2][1][1]) / norm_cubed[2][1])) * g(2);
  dudt(16) = u(17,0);
  dudt(17) = (((m(0) * diff_positions[2][0][2]) / norm_cubed[2][0]) + ((m(1) * diff_positions[2][1][2]) / norm_cubed[2][1])) * g(2);
  
 }
 
}
