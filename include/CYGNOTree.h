//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul 24 18:00:45 2019 by ROOT version 6.12/06
// from TTree nTuple/tree
// found on file: /ua9/data/CYGNO/CYGNO-MC-data/bsub_outputs/50Water10Pb2Cu/Geo50Water10Pb2Cu_CYGNOtest_surface_gamma_fullshield_template_part17.root
//////////////////////////////////////////////////////////

#ifndef CYGNOTree_h
#define CYGNOTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

using namespace std;

class CYGNOTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           eventnumber;
   Int_t           numvertex;
   Int_t           numparticles;
   Int_t           numhits;
   Int_t           numflu0;
   Int_t           numflu;
   Int_t           numneu;
   Int_t           numion;
   Int_t           numele;
   Int_t           numpos;
   Int_t           numpro;
   Int_t           neutronflag;
   Int_t           muonflag;
   Int_t           inelasticflag;
   Double_t        energyDep;
   vector<double>  *xpos_vertex;
   vector<double>  *ypos_vertex;
   vector<double>  *zpos_vertex;
   vector<double>  *time_vertex;
   vector<int>     *numparticle_vertex;
   vector<int>     *pdgid_particle;
   vector<double>  *ivertex_particle;
   vector<double>  *px_particle;
   vector<double>  *py_particle;
   vector<double>  *pz_particle;
   vector<double>  *ekin_particle;
   vector<double>  *etot_particle;
   vector<double>  *impact_param_particle;
   vector<double>  *direc_angle_particle;

   // List of branches
   TBranch        *b_eventnumber;   //!
   TBranch        *b_numvertex;   //!
   TBranch        *b_numparticles;   //!
   TBranch        *b_numhits;   //!
   TBranch        *b_numflu0;   //!
   TBranch        *b_numflu;   //!
   TBranch        *b_numneu;   //!
   TBranch        *b_numion;   //!
   TBranch        *b_numele;   //!
   TBranch        *b_numpos;   //!
   TBranch        *b_numpro;   //!
   TBranch        *b_neutronflag;   //!
   TBranch        *b_muonflag;   //!
   TBranch        *b_inelasticflag;   //!
   TBranch        *b_energyDep;   //!
   TBranch        *b_xpos_vertex;   //!
   TBranch        *b_ypos_vertex;   //!
   TBranch        *b_zpos_vertex;   //!
   TBranch        *b_time_vertex;   //!
   TBranch        *b_numparticle_vertex;   //!
   TBranch        *b_pdgid_particle;   //!
   TBranch        *b_ivertex_particle;   //!
   TBranch        *b_px_particle;   //!
   TBranch        *b_py_particle;   //!
   TBranch        *b_pz_particle;   //!
   TBranch        *b_ekin_particle;   //!
   TBranch        *b_etot_particle;   //!
   TBranch        *b_impact_param_particle;   //!
   TBranch        *b_direc_angle_particle;   //!

   CYGNOTree(TTree *tree=0);
   virtual ~CYGNOTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef CYGNOTree_cxx
CYGNOTree::CYGNOTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
//   if (tree == 0) {
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/ua9/data/CYGNO/CYGNO-MC-data/bsub_outputs/50Water10Pb2Cu/Geo50Water10Pb2Cu_CYGNOtest_surface_gamma_fullshield_template_part17.root");
//      if (!f || !f->IsOpen()) {
//         f = new TFile("/ua9/data/CYGNO/CYGNO-MC-data/bsub_outputs/50Water10Pb2Cu/Geo50Water10Pb2Cu_CYGNOtest_surface_gamma_fullshield_template_part17.root");
//      }
//      f->GetObject("nTuple",tree);
//
//   }
//   Init(tree);
}

CYGNOTree::~CYGNOTree()
{
//   if (!fChain) return;
//   delete fChain->GetCurrentFile();
}

Int_t CYGNOTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t CYGNOTree::LoadTree(Long64_t entry)
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

void CYGNOTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   xpos_vertex = 0;
   ypos_vertex = 0;
   zpos_vertex = 0;
   time_vertex = 0;
   numparticle_vertex = 0;
   pdgid_particle = 0;
   ivertex_particle = 0;
   px_particle = 0;
   py_particle = 0;
   pz_particle = 0;
   ekin_particle = 0;
   etot_particle = 0;
   impact_param_particle = 0;
   direc_angle_particle = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("eventnumber", &eventnumber, &b_eventnumber);
   fChain->SetBranchAddress("numvertex", &numvertex, &b_numvertex);
   fChain->SetBranchAddress("numparticles", &numparticles, &b_numparticles);
   fChain->SetBranchAddress("numhits", &numhits, &b_numhits);
   fChain->SetBranchAddress("numflu0", &numflu0, &b_numflu0);
   fChain->SetBranchAddress("numflu", &numflu, &b_numflu);
   fChain->SetBranchAddress("numneu", &numneu, &b_numneu);
   fChain->SetBranchAddress("numion", &numion, &b_numion);
   fChain->SetBranchAddress("numele", &numele, &b_numele);
   fChain->SetBranchAddress("numpos", &numpos, &b_numpos);
   fChain->SetBranchAddress("numpro", &numpro, &b_numpro);
   fChain->SetBranchAddress("neutronflag", &neutronflag, &b_neutronflag);
   fChain->SetBranchAddress("muonflag", &muonflag, &b_muonflag);
   fChain->SetBranchAddress("inelasticflag", &inelasticflag, &b_inelasticflag);
   fChain->SetBranchAddress("energyDep", &energyDep, &b_energyDep);
   fChain->SetBranchAddress("xpos_vertex", &xpos_vertex, &b_xpos_vertex);
   fChain->SetBranchAddress("ypos_vertex", &ypos_vertex, &b_ypos_vertex);
   fChain->SetBranchAddress("zpos_vertex", &zpos_vertex, &b_zpos_vertex);
   fChain->SetBranchAddress("time_vertex", &time_vertex, &b_time_vertex);
   fChain->SetBranchAddress("numparticle_vertex", &numparticle_vertex, &b_numparticle_vertex);
   fChain->SetBranchAddress("pdgid_particle", &pdgid_particle, &b_pdgid_particle);
   fChain->SetBranchAddress("ivertex_particle", &ivertex_particle, &b_ivertex_particle);
   fChain->SetBranchAddress("px_particle", &px_particle, &b_px_particle);
   fChain->SetBranchAddress("py_particle", &py_particle, &b_py_particle);
   fChain->SetBranchAddress("pz_particle", &pz_particle, &b_pz_particle);
   fChain->SetBranchAddress("ekin_particle", &ekin_particle, &b_ekin_particle);
   fChain->SetBranchAddress("etot_particle", &etot_particle, &b_etot_particle);
   fChain->SetBranchAddress("impact_param_particle", &impact_param_particle, &b_impact_param_particle);
   fChain->SetBranchAddress("direc_angle_particle", &direc_angle_particle, &b_direc_angle_particle);
   Notify();
}

Bool_t CYGNOTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void CYGNOTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t CYGNOTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef CYGNOTree_cxx
