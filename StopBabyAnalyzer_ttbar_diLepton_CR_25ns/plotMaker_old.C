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
void plotMaker(){

  //
  // Open Files
  //
  TString inDir = "Histos/";
  
  TString outDir = "Plots/";
  
  // vector for kColors, list backgrounds first then signal
  std::vector<Color_t> colors; 

  std::vector<TFile*> bkg_files;
  std::vector<std::string> bkg_file_names;
  std::vector<std::string> bkg_file_names_tex;

  std::vector<TFile*> sig_files;
  std::vector<std::string> sig_file_names;
  std::vector<std::string> sig_file_names_tex;
  
  double lumi=5.0;
  
  //
  // data
  //
  bool plotData = false;

  TFile *data_file;
  if(plotData) data_file = new TFile(inDir+"histos__data.root", "read");

  //
  // backgrounds
  //

  // Rare (all others)
  TFile *f_rare = new TFile(inDir+"histos__rare.root", "read");
  bkg_file_names.push_back("Rare");
  bkg_file_names_tex.push_back("$Rare$");
  bkg_files.push_back(f_rare);
  colors.push_back(kMagenta-5);


  // W+Jets, amcnlo
  //TFile *f_wJets = new TFile(inDir+"histos__WJetsToLNu_amcnlo_pythia8_25ns.root", "read");
  //bkg_file_names.push_back("W+Jets, amcnlo");
  //bkg_file_names_tex.push_back("$W$+Jets, amcnlo");
  //bkg_files.push_back(f_wJets);
  //colors.push_back(kOrange-2);

  // W+Jets, madgraph pythia8
  TFile *f_wJets = new TFile(inDir+"histos__WJetsToLNu_madgraph_pythia8_25ns.root", "read");
  bkg_file_names.push_back("W+Jets, madgraph");
  bkg_file_names_tex.push_back("$W$+Jets, madgraph");
  bkg_files.push_back(f_wJets);
  colors.push_back(kOrange-2);

  

  // DYJets
  TFile *f_dyjets = new TFile(inDir+"histos__DYJets.root", "read");
  bkg_file_names.push_back("DY Jets, amcnlo");
  bkg_file_names_tex.push_back("DY+Jets, amcnlo");
  bkg_files.push_back(f_dyjets);
  colors.push_back(kGreen);


  // singleT
  TFile *f_singleT = new TFile(inDir+"histos__singleT.root", "read");
  bkg_file_names.push_back("Single t, powheg");
  bkg_file_names_tex.push_back("Single $t$, powheg");
  bkg_files.push_back(f_singleT);
  colors.push_back(kYellow+1);

  /*
  // ttbar_1l
  TFile *f_ttbar_1l = new TFile(inDir+"histos__ttbar_1l_amcnlo_pythia8_25ns.root", "read");
  bkg_file_names.push_back("t#bar{t}, 1l, amcnlo");
  bkg_file_names_tex.push_back("$t\\bar{t}$, 1l, amcnlo");
  bkg_files.push_back(f_ttbar_1l);
  colors.push_back(kRed-7);


  // ttbar_2l
  TFile *f_ttbar_2l = new TFile(inDir+"histos__ttbar_2l_amcnlo_pythia8_25ns.root", "read");
  bkg_file_names.push_back("t#bar{t}, 2l, amcnlo");
  bkg_file_names_tex.push_back("$t\\bar{t}$, 2l, amcnlo");
  bkg_files.push_back(f_ttbar_2l);
  colors.push_back(kCyan-3);
  */

  // ttbar_1l
  TFile *f_ttbar_1l = new TFile(inDir+"histos__ttbar_1l_powheg_pythia8_25ns.root", "read");
  bkg_file_names.push_back("t#bar{t}, 1l, powheg");
  bkg_file_names_tex.push_back("$t\\bar{t}$, 1l, powheg");
  bkg_files.push_back(f_ttbar_1l);
  colors.push_back(kRed-7);


  // ttbar_2l
  TFile *f_ttbar_2l = new TFile(inDir+"histos__ttbar_2l_powheg_pythia8_25ns.root", "read");
  bkg_file_names.push_back("t#bar{t}, 2l, powheg");
  bkg_file_names_tex.push_back("$t\\bar{t}$, 2l, powheg");
  bkg_files.push_back(f_ttbar_2l);
  colors.push_back(kCyan-3);
  
  
  /*
  // ttbar_1l
  TFile *f_ttbar_1l = new TFile(inDir+"histos__ttbar_1l_madgraph_pythia8_25ns.root", "read");
  bkg_file_names.push_back("t#bar{t}, 1l, madgraph");
  bkg_file_names_tex.push_back("$t\\bar{t}$, 1l, madgraph");
  bkg_files.push_back(f_ttbar_1l);
  colors.push_back(kRed-7);


  // ttbar_2l
  TFile *f_ttbar_2l = new TFile(inDir+"histos__ttbar_2l_madgraph_pythia8_25ns.root", "read");
  bkg_file_names.push_back("t#bar{t}, 2l, madgraph");
  bkg_file_names_tex.push_back("$t\\bar{t}$, 2l, madgraph");
  bkg_files.push_back(f_ttbar_2l);
  colors.push_back(kCyan-3);
  */

  
  //
  // signals
  //
  double sig_SF = 100.0;
  /*
  TFile *f_stop_850_100 = new TFile(inDir+"histos__stop_850_100.root", "read");
  sig_file_names.push_back("T2tt(850,100)x100");
  sig_file_names_tex.push_back("T2tt(850,100)");
  sig_files.push_back(f_stop_850_100);
  colors.push_back(kBlue);
  
  
  TFile *f_stop_425_325 = new TFile(inDir+"histos__stop_425_325.root", "read");
  sig_file_names.push_back("T2tt(425,325)x100");
  sig_file_names_tex.push_back("T2tt(425,325)");
  sig_files.push_back(f_stop_425_325);
  colors.push_back(kGreen);

  TFile *f_stop_500_325 = new TFile(inDir+"histos__stop_500_325.root", "read");
  sig_file_names.push_back("T2tt(500,325)x100");
  sig_file_names_tex.push_back("T2tt(500,325)");
  sig_files.push_back(f_stop_500_325);
  colors.push_back(kMagenta+2);

  TFile *f_stop_650_325 = new TFile(inDir+"histos__stop_650_325.root", "read");
  sig_file_names.push_back("T2tt(650,325)x100");
  sig_file_names_tex.push_back("T2tt(650,325)");
  sig_files.push_back(f_stop_650_325);
  colors.push_back(kOrange+7);
  */

  // Dummy file, since there exists a weird problem where the integral
  // of the histograms from the last file are all 0
  TFile *f_dummy = new TFile("Plots/f_dummy.root", "recreate");
 


  //
  // Variables to plot
  //
  std::vector<std::string> var_list_label;
  std::vector<std::string> var_list_title;
  std::vector<std::string> var_list_xaxis;

  // nJets
  var_list_label.push_back("nJets");
  var_list_title.push_back("Number of Jets");
  var_list_xaxis.push_back("nJets");

  // nTags
  var_list_label.push_back("nTags_loose");
  var_list_title.push_back("Number of Tags, loose WP=0.605");
  var_list_xaxis.push_back("nTags, loose WP");

  // nTags
  var_list_label.push_back("nTags_medium");
  var_list_title.push_back("Number of Tags, medium WP=0.890");
  var_list_xaxis.push_back("nTags, med WP");

  // nTags
  var_list_label.push_back("nTags_tight");
  var_list_title.push_back("Number of Tags, tight WP=0.970");
  var_list_xaxis.push_back("nTags, tight WP");

  
  // MET
  var_list_label.push_back("met");
  var_list_title.push_back("MET");
  var_list_xaxis.push_back("MET");

  // MET Phi
  var_list_label.push_back("met_phi");
  var_list_title.push_back("MET Phi");
  var_list_xaxis.push_back("MET #phi");

  
  
  // lep1 pT
  var_list_label.push_back("lep1_pt");
  var_list_title.push_back("leading pT lep, pT");
  var_list_xaxis.push_back("pT");

  // lep1 eta
  var_list_label.push_back("lep1_eta");
  var_list_title.push_back("leading pT lep, #eta");
  var_list_xaxis.push_back("#eta");

  // lep1 phi
  var_list_label.push_back("lep1_phi");
  var_list_title.push_back("leading pT lep, #phi");
  var_list_xaxis.push_back("#phi");


  // lep2 pT
  var_list_label.push_back("lep2_pt");
  var_list_title.push_back("trailing pT lep, pT");
  var_list_xaxis.push_back("pT");

  // lep2 eta
  var_list_label.push_back("lep2_eta");
  var_list_title.push_back("trailing pT lep, #eta");
  var_list_xaxis.push_back("#eta");

  // lep2 phi
  var_list_label.push_back("lep2_phi");
  var_list_title.push_back("trailing pT lep, #phi");
  var_list_xaxis.push_back("#phi");

  // diLep mass
  var_list_label.push_back("diLepton_invariant_mass");
  var_list_title.push_back("M_{ll}");
  var_list_xaxis.push_back("M_{ll}");
  
  // jet pT
  var_list_label.push_back("jet_pt");
  var_list_title.push_back("jet, pT");
  var_list_xaxis.push_back("pT");

  // jet csv
  var_list_label.push_back("jet_csv");
  var_list_title.push_back("jet CSV");
  var_list_xaxis.push_back("csv");

    
  // MT
  var_list_label.push_back("mt");
  var_list_title.push_back("M_{T}");
  var_list_xaxis.push_back("M_{T}");
  
  // minChi2
  var_list_label.push_back("hadronic_top_chi2");
  var_list_title.push_back("min #Chi^{2}, Hadronic Top");
  var_list_xaxis.push_back("min #Chi^{2}");

  // MT2W
  var_list_label.push_back("MT2W");
  var_list_title.push_back("MT2W");
  var_list_xaxis.push_back("MT2W");
    

  //
  // histoHelper for categories
  //
  histoHelper histoHelper_forCats;
  
  //
  // Loop over files and grab histograms
  //
  TString hName = "";
  TString hName_clone = "";
  TH1F *h_data  = new TH1F("","",1,0,1);
  TH1F *h_temp  = NULL;
  TH1F *h_clone = NULL;

  for(int iVar=0; iVar<(int)var_list_label.size(); iVar++){

    for(int iCat=0; iCat<(int)histoHelper_forCats.cat_labels.size(); iCat++){
      std::string cat_title_for_subtitle = "";
      cat_title_for_subtitle += histoHelper_forCats.cat_titles[iCat];
  
      // Data;
      if(plotData){
	hName = "h_";
	hName += var_list_label[iVar];
	hName += "__";
	hName += histoHelper_forCats.cat_labels[iCat];
	
	hName_clone = hName;
	hName_clone += "__data";

	h_temp = (TH1F*)data_file->Get(hName);
	h_data = (TH1F*)h_temp->Clone(hName_clone);
      }

            
      // Backgrounds
      std::vector<TH1F*> bkg_histos;
      for(int iFile=0; iFile<(int)bkg_files.size(); iFile++){
	
	hName = "h_";
	hName += var_list_label[iVar];
	hName += "__";
	hName += histoHelper_forCats.cat_labels[iCat];

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
     
	hName = "h_";
	hName += var_list_label[iVar];
	hName += "__";
	hName += histoHelper_forCats.cat_labels[iCat];
	
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
      options += "data_MC_plot__";
      options += var_list_label[iVar];
      options += "__";
      options += histoHelper_forCats.cat_labels[iCat];
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
      options += "data_MC_plot__";
      options += var_list_label[iVar];
      options += "__";
      options += histoHelper_forCats.cat_labels[iCat];
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

  
  const int cats = (int)histoHelper_forCats.cat_labels.size();
  double totBkg[cats];
  double totBkg_err[cats];

  double tt2lBkg[cats];
  double tt2lBkg_err[cats];

  FILE *yFile;
  TString yieldFile = "Plots/yieldTable_stop_1l.tex";
  yFile = fopen(yieldFile.Data(), "w");

  // Tex File Formatting
  fprintf(yFile, "\\documentclass{article}\n");
  fprintf(yFile, "\\usepackage[landscape]{geometry}\n");
  fprintf(yFile, "\\usepackage{chngpage}\n\n");
  fprintf(yFile, "\\begin{document}\n");
  //fprintf(yFile, "\\small\n");
  fprintf(yFile, "\\tiny\n");


  // Get number of collumns for table - ie categories
  fprintf(yFile, "\\begin{tabular}{|l|");
 
  // Loop over catogories
  for(int iCat=0; iCat<(int)histoHelper_forCats.cat_labels.size(); iCat++){
    fprintf(yFile,"c|");
  }
  //fprintf(yFile, "c|} \\hline \n");
  fprintf(yFile, "} \\hline \n");


  // Loop over catogories for titles
  for(int iCat=0; iCat<(int)histoHelper_forCats.cat_labels.size(); iCat++){
    
    TString cat_title_tex =  histoHelper_forCats.cat_titles_tex[iCat];
    fprintf(yFile,"& $%s$ ",cat_title_tex.Data());

  }
  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
  
  
  // Loop over signal files
  for(int iSig=0; iSig<(int)sig_file_names_tex.size(); iSig++){
    
    // Signal name
    fprintf(yFile,"%s", sig_file_names_tex[iSig].c_str());
    
    // Loop over categories to get signal yields
    for(int iCat=0; iCat<(int)histoHelper_forCats.cat_labels.size(); iCat++){
      TString hName = "h_nJets__";
      hName += histoHelper_forCats.cat_labels[iCat];

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
    for(int iCat=0; iCat<(int)histoHelper_forCats.cat_labels.size(); iCat++){
      TString hName = "h_nJets__";
      hName += histoHelper_forCats.cat_labels[iCat];

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

      // ttbar yields
      TString bkg_title = "";
      bkg_title += bkg_files[iBkg]->GetName();
      if(bkg_title.Contains("ttbar_2l")){
	error = 0.0;
	if(iBkg==0) tt2lBkg[iCat]  = h_temp->IntegralAndError(0,-1,error);
	else        tt2lBkg[iCat] += h_temp->IntegralAndError(0,-1,error);

	if(iBkg==0) tt2lBkg_err[iCat]  = pow(error,2);
	else        tt2lBkg_err[iCat] += pow(error,2);
      }
	
	  
    } // end loop over cats

    fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");

  } // end loop over bkg

  
  // Yields for total Background
  fprintf(yFile,"Total Background");
 
  // Loop over categories to get background yields
  for(int iCat=0; iCat<(int)histoHelper_forCats.cat_labels.size(); iCat++){
    fprintf(yFile, " & %.2f $\\pm$ %.2f ", totBkg[iCat], sqrt(totBkg_err[iCat]) );
  }
  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");


  // Yields for ttbar purity
  fprintf(yFile,"$t\\bar{t}$ 2l purity");
 
  // Loop over categories to get background yields
  for(int iCat=0; iCat<(int)histoHelper_forCats.cat_labels.size(); iCat++){
    double purity = tt2lBkg[iCat]/totBkg[iCat];
    double purity_err = sqrt( purity*(1-purity)/totBkg[iCat] );
    fprintf(yFile, " & %.2f $\\pm$ %.2f ", purity, purity_err );
  }
  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");


  // Yields for data
  if(plotData){
    fprintf(yFile, "Data");

    // Loop over categories for data yields
    for(int iCat=0; iCat<(int)histoHelper_forCats.cat_labels.size(); iCat++){
      TString hName = "h_nJets__";
      hName += histoHelper_forCats.cat_labels[iCat];
      
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

  cout << endl;
  cout << "Table of ttbar diLepton CR yields written to: " << yieldFile << endl;
  cout << endl;



  //
  // Table for tW vs tt2l difference of ratios * subtraction uncertainty
  //
  TString ratioComparisonFile = "Plots/nJetsRatioComparison_CR4.tex";
  yFile = fopen(ratioComparisonFile.Data(), "w");

  // Tex File Formatting
  fprintf(yFile, "\\documentclass{article}\n");
  fprintf(yFile, "\\usepackage[landscape]{geometry}\n");
  fprintf(yFile, "\\usepackage{chngpage}\n\n");
  fprintf(yFile, "\\begin{document}\n");
  //fprintf(yFile, "\\small\n");
  fprintf(yFile, "\\tiny\n");


  // Get number of collumns for table - cats, ratio, difference for each (ttbar2l, tW); 
  fprintf(yFile, "\\begin{tabular}{|l|c|c|c|c|c|c|} \\hline \n");

  // Set titles
  fprintf(yFile, "Category");
  fprintf(yFile, " & $R(>=3j/==2j)_{tW}$ & $R(>=3j/==2j)_{t\\bar{t},2l}$ & Diff(>=3j/==2j)");
  fprintf(yFile, " & $R(>=4j/==2j)_{tW}$ & $R(>=4j/==2j)_{t\\bar{t},2l}$ & Diff(>=4j/==2j)");
  fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");

  for(int iCat=0; iCat<(int)histoHelper_forCats.cat_labels.size(); iCat++){
    

    TString cat_title_tex =  histoHelper_forCats.cat_titles_tex[iCat];
    if( !cat_title_tex.Contains(">=2 Jets") ) continue;
    if( cat_title_tex.Contains("0 Tags") ) continue;

    fprintf(yFile,"$%s$ ",cat_title_tex.Data());

    TString h_nJets_name = "h_nJets__";
    h_nJets_name += histoHelper_forCats.cat_labels[iCat];


    TH1D *h_ttbar_nJets = (TH1D*)f_ttbar_2l->Get(h_nJets_name);

    double ttbar2l_ee2j_err= h_ttbar_nJets->GetBinError( h_ttbar_nJets->FindBin(2) );
    double ttbar2l_ee2j = h_ttbar_nJets->GetBinContent( h_ttbar_nJets->FindBin(2) );
    
    double ttbar2l_ge3j_err = 0.0;
    double ttbar2l_ge3j = h_ttbar_nJets->IntegralAndError( h_ttbar_nJets->FindBin(3), -1, ttbar2l_ge3j_err );

    double ttbar2l_ge4j_err = 0.0;
    double ttbar2l_ge4j = h_ttbar_nJets->IntegralAndError( h_ttbar_nJets->FindBin(4), -1, ttbar2l_ge4j_err );  

    double r_ttbar2l_ge3j_ee2j = ttbar2l_ge3j/ttbar2l_ee2j;
    double r_ttbar2l_ge3j_ee2j_err = r_ttbar2l_ge3j_ee2j*sqrt( pow( ttbar2l_ge3j_err/ttbar2l_ge3j, 2 ) + pow( ttbar2l_ee2j_err/ttbar2l_ee2j, 2 ) );

    double r_ttbar2l_ge4j_ee2j = ttbar2l_ge4j/ttbar2l_ee2j;
    double r_ttbar2l_ge4j_ee2j_err = r_ttbar2l_ge4j_ee2j*sqrt( pow( ttbar2l_ge4j_err/ttbar2l_ge4j, 2 ) + pow( ttbar2l_ee2j_err/ttbar2l_ee2j, 2 ) );



    TH1D *h_tW_nJets = (TH1D*)f_singleT->Get(h_nJets_name);

    double tW_ee2j_err = h_tW_nJets->GetBinError( h_tW_nJets->FindBin(2) );
    double tW_ee2j = h_tW_nJets->GetBinContent( h_tW_nJets->FindBin(2) );

    double tW_ge3j_err = 0.0;
    double tW_ge3j = h_tW_nJets->IntegralAndError( h_tW_nJets->FindBin(3), -1, tW_ge3j_err );

    double tW_ge4j_err = 0.0;
    double tW_ge4j = h_tW_nJets->IntegralAndError( h_tW_nJets->FindBin(4), -1, tW_ge4j_err );
    
    double r_tW_ge3j_ee2j = tW_ge3j/tW_ee2j;
    double r_tW_ge3j_ee2j_err = r_tW_ge3j_ee2j*sqrt( pow( tW_ge3j_err/tW_ge3j, 2 ) + pow( tW_ee2j_err/tW_ee2j, 2 ) );

    double r_tW_ge4j_ee2j = tW_ge4j/tW_ee2j;
    double r_tW_ge4j_ee2j_err = r_tW_ge4j_ee2j*sqrt( pow( tW_ge4j_err/tW_ge4j, 2 ) + pow( tW_ee2j_err/tW_ee2j, 2 ) );


    double diff_ge3j_ee2j = r_tW_ge3j_ee2j - r_ttbar2l_ge3j_ee2j;
    double diff_ge3j_ee2j_err = sqrt( pow( r_ttbar2l_ge3j_ee2j_err, 2 ) + pow( r_tW_ge3j_ee2j_err, 2 ) );

    double diff_ge4j_ee2j = r_tW_ge4j_ee2j - r_ttbar2l_ge4j_ee2j;
    double diff_ge4j_ee2j_err = sqrt( pow( r_ttbar2l_ge4j_ee2j_err, 2 ) + pow( r_tW_ge4j_ee2j_err, 2 ) );


    fprintf( yFile, " & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f & %.3f $\\pm$ %.3f ", r_tW_ge3j_ee2j, r_tW_ge3j_ee2j_err, r_ttbar2l_ge3j_ee2j, r_ttbar2l_ge3j_ee2j_err, diff_ge3j_ee2j, diff_ge3j_ee2j_err, r_tW_ge4j_ee2j, r_tW_ge4j_ee2j_err, r_ttbar2l_ge4j_ee2j, r_ttbar2l_ge4j_ee2j_err, diff_ge4j_ee2j, diff_ge4j_ee2j_err );

    fprintf(yFile, "\\"); fprintf(yFile, "\\ \\hline \n");
 
  }   

  fprintf(yFile, "\\end{tabular} \n");

  fprintf(yFile, "\\end{document} \n");

  fclose(yFile);

  cout << endl;
  cout << "Table of ratios of nJets >=3j/2j, >=4j/2j tW vs ttbar2l written to: " << ratioComparisonFile << endl;
  cout << endl;

  
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
