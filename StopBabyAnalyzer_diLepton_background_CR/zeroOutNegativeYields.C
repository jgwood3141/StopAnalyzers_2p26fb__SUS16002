#include "TROOT.h"
#include "Riostream.h"
#include "TFile.h"
#include "TCollection.h"
#include "TKey.h"
#include "TClass.h"
#include "TH1.h"
#include "TH2.h"
#include "TString.h"

#include "histoHelper.h"

int zeroOutNegativeYields(TString f_in_name){


  TString nonZeroExt = "_noNegYield.root";

  if(f_in_name.Contains(nonZeroExt) ) return 0;

  histoHelper histos;
  TString incl_name = "";
  //TString ee0lep_name = "";
  TString ee1lep_name = "";
  TString ge2lep_name = "";
  TString ZtoNuNu_name = "";
  for(int iClassy=0; iClassy<(int)histos.classifications.size(); iClassy++){
    if( histos.classifications[iClassy]->id == k_incl ){
      incl_name = histos.classifications[iClassy]->label;
    }
    //if( histos.classifications[iClassy]->id == k_ee0lep ){
      //ee0lep_name = histos.classifications[iClassy]->label;
    //}
    if( histos.classifications[iClassy]->id == k_ee1lep ){
      ee1lep_name = histos.classifications[iClassy]->label;
    }
    if( histos.classifications[iClassy]->id == k_ge2lep ){
      ge2lep_name = histos.classifications[iClassy]->label;
    }
    if( histos.classifications[iClassy]->id == k_ZtoNuNu ){
      ZtoNuNu_name = histos.classifications[iClassy]->label;
    }
  
  }  

  TString f_out_name = f_in_name;
  f_out_name.ReplaceAll(".root", nonZeroExt);

  TFile *f_in = new TFile(f_in_name, "read");

  TFile *f_out = new TFile(f_out_name, "recreate");

  TIter nextIter(f_in->GetListOfKeys());
  TKey *key;
  int nHists=0;
  int nZeros=0;
  while ((key = (TKey*)nextIter())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    
    if(cl->InheritsFrom("TH1D")){
      nHists++;
      TH1D *h = (TH1D*)key->ReadObj();
      TH1D *h_clone = (TH1D*)h->Clone();
      h_clone->SetDirectory(f_out);
      if(h_clone->Integral(0,-1)<0.0){
	h_clone->Reset();
	nZeros++;
      }
    }
    if(cl->InheritsFrom("TH2D")){
      nHists++;
      TH2D *h = (TH2D*)key->ReadObj();
      TH2D *h_clone = (TH2D*)h->Clone();
      h_clone->SetDirectory(f_out);
      if(h_clone->Integral(0,-1)<0.0){
	h_clone->Reset();
	nZeros++;
      }
    }

  }


  f_out->Write();
  f_out->Close();
  f_in->Close();

  cout << "  Out of " << nHists << " histos tested, " << nZeros << " histos with negative yield were found and set to zero " << endl;
  cout << "  Output written to: " << f_out_name << endl;


  if( nZeros == 0 ) return 0;

  
  // Re-sum inclusive histos
  f_out = new TFile(f_out_name, "update");

  TIter nextIter2(f_out->GetListOfKeys());
  TKey *key2;
  while ((key2 = (TKey*)nextIter2())) {
    TClass *cl = gROOT->GetClass(key2->GetClassName());
      
    if(cl->InheritsFrom("TH1D")){

      TH1D *h_incl = (TH1D*)key2->ReadObj();
      TString h_name = h_incl->GetName();
      
      if( !h_name.Contains(incl_name) ) continue;
	
      //TString h_name_ee0lep = h_name;
      //h_name_ee0lep.ReplaceAll(incl_name, ee0lep_name);
      //TH1D *h_ee0lep = (TH1D*)f_out->Get(h_name_ee0lep);
	
	
      TString h_name_ee1lep = h_name;
      h_name_ee1lep.ReplaceAll(incl_name, ee1lep_name);
      TH1D *h_ee1lep = (TH1D*)f_out->Get(h_name_ee1lep);
	
	
      TString h_name_ge2lep = h_name;
      h_name_ge2lep.ReplaceAll(incl_name, ge2lep_name);
      TH1D *h_ge2lep = (TH1D*)f_out->Get(h_name_ge2lep);
      
	
      TString h_name_ZtoNuNu = h_name;
      h_name_ZtoNuNu.ReplaceAll(incl_name, ZtoNuNu_name);
      TH1D *h_ZtoNuNu = (TH1D*)f_out->Get(h_name_ZtoNuNu);
	
	
      h_incl->Reset();
      h_incl->SetDirectory(f_out);

      //h_incl->Add(h_ee0lep);
      h_incl->Add(h_ee1lep);
      h_incl->Add(h_ge2lep);
      h_incl->Add(h_ZtoNuNu);
	
    }
    if(cl->InheritsFrom("TH2D")){
	
      TH2D *h_incl = (TH2D*)key2->ReadObj();
      TString h_name = h_incl->GetName();
	
      if( !h_name.Contains(incl_name) ) continue;
	
      //TString h_name_ee0lep = h_name;
      //h_name_ee0lep.ReplaceAll(incl_name, ee0lep_name);
      //TH2D *h_ee0lep = (TH2D*)f_out->Get(h_name_ee0lep);
	
	
      TString h_name_ee1lep = h_name;
      h_name_ee1lep.ReplaceAll(incl_name, ee1lep_name);
      TH2D *h_ee1lep = (TH2D*)f_out->Get(h_name_ee1lep);
	
	
      TString h_name_ge2lep = h_name;
      h_name_ge2lep.ReplaceAll(incl_name, ge2lep_name);
      TH2D *h_ge2lep = (TH2D*)f_out->Get(h_name_ge2lep);
	
	
      TString h_name_ZtoNuNu = h_name;
      h_name_ZtoNuNu.ReplaceAll(incl_name, ZtoNuNu_name);
      TH2D *h_ZtoNuNu = (TH2D*)f_out->Get(h_name_ZtoNuNu);
	
      
      h_incl->Reset();
      h_incl->SetDirectory(f_out);

      //h_incl->Add(h_ee0lep);
      h_incl->Add(h_ee1lep);
      h_incl->Add(h_ge2lep);
      h_incl->Add(h_ZtoNuNu);
	
    }

  }
  
   
      
      
  f_out->Write();
  f_out->Close();
  
  return 0;
}
