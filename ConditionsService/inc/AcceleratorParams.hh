#ifndef ConditionsService_AcceleratorParams_hh
#define ConditionsService_AcceleratorParams_hh
//
// Some parameters of the accelerator complex.
//
// $Id: AcceleratorParams.hh,v 1.3 2011/05/17 15:41:35 greenc Exp $
// $Author: greenc $
// $Date: 2011/05/17 15:41:35 $
//
// Original author Rob Kutschke
//

// C++ includes.
#include <iostream>

// Mu2e includes.
#include "ConditionsService/inc/ConditionsEntity.hh"

namespace mu2e
{
  class SimpleConfig;

  struct AcceleratorParams: public ConditionsEntity{

    // The nominal debuncher orbital period.
    double deBuncherPeriod;

    AcceleratorParams ( SimpleConfig const& config );

    // Accept compiler generated:
    // copy c'tor, d'tor and assignment operator.

  private:

    // We want to discourage multi-phase construction.
    AcceleratorParams ();

  };

  // Shift left (printing) operator.
  inline std::ostream& operator<<(std::ostream& ost,
                                  const AcceleratorParams& lw ){
    ost << "( "
        << lw.deBuncherPeriod << ", "
        << " )";

    return ost;
  }

}

#endif /* ConditionsService_AcceleratorParams_hh */
