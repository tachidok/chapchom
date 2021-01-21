#include "cc_factory_time_stepper.h"

namespace chapchom
{

 // ===================================================================
 /// Empty constructor
 // ===================================================================
 CCFactoryTimeStepper::CCFactoryTimeStepper()
 { 

 }

 // ===================================================================
 /// Empty destructor
 // ===================================================================
 CCFactoryTimeStepper::~CCFactoryTimeStepper()
 { 

 }

 // ===================================================================
 /// Returns the specified time stepper (integration method)
 // ===================================================================
 ACTimeStepper* CCFactoryTimeStepper::create_time_stepper(std::string time_stepper_name)
 {
  // Get the string and change it to lower case 
  std::transform(time_stepper_name.begin(), time_stepper_name.end(),
                 time_stepper_name.begin(), ::tolower);
  
  // ------------------------------------------------------
  // Check what time stepper method we need to create
  // ------------------------------------------------------
  // Euler method
  if (time_stepper_name.compare("euler")==0)
   {
    return new CCEulerMethod();
   }
  // Runge-Kutta 4 method
  else if (time_stepper_name.compare("rk4")==0)
   {
    return new CCRK4Method();
   }
  // Backward-Euler as Predictor-Corrector method
  else if (time_stepper_name.compare("bepc")==0)
   {
    return new CCAdamsMoulton2PCMethod();
   }
  // Adams-Moulton 2 as Predictor-Corrector method
  else if (time_stepper_name.compare("am2pc")==0)
   {
    return new CCAdamsMoulton2PCMethod();
   }
  // Backward Euler method
  else if (time_stepper_name.compare("bdf1")==0)
   {
    return new CCBackwardEulerMethod();
   }
  // Adams-Moulton 2 or Trapezoidal Rule method
  else if (time_stepper_name.compare("am2")==0)
   {
    return new CCAdamsMoulton2Method();
   }
  // BDF 2 method
  else if (time_stepper_name.compare("bdf2")==0)
   {
    return new CCBDF2Method();
   }
  // Runge-Kutta 4(5) Fehlberg method
  else if (time_stepper_name.compare("rk45f")==0)
   {
    return new CCAdaptiveRK45FMethod();
   }
  // Runge-Kutta 4(5) Dormand-Prince method
  else if (time_stepper_name.compare("rk45dp")==0)
   {
    return new CCAdaptiveRK45DPMethod();
   }
  else
   {
    std::ostringstream error_message;
    error_message << "The time stepper (integration method) you want to use is not "
                  << "implemented yet. Please implement it yourself or select"
                  << "another one\n\n"
                  << "Availables ones\n"
                  << "- Euler (euler)\n"
                  << "- Runge-Kutta 4 (rk4)\n"
                  << "- Adams-Moulton 2 - Predictor-Corrector (am2pc)\n"
                  << "- Backward Euler - Fully Implicit (bdf1)\n"
                  << "- Adams-Moulton 2 - Fully Implicit (am2)\n"
                  << "- Backward Differentiation Formula 2 - Fully Implicit (bdf2)\n"
                  << "- Adaptive Runge-Kutta 4(5) Fehlberg (rk45f)\n"
                  << "- Adaptive Runge-Kutta 4(5) Dormand-Prince (rk45dp)\n"
                  << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
  
 }

}

