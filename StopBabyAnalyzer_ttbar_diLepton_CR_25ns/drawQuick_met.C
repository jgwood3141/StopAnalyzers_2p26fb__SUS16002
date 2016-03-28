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
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TMatrixDSym.h"

void drawQuick_met(){

  gStyle->SetOptStat(0);
  gStyle->SetHistLineWidth(3);

  bool drawErrorBand = false;

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
  TString hName = "h__met__incl__nominal__ge2j_ge1t_gt0met";
  TString hTitle = "MET, ee/em/mumu selection, >=2jet, >=1 tag";

  int rebin_default = 1;

  int rebin_met = 5;
  int nBins_rebin_met = 8;
  double xBins[9]{0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 350.0, 450.0, 550.0};
  //int nBins_rebin_met = 6;
  //double xBins[7]{0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 550.0};

  std::vector<TString> hName_metRes;
  
  TString hName_metResUp_1 = hName;
  hName_metResUp_1.ReplaceAll("__nominal__","__metRes_ee2j_met_250_350_scaleUp__");
  hName_metRes.push_back(hName_metResUp_1);
  TString hName_metResDn_1 = hName;
  hName_metResDn_1.ReplaceAll("__nominal__","__metRes_ee2j_met_250_350_scaleDown__");
  hName_metRes.push_back(hName_metResDn_1);


  TString hName_metResUp_2 = hName;
  hName_metResUp_2.ReplaceAll("__nominal__","__metRes_ee2j_met_350_inf_scaleUp__");
  hName_metRes.push_back(hName_metResUp_2);
  TString hName_metResDn_2 = hName;
  hName_metResDn_2.ReplaceAll("__nominal__","__metRes_ee2j_met_350_inf_scaleDown__");
  hName_metRes.push_back(hName_metResDn_2);


  TString hName_metResUp_3 = hName;
  hName_metResUp_3.ReplaceAll("__nominal__","__metRes_ee3j_met_250_350_scaleUp__");
  hName_metRes.push_back(hName_metResUp_3);
  TString hName_metResDn_3 = hName;
  hName_metResDn_3.ReplaceAll("__nominal__","__metRes_ee3j_met_250_350_scaleDown__");
  hName_metRes.push_back(hName_metResDn_3);


  TString hName_metResUp_4 = hName;
  hName_metResUp_4.ReplaceAll("__nominal__","__metRes_ee3j_met_350_inf_scaleUp__");
  hName_metRes.push_back(hName_metResUp_4);
  TString hName_metResDn_4 = hName;
  hName_metResDn_4.ReplaceAll("__nominal__","__metRes_ee3j_met_350_inf_scaleDown__");
  hName_metRes.push_back(hName_metResDn_4);


  TString hName_metResUp_5 = hName;
  hName_metResUp_5.ReplaceAll("__nominal__","__metRes_ge4j_lt200mt2w_met_250_325_scaleUp__");
  hName_metRes.push_back(hName_metResUp_5);
  TString hName_metResDn_5 = hName;
  hName_metResDn_5.ReplaceAll("__nominal__","__metRes_ge4j_lt200mt2w_met_250_325_scaleDown__");
  hName_metRes.push_back(hName_metResDn_5);


  TString hName_metResUp_6 = hName;
  hName_metResUp_6.ReplaceAll("__nominal__","__metRes_ge4j_lt200mt2w_met_325_inf_scaleUp__");
  hName_metRes.push_back(hName_metResUp_6);
  TString hName_metResDn_6 = hName;
  hName_metResDn_6.ReplaceAll("__nominal__","__metRes_ge4j_lt200mt2w_met_325_inf_scaleDown__");
  hName_metRes.push_back(hName_metResDn_6);

  
  TString hName_metResUp_7 = hName;
  hName_metResUp_7.ReplaceAll("__nominal__","__metRes_ge4j_ge200mt2w_met_250_350_scaleUp__");
  hName_metRes.push_back(hName_metResUp_7);
  TString hName_metResDn_7 = hName;
  hName_metResDn_7.ReplaceAll("__nominal__","__metRes_ge4j_ge200mt2w_met_250_350_scaleDown__");
  hName_metRes.push_back(hName_metResDn_7);


  TString hName_metResUp_8 = hName;
  hName_metResUp_8.ReplaceAll("__nominal__","__metRes_ge4j_ge200mt2w_met_350_450_scaleUp__");
  hName_metRes.push_back(hName_metResUp_8);
  TString hName_metResDn_8 = hName;
  hName_metResDn_8.ReplaceAll("__nominal__","__metRes_ge4j_ge200mt2w_met_350_450_scaleDown__");
  hName_metRes.push_back(hName_metResDn_8);


  TString hName_metResUp_9 = hName;
  hName_metResUp_9.ReplaceAll("__nominal__","__metRes_ge4j_ge200mt2w_met_450_inf_scaleUp__");
  hName_metRes.push_back(hName_metResUp_9);
  TString hName_metResDn_9 = hName;
  hName_metResDn_9.ReplaceAll("__nominal__","__metRes_ge4j_ge200mt2w_met_450_inf_scaleDown__");
  hName_metRes.push_back(hName_metResDn_9);
  
  /*
  TString hName_topPtUp = hName;
  hName_topPtUp.ReplaceAll("__nominal__","__topPt_scaleUp__");
  hName_metRes.push_back(hName_topPtUp);
  
  TString hName_topPtDn = hName;
  hName_topPtDn.ReplaceAll("__nominal__","__topPt_scaleDown__");
  hName_metRes.push_back(hName_topPtDn);
  */

  TH1D *h_data = (TH1D*)f_data->Get(hName);
  h_data->SetBinContent(h_data->GetNbinsX(), h_data->GetBinContent(h_data->GetNbinsX())+h_data->GetBinContent(h_data->GetNbinsX()+1));
  h_data->SetBinError(h_data->GetNbinsX(), sqrt( pow(h_data->GetBinError(h_data->GetNbinsX()),2)+pow(h_data->GetBinError(h_data->GetNbinsX()+1),2) ) );
  if(hName.Contains("__met_")) h_data = (TH1D*)h_data->Rebin(nBins_rebin_met,hName+"__data_rebin",xBins);
  

  
  TH1D *h_all_mc_nom = (TH1D*)f_all_mc->Get(hName);
  h_all_mc_nom->SetBinContent(h_all_mc_nom->GetNbinsX(), h_all_mc_nom->GetBinContent(h_all_mc_nom->GetNbinsX())+h_all_mc_nom->GetBinContent(h_all_mc_nom->GetNbinsX()+1));
  h_all_mc_nom->SetBinError(h_all_mc_nom->GetNbinsX(), sqrt( pow(h_all_mc_nom->GetBinError(h_all_mc_nom->GetNbinsX()),2)+pow(h_all_mc_nom->GetBinError(h_all_mc_nom->GetNbinsX()+1),2) ) );
  if(hName.Contains("__met_")) h_all_mc_nom = (TH1D*)h_all_mc_nom->Rebin(nBins_rebin_met,hName+"__allMC_rebin",xBins);
  h_all_mc_nom->SetLineColor(kRed);
  
  double SF = h_data->Integral(0,-1)/h_all_mc_nom->Integral(0,-1);
  h_all_mc_nom->Scale(SF);
  
  TH1D *h_mc_band = (TH1D*)h_all_mc_nom->Clone(hName+"__mc_error_band");
  if(drawErrorBand){
    for(int iSys=0; iSys<(int)hName_metRes.size(); iSys+=2){
      
      TH1D *h_tempUp = (TH1D*)f_all_mc->Get(hName_metRes[iSys]);
      h_tempUp->SetBinContent(h_tempUp->GetNbinsX(), h_tempUp->GetBinContent(h_tempUp->GetNbinsX())+h_tempUp->GetBinContent(h_tempUp->GetNbinsX()+1));
      h_tempUp->SetBinError(h_tempUp->GetNbinsX(), sqrt( pow(h_tempUp->GetBinError(h_tempUp->GetNbinsX()),2)+pow(h_tempUp->GetBinError(h_tempUp->GetNbinsX()+1),2) ) );
      if(hName.Contains("__met_")) h_tempUp = (TH1D*)h_tempUp->Rebin(nBins_rebin_met,hName_metRes[iSys]+"__tempDn_rebin",xBins);
      h_tempUp->Scale(SF);
    
      TH1D *h_tempDn = (TH1D*)f_all_mc->Get(hName_metRes[iSys+1]);
      h_tempDn->SetBinContent(h_tempDn->GetNbinsX(), h_tempDn->GetBinContent(h_tempDn->GetNbinsX())+h_tempDn->GetBinContent(h_tempDn->GetNbinsX()+1));
      h_tempDn->SetBinError(h_tempDn->GetNbinsX(), sqrt( pow(h_tempDn->GetBinError(h_tempDn->GetNbinsX()),2)+pow(h_tempDn->GetBinError(h_tempDn->GetNbinsX()+1),2) ) );
      if(hName.Contains("__met_")) h_tempDn = (TH1D*)h_tempDn->Rebin(nBins_rebin_met,hName_metRes[iSys+1]+"__tempDn_rebin",xBins);
      h_tempDn->Scale(SF);

      for(int iBin=1; iBin<=(int)h_mc_band->GetNbinsX(); iBin++){

	double nom_yield      = h_mc_band->GetBinContent(iBin);
	double nom_error      = h_mc_band->GetBinError(iBin);
	if(iSys==0) nom_error = 0.0; // only diff in metRes for error

	double metResUp_yield = h_tempUp->GetBinContent(iBin);
	double metResDn_yield = h_tempDn->GetBinContent(iBin);

	double max_diff = std::max( fabs(metResUp_yield-nom_yield), fabs(metResDn_yield-nom_yield) );
      
	double error = sqrt( pow(max_diff,2) + pow(nom_error,2) );
	h_mc_band->SetBinError(iBin,error);
      }
    
    }
  }

  h_mc_band->SetFillStyle(3004);
  h_mc_band->SetFillColor(kBlack);


  TH1D *h_mc_ttv = (TH1D*)f_TTV->Get(hName);
  h_mc_ttv->SetBinContent(h_mc_ttv->GetNbinsX(), h_mc_ttv->GetBinContent(h_mc_ttv->GetNbinsX())+h_mc_ttv->GetBinContent(h_mc_ttv->GetNbinsX()+1));
  h_mc_ttv->SetBinError(h_mc_ttv->GetNbinsX(), sqrt( pow(h_mc_ttv->GetBinError(h_mc_ttv->GetNbinsX()),2)+pow(h_mc_ttv->GetBinError(h_mc_ttv->GetNbinsX()+1),2) ) );
  h_mc_ttv->Scale(SF);
  if(hName.Contains("__met_")) h_mc_ttv = (TH1D*)h_mc_ttv->Rebin(nBins_rebin_met,hName+"__ttv_rebin",xBins);
  h_mc_ttv->SetLineColor(kMagenta-5);
  h_mc_ttv->SetFillColor(kMagenta-5);

  TH1D *h_mc_wjets = (TH1D*)f_wjets->Get(hName);
  h_mc_wjets->SetBinContent(h_mc_wjets->GetNbinsX(), h_mc_wjets->GetBinContent(h_mc_wjets->GetNbinsX())+h_mc_wjets->GetBinContent(h_mc_wjets->GetNbinsX()+1));
  h_mc_wjets->SetBinError(h_mc_wjets->GetNbinsX(), sqrt( pow(h_mc_wjets->GetBinError(h_mc_wjets->GetNbinsX()),2)+pow(h_mc_wjets->GetBinError(h_mc_wjets->GetNbinsX()+1),2) ) );
  h_mc_wjets->Scale(SF);
  if(hName.Contains("__met_")) h_mc_wjets = (TH1D*)h_mc_wjets->Rebin(nBins_rebin_met,hName+"__wjets_rebin",xBins);
  h_mc_wjets->SetLineColor(kOrange-2);
  h_mc_wjets->SetFillColor(kOrange-2);

  TH1D *h_mc_dyjets = (TH1D*)f_dyjets->Get(hName);
  h_mc_dyjets->SetBinContent(h_mc_dyjets->GetNbinsX(), h_mc_dyjets->GetBinContent(h_mc_dyjets->GetNbinsX())+h_mc_dyjets->GetBinContent(h_mc_dyjets->GetNbinsX()+1));
  h_mc_dyjets->SetBinError(h_mc_dyjets->GetNbinsX(), sqrt( pow(h_mc_dyjets->GetBinError(h_mc_dyjets->GetNbinsX()),2)+pow(h_mc_dyjets->GetBinError(h_mc_dyjets->GetNbinsX()+1),2) ) );
  h_mc_dyjets->Scale(SF);
  if(hName.Contains("__met_")) h_mc_dyjets = (TH1D*)h_mc_dyjets->Rebin(nBins_rebin_met,hName+"__dyjets_rebin",xBins);
  h_mc_dyjets->SetLineColor(kGreen);
  h_mc_dyjets->SetFillColor(kGreen);

  TH1D *h_mc_singleT = (TH1D*)f_singleT->Get(hName);
  h_mc_singleT->Scale(SF);
  h_mc_singleT->SetBinContent(h_mc_singleT->GetNbinsX(), h_mc_singleT->GetBinContent(h_mc_singleT->GetNbinsX())+h_mc_singleT->GetBinContent(h_mc_singleT->GetNbinsX()+1));
  h_mc_singleT->SetBinError(h_mc_singleT->GetNbinsX(), sqrt( pow(h_mc_singleT->GetBinError(h_mc_singleT->GetNbinsX()),2)+pow(h_mc_singleT->GetBinError(h_mc_singleT->GetNbinsX()+1),2) ) );
  if(hName.Contains("__met_")) h_mc_singleT = (TH1D*)h_mc_singleT->Rebin(nBins_rebin_met,hName+"__singleT_rebin",xBins);
  h_mc_singleT->SetLineColor(kYellow+1);
  h_mc_singleT->SetFillColor(kYellow+1);
  
  TH1D *h_mc_ttbar = (TH1D*)f_ttbar->Get(hName);
  h_mc_ttbar->Scale(SF);
  h_mc_ttbar->SetBinContent(h_mc_ttbar->GetNbinsX(), h_mc_ttbar->GetBinContent(h_mc_ttbar->GetNbinsX())+h_mc_ttbar->GetBinContent(h_mc_ttbar->GetNbinsX()+1));
  h_mc_ttbar->SetBinError(h_mc_ttbar->GetNbinsX(), sqrt( pow(h_mc_ttbar->GetBinError(h_mc_ttbar->GetNbinsX()),2)+pow(h_mc_ttbar->GetBinError(h_mc_ttbar->GetNbinsX()+1),2) ) );
  if(hName.Contains("__met_")) h_mc_ttbar = (TH1D*)h_mc_ttbar->Rebin(nBins_rebin_met,hName+"__ttbar_rebin",xBins);
  h_mc_ttbar->SetLineColor(kCyan-3);
  h_mc_ttbar->SetFillColor(kCyan-3);


  THStack *h_stack = new THStack("h_stack", "");
  h_stack->Add(h_mc_ttv);
  h_stack->Add(h_mc_wjets);
  h_stack->Add(h_mc_dyjets);
  h_stack->Add(h_mc_singleT);
  h_stack->Add(h_mc_ttbar);

  h_stack->SetTitle(hTitle);

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
  
  h_stack->SetMaximum(1.1*max);
  h_stack->SetMinimum(0.1);

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
  h_ratio->SetTitle("");

  TH1D *h_ratio_band = (TH1D*)h_mc_band->Clone("h_ratio_band");
  h_ratio_band->SetFillColor(kBlack);
  h_ratio_band->SetFillStyle(3004);
  for(int iBin=1; iBin<=h_data->GetNbinsX(); iBin++){
    if( !(h_data->GetBinContent(iBin)>0.0) || !(h_all_mc_nom->GetBinContent(iBin)>0.0) ) continue;
    double ratio = h_data->GetBinContent(iBin)/h_all_mc_nom->GetBinContent(iBin);
    double error = ratio*sqrt( pow( h_data->GetBinError(iBin)/h_data->GetBinContent(iBin), 2) );
    double error_allStats = ratio*sqrt( pow( h_data->GetBinError(iBin)/h_data->GetBinContent(iBin), 2) + pow( h_all_mc_nom->GetBinError(iBin)/h_all_mc_nom->GetBinContent(iBin), 2) );
    cout << "Bin [" << h_ratio->GetXaxis()->GetBinLowEdge(iBin) << "," << h_ratio->GetXaxis()->GetBinUpEdge(iBin) << "], Ratio = " << ratio << " +/- " << error_allStats << endl;
    h_ratio->SetBinContent(iBin, ratio);
    h_ratio->SetBinError(iBin, error_allStats);
    
    double percent_err_mc = (h_mc_band->GetBinError(iBin)/h_mc_band->GetBinContent(iBin));
    h_ratio_band->SetBinContent(iBin,1.0);
    h_ratio_band->SetBinError(iBin,percent_err_mc);
  }
  //h_ratio->Divide(h_mc_band);

  double data_incl = h_data->Integral(h_data->FindBin(251.0),h_data->GetNbinsX());
  double mc_incl = h_all_mc_nom->Integral(h_all_mc_nom->FindBin(251.0),h_all_mc_nom->GetNbinsX());
  double sf_incl = data_incl/mc_incl;
  
  cout << "Data 250-inf = " << data_incl << endl;
  cout << "MC 250-inf   = " << mc_incl << endl;
  cout << "SF 250-inf   = " << sf_incl << endl;
  cout << endl;

  double data_250_350 = h_data->Integral(h_data->FindBin(251.0),h_data->FindBin(349.0));
  double data_ratio_250_350 = data_250_350/data_incl;
  double binErr_250_350 = sqrt( (data_ratio_250_350*(1-data_ratio_250_350))/data_incl );
  double mc_250_350 = h_all_mc_nom->Integral(h_all_mc_nom->FindBin(251.0),h_all_mc_nom->FindBin(349.0));
  double sf_250_350 = (data_250_350/mc_250_350)/sf_incl;
  double sf_err_250_350 = (binErr_250_350/data_ratio_250_350)*sf_250_350;

  cout << "Data 250-350           = " << data_250_350 << endl;
  cout << "Data Ratio             = " << data_ratio_250_350 << endl;
  cout << "Err Data Ratio 250-350 = " << binErr_250_350 << endl;
  cout << "MC 250-350             = " << mc_250_350 << endl;
  cout << "Data/MC 250-350        = " << data_250_350/mc_250_350 << endl;
  cout << "SF 250-350             = " << sf_250_350 << endl;
  cout << "~Err SF                = " << sf_err_250_350 << endl;
  cout << endl;

  double data_350_450   = h_data->Integral(h_data->FindBin(351.0),h_data->FindBin(449.0));
  double data_ratio_350_450  = data_350_450/data_incl;
  double binErr_350_450 = sqrt( (data_ratio_350_450*(1-data_ratio_350_450))/data_incl );
  double mc_350_450 = h_all_mc_nom->Integral(h_all_mc_nom->FindBin(351.0),h_all_mc_nom->FindBin(449.0));
  double sf_350_450 = (data_350_450/mc_350_450)/sf_incl;
  double sf_err_350_450 = (binErr_350_450/data_ratio_350_450)*sf_350_450;
  cout << "Data 350-450           = " << data_350_450 << endl;
  cout << "Data Ratio             = " << data_ratio_350_450 << endl;
  cout << "Err Data Ratio 350-450 = " << binErr_350_450 << endl;
  cout << "MC 350-450             = " << mc_350_450 << endl;
  cout << "Data/MC 350-450        = " << data_350_450/mc_350_450 << endl;
  cout << "SF 350-450             = " << sf_350_450 << endl;
  cout << "~Err SF                = " << sf_err_350_450 << endl;
  cout << endl;


  double data_450_inf   = h_data->Integral(h_data->FindBin(451.0),h_data->FindBin(549.0));
  double data_ratio_450_inf  = data_450_inf/data_incl;
  double binErr_450_inf = sqrt( (data_ratio_450_inf*(1-data_ratio_450_inf))/data_incl );
  double mc_450_inf = h_all_mc_nom->Integral(h_all_mc_nom->FindBin(451.0),h_all_mc_nom->FindBin(549.0));
  double sf_450_inf = (data_450_inf/mc_450_inf)/sf_incl;
  double sf_err_450_inf = (binErr_450_inf/data_ratio_450_inf)*sf_450_inf;
  cout << "Data 450-inf           = " << data_450_inf << endl;
  cout << "Data Ratio             = " << data_ratio_450_inf << endl;
  cout << "Err Data Ratio 450-inf = " << binErr_450_inf << endl;
  cout << "MC 450-inf             = " << mc_450_inf << endl;
  cout << "Data/MC 450-inf        = " << data_450_inf/mc_450_inf << endl;
  cout << "SF 450-inf             = " << sf_450_inf << endl;
  cout << "~Err SF                = " << sf_err_450_inf << endl;
  cout << endl;


  cout << "Scale Factors and Binomial Errors: " << endl;
  cout << "    250-350 = " << sf_250_350 << " +/- " << sf_err_250_350 << " (" << 100*sf_err_250_350/sf_250_350 << "%)" << endl;
  cout << "    350-450 = " << sf_350_450 << " +/- " << sf_err_350_450 << " (" << 100*sf_err_350_450/sf_350_450 << "%)" << endl;
  cout << "    450-inf = " << sf_450_inf << " +/- " << sf_err_450_inf << " (" << 100*sf_err_450_inf/sf_450_inf << "%)" << endl;
  cout << endl;


  TH1D *h_sf = (TH1D*)h_ratio->Clone("h_sf");
  for(int iBin=1; iBin<=(int)h_sf->GetNbinsX(); iBin++){
    double data_incl_yield = h_data->Integral(iBin, h_data->GetNbinsX());
    double data_bin_yield = h_data->GetBinContent(iBin);
    double data_ratio = data_bin_yield/data_incl_yield;
    double bin_bin_err = sqrt( data_ratio*(1-data_ratio)/data_incl_yield );
    double percent_err = bin_bin_err/data_ratio;
    h_sf->SetBinError(iBin, h_sf->GetBinContent(iBin)*percent_err);
  }

  
  double metBegin = 150.0;
  double metEnd   = 550.0;
  TFitResultPtr r = h_ratio->Fit("pol1","S","",metBegin,metEnd);
  TF1 *fit = (TF1*)h_ratio->GetFunction("pol1");
  //h_sf->Fit("pol1","FEM","",metBegin,metEnd);
  //TF1 *fit = (TF1*)h_sf->GetFunction("pol1");
  double b = fit->GetParameter(0);
  double b_err = fit->GetParError(0);
  double m = fit->GetParameter(1);
  double m_err = fit->GetParError(1);
  cout << "Fit Results: y = " << m << "x + " << b << endl;

  double fit_300 = m*300+b;
  double err_300 = sqrt( pow(m*300*sqrt( pow(m_err/m,2) ),2)+pow(b_err,2) );
  double sf_300 = fit_300/sf_incl;
  //double err_sf_300 = sf_300*sqrt( pow(1/sqrt(data_incl),2) + pow(err_300/fit_300,2) );
  //double err_sf_300 = sf_300*sqrt( pow(err_300/fit_300,2) );
  //double err_sf_300 = (binErr_250_350/data_ratio_250_350)*sf_300;
  double fit_yield_300 = fit->Integral(250.0,350.0);
  double fit_error_300 = fit->IntegralError(250.0,350.0,r->GetParams(), r->GetCovarianceMatrix().GetMatrixArray() );
  double err_sf_300 = (fit_error_300/fit_yield_300)*sf_300;

  double fit_400 = m*400+b;
  double err_400 = sqrt( pow(m*400*sqrt( pow(m_err/m,2) ),2)+pow(b_err,2) );
  double sf_400 = fit_400/sf_incl;
  //double err_sf_400 = sf_400*sqrt( pow(1/sqrt(data_incl),2) + pow(err_400/fit_400,2) );
  //double err_sf_400 = sf_400*sqrt( pow(err_400/fit_400,2) );
  //double err_sf_400 = (binErr_350_450/data_ratio_350_450)*sf_400;
  double fit_yield_400 = fit->Integral(350.0,450.0);
  double fit_error_400 = fit->IntegralError(350.0,450.0,r->GetParams(), r->GetCovarianceMatrix().GetMatrixArray() );
  double err_sf_400 = (fit_error_400/fit_yield_400)*sf_400;

  double fit_500 = m*500+b;
  double err_500 = sqrt( pow(m*500*sqrt( pow(m_err/m,2) ),2)+pow(b_err,2) );
  double sf_500 = fit_500/sf_incl;
  //double err_sf_500 = sf_500*sqrt( pow(1/sqrt(data_incl),2) + pow(err_500/fit_500,2) );
  //double err_sf_500 = sf_500*sqrt( pow(err_500/fit_500,2) );
  //double err_sf_500 = (binErr_450_inf/data_ratio_450_inf)*sf_500;
  double fit_yield_500 = fit->Integral(450.0,550.0);
  double fit_error_500 = fit->IntegralError(450.0,550.0,r->GetParams(), r->GetCovarianceMatrix().GetMatrixArray() );
  double err_sf_500 = (fit_error_500/fit_yield_500)*sf_500;

  cout << "Scale Factors and error from fit: " << endl;
  cout << "  MET=300: sf = " << sf_300 << " +/- " << err_sf_300 << " (" << 100.0*err_sf_300/sf_300 << "%)" << endl;
  cout << "  MET=400: sf = " << sf_400 << " +/- " << err_sf_400 << " (" << 100.0*err_sf_400/sf_400 << "%)" << endl;
  cout << "  MET=500: sf = " << sf_500 << " +/- " << err_sf_500 << " (" << 100.0*err_sf_500/sf_500 << "%)" << endl;
  
  
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

  TFile *f_out = new TFile("histos__"+hName+".root", "recreate");
  h_data->SetDirectory(f_out);
  h_mc_ttv->SetDirectory(f_out);
  h_mc_wjets->SetDirectory(f_out);
  h_mc_dyjets->SetDirectory(f_out);
  h_mc_singleT->SetDirectory(f_out);
  h_mc_ttbar->SetDirectory(f_out);
  h_mc_band->SetDirectory(f_out);
  h_ratio->SetDirectory(f_out);
  h_ratio_band->SetDirectory(f_out);
  //fit->SetDirectory(f_out);
  f_out->Write();
  f_out->Close();

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
