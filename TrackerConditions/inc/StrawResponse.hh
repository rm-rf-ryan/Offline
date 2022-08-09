#ifndef TrackerConditions_StrawResponse_hh
#define TrackerConditions_StrawResponse_hh
//
// StrawResponse collects the net response features of straws
// used in reconstruction
//

#include <iostream>
#include <vector>
#include <array>
#include "Offline/TrackerGeom/inc/Straw.hh"
#include "Offline/DataProducts/inc/TrkTypes.hh"
#include "Offline/DataProducts/inc/StrawId.hh"
#include "Offline/TrackerConditions/inc/StrawDrift.hh"
#include "Offline/TrackerConditions/inc/StrawElectronics.hh"
#include "Offline/TrackerConditions/inc/StrawPhysics.hh"
#include "Offline/GeneralUtilities/inc/SplineInterpolation.hh"
#include "Offline/Mu2eInterfaces/inc/ProditionsEntity.hh"


namespace mu2e {
  class Straw;
  class StrawDrift;
  class StrawId;

  class StrawResponse : virtual public ProditionsEntity {
    public:
      typedef std::shared_ptr<StrawResponse> ptr_t;
      typedef std::shared_ptr<const StrawResponse> cptr_t;
      constexpr static const char* cxname = {"StrawResponse"};

      struct DriftInfo {
        double distance;
        double speed;
        double variance;
      };

      explicit StrawResponse( StrawDrift::cptr_t strawDrift,
          StrawElectronics::cptr_t strawElectronics,
          StrawPhysics::cptr_t strawPhysics,
          int eBins, double eBinWidth,
          std::vector<double> edep, std::vector<double> halfvpscale,
          double central, std::vector<double> centres,
          std::vector<double> resslope, bool truncateLongitudinal,
          bool rmsLongErrors, int totTBins, double totTBinWidth,
          int totEBins, double totEBinWidth, std::vector<double> totdtime,
          std::vector<double> totderror,
          std::vector<double> derr,
          bool usepderr, std::vector<double> parDriftDocas,
          std::vector<double> parDriftOffsets, std::vector<double> parDriftRes,
          double wbuf, double slfac, double errfac, bool usenonlindrift,
          double lindriftvel, double mint0doca,
          std::array<double, StrawId::_nustraws> pmpEnergyScale,
          double electronicsTimeDelay, double gasGain,
          std::array<double,StrawElectronics::npaths> analognoise,
          std::array<double,StrawElectronics::npaths> dVdI,
          double vsat, double ADCped, double pmpEnergyScaleAvg,
          std::array<double, StrawId::_nustraws> strawHalfvp,
          bool useDriftSplines, bool driftIgnorePhi,
          SplineInterpolation driftresspline,
          double driftSplineDeltaPhi,
          std::vector<double> d2t_x, std::vector<std::vector<double> > d2t_2d,
          std::vector<std::vector<double> > d2t_2dv,
          std::vector<double> t2d_x, std::vector<std::vector<double> > t2d_2d) :
        ProditionsEntity(cxname),
        _strawDrift(strawDrift),
        _strawElectronics(strawElectronics),
        _strawPhysics(strawPhysics),
        _eBins(eBins), _eBinWidth(eBinWidth),
        _edep(edep), _halfvpscale(halfvpscale), _central(central), _centres(centres),
        _resslope(resslope), _truncateLongitudinal(truncateLongitudinal),
        _rmsLongErrors(rmsLongErrors), _totTBins(totTBins), _totTBinWidth(totTBinWidth),
        _totEBins(totEBins), _totEBinWidth(totEBinWidth),
        _totdtime(totdtime),
        _totderror(totderror),
        _derr(derr), _usepderr(usepderr), _parDriftDocas(parDriftDocas),
        _parDriftOffsets(parDriftOffsets), _parDriftRes(parDriftRes),
        _wbuf(wbuf), _slfac(slfac), _errfac(errfac),
        _usenonlindrift(usenonlindrift), _lindriftvel(lindriftvel),
        _mint0doca(mint0doca),
        _pmpEnergyScale(pmpEnergyScale),
        _electronicsTimeDelay(electronicsTimeDelay),
        _gasGain(gasGain), _analognoise(analognoise),
        _dVdI(dVdI), _vsat(vsat), _ADCped(ADCped),
        _pmpEnergyScaleAvg(pmpEnergyScaleAvg),
        _strawHalfvp(strawHalfvp),
        _useDriftSplines(useDriftSplines),
        _driftIgnorePhi(driftIgnorePhi),
        _driftResSpline(driftresspline),
        _driftSplineDeltaPhi(driftSplineDeltaPhi),
        _d2t_x(d2t_x), _d2t_2d(d2t_2d), _d2t_2dv(d2t_2dv),
        _t2d_x(t2d_x), _t2d_2d(t2d_2d){}

      virtual ~StrawResponse() {}

      DriftInfo driftInfoAtDistance(StrawId strawId, double ddist, double dtime, double phi,
          bool noSpline=false) const;
      double driftDistanceToTime(StrawId strawId, double ddist, double phi,
          bool noSpline=false) const;
      double driftInstantSpeed(StrawId strawId, double ddist, double phi,
          bool noSpline=false) const;
      double driftTimeError(StrawId strawId, double ddist, double phi,
          bool noSpline=false) const;

      bool wireDistance(Straw const& straw, double edep, double dt,
          double& wdist, double& wderr, double& halfpv) const;
      bool useParameterizedDriftError() const { return _usepderr; }
      bool useNonLinearDrift() const { return _usenonlindrift; }
      double Mint0doca() const { return _mint0doca;}
      double strawGain() const { return _strawPhysics->strawGain();}

      double halfPropV(StrawId strawId, double kedep) const;

      // this is used to update values from the database
      void setOffsets( std::array<double, StrawId::_nupanels> timeOffsetPanel,
          std::array<double, StrawId::_nustraws> timeOffsetStrawHV,
          std::array<double, StrawId::_nustraws> timeOffsetStrawCal ) {
        _timeOffsetPanel = timeOffsetPanel;
        _timeOffsetStrawHV = timeOffsetStrawHV;
        _timeOffsetStrawCal = timeOffsetStrawCal;
      }

      double driftTimeToDistance(StrawId strawId, double dtime, double phi, bool noSpline=false) const;
      double driftConstantSpeed() const {return _lindriftvel;} // constant value used for annealing errors, should be close to average velocity
      double driftDistanceError(StrawId strawId, double ddist, double phi, bool noSpline=false) const;
      double driftDistanceOffset(StrawId strawId, double ddist, double phi, double DOCA) const;
      double driftTimeOffset(StrawId strawId, double ddist, double phi, double DOCA) const;

      double peakMinusPedestalEnergyScale() const { return _pmpEnergyScaleAvg; }
      double peakMinusPedestalEnergyScale(StrawId sid) const { return _pmpEnergyScale[sid.uniqueStraw()]; }
      double analogNoise(StrawElectronics::Path ipath) const { return _analognoise[ipath]; }  // incoherent noise
      double fallTime(StrawElectronics::Path ipath) const { return 22.;} //FIXME
      double currentToVoltage(StrawElectronics::Path ipath) const { return _dVdI[ipath]; }
      double saturatedResponse(double vlin) const;
      double ADCPedestal() const { return _ADCped; };

      // converts times from TDC times to time relative to Event Window
      // removes channel to channel delays and overall electronics time delay
      void calibrateTimes(TrkTypes::TDCValues const& tdc, TrkTypes::TDCTimes &times, const StrawId &id) const;
      // approximate drift distatnce from ToT value
      double TOTdriftTime(Straw const& straw, double tot, double edep) const;
      double TOTdriftTimeError(Straw const& straw, double tot, double edep) const;
      double pathLength(Straw const& straw, double tot) const;
      //      double pathLength(StrawHit const& strawhit, double theta) const;

      void print(std::ostream& os) const;
      void printVector(std::ostream& os, std::string const& name,
          std::vector<double> const& a) const;

      template<typename T, size_t SIZE>
        void printArray(std::ostream& os, std::string const& name,
            std::array<T,SIZE> const& a) const;

      // StrawElectronics functions we are allowed to use
      inline size_t nADCPreSamples() const { return _strawElectronics->nADCPreSamples(); }
      inline double adcLSB() const { return _strawElectronics->adcLSB(); }
      inline double totLSB() const { return _strawElectronics->totLSB(); }
      inline double adcPeriod() const { return _strawElectronics->adcPeriod(); }
      inline uint16_t maxADC() const { return _strawElectronics->maxADC(); }
      // StrawPhysics functions we are allowed to use
      inline double ionizationEnergy(double q) const { return _strawPhysics->ionizationEnergy(q); }

      double wpRes(double kedep, double wdist) const;
    private:

      // helper functions
      static double PieceLine(std::vector<double> const& xvals,
          std::vector<double> const& yvals, double xval);

      StrawDrift::cptr_t _strawDrift;
      StrawElectronics::cptr_t _strawElectronics;
      StrawPhysics::cptr_t _strawPhysics;

      // parametric data for calibration functions
      // TD reconstruction uses 1/2 the propagation velocity and depends on the
      // Dependence on position and straw length still needed FIXME!
      // (reconstructed) energy deposit
      bool _evenBins;
      int _eBins;
      double _eBinWidth;
      std::vector<double> _edep; // energy deposit boundaries
      std::vector<double> _halfvpscale; // scaling of effective 1/2 propagation velocity by edep
      double _central; // max wire distance for central wire region
      std::vector<double> _centres; // wire center resolution by edep
      std::vector<double> _resslope; // resolution slope vs position by edep
      bool _truncateLongitudinal; // true for standard fit, false for straight line calibrated fit
      bool _rmsLongErrors; // true for standard fit, false for straight line calibrated fit
      size_t _totTBins;
      double _totTBinWidth;
      size_t _totEBins;
      double _totEBinWidth;
      std::vector<double> _totdtime;
      std::vector<double> _totderror;
      std::vector<double> _derr; // parameters describing the drift error function
      bool _usepderr; // flag to use calculated version of drift error calculation
      std::vector<double> _parDriftDocas;
      std::vector<double> _parDriftOffsets;
      std::vector<double> _parDriftRes;
      double _wbuf; // buffer at the edge of the straws, in terms of sigma
      double _slfac; // factor of straw length to set 'missing cluster' hits
      double _errfac; // error inflation for 'missing cluster' hits

      bool _usenonlindrift;
      double _lindriftvel;
      double _mint0doca;  // minimum doca for t0 calculation.  Note this is a SIGNED QUANTITITY

      std::array<double, StrawId::_nustraws> _pmpEnergyScale;
      std::array<double, StrawId::_nupanels> _timeOffsetPanel;
      std::array<double, StrawId::_nustraws> _timeOffsetStrawHV;
      std::array<double, StrawId::_nustraws> _timeOffsetStrawCal;
      double _electronicsTimeDelay;
      double _gasGain;
      std::array<double,StrawElectronics::npaths> _analognoise; //noise (mVolt) from the straw itself
      std::array<double,StrawElectronics::npaths> _dVdI; // scale factor between charge and voltage (milliVolts/picoCoulombs)
      double _vsat;
      double _ADCped;
      double _pmpEnergyScaleAvg;
      std::array<double, StrawId::_nustraws> _strawHalfvp;
      bool _useDriftSplines;
      bool _driftIgnorePhi;
      SplineInterpolation _driftResSpline;
      double _driftSplineDeltaPhi;
      std::vector<double> _d2t_x;
      std::vector<std::vector<double> > _d2t_2d;
      std::vector<std::vector<double> > _d2t_2dv;
      std::vector<double> _t2d_x;
      std::vector<std::vector<double> > _t2d_2d;
  };
}
#endif

