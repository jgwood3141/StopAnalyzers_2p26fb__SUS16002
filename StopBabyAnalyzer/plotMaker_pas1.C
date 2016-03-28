// ROOT
#include "TFile.h"
#include "TH1.h"
#include "TString.h"
#include "TColor.h"

// std
#include <vector>

// histoHelper
#include "histoHelper.h"

// dataMCplotMaker
#include "../../Software/dataMCplotMaker/dataMCplotMaker.cc"

//
// Main
//
void plotMaker_pas1(){

  //
  // histoHelper for categories
  //
  histoHelper h_helper;

  TString hName_incl = "";
  TString hName_0lep = "";
  TString hName_1lep = "";
  TString hName_2lep = "";
  TString hName_ZtoNuNu = "";

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
  
  TString outDir = "Plots_pas1/";
  
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
  
  //double lumi=3.0;
  //double lumi=2.11;
  double lumi=2.26;
  
  //
  // data
  //
  bool plotData = true;

  TFile *data_file;
  //if(plotData) data_file = new TFile(inDir+"histos__data_25ns.root", "read");
  if(plotData) data_file = new TFile(inDir+"histos__data_singleEl_singleMu_2015CD_25ns.root", "read");

  //
  // backgrounds
  //

  // 0 lepton
  TFile *f_allBkg = new TFile(inDir+"histos__allBkg_25ns.root", "read");
  //bkg_classy_names.push_back(hName_0lep);
  //bkg_file_names.push_back("==0 lep");
  //bkg_file_names_tex.push_back("$==0$ lepton");
  //bkg_files.push_back(f_allBkg);
  //colors.push_back(kYellow+1);


  // 1 lepton
  bkg_classy_names.push_back(hName_1lep);
  bkg_file_names.push_back("==1 lep");
  bkg_file_names_tex.push_back("$==1$ lepton");
  bkg_files.push_back(f_allBkg);
  colors.push_back(kRed-7);


  // 2 lepton
  bkg_classy_names.push_back(hName_2lep);
  bkg_file_names.push_back(">=2 lep");
  bkg_file_names_tex.push_back("$\\ge$2 lep");
  bkg_files.push_back(f_allBkg);
  colors.push_back(kCyan-3);


  // ZtoNuNu
  bkg_classy_names.push_back(hName_ZtoNuNu);
  bkg_file_names.push_back("Z to #nu#nu");
  bkg_file_names_tex.push_back("$Z\\rightarrow\\nu\\nu$");
  bkg_files.push_back(f_allBkg);
  colors.push_back(kMagenta-5);


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
  colors.push_back(kGreen);

  
  TFile *f_stop_500_325 = new TFile(inDir+"histos__stop_500_325.root", "read");
  sig_classy_names.push_back(hName_incl);
  sig_file_names.push_back("T2tt(500,325)");
  sig_file_names_tex.push_back("T2tt(500,325)");
  sig_files.push_back(f_stop_500_325);
  colors.push_back(kMagenta+2);


  TFile *f_stop_650_325 = new TFile(inDir+"histos__stop_650_325.root", "read");
  sig_classy_names.push_back(hName_incl);
  sig_file_names.push_back("T2tt(650,325)");
  sig_file_names_tex.push_back("T2tt(650,325)");
  sig_files.push_back(f_stop_650_325);
  colors.push_back(kOrange+7);
  
  
  TFile *f_stop_850_100 = new TFile(inDir+"histos__stop_850_100.root", "read");
  sig_classy_names.push_back(hName_incl);
  sig_file_names.push_back("T2tt(850,100)");
  sig_file_names_tex.push_back("T2tt(850,100)");
  sig_files.push_back(f_stop_850_100);
  colors.push_back(kBlue);
  */

  
  // Dummy file, since there exists a weird problem where the integral
  // of the histograms from the last file are all 0
  TFile *f_dummy = new TFile(outDir+"f_dummy.root", "recreate");
 


  //
  // Variables to plot
  //
  std::vector<std::string> var_list_label;
  std::vector<std::string> var_list_title;
  std::vector<std::string> var_list_xaxis;

  for(int iVar=0; iVar<(int)h_helper.vars_1D.size(); iVar++){
    
    TString var = h_helper.vars_1D[iVar]->label;
    if(var.Contains("yield")) continue;
    if(var.Contains("genweight")) continue;
    
    var_list_label.push_back((std::string)h_helper.vars_1D[iVar]->label);
    var_list_title.push_back((std::string)h_helper.vars_1D[iVar]->title);
    var_list_xaxis.push_back((std::string)h_helper.vars_1D[iVar]->titleX);
  }

    
  //
  // Loop over files and grab histograms
  //
  TString hName = "";
  TString hName_clone = "";
  TH1F *h_data  = new TH1F("","",1,0,1);
  TH1F *h_temp  = NULL;
  TH1F *h_clone = NULL;

  for(int iVar=0; iVar<(int)var_list_label.size(); iVar++){
    TString test = var_list_label[iVar];
    if(test.Contains("nEvents")) continue;
    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      std::string cat_title_for_subtitle = "";
      cat_title_for_subtitle += h_helper.categories[iCat]->title;
  
      // Data;
      if(plotData){
	hName = "h__";
	hName += var_list_label[iVar];
	hName += "__";
	hName += hName_incl;
	hName += "__";
	hName += hName_nominal_sys;
	hName += "__";
	hName += h_helper.categories[iCat]->label;
	
	hName_clone = hName;
	hName_clone += "__data";

	h_temp = (TH1F*)data_file->Get(hName);
	if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
	h_data = (TH1F*)h_temp->Clone(hName_clone);
      }

            
      // Backgrounds
      std::vector<TH1F*> bkg_histos;
      for(int iFile=0; iFile<(int)bkg_files.size(); iFile++){

	hName = "h__";
	hName += var_list_label[iVar];
	hName += "__";
	hName += bkg_classy_names[iFile];
	hName += "__";
	hName += hName_nominal_sys;
	hName += "__";
	hName += h_helper.categories[iCat]->label;
	//hName += "__sysError";

	hName_clone = hName;
	hName_clone += "__bkg_";
	hName_clone += iFile;
	
	h_temp = (TH1F*)bkg_files[iFile]->Get(hName);
	if(!h_temp) cout << "BAD BKG HISTO: " << hName << endl;
	h_clone = (TH1F*)h_temp->Clone(hName_clone);
	bkg_histos.push_back(h_clone);
		
      } // end loop over files
    
      // Signal
      std::vector<TH1F*> sig_histos;
      for(int iFile=0; iFile<(int)sig_files.size(); iFile++){

	hName = "h__";
	hName += var_list_label[iVar];
	hName += "__";
	hName += sig_classy_names[iFile];
	hName += "__";
	hName += hName_nominal_sys;
	hName += "__";
	hName += h_helper.categories[iCat]->label;
	//hName += "__sysError";

	hName_clone = hName;
	hName_clone +="__sig_";
	hName_clone += iFile;

	h_temp = (TH1F*)sig_files[iFile]->Get(hName);
	if(!h_temp) cout << "BAD SIG HISTO: " << hName << endl;
	h_clone = (TH1F*)h_temp->Clone(hName_clone);
	h_clone->Scale(sig_SF);
	sig_histos.push_back(h_clone);
	
      } // end loop over files
      
      
      // Option String, Log Scale Plot
      std::string options = "";

      options += "--outputName ";
      options += outDir;
      options += "data_MC_plot__byGenLeptonDecay__";
      options += var_list_label[iVar];
      options += "__";
      options += h_helper.categories[iCat]->label;
      options += "__logScale.pdf  ";
      
      options += "--xAxisLabel ";
      options += var_list_xaxis[iVar];
      options += "  ";
      
      options += "--legendRight -0.10  ";

      options += "--energy 13  ";

      options += "--lumi ";
      options += Form("%.3f  ", lumi);
      
      options += "--preserveBackgroundOrder  ";
      options += "--preserveSignalOrder  ";

      
      dataMCplotMaker(h_data, bkg_histos, bkg_file_names, var_list_title[iVar], cat_title_for_subtitle, options, sig_histos, sig_file_names, colors);


      // Option String, Linear Scale Plot
      options = "";
      
      options += "--outputName ";
      options += outDir;
      options += "data_MC_plot__byGenLeptonDecay__";
      options += var_list_label[iVar];
      options += "__";
      options += h_helper.categories[iCat]->label;
      options += "__linScale.pdf  ";
      
      options += "--xAxisLabel ";
      options += var_list_xaxis[iVar];
      options += "  ";
      
      options += "--legendRight -0.10  ";

      options += "--energy 13  ";

      options += "--lumi ";
      options += Form("%.3f  ", lumi);
      
      options += "--preserveBackgroundOrder  ";
      options += "--preserveSignalOrder  ";

      options += "--isLinear ";
            

      dataMCplotMaker(h_data, bkg_histos, bkg_file_names, var_list_title[iVar], cat_title_for_subtitle, options, sig_histos, sig_file_names, colors);

      
    } // end loop over categories

  } // end loop over vars
      


  //
  // Make Tables
  //
  const int cats = (int)h_helper.categories.size();
  double totBkg[cats];
  double totBkg_err[cats];

  FILE *yFile;
  TString texFile = outDir;
  texFile += "yieldTable_stop_1l__genLeptonDecay.tex";
  yFile = fopen(texFile.Data(), "w");

  // Tex File Formatting
  fprintf(yFile, "\\documentclass{article}\n");
  fprintf(yFile, "\\usepackage[landscape]{geometry}\n");
  fprintf(yFile, "\\usepackage{chngpage}\n\n");
  fprintf(yFile, "\\begin{document}\n");
  //fprintf(yFile, "\\small\n");
  fprintf(yFile, "\\tiny\n");


  //
  // Low DM
  //

  // Get number of collumns for table - ie categories
  fprintf(yFile, "\\begin{tabular}{|l|");
 
  // Loop over catogories
  for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
    TString cat_title = "";
    cat_title += h_helper.categories[iCat]->tex;
    if(!cat_title.Contains("Low")) continue;
    
    fprintf(yFile,"c|");
  }
  fprintf(yFile, "c|} \\hline \n");


  // Loop over catogories for titles
  for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
    TString cat_title = "";
    cat_title += h_helper.categories[iCat]->tex;
    if(!cat_title.Contains("Low")) continue;
    
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
      if(!cat_title.Contains("Low")) continue;
    
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
      if(!cat_title.Contains("Low")) continue;
      
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
    if(!cat_title.Contains("Low")) continue;
    
    TString hName = "h__yields__";
    hName += hName_incl;
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
      if(!cat_title.Contains("Low")) continue;

      TString hName = "h__yields__";
      hName += hName_incl;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      
      TH1D* h_temp = (TH1D*)data_file->Get(hName);
      if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
	
      // Data Yields
      double error = 0.0;
      double integral = h_temp->IntegralAndError(0,-1,error);
      fprintf(yFile, " & %.2f $\\pm$ %.2f ", integral, error );

    } // end loop over categories
    
    fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");

  } // end if plotting data
  fprintf(yFile, "\\end{tabular} \n");

  fprintf(yFile, "\\"); fprintf(yFile, "\\ \n"); 
  fprintf(yFile, "\\"); fprintf(yFile, "\\ \n"); 
  fprintf(yFile, "\\"); fprintf(yFile, "\\ \n"); 
  fprintf(yFile, "\\"); fprintf(yFile, "\\ \n"); 


  //
  // High DM
  //

  // Get number of collumns for table - ie categories
  fprintf(yFile, "\\begin{tabular}{|l|");
 
  // Loop over catogories
  for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
    TString cat_title = "";
    cat_title += h_helper.categories[iCat]->tex;
    if(!cat_title.Contains("High")) continue;
    
    fprintf(yFile,"c|");
  }
  fprintf(yFile, "c|} \\hline \n");


  // Loop over catogories for titles
  for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
    TString cat_title = "";
    cat_title += h_helper.categories[iCat]->tex;
    if(!cat_title.Contains("High")) continue;
    
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
      if(!cat_title.Contains("High")) continue;
      
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
      double integral = h_temp->IntegralAndError(0,-1,error);
      fprintf(yFile, " & %.2f $\\pm$ %.2f ", integral, error );
      
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
      if(!cat_title.Contains("High")) continue;
 
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
      fprintf(yFile, " & %.2f $\\pm$ %.2f ", integral, error);
	  
    } // end loop over cats

    fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");

  } // end loop over bkg

  
  // Yields for total Background
  fprintf(yFile,"Total Background");
 
  // Loop over categories to get background yields
  for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
    TString cat_title = "";
    cat_title += h_helper.categories[iCat]->tex;
    if(!cat_title.Contains("High")) continue;
    
    TString hName = "h__yields__";
    hName += hName_incl;
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
    //fprintf(yFile, " & %.2f $\\pm$ %.2f ", totBkg[iCat], sqrt(totBkg_err[iCat]));
  }
  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");

  // Yields for data
  if(plotData){
    fprintf(yFile, "Data");

    // Loop over categories for data yields
    for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
      TString cat_title = "";
      cat_title += h_helper.categories[iCat]->tex;
      if(!cat_title.Contains("High")) continue;
      
      TString hName = "h__yields__";
      hName += hName_incl;
      hName += "__";
      hName += hName_nominal_sys;
      hName += "__";
      hName += h_helper.categories[iCat]->label;
      TH1D* h_temp = (TH1D*)data_file->Get(hName);
      if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
	
      // Data Yields
      double error = 0.0;
      double integral = h_temp->IntegralAndError(0,-1,error);
      fprintf(yFile, " & %.2f $\\pm$ %.2f ", integral, error );

    } // end loop over categories
    
    fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");

  } // end if plotting data


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
  
  return;
}
