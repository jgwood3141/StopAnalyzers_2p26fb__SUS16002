#include "Riostream.h"
#include "TStyle.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TH1.h"
#include "TLegend.h"
#include "TLine.h"
#include "TString.h"

#include <vector>

void drawOverlay( std::vector<TH1F*> allHists, vector<TString> histLabels, TString title, TString saveMe, bool unitNorm=false, int rebin=1){

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

  // Draw 
  for(int iHist=0; iHist<nHists; iHist++){
    if(iHist==0) allHists[iHist]->Draw("hist");
    else         allHists[iHist]->Draw("hist same");
  }
  leg->Draw();
  
  pad2->cd();
  
  TLine unity(allHists[0]->GetBinLowEdge(0), 1.0, allHists[0]->GetBinLowEdge(allHists[0]->GetNbinsX()+1), 1.0);
  unity.SetLineWidth(3);
  unity.SetLineColor(kRed);

  TH1F *ratio[nHists];
  
  for(int iHist=0; iHist<nHists; iHist++){
    TString ratio_name = "ratio_";
    ratio_name += Form("%d", iHist);
    ratio[iHist] = (TH1F*)allHists[iHist]->Clone(ratio_name);
    ratio[iHist]->Divide(allHists[0]);
    ratio[iHist]->SetMaximum(2.0);
    ratio[iHist]->SetMinimum(0.5);
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
  
			 
    
  
  

void overlayHists(){

  gStyle->SetOptStat(0);

  // Open Files
  TFile *f_run25ns = new TFile("Histos_Phys14_OriginalUCLASynch/histos__ttbar_2l_powheg_pythia8_25ns.root", "read");

  TFile *f_phys14 = new TFile("../StopBabyAnalyzer_Phys14/Histos_OriginalUCLASynch/histos__ttbar_2l.root", "read");

  vector<TH1F*> histos;
  vector<TString> hLabels;
  
  // MET overlay
  TH1F *met_run25ns = (TH1F*)f_run25ns->Get("h_met__baseline");
  met_run25ns->SetLineColor(kBlue);
  histos.push_back(met_run25ns);
  hLabels.push_back("ttbar 2l, powheg run25ns");

  TH1F *met_phys14 = (TH1F*)f_phys14->Get("h_met__baseline");
  met_phys14->SetLineColor(kRed);
  histos.push_back(met_phys14);
  hLabels.push_back("ttbar 2l, madgraph phys14");

  drawOverlay(histos, hLabels, "t#bar{t} 2l, MET, baseline selection", "Plots_Overlays/h_overlay__ttbar2l__met_baseline__run25ns_vs_phys14.pdf", false, 2);

  drawOverlay(histos, hLabels, "t#bar{t} 2l, MET, baseline selection", "Plots_Overlays/h_overlay__ttbar2l__met_baseline__run25ns_vs_phys14_unitNorm.pdf", true, 2);
  histos.clear();
  hLabels.clear();


  // MT2W overlay
  TH1F *mt2w_run25ns = (TH1F*)f_run25ns->Get("h_MT2W__baseline");
  mt2w_run25ns->SetLineColor(kBlue);
  histos.push_back(mt2w_run25ns);
  hLabels.push_back("ttbar 2l, powheg run25ns");

  TH1F *mt2w_phys14 = (TH1F*)f_phys14->Get("h_MT2W__baseline");
  mt2w_phys14->SetLineColor(kRed);
  histos.push_back(mt2w_phys14);
  hLabels.push_back("ttbar 2l, madgraph phys14");

  drawOverlay(histos, hLabels, "t#bar{t} 2l, MT2W, baseline selection", "Plots_Overlays/h_overlay__ttbar2l__mt2w_baseline__run25ns_vs_phys14.pdf", false, 2);

  drawOverlay(histos, hLabels, "t#bar{t} 2l, MT2W, baseline selection", "Plots_Overlays/h_overlay__ttbar2l__mt2w_baseline__run25ns_vs_phys14_unitNorm.pdf", true, 2);
  histos.clear();
  hLabels.clear();




  f_run25ns->Close();
  f_phys14->Close();

  return;
}
