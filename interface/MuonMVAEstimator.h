//--------------------------------------------------------------------------------------------------
// $Id $
//
// MuonMVAEstimator
//
// Helper Class for applying MVA electron ID selection
//
// Authors: S.Xie
//--------------------------------------------------------------------------------------------------


/// --> NOTE if you want to use this class as standalone without the CMSSW part 
///  you need to uncomment the below line and compile normally with scramv1 b 
///  Then you need just to load it in your root macro the lib with the correct path, eg:
///  gSystem->Load("/data/benedet/CMSSW_5_2_2/lib/slc5_amd64_gcc462/pluginEGammaEGammaAnalysisTools.so");

//#define STANDALONE   // <---- this line

#ifndef MuonMVAEstimator_H
#define MuonMVAEstimator_H

#ifndef STANDALONE
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "Muon/MuonAnalysisTools/interface/MuonEffectiveArea.h"
#endif
#include <vector>
#include <TROOT.h>
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

class MuonMVAEstimator{
  public:
    MuonMVAEstimator();
    ~MuonMVAEstimator(); 
  
    enum MVAType {
      kIDIsoRingsCombined = 0,  
      kIsoRings,
      kIsoDeltaR
    };
  
    void     initialize( std::string methodName,
                         std::string weightsfile,
                         MuonMVAEstimator::MVAType type);
    void     initialize( std::string methodName,
                         MuonMVAEstimator::MVAType type,
                         Bool_t useBinnedVersion,
                         std::vector<std::string> weightsfiles );
    
    Bool_t   isInitialized() const { return fisInitialized; }
    UInt_t   GetMVABin( double eta, double pt, 
                        Bool_t isGlobal, Bool_t isTrackerMuon) const;
    
    void SetPrintMVADebug(bool b) { fPrintMVADebug = b; }
    
    void bindVariables();
    
#ifndef STANDALONE
    Double_t mvaValue(const reco::Muon& mu, 
                      const reco::Vertex& vertex, 
                      const reco::PFCandidateCollection &PFCandidates,
                      double Rho,
                      MuonEffectiveArea::MuonEffectiveAreaTarget EATarget,
                      const reco::GsfElectronCollection &IdentifiedElectrons,
                      const reco::MuonCollection &IdentifiedMuons);
    
    // MVA value for the isoDeltaR MVA
    Double_t mvaValue(const reco::Muon& mu,
		      const reco::PFCandidateCollection &PFCandidates,
		      double Rho, 
		      MuonEffectiveArea::MuonEffectiveAreaTarget EATarget);
#endif
    
    
 private:
    std::vector<TMVA::Reader*> fTMVAReader;
    std::string                fMethodname;
    Bool_t                     fisInitialized;
    Bool_t                     fPrintMVADebug;
    MVAType                    fMVAType;
    Bool_t                     fUseBinnedVersion;
    UInt_t                     fNMVABins;
    
    // spectator categorization variables
    Float_t                    fMVAVar_MuEta;
    Float_t                    fMVAVar_MuPt;
    Float_t                    fMVAVar_MuTypeBits;

    //ID variables
    Float_t                    fMVAVar_MuTkNchi2;
    Float_t                    fMVAVar_MuGlobalNchi2;
    Float_t                    fMVAVar_MuNValidHits;
    Float_t                    fMVAVar_MuNTrackerHits;
    Float_t                    fMVAVar_MuNPixelHits;
    Float_t                    fMVAVar_MuNMatches;
    Float_t                    fMVAVar_MuD0;
    Float_t                    fMVAVar_MuIP3d;
    Float_t                    fMVAVar_MuIP3dSig;
    Float_t                    fMVAVar_MuTrkKink;
    Float_t                    fMVAVar_MuSegmentCompatibility;
    Float_t                    fMVAVar_MuCaloCompatibility;
    Float_t                    fMVAVar_MuHadEnergy;
    Float_t                    fMVAVar_MuEmEnergy;
    Float_t                    fMVAVar_MuHadS9Energy;
    Float_t                    fMVAVar_MuEmS9Energy;

    //isolation
    Float_t                   fMVAVar_ChargedIso_DR0p0To0p1;
    Float_t                   fMVAVar_ChargedIso_DR0p1To0p2;
    Float_t                   fMVAVar_ChargedIso_DR0p2To0p3;
    Float_t                   fMVAVar_ChargedIso_DR0p3To0p4;
    Float_t                   fMVAVar_ChargedIso_DR0p4To0p5;
    Float_t                   fMVAVar_GammaIso_DR0p0To0p1;
    Float_t                   fMVAVar_GammaIso_DR0p1To0p2;
    Float_t                   fMVAVar_GammaIso_DR0p2To0p3;
    Float_t                   fMVAVar_GammaIso_DR0p3To0p4;
    Float_t                   fMVAVar_GammaIso_DR0p4To0p5;
    Float_t                   fMVAVar_NeutralHadronIso_DR0p0To0p1;
    Float_t                   fMVAVar_NeutralHadronIso_DR0p1To0p2;
    Float_t                   fMVAVar_NeutralHadronIso_DR0p2To0p3;
    Float_t                   fMVAVar_NeutralHadronIso_DR0p3To0p4;
    Float_t                   fMVAVar_NeutralHadronIso_DR0p4To0p5;
    
    
    // isolation variables II
    Float_t                   fMVAVar_MuRelIsoPFCharged;
    Float_t                   fMVAVar_MuRelIsoPFNeutral;
    Float_t                   fMVAVar_MuRelIsoPFPhotons;
    Float_t                   fMVAVar_MuDeltaRMean;
    Float_t                   fMVAVar_MuDeltaRSum;
    Float_t                   fMVAVar_MuDensity;

};

#endif
