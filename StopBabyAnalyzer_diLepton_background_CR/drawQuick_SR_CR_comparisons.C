#include "Riostream.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TLine.h"
#include "TString.h"

#include <vector>

void drawOverlay( std::vector<TH1D*> allHists, vector<TString> histLabels, TString title, TString saveMe, bool unitNorm=false, int rebin=1){

  const int nHists = (int)allHists.size();

  TCanvas *can = new TCanvas("can","can", 10, 10, 800, 1000);

  TPad *pad1 = new TPad("pad1", "pad1", 0.00, 0.20, 1.00, 1.00);
  TPad *pad2 = new TPad("pad2", "pad2", 0.00, 0.00, 1.00, 0.19);
  pad1->Draw();
  pad2->Draw();

  pad1->cd();
  
  TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);

  // find max
  double max=0.0;
  for(int iHist=0; iHist<nHists; iHist++){
    if(unitNorm) allHists[iHist]->Scale(1.0/allHists[iHist]->Integral(0,-1));
    allHists[iHist]->Rebin(rebin);
    max = std::max( max, (double)allHists[iHist]->GetBinContent( allHists[iHist]->GetMaximumBin() ) );
    leg->AddEntry(allHists[iHist], histLabels[iHist], "l");
  }
  allHists[0]->SetMaximum(max*1.1);
  allHists[0]->SetMinimum(0.0);
  allHists[0]->SetTitle(title);

  // Draw 
  for(int iHist=0; iHist<nHists; iHist++){
    if(iHist==0) allHists[iHist]->Draw("hist");
    else         allHists[iHist]->Draw("hist same");
  }
  leg->Draw();
  
  pad2->cd();
  
  TLine unity(allHists[0]->GetBinLowEdge(1), 1.0, allHists[0]->GetBinLowEdge(allHists[0]->GetNbinsX()+1), 1.0);
  unity.SetLineWidth(3);
  unity.SetLineColor(kRed);

  TH1D *ratio[nHists];
  
  for(int iHist=0; iHist<nHists; iHist++){
    TString ratio_name = "ratio_";
    ratio_name += Form("%d", iHist);
    ratio[iHist] = (TH1D*)allHists[iHist]->Clone(ratio_name);
    ratio[iHist]->Divide(allHists[0]);
    ratio[iHist]->SetMaximum(2.0);
    ratio[iHist]->SetMinimum(0.0);
    if(nHists>2) ratio[iHist]->SetLineColor( allHists[iHist]->GetLineColor() );
    else ratio[iHist]->SetLineColor(kBlack);
   
    if(iHist==1){
      ratio[iHist]->SetTitle("");
      ratio[iHist]->Draw("e1");
      unity.Draw();
      ratio[iHist]->Draw("e1 same");
    }
    else if(iHist>1) ratio[iHist]->Draw("e1 same");
  }

  can->SaveAs(saveMe);
  can->~TCanvas();

  return;
}



void drawQuick_SR_CR_comparisons(){

  gStyle->SetOptStat(0);

  std::vector<TH1D*> histos;
  std::vector<TString> hLabels;
  
  TFile *f_SR_mc   = new TFile("../StopBabyAnalyzer/Histos/Nominal/histos__allBkg_25ns.root", "read");
  TFile *f_SR_data = new TFile("../StopBabyAnalyzer/Histos/Nominal/histos__data_singleEl_singleMu_2015CD_25ns.root", "read");

  TFile *f_CR_mc   = new TFile("Histos/Nominal/histos__allBkg_25ns.root", "read");
  TFile *f_CR_data = new TFile("Histos/Nominal/histos__data_singleEl_singleMu_2015CD_25ns.root", "read");
  
  //drawOverlay( std::vector<TH1D*> allHists, vector<TString> histLabels, TString title, TString saveMe, bool unitNorm=false, int rebin=1)


  //
  // >=3 jets, MET>=250, MT2W data/mc comparisons
  //
  TH1D *h_CR_mc__ge3j_ge250met__mt2w = (TH1D*)f_CR_mc->Get("h__mt2w__ge2lep__nominal__ge3j_ge250met");
  TH1D *h_CR_data__ge3j_ge250met__mt2w = (TH1D*)f_CR_data->Get("h__mt2w__incl__nominal__ge3j_ge250met");
  

  TH1D *h_SR_mc__ge3j_ge250met_lt200mt2w__mt2w = (TH1D*)f_SR_mc->Get("h__mt2w__ge2lep__nominal__ge3j_ge250met_lt200mt2w");
  TH1D *h_SR_data__ge3j_ge250met_lt200mt2w__mt2w = (TH1D*)f_SR_data->Get("h__mt2w__incl__nominal__ge3j_ge250met_lt200mt2w");
  
  TH1D *h_SR_mc__ge3j_ge250met_ge200mt2w__mt2w = (TH1D*)f_SR_mc->Get("h__mt2w__ge2lep__nominal__ge3j_ge250met_ge200mt2w");
  TH1D *h_SR_data__ge3j_ge250met_ge200mt2w__mt2w = (TH1D*)f_SR_data->Get("h__mt2w__incl__nominal__ge3j_ge250met_ge200mt2w");
  
  
  TH1D *h_SR_mc__ge3j_ge250met__mt2w = (TH1D*)h_SR_mc__ge3j_ge250met_lt200mt2w__mt2w->Clone("h_SR_mc__ge3j_ge250met__mt2w");
  h_SR_mc__ge3j_ge250met__mt2w->Add(h_SR_mc__ge3j_ge250met_ge200mt2w__mt2w);
  
  TH1D *h_SR_data__ge3j_ge250met__mt2w = (TH1D*)h_SR_data__ge3j_ge250met_lt200mt2w__mt2w->Clone("h_SR_data__ge3j_ge250met__mt2w");
  h_SR_data__ge3j_ge250met__mt2w->Add(h_SR_data__ge3j_ge250met_ge200mt2w__mt2w);
  
  
  h_CR_mc__ge3j_ge250met__mt2w->SetLineColor(kRed);
  histos.push_back(h_CR_mc__ge3j_ge250met__mt2w);
  hLabels.push_back("CR 2lep MC, >=3jets MET>=250, MT2W");
  
  histos.push_back(h_SR_mc__ge3j_ge250met__mt2w);
  hLabels.push_back("SR 2lep MC, >=3jets MET>=250, MT2W");
    
  drawOverlay( histos, hLabels, "SR vs CR, 2lep MC, >=3jets MET>=250, MT2W", "sr_vs_cr__mc__ge3j_ge250met__mt2w.pdf", true);
  histos.clear();
  hLabels.clear();
  

  h_CR_data__ge3j_ge250met__mt2w->SetLineColor(kRed);
  histos.push_back(h_CR_data__ge3j_ge250met__mt2w);
  hLabels.push_back("CR DATA, >=3jets MET>=250, MT2W");
  
  histos.push_back(h_SR_data__ge3j_ge250met__mt2w);
  hLabels.push_back("SR DATA, >=3jets MET>=250, MT2W");
    
  drawOverlay( histos, hLabels, "SR vs CR, DATA, >=3jets MET>=250, MT2W", "sr_vs_cr__data__ge3j_ge250met__mt2w.pdf", true);
  histos.clear();
  hLabels.clear();
  

  // Rebin
  int nBins=2;
  double xBins[3]{0.0,200.0,600.0};


  TH1D *h_CR_mc__ge3j_ge250met__mt2w__rebin = (TH1D*)h_CR_mc__ge3j_ge250met__mt2w->Rebin(nBins,"h_CR_mc__ge3j_ge250met__mt2w__rebin",xBins);
  TH1D *h_CR_data__ge3j_ge250met__mt2w__rebin = (TH1D*)h_CR_data__ge3j_ge250met__mt2w->Rebin(nBins,"h_CR_data__ge3j_ge250met__mt2w__rebin",xBins);
  
  TH1D *h_SR_mc__ge3j_ge250met__mt2w__rebin = (TH1D*)h_SR_mc__ge3j_ge250met__mt2w->Rebin(nBins,"h_SR_mc__ge3j_ge250met__mt2w__rebin",xBins);
  TH1D* h_SR_data__ge3j_ge250met__mt2w__rebin = (TH1D*)h_SR_data__ge3j_ge250met__mt2w->Rebin(nBins,"h_SR_data__ge3j_ge250met__mt2w__rebin",xBins);
  


  h_CR_mc__ge3j_ge250met__mt2w__rebin->SetLineColor(kRed);
  histos.push_back(h_CR_mc__ge3j_ge250met__mt2w__rebin);
  hLabels.push_back("CR 2lep MC, >=3jets MET>=250, MT2W");
  
  histos.push_back(h_SR_mc__ge3j_ge250met__mt2w__rebin);
  hLabels.push_back("SR 2lep MC, >=3jets MET>=250, MT2W");
    
  drawOverlay( histos, hLabels, "SR vs CR, 2lep MC, >=3jets MET>=250, MT2W", "sr_vs_cr__mc__ge3j_ge250met__mt2w__rebin.pdf", true);
  histos.clear();
  hLabels.clear();
  

  h_CR_data__ge3j_ge250met__mt2w__rebin->SetLineColor(kRed);
  histos.push_back(h_CR_data__ge3j_ge250met__mt2w__rebin);
  hLabels.push_back("CR DATA, >=3jets MET>=250, MT2W");
  
  histos.push_back(h_SR_data__ge3j_ge250met__mt2w__rebin);
  hLabels.push_back("SR DATA, >=3jets MET>=250, MT2W");
    
  drawOverlay( histos, hLabels, "SR vs CR, DATA, >=3jets MET>=250, MT2W", "sr_vs_cr__data__ge3j_ge250met__mt2w__rebin.pdf", true);
  histos.clear();
  hLabels.clear();
  

  

  return;
}

  
