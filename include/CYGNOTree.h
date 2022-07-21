//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri May 13 16:07:43 2022 by ROOT version 6.24/06
// from TTree nTuple/tree
// found on file: ../LIME-MC-build/ext_test_lime.root
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
   Int_t           numflugamma1;
   Int_t           numflugamma2;
   Int_t           numflugamma3;
   Int_t           numflugamma_airbox;
   Int_t           numfluneutron1;
   Int_t           numfluneutron2;
   Int_t           numfluneutron3;
   Int_t           numfluneutron_airbox;
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
   Double_t        energyDep_NR;
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
   vector<int>     *parentID_hits;
   vector<int>     *pdgID_hits;
   vector<int>     *trackID_hits;
   vector<double>  *time_hits;
   vector<double>  *kinEne_hits;
   vector<double>  *x_hits;
   vector<double>  *y_hits;
   vector<double>  *z_hits;
   vector<double>  *x_vertex_hits;
   vector<double>  *y_vertex_hits;
   vector<double>  *z_vertex_hits;
   vector<double>  *tracklen_hits;
   vector<double>  *energyDep_hits;
   vector<int>     *trackid_flu;
   vector<int>     *prestepVolNo_flu;
   vector<int>     *volNo_flu;
   vector<int>     *copyNo_flu;
   vector<int>     *pdg_flu;
   vector<double>  *prestepx_flu;
   vector<double>  *prestepy_flu;
   vector<double>  *prestepz_flu;
   vector<double>  *poststepx_flu;
   vector<double>  *poststepy_flu;
   vector<double>  *poststepz_flu;
   vector<double>  *px_flu;
   vector<double>  *py_flu;
   vector<double>  *pz_flu;
   vector<double>  *E_flu;
   vector<double>  *kinE_flu;
   vector<double>  *m_flu;
   vector<int>     *trackid_neu;
   vector<int>     *parentid_neu;
   vector<double>  *poststepx_neu;
   vector<double>  *poststepy_neu;
   vector<double>  *poststepz_neu;
   vector<double>  *px_neu;
   vector<double>  *py_neu;
   vector<double>  *pz_neu;
   vector<double>  *E_neu;
   vector<double>  *kinE_neu;
   vector<int>     *A_ion;
   vector<int>     *Z_ion;
   vector<int>     *pdg_ion;
   vector<int>     *trackid_ion;
   vector<int>     *volNo_ion;
   vector<int>     *copyNo_ion;
   vector<double>  *posx_ion;
   vector<double>  *posy_ion;
   vector<double>  *posz_ion;
   vector<double>  *E_ion;
   vector<double>  *kinE_ion;
   vector<int>     *trackid_ele;
   vector<int>     *parentid_ele;
   vector<double>  *poststepx_ele;
   vector<double>  *poststepy_ele;
   vector<double>  *poststepz_ele;
   vector<double>  *px_ele;
   vector<double>  *py_ele;
   vector<double>  *pz_ele;
   vector<double>  *E_ele;
   vector<double>  *kinE_ele;
   vector<int>     *trackid_pos;
   vector<int>     *parentid_pos;
   vector<double>  *poststepx_pos;
   vector<double>  *poststepy_pos;
   vector<double>  *poststepz_pos;
   vector<double>  *px_pos;
   vector<double>  *py_pos;
   vector<double>  *pz_pos;
   vector<double>  *E_pos;
   vector<double>  *kinE_pos;
   vector<int>     *trackid_pro;
   vector<int>     *parentid_pro;
   vector<double>  *poststepx_pro;
   vector<double>  *poststepy_pro;
   vector<double>  *poststepz_pro;
   vector<double>  *px_pro;
   vector<double>  *py_pro;
   vector<double>  *pz_pro;
   vector<double>  *E_pro;
   vector<double>  *kinE_pro;

   // List of branches
   TBranch        *b_eventnumber;   //!
   TBranch        *b_numvertex;   //!
   TBranch        *b_numparticles;   //!
   TBranch        *b_numhits;   //!
   TBranch        *b_numflu0;   //!
   TBranch        *b_numflugamma1;   //!
   TBranch        *b_numflugamma2;   //!
   TBranch        *b_numflugamma3;   //!
   TBranch        *b_numflugamma_airbox;   //!
   TBranch        *b_numfluneutron1;   //!
   TBranch        *b_numfluneutron2;   //!
   TBranch        *b_numfluneutron3;   //!
   TBranch        *b_numfluneutron_airbox;   //!
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
   TBranch        *b_energyDep_NR;   //!
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
   TBranch        *b_parentID_hits;   //!
   TBranch        *b_pdgID_hits;   //!
   TBranch        *b_trackID_hits;   //!
   TBranch        *b_time_hits;   //!
   TBranch        *b_kinEne_hits;   //!
   TBranch        *b_x_hits;   //!
   TBranch        *b_y_hits;   //!
   TBranch        *b_z_hits;   //!
   TBranch        *b_x_vertex_hits;   //!
   TBranch        *b_y_vertex_hits;   //!
   TBranch        *b_z_vertex_hits;   //!
   TBranch        *b_tracklen_hits;   //!
   TBranch        *b_energyDep_hits;   //!
   TBranch        *b_trackid_flu;   //!
   TBranch        *b_prestepVolNo_flu;   //!
   TBranch        *b_volNo_flu;   //!
   TBranch        *b_copyNo_flu;   //!
   TBranch        *b_pdg_flu;   //!
   TBranch        *b_prestepx_flu;   //!
   TBranch        *b_prestepy_flu;   //!
   TBranch        *b_prestepz_flu;   //!
   TBranch        *b_poststepx_flu;   //!
   TBranch        *b_poststepy_flu;   //!
   TBranch        *b_poststepz_flu;   //!
   TBranch        *b_px_flu;   //!
   TBranch        *b_py_flu;   //!
   TBranch        *b_pz_flu;   //!
   TBranch        *b_E_flu;   //!
   TBranch        *b_kinE_flu;   //!
   TBranch        *b_m_flu;   //!
   TBranch        *b_trackid_neu;   //!
   TBranch        *b_parentid_neu;   //!
   TBranch        *b_poststepx_neu;   //!
   TBranch        *b_poststepy_neu;   //!
   TBranch        *b_poststepz_neu;   //!
   TBranch        *b_px_neu;   //!
   TBranch        *b_py_neu;   //!
   TBranch        *b_pz_neu;   //!
   TBranch        *b_E_neu;   //!
   TBranch        *b_kinE_neu;   //!
   TBranch        *b_A_ion;   //!
   TBranch        *b_Z_ion;   //!
   TBranch        *b_pdg_ion;   //!
   TBranch        *b_trackid_ion;   //!
   TBranch        *b_volNo_ion;   //!
   TBranch        *b_copyNo_ion;   //!
   TBranch        *b_posx_ion;   //!
   TBranch        *b_posy_ion;   //!
   TBranch        *b_posz_ion;   //!
   TBranch        *b_E_ion;   //!
   TBranch        *b_kinE_ion;   //!
   TBranch        *b_trackid_ele;   //!
   TBranch        *b_parentid_ele;   //!
   TBranch        *b_poststepx_ele;   //!
   TBranch        *b_poststepy_ele;   //!
   TBranch        *b_poststepz_ele;   //!
   TBranch        *b_px_ele;   //!
   TBranch        *b_py_ele;   //!
   TBranch        *b_pz_ele;   //!
   TBranch        *b_E_ele;   //!
   TBranch        *b_kinE_ele;   //!
   TBranch        *b_trackid_pos;   //!
   TBranch        *b_parentid_pos;   //!
   TBranch        *b_poststepx_pos;   //!
   TBranch        *b_poststepy_pos;   //!
   TBranch        *b_poststepz_pos;   //!
   TBranch        *b_px_pos;   //!
   TBranch        *b_py_pos;   //!
   TBranch        *b_pz_pos;   //!
   TBranch        *b_E_pos;   //!
   TBranch        *b_kinE_pos;   //!
   TBranch        *b_trackid_pro;   //!
   TBranch        *b_parentid_pro;   //!
   TBranch        *b_poststepx_pro;   //!
   TBranch        *b_poststepy_pro;   //!
   TBranch        *b_poststepz_pro;   //!
   TBranch        *b_px_pro;   //!
   TBranch        *b_py_pro;   //!
   TBranch        *b_pz_pro;   //!
   TBranch        *b_E_pro;   //!
   TBranch        *b_kinE_pro;   //!

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
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../LIME-MC-build/ext_test_lime.root");
//      if (!f || !f->IsOpen()) {
//         f = new TFile("../LIME-MC-build/ext_test_lime.root");
//      }
//      f->GetObject("nTuple",tree);

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
   parentID_hits = 0;
   pdgID_hits = 0;
   trackID_hits = 0;
   time_hits = 0;
   kinEne_hits = 0;
   x_hits = 0;
   y_hits = 0;
   z_hits = 0;
   x_vertex_hits = 0;
   y_vertex_hits = 0;
   z_vertex_hits = 0;
   tracklen_hits = 0;
   energyDep_hits = 0;
   trackid_flu = 0;
   prestepVolNo_flu = 0;
   volNo_flu = 0;
   copyNo_flu = 0;
   pdg_flu = 0;
   prestepx_flu = 0;
   prestepy_flu = 0;
   prestepz_flu = 0;
   poststepx_flu = 0;
   poststepy_flu = 0;
   poststepz_flu = 0;
   px_flu = 0;
   py_flu = 0;
   pz_flu = 0;
   E_flu = 0;
   kinE_flu = 0;
   m_flu = 0;
   trackid_neu = 0;
   parentid_neu = 0;
   poststepx_neu = 0;
   poststepy_neu = 0;
   poststepz_neu = 0;
   px_neu = 0;
   py_neu = 0;
   pz_neu = 0;
   E_neu = 0;
   kinE_neu = 0;
   A_ion = 0;
   Z_ion = 0;
   pdg_ion = 0;
   trackid_ion = 0;
   volNo_ion = 0;
   copyNo_ion = 0;
   posx_ion = 0;
   posy_ion = 0;
   posz_ion = 0;
   E_ion = 0;
   kinE_ion = 0;
   trackid_ele = 0;
   parentid_ele = 0;
   poststepx_ele = 0;
   poststepy_ele = 0;
   poststepz_ele = 0;
   px_ele = 0;
   py_ele = 0;
   pz_ele = 0;
   E_ele = 0;
   kinE_ele = 0;
   trackid_pos = 0;
   parentid_pos = 0;
   poststepx_pos = 0;
   poststepy_pos = 0;
   poststepz_pos = 0;
   px_pos = 0;
   py_pos = 0;
   pz_pos = 0;
   E_pos = 0;
   kinE_pos = 0;
   trackid_pro = 0;
   parentid_pro = 0;
   poststepx_pro = 0;
   poststepy_pro = 0;
   poststepz_pro = 0;
   px_pro = 0;
   py_pro = 0;
   pz_pro = 0;
   E_pro = 0;
   kinE_pro = 0;
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
   fChain->SetBranchAddress("numflugamma1", &numflugamma1, &b_numflugamma1);
   fChain->SetBranchAddress("numflugamma2", &numflugamma2, &b_numflugamma2);
   fChain->SetBranchAddress("numflugamma3", &numflugamma3, &b_numflugamma3);
   fChain->SetBranchAddress("numflugamma_airbox", &numflugamma_airbox, &b_numflugamma_airbox);
   fChain->SetBranchAddress("numfluneutron1", &numfluneutron1, &b_numfluneutron1);
   fChain->SetBranchAddress("numfluneutron2", &numfluneutron2, &b_numfluneutron2);
   fChain->SetBranchAddress("numfluneutron3", &numfluneutron3, &b_numfluneutron3);
   fChain->SetBranchAddress("numfluneutron_airbox", &numfluneutron_airbox, &b_numfluneutron_airbox);
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
   fChain->SetBranchAddress("energyDep_NR", &energyDep_NR, &b_energyDep_NR);
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
   fChain->SetBranchAddress("parentID_hits", &parentID_hits, &b_parentID_hits);
   fChain->SetBranchAddress("pdgID_hits", &pdgID_hits, &b_pdgID_hits);
   fChain->SetBranchAddress("trackID_hits", &trackID_hits, &b_trackID_hits);
   fChain->SetBranchAddress("time_hits", &time_hits, &b_time_hits);
   fChain->SetBranchAddress("kinEne_hits", &kinEne_hits, &b_kinEne_hits);
   fChain->SetBranchAddress("x_hits", &x_hits, &b_x_hits);
   fChain->SetBranchAddress("y_hits", &y_hits, &b_y_hits);
   fChain->SetBranchAddress("z_hits", &z_hits, &b_z_hits);
   fChain->SetBranchAddress("x_vertex_hits", &x_vertex_hits, &b_x_vertex_hits);
   fChain->SetBranchAddress("y_vertex_hits", &y_vertex_hits, &b_y_vertex_hits);
   fChain->SetBranchAddress("z_vertex_hits", &z_vertex_hits, &b_z_vertex_hits);
   fChain->SetBranchAddress("tracklen_hits", &tracklen_hits, &b_tracklen_hits);
   fChain->SetBranchAddress("energyDep_hits", &energyDep_hits, &b_energyDep_hits);
   fChain->SetBranchAddress("trackid_flu", &trackid_flu, &b_trackid_flu);
   fChain->SetBranchAddress("prestepVolNo_flu", &prestepVolNo_flu, &b_prestepVolNo_flu);
   fChain->SetBranchAddress("volNo_flu", &volNo_flu, &b_volNo_flu);
   fChain->SetBranchAddress("copyNo_flu", &copyNo_flu, &b_copyNo_flu);
   fChain->SetBranchAddress("pdg_flu", &pdg_flu, &b_pdg_flu);
   fChain->SetBranchAddress("prestepx_flu", &prestepx_flu, &b_prestepx_flu);
   fChain->SetBranchAddress("prestepy_flu", &prestepy_flu, &b_prestepy_flu);
   fChain->SetBranchAddress("prestepz_flu", &prestepz_flu, &b_prestepz_flu);
   fChain->SetBranchAddress("poststepx_flu", &poststepx_flu, &b_poststepx_flu);
   fChain->SetBranchAddress("poststepy_flu", &poststepy_flu, &b_poststepy_flu);
   fChain->SetBranchAddress("poststepz_flu", &poststepz_flu, &b_poststepz_flu);
   fChain->SetBranchAddress("px_flu", &px_flu, &b_px_flu);
   fChain->SetBranchAddress("py_flu", &py_flu, &b_py_flu);
   fChain->SetBranchAddress("pz_flu", &pz_flu, &b_pz_flu);
   fChain->SetBranchAddress("E_flu", &E_flu, &b_E_flu);
   fChain->SetBranchAddress("kinE_flu", &kinE_flu, &b_kinE_flu);
   fChain->SetBranchAddress("m_flu", &m_flu, &b_m_flu);
   fChain->SetBranchAddress("trackid_neu", &trackid_neu, &b_trackid_neu);
   fChain->SetBranchAddress("parentid_neu", &parentid_neu, &b_parentid_neu);
   fChain->SetBranchAddress("poststepx_neu", &poststepx_neu, &b_poststepx_neu);
   fChain->SetBranchAddress("poststepy_neu", &poststepy_neu, &b_poststepy_neu);
   fChain->SetBranchAddress("poststepz_neu", &poststepz_neu, &b_poststepz_neu);
   fChain->SetBranchAddress("px_neu", &px_neu, &b_px_neu);
   fChain->SetBranchAddress("py_neu", &py_neu, &b_py_neu);
   fChain->SetBranchAddress("pz_neu", &pz_neu, &b_pz_neu);
   fChain->SetBranchAddress("E_neu", &E_neu, &b_E_neu);
   fChain->SetBranchAddress("kinE_neu", &kinE_neu, &b_kinE_neu);
   fChain->SetBranchAddress("A_ion", &A_ion, &b_A_ion);
   fChain->SetBranchAddress("Z_ion", &Z_ion, &b_Z_ion);
   fChain->SetBranchAddress("pdg_ion", &pdg_ion, &b_pdg_ion);
   fChain->SetBranchAddress("trackid_ion", &trackid_ion, &b_trackid_ion);
   fChain->SetBranchAddress("volNo_ion", &volNo_ion, &b_volNo_ion);
   fChain->SetBranchAddress("copyNo_ion", &copyNo_ion, &b_copyNo_ion);
   fChain->SetBranchAddress("posx_ion", &posx_ion, &b_posx_ion);
   fChain->SetBranchAddress("posy_ion", &posy_ion, &b_posy_ion);
   fChain->SetBranchAddress("posz_ion", &posz_ion, &b_posz_ion);
   fChain->SetBranchAddress("E_ion", &E_ion, &b_E_ion);
   fChain->SetBranchAddress("kinE_ion", &kinE_ion, &b_kinE_ion);
   fChain->SetBranchAddress("trackid_ele", &trackid_ele, &b_trackid_ele);
   fChain->SetBranchAddress("parentid_ele", &parentid_ele, &b_parentid_ele);
   fChain->SetBranchAddress("poststepx_ele", &poststepx_ele, &b_poststepx_ele);
   fChain->SetBranchAddress("poststepy_ele", &poststepy_ele, &b_poststepy_ele);
   fChain->SetBranchAddress("poststepz_ele", &poststepz_ele, &b_poststepz_ele);
   fChain->SetBranchAddress("px_ele", &px_ele, &b_px_ele);
   fChain->SetBranchAddress("py_ele", &py_ele, &b_py_ele);
   fChain->SetBranchAddress("pz_ele", &pz_ele, &b_pz_ele);
   fChain->SetBranchAddress("E_ele", &E_ele, &b_E_ele);
   fChain->SetBranchAddress("kinE_ele", &kinE_ele, &b_kinE_ele);
   fChain->SetBranchAddress("trackid_pos", &trackid_pos, &b_trackid_pos);
   fChain->SetBranchAddress("parentid_pos", &parentid_pos, &b_parentid_pos);
   fChain->SetBranchAddress("poststepx_pos", &poststepx_pos, &b_poststepx_pos);
   fChain->SetBranchAddress("poststepy_pos", &poststepy_pos, &b_poststepy_pos);
   fChain->SetBranchAddress("poststepz_pos", &poststepz_pos, &b_poststepz_pos);
   fChain->SetBranchAddress("px_pos", &px_pos, &b_px_pos);
   fChain->SetBranchAddress("py_pos", &py_pos, &b_py_pos);
   fChain->SetBranchAddress("pz_pos", &pz_pos, &b_pz_pos);
   fChain->SetBranchAddress("E_pos", &E_pos, &b_E_pos);
   fChain->SetBranchAddress("kinE_pos", &kinE_pos, &b_kinE_pos);
   fChain->SetBranchAddress("trackid_pro", &trackid_pro, &b_trackid_pro);
   fChain->SetBranchAddress("parentid_pro", &parentid_pro, &b_parentid_pro);
   fChain->SetBranchAddress("poststepx_pro", &poststepx_pro, &b_poststepx_pro);
   fChain->SetBranchAddress("poststepy_pro", &poststepy_pro, &b_poststepy_pro);
   fChain->SetBranchAddress("poststepz_pro", &poststepz_pro, &b_poststepz_pro);
   fChain->SetBranchAddress("px_pro", &px_pro, &b_px_pro);
   fChain->SetBranchAddress("py_pro", &py_pro, &b_py_pro);
   fChain->SetBranchAddress("pz_pro", &pz_pro, &b_pz_pro);
   fChain->SetBranchAddress("E_pro", &E_pro, &b_E_pro);
   fChain->SetBranchAddress("kinE_pro", &kinE_pro, &b_kinE_pro);
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
