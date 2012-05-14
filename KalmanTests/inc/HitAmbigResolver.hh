//
// class to resolve hit ambiguities by panel, assuming a reasonable track
// fit as input
//
// $Id: HitAmbigResolver.hh,v 1.1 2012/05/14 19:20:02 brownd Exp $
// $Author: brownd $ 
// $Date: 2012/05/14 19:20:02 $
//
#ifndef HitAmbigResolver_HH
#define HitAmbigResolver_HH
#include "BaBar/BaBar.hh"
#include "KalmanTests/inc/AmbigResolver.hh"
#include "KalmanTests/inc/TrkStrawHitState.hh"
#include "fhiclcpp/ParameterSet.h"
#include "KalmanTests/inc/TrkDef.hh"
#include <cstddef>
#include <vector>

class TrkDifTraj;
class KalRep;

namespace mu2e {

  class HitAmbigResolver : public AmbigResolver {
    public:
      enum trajtype {reftraj=0};
// construct from parameter set
      explicit HitAmbigResolver(fhicl::ParameterSet const&);
      virtual ~HitAmbigResolver();
// resolve a track.  Depending on the configuration, this might
// update the hit state and the t0 value.
      virtual void resolveTrk(TrkKalFit& kfit) const;
    private:
// penalty function depends on the drift radius
      double penaltyError(double rdrift) const;
      double _mindrift; // minimum drift to assign an ambiguity.  Below this, an ambiguity of '0' is defined
      double _zeropenalty; // special penalty for drifts below the minimum
      bool _penalty; // apply penalty or notA
// exponential + linear fit to ambiguity mis-assignment
      double _expnorm;
      double _lambda;
      double _offset;
      double _slope;
  };
}
#endif
