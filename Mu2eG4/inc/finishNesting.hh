#ifndef Mu2eG4_finishNesting_hh
#define Mu2eG4_finishNesting_hh
//
// Free function to be used by the nest... functions
// 
// $Id: finishNesting.hh,v 1.3 2011/05/17 15:41:36 greenc Exp $
// $Author: greenc $ 
// $Date: 2011/05/17 15:41:36 $
//
// Original author KLG
//


//class G4RotationMatrix;
//class G4ThreeVector;
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

class VolumeInfo;

class G4Material;
class G4LogicalVolume;
class G4Colour;

namespace mu2e {

  void finishNesting(VolumeInfo& info,
                     G4Material* material,
                     G4RotationMatrix* rot,
                     G4ThreeVector const & offset,
                     G4LogicalVolume* parent,
                     int copyNo,
                     bool const isVisible,
                     G4Colour const color,
                     bool const forceSolid,
                     bool const forceAuxEdgeVisible,
                     bool const placePV,
                     bool const doSurfaceCheck,
                     bool const verbose = false
                     );

}

#endif /* Mu2eG4_finishNesting_hh */
