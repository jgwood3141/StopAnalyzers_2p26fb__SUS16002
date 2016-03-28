#include "TStyle.h"
#include "TFile.h"
#include "TString.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TLine.h"

void drawQuick_nJetsSF(){

  gStyle->SetOptStat(0);

  const int nBins = 4;
  double xBins[nBins+1]{50.0,100.0,150.0,200.0,250.0};
  
  TH1D *h_k3 = new TH1D("h_k3", "nJets Scale Factors, for E_{T}^{miss} > bin low edge;E_{T}^{miss}[GeV];nJets Scale Factor", nBins,xBins);
  h_k3->SetBinContent( 1, 1.08 );
  h_k3->SetBinError  ( 1, 0.06 );
  h_k3->SetBinContent( 2, 1.06 );
  h_k3->SetBinError  ( 2, 0.10 );
  h_k3->SetBinContent( 3, 1.17 );
  h_k3->SetBinError  ( 3, 0.24 );
  h_k3->SetBinContent( 4, 1.02 );
  h_k3->SetBinError  ( 4, 0.52 );

  h_k3->SetLineColor(kRed);
  
  TLine *l_k3 = new TLine(50.0, 1.08, 250.0, 1.08);
  l_k3->SetLineColor(kOrange+1);
  l_k3->SetLineWidth(3);

  TH1D *h_k4 = new TH1D("h_k4", "nJets Scale Factors vs E_{T}^{miss};E_{T}^{miss}[GeV];nJets Scale Factor", nBins,xBins);
  h_k4->SetBinContent( 1, 0.92 );
  h_k4->SetBinError  ( 1, 0.06 );
  h_k4->SetBinContent( 2, 0.93 );
  h_k4->SetBinError  ( 2, 0.09 );
  h_k4->SetBinContent( 3, 1.11 );
  h_k4->SetBinError  ( 3, 0.22 );
  h_k4->SetBinContent( 4, 1.07 );
  h_k4->SetBinError  ( 4, 0.48 );

  h_k4->SetLineColor(kBlue);

  TLine *l_k4 = new TLine(50.0, 0.92, 250.0, 0.92);
  l_k4->SetLineColor(kAzure+6);
  l_k4->SetLineWidth(3);

  TCanvas *can = new TCanvas("can", "can",10, 10, 800, 1000);

  h_k3->Draw("e1");
  h_k3->GetYaxis()->SetTitleOffset(1.5);

  l_k3->Draw("same");
  l_k4->Draw("same");
  h_k3->Draw("e1 same");
  h_k4->Draw("e1 same");

  
  TLegend *leg = new TLegend( 0.15, 0.70, 0.40, 0.87 );
  leg->AddEntry(h_k3, "nJets Scale Factor, K3", "l");
  leg->AddEntry(h_k4, "nJets Scale Factor, K4", "l");
  leg->Draw("same");

  TString saveMeAs = "nJetsSF_plot";
  can->SaveAs(saveMeAs+".pdf");
  can->SaveAs(saveMeAs+".C");

  return;
}
