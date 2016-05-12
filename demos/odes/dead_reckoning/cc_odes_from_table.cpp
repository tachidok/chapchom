/** \file This file implements the CCODEsFromTable class
 */

#include "cc_odes_from_table.h"

// ===================================================================
// Constructor, sets the number of odes. We currently have two odes,
// one for the velocity and the other for the acceleration
// ===================================================================
CCODEsFromTable::CCODEsFromTable()
 : CAODEs(2)
{ }

// ===================================================================
// Empty destructor
// ===================================================================
CCODEsFromTable::~CCODEsFromTable()
{ }

// ===================================================================
// Evaluates the system of odes at the given time "t" and the values
// of the function in "y". The evaluation produces results in the dy
// vector
// ===================================================================
void CCODEsFromTable::evaluate(const double t,
			       const std::vector<double> &y,
			       std::vector<double> &dy)
{

}
 
// ===================================================================
// Evaluates the specified ode by "i" of the system of odes at the
// given time "t" and the values of the function in "y". The
// evaluation produces results in the dy vector at the dy[i] position
// ===================================================================
void CCODEsFromTable::evaluate(const unsigned i, const double t,
			       const std::vector<double> &y,
			       std::vector<double> &dy)
{

}
 
