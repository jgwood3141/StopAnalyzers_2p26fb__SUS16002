// ROOT
#include "TFile.h"
#include "TH1.h"
#include "TString.h"

// std
#include <vector>

// histoHelper
#include "../StopBabyAnalyzer/histoHelper.h"


//
// Main
//
int tableMaker_diLepton_background_CR_ratio(){

  TH1::SetDefaultSumw2();

  //
  // histoHelper for categories
  //
  histoHelper h_helper;
  
  TString hName_incl = "";
  TString hName_1lep = "";
  TString hName_2lep = "";
  TString hName_ZtoNuNu = "";

  for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){
    if( h_helper.classifications[iClassy]->id == k_incl ){
      hName_incl = h_helper.classifications[iClassy]->label;
    }
    if( h_helper.classifications[iClassy]->id == k_ee1lep ){
      hName_1lep = h_helper.classifications[iClassy]->label;
    }
    if( h_helper.classifications[iClassy]->id == k_ge2lep ){
      hName_2lep = h_helper.classifications[iClassy]->label;
    }
    if( h_helper.classifications[iClassy]->id == k_ZtoNuNu ){
      hName_ZtoNuNu = h_helper.classifications[iClassy]->label;
    }

  }


  TString hName_nominal_sys = "";
  for(int iSys=0; iSys<(int)h_helper.systematics.size(); iSys++){
    if( h_helper.systematics[iSys]->id == k_nominal ){
      hName_nominal_sys = h_helper.systematics[iSys]->label;
    }
  }


  //
  // Scale Factors, Evt. Weights
  //
  double K3 = 1.10;
  double K3_err = 0.06;
  double K4 = 0.94;
  double K4_err = 0.06;

  //
  // Open Files
  //
  TString inDir_SR       = "../StopBabyAnalyzer/Histos/Nominal/";
  TString inDir_SR_JESup = "../StopBabyAnalyzer/Histos/JESup/";
  TString inDir_SR_JESdn = "../StopBabyAnalyzer/Histos/JESdown/";
  
  TString inDir_CR       = "Histos/Nominal/";
  TString inDir_CR_JESup = "Histos/JESup/";
  TString inDir_CR_JESdn = "Histos/JESdown/";

  TString outDir = "Plots/";
  

  //
  // backgrounds
  //

  // Signal Region
  TFile *f_SR       = new TFile(inDir_SR+"histos__allBkg_25ns.root", "read");
  TFile *f_SR_JESup = new TFile(inDir_SR_JESup+"histos__allBkg_25ns.root", "read");
  TFile *f_SR_JESdn = new TFile(inDir_SR_JESdn+"histos__allBkg_25ns.root", "read");
  TString h_classy_SR = hName_2lep;
    

  // diLepton CR Region
  TFile *f_CR       = new TFile(inDir_CR+"histos__allBkg_25ns.root", "read");
  TFile *f_CR_JESup = new TFile(inDir_CR_JESup+"histos__allBkg_25ns.root", "read");
  TFile *f_CR_JESdn = new TFile(inDir_CR_JESdn+"histos__allBkg_25ns.root", "read");
  //TString h_classy_CR = hName_2lep;
  TString h_classy_CR = hName_incl;
  
  
  // diLepton data
  //TFile *f_data_CR = new TFile(inDir_CR+"histos__allBkg_25ns.root", "read");
  TFile *f_data_CR = new TFile(inDir_CR+"histos__data_singleEl_singleMu_2015CD_25ns.root", "read");
  TString h_classy_CR_data = hName_incl;


 
  //
  // Signal Region Categories
  //
  TString sr_cat_incl = "baseline";

  std::vector<TString> sr_cat_labels;
  sr_cat_labels.push_back("lowDM__met_250_325");
  sr_cat_labels.push_back("lowDM__met_325_inf");
  sr_cat_labels.push_back("highDM__met_250_350");
  sr_cat_labels.push_back("highDM__met_350_450");
  sr_cat_labels.push_back("highDM__met_450_inf");
  sr_cat_labels.push_back("highDM__ee3j__met_250_350");
  sr_cat_labels.push_back("highDM__ee3j__met_350_inf");
  sr_cat_labels.push_back("compDM__ee2j__met_250_350");
  sr_cat_labels.push_back("compDM__ee2j__met_350_inf");
  
  std::vector<TString> sr_cat_tex;
  sr_cat_tex.push_back("$Low {\\Delta}M, 250<MET<325$");
  sr_cat_tex.push_back("$Low {\\Delta}M, MET>325$");
  sr_cat_tex.push_back("$High {\\Delta}M, 250<MET<350$");
  sr_cat_tex.push_back("$High {\\Delta}M, 350<MET<450$");
  sr_cat_tex.push_back("$High {\\Delta}M, MET>450$");
  sr_cat_tex.push_back("$High {\\Delta}M, ==3jets, 250<MET<350$");
  sr_cat_tex.push_back("$High {\\Delta}M, ==3jets, MET>350$");
  sr_cat_tex.push_back("$Compressed {\\Delta}M, ==2jets, 250<MET<350$");
  sr_cat_tex.push_back("$Compressed {\\Delta}M, ==2jets, MET>350$");
  

  const int nSRs = (int)sr_cat_labels.size();

  
  std::vector<TString> cr_cat_labels;
  cr_cat_labels.push_back("ge3j_ge250met_lt200mt2w");
  cr_cat_labels.push_back("ge3j_ge250met_lt200mt2w");
  cr_cat_labels.push_back("ge3j_ge250met_ge200mt2w");
  cr_cat_labels.push_back("ge3j_ge250met_ge200mt2w");
  cr_cat_labels.push_back("ge3j_ge250met_ge200mt2w");
  cr_cat_labels.push_back("ge3j_ge250met_ge200mt2w");
  cr_cat_labels.push_back("ge3j_ge250met_ge200mt2w");
  cr_cat_labels.push_back("ee2j_ge250met_ge6p4modTop");
  cr_cat_labels.push_back("ee2j_ge250met_ge6p4modTop");
  
  /*
  std::vector< std::pair<double,double> > sr_cat_met_res_SFs;
  std::pair<double,double> sr_met_res_SF;
  sr_met_res_SF.first = 1.048;  sr_met_res_SF.second = 0.025;
  sr_cat_met_res_SFs.push_back( sr_met_res_SF );
  sr_met_res_SF.first = 0.944;  sr_met_res_SF.second = 0.029;
  sr_cat_met_res_SFs.push_back( sr_met_res_SF );
  sr_met_res_SF.first = 1.050;  sr_met_res_SF.second = 0.021;
  sr_cat_met_res_SFs.push_back( sr_met_res_SF );
  sr_met_res_SF.first = 0.910;  sr_met_res_SF.second = 0.051;
  sr_cat_met_res_SFs.push_back( sr_met_res_SF );
  sr_met_res_SF.first = 0.924;  sr_met_res_SF.second = 0.063;
  sr_cat_met_res_SFs.push_back( sr_met_res_SF );
  sr_met_res_SF.first = 1.032;  sr_met_res_SF.second = 0.014;
  sr_cat_met_res_SFs.push_back( sr_met_res_SF );
  sr_met_res_SF.first = 0.928;  sr_met_res_SF.second = 0.030;
  sr_cat_met_res_SFs.push_back( sr_met_res_SF );
  sr_met_res_SF.first = 1.032;  sr_met_res_SF.second = 0.009;
  sr_cat_met_res_SFs.push_back( sr_met_res_SF );
  sr_met_res_SF.first = 0.913;  sr_met_res_SF.second = 0.024;
  sr_cat_met_res_SFs.push_back( sr_met_res_SF );


  
  bool doMetResScaling = false;
  bool doMetResUncOnly = false;

  if( doMetResScaling && doMetResUncOnly ){
    cout << "can't set both met res scaling and met res uncertainty only..." << endl;
    return 1;
  }
  */
  
  std::vector<TString> sys_limit_labels;
  sys_limit_labels.push_back("lumiup");
  sys_limit_labels.push_back("lumidown");
  sys_limit_labels.push_back("Bup_HF");
  sys_limit_labels.push_back("Bdown_HF");
  sys_limit_labels.push_back("Bup_LF");
  sys_limit_labels.push_back("Bdown_LF");
  sys_limit_labels.push_back("LepEffup");
  sys_limit_labels.push_back("LepEffdown");
  //sys_limit_labels.push_back("TopPtup");
  //sys_limit_labels.push_back("TopPtdown");
  sys_limit_labels.push_back("nJetsSFK3up");
  sys_limit_labels.push_back("nJetsSFK3down");
  sys_limit_labels.push_back("nJetsSFK4up");
  sys_limit_labels.push_back("nJetsSFK4down");
  sys_limit_labels.push_back("PDFup");
  sys_limit_labels.push_back("PDFdown");
  sys_limit_labels.push_back("Alphasup");
  sys_limit_labels.push_back("Alphasdown");
  sys_limit_labels.push_back("muRFup");
  sys_limit_labels.push_back("muRFdown");
  /*
  sys_limit_labels.push_back("metRes_ee2j_met_250_350_up");
  sys_limit_labels.push_back("metRes_ee2j_met_250_350_down");
  sys_limit_labels.push_back("metRes_ee2j_met_350_inf_up");
  sys_limit_labels.push_back("metRes_ee2j_met_350_inf_down");
  sys_limit_labels.push_back("metRes_ee3j_met_250_350_up");
  sys_limit_labels.push_back("metRes_ee3j_met_250_350_down");
  sys_limit_labels.push_back("metRes_ee3j_met_350_inf_up");
  sys_limit_labels.push_back("metRes_ee3j_met_350_inf_down");
  sys_limit_labels.push_back("metRes_ge4j_lt200mt2w_met_250_325_up");
  sys_limit_labels.push_back("metRes_ge4j_lt200mt2w_met_250_325_down");
  sys_limit_labels.push_back("metRes_ge4j_lt200mt2w_met_325_inf_up");
  sys_limit_labels.push_back("metRes_ge4j_lt200mt2w_met_325_inf_down");
  sys_limit_labels.push_back("metRes_ge4j_ge200mt2w_met_250_350_up");
  sys_limit_labels.push_back("metRes_ge4j_ge200mt2w_met_250_350_down");
  sys_limit_labels.push_back("metRes_ge4j_ge200mt2w_met_350_450_up");
  sys_limit_labels.push_back("metRes_ge4j_ge200mt2w_met_350_450_down");
  sys_limit_labels.push_back("metRes_ge4j_ge200mt2w_met_450_inf_up");
  sys_limit_labels.push_back("metRes_ge4j_ge200mt2w_met_450_inf_down");
  sys_limit_labels.push_back("diNuSF_met_250_350_up");
  sys_limit_labels.push_back("diNuSF_met_250_350_down");
  sys_limit_labels.push_back("diNuSF_met_350_450_up");
  sys_limit_labels.push_back("diNuSF_met_350_450_down");
  sys_limit_labels.push_back("diNuSF_met_450_inf_up");
  sys_limit_labels.push_back("diNuSF_met_450_inf_down");
  */
  sys_limit_labels.push_back("metRESup");
  sys_limit_labels.push_back("metRESdown");
  sys_limit_labels.push_back("diNuSFup");
  sys_limit_labels.push_back("diNuSFdown");
  
  std::vector<TString> sys_labels;
  sys_labels.push_back("lumi_scaleUp");
  sys_labels.push_back("lumi_scaleDown");
  sys_labels.push_back("bTagEffHF_scaleUp");
  sys_labels.push_back("bTagEffHF_scaleDown");
  sys_labels.push_back("bTagEffLF_scaleUp");
  sys_labels.push_back("bTagEffLF_scaleDown");
  sys_labels.push_back("lepSF_scaleUp");
  sys_labels.push_back("lepSF_scaleDown");
  //sys_labels.push_back("topPt_scaleUp");
  //sys_labels.push_back("topPt_scaleDown");
  sys_labels.push_back("nJetsSFK3_scaleUp");
  sys_labels.push_back("nJetsSFK3_scaleDown");
  sys_labels.push_back("nJetsSFK4_scaleUp");
  sys_labels.push_back("nJetsSFK4_scaleDown");
  sys_labels.push_back("pdf_scaleUp");
  sys_labels.push_back("pdf_scaleDown");
  sys_labels.push_back("alphaS_scaleUp");
  sys_labels.push_back("alphaS_scaleDown");
  sys_labels.push_back("q2_scaleUp");
  sys_labels.push_back("q2_scaleDown");
  /*
  sys_labels.push_back("metRes_ee2j_met_250_350_scaleUp");
  sys_labels.push_back("metRes_ee2j_met_250_350_scaleDown");
  sys_labels.push_back("metRes_ee2j_met_350_inf_scaleUp");
  sys_labels.push_back("metRes_ee2j_met_350_inf_scaleDown");
  sys_labels.push_back("metRes_ee3j_met_250_350_scaleUp");
  sys_labels.push_back("metRes_ee3j_met_250_350_scaleDown");
  sys_labels.push_back("metRes_ee3j_met_350_inf_scaleUp");
  sys_labels.push_back("metRes_ee3j_met_350_inf_scaleDown");
  sys_labels.push_back("metRes_ge4j_lt200mt2w_met_250_325_scaleUp");
  sys_labels.push_back("metRes_ge4j_lt200mt2w_met_250_325_scaleDown");
  sys_labels.push_back("metRes_ge4j_lt200mt2w_met_325_inf_scaleUp");
  sys_labels.push_back("metRes_ge4j_lt200mt2w_met_325_inf_scaleDown");
  sys_labels.push_back("metRes_ge4j_ge200mt2w_met_250_350_scaleUp");
  sys_labels.push_back("metRes_ge4j_ge200mt2w_met_250_350_scaleDown");
  sys_labels.push_back("metRes_ge4j_ge200mt2w_met_350_450_scaleUp");
  sys_labels.push_back("metRes_ge4j_ge200mt2w_met_350_450_scaleDown");
  sys_labels.push_back("metRes_ge4j_ge200mt2w_met_450_inf_scaleUp");
  sys_labels.push_back("metRes_ge4j_ge200mt2w_met_450_inf_scaleDown");
  sys_labels.push_back("diNuSF_met_250_350_scaleUp");
  sys_labels.push_back("diNuSF_met_250_350_scaleDown");
  sys_labels.push_back("diNuSF_met_350_450_scaleUp");
  sys_labels.push_back("diNuSF_met_350_450_scaleDown");
  sys_labels.push_back("diNuSF_met_450_inf_scaleUp");
  sys_labels.push_back("diNuSF_met_450_inf_scaleDown");
  */
  sys_labels.push_back("metRes_scaleUp");
  sys_labels.push_back("metRes_scaleDown");
  sys_labels.push_back("diNuSF_scaleUp");
  sys_labels.push_back("diNuSF_scaleDown");
  
  std::vector<TString> sys_tex;
  sys_tex.push_back("Luminosity");
  sys_tex.push_back("Luminosity");
  sys_tex.push_back("bTag~Efficiency,~Heavy~Flavour");
  sys_tex.push_back("bTag~Efficiency,~Heavy~Flavour");
  sys_tex.push_back("bTag~Efficiency,~Light~Flavour");
  sys_tex.push_back("bTag~Efficiency,~Light~Flavour");
  sys_tex.push_back("lepton~SF");
  sys_tex.push_back("lepton~SF");
  //sys_tex.push_back("top~p_{T}~SF");
  //sys_tex.push_back("top~p_{T}~SF");
  sys_tex.push_back("nJets~SF,~K3");
  sys_tex.push_back("nJets~SF,~K3");
  sys_tex.push_back("nJets~SF,~K4");
  sys_tex.push_back("nJets~SF,~K4");
  sys_tex.push_back("PDF");
  sys_tex.push_back("PDF");
  sys_tex.push_back("\\alpha_{S}");
  sys_tex.push_back("\\alpha_{S}");
  sys_tex.push_back("Q^{2}");
  sys_tex.push_back("Q^{2}");
  /*
  sys_tex.push_back("MET Resolution,~2j,~250<MET<350");
  sys_tex.push_back("MET Resolution,~2j,~250<MET<350");
  sys_tex.push_back("MET Resolution,~2j,~MET>350");
  sys_tex.push_back("MET Resolution,~2j,~MET>350");
  sys_tex.push_back("MET Resolution,~3j,~250<MET<350");
  sys_tex.push_back("MET Resolution,~3j,~250<MET<350");
  sys_tex.push_back("MET Resolution,~3j,~MET>350");
  sys_tex.push_back("MET Resolution,~3j,~MET>350");
  sys_tex.push_back("MET Resolution,~\\ge4j,~MT2W<200,~250<MET<325");
  sys_tex.push_back("MET Resolution,~\\ge4j,~MT2W<200,~250<MET<325");
  sys_tex.push_back("MET Resolution,~\\ge4j,~MT2W<200,~MET\\ge325");
  sys_tex.push_back("MET Resolution,~\\ge4j,~MT2W<200,~MET\\ge325");
  sys_tex.push_back("MET Resolution,~\\ge4j,~MT2W\\ge200,~250<MET<350");
  sys_tex.push_back("MET Resolution,~\\ge4j,~MT2W\\ge200,~250<MET<350");
  sys_tex.push_back("MET Resolution,~\\ge4j,~MT2W\\ge200,~350<MET<450");
  sys_tex.push_back("MET Resolution,~\\ge4j,~MT2W\\ge200,~350<MET<450");
  sys_tex.push_back("MET Resolution,~\\ge4j,~MT2W\\ge200,~MET\\ge450");
  sys_tex.push_back("MET Resolution,~\\ge4j,~MT2W\\ge200,~MET\\ge450");
  sys_tex.push_back("diNuetrino SF,~250<MET<350");
  sys_tex.push_back("diNuetrino SF,~250<MET<350");
  sys_tex.push_back("diNuetrino SF,~350<MET<450");
  sys_tex.push_back("diNuetrino SF,~350<MET<450");
  sys_tex.push_back("diNuetrino SF,~MET>450");
  sys_tex.push_back("diNuetrino SF,~MET>450");
  */
  sys_tex.push_back("MET Resolution");
  sys_tex.push_back("MET Resolution");
  sys_tex.push_back("diNuetrino~SF");
  sys_tex.push_back("diNuetrino~SF");
  
  //const int nSys = (int)sys_labels.size() + 5; // +1 for nominal, +2 for JES, +2 for metRes
  const int nSys = (int)sys_labels.size() + 3; // +1 for nominal, +2 for JES


  // Output file for ratio
  TFile  *f_out = new TFile(inDir_CR+"histos__diLepton_Bkg_Estimate_25ns.root", "recreate");

  // Histograms for limit setting
  TH1D *h_SR[nSys];
  h_SR[0] = new TH1D("CR2lyield", "CR2lyield", nSRs, 0.0, nSRs); // Nominal
  for(int iCat=0; iCat<(int)nSRs; iCat++) h_SR[0]->GetXaxis()->SetBinLabel( iCat+1, sr_cat_labels[iCat].Data() );
  h_SR[0]->SetDirectory(f_out);
  // Systematics from vectors
  for(int iSys=0; iSys<(int)sys_labels.size(); iSys++){
    h_SR[iSys+1] = new TH1D(Form("CR2l_%s",sys_limit_labels[iSys].Data()), Form("CR2l_%s",sys_limit_labels[iSys].Data()), nSRs, 0.0, nSRs);   
    for(int iCat=0; iCat<(int)nSRs; iCat++) h_SR[iSys+1]->GetXaxis()->SetBinLabel( iCat+1, sr_cat_labels[iCat].Data() );
    h_SR[iSys+1]->SetDirectory(f_out);
  }
  /*
  // MET resolution
  h_SR[nSys-2] = new TH1D("CR2l_metResup", "CR2l_metResup", nSRs, 0.0, nSRs);
  for(int iCat=0; iCat<(int)nSRs; iCat++) h_SR[nSys-2]->GetXaxis()->SetBinLabel( iCat+1, sr_cat_labels[iCat].Data() );
  h_SR[nSys-2]->SetDirectory(f_out);
  h_SR[nSys-1] = new TH1D("CR2l_metResdown", "CR2l_metResdown", nSRs, 0.0, nSRs);
  for(int iCat=0; iCat<(int)nSRs; iCat++) h_SR[nSys-1]->GetXaxis()->SetBinLabel( iCat+1, sr_cat_labels[iCat].Data() );
  h_SR[nSys-1]->SetDirectory(f_out);
  */
  // JES
  h_SR[nSys-2] = new TH1D("CR2l_JESup", "CR2l_JESup", nSRs, 0.0, nSRs);
  for(int iCat=0; iCat<(int)nSRs; iCat++) h_SR[nSys-4]->GetXaxis()->SetBinLabel( iCat+1, sr_cat_labels[iCat].Data() );
  h_SR[nSys-2]->SetDirectory(f_out);
  h_SR[nSys-1] = new TH1D("CR2l_JESdown", "CR2l_JESdown", nSRs, 0.0, nSRs);
  for(int iCat=0; iCat<(int)nSRs; iCat++) h_SR[nSys-3]->GetXaxis()->SetBinLabel( iCat+1, sr_cat_labels[iCat].Data() );
  h_SR[nSys-1]->SetDirectory(f_out);
  

  //
  // Make Tables
  //


  // ROW=Categories, COL=DiLepton Estimate and Components
  FILE *yFile;
  TString texFile = outDir;
  texFile += "ratioTable_signalRegion_over_dileptonControlRegion_stop_1l.tex";
  yFile = fopen(texFile.Data(), "w");

  cout << "Writing file of diLepton Estimates to file; " << endl;
  cout << "    " << texFile << endl;

  // Tex File Formatting
  fprintf(yFile, "\\documentclass{article}\n");
  fprintf(yFile, "\\usepackage[landscape]{geometry}\n");
  fprintf(yFile, "\\usepackage{chngpage}\n\n");
  fprintf(yFile, "\\usepackage{graphicx} \n\n");
  fprintf(yFile, "\\begin{document}\n");
  fprintf(yFile, "\\tiny\n");  //fprintf(yFile, "\\small\n");
  fprintf(yFile, "\\begin{table} \n");
  fprintf(yFile, "\\caption{ diLepton Background Estimate and Components, for each Signal Region } \n");
  fprintf(yFile, "\\scalebox{1.0}{ \n");
  fprintf(yFile, "\\begin{tabular}{|l|c|c|c|c|c|c|c|} \\hline \n");
  fprintf(yFile, "Category & $M_{MET,nJet~bin}^{SR}$ & $N_{Incl}^{CR}$ & $M_{Incl}^{CR}$ & $M_{2\\ell}^{SR}$ & $M_{2\\ell}^{SR}/M_{Incl}^{CR}$ & $M_{MET,nJet~bin}^{SR}/M_{2\\ell}^{SR}$ & $N_{2\\ell,estimate}^{SR}$");
  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \\hline \n");



  // ROW=Categories, COL=DiLepton Estimate and Components, Simple
  FILE *yFile2;
  texFile = outDir;
  texFile += "ratioTable_signalRegion_over_dileptonControlRegion_stop_1l__simple.tex";
  yFile2 = fopen(texFile.Data(), "w");

  cout << "Writing simple file of diLepton Estimates to file; " << endl;
  cout << "    " << texFile << endl;

  // Tex File Formatting
  fprintf(yFile2, "\\documentclass{article}\n");
  fprintf(yFile2, "\\usepackage[landscape]{geometry}\n");
  fprintf(yFile2, "\\usepackage{chngpage}\n\n");
  fprintf(yFile2, "\\usepackage{graphicx} \n\n");
  fprintf(yFile2, "\\begin{document}\n");
  fprintf(yFile2, "\\tiny\n");  //fprintf(yFile2, "\\small\n");
  fprintf(yFile2, "\\begin{table} \n");
  fprintf(yFile2, "\\caption{ diLepton Background Estimate and Components, for each Signal Region } \n");
  fprintf(yFile2, "\\scalebox{1.0}{ \n");
  fprintf(yFile2, "\\begin{tabular}{|l|c|c|c|c||} \\hline \n");
  fprintf(yFile2, "Category & $N_{Incl}^{CR}$ & $M_{2\\ell}^{SR}/M_{Incl}^{CR}$ & $M_{MET,nJet~bin}^{SR}/M_{2\\ell}^{SR}$ & $N_{2\\ell,estimate}^{SR}$");
  fprintf(yFile2, "\\"); fprintf(yFile2, "\\ \\hline \\hline \n");



  
  // ROW=Uncertainties, COL=DiLepton Estimate and Components, Simple
  FILE *uncFileSummary;
  TString uncFileSummaryName = outDir;
  uncFileSummaryName += "ratioTable_signalRegion_over_dileptonControlRegion_stop_1l__uncertaintyTable__summary.tex";
  uncFileSummary = fopen(uncFileSummaryName.Data(), "w");
    
  cout << "Writing table of diLepton uncertainties to: " << endl;
  cout << "    " << uncFileSummaryName << endl;

  // Tex File Formatting
  fprintf(uncFileSummary, "\\documentclass{article}\n");
  fprintf(uncFileSummary, "\\usepackage[landscape]{geometry}\n");
  fprintf(uncFileSummary, "\\usepackage{chngpage}\n\n");
  fprintf(uncFileSummary, "\\usepackage{graphicx} \n\n");
  fprintf(uncFileSummary, "\\begin{document}\n");
  fprintf(uncFileSummary, "\\tiny \n"); //fprintf(uncFileSummary, "\\small \n");
  fprintf(uncFileSummary, "\\begin{table} \n");
  fprintf(uncFileSummary, "\\caption{ Summary of diLepton Background Estimate Uncertainties } \n");
  fprintf(uncFileSummary, "\\scalebox{0.7}{ \n");
  fprintf(uncFileSummary, "\\begin{tabular}{|l|c|c|c|c|} \\hline \n");
  fprintf(uncFileSummary, "Systematic & $N_{Incl}^{CR},~(\\%%)$ & $M_{2\\ell}^{SR}/M_{Incl}^{CR},~(\\%%)$ & $M_{MET,nJet~bin}^{SR}/M_{2\\ell}^{SR},~(\\%%)$ & $N_{2\\ell,estimate}^{SR},~(\\%%)$ ");
  fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \\hline \n");


  //const int nSys_unique = ( (nSys-1)/2)+3; // nSys has nominal so -1, then nSys has up/down in list, jes and metRes, so 1/2 for unique, +3 for data stats, mc stats, and total
  const int nSys_unique = ( (nSys-1)/2)+3; // nSys has nominal so -1, then nSys has up/down in list, jes, so 1/2 for unique, +3 for data stats, mc stats, and total
  double uncMax_cr_data_incl[nSys_unique]; 
  double uncMin_cr_data_incl[nSys_unique];
  double uncMax_ratio[nSys_unique]; 
  double uncMin_ratio[nSys_unique];
  double uncMax_tf[nSys_unique]; 
  double uncMin_tf[nSys_unique];
  double uncMax_sr_estimate[nSys_unique]; 
  double uncMin_sr_estimate[nSys_unique];
  for(int iSys=0; iSys<nSys_unique; iSys++){
    uncMax_cr_data_incl[iSys] = 0.0;
    uncMin_cr_data_incl[iSys] = 999.9;
    uncMax_ratio[iSys] = 0.0;
    uncMin_ratio[iSys] = 999.9;
    uncMax_tf[iSys] = 0.0;
    uncMin_tf[iSys] = 999.9;
    uncMax_sr_estimate[iSys] = 0.0;
    uncMin_sr_estimate[iSys] = 999.9;
  }

   
  //
  // Loop over categories to get Inclusive CR yields
  //
  TH1D *h_temp = NULL;

  TString hName = "h__yields__";

  TString hName_CR = "";
  TString hName_SR = "";

  for(int iSR=0; iSR<(int)sr_cat_tex.size(); iSR++){
    
    // ROW=Uncertainties, COL=DiLepton Estimate and Components, Simple
    FILE *uncFile;
    TString uncFileName = outDir;
    uncFileName += "ratioTable_signalRegion_over_dileptonControlRegion_stop_1l__uncertaintyTable__";
    uncFileName += sr_cat_labels[iSR];
    uncFileName += ".tex";
    uncFile = fopen(uncFileName.Data(), "w");
    
    cout << "Writing table of diLepton uncertainties to: " << endl;
    cout << "    " << uncFileName << endl;

    // Tex File Formatting
    fprintf(uncFile, "\\documentclass{article}\n");
    fprintf(uncFile, "\\usepackage[landscape]{geometry}\n");
    fprintf(uncFile, "\\usepackage{chngpage}\n\n");
    fprintf(uncFile, "\\usepackage{graphicx} \n\n");
    fprintf(uncFile, "\\begin{document}\n");
    fprintf(uncFile, "\\tiny \n"); //fprintf(uncFile, "\\small \n");
    fprintf(uncFile, "\\begin{table} \n");
    fprintf(uncFile, "\\caption{ diLepton Background Estimate Uncertainties, for %s } \n", sr_cat_tex[iSR].Data());
    fprintf(uncFile, "\\scalebox{0.7}{ \n");
    fprintf(uncFile, "\\begin{tabular}{|l|c|c|c|c|} \\hline \n");
    fprintf(uncFile, "Systematic & $N_{Incl}^{CR}$ & $M_{2\\ell}^{SR}/M_{Incl}^{CR},~(SysUp,~SysDn)~$ & $M_{MET,nJet~bin}^{SR}/M_{2\\ell}^{SR},~(SysUp,~SysDn)~$ & $N_{2\\ell,estimate}^{SR},~(SysUp,~SysDn)~$ ");
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \n");

  

    // ROW=Uncertainties, COL=DiLepton Estimate and Components
    FILE *uncFile2;
    TString uncFile2Name = outDir;
    uncFile2Name += "ratioTable_signalRegion_over_dileptonControlRegion_stop_1l__uncertaintyTable__fullCalc__";
    uncFile2Name += sr_cat_labels[iSR];
    uncFile2Name += ".tex";
    uncFile2 = fopen(uncFile2Name.Data(), "w");
    
    cout << "Writing table of diLepton uncertainties to: " << endl;
    cout << "    " << uncFile2Name << endl;

    // Tex File Formatting
    fprintf(uncFile2, "\\documentclass{article}\n");
    fprintf(uncFile2, "\\usepackage[landscape]{geometry}\n");
    fprintf(uncFile2, "\\usepackage{chngpage}\n\n");
    fprintf(uncFile2, "\\usepackage{graphicx} \n\n");
    fprintf(uncFile2, "\\begin{document}\n");
    fprintf(uncFile2, "\\tiny \n"); //fprintf(uncFile2, "\\small \n");
    fprintf(uncFile2, "\\begin{table} \n");
    fprintf(uncFile2, "\\caption{ diLepton Background Estimate Uncertainties, for %s } \n", sr_cat_tex[iSR].Data());
    fprintf(uncFile2, "\\scalebox{0.6}{ \n");
    fprintf(uncFile2, "\\begin{tabular}{|l|c|c|c|c|c|c|c|} \\hline \n");
    fprintf(uncFile2, "Systematic & $N_{Incl}^{CR},~(\\%%)$ & $M_{2\\ell}^{SR},~(\\%%)$ & $M_{Incl}^{CR},~(\\%%)$ & $M_{2\\ell}^{SR}/M_{Incl}^{CR},~(\\%%)$ & $M_{MET,nJet~bin}^{SR},~(\\%%)$ & $M_{MET,nJet~bin}^{SR}/M_{2\\ell}^{SR},~(\\%%)$ & $N_{2\\ell,estimate}^{SR},~(\\%%)$ ");
    fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \n");
    
    

    // Category Name for tables
    fprintf(yFile, " %s & ", sr_cat_tex[iSR].Data() );
    fprintf(yFile2, " %s & ", sr_cat_tex[iSR].Data() );


    //
    // Get yields, begin calculation for this cateogry
    //

    // SR, met bin 
    TString hName_SR_bin = hName;
    hName_SR_bin += h_classy_SR;
    hName_SR_bin += "__";
    hName_SR_bin += hName_nominal_sys;
    hName_SR_bin += "__";
    hName_SR_bin += sr_cat_labels[iSR];
      
    TH1D *h_SR_bin = (TH1D*)f_SR->Get(hName_SR_bin);
    if(!h_SR_bin) cout << "BAD SR BIN HISTO: " << hName_SR_bin << endl;

    double sr_bin_error = 0.0;
    double sr_bin_yield = h_SR_bin->IntegralAndError(0,-1,sr_bin_error);

    /*
    if(doMetResScaling){
      sr_bin_error *= sr_cat_met_res_SFs[iSR].first;
      sr_bin_yield *= sr_cat_met_res_SFs[iSR].first;
    }
    */
    
    // SR, incl
    TString hName_SR_incl = hName;
    hName_SR_incl += h_classy_SR;
    hName_SR_incl += "__";
    hName_SR_incl += hName_nominal_sys;
    hName_SR_incl += "__";
    hName_SR_incl += cr_cat_labels[iSR];

    TH1D *h_SR_incl = (TH1D*)f_SR->Get(hName_SR_incl);
    if(!h_SR_incl) cout << "BAD SR INCL HISTO: " << hName_SR_incl << endl;
    
    double sr_incl_error = 0.0;
    double sr_incl_yield = h_SR_incl->IntegralAndError(0,-1,sr_incl_error);;

    // CR, incl, MC
    TString hName_CR_mc = hName;
    hName_CR_mc += hName_incl;
    hName_CR_mc += "__";
    hName_CR_mc += hName_nominal_sys;
    hName_CR_mc += "__";
    hName_CR_mc += cr_cat_labels[iSR];

    TH1D *h_CR_mc = (TH1D*)f_CR->Get(hName_CR_mc);
    if(!h_CR_mc) cout << "BAD CR INCL MC HISTO: " << hName_CR_mc << endl;
    
    double cr_mc_incl_error = 0.0;
    double cr_mc_incl_yield = h_CR_mc->IntegralAndError(0,-1,cr_mc_incl_error);

    // CR, incl, Data
    TString hName_CR_data = hName;
    hName_CR_data += hName_incl;
    hName_CR_data += "__";
    hName_CR_data += hName_nominal_sys;
    hName_CR_data += "__";
    hName_CR_data += cr_cat_labels[iSR];

    TH1D *h_CR_data = (TH1D*)f_data_CR->Get(hName_CR_data);
    if(!h_CR_data) cout << "BAD CR INCL DATA HISTO: " << hName_CR_data << endl;
    
    double cr_data_incl_error = 0.0;
    double cr_data_incl_yield = h_CR_data->IntegralAndError(0,-1,cr_data_incl_error);


    // Ratio of SR/CR
    double ratio = sr_incl_yield/cr_mc_incl_yield;
    //double ratio_err = ratio*sqrt( pow( sr_incl_error/sr_incl_yield, 2 ) + pow( cr_mc_incl_error/cr_mc_incl_yield, 2 ) );
    double ratio_err = ratio*sqrt( pow( cr_mc_incl_error/cr_mc_incl_yield, 2 ) ); // avoid double counting mc stats
    double ratio_statErr = ratio_err;

    // Transfer Factor SR_bin/SR_incl
    double tf = sr_bin_yield/sr_incl_yield;
    //double tf_err = tf*sqrt( pow( sr_bin_error/sr_bin_yield, 2 ) + pow( sr_incl_error/sr_incl_yield, 2 ) );
    double tf_err = sqrt( tf*(1-tf)/h_SR_incl->GetEntries() ); // binomial errors since sr_bin_yield is a subset of sr_incl_yield

    double sr_estimate = cr_data_incl_yield*ratio*tf;
    double sr_estimate_error = sr_estimate*sqrt( pow(cr_data_incl_error/cr_data_incl_yield, 2) + pow(ratio_err/ratio, 2) + pow(tf_err/tf, 2) );
    double sr_estimate_error_mc_stats = sr_estimate*sqrt( pow(ratio_err/ratio, 2) + pow(tf_err/tf, 2) );


    // Fill histograms for limit setting
    h_SR[0]->SetBinContent( iSR+1, sr_estimate );
    h_SR[0]->SetBinError( iSR+1, sr_estimate_error );
    

    //
    // Tables for uncertainties
    //

    fprintf(uncFile, "Nominal & %.2f & %.2f & %.2f & %.2f ", cr_data_incl_yield, ratio, tf, sr_estimate );  
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \\hline \n");


    fprintf(uncFile2, "Nominal & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f ", cr_data_incl_yield, sr_incl_yield, cr_mc_incl_yield, ratio, sr_bin_yield, tf, sr_estimate );
    fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \\hline \n"); //fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \n");
    
    



    fprintf(uncFile, "Data Stats & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,%.2f),~(%.1f\\%%,~%.1f\\%%) ", cr_data_incl_yield+cr_data_incl_error, cr_data_incl_yield-cr_data_incl_error,(100*cr_data_incl_error/cr_data_incl_yield),(-100*cr_data_incl_error/cr_data_incl_yield), ratio, ratio, 0.0, 0.0, tf, tf, 0.0, 0.0, (cr_data_incl_yield+cr_data_incl_error)*ratio*tf, (cr_data_incl_yield-cr_data_incl_error)*ratio*tf,(100*(((cr_data_incl_yield+cr_data_incl_error)*ratio*tf)-sr_estimate))/sr_estimate, (100*(((cr_data_incl_yield-cr_data_incl_error)*ratio*tf)-sr_estimate))/sr_estimate );
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \n");
    

    fprintf(uncFile2, "Data Stats Up & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", cr_data_incl_yield+cr_data_incl_error, (100*cr_data_incl_error/cr_data_incl_yield), sr_incl_yield, 0.0, cr_mc_incl_yield, 0.0, ratio, 0.0, sr_bin_yield, 0.0, tf, 0.0, (cr_data_incl_yield+cr_data_incl_error)*ratio*tf, (100*(((cr_data_incl_yield+cr_data_incl_error)*ratio*tf)-sr_estimate))/sr_estimate );
    fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\  \n"); //fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \n");

    fprintf(uncFile2, "Data Stats Down & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", cr_data_incl_yield-cr_data_incl_error, (-100*cr_data_incl_error/cr_data_incl_yield), sr_incl_yield, 0.0, cr_mc_incl_yield, 0.0, ratio, 0.0, sr_bin_yield, 0.0, tf, 0.0, (cr_data_incl_yield-cr_data_incl_error)*ratio*tf, (100*(((cr_data_incl_yield-cr_data_incl_error)*ratio*tf)-sr_estimate))/sr_estimate );
    fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \n");


    uncMax_cr_data_incl[0] = std::max( uncMax_cr_data_incl[0], (100*cr_data_incl_error/cr_data_incl_yield) );
    uncMin_cr_data_incl[0] = std::min( uncMin_cr_data_incl[0], (100*cr_data_incl_error/cr_data_incl_yield) );
    uncMax_ratio[0] = std::max( uncMax_ratio[0], 0.0 );
    uncMin_ratio[0] = std::min( uncMin_ratio[0], 0.0 );
    uncMax_tf[0] = std::max( uncMax_tf[0], 0.0 );
    uncMin_tf[0] = std::min( uncMin_tf[0], 0.0 );
    uncMax_sr_estimate[0] = std::max( uncMax_sr_estimate[0], (100*(((cr_data_incl_yield+cr_data_incl_error)*ratio*tf)-sr_estimate))/sr_estimate );
    uncMin_sr_estimate[0] = std::min( uncMin_sr_estimate[0], (100*(((cr_data_incl_yield+cr_data_incl_error)*ratio*tf)-sr_estimate))/sr_estimate );




    fprintf(uncFile, "MC Stats & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,%.2f),~(%.1f\\%%,~%.1f\\%%) ", cr_data_incl_yield, cr_data_incl_yield,0.0,0.0, ratio+ratio_err, ratio-ratio_err,(100*ratio_err/ratio),(-100*ratio_err/ratio), tf+tf_err, tf-tf_err,(100*tf_err/tf),(-100*tf_err/tf), sr_estimate+sr_estimate_error_mc_stats, sr_estimate-sr_estimate_error_mc_stats,(100*sr_estimate_error_mc_stats/sr_estimate),(-100*sr_estimate_error_mc_stats/sr_estimate) );
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \n");

    
    fprintf(uncFile2, "MC Stats Up & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", cr_data_incl_yield, 0.0, sr_incl_yield+sr_incl_error, (100*sr_incl_error/sr_incl_yield), cr_mc_incl_yield+cr_mc_incl_error, (100*cr_mc_incl_error/cr_mc_incl_yield), ratio+ratio_err, (100*ratio_err/ratio), sr_bin_yield+sr_bin_error, (100*sr_bin_error/sr_bin_yield), tf+tf_err, (100*tf_err/tf), sr_estimate+sr_estimate_error_mc_stats, (100*sr_estimate_error_mc_stats/sr_estimate) );
    fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\  \n"); //fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \n");

    fprintf(uncFile2, "MC Stats Down & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ", cr_data_incl_yield, 0.0, sr_incl_yield-sr_incl_error, (-100*sr_incl_error/sr_incl_yield), cr_mc_incl_yield-cr_mc_incl_error, (-100*cr_mc_incl_error/cr_mc_incl_yield), ratio-ratio_err, (-100*ratio_err/ratio), sr_bin_yield-sr_bin_error, (-100*sr_bin_error/sr_bin_yield), tf-tf_err, (-100*tf_err/tf), sr_estimate-sr_estimate_error_mc_stats, (-100*sr_estimate_error_mc_stats/sr_estimate) );
    fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \n");


    uncMax_cr_data_incl[1] = std::max( uncMax_cr_data_incl[1], 0.0 );
    uncMin_cr_data_incl[1] = std::min( uncMin_cr_data_incl[1], 0.0 );
    uncMax_ratio[1] = std::max( uncMax_ratio[1], (100*ratio_err/ratio) );
    uncMin_ratio[1] = std::min( uncMin_ratio[1], (100*ratio_err/ratio) );
    uncMax_tf[1] = std::max( uncMax_tf[1], (100*tf_err/tf) );
    uncMin_tf[1] = std::min( uncMin_tf[1], (100*tf_err/tf) );
    uncMax_sr_estimate[1] = std::max( uncMax_sr_estimate[1], (100*sr_estimate_error_mc_stats/sr_estimate) );
    uncMin_sr_estimate[1] = std::min( uncMin_sr_estimate[1], (100*sr_estimate_error_mc_stats/sr_estimate) );


  
    //
    // Loop over systematics
    //
    int unique_sys = 2;
    for(int iSys=0; iSys<(int)sys_labels.size(); iSys+=2){
      
      // SR, met bin, up
      TString hName_SR_bin_up = hName;
      hName_SR_bin_up += h_classy_SR;
      hName_SR_bin_up += "__";
      hName_SR_bin_up += sys_labels[iSys];
      hName_SR_bin_up += "__";
      hName_SR_bin_up += sr_cat_labels[iSR];
      
      TH1D *h_SR_bin_up = (TH1D*)f_SR->Get(hName_SR_bin_up);
      if(!h_SR_bin_up) cout << "BAD SR BIN UP HISTO: " << hName_SR_bin_up << endl;
      double sr_bin_error_up = 0.0;
      double sr_bin_yield_up = h_SR_bin_up->IntegralAndError(0,-1,sr_bin_error_up);
      /*
      if(doMetResScaling){
	sr_bin_error_up *= sr_cat_met_res_SFs[iSR].first;
	sr_bin_yield_up *= sr_cat_met_res_SFs[iSR].first;
      }
      */
      
      // SR, incl
      TString hName_SR_incl_up = hName;
      hName_SR_incl_up += h_classy_SR;
      hName_SR_incl_up += "__";
      hName_SR_incl_up += sys_labels[iSys];
      hName_SR_incl_up += "__";
      hName_SR_incl_up += cr_cat_labels[iSR];

      TH1D *h_SR_incl_up = (TH1D*)f_SR->Get(hName_SR_incl_up);
      if(!h_SR_incl_up) cout << "BAD SR INCL UP HISTO: " << hName_SR_incl_up << endl;
    
      double sr_incl_error_up = 0.0;
      double sr_incl_yield_up = h_SR_incl_up->IntegralAndError(0,-1,sr_incl_error_up);

      // CR, incl, MC
      TString hName_CR_mc_up = hName;
      hName_CR_mc_up += hName_incl;
      hName_CR_mc_up += "__";
      hName_CR_mc_up += sys_labels[iSys];
      hName_CR_mc_up += "__";
      hName_CR_mc_up += cr_cat_labels[iSR];

      TH1D *h_CR_mc_up = (TH1D*)f_CR->Get(hName_CR_mc_up);
      if(!h_CR_mc_up) cout << "BAD CR INCL UP MC HISTO: " << hName_CR_mc_up << endl;
    
      double cr_mc_incl_error_up = 0.0;
      double cr_mc_incl_yield_up = h_CR_mc_up->IntegralAndError(0,-1,cr_mc_incl_error_up);

      // Ratio of SR/CR, up
      double ratio_up = sr_incl_yield_up/cr_mc_incl_yield_up;
      //double ratio_up_statErr = ratio_up*sqrt( pow( sr_incl_error_up/sr_incl_yield_up, 2 ) + pow( cr_mc_incl_error_up/cr_mc_incl_yield_up, 2 ) );
      double ratio_up_statErr = ratio_up*sqrt( pow( cr_mc_incl_error_up/cr_mc_incl_yield_up, 2 ) ); // avoid double counting mc stats

      // Transfer Factor SR_bin/SR_incl, up
      double tf_up = sr_bin_yield_up/sr_incl_yield_up;
      double tf_up_statErr = sqrt( tf_up*(1-tf_up)/h_SR_incl_up->GetEntries() ); // binomial errors since sr_bin_yield is a subset of sr_incl_yield

      // SR estimate, up
      double sr_estimate_up = cr_data_incl_yield*ratio_up*tf_up;
      double sr_estimate_up_statErr = sr_estimate_up*sqrt( pow( cr_data_incl_error/cr_data_incl_yield,2 ) + pow( ratio_up_statErr/ratio_up,2 ) + pow( tf_up_statErr/tf_up,2 ) );

      fprintf(uncFile2, "$%s,~Up$ & %.2f,~(%.2f\\%%) & %.2f,~(%.2f\\%%) & %.2f~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ",sys_tex[iSys].Data(),cr_data_incl_yield,0.0,sr_incl_yield_up,(100*(sr_incl_yield_up-sr_incl_yield)/sr_incl_yield),cr_mc_incl_yield_up,(100*(cr_mc_incl_yield_up-cr_mc_incl_yield)/cr_mc_incl_yield), ratio_up, (100*(ratio_up-ratio)/ratio), sr_bin_yield_up, (100*(sr_bin_yield_up-sr_bin_yield)/sr_bin_yield), tf_up, (100*(tf_up-tf)/tf), sr_estimate_up, (100*(sr_estimate_up-sr_estimate)/sr_estimate) );
      fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\  \n"); //fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \n");
        

      // SR, met bin, dn
      TString hName_SR_bin_dn = hName;
      hName_SR_bin_dn += h_classy_SR;
      hName_SR_bin_dn += "__";
      hName_SR_bin_dn += sys_labels[iSys+1];
      hName_SR_bin_dn += "__";
      hName_SR_bin_dn += sr_cat_labels[iSR];
      
      TH1D *h_SR_bin_dn = (TH1D*)f_SR->Get(hName_SR_bin_dn);
      if(!h_SR_bin_dn) cout << "BAD SR BIN DN HISTO: " << hName_SR_bin_dn << endl;
      double sr_bin_error_dn = 0.0;
      double sr_bin_yield_dn = h_SR_bin_dn->IntegralAndError(0,-1,sr_bin_error_dn);
      /*
      if(doMetResScaling){
	sr_bin_error_dn *= sr_cat_met_res_SFs[iSR].first;
	sr_bin_yield_dn *= sr_cat_met_res_SFs[iSR].first;
      }
      */
      
      // SR, incl
      TString hName_SR_incl_dn = hName;
      hName_SR_incl_dn += h_classy_SR;
      hName_SR_incl_dn += "__";
      hName_SR_incl_dn += sys_labels[iSys+1];
      hName_SR_incl_dn += "__";
      hName_SR_incl_dn += cr_cat_labels[iSR];

      TH1D *h_SR_incl_dn = (TH1D*)f_SR->Get(hName_SR_incl_dn);
      if(!h_SR_incl_dn) cout << "BAD SR INCL DN HISTO: " << hName_SR_incl_dn << endl;
    
      double sr_incl_error_dn = 0.0;
      double sr_incl_yield_dn = h_SR_incl_dn->IntegralAndError(0,-1,sr_incl_error_dn);

      // CR, incl, MC
      TString hName_CR_mc_dn = hName;
      hName_CR_mc_dn += hName_incl;
      hName_CR_mc_dn += "__";
      hName_CR_mc_dn += sys_labels[iSys+1];
      hName_CR_mc_dn += "__";
      hName_CR_mc_dn += cr_cat_labels[iSR];

      TH1D *h_CR_mc_dn = (TH1D*)f_CR->Get(hName_CR_mc_dn);
      if(!h_CR_mc_dn) cout << "BAD CR INCL DN MC HISTO: " << hName_CR_mc_dn << endl;
 
      double cr_mc_incl_error_dn = 0.0;
      double cr_mc_incl_yield_dn = h_CR_mc_dn->IntegralAndError(0,-1,cr_mc_incl_error_dn);

      // Ratio of SR/CR, dn
      double ratio_dn = sr_incl_yield_dn/cr_mc_incl_yield_dn;
      //double ratio_dn_statErr = ratio_dn*sqrt( pow( sr_incl_error_dn/sr_incl_yield_dn,2 ) + pow( cr_mc_incl_error_dn/cr_mc_incl_yield_dn,2 ) );
      double ratio_dn_statErr = ratio_dn*sqrt( pow( cr_mc_incl_error_dn/cr_mc_incl_yield_dn,2 ) ); // avoid double counting MC stats
      
      // Transfer Factor SR_bin/SR_incl, dn
      double tf_dn = sr_bin_yield_dn/sr_incl_yield_dn;
      double tf_dn_statErr = sqrt( tf_dn*(1-tf_dn)/h_SR_incl_dn->GetEntries() ); // binomial errors since sr_bin_yield is a subset of sr_incl_yield

      // SR estimate, dn
      double sr_estimate_dn = cr_data_incl_yield*ratio_dn*tf_dn;
      double sr_estimate_dn_statErr = sr_estimate_dn*sqrt( pow( cr_data_incl_error/cr_data_incl_yield,2 ) + pow( ratio_dn_statErr/ratio_dn,2 ) + pow( tf_dn_statErr/tf_dn,2 ) );

      // Diff in Ratio
      double ratio_max_diff = std::max( fabs(ratio_up-ratio), fabs(ratio_dn-ratio) );
      double ratio_max_diff_sq = pow( ratio_max_diff, 2 );
      ratio_err = pow( ratio_err, 2 );
      ratio_err += ratio_max_diff_sq;
      ratio_err = sqrt(ratio_err);

      // Diff in TF
      double tf_max_diff = std::max( fabs(tf_up-tf), fabs(tf_dn-tf) );
      double tf_max_diff_sq = pow( tf_max_diff, 2 );
      tf_err = pow( tf_err, 2 );
      tf_err += tf_max_diff_sq;
      tf_err = sqrt(tf_err);

      // Diff in SR estimate
      double est_max_diff = std::max( fabs(sr_estimate_up-sr_estimate), fabs(sr_estimate_dn-sr_estimate) );
      double est_max_diff_sq = pow( est_max_diff, 2 );
      sr_estimate_error = pow( sr_estimate_error, 2 );
      sr_estimate_error += est_max_diff_sq;
      sr_estimate_error = sqrt(sr_estimate_error);


      // Fill histograms for limit setting
      h_SR[iSys+1]->SetBinContent( iSR+1, sr_estimate_up );
      h_SR[iSys+1]->SetBinError( iSR+1, sr_estimate_up_statErr );
      h_SR[iSys+2]->SetBinContent( iSR+1, sr_estimate_dn );
      h_SR[iSys+2]->SetBinError( iSR+1, sr_estimate_dn_statErr );
    

      // Tables
      fprintf(uncFile, "$%s$ & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,%.2f),~(%.1f\\%%,~%.1f\\%%) ", sys_tex[iSys].Data(),cr_data_incl_yield, cr_data_incl_yield,0.0,0.0, ratio_up, ratio_dn,(100*(ratio_up-ratio)/ratio),(100*(ratio_dn-ratio)/ratio), tf_up, tf_dn,(100*(tf_up-tf)/tf),(100*(tf_dn-tf)/tf), sr_estimate_up, sr_estimate_dn,(100*(sr_estimate_up-sr_estimate)/sr_estimate),(100*(sr_estimate_dn-sr_estimate)/sr_estimate) );
      fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \n");


      fprintf(uncFile2, "$%s,~Down$ & %.2f,~(%.2f\\%%) & %.2f,~(%.2f\\%%) & %.2f~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ",sys_tex[iSys].Data(),cr_data_incl_yield,0.0,sr_incl_yield_dn,(100*(sr_incl_yield_dn-sr_incl_yield)/sr_incl_yield),cr_mc_incl_yield_dn,(100*(cr_mc_incl_yield_dn-cr_mc_incl_yield)/cr_mc_incl_yield), ratio_dn, (100*(ratio_dn-ratio)/ratio), sr_bin_yield_dn, (100*(sr_bin_yield_dn-sr_bin_yield)/sr_bin_yield), tf_dn, (100*(tf_dn-tf)/tf), sr_estimate_dn, (100*(sr_estimate_dn-sr_estimate)/sr_estimate) );
      fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \n");
  

      uncMax_cr_data_incl[unique_sys] = std::max( uncMax_cr_data_incl[unique_sys], 0.0 );
      uncMin_cr_data_incl[unique_sys] = std::min( uncMin_cr_data_incl[unique_sys], 0.0 );
      uncMax_ratio[unique_sys] = std::max( uncMax_ratio[unique_sys], (100*ratio_max_diff/ratio) );
      uncMin_ratio[unique_sys] = std::min( uncMin_ratio[unique_sys], (100*ratio_max_diff/ratio) );
      uncMax_tf[unique_sys] = std::max( uncMax_tf[unique_sys], (100*tf_max_diff/tf) );
      uncMin_tf[unique_sys] = std::min( uncMin_tf[unique_sys], (100*tf_max_diff/tf) );
      uncMax_sr_estimate[unique_sys] = std::max( uncMax_sr_estimate[unique_sys], (100*est_max_diff/sr_estimate) );
      uncMin_sr_estimate[unique_sys] = std::min( uncMin_sr_estimate[unique_sys], (100*est_max_diff/sr_estimate) );
      
      unique_sys++;

    } // end loop over systematics


    //
    // JES
    //

    // SR, met bin, jesUp
    TString hName_SR_bin_jesUp = hName;
    hName_SR_bin_jesUp += h_classy_SR;
    hName_SR_bin_jesUp += "__";
    hName_SR_bin_jesUp += hName_nominal_sys;
    hName_SR_bin_jesUp += "__";
    hName_SR_bin_jesUp += sr_cat_labels[iSR];
      
    TH1D *h_SR_bin_jesUp = (TH1D*)f_SR_JESup->Get(hName_SR_bin_jesUp);
    if(!h_SR_bin_jesUp) cout << "BAD SR BIN JESUP HISTO: " << hName_SR_bin_jesUp << endl;
    double sr_bin_error_jesUp = 0.0;
    double sr_bin_yield_jesUp = h_SR_bin_jesUp->IntegralAndError(0,-1,sr_bin_error_jesUp);
    /*
    if(doMetResScaling){
      sr_bin_error_jesUp *= sr_cat_met_res_SFs[iSR].first;
      sr_bin_yield_jesUp *= sr_cat_met_res_SFs[iSR].first;
    }
    */
      
    // SR, incl
    TString hName_SR_incl_jesUp = hName;
    hName_SR_incl_jesUp += h_classy_SR;
    hName_SR_incl_jesUp += "__";
    hName_SR_incl_jesUp += hName_nominal_sys;
    hName_SR_incl_jesUp += "__";
    hName_SR_incl_jesUp += cr_cat_labels[iSR];;

    TH1D *h_SR_incl_jesUp = (TH1D*)f_SR_JESup->Get(hName_SR_incl_jesUp);
    if(!h_SR_incl_jesUp) cout << "BAD SR INCL JESUP HISTO: " << hName_SR_incl_jesUp << endl;
    
    double sr_incl_error_jesUp = 0.0;
    double sr_incl_yield_jesUp = h_SR_incl_jesUp->IntegralAndError(0,-1,sr_incl_error_jesUp);

    // CR, incl, MC
    TString hName_CR_mc_jesUp = hName;
    hName_CR_mc_jesUp += hName_incl;
    hName_CR_mc_jesUp += "__";
    hName_CR_mc_jesUp += hName_nominal_sys;
    hName_CR_mc_jesUp += "__";
    hName_CR_mc_jesUp += cr_cat_labels[iSR];

    TH1D *h_CR_mc_jesUp = (TH1D*)f_CR_JESup->Get(hName_CR_mc_jesUp);
    if(!h_CR_mc_jesUp) cout << "BAD CR INCL JESUP MC HISTO: " << hName_CR_mc_jesUp << endl;
    
    double cr_mc_incl_error_jesUp = 0.0;
    double cr_mc_incl_yield_jesUp = h_CR_mc_jesUp->IntegralAndError(0,-1,cr_mc_incl_error_jesUp);

    // Ratio of SR/CR, jesUp
    double ratio_jesUp = sr_incl_yield_jesUp/cr_mc_incl_yield_jesUp;
    double ratio_jesUp_statErr = ratio_jesUp*sqrt( pow( cr_mc_incl_error_jesUp/cr_mc_incl_yield_jesUp,2 ) );
      
    // Transfer Factor SR_bin/SR_incl, jesUp
    double tf_jesUp = sr_bin_yield_jesUp/sr_incl_yield_jesUp;
    double tf_jesUp_statErr = sqrt( tf_jesUp*(1-tf_jesUp)/h_SR_incl_jesUp->GetEntries() ); // binomial errors since sr_bin_yield is a subset of sr_incl_yield

    // SR estimate, jesUp
    double sr_estimate_jesUp = cr_data_incl_yield*ratio_jesUp*tf_jesUp;
    double sr_estimate_jesUp_statErr = sr_estimate_jesUp*sqrt( pow(cr_data_incl_error/cr_data_incl_yield,2) + pow(ratio_jesUp_statErr/ratio_jesUp,2) + pow(tf_jesUp_statErr/tf_jesUp,2) );

    
    fprintf(uncFile2, "JES Up & %.2f,~(%.2f\\%%) & %.2f,~(%.2f\\%%) & %.2f~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ",cr_data_incl_yield,0.0,sr_incl_yield_jesUp,(100*(sr_incl_yield_jesUp-sr_incl_yield)/sr_incl_yield),cr_mc_incl_yield_jesUp,(100*(cr_mc_incl_yield_jesUp-cr_mc_incl_yield)/cr_mc_incl_yield), ratio_jesUp, (100*(ratio_jesUp-ratio)/ratio), sr_bin_yield_jesUp, (100*(sr_bin_yield_jesUp-sr_bin_yield)/sr_bin_yield), tf_jesUp, (100*(tf_jesUp-tf)/tf), sr_estimate_jesUp, (100*(sr_estimate_jesUp-sr_estimate)/sr_estimate) );
    fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\  \n"); //fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \n");
      



    // SR, met bin, jesDn
    TString hName_SR_bin_jesDn = hName;
    hName_SR_bin_jesDn += h_classy_SR;
    hName_SR_bin_jesDn += "__";
    hName_SR_bin_jesDn += hName_nominal_sys;
    hName_SR_bin_jesDn += "__";
    hName_SR_bin_jesDn += sr_cat_labels[iSR];
      
    TH1D *h_SR_bin_jesDn = (TH1D*)f_SR_JESdn->Get(hName_SR_bin_jesDn);
    if(!h_SR_bin_jesDn) cout << "BAD SR BIN JESDN HISTO: " << hName_SR_bin_jesDn << endl;
    double sr_bin_error_jesDn = 0.0;
    double sr_bin_yield_jesDn = h_SR_bin_jesDn->IntegralAndError(0,-1,sr_bin_error_jesDn);

    /*
    if(doMetResScaling){
      sr_bin_error_jesDn *= sr_cat_met_res_SFs[iSR].first;
      sr_bin_yield_jesDn *= sr_cat_met_res_SFs[iSR].first;
    }
    */
      
    // SR, incl
    TString hName_SR_incl_jesDn = hName;
    hName_SR_incl_jesDn += h_classy_SR;
    hName_SR_incl_jesDn += "__";
    hName_SR_incl_jesDn += hName_nominal_sys;
    hName_SR_incl_jesDn += "__";
    hName_SR_incl_jesDn += cr_cat_labels[iSR];

    TH1D *h_SR_incl_jesDn = (TH1D*)f_SR_JESdn->Get(hName_SR_incl_jesDn);
    if(!h_SR_incl_jesDn) cout << "BAD SR INCL JESDN HISTO: " << hName_SR_incl_jesDn << endl;
    
    double sr_incl_error_jesDn = 0.0;
    double sr_incl_yield_jesDn = h_SR_incl_jesDn->IntegralAndError(0,-1,sr_incl_error_jesDn);

    // CR, incl, MC
    TString hName_CR_mc_jesDn = hName;
    hName_CR_mc_jesDn += hName_incl;
    hName_CR_mc_jesDn += "__";
    hName_CR_mc_jesDn += hName_nominal_sys;
    hName_CR_mc_jesDn += "__";
    hName_CR_mc_jesDn += cr_cat_labels[iSR];

    TH1D *h_CR_mc_jesDn = (TH1D*)f_CR_JESdn->Get(hName_CR_mc_jesDn);
    if(!h_CR_mc_jesDn) cout << "BAD CR INCL JESDN MC HISTO: " << hName_CR_mc_jesDn << endl;
    
    double cr_mc_incl_error_jesDn = 0.0;
    double cr_mc_incl_yield_jesDn = h_CR_mc_jesDn->IntegralAndError(0,-1,cr_mc_incl_error_jesDn);

    // Ratio of SR/CR, jesDn
    double ratio_jesDn = sr_incl_yield_jesDn/cr_mc_incl_yield_jesDn;
    double ratio_jesDn_statErr = ratio_jesDn*sqrt( pow(cr_mc_incl_error_jesDn/cr_mc_incl_yield_jesDn,2) );

    // Transfer Factor SR_bin/SR_incl, jesDn
    double tf_jesDn = sr_bin_yield_jesDn/sr_incl_yield_jesDn;
    double tf_jesDn_statErr = sqrt( tf_jesDn*(1-tf_jesDn)/h_SR_incl_jesDn->GetEntries() ); // binomial errors since sr_bin_yield is a subset of sr_incl_yield

    // SR estimate, jesDn
    double sr_estimate_jesDn = cr_data_incl_yield*ratio_jesDn*tf_jesDn;
    double sr_estimate_jesDn_statErr = sr_estimate_jesDn*sqrt( pow(cr_data_incl_error/cr_data_incl_yield,2) + pow(ratio_jesDn_statErr/ratio_jesDn,2) + pow( tf_jesDn_statErr/tf_jesDn,2) );

    // Diff in Ratio
    double ratio_max_diff = std::max( fabs(ratio_jesUp-ratio), fabs(ratio_jesDn-ratio) );
    double ratio_max_diff_sq = pow( ratio_max_diff, 2 );
    ratio_err = pow( ratio_err, 2 );
    ratio_err += ratio_max_diff_sq;
    ratio_err = sqrt(ratio_err);

    // Diff in TF
    double tf_max_diff = std::max( fabs(tf_jesUp-tf), fabs(tf_jesDn-tf) );
    double tf_max_diff_sq = pow( tf_max_diff, 2 );
    tf_err = pow( tf_err, 2 );
    tf_err += tf_max_diff_sq;
    tf_err = sqrt(tf_err);

    // Diff in SR estimate
    double est_max_diff = std::max( fabs(sr_estimate_jesUp-sr_estimate), fabs(sr_estimate_jesDn-sr_estimate) );
    double est_max_diff_sq = pow( est_max_diff, 2 );
    sr_estimate_error = pow( sr_estimate_error, 2 );
    sr_estimate_error += est_max_diff_sq;
    sr_estimate_error = sqrt(sr_estimate_error);


    /*
    // Fill Histos For limit setting
    h_SR[nSys-4]->SetBinContent( iSR+1, sr_estimate_jesUp );
    h_SR[nSys-4]->SetBinError( iSR+1, sr_estimate_jesUp_statErr );
    h_SR[nSys-3]->SetBinContent( iSR+1, sr_estimate_jesDn );
    h_SR[nSys-3]->SetBinError( iSR+1, sr_estimate_jesDn_statErr );
    */
    // Fill Histos For limit setting
    h_SR[nSys-2]->SetBinContent( iSR+1, sr_estimate_jesUp );
    h_SR[nSys-2]->SetBinError( iSR+1, sr_estimate_jesUp_statErr );
    h_SR[nSys-1]->SetBinContent( iSR+1, sr_estimate_jesDn );
    h_SR[nSys-1]->SetBinError( iSR+1, sr_estimate_jesDn_statErr );
    
    // Tables
    
    fprintf(uncFile, "JES & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,%.2f),~(%.1f\\%%,~%.1f\\%%) ",cr_data_incl_yield, cr_data_incl_yield,0.0,0.0, ratio_jesUp, ratio_jesDn,(100*(ratio_jesUp-ratio)/ratio),(100*(ratio_jesDn-ratio)/ratio), tf_jesUp, tf_jesDn,(100*(tf_jesUp-tf)/tf),(100*(tf_jesDn-tf)/tf), sr_estimate_jesUp, sr_estimate_jesDn,(100*(sr_estimate_jesUp-sr_estimate)/sr_estimate),(100*(sr_estimate_jesDn-sr_estimate)/sr_estimate) );
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \n");

    
    fprintf(uncFile2, "JES Down & %.2f,~(%.2f\\%%) & %.2f,~(%.2f\\%%) & %.2f~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ",cr_data_incl_yield,0.0,sr_incl_yield_jesDn,(100*(sr_incl_yield_jesDn-sr_incl_yield)/sr_incl_yield),cr_mc_incl_yield_jesDn,(100*(cr_mc_incl_yield_jesDn-cr_mc_incl_yield)/cr_mc_incl_yield), ratio_jesDn, (100*(ratio_jesDn-ratio)/ratio), sr_bin_yield_jesDn, (100*(sr_bin_yield_jesDn-sr_bin_yield)/sr_bin_yield), tf_jesDn, (100*(tf_jesDn-tf)/tf), sr_estimate_jesDn, (100*(sr_estimate_jesDn-sr_estimate)/sr_estimate) );
    fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \n");  //fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \\hline \n"); 

    
    uncMax_cr_data_incl[nSys_unique-2] = std::max( uncMax_cr_data_incl[nSys_unique-2], 0.0 );
    uncMin_cr_data_incl[nSys_unique-2] = std::min( uncMin_cr_data_incl[nSys_unique-2], 0.0 );
    uncMax_ratio[nSys_unique-2] = std::max( uncMax_ratio[nSys_unique-2], (100*ratio_max_diff/ratio) );
    uncMin_ratio[nSys_unique-2] = std::min( uncMin_ratio[nSys_unique-2], (100*ratio_max_diff/ratio) );
    uncMax_tf[nSys_unique-2] = std::max( uncMax_tf[nSys_unique-2], (100*tf_max_diff/tf) );
    uncMin_tf[nSys_unique-2] = std::min( uncMin_tf[nSys_unique-2], (100*tf_max_diff/tf) );
    uncMax_sr_estimate[nSys_unique-2] = std::max( uncMax_sr_estimate[nSys_unique-2], (100*est_max_diff/sr_estimate) );
    uncMin_sr_estimate[nSys_unique-2] = std::min( uncMin_sr_estimate[nSys_unique-2], (100*est_max_diff/sr_estimate) );

    /*
    uncMax_cr_data_incl[nSys_unique-3] = std::max( uncMax_cr_data_incl[nSys_unique-3], 0.0 );
    uncMin_cr_data_incl[nSys_unique-3] = std::min( uncMin_cr_data_incl[nSys_unique-3], 0.0 );
    uncMax_ratio[nSys_unique-3] = std::max( uncMax_ratio[nSys_unique-3], (100*ratio_max_diff/ratio) );
    uncMin_ratio[nSys_unique-3] = std::min( uncMin_ratio[nSys_unique-3], (100*ratio_max_diff/ratio) );
    uncMax_tf[nSys_unique-3] = std::max( uncMax_tf[nSys_unique-3], (100*tf_max_diff/tf) );
    uncMin_tf[nSys_unique-3] = std::min( uncMin_tf[nSys_unique-3], (100*tf_max_diff/tf) );
    uncMax_sr_estimate[nSys_unique-3] = std::max( uncMax_sr_estimate[nSys_unique-3], (100*est_max_diff/sr_estimate) );
    uncMin_sr_estimate[nSys_unique-3] = std::min( uncMin_sr_estimate[nSys_unique-3], (100*est_max_diff/sr_estimate) );


    
    // MET resolution uncertainty
    if(doMetResScaling){

      double sr_bin_error_metResUp = sr_bin_error*( (sr_cat_met_res_SFs[iSR].first+sr_cat_met_res_SFs[iSR].second)/sr_cat_met_res_SFs[iSR].first );
      double sr_bin_yield_metResUp = sr_bin_yield*( (sr_cat_met_res_SFs[iSR].first+sr_cat_met_res_SFs[iSR].second)/sr_cat_met_res_SFs[iSR].first );

      double tf_metResUp = sr_bin_yield_metResUp/sr_incl_yield;
      double tf_metResUp_statErr = sqrt( tf_metResUp*(1-tf_metResUp)/h_SR_incl->GetEntries() ); // binomial errors since sr_bin_yield is a subset of sr_incl_yield
      double sr_estimate_metResUp = cr_data_incl_yield*ratio*tf_metResUp;
      double sr_estimate_metResUp_statErr = sr_estimate_metResUp*sqrt( pow(cr_data_incl_error/cr_data_incl_yield,2) + pow(ratio_statErr/ratio,2) + pow(tf_metResUp_statErr/tf_metResUp,2) );

      
      fprintf(uncFile2, "MET Resolution Up & %.2f,~(%.2f\\%%) & %.2f,~(%.2f\\%%) & %.2f~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ",cr_data_incl_yield,0.0,sr_incl_yield,0.0,cr_mc_incl_yield,0.0, ratio, 0.0, sr_bin_yield_metResUp, (100*(sr_bin_yield_metResUp-sr_bin_yield)/sr_bin_yield), tf_metResUp, (100*(tf_metResUp-tf)/tf), sr_estimate_metResUp, (100*(sr_estimate_metResUp-sr_estimate)/sr_estimate) );
      fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\  \n"); //fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \n");

      
      double sr_bin_error_metResDown = sr_bin_error*( (sr_cat_met_res_SFs[iSR].first-sr_cat_met_res_SFs[iSR].second)/sr_cat_met_res_SFs[iSR].first );
      double sr_bin_yield_metResDown = sr_bin_yield*( (sr_cat_met_res_SFs[iSR].first-sr_cat_met_res_SFs[iSR].second)/sr_cat_met_res_SFs[iSR].first );

      double tf_metResDown = sr_bin_yield_metResDown/sr_incl_yield;
      double tf_metResDown_statErr = sqrt( tf_metResDown*(1-tf_metResDown)/h_SR_incl->GetEntries() ); // binomial errors since sr_bin_yield is a subset of sr_incl_yield
      double sr_estimate_metResDown = cr_data_incl_yield*ratio*tf_metResDown;
      double sr_estimate_metResDown_statErr = sr_estimate_metResDown*sqrt( pow(cr_data_incl_error/cr_data_incl_yield,2) + pow(ratio_statErr/ratio,2) + pow(tf_metResDown_statErr/tf_metResDown,2) );

  

      // Diff in TF
      double tf_metRes_max_diff = std::max( fabs(tf_metResUp-tf), fabs(tf_metResDown-tf) );
      double tf_metRes_max_diff_sq = pow( tf_metRes_max_diff, 2 );
      tf_err = pow( tf_err, 2 );
      tf_err += tf_metRes_max_diff_sq;
      tf_err = sqrt(tf_err);

      // Diff in SR estimate
      double est_metRes_max_diff = std::max( fabs(sr_estimate_metResUp-sr_estimate), fabs(sr_estimate_metResDown-sr_estimate) );
      double est_metRes_max_diff_sq = pow( est_metRes_max_diff, 2 );
      sr_estimate_error = pow( sr_estimate_error, 2 );
      sr_estimate_error += est_metRes_max_diff_sq;
      sr_estimate_error = sqrt(sr_estimate_error);


      // Fill Histos For limit setting
      h_SR[nSys-2]->SetBinContent( iSR+1, sr_estimate_metResUp );
      h_SR[nSys-2]->SetBinError( iSR+1, sr_estimate_metResUp_statErr );
      h_SR[nSys-1]->SetBinContent( iSR+1, sr_estimate_metResDown );
      h_SR[nSys-1]->SetBinError( iSR+1, sr_estimate_metResDown_statErr );
    


      fprintf(uncFile, "MET Resolution & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,%.2f),~(%.1f\\%%,~%.1f\\%%) ",cr_data_incl_yield, cr_data_incl_yield,0.0,0.0, ratio, ratio,0.0,0.0, tf_metResUp, tf_metResDown,(100*(tf_metResUp-tf)/tf),(100*(tf_metResDown-tf)/tf), sr_estimate_metResUp, sr_estimate_metResDown,(100*(sr_estimate_metResUp-sr_estimate)/sr_estimate),(100*(sr_estimate_metResDown-sr_estimate)/sr_estimate) );
      fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \n");


      fprintf(uncFile2, "MET Resolution Down & %.2f,~(%.2f\\%%) & %.2f,~(%.2f\\%%) & %.2f~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ",cr_data_incl_yield,0.0,sr_incl_yield,0.0,cr_mc_incl_yield,0.0, ratio, 0.0, sr_bin_yield_metResDown, (100*(sr_bin_yield_metResDown-sr_bin_yield)/sr_bin_yield), tf_metResDown, (100*(tf_metResDown-tf)/tf), sr_estimate_metResDown, (100*(sr_estimate_metResDown-sr_estimate)/sr_estimate) );
      fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \\hline \n"); //fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\  \n");
    

      uncMax_cr_data_incl[nSys_unique-2] = std::max( uncMax_cr_data_incl[nSys_unique-2], 0.0 );
      uncMin_cr_data_incl[nSys_unique-2] = std::min( uncMin_cr_data_incl[nSys_unique-2], 0.0 );
      uncMax_ratio[nSys_unique-2] = std::max( uncMax_ratio[nSys_unique-2], 0.0 );
      uncMin_ratio[nSys_unique-2] = std::min( uncMin_ratio[nSys_unique-2], 0.0 );
      uncMax_tf[nSys_unique-2] = std::max( uncMax_tf[nSys_unique-2], (100*tf_metRes_max_diff/tf) );
      uncMin_tf[nSys_unique-2] = std::min( uncMin_tf[nSys_unique-2], (100*tf_metRes_max_diff/tf) );
      uncMax_sr_estimate[nSys_unique-2] = std::max( uncMax_sr_estimate[nSys_unique-2], (100*est_metRes_max_diff/sr_estimate) );
      uncMin_sr_estimate[nSys_unique-2] = std::min( uncMin_sr_estimate[nSys_unique-2], (100*est_metRes_max_diff/sr_estimate) );


    }

    if(doMetResUncOnly){
      double sr_bin_error_metResUp = sr_bin_error;
      double sr_bin_yield_metResUp = sr_bin_yield;
      if( fabs( (sr_cat_met_res_SFs[iSR].first+sr_cat_met_res_SFs[iSR].second)-1.0 ) > fabs( (sr_cat_met_res_SFs[iSR].first-sr_cat_met_res_SFs[iSR].second)-1.0 ) ){
	sr_bin_error_metResUp *= (sr_cat_met_res_SFs[iSR].first+sr_cat_met_res_SFs[iSR].second);
	sr_bin_yield_metResUp *= (sr_cat_met_res_SFs[iSR].first+sr_cat_met_res_SFs[iSR].second);
      }
      else{
	sr_bin_error_metResUp *= (sr_cat_met_res_SFs[iSR].first-sr_cat_met_res_SFs[iSR].second);
	sr_bin_yield_metResUp *= (sr_cat_met_res_SFs[iSR].first-sr_cat_met_res_SFs[iSR].second);
      }

      double tf_metResUp = sr_bin_yield_metResUp/sr_incl_yield;
      double tf_metResUp_statErr = sqrt( tf_metResUp*(1-tf_metResUp)/h_SR_incl->GetEntries() ); // binomial errors since sr_bin_yield is a subset of sr_incl_yield
      double sr_estimate_metResUp = cr_data_incl_yield*ratio*tf_metResUp;
      double sr_estimate_metResUp_statErr = sr_estimate_metResUp*sqrt( pow(cr_data_incl_error/cr_data_incl_yield,2) + pow(ratio_statErr/ratio,2) + pow(tf_metResUp_statErr/tf_metResUp,2) );

      
      fprintf(uncFile2, "MET Resolution Up & %.2f,~(%.2f\\%%) & %.2f,~(%.2f\\%%) & %.2f~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ",cr_data_incl_yield,0.0,sr_incl_yield,0.0,cr_mc_incl_yield,0.0, ratio, 0.0, sr_bin_yield_metResUp, (100*(sr_bin_yield_metResUp-sr_bin_yield)/sr_bin_yield), tf_metResUp, (100*(tf_metResUp-tf)/tf), sr_estimate_metResUp, (100*(sr_estimate_metResUp-sr_estimate)/sr_estimate) );
      fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\  \n"); //fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \n");


      double sr_bin_error_metResDown = sr_bin_error;
      double sr_bin_yield_metResDown = sr_bin_yield;

      double tf_metResDown = sr_bin_yield_metResDown/sr_incl_yield;
      double tf_metResDown_statErr = sqrt( tf_metResDown*(1-tf_metResDown)/h_SR_incl->GetEntries() ); // binomial errors since sr_bin_yield is a subset of sr_incl_yield
      double sr_estimate_metResDown = cr_data_incl_yield*ratio*tf_metResDown;
      double sr_estimate_metResDown_statErr = sr_estimate_metResDown*sqrt( pow(cr_data_incl_error/cr_data_incl_yield,2) + pow(ratio_statErr/ratio,2) + pow(tf_metResDown_statErr/tf_metResDown,2) );

  

      // Diff in TF
      double tf_metRes_max_diff = std::max( fabs(tf_metResUp-tf), fabs(tf_metResDown-tf) );
      double tf_metRes_max_diff_sq = pow( tf_metRes_max_diff, 2 );
      tf_err = pow( tf_err, 2 );
      tf_err += tf_metRes_max_diff_sq;
      tf_err = sqrt(tf_err);

      // Diff in SR estimate
      double est_metRes_max_diff = std::max( fabs(sr_estimate_metResUp-sr_estimate), fabs(sr_estimate_metResDown-sr_estimate) );
      double est_metRes_max_diff_sq = pow( est_metRes_max_diff, 2 );
      sr_estimate_error = pow( sr_estimate_error, 2 );
      sr_estimate_error += est_metRes_max_diff_sq;
      sr_estimate_error = sqrt(sr_estimate_error);


      // Fill Histos For limit setting
      h_SR[nSys-2]->SetBinContent( iSR+1, sr_estimate_metResUp );
      h_SR[nSys-2]->SetBinError( iSR+1, sr_estimate_metResUp_statErr );
      h_SR[nSys-1]->SetBinContent( iSR+1, sr_estimate_metResDown );
      h_SR[nSys-1]->SetBinError( iSR+1, sr_estimate_metResDown_statErr );
    


      fprintf(uncFile, "MET Resolution & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,%.2f),~(%.1f\\%%,~%.1f\\%%) ",cr_data_incl_yield, cr_data_incl_yield,0.0,0.0, ratio, ratio,0.0,0.0, tf_metResUp, tf_metResDown,(100*(tf_metResUp-tf)/tf),(100*(tf_metResDown-tf)/tf), sr_estimate_metResUp, sr_estimate_metResDown,(100*(sr_estimate_metResUp-sr_estimate)/sr_estimate),(100*(sr_estimate_metResDown-sr_estimate)/sr_estimate) );
      fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \\hline \n");


      fprintf(uncFile2, "MET Resolution Down & %.2f,~(%.2f\\%%) & %.2f,~(%.2f\\%%) & %.2f~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) & %.2f ~(%.2f\\%%) ",cr_data_incl_yield,0.0,sr_incl_yield,0.0,cr_mc_incl_yield,0.0, ratio, 0.0, sr_bin_yield_metResDown, (100*(sr_bin_yield_metResDown-sr_bin_yield)/sr_bin_yield), tf_metResDown, (100*(tf_metResDown-tf)/tf), sr_estimate_metResDown, (100*(sr_estimate_metResDown-sr_estimate)/sr_estimate) );
      fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \\hline \n"); //fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \n");
    

      uncMax_cr_data_incl[nSys_unique-2] = std::max( uncMax_cr_data_incl[nSys_unique-2], 0.0 );
      uncMin_cr_data_incl[nSys_unique-2] = std::min( uncMin_cr_data_incl[nSys_unique-2], 0.0 );
      uncMax_ratio[nSys_unique-2] = std::max( uncMax_ratio[nSys_unique-2], 0.0 );
      uncMin_ratio[nSys_unique-2] = std::min( uncMin_ratio[nSys_unique-2], 0.0 );
      uncMax_tf[nSys_unique-2] = std::max( uncMax_tf[nSys_unique-2], (100*tf_metRes_max_diff/tf) );
      uncMin_tf[nSys_unique-2] = std::min( uncMin_tf[nSys_unique-2], (100*tf_metRes_max_diff/tf) );
      uncMax_sr_estimate[nSys_unique-2] = std::max( uncMax_sr_estimate[nSys_unique-2], (100*est_metRes_max_diff/sr_estimate) );
      uncMin_sr_estimate[nSys_unique-2] = std::min( uncMin_sr_estimate[nSys_unique-2], (100*est_metRes_max_diff/sr_estimate) );


    }
    */

    fprintf(uncFile, "Total Uncertainty & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,~%.2f),~(%.1f\\%%,~%.1f\\%%) & (%.2f,%.2f),~(%.1f\\%%,~%.1f\\%%) ",cr_data_incl_yield+cr_data_incl_error, cr_data_incl_yield-cr_data_incl_error,(100*cr_data_incl_error/cr_data_incl_yield),(-100*cr_data_incl_error/cr_data_incl_yield), ratio+ratio_err, ratio-ratio_err,(100*ratio_err/ratio),(-100*ratio_err/ratio), tf+tf_err, tf-tf_err,(100*tf_err/tf),(-100*tf_err/tf), sr_estimate+sr_estimate_error, sr_estimate-sr_estimate_error,(100*sr_estimate_error/sr_estimate),(-100*sr_estimate_error/sr_estimate) );
    fprintf(uncFile, "\\"); fprintf(uncFile, "\\ \\hline \n");


    fprintf(uncFile2, "Total Uncertainties & %.2f\\%% & & & %.2f\\%% & & %.2f\\%% & %.2f\\%% ",(100*cr_data_incl_error/cr_data_incl_yield), (100*ratio_err/ratio), (100*tf_err/tf), (100*sr_estimate_error/sr_estimate) );
    fprintf(uncFile2, "\\"); fprintf(uncFile2, "\\ \\hline \n");

    
    uncMax_cr_data_incl[nSys_unique-1] = std::max( uncMax_cr_data_incl[nSys_unique-1], (100*cr_data_incl_error/cr_data_incl_yield) );
    uncMin_cr_data_incl[nSys_unique-1] = std::min( uncMin_cr_data_incl[nSys_unique-1], (100*cr_data_incl_error/cr_data_incl_yield) );
    uncMax_ratio[nSys_unique-1] = std::max( uncMax_ratio[nSys_unique-1], (100*ratio_err/ratio) );
    uncMin_ratio[nSys_unique-1] = std::min( uncMin_ratio[nSys_unique-1], (100*ratio_err/ratio) );
    uncMax_tf[nSys_unique-1] = std::max( uncMax_tf[nSys_unique-1], (100*tf_err/tf) );
    uncMin_tf[nSys_unique-1] = std::min( uncMin_tf[nSys_unique-1], (100*tf_err/tf) );
    uncMax_sr_estimate[nSys_unique-1] = std::max( uncMax_sr_estimate[nSys_unique-1], (100*sr_estimate_error/sr_estimate) );
    uncMin_sr_estimate[nSys_unique-1] = std::min( uncMin_sr_estimate[nSys_unique-1], (100*sr_estimate_error/sr_estimate) );
    
       

    fprintf(uncFile, "\\end{tabular} \n");
    fprintf(uncFile, "} \n");
    fprintf(uncFile, "\\end{table} \n");
    fprintf(uncFile, "\\end{document} \n");
    fclose(uncFile);
  
  
    fprintf(uncFile2, "\\end{tabular} \n");
    fprintf(uncFile2, "} \n");
    fprintf(uncFile2, "\\end{table} \n");
    fprintf(uncFile2, "\\end{document} \n");
    fclose(uncFile2);
  

    fprintf(yFile, "%.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f " , sr_bin_yield, sr_bin_error, cr_data_incl_yield, cr_data_incl_error, cr_mc_incl_yield, cr_mc_incl_error, sr_incl_yield, sr_incl_error, ratio, ratio_err, tf, tf_err, sr_estimate, sr_estimate_error);
    fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");


    fprintf(yFile2, "%.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f " , cr_data_incl_yield, cr_data_incl_error, ratio, ratio_err, tf, tf_err, sr_estimate, sr_estimate_error);
    fprintf(yFile2, "\\"); fprintf(yFile2, "\\ \\hline \n");

  } // end loop over signal regions



  // summary table of uncertainties
  fprintf(uncFileSummary, "Data Stats & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data_incl[0], uncMax_cr_data_incl[0], uncMin_ratio[0], uncMax_ratio[0], uncMin_tf[0], uncMax_tf[0], uncMin_sr_estimate[0], uncMax_sr_estimate[0]);
  fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \n");
  
  fprintf(uncFileSummary, "MC Stats & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data_incl[1], uncMax_cr_data_incl[1], uncMin_ratio[1], uncMax_ratio[1], uncMin_tf[1], uncMax_tf[1], uncMin_sr_estimate[1], uncMax_sr_estimate[1]);
  fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \n");

  int unique_sys = 2;
  for(int iSys=0; iSys<(int)sys_labels.size(); iSys+=2){
    fprintf(uncFileSummary, "$%s$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", sys_tex[iSys].Data(), uncMin_cr_data_incl[unique_sys], uncMax_cr_data_incl[unique_sys], uncMin_ratio[unique_sys], uncMax_ratio[unique_sys], uncMin_tf[unique_sys], uncMax_tf[unique_sys], uncMin_sr_estimate[unique_sys], uncMax_sr_estimate[unique_sys]);
    fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \n");
    unique_sys++;
  }


  fprintf(uncFileSummary, "JES & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data_incl[nSys_unique-2], uncMax_cr_data_incl[nSys_unique-2], uncMin_ratio[nSys_unique-2], uncMax_ratio[nSys_unique-2], uncMin_tf[nSys_unique-2], uncMax_tf[nSys_unique-2], uncMin_sr_estimate[nSys_unique-2], uncMax_sr_estimate[nSys_unique-2]);
  fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \n");
  
  /*
  fprintf(uncFileSummary, "MET Resolution & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data_incl[nSys_unique-2], uncMax_cr_data_incl[nSys_unique-2], uncMin_ratio[nSys_unique-2], uncMax_ratio[nSys_unique-2], uncMin_tf[nSys_unique-2], uncMax_tf[nSys_unique-2], uncMin_sr_estimate[nSys_unique-2], uncMax_sr_estimate[nSys_unique-2]);
  fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \\hline \n");
  */
  fprintf(uncFileSummary, "Total & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ & $%.1f~-~%.1f~\\%%$ ", uncMin_cr_data_incl[nSys_unique-1], uncMax_cr_data_incl[nSys_unique-1], uncMin_ratio[nSys_unique-1], uncMax_ratio[nSys_unique-1], uncMin_tf[nSys_unique-1], uncMax_tf[nSys_unique-1], uncMin_sr_estimate[nSys_unique-1], uncMax_sr_estimate[nSys_unique-1]);
  fprintf(uncFileSummary, "\\"); fprintf(uncFileSummary, "\\ \\hline \n");
    


  
  fprintf(yFile, "\\end{tabular} \n");
  fprintf(yFile, "} \n");
  fprintf(yFile, "\\end{table} \n");
  fprintf(yFile, "\\end{document} \n");
  fclose(yFile);

  fprintf(yFile2, "\\end{tabular} \n");
  fprintf(yFile2, "} \n");
  fprintf(yFile2, "\\end{table} \n");
  fprintf(yFile2, "\\end{document} \n");
  fclose(yFile2);

  fprintf(uncFileSummary, "\\end{tabular} \n");
  fprintf(uncFileSummary, "} \n");
  fprintf(uncFileSummary, "\\end{table} \n");
  fprintf(uncFileSummary, "\\end{document} \n");
  fclose(uncFileSummary);

  
  
  
  //
  // Clean up
  //
  f_out->Write();
  f_out->Close();
  f_SR->Close();
  f_CR->Close();
  f_data_CR->Close();
  return 0;
}
