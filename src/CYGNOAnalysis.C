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

    h_edepDet = new TH1D("h_edepDet","edepDet",600,0,120);
    h_edepDet_norm = new TH1D("h_edepDet_norm","edepDet-norm",600,0,120);
    h_edepDet_full = new TH1D("h_edepDet_full","edepDet-full",600,0,3000);
    h_edepDet_full_norm = new TH1D("h_edepDet_full_norm","edepDet-full-norm",600,0,3000);

    h_EprimaryShield0 = new TH1D("h_EprimaryShield0","",600,0,120);
    h_EprimaryShield0_norm = new TH1D("h_EprimaryShield0_norm","",600,0,120);
    h_EprimaryShield0_full = new TH1D("h_EprimaryShield0_full","",600,0,3000);
    h_EprimaryShield0_full_norm = new TH1D("h_EprimaryShield0_full_norm","",600,0,3000);

    h_EprimaryShield1 = new TH1D("h_EprimaryShield1","",600,0,120);
    h_EprimaryShield1_norm = new TH1D("h_EprimaryShield1_norm","",600,0,120);
    h_EprimaryShield1_full = new TH1D("h_EprimaryShield1_full","",600,0,3000);
    h_EprimaryShield1_full_norm = new TH1D("h_EprimaryShield1_full_norm","",600,0,3000);

    h_EprimaryShield2 = new TH1D("h_EprimaryShield2","",600,0,120);
    h_EprimaryShield2_norm = new TH1D("h_EprimaryShield2_norm","",600,0,120);
    h_EprimaryShield2_full = new TH1D("h_EprimaryShield2_full","",600,0,3000);
    h_EprimaryShield2_full_norm = new TH1D("h_EprimaryShield2_full_norm","",600,0,3000);

    h_EprimaryShield3 = new TH1D("h_EprimaryShield3","",600,0,120);
    h_EprimaryShield3_norm = new TH1D("h_EprimaryShield3_norm","",600,0,120);
    h_EprimaryShield3_full = new TH1D("h_EprimaryShield3_full","",600,0,3000);
    h_EprimaryShield3_full_norm = new TH1D("h_EprimaryShield3_full_norm","",600,0,3000);

    h_EprimaryAirBox = new TH1D("h_EprimaryAirBox","",600,0,120);
    h_EprimaryAirBox_norm = new TH1D("h_EprimaryAirBox_norm","",600,0,120);
    h_EprimaryAirBox_full = new TH1D("h_EprimaryAirBox_full","",600,0,3000);
    h_EprimaryAirBox_full_norm = new TH1D("h_EprimaryAirBox_full_norm","",600,0,3000);

    h_EallAirBox = new TH1D("h_EallAirBox","",600,0,120);
    h_EallAirBox_norm = new TH1D("h_EallAirBox_norm","",600,0,120);
    h_EallAirBox_full = new TH1D("h_EallAirBox_full","",600,0,3000);
    h_EallAirBox_full_norm = new TH1D("h_EallAirBox_full_norm","",600,0,3000);

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
    h3_xyz_pos = new TH3D("h3_xyx_pos","",100,-600,600,100,-600,600,600,-600,600);
    h3_xyz_pro = new TH3D("h3_xyx_pro","",100,-600,600,100,-600,600,600,-600,600);


    h_edepDet->Sumw2();
    h_edepDet_norm->Sumw2();
    h_edepDet_full->Sumw2();
    h_edepDet_full_norm->Sumw2();

    h_EprimaryShield0->Sumw2();
    h_EprimaryShield0_norm->Sumw2(); 
    h_EprimaryShield0_full->Sumw2();    
    h_EprimaryShield0_full_norm->Sumw2();

    h_EprimaryShield1->Sumw2();
    h_EprimaryShield1_norm->Sumw2(); 
    h_EprimaryShield1_full->Sumw2();    
    h_EprimaryShield1_full_norm->Sumw2();
    
    h_EprimaryShield2->Sumw2();
    h_EprimaryShield2_norm->Sumw2(); 
    h_EprimaryShield2_full->Sumw2();    
    h_EprimaryShield2_full_norm->Sumw2();

    h_EprimaryShield3->Sumw2();
    h_EprimaryShield3_norm->Sumw2(); 
    h_EprimaryShield3_full->Sumw2();    
    h_EprimaryShield3_full_norm->Sumw2();

    h_EprimaryAirBox->Sumw2();
    h_EprimaryAirBox_norm->Sumw2();
    h_EprimaryAirBox_full->Sumw2();
    h_EprimaryAirBox_full_norm->Sumw2();

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
    _total_events = 0;
    
    Long64_t nentries;
   
    cout<< "Setting histograms" << endl;  
    this->SetHistograms();
    //this->SetTree();
    
    list<string>::iterator my_file_iter;
    
    for(my_file_iter = _file_to_be_open.begin(); my_file_iter != _file_to_be_open.end(); ++my_file_iter){
        //loop on files
        TFile * fopen = new TFile(my_file_iter->c_str());
        TTree * mytree = new TTree();
        TH1D *n_event_gen;
        
	//	if ((fopen->IsOpen()==false) ||  (fopen->GetListOfKeys()->Contains("nT")==false)) continue; 
 	if ((fopen->GetListOfKeys()->Contains("nTuple")==false)) continue; 

        n_event_gen = (TH1D*) fopen->Get("histo/NTot");

	 events = n_event_gen->GetBinContent(1);
        _total_events += events;
    
        mytree = (TTree*) fopen->Get("nTuple");
        this->Init(mytree);
        
        nentries = mytree->GetEntriesFast();
        cout<<"Found file "<<*my_file_iter<<" Entries = "<<mytree->GetEntries()<<"  Events = "<<events<<" Total = "<<_total_events<<endl;
        
        for (Long64_t jentry=0; jentry<nentries;jentry++) { //loop on entries
            
            if(jentry %1000000 == 0){cout<<"Event N. "<<jentry<<endl;}
            
            //nb = mytree->GetEntry(jentry);  //load the full entry of the tree (slow)
            
            //load only some branches ( faster !)
            b_energyDep->GetEntry(jentry);
            b_E_flu->GetEntry(jentry);
            if (E_flu->size()==0)
		continue;

            b_trackid_flu->GetEntry(jentry);
            b_volNo_flu->GetEntry(jentry);
            //b_prestepVolNo_flu->GetEntry(jentry);
            //b_pdg_flu->GetEntry(jentry);
            //b_poststepx_flu->GetEntry(jentry);
            //b_poststepy_flu->GetEntry(jentry);
            //b_poststepz_flu->GetEntry(jentry);
            //b_px_flu->GetEntry(jentry);
            //b_py_flu->GetEntry(jentry);
            //b_pz_flu->GetEntry(jentry);
            //b_E_ele->GetEntry(jentry);
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
            
            if(_smearing == true){
                this->Smearing();
            }
          
    
	    //All
	    for (int iflu=0; iflu < E_flu->size(); iflu++){ 

        	    if(volNo_flu->at(iflu)==3 && trackid_flu->at(iflu)==1){
                        h_EprimaryShield0->Fill(E_flu->at(iflu));
                        h_EprimaryShield0_norm->Fill(E_flu->at(iflu)); 
                        h_EprimaryShield0_full->Fill(E_flu->at(iflu));    
                        h_EprimaryShield0_full_norm->Fill(E_flu->at(iflu));
			//cout << "E_flu " << E_flu->at(iflu) << "  trackid_flu " << trackid_flu->at(iflu) << endl;
                    }
        	    if(volNo_flu->at(iflu)==4 && trackid_flu->at(iflu)==1){
                        h_EprimaryShield1->Fill(E_flu->at(iflu));
                        h_EprimaryShield1_norm->Fill(E_flu->at(iflu)); 
                        h_EprimaryShield1_full->Fill(E_flu->at(iflu));    
                        h_EprimaryShield1_full_norm->Fill(E_flu->at(iflu));
                    }
                        
        	    if(volNo_flu->at(iflu)==5 && trackid_flu->at(iflu)==1){
                        h_EprimaryShield2->Fill(E_flu->at(iflu));
                        h_EprimaryShield2_norm->Fill(E_flu->at(iflu)); 
                        h_EprimaryShield2_full->Fill(E_flu->at(iflu));    
                        h_EprimaryShield2_full_norm->Fill(E_flu->at(iflu));
                    }
        
        	    if(volNo_flu->at(iflu)==6 && trackid_flu->at(iflu)==1){
                        h_EprimaryShield3->Fill(E_flu->at(iflu));
                        h_EprimaryShield3_norm->Fill(E_flu->at(iflu)); 
                        h_EprimaryShield3_full->Fill(E_flu->at(iflu));    
                        h_EprimaryShield3_full_norm->Fill(E_flu->at(iflu));
                    }
        
        	    if(volNo_flu->at(iflu)==7 && trackid_flu->at(iflu)==1){
                        h_EprimaryAirBox->Fill(E_flu->at(iflu));
                        h_EprimaryAirBox_norm->Fill(E_flu->at(iflu));
                        h_EprimaryAirBox_full->Fill(E_flu->at(iflu));
                        h_EprimaryAirBox_full_norm->Fill(E_flu->at(iflu));
                    }
        
        	    if(volNo_flu->at(iflu)==7){
                        h_EallAirBox->Fill(E_flu->at(iflu));
                        h_EallAirBox_norm->Fill(E_flu->at(iflu));
                        h_EallAirBox_full->Fill(E_flu->at(iflu));
                        h_EallAirBox_full_norm->Fill(E_flu->at(iflu));
                    }
        
              }

             //FIXME : double counting due to non-primary electrons 
             for (int iele = 0; iele < E_ele->size(); iele++){
	             h3_xyz_ele->Fill(poststepx_ele->at(iele),poststepy_ele->at(iele),poststepz_ele->at(iele));	
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


              if(energyDep >0.){
                  h_edepDet->Fill(energyDep);
                  h_edepDet_norm->Fill(energyDep);
                  h_edepDet_full->Fill(energyDep);
                  h_edepDet_full_norm->Fill(energyDep);
                  //cout << "energy deposit = " << energyDep <<  endl;
             }	    
	} //end loop on entries
        
        if (_externalflux){
            _total_flux_events += h_EprimaryShield0->GetEntries();
        }    

	delete mytree;
        delete fopen;
        //delete n_event_gen;
    } //end loop on files
    

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
  
    Double_t AirBox_x = 1.45;
    Double_t AirBox_y = 1.45;
    Double_t AirBox_z = 2.45; //here x and z swiped wrt CYGNODetectorConstruction 
    //Double_t AirBox_x = 2;
    //Double_t AirBox_y = 2;
    //Double_t AirBox_z = 3; //here x and z swiped wrt CYGNODetectorConstruction 
     
    Double_t ndays;
    if (!_externalflux){
      Double_t ndec1d = _activity*86400*_mass;
      ndays = _total_events/ndec1d;
    }
    else{
      Double_t nflu_1d = _externalflux_value * (2*(AirBox_x+2*_tot_shield_thickness)*(2+AirBox_y*_tot_shield_thickness) + 4*(AirBox_y+2*_tot_shield_thickness)*(AirBox_z+2*_tot_shield_thickness)) * 10000. * 86400.;
      ndays = _total_flux_events/ nflu_1d;
    } 
    binwitdh = h_edepDet_norm->GetBinWidth(1);
    norm = 1./(ndays*binwitdh*_CYGNO_gas_mass);
    h_edepDet_norm->Scale(norm);
    //normalized to cpd/kg/keV

    binwitdh_full = h_edepDet_full_norm->GetBinWidth(1);
    normfull = 1./(ndays*binwitdh_full*_CYGNO_gas_mass);
    h_edepDet_full_norm->Scale(normfull);
    //normalized to cpd/kg/keV

    cout << "norm = " << norm << "   normfull = " << normfull  << "   binwidth = " << binwitdh << " CYGNO_gas_mass = " << _CYGNO_gas_mass << "  ndays = " <<ndays << endl;
     
    _norm  = norm;
    _normfull  = normfull;

    norm_flu0 = _externalflux_value * 10000. * (2*(AirBox_x+2*_tot_shield_thickness)*(AirBox_y+2*_tot_shield_thickness) + 4*(AirBox_y+2*_tot_shield_thickness)*(AirBox_z+2*_tot_shield_thickness)) / h_EprimaryShield0->GetEntries();  
    h_EprimaryShield0_norm->Scale(norm_flu0); 
    h_EprimaryShield0_full_norm->Scale(norm_flu0);
    //normalized to cts/sec

    //norm_flu1 = (_externalflux_value * 10000. * (2*(AirBox_x+2*(_shield3_thickness+_shield2_thickness+_shield1_thickness))*(AirBox_y+2*(_shield3_thickness+_shield2_thickness+_shield1_thickness)) + 4*(AirBox_y+2*(_shield3_thickness+_shield2_thickness+_shield1_thickness))*(AirBox_z+2*(_shield3_thickness+_shield2_thickness+_shield1_thickness)))) / h_EprimaryShield0->GetEntries();  
    //h_EprimaryShield1_norm->Scale(norm_flu1); 
    //h_EprimaryShield1_full_norm->Scale(norm_flu1);
    ////normalized to cts/sec

    //norm_flu2 = (_externalflux_value * 10000. * (2*(AirBox_x+2*(_shield3_thickness+_shield2_thickness))*(AirBox_y+2*(_shield3_thickness+_shield2_thickness)) + 4*(AirBox_y+2*(_shield3_thickness+_shield2_thickness))*(AirBox_z+2*(_shield3_thickness+_shield2_thickness)))) / h_EprimaryShield0->GetEntries();  
    //h_EprimaryShield2_norm->Scale(norm_flu2); 
    //h_EprimaryShield2_full_norm->Scale(norm_flu2);
    ////normalized to cts/sec

    //norm_flu3 = (_externalflux_value * 10000. * (2*(2+2*_shield3_thickness)*(2+2*_shield3_thickness) + 4*(2+2*_shield3_thickness)*(3+2*_shield3_thickness))) / h_EprimaryShield0->GetEntries();  
    //h_EprimaryShield3_norm->Scale(norm_flu3); 
    //h_EprimaryShield3_full_norm->Scale(norm_flu3);
    ////normalized to cts/sec

    //norm_flu_airbox = (_externalflux_value * 10000. * (2*2*2 + 4*2*3)) / h_EprimaryShield0->GetEntries();  
    //h_EprimaryAirBox_norm->Scale(norm_flu_airbox);
    //h_EprimaryAirBox_full_norm->Scale(norm_flu_airbox);
    //h_EallAirBox_norm->Scale(norm);
    //h_EallAirBox_full_norm->Scale(normfull);
    ////normalized to cts/sec

    h_EprimaryShield1_norm->Scale(norm_flu0); 
    h_EprimaryShield1_full_norm->Scale(norm_flu0);
    h_EprimaryShield2_norm->Scale(norm_flu0); 
    h_EprimaryShield2_full_norm->Scale(norm_flu0);
    h_EprimaryShield3_norm->Scale(norm_flu0); 
    h_EprimaryShield3_full_norm->Scale(norm_flu0);
    h_EprimaryAirBox_norm->Scale(norm_flu0); 
    h_EprimaryAirBox_full_norm->Scale(norm_flu0);

   
}


void CYGNOAnalysis::ComputeBKG(){

    Double_t binmin,binmax,binmax_kmm;
    Double_t int_counts;

    Double_t interval;
    
    binmin = h_edepDet->FindBin(0.);
    binmax = h_edepDet->FindBin(20.)-1;
    
    int_counts = h_edepDet->Integral(binmin,binmax);
    _bkg_cpd_kg = int_counts*_norm*h_edepDet->GetBinWidth(1);
    _bkg_cpd_kg_err = sqrt(int_counts)*_norm*h_edepDet->GetBinWidth(1);
    
    interval = (h_edepDet->GetXaxis()->GetBinUpEdge(binmax))  - h_edepDet->GetBinLowEdge(binmin);
    _bkg_cpd_kg_kev = _bkg_cpd_kg/interval;
    _bkg_cpd_kg_kev_err = _bkg_cpd_kg_err/interval;
    
}
