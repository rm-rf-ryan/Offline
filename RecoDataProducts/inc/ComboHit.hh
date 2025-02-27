#ifndef RecoDataProducts_ComboHit_hh
#define RecoDataProducts_ComboHit_hh
//
// Class to describe a combination of one or more StrawHits.
// These can be aggregated together through the dedicated collection
//
// Original author David Brown Dec 2017
//
// Mu2e includes
#include "Offline/DataProducts/inc/StrawEnd.hh"
#include "Offline/DataProducts/inc/StrawId.hh"
#include "Offline/DataProducts/inc/StrawIdMask.hh"
#include "Offline/DataProducts/inc/GenVector.hh"
#include "Offline/DataProducts/inc/TrkTypes.hh"
#include "Offline/RecoDataProducts/inc/StrawHitFlag.hh"
#include "Offline/RecoDataProducts/inc/StrawHitIndex.hh"
#include <stdint.h>
// art includes
#ifndef __ROOTCLING__
#include "art/Framework/Principal/Handle.h"
//#include "canvas/Persistency/Provenance/ProductID.h"
#endif
#include "canvas/Persistency/Common/ProductPtr.h"
// C++ includes
#include <array>
#include <vector>
namespace mu2e {

  struct ComboHit {
    enum edir{wire=0,trans,z}; // should switch to  UVW TODO
    constexpr static size_t MaxNCombo = 8;
    using PIArray = std::array<uint16_t,MaxNCombo>; // array of indices into parent collection
    // General accessors that apply to all kinds of combo hits
    auto const& pos() const { return _pos; }
    auto const& wdir() const { return _udir; } // legacy function
    // in UVW coordinate system
    auto const& uDir() const { return _udir; } // along wire
    auto const& vDir() const { return _vdir; } // perp to wire and Z
    auto wDir() const { return XYZVectorF(0.0,0.0,1.0); }
    auto centerPos() const { return _pos - _wdist*_udir; }
//
    float posRes(edir dir) const;
    auto energyDep() const { return _edep; }
    auto phi() const { return _pos.phi();} // legacy function
    auto timeRes() const { return _timeres; }
    auto timeVar() const { return _timeres*_timeres; }
    auto correctedTime() const { return _time; }
    auto qual() const { return _qual; }
    StrawHitFlag const& flag() const { return _flag; }
    StrawId const& strawId() const { return _sid; }
    auto uRes() const { return _ures; }
    auto uVar() const { return _ures*_ures; }
    auto wireRes() const { return uRes(); }
    auto wireVar() const { return uVar(); }
    auto vRes() const { return _vres; }
    auto vVar() const { return _vres*_vres; }
    auto wRes() const { return _wres; }
    auto wVar() const { return _wres*_wres; }
    auto transRes() const { return vRes(); }
    auto transVar() const { return vVar(); }

    auto uPos() const { return _wdist; }
    auto wireDist() const { return _wdist; }
    auto vPos() const { return _pos.Dot(vDir()); }
    // book-keeping accessors
    auto nCombo() const { return _ncombo; }
    auto nStrawHits() const { return _nsh; }
    auto const& mask() const { return _mask;}
    void init(ComboHit const& other, size_t index);
    auto index(size_t ish=0) const { return _pind.at(ish); }
    bool addIndex(size_t shi); // append an index to the
    auto const& indexArray() const { return _pind; }
    void print( std::ostream& ost = std::cout, bool doEndl = true ) const;
    // Accessors that only make sense for single-straw Combo hits
    auto TOT(StrawEnd end=StrawEnd::cal)       const { return _tot[end];}
     // compatibility constructor (deprecated)
    auto endTime(StrawEnd end=StrawEnd::cal)     const { return _etime[end];}
    auto const& TOTs() const { return _tot; }
    auto const& endTimes() const { return _etime; }
    StrawEnd const& earlyEnd() const { return _eend; } // End with earliest tdc time
    StrawEnd lateEnd() const { return _eend.otherEnd(); } // End with later tdc time
    // Accessors for hits used in helices
    auto helixPhi() const { return _hphi;}
    // interface returning calibration info: these should be refactored to
    // use StrawResponse TODO
    auto driftTime() const { return _dtime; }
    auto propTime() const { return _ptime; }
    // legacy functions
    //  No new code should use these accessors, they should be removed soon TODO
//    ComboHit(const ComboHit&, StrawHitIndex, double);
    float time() const { return _etime[_eend]; }
    CLHEP::Hep3Vector posCLHEP() const { return GenVector::Hep3Vec(pos()); }
    // persistent payload
    // vector information.  These are stored explicitly even though they are reducible to a
    // smaller payload as the processing time cost of reconstituting them is higher than the memory access time cost
    XYZVectorF _pos; // best estimate of the position of this hit in space
    XYZVectorF _udir; // wire direction of this hit
    XYZVectorF _vdir; // direction perp to hit and Z
    float _ures = -1.0; // resolution along U direction (wire direction)
    float _vres = -1.0; // resolution along V direction
    float _wres = -1.0; // resolution along W direction
    float _wdist = 0.0; // distance from wire center along the wire direction
    float _time = 0.0; // best estimate of time the physical particle created this hit: aggregate and calibrated
    float _timeres = -1.0; // estimated resolution of time measurement
    float _edep = 0.0; // average energy deposition
    float _qual = 0.0; // quality of hit or combination
    StrawHitFlag _flag; // condition of this hit
    StrawId _sid; // straw identifier; for composites, not all fields are complete, use in conjunction with mask
    StrawIdMask _mask; // mask of valid StrawId fields
    StrawEnd _eend; // early tdc end
    // low-level quantities needed for calibration.  These only make sense for single-straw hits
    TrkTypes::TOTTimes  _tot = {0.0, 0.0 };   // TOT times in ns from each end
    TrkTypes::TDCTimes _etime = {0.0, 0.0 }; // threshold crossing times in ns from each end
    // bookkeeping info
    uint16_t _ncombo = 0; // number of associated input objects
    uint16_t _nsh = 0; // number of underlying straw hits
    PIArray _pind = {0,0,0,0,0,0,0,0}; // Indices back to parent objects
    // information specific to hits associated with a helix
    float _hphi = 0.0; // azimuth relative to a helix center
    float _xyWeight = 0.0;       // weight used to perform the x-y circle fit
    float _zphiWeight = 0.0;     // weight used to perfom the z-phi linear fit
    // low-level derived data that should move to StrawResponse
    float _dtime = 0.0; // TOT based drift time estimate
    float _ptime = 0.0; // prop time estimate
  };
  // ComboHitCollection is a non-trivial subclass of vector which includes navigation of nested ComboHits
  class ComboHitCollection : public std::vector<mu2e::ComboHit> {
    public:
      enum Sort {unsorted=0,zsort,sidsort,timesort}; // define sort state of the contents
      using CHCIter = std::vector<ComboHitCollection::const_iterator>;
      using CHCPTR = art::ProductPtr<ComboHitCollection>;
      using SHIV = std::vector<StrawHitIndex>;
      ComboHitCollection(Sort sort=unsorted) : _sort(sort) {}
      // fill a vector of indices to the underlying digis used in a given ComboHit
      // This function is called recursively, so the the vector must be empty on the top-most call
#ifndef __ROOTCLING__
      // find the parent at a given level
      CHCPTR parent(StrawIdMask::Level level) const;
      void fillStrawDigiIndices( size_t chindex, SHIV& shids) const;
      // Fill indices to the specified level.  Return value is the collection to whic
      // the indices apply.  first, given all my hits
      ComboHitCollection const* fillStrawHitIndices( SHIV& shiv, StrawIdMask::Level clevel=StrawIdMask::uniquestraw) const;
      // given a specific hit (index) in myself
      ComboHitCollection const* fillStrawHitIndices( size_t chindex, SHIV& shiv, StrawIdMask::Level clevel=StrawIdMask::uniquestraw) const;
      // given a vector of indices
      ComboHitCollection const* fillStrawHitIndices(SHIV const& inshiv, SHIV& outshiv, StrawIdMask::Level clevel=StrawIdMask::uniquestraw) const;
      // the following are deprecated in favor of the more-efficient and self-checking functions above
      // translate a collection of ComboHits into the lowest-level (straw) combo hits.  This function is recursive
      void fillComboHits( std::vector<uint16_t> const& indices, CHCIter& iters) const;
      // fill a vector of iterators to the ComboHits 1 layer below a given ComboHit.  This is NOT RECURSIVE
      void fillComboHits( size_t chindex, CHCIter& iters) const;
      // set the parent Id given a handle to the parent collection
      void setParent(art::Handle<ComboHitCollection> const& phandle);
      void setParent(art::ValidHandle<ComboHitCollection> const& phandle);
      // or directly from the productPtr
      void setParent(CHCPTR const& parent);
      // or set to be the same as another collection
      void setSameParent(ComboHitCollection const& other);
#endif
      // accessors
      auto const& parent() const { return _parent; }
      StrawIdMask::Level level() const;
      auto sort() const { return _sort; }
      unsigned nStrawHits() const;
    private:
      // reference back to the input ComboHit collection this one references
      CHCPTR _parent; // pointer to the parent object
      Sort _sort; // record how this collection was sorted
  };
  inline std::ostream& operator<<( std::ostream& ost,
                                   ComboHit const& hit){
    hit.print(ost,false);
    return ost;
  }
}
#endif
