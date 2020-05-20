#define CYGNOAnalysis_cxx
#include "CYGNOTree.h"
#include "CYGNOAnalysis.h"
#include "srtutils.cc"
#include <TFile.h>
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <string>
#include <list>
#include <sstream>

using namespace std;

void CYGNOAnalysis::Config(string config_file){
    

    TString config(config_file);
    
    _CYGNO_gas_mass = Double_t (GetValue("CYGNO_gas_mass",config));
    _externalflux = Bool_t (GetValue("externalflux",config));
    _smearing = Bool_t (GetValue("smearing",config));
    if (!_externalflux){
        _mass = Double_t (GetValue("mass",config));
        _activity = Double_t (GetValue("activity",config));
    	_half_life = Double_t(GetValue("half_life",config));
    	if(!_half_life){_half_life = -999;}
    }    
    else{
        _externalflux_value = Double_t (GetValue("externalflux_value",config));
        _shield0_thickness = Double_t (GetValue("shield0_thickness",config));
        _shield1_thickness = Double_t (GetValue("shield1_thickness",config));
        _shield2_thickness = Double_t (GetValue("shield2_thickness",config));
        _shield3_thickness = Double_t (GetValue("shield3_thickness",config));
        _tot_shield_thickness = _shield0_thickness + _shield1_thickness + _shield2_thickness + _shield3_thickness;
        cout << "thick0 = " << _shield0_thickness <<  endl;
        cout << "thick1 = " << _shield1_thickness <<  endl;
        cout << "thick2 = " << _shield2_thickness <<  endl;
        cout << "thick3 = " << _shield3_thickness <<  endl;
    } 

    TString flist(GetFileName("filelist",config));
    TString froot(GetFileName("root_out",config));
    
    ifstream list_of_files(flist);
    string temp;
    
    while(list_of_files>>temp){
        cout<<"File "<<temp<<endl;
        _file_to_be_open.push_back(temp);
        
    }
    _f_output = new TFile(froot, "RECREATE","root_file");
}


void CYGNOAnalysis::SetHistograms(){

    h_NTot = new TH1D("h_NTot","",1,0,1);
    h_NTotFlux0 = new TH1D("h_NTotFlux0","",1,0,1);
    h_NGammaFlux1 = new TH1D("h_NGammaFlux1","",1,0,1);
    h_NGammaFlux2 = new TH1D("h_NGammaFlux2","",1,0,1);
    h_NGammaFlux3 = new TH1D("h_NGammaFlux3","",1,0,1);
    h_NGammaAirBox = new TH1D("h_NGammaAirBox","",1,0,1);
    h_NNeutronFlux1 = new TH1D("h_NNeutronFlux1","",1,0,1);
    h_NNeutronFlux2 = new TH1D("h_NNeutronFlux2","",1,0,1);
    h_NNeutronFlux3 = new TH1D("h_NNeutronFlux3","",1,0,1);
    h_NNeutronAirBox = new TH1D("h_NNeutronAirBox","",1,0,1);
    
    h_edepDet = new TH1D("h_edepDet","edepDet",600,0,120);
    h_edepDet_norm = new TH1D("h_edepDet_norm","edepDet-norm",600,0,120);
    h_edepDet_full = new TH1D("h_edepDet_full","edepDet-full",600,0,3000);
    h_edepDet_full_norm = new TH1D("h_edepDet_full_norm","edepDet-full-norm",600,0,3000);

    h_edepDet_NR = new TH1D("h_edepDet_NR","edepDet_NR",600,0,120);
    h_edepDet_NR_norm = new TH1D("h_edepDet_NR_norm","edepDet_NR-norm",600,0,120);
    h_edepDet_NR_full = new TH1D("h_edepDet_NR_full","edepDet_NR-full",600,0,3000);
    h_edepDet_NR_full_norm = new TH1D("h_edepDet_NR_full_norm","edepDet_NR-full-norm",600,0,3000);
    
    h_EgammaShield0 = new TH1D("h_EgammaShield0","",600,0,120);
    h_EgammaShield0_norm = new TH1D("h_EgammaShield0_norm","",600,0,120);
    h_EgammaShield0_full = new TH1D("h_EgammaShield0_full","",600,0,3000);
    h_EgammaShield0_full_norm = new TH1D("h_EgammaShield0_full_norm","",600,0,3000);

    h_EgammaShield1 = new TH1D("h_EgammaShield1","",600,0,120);
    h_EgammaShield1_norm = new TH1D("h_EgammaShield1_norm","",600,0,120);
    h_EgammaShield1_full = new TH1D("h_EgammaShield1_full","",600,0,3000);
    h_EgammaShield1_full_norm = new TH1D("h_EgammaShield1_full_norm","",600,0,3000);

    h_EgammaShield2 = new TH1D("h_EgammaShield2","",600,0,120);
    h_EgammaShield2_norm = new TH1D("h_EgammaShield2_norm","",600,0,120);
    h_EgammaShield2_full = new TH1D("h_EgammaShield2_full","",600,0,3000);
    h_EgammaShield2_full_norm = new TH1D("h_EgammaShield2_full_norm","",600,0,3000);

    h_EgammaShield3 = new TH1D("h_EgammaShield3","",600,0,120);
    h_EgammaShield3_norm = new TH1D("h_EgammaShield3_norm","",600,0,120);
    h_EgammaShield3_full = new TH1D("h_EgammaShield3_full","",600,0,3000);
    h_EgammaShield3_full_norm = new TH1D("h_EgammaShield3_full_norm","",600,0,3000);

    h_EgammaAirBox = new TH1D("h_EgammaAirBox","",600,0,120);
    h_EgammaAirBox_norm = new TH1D("h_EgammaAirBox_norm","",600,0,120);
    h_EgammaAirBox_full = new TH1D("h_EgammaAirBox_full","",600,0,3000);
    h_EgammaAirBox_full_norm = new TH1D("h_EgammaAirBox_full_norm","",600,0,3000);

    h_EallAirBox = new TH1D("h_EallAirBox","",600,0,120);
    h_EallAirBox_norm = new TH1D("h_EallAirBox_norm","",600,0,120);
    h_EallAirBox_full = new TH1D("h_EallAirBox_full","",600,0,3000);
    h_EallAirBox_full_norm = new TH1D("h_EallAirBox_full_norm","",600,0,3000);

    //double bins[22] = {0,0.001,0.005,0.010,0.030,0.050,0.100,0.500,1.000,2.000,3.000,4.000,6.000,10,50,100,200,300,400,500,1000,2000};
    double bins[22] = {0.,1.,5.,10.,30.,50.,100.,500.,1000.,2000.,3000.,4000.,6000.,10000.,50000.,100000.,200000.,300000.,400000.,500000.,1000000.,2000000.}; //keV

    h_EneutronShield0 = new TH1D("h_EneutronShield0","",600,0,120);
    h_EneutronShield0_norm = new TH1D("h_EneutronShield0_norm","",600,0,120);
    //h_EneutronShield0_full = new TH1D("h_EneutronShield0_full","",600,0,3000);
    //h_EneutronShield0_full_norm = new TH1D("h_EneutronShield0_full_norm","",600,0,3000);
    h_EneutronShield0_full = new TH1D("h_EneutronShield0_full","",21,bins);
    h_EneutronShield0_full_norm = new TH1D("h_EneutronShield0_full_norm","",21,bins);

    h_EneutronShield1 = new TH1D("h_EneutronShield1","",600,0,120);
    h_EneutronShield1_norm = new TH1D("h_EneutronShield1_norm","",600,0,120);
    //h_EneutronShield1_full = new TH1D("h_EneutronShield1_full","",600,0,3000);
    //h_EneutronShield1_full_norm = new TH1D("h_EneutronShield1_full_norm","",600,0,3000);
    h_EneutronShield1_full = new TH1D("h_EneutronShield1_full","",21,bins);
    h_EneutronShield1_full_norm = new TH1D("h_EneutronShield1_full_norm","",21,bins);

    h_EneutronShield2 = new TH1D("h_EneutronShield2","",600,0,120);
    h_EneutronShield2_norm = new TH1D("h_EneutronShield2_norm","",600,0,120);
    //h_EneutronShield2_full = new TH1D("h_EneutronShield2_full","",600,0,3000);
    //h_EneutronShield2_full_norm = new TH1D("h_EneutronShield2_full_norm","",600,0,3000);
    h_EneutronShield2_full = new TH1D("h_EneutronShield2_full","",21,bins);
    h_EneutronShield2_full_norm = new TH1D("h_EneutronShield2_full_norm","",21,bins);

    h_EneutronShield3 = new TH1D("h_EneutronShield3","",600,0,120);
    h_EneutronShield3_norm = new TH1D("h_EneutronShield3_norm","",600,0,120);
    //h_EneutronShield3_full = new TH1D("h_EneutronShield3_full","",600,0,3000);
    //h_EneutronShield3_full_norm = new TH1D("h_EneutronShield3_full_norm","",600,0,3000);
    h_EneutronShield3_full = new TH1D("h_EneutronShield3_full","",21,bins);
    h_EneutronShield3_full_norm = new TH1D("h_EneutronShield3_full_norm","",21,bins);

    h_EneutronAirBox = new TH1D("h_EneutronAirBox","",600,0,120);
    h_EneutronAirBox_norm = new TH1D("h_EneutronAirBox_norm","",600,0,120);
    //h_EneutronAirBox_full = new TH1D("h_EneutronAirBox_full","",600,0,3000);
    //h_EneutronAirBox_full_norm = new TH1D("h_EneutronAirBox_full_norm","",600,0,3000);
    h_EneutronAirBox_full = new TH1D("h_EneutronAirBox_full","",21,bins);
    h_EneutronAirBox_full_norm = new TH1D("h_EneutronAirBox_full_norm","",21,bins);
   // h_AbsPxShield0 = new TH1D("h_AbsPxShield0","",600,-1,1);
   // h_AbsPyShield0 = new TH1D("h_AbsPyShield0","",600,-1,1);
   // h_AbsPzShield0 = new TH1D("h_AbsPzShield0","",600,-1,1);
   // 
   // h_AbsPxShield1 = new TH1D("h_AbsPxShield1","",600,-1,1);
   // h_AbsPyShield1 = new TH1D("h_AbsPyShield1","",600,-1,1);
   // h_AbsPzShield1 = new TH1D("h_AbsPzShield1","",600,-1,1);
   // 
   // h_AbsPxShield2 = new TH1D("h_AbsPxShield2","",600,-1,1);
   // h_AbsPyShield2 = new TH1D("h_AbsPyShield2","",600,-1,1);
   // h_AbsPzShield2 = new TH1D("h_AbsPzShield2","",600,-1,1);

   // h_AbsPxShield3 = new TH1D("h_AbsPxShield3","",600,-1,1);
   // h_AbsPyShield3 = new TH1D("h_AbsPyShield3","",600,-1,1);
   // h_AbsPzShield3 = new TH1D("h_AbsPzShield3","",600,-1,1);
   // 
   // h_AbsPxAirBox = new TH1D("h_AbsPxAirBox","",600,-1,1);
   // h_AbsPyAirBox = new TH1D("h_AbsPyAirBox","",600,-1,1);
   // h_AbsPzAirBox = new TH1D("h_AbsPzAirBox","",600,-1,1);
    
    h_GammaThetaShield0 = new TH1D("h_GammaThetaShield0","",120,0,TMath::Pi());
    h_GammaPhiShield0   = new TH1D("h_GammaPhiShield0","",120,0,2*TMath::Pi()); 
    h_GammaThetaShield1= new TH1D("h_GammaThetaShield1","",120,0,TMath::Pi());
    h_GammaPhiShield1  = new TH1D("h_GammaPhiShield1","",120,0,2*TMath::Pi());
    h_GammaThetaShield2= new TH1D("h_GammaThetaShield2","",120,0,TMath::Pi());
    h_GammaPhiShield2 = new TH1D("h_GammaPhiShield2","",120,0,2*TMath::Pi());
    h_GammaThetaShield3= new TH1D("h_GammaThetaShield3","",120,0,TMath::Pi());
    h_GammaPhiShield3 = new TH1D("h_GammaPhiShield3","",120,0,2*TMath::Pi());
    h_GammaThetaAirBox= new TH1D("h_GammaThetaAirBox","",120,0,TMath::Pi());
    h_GammaPhiAirBox = new TH1D("h_GammaPhiAirBox","",120,0,2*TMath::Pi());
    
    h_NeutronThetaShield0 = new TH1D("h_NeutronThetaShield0","",120,0,TMath::Pi());
    h_NeutronPhiShield0   = new TH1D("h_NeutronPhiShield0","",120,0,2*TMath::Pi()); 
    h_NeutronThetaShield1= new TH1D("h_NeutronThetaShield1","",120,0,TMath::Pi());
    h_NeutronPhiShield1  = new TH1D("h_NeutronPhiShield1","",120,0,2*TMath::Pi());
    h_NeutronThetaShield2= new TH1D("h_NeutronThetaShield2","",120,0,TMath::Pi());
    h_NeutronPhiShield2 = new TH1D("h_NeutronPhiShield2","",120,0,2*TMath::Pi());
    h_NeutronThetaShield3= new TH1D("h_NeutronThetaShield3","",120,0,TMath::Pi());
    h_NeutronPhiShield3 = new TH1D("h_NeutronPhiShield3","",120,0,2*TMath::Pi());
    h_NeutronThetaAirBox= new TH1D("h_NeutronThetaAirBox","",120,0,TMath::Pi());
    h_NeutronPhiAirBox = new TH1D("h_NeutronPhiAirBox","",120,0,2*TMath::Pi());

    
    h_E_ele = new TH1D("h_E_ele","",600,0,120);
    h_E_ele_norm = new TH1D("h_E_ele_norm","",600,0,120);
    h_E_ele_full = new TH1D("h_E_ele_full","",600,0,3000);
    h_E_ele_full_norm = new TH1D("h_E_ele_full_norm","",600,0,3000);

    h_E_pos = new TH1D("h_E_pos","",600,0,120);
    h_E_pos_norm = new TH1D("h_E_pos_norm","",600,0,120);
    h_E_pos_full = new TH1D("h_E_pos_full","",600,0,3000);
    h_E_pos_full_norm = new TH1D("h_E_pos_full_norm","",600,0,3000);

    h_E_pro = new TH1D("h_E_pro","",600,0,120);
    h_E_pro_norm = new TH1D("h_E_pro_norm","",600,0,120);
    h_E_pro_full = new TH1D("h_E_pro_full","",600,0,3000);
    h_E_pro_full_norm = new TH1D("h_E_pro_full_norm","",600,0,3000);

    h3_xyz_ele = new TH3D("h3_xyx_ele","",100,-600,600,100,-600,600,100,-600,600);
    h3_xyz_ele_fiducial = new TH3D("h3_xyx_ele_fiducial","",100,-600,600,100,-600,600,100,-600,600);
    h3_xyz_pos = new TH3D("h3_xyx_pos","",100,-600,600,100,-600,600,600,-600,600);
    h3_xyz_pro = new TH3D("h3_xyx_pro","",100,-600,600,100,-600,600,600,-600,600);

    h_NTot->Sumw2();
    h_NTotFlux0->Sumw2();
    h_NGammaFlux1->Sumw2();
    h_NGammaFlux2->Sumw2();
    h_NGammaFlux3->Sumw2();
    h_NGammaAirBox->Sumw2();
    h_NNeutronFlux1->Sumw2();
    h_NNeutronFlux2->Sumw2();
    h_NNeutronFlux3->Sumw2();
    h_NNeutronAirBox->Sumw2();

    h_edepDet->Sumw2();
    h_edepDet_norm->Sumw2();
    h_edepDet_full->Sumw2();
    h_edepDet_full_norm->Sumw2();
    
    h_edepDet_NR->Sumw2();
    h_edepDet_NR_norm->Sumw2();
    h_edepDet_NR_full->Sumw2();
    h_edepDet_NR_full_norm->Sumw2();

    h_EgammaShield0->Sumw2();
    h_EgammaShield0_norm->Sumw2(); 
    h_EgammaShield0_full->Sumw2();    
    h_EgammaShield0_full_norm->Sumw2();

    h_EgammaShield1->Sumw2();
    h_EgammaShield1_norm->Sumw2(); 
    h_EgammaShield1_full->Sumw2();    
    h_EgammaShield1_full_norm->Sumw2();
    
    h_EgammaShield2->Sumw2();
    h_EgammaShield2_norm->Sumw2(); 
    h_EgammaShield2_full->Sumw2();    
    h_EgammaShield2_full_norm->Sumw2();

    h_EgammaShield3->Sumw2();
    h_EgammaShield3_norm->Sumw2(); 
    h_EgammaShield3_full->Sumw2();    
    h_EgammaShield3_full_norm->Sumw2();

    h_EgammaAirBox->Sumw2();
    h_EgammaAirBox_norm->Sumw2();
    h_EgammaAirBox_full->Sumw2();
    h_EgammaAirBox_full_norm->Sumw2();

    h_EneutronShield0->Sumw2();
    h_EneutronShield0_norm->Sumw2(); 
    h_EneutronShield0_full->Sumw2();    
    h_EneutronShield0_full_norm->Sumw2();

    h_EneutronShield1->Sumw2();
    h_EneutronShield1_norm->Sumw2(); 
    h_EneutronShield1_full->Sumw2();    
    h_EneutronShield1_full_norm->Sumw2();
    
    h_EneutronShield2->Sumw2();
    h_EneutronShield2_norm->Sumw2(); 
    h_EneutronShield2_full->Sumw2();    
    h_EneutronShield2_full_norm->Sumw2();

    h_EneutronShield3->Sumw2();
    h_EneutronShield3_norm->Sumw2(); 
    h_EneutronShield3_full->Sumw2();    
    h_EneutronShield3_full_norm->Sumw2();

    h_EneutronAirBox->Sumw2();
    h_EneutronAirBox_norm->Sumw2();
    h_EneutronAirBox_full->Sumw2();
    h_EneutronAirBox_full_norm->Sumw2();
    //h_AbsPxShield0->Sumw2(); 
    //h_AbsPyShield0->Sumw2();
    //h_AbsPzShield0->Sumw2();
    //
    //h_AbsPxShield1->Sumw2();
    //h_AbsPyShield1->Sumw2();
    //h_AbsPzShield1->Sumw2();

    //h_AbsPxShield2->Sumw2();
    //h_AbsPyShield2->Sumw2();
    //h_AbsPzShield2->Sumw2();
    //
    //h_AbsPxShield3->Sumw2();
    //h_AbsPyShield3->Sumw2();
    //h_AbsPzShield3->Sumw2();

    //h_AbsPxAirBox->Sumw2();
    //h_AbsPyAirBox->Sumw2();
    //h_AbsPzAirBox->Sumw2();

    h_GammaThetaShield0->Sumw2();
    h_GammaPhiShield0->Sumw2(); 
    h_GammaThetaShield1->Sumw2();
    h_GammaPhiShield1->Sumw2(); 
    h_GammaThetaShield2->Sumw2();
    h_GammaPhiShield2->Sumw2(); 
    h_GammaThetaShield3->Sumw2();
    h_GammaPhiShield3->Sumw2(); 
    h_GammaThetaAirBox->Sumw2();
    h_GammaPhiAirBox->Sumw2(); 
  
    h_NeutronThetaShield0->Sumw2();
    h_NeutronPhiShield0->Sumw2(); 
    h_NeutronThetaShield1->Sumw2();
    h_NeutronPhiShield1->Sumw2(); 
    h_NeutronThetaShield2->Sumw2();
    h_NeutronPhiShield2->Sumw2(); 
    h_NeutronThetaShield3->Sumw2();
    h_NeutronPhiShield3->Sumw2(); 
    h_NeutronThetaAirBox->Sumw2();
    h_NeutronPhiAirBox->Sumw2(); 


    h_EallAirBox->Sumw2();
    h_EallAirBox_norm->Sumw2();
    h_EallAirBox_full->Sumw2();
    h_EallAirBox_full_norm->Sumw2();

    h_E_ele->Sumw2();
    h_E_ele_norm->Sumw2();
    h_E_ele_full->Sumw2();
    h_E_ele_full_norm->Sumw2();

    h_E_pos->Sumw2();
    h_E_pos_norm->Sumw2();
    h_E_pos_full->Sumw2();
    h_E_pos_full_norm->Sumw2();

    h_E_pro->Sumw2();
    h_E_pro_norm->Sumw2();
    h_E_pro_full->Sumw2();
    h_E_pro_full_norm->Sumw2();

}

void CYGNOAnalysis::SetTree()
{

}



void CYGNOAnalysis::Loop()
{
    Long64_t  events = 0;
    Long64_t  flu0 = 0;
    Long64_t  gammaflu1 = 0;
    Long64_t  gammaflu2 = 0;
    Long64_t  gammaflu3 = 0;
    Long64_t  gammaflu_airbox = 0;
    Long64_t  neutronflu1 = 0;
    Long64_t  neutronflu2 = 0;
    Long64_t  neutronflu3 = 0;
    Long64_t  neutronflu_airbox = 0;
    _total_events = 0;
    _total_flux_events = 0.;   
    _total_flux_events_flu0 = 0;
    _total_flux_events_flu0_test = 0;
    _total_flux_events_gammaflu1=0; 
    _total_flux_events_gammaflu2=0; 
    _total_flux_events_gammaflu3=0; 
    _total_flux_events_gammaflu_airbox=0; 
    _total_flux_events_neutronflu1=0; 
    _total_flux_events_neutronflu2=0; 
    _total_flux_events_neutronflu3=0; 
    _total_flux_events_neutronflu_airbox=0; 
 
    Long64_t nentries;
   
    cout<< "Setting histograms" << endl;  
    this->SetHistograms();
    //this->SetTree();
    
    list<string>::iterator my_file_iter;

    for(my_file_iter = _file_to_be_open.begin(); my_file_iter != _file_to_be_open.end(); ++my_file_iter){
        //loop on files
        TFile * fopen = TFile::Open(my_file_iter->c_str());
        TTree * mytree = new TTree();
        TH1D *n_event_gen;
        TH1D *n_event_flu0;
        TH1D *n_event_flugamma1;
        TH1D *n_event_flugamma2;
        TH1D *n_event_flugamma3;
        TH1D *n_event_flugamma_airbox;
        TH1D *n_event_fluneutron1;
        TH1D *n_event_fluneutron2;
        TH1D *n_event_fluneutron3;
        TH1D *n_event_fluneutron_airbox;
                
	//	if ((fopen->IsOpen()==false) ||  (fopen->GetListOfKeys()->Contains("nT")==false)) continue; 
 	if ((fopen->GetListOfKeys()->Contains("nTuple")==false)) continue; 

        n_event_gen = (TH1D*) fopen->Get("histo/NTot");
        n_event_flu0 = (TH1D*) fopen->Get("histo/numFlu0");
        n_event_flugamma1 = (TH1D*) fopen->Get("histo/numFluGamma1");
        n_event_flugamma2 = (TH1D*) fopen->Get("histo/numFluGamma2");
        n_event_flugamma3 = (TH1D*) fopen->Get("histo/numFluGamma3");
        n_event_flugamma_airbox = (TH1D*) fopen->Get("histo/numFluGammaAirBox");
        //FIXME : new structure
        n_event_fluneutron1 = (TH1D*) fopen->Get("histo/numFluNeutron1");
        n_event_fluneutron2 = (TH1D*) fopen->Get("histo/numFluNeutron2");
        n_event_fluneutron3 = (TH1D*) fopen->Get("histo/numFluNeutron3");
        n_event_fluneutron_airbox = (TH1D*) fopen->Get("histo/numFluNeutronAirBox");

        
	events = n_event_gen->GetBinContent(1);
        _total_events += events;
        
        flu0 = n_event_flu0->GetBinContent(2); //primaries entering the shielding0 once
        
	gammaflu1 = 0 ; 
        gammaflu2 = 0 ;
        gammaflu3 = 0 ;
        gammaflu_airbox =0; 
        //gammaflu1 = n_event_flugamma1->GetBinContent(2); //gammas entering the shielding1 once
        //gammaflu2 = n_event_flugamma2->GetBinContent(2); //gammas entering the shielding2 once
        //gammaflu3 = n_event_flugamma3->GetBinContent(2); //gammas entering the shielding3 once
        //gammaflu_airbox = n_event_flugamma_airbox->GetBinContent(2); //gammas entering the airbox once
        for (int j=1; j<=10; j++){
            gammaflu1 += n_event_flugamma1->GetBinContent(j+1)*j; //gamma entering the shielding1 
            gammaflu2 += n_event_flugamma2->GetBinContent(j+1)*j; //gamma entering the shielding2 
            gammaflu3 += n_event_flugamma3->GetBinContent(j+1)*j; //gamma entering the shielding3 
            gammaflu_airbox += n_event_flugamma_airbox->GetBinContent(j+1)*j; //gamma entering the airbox 
        }



        neutronflu1 = 0 ; 
        neutronflu2 = 0 ;
        neutronflu3 = 0 ;
        neutronflu_airbox =0; 
        
        //FIXME : new structure
        for (int j=1; j<=10; j++){
            neutronflu1 += n_event_fluneutron1->GetBinContent(j+1)*j; //neutrons entering the shielding1 
            neutronflu2 += n_event_fluneutron2->GetBinContent(j+1)*j; //neutrons entering the shielding2 
            neutronflu3 += n_event_fluneutron3->GetBinContent(j+1)*j; //neutrons entering the shielding3 
            neutronflu_airbox += n_event_fluneutron_airbox->GetBinContent(j+1)*j; //neutrons entering the airbox 
        }
        _total_flux_events_flu0 += flu0;        
        cout << "flu0 = " << flu0 << endl;
        _total_flux_events_gammaflu1 += gammaflu1;        
        cout << "gamma flux 1 = " << gammaflu1 << endl;
        _total_flux_events_gammaflu2 += gammaflu2;        
        cout << "gamma flux 2 = " << gammaflu2 << endl;
        _total_flux_events_gammaflu3 += gammaflu3;        
        cout << "gamma flux 3 = " << gammaflu3 << endl;
        _total_flux_events_gammaflu_airbox += gammaflu_airbox;        
        cout << "gamma flux airbox = " << gammaflu_airbox << endl;
        _total_flux_events_neutronflu1 += neutronflu1;        
        cout << "neutron flux 1 = " << neutronflu1 << endl;
        _total_flux_events_neutronflu2 += neutronflu2;        
        cout << "neutron flux 2 = " << neutronflu2 << endl;
        _total_flux_events_neutronflu3 += neutronflu3;        
        cout << "neutron flux 3 = " << neutronflu3 << endl;
        _total_flux_events_neutronflu_airbox += neutronflu_airbox;        
        cout << "neutron flux airbox = " << neutronflu_airbox << endl;


 
        mytree = (TTree*) fopen->Get("nTuple");
        this->Init(mytree);
        
        nentries = mytree->GetEntriesFast();
        cout<<"Found file "<<*my_file_iter<<" Entries = "<<mytree->GetEntries()<<"  Events = "<<events<<" Total = "<<_total_events<<endl;
	
	TBranch* br = (TBranch*)mytree->GetListOfBranches()->FindObject("E_flu");
        cout << br << endl;
        
        for (Long64_t jentry=0; jentry<nentries;jentry++) { //loop on entries
            
            if(jentry %1000000 == 0){cout<<"Event N. "<<jentry<<endl;}
            
            //nb = mytree->GetEntry(jentry);  //load the full entry of the tree (slow)
            
            //load only some branches ( faster !)
            b_energyDep->GetEntry(jentry);
            b_numflu0->GetEntry(jentry);
            //FIXME : _flu branches + NR
            b_energyDep_NR->GetEntry(jentry);
            //if (br){ 
	      b_E_flu->GetEntry(jentry);
              if (E_flu->size()==0)
	          continue;

              b_trackid_flu->GetEntry(jentry);
              b_volNo_flu->GetEntry(jentry);
              b_prestepVolNo_flu->GetEntry(jentry);
              b_pdg_flu->GetEntry(jentry);
              //b_poststepx_flu->GetEntry(jentry);
              //b_poststepy_flu->GetEntry(jentry);
              //b_poststepz_flu->GetEntry(jentry);
              b_px_flu->GetEntry(jentry);
              b_py_flu->GetEntry(jentry);
              b_pz_flu->GetEntry(jentry);
              b_E_ele->GetEntry(jentry);
              b_parentid_ele->GetEntry(jentry);
              b_trackid_ele->GetEntry(jentry);
              //b_E_pos->GetEntry(jentry);
              //b_E_pro->GetEntry(jentry);
              //b_E_ion->GetEntry(jentry);
              b_poststepx_ele->GetEntry(jentry);
              b_poststepy_ele->GetEntry(jentry);
              b_poststepz_ele->GetEntry(jentry);
              //b_poststepx_pos->GetEntry(jentry);
              //b_poststepy_pos->GetEntry(jentry);
              //b_poststepz_pos->GetEntry(jentry);
              //b_poststepx_pro->GetEntry(jentry);
              //b_poststepy_pro->GetEntry(jentry);
              //b_poststepz_pro->GetEntry(jentry);
              //b_posx_ion->GetEntry(jentry);
              //b_posy_ion->GetEntry(jentry);
              //b_posz_ion->GetEntry(jentry);
	      //
	    //}//if branch 
            if(_smearing == true){
                this->Smearing();
            }
          
            double phi;
	    
            //FIXME : _flu branches
            //All
            //if (br){
	      for (int iflu=0; iflu < E_flu->size(); iflu++){ 

                      if(prestepVolNo_flu->at(iflu) ==2 && volNo_flu->at(iflu)==3 && pdg_flu->at(iflu)==22){
                          h_EgammaShield0->Fill(E_flu->at(iflu));
                          h_EgammaShield0_norm->Fill(E_flu->at(iflu)); 
                          h_EgammaShield0_full->Fill(E_flu->at(iflu));    
                          h_EgammaShield0_full_norm->Fill(E_flu->at(iflu));
                          h_GammaThetaShield0->Fill(acos(-pz_flu->at(iflu)/sqrt(px_flu->at(iflu)*px_flu->at(iflu)+py_flu->at(iflu)*py_flu->at(iflu)+pz_flu->at(iflu)*pz_flu->at(iflu))));
                          phi = atan2(-py_flu->at(iflu),-px_flu->at(iflu));
                          if (phi<0) phi = phi+2*TMath::Pi();
                          h_GammaPhiShield0->Fill(phi);
	        	  //cout << "phi = " << acos(-px_flu->at(iflu)*sqrt(px_flu->at(iflu)*px_flu->at(iflu)+py_flu->at(iflu)*py_flu->at(iflu)+pz_flu->at(iflu)*pz_flu->at(iflu))/sqrt(px_flu->at(iflu)*px_flu->at(iflu)+py_flu->at(iflu)*py_flu->at(iflu))) << endl;
                      }
                      if(prestepVolNo_flu->at(iflu) ==3 && volNo_flu->at(iflu)==4 && pdg_flu->at(iflu)==22){
                          h_EgammaShield1->Fill(E_flu->at(iflu));
                          h_EgammaShield1_norm->Fill(E_flu->at(iflu)); 
                          h_EgammaShield1_full->Fill(E_flu->at(iflu));    
                          h_EgammaShield1_full_norm->Fill(E_flu->at(iflu));
                          h_GammaThetaShield1->Fill(acos(-pz_flu->at(iflu)/sqrt(px_flu->at(iflu)*px_flu->at(iflu)+py_flu->at(iflu)*py_flu->at(iflu)+pz_flu->at(iflu)*pz_flu->at(iflu))));
                          phi = atan2(-py_flu->at(iflu),-px_flu->at(iflu));
                          if (phi<0) phi = phi+2*TMath::Pi();
                          h_GammaPhiShield1->Fill(phi);
                          ////h_PhiShield1->Fill(atan2(py_flu->at(iflu)/px_flu->at(iflu)));
                          ////Phi defined between -pi and pi
                      }
                          
                      if(prestepVolNo_flu->at(iflu) ==4 && volNo_flu->at(iflu)==5 && pdg_flu->at(iflu)==22){
                          h_EgammaShield2->Fill(E_flu->at(iflu));
                          h_EgammaShield2_norm->Fill(E_flu->at(iflu)); 
                          h_EgammaShield2_full->Fill(E_flu->at(iflu));    
                          h_EgammaShield2_full_norm->Fill(E_flu->at(iflu));
                          h_GammaThetaShield2->Fill(acos(-pz_flu->at(iflu)/sqrt(px_flu->at(iflu)*px_flu->at(iflu)+py_flu->at(iflu)*py_flu->at(iflu)+pz_flu->at(iflu)*pz_flu->at(iflu))));
                          phi = atan2(-py_flu->at(iflu),-px_flu->at(iflu));
                          if (phi<0) phi = phi+2*TMath::Pi();
                          h_GammaPhiShield2->Fill(phi);
                      }
        
                      if(prestepVolNo_flu->at(iflu) ==5 && volNo_flu->at(iflu)==6 && pdg_flu->at(iflu)==22){
                          h_EgammaShield3->Fill(E_flu->at(iflu));
                          h_EgammaShield3_norm->Fill(E_flu->at(iflu)); 
                          h_EgammaShield3_full->Fill(E_flu->at(iflu));    
                          h_EgammaShield3_full_norm->Fill(E_flu->at(iflu));
                          h_GammaThetaShield3->Fill(acos(-pz_flu->at(iflu)/sqrt(px_flu->at(iflu)*px_flu->at(iflu)+py_flu->at(iflu)*py_flu->at(iflu)+pz_flu->at(iflu)*pz_flu->at(iflu))));
                          phi = atan2(-py_flu->at(iflu),-px_flu->at(iflu));
                          if (phi<0) phi = phi+2*TMath::Pi();
                          h_GammaPhiShield3->Fill(phi);
                      }
        
                      if(prestepVolNo_flu->at(iflu) ==6 && volNo_flu->at(iflu)==7 && pdg_flu->at(iflu)==22){
                          h_EgammaAirBox->Fill(E_flu->at(iflu));
                          h_EgammaAirBox_norm->Fill(E_flu->at(iflu));
                          h_EgammaAirBox_full->Fill(E_flu->at(iflu));
                          h_EgammaAirBox_full_norm->Fill(E_flu->at(iflu));
                          h_GammaThetaAirBox->Fill(acos(-pz_flu->at(iflu)/sqrt(px_flu->at(iflu)*px_flu->at(iflu)+py_flu->at(iflu)*py_flu->at(iflu)+pz_flu->at(iflu)*pz_flu->at(iflu))));
                          phi = atan2(-py_flu->at(iflu),-px_flu->at(iflu));
                          if (phi<0) phi = phi+2*TMath::Pi();
                          h_GammaPhiAirBox->Fill(phi);
                      }
        
                      if(prestepVolNo_flu->at(iflu) ==6 && volNo_flu->at(iflu)==7){
                          h_EallAirBox->Fill(E_flu->at(iflu));
                          h_EallAirBox_norm->Fill(E_flu->at(iflu));
                          h_EallAirBox_full->Fill(E_flu->at(iflu));
                          h_EallAirBox_full_norm->Fill(E_flu->at(iflu));
                      }
        
                      if(prestepVolNo_flu->at(iflu) ==2 && volNo_flu->at(iflu)==3 && pdg_flu->at(iflu)==2112){
                          h_EneutronShield0->Fill(E_flu->at(iflu)-939565.36);
                          h_EneutronShield0_norm->Fill(E_flu->at(iflu)-939565.36); 
                          h_EneutronShield0_full->Fill(E_flu->at(iflu)-939565.36);    
                          h_EneutronShield0_full_norm->Fill(E_flu->at(iflu)-939565.36);
                          h_NeutronThetaShield0->Fill(acos(-pz_flu->at(iflu)/sqrt(px_flu->at(iflu)*px_flu->at(iflu)+py_flu->at(iflu)*py_flu->at(iflu)+pz_flu->at(iflu)*pz_flu->at(iflu))));
                          phi = atan2(-py_flu->at(iflu),-px_flu->at(iflu));
                          if (phi<0) phi = phi+2*TMath::Pi();
                          h_NeutronPhiShield0->Fill(phi);
                      }
                      if(prestepVolNo_flu->at(iflu) ==3 && volNo_flu->at(iflu)==4 && pdg_flu->at(iflu)==2112){
                          h_EneutronShield1->Fill(E_flu->at(iflu)-939565.36);
                          h_EneutronShield1_norm->Fill(E_flu->at(iflu)-939565.36); 
                          h_EneutronShield1_full->Fill(E_flu->at(iflu)-939565.36);    
                          h_EneutronShield1_full_norm->Fill(E_flu->at(iflu)-939565.36);
                          h_NeutronThetaShield1->Fill(acos(-pz_flu->at(iflu)/sqrt(px_flu->at(iflu)*px_flu->at(iflu)+py_flu->at(iflu)*py_flu->at(iflu)+pz_flu->at(iflu)*pz_flu->at(iflu))));
                          phi = atan2(-py_flu->at(iflu),-px_flu->at(iflu));
                          if (phi<0) phi = phi+2*TMath::Pi();
                          h_NeutronPhiShield1->Fill(phi);
                      }
                          
                      if(prestepVolNo_flu->at(iflu) ==4 && volNo_flu->at(iflu)==5 && pdg_flu->at(iflu)==2112){
                          h_EneutronShield2->Fill(E_flu->at(iflu)-939565.36);
                          h_EneutronShield2_norm->Fill(E_flu->at(iflu)-939565.36); 
                          h_EneutronShield2_full->Fill(E_flu->at(iflu)-939565.36);    
                          h_EneutronShield2_full_norm->Fill(E_flu->at(iflu)-939565.36);
                          h_NeutronThetaShield2->Fill(acos(-pz_flu->at(iflu)/sqrt(px_flu->at(iflu)*px_flu->at(iflu)+py_flu->at(iflu)*py_flu->at(iflu)+pz_flu->at(iflu)*pz_flu->at(iflu))));
                          phi = atan2(-py_flu->at(iflu),-px_flu->at(iflu));
                          if (phi<0) phi = phi+2*TMath::Pi();
                          h_NeutronPhiShield2->Fill(phi);
                      }
        
                      if(prestepVolNo_flu->at(iflu) ==5 && volNo_flu->at(iflu)==6 && pdg_flu->at(iflu)==2112){
                          h_EneutronShield3->Fill(E_flu->at(iflu)-939565.36);
                          h_EneutronShield3_norm->Fill(E_flu->at(iflu)-939565.36); 
                          h_EneutronShield3_full->Fill(E_flu->at(iflu)-939565.36);    
                          h_EneutronShield3_full_norm->Fill(E_flu->at(iflu)-939565.36);
                          h_NeutronThetaShield3->Fill(acos(-pz_flu->at(iflu)/sqrt(px_flu->at(iflu)*px_flu->at(iflu)+py_flu->at(iflu)*py_flu->at(iflu)+pz_flu->at(iflu)*pz_flu->at(iflu))));
                          phi = atan2(-py_flu->at(iflu),-px_flu->at(iflu));
                          if (phi<0) phi = phi+2*TMath::Pi();
                          h_NeutronPhiShield3->Fill(phi);
                      }
        
                      if(prestepVolNo_flu->at(iflu) ==6 && volNo_flu->at(iflu)==7 && pdg_flu->at(iflu)==2112){
                          h_EneutronAirBox->Fill(E_flu->at(iflu)-939565.36);
                          h_EneutronAirBox_norm->Fill(E_flu->at(iflu)-939565.36);
                          h_EneutronAirBox_full->Fill(E_flu->at(iflu)-939565.36);
                          h_EneutronAirBox_full_norm->Fill(E_flu->at(iflu)-939565.36);
                          h_NeutronThetaAirBox->Fill(acos(-pz_flu->at(iflu)/sqrt(px_flu->at(iflu)*px_flu->at(iflu)+py_flu->at(iflu)*py_flu->at(iflu)+pz_flu->at(iflu)*pz_flu->at(iflu))));
                          phi = atan2(-py_flu->at(iflu),-px_flu->at(iflu));
                          if (phi<0) phi = phi+2*TMath::Pi();
                          h_NeutronPhiAirBox->Fill(phi);
                      }
        
                }
             
             //FIXME : double counting ??
             for (int iele = 0; iele < E_ele->size(); iele++){
                     Bool_t doublecount = false;
	             if(iele!=0 && parentid_ele->at(iele)!=trackid_ele->at(iele-1) && parentid_ele->at(iele)!=parentid_ele->at(iele-1)) {
                         // method to be checked...
                         //for (int jele=0; jele<iele; jele++){
                         //    if(parentid_ele->at(iele)==trackid_ele->at(jele)){
                         //        doublecount = true;
                         //        break;
                         //    }
                         //}
                         if (!doublecount){
                             h3_xyz_ele->Fill(poststepx_ele->at(iele),poststepy_ele->at(iele),poststepz_ele->at(iele));	
                             
                             if (TMath::Abs(poststepx_ele->at(iele))<510 && TMath::Abs(poststepy_ele->at(iele))<510 && TMath::Abs(poststepz_ele->at(iele))<510 ){
	                          h3_xyz_ele_fiducial->Fill(poststepx_ele->at(iele),poststepy_ele->at(iele),poststepz_ele->at(iele));	
	                     }
                         }
                     }
              }
              //for (int ipos = 0; ipos < E_pos->size(); ipos++){
	      //        h3_xyz_pos->Fill(poststepx_pos->at(ipos),poststepy_pos->at(ipos),poststepz_pos->at(ipos));	
              //}
              //for (int ipro = 0; ipro < E_pro->size(); ipro++){
	      //        h3_xyz_pro->Fill(poststepx_pro->at(ipro),poststepy_pro->at(ipro),poststepz_pro->at(ipro));	
              //}
              //for (int iion = 0; iion < E_ion->size(); iion++){
	      //        h3_xyz_ion->Fill(posx_ion->at(iion),posy_ion->at(iion),posz_ion->at(iion));	
              //}
	    //}  //end if branch exist
              if(energyDep >0.){
                  h_edepDet->Fill(energyDep);
                  h_edepDet_norm->Fill(energyDep);
                  h_edepDet_full->Fill(energyDep);
                  h_edepDet_full_norm->Fill(energyDep);
                  //cout << "energy deposit = " << energyDep <<  endl;
                  //FIXME                  
                  if(energyDep_NR >0.){
                      h_edepDet_NR->Fill(energyDep_NR);
                      h_edepDet_NR_norm->Fill(energyDep_NR);
                      h_edepDet_NR_full->Fill(energyDep_NR);
                      h_edepDet_NR_full_norm->Fill(energyDep_NR);
                    }
	      }	
              if (_externalflux){
                 if (numflu0>0)
              	_total_flux_events_flu0_test += numflu0;
             }    
	} //end loop on entries
        
	delete mytree;
        delete fopen;
        //delete n_event_gen;
    } //end loop on files
    
    h_NTot->SetBinContent(1,_total_events);
    h_NTotFlux0->SetBinContent(1,_total_flux_events_flu0);        
    h_NGammaFlux1->SetBinContent(1,_total_flux_events_gammaflu1);
    h_NGammaFlux2->SetBinContent(1,_total_flux_events_gammaflu2);
    h_NGammaFlux3->SetBinContent(1,_total_flux_events_gammaflu3);
    h_NGammaAirBox->SetBinContent(1,_total_flux_events_gammaflu_airbox);
    h_NNeutronFlux1->SetBinContent(1,_total_flux_events_neutronflu1);
    h_NNeutronFlux2->SetBinContent(1,_total_flux_events_neutronflu2);
    h_NNeutronFlux3->SetBinContent(1,_total_flux_events_neutronflu3);
    h_NNeutronAirBox->SetBinContent(1,_total_flux_events_neutronflu_airbox);

    //if (_externalflux){
    //    _total_flux_events += h_EgammaShield0->GetEntries();
    //}    
    //cout << "h_EgammaShield0 entries = " << _total_flux_events << endl;
    //cout << "numflu0 = " << _total_flux_events_flu0 << endl;
    //cout << "numflu0_test = " << _total_flux_events_flu0_test << endl;


    this->Normalize();
    this->ComputeBKG();

    //cygno_tree->Fill();
    
    _f_output->cd();
    _f_output->Write();
    _f_output->Close();
 

}


void CYGNOAnalysis::Smearing(){
    Double_t smearing = 1;
    if(energyDep){
    smearing = factor->Gaus(1, 1. / sqrt(energyDep));
    }else{
    smearing = 1.;
    }
    energyDep = energyDep*smearing;
    
}

void CYGNOAnalysis::Normalize(){
    
    Double_t binwitdh, binwitdh_full, norm, normfull;
    Double_t norm_flu0, norm_flu0_full;
    Double_t norm_flu1, norm_flu1_full;
    Double_t norm_flu2, norm_flu2_full;
    Double_t norm_flu3, norm_flu3_full;
    Double_t norm_flu_airbox, norm_flu_airbox_full;
    Double_t surface_Shield0, surface_Shield1, surface_Shield2, surface_Shield3, surface_AirBox;
   
    //FIXME CYGNO 
    //Double_t AirBox_x = 1.45;
    //Double_t AirBox_y = 1.45;
    //Double_t AirBox_z = 2.65; //here x and z swiped wrt CYGNODetectorConstruction 
    //FIXME LIME
    Double_t AirBox_x = 0.8;
    Double_t AirBox_y = 0.8;
    Double_t AirBox_z = 2; //here x and z swiped wrt CYGNODetectorConstruction 
     
    Double_t ndays;
    if (!_externalflux){
      Double_t ndec1d = _activity*86400*_mass;
      ndays = _total_events/ndec1d;
    }
    else{
      Double_t nflu_1d = _externalflux_value * (2*(AirBox_x+2*_tot_shield_thickness)*(2+AirBox_y*_tot_shield_thickness) + 4*(AirBox_y+2*_tot_shield_thickness)*(AirBox_z+2*_tot_shield_thickness)) * 10000. * 86400.;
      //ndays = _total_flux_events/ nflu_1d;
      ndays = _total_flux_events_flu0/ nflu_1d;
    } 

    std::cout << "Equivalent time of this simulation: " << ndays << " days" << std::endl;
    binwitdh = h_edepDet_norm->GetBinWidth(1);
    norm = 1./(ndays*binwitdh*_CYGNO_gas_mass);
    h_edepDet_norm->Scale(norm);
    h_edepDet_NR_norm->Scale(norm);
    //normalized to cpd/kg/keV

    binwitdh_full = h_edepDet_full_norm->GetBinWidth(1);
    normfull = 1./(ndays*binwitdh_full*_CYGNO_gas_mass);
    h_edepDet_full_norm->Scale(normfull);
    h_edepDet_NR_full_norm->Scale(normfull);
    //normalized to cpd/kg/keV

    cout << "norm = " << norm << "   normfull = " << normfull  << "   binwidth = " << binwitdh << " CYGNO_gas_mass = " << _CYGNO_gas_mass << "  ndays = " <<ndays << endl;
     
    _norm  = norm;
    _normfull  = normfull;

    surface_Shield0 =(2*(AirBox_x+2*_tot_shield_thickness)*(AirBox_y+2*_tot_shield_thickness) + 4*(AirBox_y+2*_tot_shield_thickness)*(AirBox_z+2*_tot_shield_thickness)); 
    //norm_flu0 = _externalflux_value * 10000. * surface_Shield0 / h_EgammaShield0->GetEntries();  
    norm_flu0 = _externalflux_value * 10000. * surface_Shield0 / _total_flux_events_flu0;  
    double binwidth = h_EgammaShield0_norm->GetBinWidth(1);
    double binwidth_full = h_EgammaShield0_full_norm->GetBinWidth(1);
    
    h_EgammaShield0_norm->Scale(norm_flu0/surface_Shield0/1.e4/binwidth); 
    h_EgammaShield0_full_norm->Scale(norm_flu0/surface_Shield0/1.e4/binwidth_full);
    //normalized to cts/cm^2/sec/keV

    //norm_flu1 = (_externalflux_value * 10000. * (2*(AirBox_x+2*(_shield3_thickness+_shield2_thickness+_shield1_thickness))*(AirBox_y+2*(_shield3_thickness+_shield2_thickness+_shield1_thickness)) + 4*(AirBox_y+2*(_shield3_thickness+_shield2_thickness+_shield1_thickness))*(AirBox_z+2*(_shield3_thickness+_shield2_thickness+_shield1_thickness)))) / h_EgammaShield0->GetEntries();  
    //h_EgammaShield1_norm->Scale(norm_flu1); 
    //h_EgammaShield1_full_norm->Scale(norm_flu1);
    ////normalized to cts/sec

    //norm_flu2 = (_externalflux_value * 10000. * (2*(AirBox_x+2*(_shield3_thickness+_shield2_thickness))*(AirBox_y+2*(_shield3_thickness+_shield2_thickness)) + 4*(AirBox_y+2*(_shield3_thickness+_shield2_thickness))*(AirBox_z+2*(_shield3_thickness+_shield2_thickness)))) / h_EgammaShield0->GetEntries();  
    //h_EgammaShield2_norm->Scale(norm_flu2); 
    //h_EgammaShield2_full_norm->Scale(norm_flu2);
    ////normalized to cts/sec

    //norm_flu3 = (_externalflux_value * 10000. * (2*(2+2*_shield3_thickness)*(2+2*_shield3_thickness) + 4*(2+2*_shield3_thickness)*(3+2*_shield3_thickness))) / h_EgammaShield0->GetEntries();  
    //h_EgammaShield3_norm->Scale(norm_flu3); 
    //h_EgammaShield3_full_norm->Scale(norm_flu3);
    ////normalized to cts/sec

    //norm_flu_airbox = (_externalflux_value * 10000. * (2*2*2 + 4*2*3)) / h_EgammaShield0->GetEntries();  
    //h_EgammaAirBox_norm->Scale(norm_flu_airbox);
    //h_EgammaAirBox_full_norm->Scale(norm_flu_airbox);
    //h_EallAirBox_norm->Scale(norm);
    //h_EallAirBox_full_norm->Scale(normfull);
    ////normalized to cts/sec

    surface_Shield1 =(2*(AirBox_x+2*(_shield3_thickness+_shield2_thickness+_shield1_thickness))*(AirBox_y+2*(_shield3_thickness+_shield2_thickness+_shield1_thickness)) + 4*(AirBox_y+2*(_shield3_thickness+_shield2_thickness+_shield1_thickness))*(AirBox_z+2*(_shield3_thickness+_shield2_thickness+_shield1_thickness)));
    surface_Shield2 =  (2*(AirBox_x+2*(_shield3_thickness+_shield2_thickness))*(AirBox_y+2*(_shield3_thickness+_shield2_thickness)) + 4*(AirBox_y+2*(_shield3_thickness+_shield2_thickness))*(AirBox_z+2*(_shield3_thickness+_shield2_thickness))); 

    surface_Shield3 = (2*(AirBox_x+2*_shield3_thickness)*(AirBox_y+2*_shield3_thickness) + 4*(AirBox_y+2*_shield3_thickness)*(AirBox_z+2*_shield3_thickness)); 

    surface_AirBox  = 2*AirBox_x*AirBox_y + 4*AirBox_y*AirBox_z; 
    

    h_EgammaShield1_norm->Scale(norm_flu0/surface_Shield1/1.e4/binwidth); 
    h_EgammaShield1_full_norm->Scale(norm_flu0/surface_Shield1/1.e4/binwidth_full);
    h_EgammaShield2_norm->Scale(norm_flu0/surface_Shield2/1.e4/binwidth); 
    h_EgammaShield2_full_norm->Scale(norm_flu0/surface_Shield2/1.e4/binwidth_full);
    h_EgammaShield3_norm->Scale(norm_flu0/surface_Shield3/1.e4/binwidth); 
    h_EgammaShield3_full_norm->Scale(norm_flu0/surface_Shield3/1.e4/binwidth_full);
    h_EgammaAirBox_norm->Scale(norm_flu0/surface_AirBox/1.e4/binwidth); 
    h_EgammaAirBox_full_norm->Scale(norm_flu0/surface_AirBox/1.e4/binwidth_full);
    //normalized to cts/cm^2/sec/keV
    h_EgammaShield0_norm->GetYaxis()->SetTitle("Flux [#gamma cm^{-2} s^{-1} keV^{-1}")      ; 
    h_EgammaShield0_full_norm->GetYaxis()->SetTitle("Flux [#gamma cm^{-2} s^{-1} keV^{-1}") ;
    h_EgammaShield1_norm->GetYaxis()->SetTitle("Flux [#gamma cm^{-2} s^{-1} keV^{-1}")      ;
    h_EgammaShield1_full_norm->GetYaxis()->SetTitle("Flux [#gamma cm^{-2} s^{-1} keV^{-1}") ;
    h_EgammaShield2_norm->GetYaxis()->SetTitle("Flux [#gamma cm^{-2} s^{-1} keV^{-1}")      ; 
    h_EgammaShield2_full_norm->GetYaxis()->SetTitle("Flux [#gamma cm^{-2} s^{-1} keV^{-1}") ; 
    h_EgammaShield3_norm->GetYaxis()->SetTitle("Flux [#gamma cm^{-2} s^{-1} keV^{-1}")      ;
    h_EgammaShield3_full_norm->GetYaxis()->SetTitle("Flux [#gamma cm^{-2} s^{-1} keV^{-1}") ; 
    h_EgammaAirBox_norm->GetYaxis()->SetTitle("Flux [#gamma cm^{-2} s^{-1} keV^{-1}")       ;
    h_EgammaAirBox_full_norm->GetYaxis()->SetTitle("Flux [#gamma cm^{-2} s^{-1} keV^{-1}")  ;

    //cout << "Gamma Flux entering Shield0 " << h_EgammaShield0_full_norm->Integral()*binwidth_full << " cm^-2 s^-1" << endl;
    //cout << "Gamma Flux entering Shield1 " << h_EgammaShield1_full_norm->Integral()*binwidth_full << " cm^-2 s^-1" << endl;
    //cout << "Gamma Flux entering Shield2 " << h_EgammaShield2_full_norm->Integral()*binwidth_full << " cm^-2 s^-1" << endl;
    //cout << "Gamma Flux entering Shield3 " << h_EgammaShield3_full_norm->Integral()*binwidth_full << " cm^-2 s^-1" << endl;
    //cout << "Gamma Flux entering AirBox " <<  h_EgammaAirBox_full_norm->Integral() *binwidth_full << " cm^-2 s^-1" << endl;
    cout << "Flux of primary particles entering Shield0 " << _total_flux_events_flu0*norm_flu0/surface_Shield0/1.e4 << " cm^-2 s^-1" << endl;
    cout << "Gamma Flux entering Shield1 " << _total_flux_events_gammaflu1*norm_flu0/surface_Shield1/1.e4<< " cm^-2 s^-1" << endl;
    cout << "Gamma Flux entering Shield2 " << _total_flux_events_gammaflu2*norm_flu0/surface_Shield2/1.e4<< " cm^-2 s^-1" << endl;
    cout << "Gamma Flux entering Shield3 " << _total_flux_events_gammaflu3*norm_flu0/surface_Shield3/1.e4<< " cm^-2 s^-1" << endl;
    cout << "Gamma Flux entering AirBox " <<  _total_flux_events_gammaflu_airbox*norm_flu0/surface_AirBox/1.e4 << " cm^-2 s^-1" << endl;
   

    //normalize variable binning histograms
    //normalized to cts/cm^2/sec
    h_EneutronShield0_norm->Scale(norm_flu0/surface_Shield0/1.e4); 
    h_EneutronShield0_full_norm->Scale(norm_flu0/surface_Shield0/1.e4);
    h_EneutronShield1_norm->Scale(norm_flu0/surface_Shield1/1.e4); 
    h_EneutronShield1_full_norm->Scale(norm_flu0/surface_Shield1/1.e4);
    h_EneutronShield2_norm->Scale(norm_flu0/surface_Shield2/1.e4); 
    h_EneutronShield2_full_norm->Scale(norm_flu0/surface_Shield2/1.e4);
    h_EneutronShield3_norm->Scale(norm_flu0/surface_Shield3/1.e4); 
    h_EneutronShield3_full_norm->Scale(norm_flu0/surface_Shield3/1.e4);
    h_EneutronAirBox_norm->Scale(norm_flu0/surface_AirBox/1.e4); 
    h_EneutronAirBox_full_norm->Scale(norm_flu0/surface_AirBox/1.e4);
    //normalized to cts/cm^2/sec/keV
    h_EneutronShield0_norm->GetYaxis()->SetTitle("Flux [n cm^{-2} s^{-1}")       ;
    h_EneutronShield0_full_norm->GetYaxis()->SetTitle("Flux [n cm^{-2} s^{-1}")  ;
    h_EneutronShield1_norm->GetYaxis()->SetTitle("Flux [n cm^{-2} s^{-1}")       ;
    h_EneutronShield1_full_norm->GetYaxis()->SetTitle("Flux [n cm^{-2} s^{-1}")  ;
    h_EneutronShield2_norm->GetYaxis()->SetTitle("Flux [n cm^{-2} s^{-1}")       ;
    h_EneutronShield2_full_norm->GetYaxis()->SetTitle("Flux [n cm^{-2} s^{-1}")  ;
    h_EneutronShield3_norm->GetYaxis()->SetTitle("Flux [n cm^{-2} s^{-1}")       ;
    h_EneutronShield3_full_norm->GetYaxis()->SetTitle("Flux [n cm^{-2} s^{-1}")  ;
    h_EneutronAirBox_norm->GetYaxis()->SetTitle("Flux [n cm^{-2} s^{-1}")        ;
    h_EneutronAirBox_full_norm->GetYaxis()->SetTitle("Flux [n cm^{-2} s^{-1}")   ;

    //cout << "Neutron Flux entering Shield0 " << h_EneutronShield0_full_norm->Integral() << " cm^-2 s^-1" << endl;
    //cout << "Neutron Flux entering Shield1 " << h_EneutronShield1_full_norm->Integral() << " cm^-2 s^-1" << endl;
    //cout << "Neutron Flux entering Shield2 " << h_EneutronShield2_full_norm->Integral() << " cm^-2 s^-1" << endl;
    //cout << "Neutron Flux entering Shield3 " << h_EneutronShield3_full_norm->Integral() << " cm^-2 s^-1" << endl;
    //cout << "Neutron Flux entering AirBox " <<  h_EneutronAirBox_full_norm->Integral()  << " cm^-2 s^-1" << endl;
    
    //cout << "Neutron Flux entering Shield0 " << _total_flux_events_neutronflu0 << " cm^-2 s^-1" << endl;
    cout << "Neutron Flux entering Shield1 " << norm_flu0*_total_flux_events_neutronflu1/surface_Shield1/1.e4 << " cm^-2 s^-1" << endl;
    cout << "Neutron Flux entering Shield2 " << norm_flu0*_total_flux_events_neutronflu2/surface_Shield2/1.e4 << " cm^-2 s^-1" << endl;
    cout << "Neutron Flux entering Shield3 " << norm_flu0*_total_flux_events_neutronflu3/surface_Shield3/1.e4 << " cm^-2 s^-1" << endl;
    cout << "Neutron Flux entering AirBox " <<  norm_flu0*_total_flux_events_neutronflu_airbox/surface_AirBox/1.e4  << " cm^-2 s^-1" << endl;
  
}


void CYGNOAnalysis::ComputeBKG(){

    Double_t binmin,binmax,binmax_kmm;
    Double_t int_counts;

    Double_t interval;
    
    //total recoils
    binmin = h_edepDet->FindBin(0.);
    binmax = h_edepDet->FindBin(20.)-1;
    
    int_counts = h_edepDet->Integral(binmin,binmax);
    _bkg_cpd_kg = int_counts*_norm*h_edepDet->GetBinWidth(1);
    _bkg_cpd_kg_err = sqrt(int_counts)*_norm*h_edepDet->GetBinWidth(1);
    
    interval = (h_edepDet->GetXaxis()->GetBinUpEdge(binmax))  - h_edepDet->GetBinLowEdge(binmin);
    _bkg_cpd_kg_kev = _bkg_cpd_kg/interval;
    _bkg_cpd_kg_kev_err = _bkg_cpd_kg_err/interval;
    
    cout <<"Number of events in [0-20] keV : " <<  _bkg_cpd_kg_kev << " +/- " << _bkg_cpd_kg_kev_err  << " cpd/kg/keV" << endl;
    cout <<"Number of events in [0-20] keV : " <<  _bkg_cpd_kg*_CYGNO_gas_mass*365 << " +/- " << _bkg_cpd_kg_err*_CYGNO_gas_mass*365  << " evts/yr" << endl;
    binmin = h_edepDet->FindBin(1.);
    int_counts = h_edepDet->Integral(binmin,binmax);
    _bkg_cpd_kg = int_counts*_norm*h_edepDet->GetBinWidth(1);
    _bkg_cpd_kg_err = sqrt(int_counts)*_norm*h_edepDet->GetBinWidth(1);
    
    interval = (h_edepDet->GetXaxis()->GetBinUpEdge(binmax))  - h_edepDet->GetBinLowEdge(binmin);
    _bkg_cpd_kg_kev = _bkg_cpd_kg/interval;
    _bkg_cpd_kg_kev_err = _bkg_cpd_kg_err/interval;

    cout <<"Number of events in [1-20] keV : " <<  _bkg_cpd_kg_kev << " +/- " << _bkg_cpd_kg_kev_err  << " cpd/kg/keV" << endl;
    cout <<"Number of events in [1-20] keV : " <<  _bkg_cpd_kg*_CYGNO_gas_mass*365 << " +/- " << _bkg_cpd_kg_err*_CYGNO_gas_mass*365  << " evts/yr" << endl;
   

    //nuclear recoils
    binmin = h_edepDet_NR->FindBin(0.);
    binmax = h_edepDet_NR->FindBin(20.)-1;
    
    int_counts = h_edepDet_NR->Integral(binmin,binmax);
    _bkg_cpd_kg_NR = int_counts*_norm*h_edepDet_NR->GetBinWidth(1);
    _bkg_cpd_kg_NR_err = sqrt(int_counts)*_norm*h_edepDet_NR->GetBinWidth(1);
    
    interval = (h_edepDet_NR->GetXaxis()->GetBinUpEdge(binmax))  - h_edepDet_NR->GetBinLowEdge(binmin);
    _bkg_cpd_kg_kev_NR = _bkg_cpd_kg_NR/interval;
    _bkg_cpd_kg_kev_NR_err = _bkg_cpd_kg_NR_err/interval;
    
    cout <<"Number of NR in [0-20] keV : " <<  _bkg_cpd_kg_kev_NR << " +/- " << _bkg_cpd_kg_kev_NR_err  << " cpd/kg/keV" << endl;
    cout <<"Number of NR in [0-20] keV : " <<  _bkg_cpd_kg_NR*_CYGNO_gas_mass*365 << " +/- " << _bkg_cpd_kg_NR_err*_CYGNO_gas_mass*365  << " evts/yr" << endl;
    binmin = h_edepDet_NR->FindBin(1.);
    int_counts = h_edepDet_NR->Integral(binmin,binmax);
    _bkg_cpd_kg_NR = int_counts*_norm*h_edepDet_NR->GetBinWidth(1);
    _bkg_cpd_kg_NR_err = sqrt(int_counts)*_norm*h_edepDet_NR->GetBinWidth(1);
    
    interval = (h_edepDet_NR->GetXaxis()->GetBinUpEdge(binmax))  - h_edepDet_NR->GetBinLowEdge(binmin);
    _bkg_cpd_kg_kev_NR = _bkg_cpd_kg_NR/interval;
    _bkg_cpd_kg_kev_NR_err = _bkg_cpd_kg_NR_err/interval;
    
    cout <<"Number of NR in [1-20] keV : " <<  _bkg_cpd_kg_kev_NR << " +/- " << _bkg_cpd_kg_kev_NR_err  << " cpd/kg/keV" << endl;
    cout <<"Number of NR in [1-20] keV : " <<  _bkg_cpd_kg_NR*_CYGNO_gas_mass*365 << " +/- " << _bkg_cpd_kg_NR_err*_CYGNO_gas_mass*365  << " evts/yr" << endl;
    
}
