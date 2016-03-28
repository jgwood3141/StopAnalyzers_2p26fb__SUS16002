// ROOT
#include "TFile.h"
#include "TH1.h"
#include "TString.h"
#include "TColor.h"
#include "TAxis.h"

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
  TString hName_0lep = "";
  TString hName_1lep = "";
  TString hName_2lep = "";
  TString hName_ZtoNuNu = "";
  TString hName_ElEl = "";
  TString hName_ElEl_1lep = "";
  TString hName_ElEl_2lep = "";
  TString hName_ElMu = "";
  TString hName_ElMu_1lep = "";
  TString hName_ElMu_2lep = "";
  TString hName_MuMu = "";
  TString hName_MuMu_1lep = "";
  TString hName_MuMu_2lep = "";
  
  for(int iClassy=0; iClassy<(int)h_helper.classifications.size(); iClassy++){
    if( h_helper.classifications[iClassy]->id == k_incl ){
      hName_incl = h_helper.classifications[iClassy]->label;
    }
    if( h_helper.classifications[iClassy]->id == k_ee0lep ){
      hName_0lep = h_helper.classifications[iClassy]->label;
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
    if( h_helper.classifications[iClassy]->id == k_elel ){
      hName_ElEl = h_helper.classifications[iClassy]->label;
    }
    if( h_helper.classifications[iClassy]->id == k_elel_ee1lep ){
      hName_ElEl_1lep = h_helper.classifications[iClassy]->label;
    }
    if( h_helper.classifications[iClassy]->id == k_elel_ge2lep ){
      hName_ElEl_2lep = h_helper.classifications[iClassy]->label;
    }
    if( h_helper.classifications[iClassy]->id == k_elmu ){
      hName_ElMu = h_helper.classifications[iClassy]->label;
    }
    if( h_helper.classifications[iClassy]->id == k_elmu_ee1lep ){
      hName_ElMu_1lep = h_helper.classifications[iClassy]->label;
    }
    if( h_helper.classifications[iClassy]->id == k_elmu_ge2lep ){
      hName_ElMu_2lep = h_helper.classifications[iClassy]->label;
    }
    if( h_helper.classifications[iClassy]->id == k_mumu ){
      hName_MuMu = h_helper.classifications[iClassy]->label;
    }
    if( h_helper.classifications[iClassy]->id == k_mumu_ee1lep ){
      hName_MuMu_1lep = h_helper.classifications[iClassy]->label;
    }
    if( h_helper.classifications[iClassy]->id == k_mumu_ge2lep ){
      hName_MuMu_2lep = h_helper.classifications[iClassy]->label;
    }

  }

  std::vector<TString> flav_loop;
  flav_loop.push_back(hName_incl);
  flav_loop.push_back(hName_ElEl);
  flav_loop.push_back(hName_ElMu);
  flav_loop.push_back(hName_MuMu);

  std::vector<TString> tt1l_flav_loop;
  tt1l_flav_loop.push_back(hName_1lep);
  tt1l_flav_loop.push_back(hName_ElEl_1lep);
  tt1l_flav_loop.push_back(hName_ElMu_1lep);
  tt1l_flav_loop.push_back(hName_MuMu_1lep);

  std::vector<TString> tt2l_flav_loop;
  tt2l_flav_loop.push_back(hName_2lep);
  tt2l_flav_loop.push_back(hName_ElEl_2lep);
  tt2l_flav_loop.push_back(hName_ElMu_2lep);
  tt2l_flav_loop.push_back(hName_MuMu_2lep);

    
  TString hName_nominal_sys = "";
  for(int iSys=0; iSys<(int)h_helper.systematics.size(); iSys++){
    if( h_helper.systematics[iSys]->id == k_nominal ){
      hName_nominal_sys = h_helper.systematics[iSys]->label;
    }
  }

  
  for(int iFlav=0; iFlav<(int)flav_loop.size(); iFlav++){

    TString hName_flav = flav_loop[iFlav];
    TString hName_flav_tt1l = tt1l_flav_loop[iFlav];
    TString hName_flav_tt2l = tt2l_flav_loop[iFlav];


    //
    // Open Files
    //
    TString inDir = "Histos/Nominal/";
    TString outDir = "Plots/";

    // vector for kColors, list backgrounds first then signal
    std::vector<Color_t> colors; 
    
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
    if(plotData) data_file = new TFile(inDir+"histos__data_25ns.root", "read");

    TFile *f_allBkg = new TFile(inDir+"histos__allBkg_25ns.root", "read");
    
    //
    // backgrounds
    //
    
    // Rare (all others)
    TFile *f_rare = new TFile(inDir+"histos__rare_25ns.root", "read");
    bkg_classy_names.push_back(hName_flav);
    bkg_file_names.push_back("Rare");
    bkg_file_names_tex.push_back("Rare");
    bkg_files.push_back(f_rare);
    

    // W+Jets, madgraph pythia8
    TFile *f_wJets = new TFile(inDir+"histos__WJets_25ns.root", "read");
    bkg_classy_names.push_back(hName_flav);
    bkg_file_names.push_back("W+Jets, madgraph");
    bkg_file_names_tex.push_back("$W$+Jets, madgraph");
    bkg_files.push_back(f_wJets);
    
    
    // DYJets
    TFile *f_dyjets = new TFile(inDir+"histos__DYJets_25ns.root", "read");
    bkg_classy_names.push_back(hName_flav);
    bkg_file_names.push_back("DY Jets, amcnlo");
    bkg_file_names_tex.push_back("DY+Jets, amcnlo");
    bkg_files.push_back(f_dyjets);
    
    
    // singleT
    TFile *f_singleT = new TFile(inDir+"histos__singleT_25ns.root", "read");
    bkg_classy_names.push_back(hName_flav);
    bkg_file_names.push_back("Single t, powheg");
    bkg_file_names_tex.push_back("Single $t$, powheg");
    bkg_files.push_back(f_singleT);
    

    // ttbar_1l
    TFile *f_ttbar = new TFile(inDir+"histos__ttbar_25ns.root", "read");
    bkg_classy_names.push_back(hName_flav_tt1l);
    //bkg_file_names.push_back("t#bar{t}, 1l, powheg");
    //bkg_file_names_tex.push_back("$t\\bar{t}$, 1l, powheg");
    bkg_file_names.push_back("t#bar{t}, 1l, powheg ext");
    bkg_file_names_tex.push_back("$t\\bar{t}$, 1l, powheg ext");
    //bkg_file_names.push_back("t#bar{t}, 1l, madgraph ext");
    //bkg_file_names_tex.push_back("$t\\bar{t}$, 1l, madgraph ext");
    bkg_files.push_back(f_ttbar);
    

    // ttbar_2l
    bkg_classy_names.push_back(hName_flav_tt2l);
    //bkg_file_names.push_back("t#bar{t}, 2l, powheg");
    //bkg_file_names_tex.push_back("$t\\bar{t}$, 2l, powheg");
    bkg_file_names.push_back("t#bar{t}, 2l, powheg ext");
    bkg_file_names_tex.push_back("$t\\bar{t}$, 2l, powheg ext");
    //bkg_file_names.push_back("t#bar{t}, 2l, madgraph ext");
    //bkg_file_names_tex.push_back("$t\\bar{t}$, 2l, madgraph ext");
    bkg_files.push_back(f_ttbar);
    
    
    //
    // signals
    //
    double sig_SF = 1.0;
    
    //TFile *f_stop_425_325 = new TFile(inDir+"histos__stop_425_325_noNegYield_25ns.root", "read");
    //sig_classy_names.push_back(hName_flav);
    //sig_file_names.push_back("T2tt(425,325)");
    //sig_file_names_tex.push_back("T2tt(425,325)");
    //sig_files.push_back(f_stop_425_325);
    
  
    //TFile *f_stop_500_325 = new TFile(inDir+"histos__stop_500_325_noNegYield_25ns.root", "read");
    //sig_classy_names.push_back(hName_flav);
    //sig_file_names.push_back("T2tt(500,325)");
    //sig_file_names_tex.push_back("T2tt(500,325)");
    //sig_files.push_back(f_stop_500_325);
    

    //TFile *f_stop_650_325 = new TFile(inDir+"histos__stop_650_325_noNegYield_25ns.root", "read");
    //sig_classy_names.push_back(hName_flav);
    //sig_file_names.push_back("T2tt(650,325)");
    //sig_file_names_tex.push_back("T2tt(650,325)");
    //sig_files.push_back(f_stop_650_325);
    
    
    //TFile *f_stop_850_100 = new TFile(inDir+"histos__stop_850_100_noNegYield_25ns.root", "read");
    //sig_classy_names.push_back(hName_flav);
    //sig_file_names.push_back("T2tt(850,100)");
    //sig_file_names_tex.push_back("T2tt(850,100)");
    //sig_files.push_back(f_stop_850_100);
    
    
    
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
    texFile += "yieldTable_stop_1l";
    texFile += hName_flav;
    texFile += "__productionMode.tex";
    yFile = fopen(texFile.Data(), "w");

    cout << "Writing Yield Table To: " << endl;
    cout << "    " << texFile << endl;
    
    // Tex File Formatting
    fprintf(yFile, "\\documentclass{article}\n");
    fprintf(yFile, "\\usepackage[landscape]{geometry}\n");
    fprintf(yFile, "\\usepackage{chngpage}\n\n");
    fprintf(yFile, "\\begin{document}\n");
    //fprintf(yFile, "\\small\n");
    fprintf(yFile, "\\tiny\n");
    
    
    //
    // Make Tables, 2 jets, 0,1,2 bTags
    //
    
    // Get number of collumns for table - ie categories
    fprintf(yFile, "\\begin{tabular}{|l|");
    
    // Loop over catogories
    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      TString cat_title = "";
      cat_title += h_helper.categories[iCat]->tex;
      //if(!cat_title.Contains("Low")) continue;
      if(cat_title.Contains("MET")) continue;
      if(cat_title.Contains("3~Jets")) continue;
      if(cat_title.Contains("==")) continue;
      
      fprintf(yFile,"c|");
    }
    fprintf(yFile, "c|} \\hline \n");

    
    // Loop over catogories for titles
    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      TString cat_title = "";
      cat_title += h_helper.categories[iCat]->tex;
      //if(!cat_title.Contains("Low")) continue;
      if(cat_title.Contains("MET")) continue;
      if(cat_title.Contains("3~Jets")) continue;
      if(cat_title.Contains("==")) continue;
      
      fprintf(yFile,"& %s ",cat_title.Data());
      
    }
    fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
    
  
    // Loop over signal files
    for(int iSig=0; iSig<(int)sig_file_names_tex.size(); iSig++){
      
      // Signal name
      fprintf(yFile,"%s", sig_file_names_tex[iSig].c_str());
      
      // Loop over categories to get signal yields
      for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
	TString cat_title = "";
	cat_title += h_helper.categories[iCat]->tex;
	//if(!cat_title.Contains("Low")) continue;
	if(cat_title.Contains("MET")) continue;
	if(cat_title.Contains("3~Jets")) continue;
	if(cat_title.Contains("==")) continue;

	TString hName = "h__yields__";
	hName += sig_classy_names[iSig];
	hName += "__";
	hName += hName_nominal_sys;
	hName += "__";
	hName += h_helper.categories[iCat]->label;
	//hName += "__sysError";
	
	TH1D* h_temp = (TH1D*)sig_files[iSig]->Get(hName);
	if(!h_temp) cout << "BAD SIG HISTO: " << hName << endl;
	
	// Signal Yields
	double error = 0.0;
	double integral = h_temp->IntegralAndError(0,-1, error);
	fprintf(yFile, " & %.2f $\\pm$ %.2f", integral, error );
	
      } // end loop over categories
      
      fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
      
    } // end loop over signals
    
    
    // Loop over backgrounds
    for(int iBkg=0; iBkg<(int)bkg_files.size(); iBkg++){

      // Background name
      fprintf(yFile,"%s", bkg_file_names_tex[iBkg].c_str());
      
      // Loop over categories to get background yields
      for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
	TString cat_title = "";
	cat_title += h_helper.categories[iCat]->tex;
	//if(!cat_title.Contains("Low")) continue;
	if(cat_title.Contains("MET")) continue;
	if(cat_title.Contains("3~Jets")) continue;
	if(cat_title.Contains("==")) continue;
	
	TString hName = "h__yields__";
	hName += bkg_classy_names[iBkg];
	hName += "__";
	hName += hName_nominal_sys;
	hName += "__";
	hName += h_helper.categories[iCat]->label;
	//hName += "__sysError";
	
	TH1D* h_temp = (TH1D*)bkg_files[iBkg]->Get(hName);
	if(!h_temp) cout << "BAD BKG HISTO: " << hName << endl;
	
	// Background Yields
	double error = 0.0;
	if(iBkg==0) totBkg[iCat]  = h_temp->IntegralAndError(0,-1,error);
	else        totBkg[iCat] += h_temp->IntegralAndError(0,-1,error);
	
	if(iBkg==0) totBkg_err[iCat]  = pow(error,2);
	else        totBkg_err[iCat] += pow(error,2);
	
	double integral = h_temp->IntegralAndError(0,-1,error);
	fprintf(yFile, " & %.2f $\\pm$ %.2f ", integral, error );
	
      } // end loop over cats

      fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
      
    } // end loop over bkg
    
  
    // Yields for total Background
    fprintf(yFile,"Total Background");
    
    // Loop over categories to get background yields
    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      TString cat_title = "";
      cat_title += h_helper.categories[iCat]->tex;
      //if(!cat_title.Contains("Low")) continue;
      if(cat_title.Contains("MET")) continue;
      if(cat_title.Contains("3~Jets")) continue;
      if(cat_title.Contains("==")) continue;
      
      TString hName = "h__yields__";
      hName += hName_flav;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      //hName += "__sysError";
      
      TH1D* h_temp = (TH1D*)f_allBkg->Get(hName);
      if(!h_temp) cout << "BAD ALL BKG HISTO: " << hName << endl;
      
      // All Bkg Yields
      double error = 0.0;
      double integral = h_temp->IntegralAndError(0,-1,error);
      fprintf(yFile, " & %.2f $\\pm$ %.2f ", integral, error );
      //fprintf(yFile, " & %.2f $\\pm$ %.2f ", totBkg[iCat], sqrt(totBkg_err[iCat]) );
    }
    fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
    
    // Yields for data
    if(plotData){
      fprintf(yFile, "Data");
      
      // Loop over categories for data yields
      for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
	TString cat_title = "";
	cat_title += h_helper.categories[iCat]->tex;
	//if(!cat_title.Contains("Low")) continue;
	if(cat_title.Contains("MET")) continue;
	if(cat_title.Contains("3~Jets")) continue;
	if(cat_title.Contains("==")) continue;
	
	TString hName = "h__yields__";
	hName += hName_flav;
	hName += "__";
	hName += hName_nominal_sys;
	hName += "__";
	hName += h_helper.categories[iCat]->label;
	
	TH1D* h_temp = (TH1D*)data_file->Get(hName);
	if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
	
	// Data Yields
	double error = 0.0;
	double integral = h_temp->IntegralAndError(0,-1,error);
	fprintf(yFile, " & %.2f ", integral );
	
      } // end loop over categories
      
      fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
      
    } // end if plotting data
    

    // Data/MC
    if(plotData){
      fprintf(yFile, "Data/MC");
      
      // Loop over categories for data yields
      for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
	TString cat_title = "";
	cat_title += h_helper.categories[iCat]->tex;
	//if(!cat_title.Contains("Low")) continue;
	if(cat_title.Contains("MET")) continue;
	if(cat_title.Contains("3~Jets")) continue;
	if(cat_title.Contains("==")) continue;
	
	TString hName = "h__yields__";
	hName += hName_flav;
	hName += "__";
	hName += hName_nominal_sys;
	hName += "__";
	hName += h_helper.categories[iCat]->label;
	
	TH1D* h_temp = (TH1D*)data_file->Get(hName);
	if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
	
	// Data Yields
	double error = 0.0;
	double integral = h_temp->IntegralAndError(0,-1,error);

	
	//hName += "__sysError";
	h_temp = (TH1D*)f_allBkg->Get(hName);
	if(!h_temp) cout << "BAD ALL BKG HISTO: " << hName << endl;
	
	// All Bkg Yields
	double error_allBkg = 0.0;
	double integral_allBkg = h_temp->IntegralAndError(0,-1,error);
	
	
	// Data/MC
	//double ratio = integral/totBkg[iCat];
	//double r_err = ratio*sqrt( pow(error/integral,2)+pow(sqrt(totBkg_err[iCat])/totBkg[iCat],2) );
	
	double ratio = integral/integral_allBkg;
	double r_err = ratio*sqrt( pow(error/integral,2)+pow(sqrt(error_allBkg)/integral_allBkg,2) );
	
      fprintf(yFile, " & %.2f $\\pm$ %.2f ", ratio, r_err );
      
      } // end loop over categories
      
      fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
      
    } // end if plotting data
    
    
    fprintf(yFile, "\\end{tabular} \n");
    
    fprintf(yFile, "\\"); fprintf(yFile, "\\ \n"); 
    fprintf(yFile, "\\"); fprintf(yFile, "\\ \n"); 
    fprintf(yFile, "\\"); fprintf(yFile, "\\ \n"); 
    fprintf(yFile, "\\"); fprintf(yFile, "\\ \n"); 
    
    fprintf(yFile, "\\end{document} \n");

    fclose(yFile);
    


    //
    // Table of diLep pT
    //
    texFile = outDir;
    texFile += "yieldTable_stop_1l";
    texFile += hName_flav;
    texFile += "__diLepPt_dataMC.tex";
    yFile = fopen(texFile.Data(), "w");

    cout << "Writing Yield Table To: " << endl;
    cout << "    " << texFile << endl;
    
    // Tex File Formatting
    fprintf(yFile, "\\documentclass{article}\n");
    fprintf(yFile, "\\usepackage[landscape]{geometry}\n");
    fprintf(yFile, "\\usepackage{chngpage}\n\n");
    fprintf(yFile, "\\begin{document}\n");
    //fprintf(yFile, "\\small\n");
    fprintf(yFile, "\\tiny\n");
    
    
    //
    // Make Tables, 2 jets, 1 btag, diLept mass 
    //
    
    // Get number of collumns for table - ie categories
    fprintf(yFile, "\\begin{tabular}{|l|c|c|c|");
    fprintf(yFile, "} \\hline \n");

    fprintf(yFile,"diLep pT bin & Data & MC & Data/MC ");
    fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");

    TH1D* h_data = (TH1D*)data_file->Get("h__diLep_pt__incl__nominal__ge2j_ge1t_gt0met");
    TH1D* h_mc = (TH1D*)f_allBkg->Get("h__diLep_pt__incl__nominal__ge2j_ge1t_gt0met");

    int nBins_pt = 5;
    double xBins[6]{ 150.0, 200.0, 250.0, 350.0, 450.0, 550.0 };

    TH1D* h_data_rebin = (TH1D*)h_data->Rebin(nBins_pt, "h_data_diLep_pt_rebin", xBins);
    TH1D* h_mc_rebin = (TH1D*)h_mc->Rebin(nBins_pt, "h_mc_diLep_pt_rebin", xBins);

    for(int iBin=1; iBin<=nBins_pt; iBin++){
      double data_error = h_data_rebin->GetBinError(iBin);
      double data_yield = h_data_rebin->GetBinContent(iBin);

      double mc_error = h_mc_rebin->GetBinError(iBin);
      double mc_yield = h_mc_rebin->GetBinContent(iBin);

      double ratio = data_yield/mc_yield;
      double ratio_error = ratio*sqrt( pow(data_error/data_yield, 2) + pow(mc_error/mc_yield, 2) );

      fprintf(yFile, "%.1f - %.1f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f ", h_data_rebin->GetXaxis()->GetBinLowEdge(iBin), h_data_rebin->GetXaxis()->GetBinUpEdge(iBin), data_yield, data_error, mc_yield, mc_error, ratio, ratio_error);
      
      fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
    }
    fprintf(yFile, "\\end{tabular} \n");
    fprintf(yFile, "\\end{document} \n");
    fclose(yFile);
    

    
  
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
    
  } // end loop over flavours

  return;

}
