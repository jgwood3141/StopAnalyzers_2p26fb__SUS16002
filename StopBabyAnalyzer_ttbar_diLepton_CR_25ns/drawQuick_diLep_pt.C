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
#include "THStack.h"

void drawQuick_diLep_pt(){

  gStyle->SetOptStat(0);
  gStyle->SetHistLineWidth(3);


  //
  // Open Data/MC files
  //
  TString inDir = "Histos/Nominal/";

  TFile *f_data = new TFile(inDir+"histos__data_25ns.root", "read");
  TFile *f_all_mc = new TFile(inDir+"histos__allBkg_25ns.root", "read");
  TFile *f_TTV = new TFile(inDir+"histos__TTV_25ns.root", "read");
  TFile *f_wjets = new TFile(inDir+"histos__WJets_25ns.root", "read");
  TFile *f_dyjets = new TFile(inDir+"histos__DYJets_25ns.root", "read");
  TFile *f_singleT = new TFile(inDir+"histos__singleT_25ns.root", "read");
  TFile *f_ttbar = new TFile(inDir+"histos__ttbar_25ns.root", "read");
  

  //
  // Grab Histos
  //
  TString hName = "h__diLep_pt__incl__nominal__ge2j_ge1t_gt0met";
  //TString hName = "h__met__incl__nominal__ge2j_ge1t_gt0met";
  
  TString hName_topPt = hName;
  hName_topPt.ReplaceAll("__nominal__","__topPt_scaleUp__");


  TH1D *h_data = (TH1D*)f_data->Get(hName);
  if(hName.Contains("diLep_pt")) h_data->Rebin(2);

  TH1D *h_all_mc_nom = (TH1D*)f_all_mc->Get(hName);
  if(hName.Contains("diLep_pt")) h_all_mc_nom->Rebin(2);
  h_all_mc_nom->SetLineColor(kRed);
  
  TH1D *h_all_mc_topPtUp = (TH1D*)f_all_mc->Get(hName_topPt);
  if(hName.Contains("diLep_pt")) h_all_mc_topPtUp->Rebin(2);
  h_all_mc_topPtUp->SetLineColor(kGreen);
  
  double SF = h_data->Integral(0,-1)/h_all_mc_nom->Integral(0,-1);
  h_all_mc_nom->Scale(SF);
  h_all_mc_topPtUp->Scale(SF);

  TH1D *h_mc_band = (TH1D*)h_all_mc_nom->Clone(hName+"__mc_error_band");
  for(int iBin=1; iBin<=(int)h_mc_band->GetNbinsX(); iBin++){
    double nom_yield = h_all_mc_nom->GetBinContent(iBin);
    double nom_error = h_all_mc_nom->GetBinError(iBin);
    double topPtUp_yield = h_all_mc_topPtUp->GetBinContent(iBin);
    double diff = fabs(topPtUp_yield-nom_yield);
    //double error = sqrt( pow(nom_error,2)+pow(diff,2) );
    double error = sqrt( pow(diff,2) );
    h_mc_band->SetBinError(iBin,error);
  }
  h_mc_band->SetFillStyle(3004);
  h_mc_band->SetFillColor(kBlack);


  TH1D *h_mc_ttv = (TH1D*)f_TTV->Get(hName);
  h_mc_ttv->Scale(SF);
  if(hName.Contains("diLep_pt")) h_mc_ttv->Rebin(2);
  h_mc_ttv->SetLineColor(kMagenta-5);
  h_mc_ttv->SetFillColor(kMagenta-5);

  TH1D *h_mc_wjets = (TH1D*)f_wjets->Get(hName);
  h_mc_wjets->Scale(SF);
  if(hName.Contains("diLep_pt")) h_mc_wjets->Rebin(2);
  h_mc_wjets->SetLineColor(kOrange-2);
  h_mc_wjets->SetFillColor(kOrange-2);

  TH1D *h_mc_dyjets = (TH1D*)f_dyjets->Get(hName);
  h_mc_dyjets->Scale(SF);
  if(hName.Contains("diLep_pt")) h_mc_dyjets->Rebin(2);
  h_mc_dyjets->SetLineColor(kGreen);
  h_mc_dyjets->SetFillColor(kGreen);

  TH1D *h_mc_singleT = (TH1D*)f_singleT->Get(hName);
  h_mc_singleT->Scale(SF);
  if(hName.Contains("diLep_pt")) h_mc_singleT->Rebin(2);
  h_mc_singleT->SetLineColor(kYellow+1);
  h_mc_singleT->SetFillColor(kYellow+1);
  
  TH1D *h_mc_ttbar = (TH1D*)f_ttbar->Get(hName);
  h_mc_ttbar->Scale(SF);
  if(hName.Contains("diLep_pt")) h_mc_ttbar->Rebin(2);
  h_mc_ttbar->SetLineColor(kCyan-3);
  h_mc_ttbar->SetFillColor(kCyan-3);


  THStack *h_stack = new THStack("h_stack", "");
  h_stack->Add(h_mc_ttv);
  h_stack->Add(h_mc_wjets);
  h_stack->Add(h_mc_dyjets);
  h_stack->Add(h_mc_singleT);
  h_stack->Add(h_mc_ttbar);


  //
  // Draw plot
  //
  TCanvas *can = new TCanvas("can", "can", 10, 10, 800, 800);

  TPad *pad1 = new TPad("pad1", "pad1", 0.00, 0.20, 1.00, 1.00);
  TPad *pad2 = new TPad("pad2", "pad2", 0.00, 0.00, 1.00, 0.19);
  pad1->Draw();
  pad2->Draw();

  pad1->cd();

  
  double max = std::max( h_all_mc_nom->GetBinContent(h_all_mc_nom->GetMaximumBin()), h_data->GetBinContent(h_data->GetMaximumBin()) );
  max = std::max( h_all_mc_nom->GetBinContent(h_all_mc_nom->GetMaximumBin()), h_all_mc_topPtUp->GetBinContent(h_all_mc_topPtUp->GetMaximumBin()) );

  h_stack->SetMaximum(1.1*max);

  h_stack->Draw("hist");
  h_mc_band->Draw("e2 same");
  h_data->Draw("e1 same");
  
  TLegend *leg = new TLegend(0.70, 0.70, 0.90, 0.90);
  leg->AddEntry(h_data, "Data", "l");
  leg->AddEntry(h_mc_ttv, "ttV", "lf");
  leg->AddEntry(h_mc_wjets, "Wjets", "lf");
  leg->AddEntry(h_mc_dyjets, "DYjets", "lf");
  leg->AddEntry(h_mc_singleT, "single t", "lf");
  leg->AddEntry(h_mc_ttbar, "ttbar", "lf");

  leg->Draw();

  pad2->cd();
  
  TH1D *h_ratio = (TH1D*)h_data->Clone("ratio");
  
  TH1D *h_ratio_band = (TH1D*)h_mc_band->Clone("h_ratio_band");
  h_ratio_band->SetFillColor(kBlack);
  h_ratio_band->SetFillStyle(3004);
  for(int iBin=1; iBin<=h_data->GetNbinsX(); iBin++){
    double ratio = h_data->GetBinContent(iBin)/h_all_mc_nom->GetBinContent(iBin);
    double error = 0.0;
    if(h_data->GetBinContent(iBin)>0.0) error = ratio*sqrt( pow( h_data->GetBinError(iBin)/h_data->GetBinContent(iBin), 2) );
    cout << "Ratio = " << ratio << " +/- " << error << endl;
    h_ratio->SetBinContent(iBin, ratio);
    h_ratio->SetBinError(iBin, error);
    
    double percent_err_mc = (h_mc_band->GetBinError(iBin)/h_mc_band->GetBinContent(iBin));
    cout << "MC % err = " << percent_err_mc << endl;
    h_ratio_band->SetBinContent(iBin,1.0);
    h_ratio_band->SetBinError(iBin,percent_err_mc);
  }
  //h_ratio->Divide(h_mc_band);

  h_ratio->GetYaxis()->SetRangeUser(0.5,1.5);

  h_ratio->Draw("e1");
  h_ratio_band->Draw("e2 same");
   
  TLine *line = new TLine(h_ratio->GetXaxis()->GetBinLowEdge(1), 1.0, h_ratio->GetXaxis()->GetBinUpEdge(h_ratio->GetNbinsX()), 1.0 );
  line->SetLineColor(kRed);
  line->Draw("same");
  h_ratio->Draw("e1 same");
  
  can->SaveAs("data_vs_mc__"+hName+".pdf");

  pad1->cd();
  pad1->SetLogy();
  h_stack->SetMaximum(10.0*max);
  can->SaveAs("data_vs_mc__"+hName+"__logy.pdf");

  can->~TCanvas();


  //
  // Clean up
  //
  f_data->Close();
  f_all_mc->Close();
  f_TTV->Close();
  f_wjets->Close();
  f_dyjets->Close();
  f_singleT->Close();
  f_ttbar->Close();
  
  return;
}
