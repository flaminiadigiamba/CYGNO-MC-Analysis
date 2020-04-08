#ifndef CYGNOAnalysis_h
#define CYGNOAnalysis_h

#include <CYGNOTree.h>
#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TString.h>
#include <TCanvas.h>
#include <TRandom.h>

using namespace std;

class CYGNOTree;

class CYGNOAnalysis : public CYGNOTree
{

protected :
    list<string> _file_to_be_open;
    TFile *_f_output;
    TTree *_tree;

    Double_t _CYGNO_gas_mass;
    Bool_t _externalflux;
    Double_t _mass;
    Double_t _activity;
    Double_t _half_life;
    Double_t _externalflux_value;
    Double_t _tot_shield_thickness;
    Double_t _shield0_thickness;
    Double_t _shield1_thickness;
    Double_t _shield2_thickness;
    Double_t _shield3_thickness;
    Long64_t _total_events=0;
    Long64_t _total_flux_events=0; 
    Long64_t _total_flux_events_flu0=0; 
    Long64_t _total_flux_events_flu0_test=0; 
    Long64_t _total_flux_events_gammaflu1=0; 
    Long64_t _total_flux_events_gammaflu2=0; 
    Long64_t _total_flux_events_gammaflu3=0; 
    Long64_t _total_flux_events_gammaflu_airbox=0; 
    Long64_t _total_flux_events_neutronflu1=0; 
    Long64_t _total_flux_events_neutronflu2=0; 
    Long64_t _total_flux_events_neutronflu3=0; 
    Long64_t _total_flux_events_neutronflu_airbox=0; 

    Double_t _bkg_cpd_kg;
    Double_t _bkg_cpd_kg_err;
    Double_t _bkg_cpd_kg_kev;
    Double_t _bkg_cpd_kg_kev_err;
    
    Bool_t _smearing;
    
    Double_t _normfull;
    Double_t _norm;
   

    TRandom *factor;
    TTree *cygno_tree;

    //histograms
    TH1D *h_NTot;
    TH1D *h_NTotFlux0;
    TH1D *h_NGammaFlux1; 
    TH1D *h_NGammaFlux2;
    TH1D *h_NGammaFlux3; 
    TH1D *h_NGammaAirBox;
    TH1D *h_NNeutronFlux1; 
    TH1D *h_NNeutronFlux2;
    TH1D *h_NNeutronFlux3; 
    TH1D *h_NNeutronAirBox;

   
    TH1D *h_edepDet;
    TH1D *h_edepDet_norm;
    TH1D *h_edepDet_full;
    TH1D *h_edepDet_full_norm;
    
    TH1D *h_edepDet_NR;
    TH1D *h_edepDet_NR_norm;
    TH1D *h_edepDet_NR_full;
    TH1D *h_edepDet_NR_full_norm;
    
    TH1D *h_EgammaShield0;
    TH1D *h_EgammaShield0_norm; 
    TH1D *h_EgammaShield0_full;    
    TH1D *h_EgammaShield0_full_norm;

    TH1D *h_EgammaShield1;
    TH1D *h_EgammaShield1_norm; 
    TH1D *h_EgammaShield1_full;    
    TH1D *h_EgammaShield1_full_norm;
    
    TH1D *h_EgammaShield2;
    TH1D *h_EgammaShield2_norm; 
    TH1D *h_EgammaShield2_full;    
    TH1D *h_EgammaShield2_full_norm;

    TH1D *h_EgammaShield3;
    TH1D *h_EgammaShield3_norm; 
    TH1D *h_EgammaShield3_full;    
    TH1D *h_EgammaShield3_full_norm;

    TH1D *h_EgammaAirBox;
    TH1D *h_EgammaAirBox_norm;
    TH1D *h_EgammaAirBox_full;
    TH1D *h_EgammaAirBox_full_norm;

    TH1D *h_EallAirBox;
    TH1D *h_EallAirBox_norm;
    TH1D *h_EallAirBox_full;
    TH1D *h_EallAirBox_full_norm;
    
    TH1D *h_EneutronShield0;
    TH1D *h_EneutronShield0_norm; 
    TH1D *h_EneutronShield0_full;    
    TH1D *h_EneutronShield0_full_norm;

    TH1D *h_EneutronShield1;
    TH1D *h_EneutronShield1_norm; 
    TH1D *h_EneutronShield1_full;    
    TH1D *h_EneutronShield1_full_norm;
    
    TH1D *h_EneutronShield2;
    TH1D *h_EneutronShield2_norm; 
    TH1D *h_EneutronShield2_full;    
    TH1D *h_EneutronShield2_full_norm;

    TH1D *h_EneutronShield3;
    TH1D *h_EneutronShield3_norm; 
    TH1D *h_EneutronShield3_full;    
    TH1D *h_EneutronShield3_full_norm;

    TH1D *h_EneutronAirBox;
    TH1D *h_EneutronAirBox_norm;
    TH1D *h_EneutronAirBox_full;
    TH1D *h_EneutronAirBox_full_norm;

    
    TH1D *h_AbsPxShield0;
    TH1D *h_AbsPyShield0; 
    TH1D *h_AbsPzShield0;    
    
    TH1D *h_AbsPxShield1;
    TH1D *h_AbsPyShield1; 
    TH1D *h_AbsPzShield1;    
    
    TH1D *h_AbsPxShield2;
    TH1D *h_AbsPyShield2; 
    TH1D *h_AbsPzShield2;    
    
    TH1D *h_AbsPxShield3;
    TH1D *h_AbsPyShield3; 
    TH1D *h_AbsPzShield3;    
    
    TH1D *h_AbsPxAirBox;
    TH1D *h_AbsPyAirBox; 
    TH1D *h_AbsPzAirBox;    

    TH1D *h_GammaThetaShield0;
    TH1D *h_GammaPhiShield0; 
    TH1D *h_GammaThetaShield1;
    TH1D *h_GammaPhiShield1; 
    TH1D *h_GammaThetaShield2;
    TH1D *h_GammaPhiShield2; 
    TH1D *h_GammaThetaShield3;
    TH1D *h_GammaPhiShield3; 
    TH1D *h_GammaThetaAirBox;
    TH1D *h_GammaPhiAirBox; 
    
    TH1D *h_NeutronThetaShield0;
    TH1D *h_NeutronPhiShield0; 
    TH1D *h_NeutronThetaShield1;
    TH1D *h_NeutronPhiShield1; 
    TH1D *h_NeutronThetaShield2;
    TH1D *h_NeutronPhiShield2; 
    TH1D *h_NeutronThetaShield3;
    TH1D *h_NeutronPhiShield3; 
    TH1D *h_NeutronThetaAirBox;
    TH1D *h_NeutronPhiAirBox; 

    TH1D *h_AirBox;
    TH1D *h_AirBox_norm;
    TH1D *h_AirBox_full;
    TH1D *h_AirBox_full_norm;

    TH1D *h_E_ele;
    TH1D *h_E_ele_norm;
    TH1D *h_E_ele_full;
    TH1D *h_E_ele_full_norm;

    TH1D *h_E_pos;
    TH1D *h_E_pos_norm;
    TH1D *h_E_pos_full;
    TH1D *h_E_pos_full_norm;

    TH1D *h_E_pro;
    TH1D *h_E_pro_norm;
    TH1D *h_E_pro_full;
    TH1D *h_E_pro_full_norm;
    
    TH1D *h_E_ion;
    TH1D *h_E_ion_norm;
    TH1D *h_E_ion_full;
    TH1D *h_E_ion_full_norm;

    TH3D *h3_xyz_ele;
    TH3D *h3_xyz_ele_fiducial;
    TH3D *h3_xyz_pos;
    TH3D *h3_xyz_pro;
    TH3D *h3_xyz_ion;

public :

   //CYGNOAnalysis(TTree *tree=0);
   CYGNOAnalysis();

   virtual ~CYGNOAnalysis();
   virtual void Config(string conf);
   virtual void SetHistograms();
   virtual void SetTree();
   //virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   //virtual void     Init(TTree *tree);
   virtual void     Loop();
   //virtual Bool_t   Notify();
   //virtual void     Show(Long64_t entry = -1);
   virtual void Smearing();
   virtual void  Normalize();
   virtual void ComputeBKG();

private:

   
//CYGNO histograms

};

#endif

#ifdef CYGNOAnalysis_cxx
CYGNOAnalysis::CYGNOAnalysis()
{
//standard constructor
}
CYGNOAnalysis::~CYGNOAnalysis()
{
//   if (!fChain) return;
//   delete fChain->GetCurrentFile();
}

Int_t CYGNOAnalysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t CYGNOAnalysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

//void CYGNOAnalysis::Init(TTree *tree)
//{
//   // The Init() function is called when the selector needs to initialize
//   // a new tree or chain. Typically here the branch addresses and branch
//   // pointers of the tree will be set.
//   // It is normally not necessary to make changes to the generated
//   // code, but the routine can be extended by the user if needed.
//   // Init() will be called many times when running on PROOF
//   // (once per file to be processed).
//
//   // Set object pointer
//   //events = 0;
//   // Set branch addresses and branch pointers
//   if (!tree) return;
//   fChain = tree;
//   fCurrent = -1;
//   fChain->SetMakeClass(1);
//
//   //fChain->SetBranchAddress("events", &events, &b_events);
//   Notify();
//}
//
//Bool_t CYGNOAnalysis::Notify()
//{
//   // The Notify() function is called when a new file is opened. This
//   // can be either for a new TTree in a TChain or when when a new TTree
//   // is started when using PROOF. It is normally not necessary to make changes
//   // to the generated code, but the routine can be extended by the
//   // user if needed. The return value is currently not used.
//
//   return kTRUE;
//}
//
//void CYGNOAnalysis::Show(Long64_t entry)
//{
//// Print contents of entry.
//// If entry is not specified, print current entry
//   if (!fChain) return;
//   fChain->Show(entry);
//}
//Int_t CYGNOAnalysis::Cut(Long64_t entry)
//{
//// This function may be called from Loop.
//// returns  1 if entry is accepted.
//// returns -1 otherwise.
//   return 1;
//}

#endif // #ifdef CYGNOAnalysis_cxx

