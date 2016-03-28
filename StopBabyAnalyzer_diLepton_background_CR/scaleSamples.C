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

int scaleThis(TString f_in_name, double SF);


void scaleSamples(){

  TString inDir = "";

  inDir = "Histos/Nominal/";
  scaleThis( inDir+"histos__WJetsToLNu_HT100To200_madgraph_pythia8_25ns.root", 1.041 );
  scaleThis( inDir+"histos__WJetsToLNu_HT200To400_madgraph_pythia8_25ns.root", 0.9321 );
  scaleThis( inDir+"histos__WJetsToLNu_HT400To600_madgraph_pythia8_25ns.root", 1.0384 );
  scaleThis( inDir+"histos__WJetsToLNu_HT600ToInf_madgraph_pythia8_25ns.root", 0.9532 );


  inDir = "Histos/JESup/";
  scaleThis( inDir+"histos__WJetsToLNu_HT100To200_madgraph_pythia8_25ns.root", 1.041 );
  scaleThis( inDir+"histos__WJetsToLNu_HT200To400_madgraph_pythia8_25ns.root", 0.9321 );
  scaleThis( inDir+"histos__WJetsToLNu_HT400To600_madgraph_pythia8_25ns.root", 1.0384 );
  scaleThis( inDir+"histos__WJetsToLNu_HT600ToInf_madgraph_pythia8_25ns.root", 0.9532 );


  inDir = "Histos/JESdown/";
  scaleThis( inDir+"histos__WJetsToLNu_HT100To200_madgraph_pythia8_25ns.root", 1.041 );
  scaleThis( inDir+"histos__WJetsToLNu_HT200To400_madgraph_pythia8_25ns.root", 0.9321 );
  scaleThis( inDir+"histos__WJetsToLNu_HT400To600_madgraph_pythia8_25ns.root", 1.0384 );
  scaleThis( inDir+"histos__WJetsToLNu_HT600ToInf_madgraph_pythia8_25ns.root", 0.9532 );
  

  return;
}



int scaleThis(TString f_in_name, double SF){

 
  cout << "Rescaling histo file: " << f_in_name << endl;
  
  TFile *f_in = new TFile(f_in_name, "read");

  TString scaleExt = "_reScaled.root";
  TString f_out_name = f_in_name;
  f_out_name.ReplaceAll(".root", scaleExt);
  
  TFile *f_out = new TFile(f_out_name, "recreate");

  cout << "Output will be writtien to: " << f_out_name << endl;
 
  TIter nextIter(f_in->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)nextIter())) {
  
    TClass *cl = gROOT->GetClass(key->GetClassName());
   
    if(cl->InheritsFrom("TH1D")){      
      TH1D *h = (TH1D*)key->ReadObj();
      TH1D *h_clone = (TH1D*)h->Clone();
      h_clone->SetDirectory(f_out);
      h_clone->Scale(SF);
    }

    if(cl->InheritsFrom("TH2D")){
      TH2D *h = (TH2D*)key->ReadObj();
      TH2D *h_clone = (TH2D*)h->Clone();
      h_clone->SetDirectory(f_out);
      h_clone->Scale(SF);
    }

  }

  f_in->Close();
  f_out->Write();
  f_out->Close();
    
  return 0;
}
