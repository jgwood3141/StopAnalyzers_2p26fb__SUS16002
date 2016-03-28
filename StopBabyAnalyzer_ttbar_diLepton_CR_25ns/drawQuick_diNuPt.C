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
#include "TF1.h"

void drawQuick_diNuPt(){

  gStyle->SetOptStat(0);
  gStyle->SetHistLineWidth(3);


  //
  // Open Data/MC files
  //
  TString inDir = "Histos/Nominal/";

  //TFile *f_ttbar = new TFile(inDir+"histos__ttbar_25ns.root", "read");
  TFile *f_ttbar = new TFile(inDir+"histos__ttbar_powheg_pythia8_ext3_25ns.root", "read");
  
  //
  // Grab Histos
  //
  TString hName = "h__diNuPt__incl__nominal__ge2j_ge1t_gt0met";
  TString hTitle = "Gen level, di-neutrino pT, ttbar ee/em/mumu selection, >=2jet, >=1 tag";

  TString hName_highMt = hName;
  hName_highMt.ReplaceAll("__diNuPt__", "__diNuPt_highMT__");
  TString hTitle_highMt = "Gen level, di-neutrino pT, MT>150, ee/em/mumu selection, >=2jet, >=1 tag";

  TString hName_lowMt = hName;
  hName_lowMt.ReplaceAll("__diNuPt__", "__diNuPt_lowMT__");
  TString hTitle_lowMt = "Gen level, di-neutrino pT, MT<150, ee/em/mumu selection, >=2jet, >=1 tag";

  std::vector<TString> v_names;
  v_names.push_back(hName);
  v_names.push_back(hName_highMt);
  v_names.push_back(hName_lowMt);

  std::vector<TString> v_titles;
  v_titles.push_back(hTitle);
  v_titles.push_back(hTitle_highMt);
  v_titles.push_back(hTitle_lowMt);
  
  
  
  //
  // Rebin Info
  //
  int rebin_default = 1;

  int rebin_met = 5;
  int nBins_rebin_met = 8;
  double xBins[9]{0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 550.0};
  

  //
  // Grab histos, make plots
  //
  TH1D *h_diNuPt_incl = (TH1D*)f_ttbar->Get(hName);
  h_diNuPt_incl->Scale(1.0/h_diNuPt_incl->Integral(0,-1));
  h_diNuPt_incl->SetBinContent(h_diNuPt_incl->GetNbinsX(), h_diNuPt_incl->GetBinContent(h_diNuPt_incl->GetNbinsX())+h_diNuPt_incl->GetBinContent(h_diNuPt_incl->GetNbinsX()+1));
  h_diNuPt_incl->SetBinError(h_diNuPt_incl->GetNbinsX(), sqrt( pow(h_diNuPt_incl->GetBinError(h_diNuPt_incl->GetNbinsX()),2)+pow(h_diNuPt_incl->GetBinError(h_diNuPt_incl->GetNbinsX()+1),2) ) );
  if(hName.Contains("__diNuPt_")) h_diNuPt_incl = (TH1D*)h_diNuPt_incl->Rebin(nBins_rebin_met,hName+"__allMC_rebin",xBins);
  
  h_diNuPt_incl->SetLineColor(kBlack);
   
  h_diNuPt_incl->SetTitle(hTitle);


  TH1D *h_diNuPt_highMT = (TH1D*)f_ttbar->Get(hName_highMt);
  h_diNuPt_highMT->Scale(1.0/h_diNuPt_highMT->Integral(0,-1));
  h_diNuPt_highMT->SetBinContent(h_diNuPt_highMT->GetNbinsX(), h_diNuPt_highMT->GetBinContent(h_diNuPt_highMT->GetNbinsX())+h_diNuPt_highMT->GetBinContent(h_diNuPt_highMT->GetNbinsX()+1));
  h_diNuPt_highMT->SetBinError(h_diNuPt_highMT->GetNbinsX(), sqrt( pow(h_diNuPt_highMT->GetBinError(h_diNuPt_highMT->GetNbinsX()),2)+pow(h_diNuPt_highMT->GetBinError(h_diNuPt_highMT->GetNbinsX()+1),2) ) );
  if(hName.Contains("__diNuPt_")) h_diNuPt_highMT = (TH1D*)h_diNuPt_highMT->Rebin(nBins_rebin_met,hName+"__allMC_rebin",xBins);
  h_diNuPt_highMT->SetLineColor(kRed);
  

  TH1D *h_diNuPt_lowMT = (TH1D*)f_ttbar->Get(hName_lowMt);
  h_diNuPt_lowMT->Scale(1.0/h_diNuPt_lowMT->Integral(0,-1));
  h_diNuPt_lowMT->SetBinContent(h_diNuPt_lowMT->GetNbinsX(), h_diNuPt_lowMT->GetBinContent(h_diNuPt_lowMT->GetNbinsX())+h_diNuPt_lowMT->GetBinContent(h_diNuPt_lowMT->GetNbinsX()+1));
  h_diNuPt_lowMT->SetBinError(h_diNuPt_lowMT->GetNbinsX(), sqrt( pow(h_diNuPt_lowMT->GetBinError(h_diNuPt_lowMT->GetNbinsX()),2)+pow(h_diNuPt_lowMT->GetBinError(h_diNuPt_lowMT->GetNbinsX()+1),2) ) );
  if(hName.Contains("__diNuPt_")) h_diNuPt_lowMT = (TH1D*)h_diNuPt_lowMT->Rebin(nBins_rebin_met,hName+"__allMC_rebin",xBins);
  h_diNuPt_lowMT->SetLineColor(kGreen+3);
  

  //
  // Draw plot
  //
  TCanvas *can = new TCanvas("can", "can", 10, 10, 800, 800);

  TPad *pad1 = new TPad("pad1", "pad1", 0.00, 0.20, 1.00, 1.00);
  TPad *pad2 = new TPad("pad2", "pad2", 0.00, 0.00, 1.00, 0.19);
  pad1->Draw();
  pad2->Draw();

  pad1->cd();

  
  double max = std::max( h_diNuPt_incl->GetBinContent(h_diNuPt_incl->GetMaximumBin()), h_diNuPt_highMT->GetBinContent(h_diNuPt_highMT->GetMaximumBin()) );
  max = std::max( max, h_diNuPt_lowMT->GetBinContent(h_diNuPt_lowMT->GetMaximumBin()) );
  
  h_diNuPt_incl->SetMaximum(1.1*max);
  
  h_diNuPt_incl->Draw("e1");
  h_diNuPt_highMT->Draw("e1 same");
  h_diNuPt_lowMT->Draw("e1 same");

  TLegend *leg = new TLegend(0.70, 0.70, 0.90, 0.90);
  leg->AddEntry(h_diNuPt_incl, "No MT Cut", "l");
  leg->AddEntry(h_diNuPt_highMT, "MT>150", "l");
  leg->AddEntry(h_diNuPt_lowMT, "MT<150", "lf");
  
  leg->Draw();

  pad2->cd();
  
  TH1D *h_ratio_highMT = (TH1D*)h_diNuPt_highMT->Clone("ratio_highMT");
  h_ratio_highMT->SetTitle("");
  h_ratio_highMT->Divide(h_diNuPt_incl);

  TH1D *h_ratio_lowMT = (TH1D*)h_diNuPt_lowMT->Clone("ratio_lowMT");
  h_ratio_lowMT->SetTitle("");
  h_ratio_lowMT->Divide(h_diNuPt_incl);
  
  TH1D *h_ratio = (TH1D*)h_diNuPt_highMT->Clone("ratio_highOverLeowMT");
  h_ratio->SetTitle("");
  h_ratio->Divide(h_diNuPt_lowMT);
  h_ratio->SetLineColor(kBlack);
  
  h_ratio_highMT->GetYaxis()->SetRangeUser(0.0,2.0);

  //h_ratio_highMT->Draw("e1");
  h_ratio->Draw("e1");
  h_ratio->GetYaxis()->SetTitle("highMT/lowMT");
 
  TLine *line = new TLine(h_ratio_highMT->GetXaxis()->GetBinLowEdge(1), 1.0, h_ratio_highMT->GetXaxis()->GetBinUpEdge(h_ratio_highMT->GetNbinsX()), 1.0 );
  line->SetLineColor(kRed);
  line->Draw("same");
  //h_ratio_highMT->Draw("e1 same");
  //h_ratio_lowMT->Draw("e1 same");
  h_ratio->Draw("e1 same");

  //can->SaveAs("mc_comparison__"+hName+".pdf");

  pad1->cd();
  pad1->SetLogy();
  h_diNuPt_incl->SetMaximum(10.0*max);
  can->SaveAs("mc_comparison__"+hName+"__logy.pdf");

  can->~TCanvas();


  //
  // Clean up
  //
  f_ttbar->Close();
  
  return;
}
