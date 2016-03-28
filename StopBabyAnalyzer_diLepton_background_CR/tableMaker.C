// ROOT
#include "TFile.h"
#include "TH1.h"
#include "TString.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TLine.h"

// std
#include <vector>

// histoHelper
#include "histoHelper.h"

//
// Main
//
void tableMaker(){

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
  // Open Files
  //
  TString inDir = "Histos/Nominal/";  
  TString outDir = "Plots/";
  
  
  // vector for backgrounds first then signal
  std::vector<TFile*> bkg_files;
  std::vector<TString> bkg_classy_names;
  std::vector<std::string> bkg_file_names;
  std::vector<std::string> bkg_file_names_tex;

  std::vector<TFile*> sig_files;
  std::vector<TString> sig_classy_names;
  std::vector<std::string> sig_file_names;
  std::vector<std::string> sig_file_names_tex;
  
  //double lumi=5.0;
  //double lumi = 2.11;
  double lumi = 2.26;
  
  //
  // data
  //
  bool plotData = true;

  TFile *data_file;
  if(plotData) data_file = new TFile(inDir+"histos__data_singleEl_singleMu_2015CD_25ns.root", "read");

  TFile *f_allBkg = new TFile(inDir+"histos__allBkg_25ns.root", "read");

  //
  // backgrounds
  //

  // Rare (all others)
  TFile *f_rare = new TFile(inDir+"histos__rare_25ns.root", "read");
  bkg_classy_names.push_back(hName_incl);
  bkg_file_names.push_back("Rare");
  bkg_file_names_tex.push_back("Rare");
  bkg_files.push_back(f_rare);
  

  // W+Jets, madgraph pythia8
  TFile *f_wJets = new TFile(inDir+"histos__WJets_25ns.root", "read");
  bkg_classy_names.push_back(hName_incl);
  bkg_file_names.push_back("W+Jets, madgraph");
  bkg_file_names_tex.push_back("$W$+Jets, madgraph");
  bkg_files.push_back(f_wJets);
  

  // DYJets
  TFile *f_dyjets = new TFile(inDir+"histos__DYJets_25ns.root", "read");
  bkg_classy_names.push_back(hName_incl);
  bkg_file_names.push_back("DY Jets, amcnlo");
  bkg_file_names_tex.push_back("DY+Jets, amcnlo");
  bkg_files.push_back(f_dyjets);
  

  // singleT
  TFile *f_singleT = new TFile(inDir+"histos__singleT_25ns.root", "read");
  bkg_classy_names.push_back(hName_incl);
  bkg_file_names.push_back("Single t, powheg");
  bkg_file_names_tex.push_back("Single $t$, powheg");
  bkg_files.push_back(f_singleT);
  

  // ttbar_1l
  TFile *f_ttbar = new TFile(inDir+"histos__ttbar_25ns.root", "read");
  bkg_classy_names.push_back(hName_1lep);
  bkg_file_names.push_back("t#bar{t}, 1l, powheg ext");
  bkg_file_names_tex.push_back("$t\\bar{t}$, 1l, powheg ext");
  //bkg_file_names.push_back("t#bar{t}, 1l, madgraph ext");
  //bkg_file_names_tex.push_back("$t\\bar{t}$, 1l, madgraph ext");
  bkg_files.push_back(f_ttbar);
  
  // ttbar_2l
  bkg_classy_names.push_back(hName_2lep);
  bkg_file_names.push_back("t#bar{t}, 2l, powheg ext");
  bkg_file_names_tex.push_back("$t\\bar{t}$, 2l, powheg ext");
  //bkg_file_names.push_back("t#bar{t}, 2l, madgraph ext");
  //bkg_file_names_tex.push_back("$t\\bar{t}$, 2l, madgraph ext");
  bkg_files.push_back(f_ttbar);
  
    
  //
  // signals
  //
  double sig_SF = 1.0;
  /*
  TFile *f_stop_425_325 = new TFile(inDir+"histos__stop_425_325.root", "read");
  sig_classy_names.push_back(hName_incl);
  sig_file_names.push_back("T2tt(425,325)");
  sig_file_names_tex.push_back("T2tt(425,325)");
  sig_files.push_back(f_stop_425_325);
  
  
  TFile *f_stop_500_325 = new TFile(inDir+"histos__stop_500_325.root", "read");
  sig_classy_names.push_back(hName_incl);
  sig_file_names.push_back("T2tt(500,325)");
  sig_file_names_tex.push_back("T2tt(500,325)");
  sig_files.push_back(f_stop_500_325);
  

  TFile *f_stop_650_325 = new TFile(inDir+"histos__stop_650_325.root", "read");
  sig_classy_names.push_back(hName_incl);
  sig_file_names.push_back("T2tt(650,325)");
  sig_file_names_tex.push_back("T2tt(650,325)");
  sig_files.push_back(f_stop_650_325);
  

  TFile *f_stop_850_100 = new TFile(inDir+"histos__stop_850_100.root", "read");
  sig_classy_names.push_back(hName_incl);
  sig_file_names.push_back("T2tt(850,100)");
  sig_file_names_tex.push_back("T2tt(850,100)");
  sig_files.push_back(f_stop_850_100);
  
  */
  

  // Dummy file, since there exists a weird problem where the integral
  // of the histograms from the last file are all 0
  TFile *f_dummy = new TFile(outDir+"f_dummy.root", "recreate");
 
    
  //
  // Loop over files and grab histograms
  //
  TString hName = "";
  TH1F *h_temp  = NULL;
  
  
  //
  // Make Tables
  //
  const int cats = (int)h_helper.categories.size();
  double totBkg[cats];
  double totBkg_err[cats];

  FILE *yFile;
  TString texFile = outDir;
  texFile += "yieldTable_stop_1l__diLepCR_CRtype_vs_nJets.tex";
  yFile = fopen(texFile.Data(), "w");
  cout << "Writing table: " << texFile.Data() << endl;

  // Tex File Formatting
  fprintf(yFile, "\\documentclass{article}\n");
  fprintf(yFile, "\\usepackage[landscape]{geometry}\n");
  fprintf(yFile, "\\usepackage{chngpage}\n");
  fprintf(yFile, "\\usepackage{graphicx} \n\n");
  fprintf(yFile, "\\begin{document}\n");
  //fprintf(yFile, "\\small\n");
  fprintf(yFile, "\\tiny\n");


  //
  // Backgrounds Columns=nJets, Rows=NCR
  //

  // Get number of columns for table - ie nJets
  fprintf(yFile, "\\begin{table} \n");
  fprintf(yFile, "\\caption{ Sum of all MC Backgrounds } \n");
  fprintf(yFile, "\\scalebox{1.0}{ \n");
  fprintf(yFile, "\\begin{tabular}{|l|");
 
  // Loop over NCR classifications, for nColumns
  for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
    if( h_helper.categories[iCat]->id != k_ee2j_ge250met &&
	h_helper.categories[iCat]->id != k_ee3j_ge250met &&
	h_helper.categories[iCat]->id != k_ge4j_ge250met    ) continue;
    fprintf(yFile,"c|");
  }
  fprintf(yFile, "} \\hline \n");


  // Loop over NCR categories, for titles
  for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
    if( h_helper.categories[iCat]->id != k_ee2j_ge250met &&
	h_helper.categories[iCat]->id != k_ee3j_ge250met &&
	h_helper.categories[iCat]->id != k_ge4j_ge250met    ) continue;
    TString cat_title = h_helper.categories[iCat]->tex;
    fprintf(yFile,"& %s ",cat_title.Data());
  }
  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");


  double ee2j_incl_yield = 0.0;
  double ee2j_incl_error = 0.0;

  double ee3j_incl_yield = 0.0;
  double ee3j_incl_error = 0.0;

  double ge4j_incl_yield = 0.0;
  double ge4j_incl_error = 0.0;

  // Loop over NCR classifications for rows
  for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){
    if( h_helper.classifications[iClassy]->id != k_NCR4 && 
	h_helper.classifications[iClassy]->id != k_NCR5 && 
	h_helper.classifications[iClassy]->id != k_NCR6    ) continue;

    fprintf(yFile, " $%s$ ", h_helper.classifications[iClassy]->tex.Data() );

    // Loop over nJets for rows
    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      if( h_helper.categories[iCat]->id != k_ee2j_ge250met &&
	  h_helper.categories[iCat]->id != k_ee3j_ge250met &&
	  h_helper.categories[iCat]->id != k_ge4j_ge250met    ) continue;
      
      TString hName = "h__yields__";
      hName += h_helper.classifications[iClassy]->label;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      //hName += "__sysError";

      TH1D* h_temp = (TH1D*)f_allBkg->Get(hName);
      if(!h_temp) cout << "BAD allBkg HISTO: " << hName << endl;
      
      double err = 0.0;
      double integral = h_temp->IntegralAndError(0,-1,err);
      fprintf(yFile, " & %.2f $\\pm$ %.2f ", integral, err);

      if(h_helper.categories[iCat]->id == k_ee2j_ge250met){
	ee2j_incl_yield += integral;
	ee2j_incl_error += pow( err, 2 );
      }
      if(h_helper.categories[iCat]->id == k_ee3j_ge250met){
	ee3j_incl_yield += integral;
	ee3j_incl_error += pow( err, 2 );
      }
      if(h_helper.categories[iCat]->id == k_ge4j_ge250met){
	ge4j_incl_yield += integral;
	ge4j_incl_error += pow( err, 2 );
      }
    
      
    } // end loop over nJets categories
    
    fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");

  } // end loop over classifications

  fprintf(yFile, "CR4$~||~$5$~||~$6 ");
  fprintf(yFile, " & %.2f $\\pm$ %.2f ", ee2j_incl_yield, sqrt(ee2j_incl_error) );
  fprintf(yFile, " & %.2f $\\pm$ %.2f ", ee3j_incl_yield, sqrt(ee3j_incl_error) );
  fprintf(yFile, " & %.2f $\\pm$ %.2f ", ge4j_incl_yield, sqrt(ge4j_incl_error) );
  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");

  
  fprintf(yFile, "\\end{tabular} \n");
  fprintf(yFile, "} \n");
  fprintf(yFile, "\\end{table} \n");

  //fprintf(yFile, "\\"); fprintf(yFile, "\\ \n"); 
  //fprintf(yFile, "\\"); fprintf(yFile, "\\ \n"); 
  //fprintf(yFile, "\\"); fprintf(yFile, "\\ \n"); 
  //fprintf(yFile, "\\"); fprintf(yFile, "\\ \n"); 


  //
  // Backgrounds Columns=nJets, Rows=NCR
  //
  
  // Get number of columns for table - ie nJets
  fprintf(yFile, "\\begin{table} \n");
  fprintf(yFile, "\\caption{ Observed Events } \n");
  fprintf(yFile, "\\scalebox{1.0}{ \n");
  fprintf(yFile, "\\begin{tabular}{|l|");

  // Loop over NCR classifications, for nColumns
  for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
    if( h_helper.categories[iCat]->id != k_ee2j_ge250met &&
	h_helper.categories[iCat]->id != k_ee3j_ge250met &&
	h_helper.categories[iCat]->id != k_ge4j_ge250met    ) continue;
    fprintf(yFile,"c|");
  }
  fprintf(yFile, "} \\hline \n");


  // Loop over NCR categories, for titles
  for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
    if( h_helper.categories[iCat]->id != k_ee2j_ge250met &&
	h_helper.categories[iCat]->id != k_ee3j_ge250met &&
	h_helper.categories[iCat]->id != k_ge4j_ge250met    ) continue;
    TString cat_title = h_helper.categories[iCat]->tex;
    fprintf(yFile,"& %s ",cat_title.Data());
  }
  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");

  ee2j_incl_yield = 0.0;
  ee2j_incl_error = 0.0;

  ee3j_incl_yield = 0.0;
  ee3j_incl_error = 0.0;

  ge4j_incl_yield = 0.0;
  ge4j_incl_error = 0.0;

  // Loop over NCR classifications for rows
  for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){
    if( h_helper.classifications[iClassy]->id != k_NCR4 && 
	h_helper.classifications[iClassy]->id != k_NCR5 && 
	h_helper.classifications[iClassy]->id != k_NCR6    ) continue;

    fprintf(yFile, " $%s$ ", h_helper.classifications[iClassy]->tex.Data() );

    // Loop over nJets for rows
    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      if( h_helper.categories[iCat]->id != k_ee2j_ge250met &&
	  h_helper.categories[iCat]->id != k_ee3j_ge250met &&
	  h_helper.categories[iCat]->id != k_ge4j_ge250met    ) continue;
      
      TString hName = "h__yields__";
      hName += h_helper.classifications[iClassy]->label;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      
      TH1D* h_temp = (TH1D*)data_file->Get(hName);
      if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
      
      double err = 0.0;
      double integral = h_temp->IntegralAndError(0,-1,err);
      fprintf(yFile, " & %.2f $\\pm$ %.2f ", integral, err);

      if(h_helper.categories[iCat]->id == k_ee2j_ge250met){
	ee2j_incl_yield += integral;
	ee2j_incl_error += pow( err, 2 );
      }
      if(h_helper.categories[iCat]->id == k_ee3j_ge250met){
	ee3j_incl_yield += integral;
	ee3j_incl_error += pow( err, 2 );
      }
      if(h_helper.categories[iCat]->id == k_ge4j_ge250met){
	ge4j_incl_yield += integral;
	ge4j_incl_error += pow( err, 2 );
      }
      
    } // end loop over nJets categories
    
    fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");

  } // end loop over classifications

  fprintf(yFile, "CR4$~||~$5$~||~$6 ");
  fprintf(yFile, " & %.2f $\\pm$ %.2f ", ee2j_incl_yield, sqrt(ee2j_incl_error) );
  fprintf(yFile, " & %.2f $\\pm$ %.2f ", ee3j_incl_yield, sqrt(ee3j_incl_error) );
  fprintf(yFile, " & %.2f $\\pm$ %.2f ", ge4j_incl_yield, sqrt(ge4j_incl_error) );
  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");

  
  fprintf(yFile, "\\end{tabular} \n");
  fprintf(yFile, "} \n");
  fprintf(yFile, "\\end{table} \n");
  fprintf(yFile, "\\end{document} \n");
  
  fclose(yFile);


  //
  // table of Data, MC, Data/MC for Cats n Classifications NCR4,5,6,Incl
  //
  std::vector<TString> hName_rows;
  /*
  hName_rows.push_back("h__yields__ncr4__nominal__ge3j_ge250met_lt200mt2w");
  hName_rows.push_back("h__yields__ncr4__nominal__ge3j_ge250met_ge200mt2w");
  hName_rows.push_back("h__yields__ncr4__nominal__ge3j_met_250_275");
  hName_rows.push_back("h__yields__ncr4__nominal__ge3j_met_275_325");
  hName_rows.push_back("h__yields__ncr4__nominal__ge3j_met_325_inf");
  hName_rows.push_back("h__yields__ncr5__nominal__ge3j_ge250met_lt200mt2w");
  hName_rows.push_back("h__yields__ncr5__nominal__ge3j_ge250met_ge200mt2w");
  hName_rows.push_back("h__yields__ncr5__nominal__ge3j_met_250_275");
  hName_rows.push_back("h__yields__ncr5__nominal__ge3j_met_275_325");
  hName_rows.push_back("h__yields__ncr5__nominal__ge3j_met_325_inf");
  hName_rows.push_back("h__yields__ncr6__nominal__ge3j_ge250met_lt200mt2w");
  hName_rows.push_back("h__yields__ncr6__nominal__ge3j_ge250met_ge200mt2w");
  hName_rows.push_back("h__yields__ncr6__nominal__ge3j_met_250_275");
  hName_rows.push_back("h__yields__ncr6__nominal__ge3j_met_275_325");
  hName_rows.push_back("h__yields__ncr6__nominal__ge3j_met_325_inf");
  */
  hName_rows.push_back("h__yields__incl__nominal__ee2j_ge250met_ge6p4modTop");
  hName_rows.push_back("h__met__incl__nominal__ee2j_ge250met");
  hName_rows.push_back("h__met__incl__nominal__ee2j_ge250met");
  hName_rows.push_back("h__yields__incl__nominal__ge3j_ge250met_lt200mt2w");
  hName_rows.push_back("h__yields__incl__nominal__ge3j_ge250met_ge200mt2w");
  hName_rows.push_back("h__yields__incl__nominal__ge3j_met_250_275");
  hName_rows.push_back("h__yields__incl__nominal__ge3j_met_275_325");
  hName_rows.push_back("h__yields__incl__nominal__ge3j_met_325_inf");
  

  std::vector<TString> tex_rows;
  /*
  tex_rows.push_back("ncr4,~\\ge3~jets,~\\ge250~MET,~MT2W<200");
  tex_rows.push_back("ncr4,~\\ge3~jets,~\\ge250~MET,~MT2W\\ge200");
  tex_rows.push_back("ncr4,~\\ge3~jets,~250<MET<275");
  tex_rows.push_back("ncr4,~\\ge3~jets,~275<MET<325");
  tex_rows.push_back("ncr4,~\\ge3~jets,~MET>325");
  tex_rows.push_back("ncr5,~\\ge3~jets,~\\ge250~MET,~MT2W<200");
  tex_rows.push_back("ncr5,~\\ge3~jets,~\\ge250~MET,~MT2W\\ge200");
  tex_rows.push_back("ncr5,~\\ge3~jets,~250<MET<275");
  tex_rows.push_back("ncr5,~\\ge3~jets,~275<MET<325");
  tex_rows.push_back("ncr5,~\\ge3~jets,~MET>325");
  tex_rows.push_back("ncr6,~\\ge3~jets,~\\ge250~MET,~MT2W<200");
  tex_rows.push_back("ncr6,~\\ge3~jets,~\\ge250~MET,~MT2W\\ge200");
  tex_rows.push_back("ncr6,~\\ge3~jets,~250<MET<275");
  tex_rows.push_back("ncr6,~\\ge3~jets,~275<MET<325");
  tex_rows.push_back("ncr6,~\\ge3~jets,~MET>325");
  */
  tex_rows.push_back("CR_{\\ell\\ell},~2~jets,~\\ge250~MET,~Mod.Topness>6.4");
  tex_rows.push_back("CR_{\\ell\\ell},~2~jets,~250<MET<275");
  tex_rows.push_back("CR_{\\ell\\ell},~2~jets,~MET>275");
  tex_rows.push_back("CR_{\\ell\\ell},~\\ge3~jets,~\\ge250~MET,~MT2W<200");
  tex_rows.push_back("CR_{\\ell\\ell},~\\ge3~jets,~\\ge250~MET,~MT2W\\ge200");
  tex_rows.push_back("CR_{\\ell\\ell},~\\ge3~jets,~250<MET<275");
  tex_rows.push_back("CR_{\\ell\\ell},~\\ge3~jets,~275<MET<325");
  tex_rows.push_back("CR_{\\ell\\ell},~\\ge3~jets,~MET>325");


  
  texFile = outDir;
  texFile += "yieldTable_stop_1l__diLepCR_dataMC_vs_cats.tex";
  yFile = fopen(texFile.Data(), "w");
  cout << "Writing table: " << texFile.Data() << endl;

  // Tex File Formatting
  fprintf(yFile, "\\documentclass{article}\n");
  fprintf(yFile, "\\usepackage[landscape]{geometry}\n");
  fprintf(yFile, "\\usepackage{chngpage}\n");
  fprintf(yFile, "\\usepackage{graphicx} \n\n");
  fprintf(yFile, "\\begin{document}\n");
  //fprintf(yFile, "\\small\n");
  fprintf(yFile, "\\tiny\n");

  //
  // Backgrounds Columns=Data,MC,Data/MC, Rows=Cats
  //

  // Get number of columns for table - ie nJets
  fprintf(yFile, "\\begin{table} \n");
  fprintf(yFile, "\\caption{ Sum of all MC Backgrounds } \n");
  fprintf(yFile, "\\scalebox{1.0}{ \n");
  fprintf(yFile, "\\begin{tabular}{|l|c|c|c|} \\hline \n");
  fprintf(yFile, " Category & Data & MC & Data/MC ");
  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");

  for(int iRow=0; iRow<(int)hName_rows.size(); iRow++){

    TString hName = hName_rows[iRow];
    TH1D* h_temp = (TH1D*)data_file->Get(hName);
    if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
      
    double data_error = 0.0;
    double data_yield = h_temp->IntegralAndError(0,-1,data_error);
    if( hName_rows[iRow].Contains("__met__") && 
	tex_rows[iRow].Contains("250<MET<275")  ) data_yield = h_temp->IntegralAndError(h_temp->FindBin(250.0),h_temp->FindBin(274.99),data_error);
    if( hName_rows[iRow].Contains("__met__") && 
	tex_rows[iRow].Contains("MET>275")  ) data_yield = h_temp->IntegralAndError(h_temp->FindBin(275.0),-1,data_error);

    //hName += "__sysError";
    h_temp = (TH1D*)f_allBkg->Get(hName);
    if(!h_temp) cout << "BAD ALL BKDG HISTO: " << hName << endl;

    double mc_error = 0.0;
    double mc_yield = h_temp->IntegralAndError(0,-1,mc_error);
    if( hName_rows[iRow].Contains("__met__") && 
	tex_rows[iRow].Contains("250<MET<275")  ) mc_yield = h_temp->IntegralAndError(h_temp->FindBin(250.0),h_temp->FindBin(274.99),mc_error);
    if( hName_rows[iRow].Contains("__met__") && 
	tex_rows[iRow].Contains("MET>275")  ) mc_yield = h_temp->IntegralAndError(h_temp->FindBin(275.0),-1,mc_error);

    double ratio = data_yield/mc_yield;
    double ratio_error = ratio*sqrt( pow(data_error/data_yield,2) + pow(mc_error/mc_yield,2) );

    fprintf(yFile, " $%s$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f ", tex_rows[iRow].Data(), data_yield, data_error, mc_yield, mc_error, ratio, ratio_error);
    fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");

  }
  
  fprintf(yFile, "\\end{tabular} \n");
  fprintf(yFile, "} \n");
  fprintf(yFile, "\\end{table} \n");
  fprintf(yFile, "\\end{document} \n");
  
  fclose(yFile);



  //
  // Ratio plot, MET bins only
  //
  double ratio = 0.0;
  double r_err = 0.0;
  
  TCanvas *can = new TCanvas("can","can",10,10,800,800);
  TH1D *h_ratio = new TH1D("h_ratio_metOnly", "Ratio of Data vs MC for diLepton CRs", 5, 0, 5);
  h_ratio->GetXaxis()->SetBinLabel(1, "2jets, 250<=MET<275");
  h_ratio->GetXaxis()->SetBinLabel(2, "2jets, MET>=275");
  h_ratio->GetXaxis()->SetBinLabel(3, ">=3j, 250<=MET<275");
  h_ratio->GetXaxis()->SetBinLabel(4, ">=3j, 275<=MET<325");
  h_ratio->GetXaxis()->SetBinLabel(5, ">=3j, MET>=325");
  h_ratio->SetStats(0);

  // Get 2 jets,  250<=MET<275
  for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){
    if( h_helper.classifications[iClassy]->id != k_incl ) continue;

    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      if( h_helper.categories[iCat]->id != k_ee2j_ge250met ) continue;
      
      TString hName = "h__met__";
      hName += h_helper.classifications[iClassy]->label;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      
      TH1D* h_temp = (TH1D*)data_file->Get(hName);
      if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
      
      double data_error = 0.0;
      double data_yield = h_temp->IntegralAndError(h_temp->FindBin(250.0),h_temp->FindBin(274.99),data_error);
      
      //hName += "__sysError";
      
      h_temp = (TH1D*)f_allBkg->Get(hName);
      if(!h_temp) cout << "BAD ALLBKG HISTO: " << hName << endl;
      
      double allBkg_error = 0.0;
      double allBkg_yield = h_temp->IntegralAndError(h_temp->FindBin(250.0),h_temp->FindBin(274.99),allBkg_error);
      
      
      double ratio = data_yield/allBkg_yield;
      double ratio_err = ratio*sqrt( pow( data_error/data_yield, 2 ) + pow( allBkg_error/allBkg_yield, 2 ) );

      h_ratio->SetBinContent(1, ratio );
      h_ratio->SetBinError(1, ratio_err);
  
    } // end loop over categories

  } // end loop over classifications


  // Get 2 jets,  MET>=275
  for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){
    if( h_helper.classifications[iClassy]->id != k_incl ) continue;

    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      if( h_helper.categories[iCat]->id != k_ee2j_ge250met ) continue;
      
      TString hName = "h__met__";
      hName += h_helper.classifications[iClassy]->label;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      
      TH1D* h_temp = (TH1D*)data_file->Get(hName);
      if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
      
      double data_error = 0.0;
      double data_yield = h_temp->IntegralAndError(h_temp->FindBin(275.0),-1,data_error);
      
      //hName += "__sysError";
      
      h_temp = (TH1D*)f_allBkg->Get(hName);
      if(!h_temp) cout << "BAD ALLBKG HISTO: " << hName << endl;
      
      double allBkg_error = 0.0;
      double allBkg_yield = h_temp->IntegralAndError(h_temp->FindBin(275.0),-1,allBkg_error);
      
      
      double ratio = data_yield/allBkg_yield;
      double ratio_err = ratio*sqrt( pow( data_error/data_yield, 2 ) + pow( allBkg_error/allBkg_yield, 2 ) );

      h_ratio->SetBinContent(2, ratio );
      h_ratio->SetBinError(2, ratio_err);
  
    } // end loop over categories

  } // end loop over classifications


  // Get >=3 jets, 250<=MET<275
  for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){
    if( h_helper.classifications[iClassy]->id != k_incl ) continue;

    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      if( h_helper.categories[iCat]->id != k_ge3j_met_250_275 ) continue;
      
      TString hName = "h__yields__";
      hName += h_helper.classifications[iClassy]->label;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      
      TH1D* h_temp = (TH1D*)data_file->Get(hName);
      if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
      
      double data_error = 0.0;
      double data_yield = h_temp->IntegralAndError(0,-1,data_error);
      
      //hName += "__sysError";
      
      h_temp = (TH1D*)f_allBkg->Get(hName);
      if(!h_temp) cout << "BAD ALLBKG HISTO: " << hName << endl;
      
      double allBkg_error = 0.0;
      double allBkg_yield = h_temp->IntegralAndError(0,-1,allBkg_error);
      
      
      double ratio = data_yield/allBkg_yield;
      double ratio_err = ratio*sqrt( pow( data_error/data_yield, 2 ) + pow( allBkg_error/allBkg_yield, 2 ) );

      h_ratio->SetBinContent(3, ratio );
      h_ratio->SetBinError(3, ratio_err);
  
    } // end loop over categories

  } // end loop over classifications


  // Get >=3 jets, 275<=MET<325
  for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){
    if( h_helper.classifications[iClassy]->id != k_incl ) continue;

    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      if( h_helper.categories[iCat]->id != k_ge3j_met_275_325 ) continue;
      
      TString hName = "h__yields__";
      hName += h_helper.classifications[iClassy]->label;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      
      TH1D* h_temp = (TH1D*)data_file->Get(hName);
      if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
      
      double data_error = 0.0;
      double data_yield = h_temp->IntegralAndError(0,-1,data_error);
      
      //hName += "__sysError";
      
      h_temp = (TH1D*)f_allBkg->Get(hName);
      if(!h_temp) cout << "BAD ALLBKG HISTO: " << hName << endl;
      
      double allBkg_error = 0.0;
      double allBkg_yield = h_temp->IntegralAndError(0,-1,allBkg_error);
      
      
      double ratio = data_yield/allBkg_yield;
      double ratio_err = ratio*sqrt( pow( data_error/data_yield, 2 ) + pow( allBkg_error/allBkg_yield, 2 ) );

      h_ratio->SetBinContent(4, ratio );
      h_ratio->SetBinError(4, ratio_err);
  
    } // end loop over categories

  } // end loop over classifications


  // Get >=3 jets, MET>=325
  for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){
    if( h_helper.classifications[iClassy]->id != k_incl ) continue;

    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      if( h_helper.categories[iCat]->id != k_ge3j_met_325_inf ) continue;
      
      TString hName = "h__yields__";
      hName += h_helper.classifications[iClassy]->label;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      
      TH1D* h_temp = (TH1D*)data_file->Get(hName);
      if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
      
      double data_error = 0.0;
      double data_yield = h_temp->IntegralAndError(0,-1,data_error);
      
      //hName += "__sysError";
      
      h_temp = (TH1D*)f_allBkg->Get(hName);
      if(!h_temp) cout << "BAD ALLBKG HISTO: " << hName << endl;
      
      double allBkg_error = 0.0;
      double allBkg_yield = h_temp->IntegralAndError(0,-1,allBkg_error);
      
      
      double ratio = data_yield/allBkg_yield;
      double ratio_err = ratio*sqrt( pow( data_error/data_yield, 2 ) + pow( allBkg_error/allBkg_yield, 2 ) );

      h_ratio->SetBinContent(5, ratio );
      h_ratio->SetBinError(5, ratio_err);
  
    } // end loop over categories

  } // end loop over classifications


  TLine *l_unity = new TLine(0.0,1.0,h_ratio->GetXaxis()->GetBinUpEdge(h_ratio->GetNbinsX()),1.0);
  l_unity->SetLineColor(kRed);
  l_unity->SetLineWidth(2);
  
  h_ratio->Draw("e1");
  l_unity->Draw();

  h_ratio->Draw("e1 same");
  
  can->SaveAs(outDir+"data_vs_mc__diLep_CR4_5_6__ge3j__ge250met__ratioOfCRs__metOnly.pdf");
  can->~TCanvas();



  //
  // Ratio plot, All CRs of interest
  //
  ratio = 0.0;
  r_err = 0.0;
  
  can = new TCanvas("can","can",10,10,800,800);
  h_ratio = new TH1D("h_ratio_allCRs", "Ratio of Data vs MC for diLepton CRs", 8, 0, 8);
  h_ratio->GetXaxis()->SetBinLabel(1, "2jets, 250<=MET<275");
  h_ratio->GetXaxis()->SetBinLabel(2, "2jets, MET>=275");
  h_ratio->GetXaxis()->SetBinLabel(3, "2jets, Mod.Topness>6.4");
  h_ratio->GetXaxis()->SetBinLabel(4, ">=3jets, 250<=MET<275");
  h_ratio->GetXaxis()->SetBinLabel(5, ">=3jets, 275<=MET<325");
  h_ratio->GetXaxis()->SetBinLabel(6, ">=3jets, MET>=325");
  h_ratio->GetXaxis()->SetBinLabel(7, ">=3jets, MT2W<200");
  h_ratio->GetXaxis()->SetBinLabel(8, ">=3jets, MT2W>=200");
  h_ratio->SetStats(0);

    // Get 2 jets,  250<=MET<275
  for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){
    if( h_helper.classifications[iClassy]->id != k_incl ) continue;

    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      if( h_helper.categories[iCat]->id != k_ee2j_ge250met ) continue;
      
      TString hName = "h__met__";
      hName += h_helper.classifications[iClassy]->label;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      
      TH1D* h_temp = (TH1D*)data_file->Get(hName);
      if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
      
      double data_error = 0.0;
      double data_yield = h_temp->IntegralAndError(h_temp->FindBin(250.0),h_temp->FindBin(274.99),data_error);
      
      //hName += "__sysError";
      
      h_temp = (TH1D*)f_allBkg->Get(hName);
      if(!h_temp) cout << "BAD ALLBKG HISTO: " << hName << endl;
      
      double allBkg_error = 0.0;
      double allBkg_yield = h_temp->IntegralAndError(h_temp->FindBin(250.0),h_temp->FindBin(274.99),allBkg_error);
      
      
      double ratio = data_yield/allBkg_yield;
      double ratio_err = ratio*sqrt( pow( data_error/data_yield, 2 ) + pow( allBkg_error/allBkg_yield, 2 ) );

      h_ratio->SetBinContent(1, ratio );
      h_ratio->SetBinError(1, ratio_err);
  
    } // end loop over categories

  } // end loop over classifications


  // Get 2 jets,  MET>=275
  for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){
    if( h_helper.classifications[iClassy]->id != k_incl ) continue;

    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      if( h_helper.categories[iCat]->id != k_ee2j_ge250met ) continue;
      
      TString hName = "h__met__";
      hName += h_helper.classifications[iClassy]->label;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      
      TH1D* h_temp = (TH1D*)data_file->Get(hName);
      if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
      
      double data_error = 0.0;
      double data_yield = h_temp->IntegralAndError(h_temp->FindBin(275.0),-1,data_error);
      
      //hName += "__sysError";
      
      h_temp = (TH1D*)f_allBkg->Get(hName);
      if(!h_temp) cout << "BAD ALLBKG HISTO: " << hName << endl;
      
      double allBkg_error = 0.0;
      double allBkg_yield = h_temp->IntegralAndError(h_temp->FindBin(275.0),-1,allBkg_error);
      
      
      double ratio = data_yield/allBkg_yield;
      double ratio_err = ratio*sqrt( pow( data_error/data_yield, 2 ) + pow( allBkg_error/allBkg_yield, 2 ) );

      h_ratio->SetBinContent(2, ratio );
      h_ratio->SetBinError(2, ratio_err);
  
    } // end loop over categories

  } // end loop over classifications


  // Get 2 jets, Modified Topness>6.4
  for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){
    if( h_helper.classifications[iClassy]->id != k_incl ) continue;

    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      if( h_helper.categories[iCat]->id != k_ee2j_ge250met_ge6p4modTop ) continue;
      
      TString hName = "h__yields__";
      hName += h_helper.classifications[iClassy]->label;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      
      TH1D* h_temp = (TH1D*)data_file->Get(hName);
      if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
      
      double data_error = 0.0;
      double data_yield = h_temp->IntegralAndError(0,-1,data_error);
      
      //hName += "__sysError";
      
      h_temp = (TH1D*)f_allBkg->Get(hName);
      if(!h_temp) cout << "BAD ALLBKG HISTO: " << hName << endl;
      
      double allBkg_error = 0.0;
      double allBkg_yield = h_temp->IntegralAndError(0,-1,allBkg_error);
      
      
      double ratio = data_yield/allBkg_yield;
      double ratio_err = ratio*sqrt( pow( data_error/data_yield, 2 ) + pow( allBkg_error/allBkg_yield, 2 ) );

      h_ratio->SetBinContent(3, ratio );
      h_ratio->SetBinError(3, ratio_err);
  
    } // end loop over categories

  } // end loop over classifications




  // Get >=3 jets, 250<=MET<275
  for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){
    if( h_helper.classifications[iClassy]->id != k_incl ) continue;

    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      if( h_helper.categories[iCat]->id != k_ge3j_met_250_275 ) continue;
      
      TString hName = "h__yields__";
      hName += h_helper.classifications[iClassy]->label;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      
      TH1D* h_temp = (TH1D*)data_file->Get(hName);
      if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
      
      double data_error = 0.0;
      double data_yield = h_temp->IntegralAndError(0,-1,data_error);
      
      //hName += "__sysError";
      
      h_temp = (TH1D*)f_allBkg->Get(hName);
      if(!h_temp) cout << "BAD ALLBKG HISTO: " << hName << endl;
      
      double allBkg_error = 0.0;
      double allBkg_yield = h_temp->IntegralAndError(0,-1,allBkg_error);
      
      
      double ratio = data_yield/allBkg_yield;
      double ratio_err = ratio*sqrt( pow( data_error/data_yield, 2 ) + pow( allBkg_error/allBkg_yield, 2 ) );

      h_ratio->SetBinContent(4, ratio );
      h_ratio->SetBinError(4, ratio_err);
  
    } // end loop over categories

  } // end loop over classifications


  // Get >=3 jets, 275<=MET<325
  for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){
    if( h_helper.classifications[iClassy]->id != k_incl ) continue;

    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      if( h_helper.categories[iCat]->id != k_ge3j_met_275_325 ) continue;
      
      TString hName = "h__yields__";
      hName += h_helper.classifications[iClassy]->label;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      
      TH1D* h_temp = (TH1D*)data_file->Get(hName);
      if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
      
      double data_error = 0.0;
      double data_yield = h_temp->IntegralAndError(0,-1,data_error);
      
      //hName += "__sysError";
      
      h_temp = (TH1D*)f_allBkg->Get(hName);
      if(!h_temp) cout << "BAD ALLBKG HISTO: " << hName << endl;
      
      double allBkg_error = 0.0;
      double allBkg_yield = h_temp->IntegralAndError(0,-1,allBkg_error);
      
      
      double ratio = data_yield/allBkg_yield;
      double ratio_err = ratio*sqrt( pow( data_error/data_yield, 2 ) + pow( allBkg_error/allBkg_yield, 2 ) );

      h_ratio->SetBinContent(5, ratio );
      h_ratio->SetBinError(5, ratio_err);
  
    } // end loop over categories

  } // end loop over classifications


  // Get >=3 jets, MET>=325
  for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){
    if( h_helper.classifications[iClassy]->id != k_incl ) continue;

    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      if( h_helper.categories[iCat]->id != k_ge3j_met_325_inf ) continue;
      
      TString hName = "h__yields__";
      hName += h_helper.classifications[iClassy]->label;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      
      TH1D* h_temp = (TH1D*)data_file->Get(hName);
      if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
      
      double data_error = 0.0;
      double data_yield = h_temp->IntegralAndError(0,-1,data_error);
      
      //hName += "__sysError";
      
      h_temp = (TH1D*)f_allBkg->Get(hName);
      if(!h_temp) cout << "BAD ALLBKG HISTO: " << hName << endl;
      
      double allBkg_error = 0.0;
      double allBkg_yield = h_temp->IntegralAndError(0,-1,allBkg_error);
      
      
      double ratio = data_yield/allBkg_yield;
      double ratio_err = ratio*sqrt( pow( data_error/data_yield, 2 ) + pow( allBkg_error/allBkg_yield, 2 ) );

      h_ratio->SetBinContent(6, ratio );
      h_ratio->SetBinError(6, ratio_err);
  
    } // end loop over categories

  } // end loop over classifications


  
  // Get >=3 jets, MT2W<200
  for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){
    if( h_helper.classifications[iClassy]->id != k_incl ) continue;

    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      if( h_helper.categories[iCat]->id != k_ge3j_ge250met_lt200mt2w ) continue;
      
      TString hName = "h__yields__";
      hName += h_helper.classifications[iClassy]->label;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      
      TH1D* h_temp = (TH1D*)data_file->Get(hName);
      if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
      
      double data_error = 0.0;
      double data_yield = h_temp->IntegralAndError(0,-1,data_error);
      
      //hName += "__sysError";
      
      h_temp = (TH1D*)f_allBkg->Get(hName);
      if(!h_temp) cout << "BAD ALLBKG HISTO: " << hName << endl;
      
      double allBkg_error = 0.0;
      double allBkg_yield = h_temp->IntegralAndError(0,-1,allBkg_error);
      
      
      double ratio = data_yield/allBkg_yield;
      double ratio_err = ratio*sqrt( pow( data_error/data_yield, 2 ) + pow( allBkg_error/allBkg_yield, 2 ) );

      h_ratio->SetBinContent(7, ratio );
      h_ratio->SetBinError(7, ratio_err);
  
    } // end loop over categories

  } // end loop over classifications


  // Get >=3 jets, MT2W>=200
  for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){
    if( h_helper.classifications[iClassy]->id != k_incl ) continue;

    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      if( h_helper.categories[iCat]->id != k_ge3j_ge250met_ge200mt2w ) continue;
      
      TString hName = "h__yields__";
      hName += h_helper.classifications[iClassy]->label;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      
      TH1D* h_temp = (TH1D*)data_file->Get(hName);
      if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
      
      double data_error = 0.0;
      double data_yield = h_temp->IntegralAndError(0,-1,data_error);
      
      //hName += "__sysError";
      
      h_temp = (TH1D*)f_allBkg->Get(hName);
      if(!h_temp) cout << "BAD ALLBKG HISTO: " << hName << endl;
      
      double allBkg_error = 0.0;
      double allBkg_yield = h_temp->IntegralAndError(0,-1,allBkg_error);
      
      
      double ratio = data_yield/allBkg_yield;
      double ratio_err = ratio*sqrt( pow( data_error/data_yield, 2 ) + pow( allBkg_error/allBkg_yield, 2 ) );

      h_ratio->SetBinContent(8, ratio );
      h_ratio->SetBinError(8, ratio_err);
  
    } // end loop over categories

  } // end loop over classifications
  


  l_unity = new TLine(0.0,1.0,h_ratio->GetXaxis()->GetBinUpEdge(h_ratio->GetNbinsX()),1.0);
  l_unity->SetLineColor(kRed);
  l_unity->SetLineWidth(2);
  
  h_ratio->Draw("e1");
  l_unity->Draw();

  h_ratio->Draw("e1 same");
  
  can->SaveAs(outDir+"data_vs_mc__diLep_CR__ratioOfCRs.pdf");
  can->~TCanvas();


  //
  // Clean up
  //
  
  if(plotData) data_file->Close();

  for(int iBkg=0; iBkg<(int)bkg_files.size(); iBkg++){
    bkg_files[iBkg]->Close();
  }
  for(int iSig=0; iSig<(int)sig_files.size(); iSig++){
    sig_files[iSig]->Close();
  }
  f_dummy->Close();
  
  return;
}
