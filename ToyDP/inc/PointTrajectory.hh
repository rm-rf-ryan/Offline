#ifndef ToyDP_PointTrajectory_hh
#define ToyDP_PointTrajectory_hh
//
// A trajectory defined as a collection of 3D points.
// One can imagine that some day we will have smarter
// trajectory classes but this is what we have for now.
//
// $Id: PointTrajectory.hh,v 1.2 2011/05/17 15:41:36 greenc Exp $
// $Author: greenc $
// $Date: 2011/05/17 15:41:36 $
//
// Original author Rob Kutschke
//

#include <vector>
#include "CLHEP/Vector/ThreeVector.h"

namespace mu2e {

  class PointTrajectory{

  public:

    // Default c'tor needed by ROOT persistency.
    PointTrajectory():_simid(-1){
    }

    // Usual c'tor.
    PointTrajectory( int simid, std::vector<CLHEP::Hep3Vector> const& points):
      _simid(simid),
      _points(points){
    }

    // Accept compiler written d'tor, copy c'tor and assignment operator.
    
    // Accessors
    int   simId() const { return _simid; }
    size_t size() const { return _points.size(); }
    std::vector<CLHEP::Hep3Vector> const& points() const { return _points;}

    // The following c'tor and addPoints method form a two-phase c'tor.
    // This is needed in addPointTrajectories to avoid copying the vector
    // of points twice.  Once we have move aware containers we can
    // get rid of these.
    PointTrajectory( int simid ):
      _simid(simid),
      _points(){
    }

    // Second phase of the two phase constructor
    void addPoint( CLHEP::Hep3Vector const& p){
      _points.push_back(p);
    }

  private:

    int _simid;
    std::vector<CLHEP::Hep3Vector> _points;

  };

}

#endif /* ToyDP_PointTrajectory_hh */
