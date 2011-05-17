#ifndef Mu2eG4_nestTorus_hh
#define Mu2eG4_nestTorus_hh
//
// Free function to create and place a new G4Torus inside a logical volume.
// 
// $Id: nestTorus.hh,v 1.6 2011/05/17 15:41:36 greenc Exp $
// $Author: greenc $ 
// $Date: 2010/03/15
//

#include <string>
#include <vector>

#include "G4Helper/inc/VolumeInfo.hh"

class G4Material;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4CSGSolid;

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Colour.hh"


namespace mu2e {

  VolumeInfo nestTorus ( std::string const& name,
                         double const halfDim[5],
                         G4Material* material,
                         G4RotationMatrix* rot,
                         G4ThreeVector const& offset,
                         G4LogicalVolume* parent,
                         int copyNo,
                         bool const isVisible,
                         G4Colour const color,
                         bool const forceSolid,
                         bool const forceAuxEdgeVisible,
                         bool const placePV,
                         bool const doSurfaceCheck
                         );
  


  // Alternate argument list, using a vector for the half dimensions.
  inline VolumeInfo nestTorus ( std::string const& name,
                                std::vector<double>&  halfDim,
                                G4Material* material,
                                G4RotationMatrix* rot,
                                G4ThreeVector& offset,
                                G4LogicalVolume* parent,
                                int copyNo,
                                bool const isVisible,
                                G4Colour const color,
                                bool const forceSolid,
                                bool const forceAuxEdgeVisible,
                                bool const placePV,
                                bool const doSurfaceCheck
                                ){
    return nestTorus( name, 
                      &halfDim[0],
                      material,
                      rot,
                      offset,
                      parent,
                      copyNo,
                      isVisible,
                      color,
                      forceSolid,
                      forceAuxEdgeVisible,
                      placePV,
                      doSurfaceCheck
                      );
  }


  // Alternate argument list (and different behavior)
  // using  VolumeInfo object 
  VolumeInfo nestTorus ( std::string const& name,
                         double const halfDim[5],
                         G4Material* material,
                         G4RotationMatrix* rot,
                         G4ThreeVector const& offset,
                         const VolumeInfo& parent,
                         int copyNo,
                         bool const isVisible,
                         G4Colour const color,
                         bool const forceSolid,
                         bool const forceAuxEdgeVisible,
                         bool const placePV,
                         bool const doSurfaceCheck
                         );
  

  // Alternate argument list, using (and different behavior)
  // using  VolumeInfo object aand vector for the half dimensions.
  inline VolumeInfo nestTorus ( std::string const& name,
                                std::vector<double>&  halfDim,
                                G4Material* material,
                                G4RotationMatrix* rot,
                                G4ThreeVector& offset,
                                const VolumeInfo& parent,
                                int copyNo,
                                bool const isVisible,
                                G4Colour const color,
                                bool const forceSolid,
                                bool const forceAuxEdgeVisible,
                                bool const placePV,
                                bool const doSurfaceCheck
                                ){
    return nestTorus( name, 
                      &halfDim[0],
                      material,
                      rot,
                      offset,
                      parent,
                      copyNo,
                      isVisible,
                      color,
                      forceSolid,
                      forceAuxEdgeVisible,
                      placePV,
                      doSurfaceCheck
                      );
  }

}

#endif /* Mu2eG4_nestTorus_hh */
