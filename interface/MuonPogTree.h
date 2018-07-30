
#ifndef MuonPOG_Tools_MuonPogTree_H
#define MuonPOG_Tools_MuonPogTree_H

#include "TROOT.h"
#include "TMath.h"
#include <bitset>
#include <vector>
#include <string>

namespace muon_pog {


  class GenInfo {
  public:
    Float_t trueNumberOfInteractions;   // Number of simultaneous interactions generated (before poissonian ev by ev smearing)
    Int_t   actualNumberOfInteractions; // Number of simultaneous interactions generated (after poissonian ev by ev smearing)
    Float_t genWeight;
    GenInfo(){};
    virtual ~GenInfo(){};
    
    ClassDef(GenInfo,1)
  };
  
  class GenParticle {
  public:
    
    GenParticle(){};
    virtual ~GenParticle(){};
    
    Int_t pdgId;  // PDG identifier
    Int_t status; // MC status
    Float_t energy; // energy [GeV]
    Float_t pt; // pt [GeV]
    Float_t eta; // eta
    Float_t phi; // phi
    Float_t vx; // x coordinate of production vertex [cm]
    Float_t vy; // y coordinate of production vertex [cm]
    Float_t vz; // z coordinate of production vertex [cm]
    std::vector<Int_t> mothers; // vector of indices of mothers
    std::vector<bool>  flags;   // vector of flags, in the same order of
                                //  of "DataFormats/HepMCCandidate/interface/GenStatusFlag.h"

  private:
    
    ClassDef(GenParticle,1)
  };

  class METs {
  public:
    Float_t pfMet;   // raw PF MET [GeV]
    Float_t pfChMet; // raw PF charged MET [GeV]
    Float_t caloMet; // raw Calo MET [GeV]

    METs(){};
    virtual ~METs(){};
    
    ClassDef(METs,1)
  };

  enum MuonDetType { DT=0, CSC, RPC };

  class ChambMatch {
  public:
    Int_t id_r;   // station/disk
    Int_t id_phi; // sector
    Int_t id_eta; // ring/wheel

    MuonDetType type;

    Float_t x; 
    Float_t y;

    Float_t phi; 
    Float_t eta;
    Float_t zGlb;

    Float_t dXdZ; 
    Float_t dYdZ;

    Float_t errx; 
    Float_t erry; 

    Float_t errDxDz; 
    Float_t errDyDz; 

    std::vector<std::size_t> indexes;
    std::vector<std::bitset<4> >  matchQuals; // bit order 0 = Trk, 1 = TrkArb, 2 = Sta, 3 = Sta Valid 

    std::vector<std::size_t> trigIndexes;

    ChambMatch(){};
    virtual ~ChambMatch(){};
    
    ClassDef(ChambMatch,5)
  };

  class DtDigiSummary {

  public:

    Int_t id_r;   // station/disk
    Int_t id_phi; // sector
    Int_t id_eta; // ring/wheel

    Int_t n_phi1; 
    Int_t n_theta;
    Int_t n_phi2;

    DtDigiSummary(){};
    virtual ~DtDigiSummary(){};

    ClassDef(DtDigiSummary,1)

  };

  class MuonSegment {

  public:

    Int_t id_r;   // station/disk
    Int_t id_phi; // sector
    Int_t id_eta; // ring/wheel
    
    Float_t x; 
    Float_t y;

    Float_t phi; 
    Float_t eta;

    Float_t dXdZ; 
    Float_t dYdZ;

    Float_t errx; 
    Float_t erry; 

    Float_t errDxDz; 
    Float_t errDyDz; 

    Float_t chi2;  
    Float_t time; 

    Int_t nHitsX; 
    Int_t nHitsY;
    
    MuonSegment(){};
    virtual ~MuonSegment(){};
    
    ClassDef(MuonSegment,1)
  };

  class TriggerPrimitive {

  public:

    Int_t id_r;   // station/disk
    Int_t id_phi; // sector
    Int_t id_eta; // ring/wheel
    
    Float_t phi; 
    Float_t phiB;

    Short_t quality;  
    Short_t bx; 

    Bool_t is2nd;  
    
    TriggerPrimitive(){};
    virtual ~TriggerPrimitive(){};

    inline Int_t bxTrackFinder() const 
    {
      return bx - (is2nd ? 1 : 0);
    };

    inline Float_t phiGlb() const 
    {
      return (phi / 4096.) + TMath::Pi() / 6. * (id_phi - 1);
    };

    ClassDef(TriggerPrimitive,3)
  };

  class HitInfo {
  public:
    Int_t r; // station/disk
    Int_t phi; // sector
    Int_t eta;   // ring/wheel
    
    MuonDetType type;

    Int_t nHits; 
    Int_t nHitsPhi; 
    Int_t nHitsTheta; 

    HitInfo(){};
    virtual ~HitInfo(){};
    
    ClassDef(HitInfo,1)
  };

  enum MuonFitType { DEFAULT=0, INNER, STA, GLB, TUNEP, PICKY, DYT, TPFMS};

  class MuonFit {
  public:
    Float_t pt;  // pt [GeV]   
    Float_t eta; // eta
    Float_t phi; // phi

    Int_t   charge;    // charge

    Float_t ptErr; // fit sigma pT 

    MuonFit(){};
    MuonFit(Float_t in_pt,
	    Float_t in_eta,
	    Float_t in_phi,
	    Int_t   in_charge,
	    Float_t in_ptErr
	    ) : pt(in_pt) ,
                eta(in_eta) ,
                phi(in_phi) ,
                charge(in_charge) ,
                ptErr(in_ptErr) {};
    virtual ~MuonFit(){};
    
    ClassDef(MuonFit,1)
  };

  class Muon {
  public:

    Float_t pt;  // pt [GeV]   
    Float_t eta; // eta
    Float_t phi; // phi

    Int_t   charge;    // charge

    Int_t   isGlobal;
    Int_t   isTracker;
    Int_t   isTrackerArb;
    Int_t   isRPC;
    Int_t   isStandAlone;
    Int_t   isPF;

    Int_t   isSoft;
    Int_t   isLoose;
    Int_t   isTight;
    Int_t   isMedium;
    Int_t   isHighPt;

    Int_t   isBadMuon;
    Int_t   isClone;
    
    //Detector Based Isolation
    Float_t trackerIso;
    Float_t EMCalIso;
    Float_t HCalIso;

    // PF Isolation
    Float_t chargedHadronIso;
    Float_t chargedHadronIsoPU;
    Float_t photonIso;
    Float_t neutralHadronIso;


    Float_t isoPflow04; // PF isolation in dR<0.4 cone dBeta
    Float_t isoPflow03; // PF isolation in dR<0.3 cone dBeta

    Float_t dxy;       // signed transverse distance to primary vertex [cm]
    Float_t dz;        // signed longitudinal distance to primary vertex at min. transv. distance [cm]
    Float_t edxy;      // uncertainty on dxy [cm]
    Float_t edz;       // uncertainty on dz [cm]
    Float_t dxybs;     // signed transverse distance to beamspot [cm]
    Float_t dzbs;      // signed longitudinal distance to beamspot [cm]

    Int_t   nHitsGlobal;
    Int_t   nHitsTracker;
    Int_t   nHitsStandAlone; 

    // Variables for ID 
    //  - General (Tight, HighPt, Soft) 
    Float_t glbNormChi2; 
    Float_t trkNormChi2; 
    Int_t   trkMuonMatchedStations;
    Int_t   rpcMuonMatchedRPCLayers;
    Int_t   trkMuonZPrimeMatchedStations;

    Int_t   glbMuonValidHits; 
    Int_t   trkPixelValidHits; 
    Int_t   trkPixelLayersWithMeas; 
    Int_t   trkTrackerLayersWithMeas; 
    Int_t   trkTrackerLostHits; 

    //  - HighPt 
    Float_t bestMuPtErr; 

    //  - Medium 
    Float_t trkValidHitFrac; 
    Float_t trkStaChi2; 
    Float_t trkKink; 
    Float_t muSegmComp; 

    //  - Soft 
    Int_t   isTrkMuOST; 
    Int_t   isTrkHP; 

    Float_t dxyBest; 
    Float_t dzBest; 
    Float_t dxyInner; 
    Float_t dzInner; 

    // Trk algo
    Int_t algo; 
    Int_t origAlgo; 

    // Muon time 
    Float_t muonTimeDof; 
    Float_t muonTime; 
    Float_t muonTimeErr;

    // RPC Muon time 
    Float_t muonRpcTimeDof; 
    Float_t muonRpcTime; 
    Float_t muonRpcTimeErr;

    std::vector<HitInfo> hits;
    std::vector<ChambMatch> matches;
    std::vector<MuonFit> fits;

    Muon(){};
    virtual ~Muon(){};

    inline Float_t fitPt( const muon_pog::MuonFitType type ) const 
    {
      return fits.at(type).pt;
    };

    inline Float_t fitEta( const muon_pog::MuonFitType type ) const 
    {
      return fits.at(type).eta;
    };

    inline Float_t fitPhi( const muon_pog::MuonFitType type ) const 
    {
      return fits.at(type).phi;
    };

    inline Int_t fitCharge( const muon_pog::MuonFitType type ) const 
    {
      return fits.at(type).charge;
    };

    inline Float_t fitPtErr( const muon_pog::MuonFitType type ) const 
    {
      return fits.at(type).ptErr;
    };

    ClassDef(Muon,5)
  };

  class MuonPair {
  public:

    MuonPair()
      {
	for (int i=0; i<2; ++i)
	  {
	    muIdx[i] = 0;
	    muPt[i]  = -999.;
	  }
      };

    MuonPair(const MuonPair & pair)
      {

	vertexProb = pair.vertexProb;
	vertexChi2 = pair.vertexChi2;
	vertexNDof = pair.vertexNDof;

	for (int i=0; i<2; ++i)
	  {
	    muIdx[i] = pair.muIdx[i];
	    muPt[i]  = pair.muPt[i];
	  }
      };

    virtual ~MuonPair() { };
    
    Float_t vertexProb;
    Float_t vertexChi2;
    Int_t   vertexNDof;
    std::size_t  muIdx[2];
    Float_t      muPt[2];
    
    const muon_pog::Muon & getMu(const int i, 
				 const std::vector<muon_pog::Muon> & muons ) const
      {
	return muons.at(muIdx[i-1]);
      };

    ClassDef(MuonPair,1)

  };
  
  class HLTObject {
  public:

    std::string filterTag; // name of filter passed by the object
    Float_t pt;            // pt of the object passing the filter [GeV]
    Float_t eta;           // eta of the object passing the filter
    Float_t phi;           // phi of the object passing the filter
    
    HLTObject(){};
    virtual ~HLTObject(){};

    ClassDef(HLTObject,1)

  };
    
  class L1Muon {
  public:
        
    Float_t pt;  // pt [GeV]
    Float_t eta; // eta
    Float_t phi; // phi
    Int_t charge; //charge (0 if invalid)
      
    Int_t quality;
    Int_t bx;
      
    Int_t tfIndex;
    
    L1Muon(){};
    virtual ~L1Muon(){};
      
    ClassDef(L1Muon,1)
      
  };

  class BMTFMuon {
  public:
        
    Float_t pt;  // pt [GeV]
    Float_t eta; // eta
    Float_t phi; // phi
    Float_t phiGlb; // phi global
    Int_t charge; //charge (0 if invalid)
      
    Int_t quality;
    Int_t bx;
      
    Int_t etaFine;
    Int_t processor;
    Int_t wheel;

    std::vector<int> trAddress;
    
    BMTFMuon(){};
    virtual ~BMTFMuon(){};
      
    ClassDef(BMTFMuon,1)
      
  };

  class HLT {
  public:
    std::vector<std::string> triggers; // vector of strings with HLT paths
    std::vector<muon_pog::HLTObject>   objects;  // vector of hlt objects assing filters

    HLT(){};
    virtual ~HLT(){};
    bool match( const std::string & path ) {
      if (  std::find (  triggers.begin(), triggers.end(), path ) != triggers.end() )
	return true;
      
      return false;
    }

    bool find( const std::string & path ) {
      for ( std::vector<std::string>::const_iterator it = triggers.begin(); it != triggers.end(); ++it ) {
	if ( it->find ( path ) != std::string::npos ) return true;
      }
      return false;
    }

    ClassDef(HLT,1)

  };

  class EventId {
  public:

    ULong64_t runNumber;              // run number
    ULong64_t luminosityBlockNumber;  // luminosity block number
    ULong64_t eventNumber;            // event number
    Int_t nMuons;                 // number of good muons in the event
    std::vector<Float_t> maxPTs;  // max PT for each good muon in the event

    EventId(){};
    virtual ~EventId(){};

    ClassDef(EventId,2)
  };

  class Event {
  public:

    ULong64_t runNumber;             // run number
    ULong64_t luminosityBlockNumber; // luminosity block number
    ULong64_t eventNumber;           // event number

    Int_t bxId;                  // bunch crossing number
    unsigned long long orbit;    // orbit number
    Float_t instLumi;            // inst lumi from scalers [10E30]

    Int_t nVtx;                      // number of valid reconstructed primary vertices 
    Float_t primaryVertex[3];        // 3d coordinates of PV [cm]
    Float_t cov_primaryVertex[3][3]; // 3x3 covariance matrix of PV estimation [cm*cm]

    std::vector<muon_pog::GenInfo> genInfos;        // venctor of genInfos; size=0 in data
    std::vector<muon_pog::GenParticle> genParticles; // venctor of genParticles size=0 in data
    std::vector<muon_pog::Muon> muons; // vector of muons
    std::vector<muon_pog::MuonPair> pairs; // vector of muon pairs
    std::vector<muon_pog::DtDigiSummary> dtDigis; // vector of DT digi counters
    std::vector<muon_pog::MuonSegment> dtSegments; // vector of DT segments
    std::vector<muon_pog::MuonSegment> cscSegments; // vector of CSC segments
    std::vector<muon_pog::TriggerPrimitive> dtPrimitives; // vector of DT trigger primitives
    muon_pog::METs mets;  // vector of different MET definitions 
    muon_pog::HLT hlt;                 // HLT objects
    std::vector <muon_pog::L1Muon> l1muons; //vector with the L1 muon candidates
    std::vector <muon_pog::BMTFMuon> bmtfMuons; //vector with the BMTF muon candidates
      
    Event(){};
    virtual ~Event(){};

    ClassDef(Event,11)
  };

}
#endif
