/** \file This file implements the CCODEsBasicNBody class
 */
#include "cc_odes_basic_n_body.h"

namespace chapchom
{
 // ===================================================================
 // Constructor, sets the number of odes. We currently have 10 odes
 // ===================================================================
 CCODEsBasicNBody::CCODEsBasicNBody(const double g,
                                    const unsigned n_bodies)
  : ACODEs(n_bodies*DIM*2), // The times 2 is because we are storing
                            // the position and the velocity of each
                            // body
    N_bodies(n_bodies),
    G(g)
 {  
  // Resize the vector storing the masses
  M.resize(N_bodies);
  
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 CCODEsBasicNBody::~CCODEsBasicNBody()
 { }
 
 // ======================================================================
 /// Set initial conditions
 // ======================================================================
 void CCODEsBasicNBody::set_initial_conditions(std::vector<std::vector<double> > &y)
 {
  // Initial conditions for 1st body
  y[0][0] = 0.0; // x-position
  y[1][0] = 0.0; // x-velocity
  y[2][0] = 0.0; // y-position
  y[3][0] = 0.0; // y-velocity
  y[4][0] = 0.0; // z-position
  y[5][0] = 0.0; // z-velocity
  // Initial conditions for 2nd body
  y[6][0] = 0.0; // x-position
  y[7][0] = -2.75674; // x-velocity
  y[8][0] = 5.2; // y-position
  y[9][0] = 0.0; // y-velocity
  y[10][0] = 0.0; // z-position
  y[11][0] = 0.0; // z-velocity
#if 0
  // Initial conditions for 3rd body
  y[12][0] = -4.503; // x-position
  y[13][0] = -1.38; // x-velocity
  y[14][0] = 2.6; // y-position
  y[15][0] = -2.39; // y-velocity
  y[16][0] = 0.0; // z-position
  y[17][0] = 0.0; // z-velocity
  // Initial conditions for 4th body
  y[18][0] = 4.503; // x-position
  y[19][0] = -1.38; // x-velocity
  y[20][0] = 2.6; // y-position
  y[21][0] = 2.39; // y-velocity
  y[22][0] = 0.0; // z-position
  y[23][0] = 0.0; // z-velocity
#endif // #if 0
#if 1
  // Initial conditions for 3rd body
  y[12][0] = -0.5; // x-position
  y[13][0] = -0.03; // x-velocity
  y[14][0] = 4.8; // y-position
  y[15][0] = -0.3; // y-velocity
  y[16][0] = 0.0; // z-position
  y[17][0] = 0.0; // z-velocity
  // Initial conditions for 4th body
  y[18][0] = 0.5; // x-position
  y[19][0] = -0.03; // x-velocity
  y[20][0] = 5.6; // y-position
  y[21][0] = 0.3; // y-velocity
  y[22][0] = 0.0; // z-position
  y[23][0] = 0.0; // z-velocity 
#endif // #if 1
 }
 
 // ===================================================================
 /// Evaluates the system of odes at time "t". The values of the i-th
 /// function at previous times are accessible via y[i][1], y[i][2]
 /// and so on. The evaluation produces results in the vector dy.
 // ===================================================================
 void CCODEsBasicNBody::evaluate(const double t,
                                 const std::vector<std::vector<double> > &y,
                                 std::vector<double> &dy)
 {
  // -----------------
  // y[0][0] Current x-position of the 1st body
  // y[1][0] Current x-velocity of the 1st body
  // y[2][0] Current y-position of the 1st body
  // y[3][0] Current y-velocity of the 1st body
  // y[4][0] Current z-position of the 1st body
  // y[5][0] Current z-velocity of the 1st body
  // y[6][0] Current x-position of the 2nd body
  // y[7][0] Current x-velocity of the 2nd body
  // y[8][0] Current y-position of the 2nd body
  // y[9][0] Current y-velocity of the 2nd body
  // y[10][0] Current z-position of the 2nd body
  // y[11][0] Current z-velocity of the 2nd body
  // y[12][0] Current x-position of the 3rd body
  // y[13][0] Current x-velocity of the 3rd body
  // y[14][0] Current y-position of the 3rd body
  // y[15][0] Current y-velocity of the 3rd body
  // y[16][0] Current z-position of the 3rd body
  // y[17][0] Current z-velocity of the 3rd body
  // y[18][0] Current x-position of the 4th body
  // y[19][0] Current x-velocity of the 4th body
  // y[20][0] Current y-position of the 4th body
  // y[21][0] Current y-velocity of the 4th body
  // y[22][0] Current z-position of the 4th body
  // y[23][0] Current z-velocity of the 4th body
  // -----------------
  // dy[0] x-velocity of the 1st body
  // dy[1] x-acceleration of the 1st body
  // dy[2] y-velocity of the 1st body
  // dy[3] y-acceleration of the 1st body
  // dy[4] z-velocity of the 1st body
  // dy[5] z-acceleration of the 1st body
  // dy[6] x-velocity of the 2nd body
  // dy[7] x-acceleration of the 2nd body
  // dy[8] y-velocity of the 2nd body
  // dy[9] y-acceleration of the 2nd body
  // dy[10] z-velocity of the 2nd body
  // dy[11] z-acceleration of the 2nd body
  // dy[12] x-velocity of the 3rd body
  // dy[13] x-acceleration of the 3rd body
  // dy[14] y-velocity of the 3rd body
  // dy[15] y-acceleration of the 3rd body
  // dy[16] z-velocity of the 3rd body
  // dy[17] z-acceleration of the 3rd body
  // dy[18] x-velocity of the 4th body
  // dy[19] x-acceleration of the 4th body
  // dy[20] y-velocity of the 4th body
  // dy[21] y-acceleration of the 4th body
  // dy[22] z-velocity of the 4th body
  // dy[23] z-acceleration of the 4th body

  // A 3D matrix that stores the difference in position of each body
  // within each body for each dimension
  std::vector<std::vector<std::vector<double> > > diff_positions(N_bodies);
  
  // Resize and compute the difference between each body's position
  for (unsigned i = 0; i < N_bodies; i++)
   {
    diff_positions[i].resize(N_bodies);
    for (unsigned j = 0; j < N_bodies; j++)
     {
      diff_positions[i][j].resize(DIM);
      diff_positions[i][j][0] = y[6*i+0][0] - y[6*j+0][0];
      diff_positions[i][j][1] = y[6*i+2][0] - y[6*j+2][0];
      diff_positions[i][j][2] = y[6*i+4][0] - y[6*j+4][0];
     } // for (j < N_bodies)
   } // for (i < N_bodies)

  // Store the sum of the difference between bodies positions
  // multiplied by the masses of each body and the gravitational
  // constant
  // \sum_{j=1}^N, with i!=j G m_{j} (x_i-x_j) / |x_i-x_j|^3

  std::vector<std::vector<double> > sum(N_bodies);
  for (unsigned i = 0; i < N_bodies; i++)
   {
    // Resize and initialise sum to zero
    sum[i].resize(DIM, 0);
    for (unsigned j = 0; j < N_bodies; j++)
     {
      if (i != j)
       {
        for (unsigned k = 0; k < DIM; k++)
         { 
          sum[i][k]+=diff_positions[i][j][k]*M[j];
         } // for (k < DIM)
       } // if (i != j)
     } // for (j < N_bodies)
   } // for (i < N_bodies) 
  
  dy[0] = y[1][0];
  dy[1] = sum[0][0]*G;
  dy[2] = y[3][0];
  dy[3] = sum[0][1]*G;
  dy[4] = y[5][0];
  dy[5] = sum[0][2]*G;
  dy[6] = y[7][0];
  dy[7] = sum[1][0]*G;
  dy[8] = y[9][0];
  dy[9] = sum[1][1]*G;
  dy[10] = y[11][0];
  dy[11] = sum[1][2]*G;
  dy[12] = y[13][0];
  dy[13] = sum[2][0]*G;
  dy[14] = y[15][0];
  dy[15] = sum[2][1]*G;
  dy[16] = y[17][0];
  dy[17] = sum[2][2]*G;
  dy[18] = y[19][0];
  dy[19] = sum[3][0]*G;
  dy[20] = y[21][0];
  dy[21] = sum[3][1]*G;
  dy[22] = y[23][0];
  dy[23] = sum[3][2]*G;
  
 }
 
 // ===================================================================
 /// Evaluates the i-th ode at time "t". The values of the function
 /// at previous times are stores at y[1], y[2] and so on. The
 /// evaluation stores the result in dy.
 // ===================================================================
 void CCODEsBasicNBody::evaluate(const unsigned i, const double t,
                                 const std::vector<double> &y, double &dy)
 {
  // Error message
  std::ostringstream error_message;
  error_message << "This method is not implemented for this class"
                << std::endl;
  throw ChapchomLibError(error_message.str(),
                         CHAPCHOM_CURRENT_FUNCTION,
                         CHAPCHOM_EXCEPTION_LOCATION);
 }


}
