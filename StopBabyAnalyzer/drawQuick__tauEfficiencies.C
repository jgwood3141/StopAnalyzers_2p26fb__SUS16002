#include "Riostream.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1.h"
#include "TString.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TLine.h"
#include "TLegend.h"

void drawQuick__tauEfficiencies(){

  gStyle->SetOptStat(0);

  //
  // Open relevant files
  //
  TFile *f_new = new TFile("histos__ttbar_powheg_pythia8_ext3_25ns__v9__eta2p4__20160209.root", "read");
  TFile *f_old = new TFile("histos__ttbar_powheg_pythia8_ext3_25ns__v7__20160209.root", "read");
  

  //
  // Grab Histos
  // 
  TH1D *h_new_genTau_pt = (TH1D*)f_new->Get("h_genHadTau_pt");
  h_new_genTau_pt->Rebin(2);

  TH1D *h_new_genTau_pt_isIsoTrack = (TH1D*)f_new->Get("h_genHadTau_pt_isIsoTrack");
  h_new_genTau_pt_isIsoTrack->Rebin(2);

  TH1D *h_new_genTau_pt_isTauId = (TH1D*)f_new->Get("h_genHadTau_pt_isTauId");
  h_new_genTau_pt_isTauId->Rebin(2);

  TH1D *h_new_genTau_pt_isIsoTrackOrTauId = (TH1D*)f_new->Get("h_genHadTau_pt_isIsoTrackOrTauId");
  h_new_genTau_pt_isIsoTrackOrTauId->Rebin(2);



  TH1D *h_old_genTau_pt = (TH1D*)f_old->Get("h_genHadTau_pt");
  h_old_genTau_pt->Rebin(2);

  TH1D *h_old_genTau_pt_isIsoTrack = (TH1D*)f_old->Get("h_genHadTau_pt_isIsoTrack");
  h_old_genTau_pt_isIsoTrack->Rebin(2);

  TH1D *h_old_genTau_pt_isTauId = (TH1D*)f_old->Get("h_genHadTau_pt_isTauId");
  h_old_genTau_pt_isTauId->Rebin(2);

  TH1D *h_old_genTau_pt_isIsoTrackOrTauId = (TH1D*)f_old->Get("h_genHadTau_pt_isIsoTrackOrTauId");
  h_old_genTau_pt_isIsoTrackOrTauId->Rebin(2);

  
  //
  // Calc Efficiencies
  //
  TH1D *h_new_eff_isIsoTrack = (TH1D*)h_new_genTau_pt_isIsoTrack->Clone("h_new_eff_isIsoTrack");
  h_new_eff_isIsoTrack->Divide(h_new_eff_isIsoTrack, h_new_genTau_pt, 1, 1, "b");

  TH1D *h_new_eff_isTauId = (TH1D*)h_new_genTau_pt_isTauId->Clone("h_new_eff_isTauId");
  h_new_eff_isTauId->Divide(h_new_eff_isTauId, h_new_genTau_pt, 1, 1, "b");

  TH1D *h_new_eff_isIsoTrackOrTauId = (TH1D*)h_new_genTau_pt_isIsoTrackOrTauId->Clone("h_new_eff_isIsoTrackOrTauId");
  h_new_eff_isIsoTrackOrTauId->Divide(h_new_eff_isIsoTrackOrTauId, h_new_genTau_pt, 1, 1, "b");



  TH1D *h_old_eff_isIsoTrack = (TH1D*)h_old_genTau_pt_isIsoTrack->Clone("h_old_eff_isIsoTrack");
  h_old_eff_isIsoTrack->Divide(h_old_eff_isIsoTrack, h_old_genTau_pt, 1, 1, "b");

  TH1D *h_old_eff_isTauId = (TH1D*)h_old_genTau_pt_isTauId->Clone("h_old_eff_isTauId");
  h_old_eff_isTauId->Divide(h_old_eff_isTauId, h_old_genTau_pt, 1, 1, "b");

  TH1D *h_old_eff_isIsoTrackOrTauId = (TH1D*)h_old_genTau_pt_isIsoTrackOrTauId->Clone("h_old_eff_isIsoTrackOrTauId");
  h_old_eff_isIsoTrackOrTauId->Divide(h_old_eff_isIsoTrackOrTauId, h_old_genTau_pt, 1, 1, "b");



  //
  // Draw Plots
  //
  TCanvas *can = new TCanvas("can", "can", 10, 10, 800, 800);
  
  h_new_eff_isIsoTrackOrTauId->SetLineColor(kGreen);
  h_new_eff_isIsoTrack->SetLineColor(kOrange+7);
  h_new_eff_isTauId->SetLineColor(kBlue);

  h_new_eff_isIsoTrackOrTauId->SetMaximum(1.1);
  
  h_new_eff_isIsoTrackOrTauId->Draw("e1");

  h_new_eff_isIsoTrackOrTauId->SetTitle("Tau Reco Efficiencies, ttbar powheg pythia8 ext, nJets>=2, met>250");
  h_new_eff_isIsoTrackOrTauId->GetXaxis()->SetTitle("Gen Tau Hadron pT [GeV]");

  TLine *line = new TLine(h_new_eff_isIsoTrack->GetXaxis()->GetBinLowEdge(1), 1.0, h_new_eff_isIsoTrack->GetXaxis()->GetBinUpEdge(h_new_eff_isIsoTrack->GetNbinsX()), 1.0);
  line->SetLineColor(kRed);
  line->Draw();

  h_new_eff_isIsoTrackOrTauId->Draw("e1 same");
  h_new_eff_isIsoTrack->Draw("e1 same");
  h_new_eff_isTauId->Draw("e1 same");

  TLegend *leg = new TLegend(0.70, 0.70, 0.9, 0.9);
  leg->AddEntry( h_new_eff_isIsoTrackOrTauId, "Tau ID OR Iso Track", "l");
  leg->AddEntry( h_new_eff_isIsoTrack, "Iso Track", "l");
  leg->AddEntry( h_new_eff_isTauId, "Tau ID", "l");
  leg->Draw();

  can->SaveAs("ttbar_powheg_pythia8_ext3__v9__tauEfficiencies.pdf");
  can->~TCanvas();



  can = new TCanvas("can", "can", 10, 10, 800, 800);
  
  h_old_eff_isIsoTrackOrTauId->SetLineColor(kGreen);
  h_old_eff_isIsoTrack->SetLineColor(kOrange+7);
  h_old_eff_isTauId->SetLineColor(kBlue);

  h_old_eff_isIsoTrackOrTauId->SetMaximum(1.1);
  
  h_old_eff_isIsoTrackOrTauId->Draw("e1");
  
  h_old_eff_isIsoTrackOrTauId->SetTitle("Tau Reco Efficiencies, ttbar powheg pythia8 ext, nJets>=2, met>250");
  h_old_eff_isIsoTrackOrTauId->GetXaxis()->SetTitle("Gen Tau Hadron pT [GeV]");

  line = new TLine(h_old_eff_isIsoTrack->GetXaxis()->GetBinLowEdge(1), 1.0, h_old_eff_isIsoTrack->GetXaxis()->GetBinUpEdge(h_old_eff_isIsoTrack->GetNbinsX()), 1.0);
  line->SetLineColor(kRed);
  line->Draw();

  h_old_eff_isIsoTrackOrTauId->Draw("e1 same");
  h_old_eff_isIsoTrack->Draw("e1 same");
  h_old_eff_isTauId->Draw("e1 same");

  leg = new TLegend(0.70, 0.70, 0.9, 0.9);
  leg->AddEntry( h_old_eff_isIsoTrackOrTauId, "Tau ID OR Iso Track", "l");
  leg->AddEntry( h_old_eff_isIsoTrack, "Iso Track", "l");
  leg->AddEntry( h_old_eff_isTauId, "Tau ID", "l");
  leg->Draw();

  can->SaveAs("ttbar_powheg_pythia8_ext3__v7__tauEfficiencies.pdf");
  can->~TCanvas();



  f_new->Close();
  f_old->Close();
  
  return;
}
