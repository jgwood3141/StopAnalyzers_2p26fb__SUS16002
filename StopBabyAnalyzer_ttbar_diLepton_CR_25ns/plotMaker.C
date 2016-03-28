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
  //flav_loop.push_back(hName_incl);
  //flav_loop.push_back(hName_ElEl);
  flav_loop.push_back(hName_ElMu);
  //flav_loop.push_back(hName_MuMu);

  std::vector<TString> tt1l_flav_loop;
  //tt1l_flav_loop.push_back(hName_1lep);
  //tt1l_flav_loop.push_back(hName_ElEl_1lep);
  tt1l_flav_loop.push_back(hName_ElMu_1lep);
  //tt1l_flav_loop.push_back(hName_MuMu_1lep);

  std::vector<TString> tt2l_flav_loop;
  //tt2l_flav_loop.push_back(hName_2lep);
  //tt2l_flav_loop.push_back(hName_ElEl_2lep);
  tt2l_flav_loop.push_back(hName_ElMu_2lep);
  //tt2l_flav_loop.push_back(hName_MuMu_2lep);

    
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
  //TString inDir = "Histos__2p26__lep2Pt20__20160218/Nominal/";
  //TString outDir = "Plots_temp/";
  
  TFile *f_rootFile_forPlots = new TFile(outDir+"ttbar_emu_CR__histosForPlots.root", "recreate");
    
  
  for(int iFlav=0; iFlav<(int)flav_loop.size(); iFlav++){

    TString hName_flav = flav_loop[iFlav];
    TString hName_flav_tt1l = tt1l_flav_loop[iFlav];
    TString hName_flav_tt2l = tt2l_flav_loop[iFlav];

        
    // vector for kColors, list backgrounds first then signal
    std::vector<Color_t> colors; 
    
    std::vector<TFile*> bkg_files;
    std::vector<TString> bkg_classy_names;
    std::vector<std::string> bkg_file_names;
    std::vector<std::string> bkg_file_names_tex;
    std::vector<std::string> bkg_file_names_labels;

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
    /*
    TFile *f_rare = new TFile(inDir+"histos__rare_25ns.root", "read");
    bkg_classy_names.push_back(hName_flav);
    bkg_file_names.push_back("Rare");
    bkg_file_names_tex.push_back("Rare");
    bkg_file_names_labels.push_back("rare");
    bkg_files.push_back(f_rare);
    colors.push_back(kMagenta-5);
    */
    TFile *f_TTV = new TFile(inDir+"histos__TTV_25ns.root", "read");
    bkg_classy_names.push_back(hName_flav);
    bkg_file_names.push_back("TTV");
    bkg_file_names_tex.push_back("TTV");
    bkg_file_names_labels.push_back("ttv");
    bkg_files.push_back(f_TTV);
    colors.push_back(kMagenta-5);


    // W+Jets, madgraph pythia8
    TFile *f_wJets = new TFile(inDir+"histos__WJets_25ns.root", "read");
    bkg_classy_names.push_back(hName_flav);
    bkg_file_names.push_back("W+Jets, madgraph");
    bkg_file_names_tex.push_back("$W$+Jets, madgraph");
    bkg_file_names_labels.push_back("wjets");
    bkg_files.push_back(f_wJets);
    colors.push_back(kOrange-2);

    /*
    // DYJets
    TFile *f_dyjets = new TFile(inDir+"histos__DYJets_25ns.root", "read");
    bkg_classy_names.push_back(hName_flav);
    bkg_file_names.push_back("DY Jets, amcnlo");
    bkg_file_names_tex.push_back("DY+Jets, amcnlo");
    bkg_file_names_labels.push_back("dyjets");
    bkg_files.push_back(f_dyjets);
    colors.push_back(kGreen);
    */
    
    // singleT
    TFile *f_singleT = new TFile(inDir+"histos__singleT_25ns.root", "read");
    bkg_classy_names.push_back(hName_flav);
    bkg_file_names.push_back("Single t, powheg");
    bkg_file_names_tex.push_back("Single $t$, powheg");
    bkg_file_names_labels.push_back("singlet");
    bkg_files.push_back(f_singleT);
    colors.push_back(kYellow+1);


    // ttbar_1l
    TFile *f_ttbar = new TFile(inDir+"histos__ttbar_25ns.root", "read");
    bkg_classy_names.push_back(hName_flav_tt1l);
    //bkg_file_names.push_back("t#bar{t}, 1l, powheg");
    //bkg_file_names_tex.push_back("$t\\bar{t}$, 1l, powheg");
    bkg_file_names.push_back("t#bar{t}, 1l, powheg ext");
    bkg_file_names_tex.push_back("$t\\bar{t}$, 1l, powheg ext");
    bkg_file_names_labels.push_back("ttbar1l");
    //bkg_file_names.push_back("t#bar{t}, 1l, madgraph ext");
    //bkg_file_names_tex.push_back("$t\\bar{t}$, 1l, madgraph ext");
    bkg_files.push_back(f_ttbar);
    colors.push_back(kRed-7);
    
    // ttbar_2l
    bkg_classy_names.push_back(hName_flav_tt2l);
    //bkg_file_names.push_back("t#bar{t}, 2l, powheg");
    //bkg_file_names_tex.push_back("$t\\bar{t}$, 2l, powheg");
    bkg_file_names.push_back("t#bar{t}, 2l, powheg ext");
    bkg_file_names_tex.push_back("$t\\bar{t}$, 2l, powheg ext");
    bkg_file_names_labels.push_back("ttbar2l");
    //bkg_file_names.push_back("t#bar{t}, 2l, madgraph ext");
    //bkg_file_names_tex.push_back("$t\\bar{t}$, 2l, madgraph ext");
    bkg_files.push_back(f_ttbar);
    colors.push_back(kCyan-3);
  
    
    //
    // signals
    //
    double sig_SF = 1.0;
    
    //TFile *f_stop_425_325 = new TFile(inDir+"histos__stop_425_325_noNegYield_25ns.root", "read");
    //sig_classy_names.push_back(hName_flav);
    //sig_file_names.push_back("T2tt(425,325)");
    //sig_file_names_tex.push_back("T2tt(425,325)");
    //sig_files.push_back(f_stop_425_325);
    //colors.push_back(kGreen);

  
    //TFile *f_stop_500_325 = new TFile(inDir+"histos__stop_500_325_noNegYield_25ns.root", "read");
    //sig_classy_names.push_back(hName_flav);
    //sig_file_names.push_back("T2tt(500,325)");
    //sig_file_names_tex.push_back("T2tt(500,325)");
    //sig_files.push_back(f_stop_500_325);
    //colors.push_back(kMagenta+2);


    //TFile *f_stop_650_325 = new TFile(inDir+"histos__stop_650_325_noNegYield_25ns.root", "read");
    //sig_classy_names.push_back(hName_flav);
    //sig_file_names.push_back("T2tt(650,325)");
    //sig_file_names_tex.push_back("T2tt(650,325)");
    //sig_files.push_back(f_stop_650_325);
    //colors.push_back(kOrange+7);
    
    
    //TFile *f_stop_850_100 = new TFile(inDir+"histos__stop_850_100_noNegYield_25ns.root", "read");
    //sig_classy_names.push_back(hName_flav);
    //sig_file_names.push_back("T2tt(850,100)");
    //sig_file_names_tex.push_back("T2tt(850,100)");
    //sig_files.push_back(f_stop_850_100);
    //colors.push_back(kBlue);
    
    
    
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

      if(!var.Contains("diLep_pt")) continue;
      
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
    TH1F *h_data_2 = NULL;
    TH1F *h_clone_2 = NULL;
    for(int iVar=0; iVar<(int)var_list_label.size(); iVar++){
      
      for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){

	std::string cat_title_for_subtitle = "";
	cat_title_for_subtitle += h_helper.categories[iCat]->title;
  
	// Data;
	if(plotData){
	  hName = "h__";
	  hName += var_list_label[iVar];
	  hName += "__";
	  hName += hName_flav;
	  hName += "__";
	  hName += hName_nominal_sys;
	  hName += "__";
	  hName += h_helper.categories[iCat]->label;
	  
	  hName_clone = hName;
	  hName_clone += "__data";
	  
	  h_temp = (TH1F*)data_file->Get(hName);
	  if(!h_temp) cout << "BAD DATA HISTO: " << hName << endl;
	  h_data = (TH1F*)h_temp->Clone(hName_clone);
	  if( hName.Contains("diLep_pt") ) h_data->Rebin(2);

	  if( hName.Contains("nJets") &&
	      hName.Contains("elmu") &&
	      hName.Contains("ge2j_ge2t_gt0met") ){
	    cout << "FOUND THIS" << endl;
	    h_data_2 = (TH1F*)h_temp->Clone(hName_clone);
	    h_data_2->SetDirectory(f_rootFile_forPlots);
	  }
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
	  //hName_clone += iFile;
	  hName_clone += bkg_file_names_labels[iFile];
	  
	  h_temp = (TH1F*)bkg_files[iFile]->Get(hName);
	  if(!h_temp) cout << "BAD BKG HISTO: " << hName << endl;
	  h_clone = (TH1F*)h_temp->Clone(hName_clone);
	  if( hName.Contains("diLep_pt") ) h_clone->Rebin(2);
	  bkg_histos.push_back(h_clone);

	  if( hName.Contains("nJets") &&
	      hName.Contains("elmu") &&
	      hName.Contains("ge2j_ge2t_gt0met") ){
	    cout << "FOUND THIS" << endl;
	    h_clone_2 = (TH1F*)h_temp->Clone(hName_clone);
	    h_clone_2->SetDirectory(f_rootFile_forPlots);
	  }
	  
	  
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
	  if( hName.Contains("diLep_pt") ) h_clone->Rebin(2);
	  h_clone->Scale(sig_SF);
	  sig_histos.push_back(h_clone);
	  
	} // end loop over files
      
      
	// Option String, Log Scale Plot
	std::string options = "";
	
	options += "--outputName ";
	options += outDir;
	options += "data_MC_plot__byProductionMode__";
	options += var_list_label[iVar];
	options += "__";
	options += hName_flav;
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
	
	//if( hName.Contains("diLep_pt") ) options += "--normalize  ";
	
	dataMCplotMaker(h_data, bkg_histos, bkg_file_names, var_list_title[iVar], cat_title_for_subtitle, options, sig_histos, sig_file_names, colors);


	// Option String, Linear Scale Plot
	options = "";
	
	options += "--outputName ";
	options += outDir;
	options += "data_MC_plot__byProductionMode__";
	options += var_list_label[iVar];
	options += "__";
	options += hName_flav;
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
    // Clean up
    //
    
    if(plotData) data_file->Close();
    
    for(int iBkg=0; iBkg<(int)bkg_files.size(); iBkg++){
      bkg_files[iBkg]->Close();
    }
    for(int iSig=0; iSig<(int)sig_files.size(); iSig++){
      sig_files[iSig]->Close();
    }
    //f_dummy->Close();
    
  } // end loop over flavours

  f_rootFile_forPlots->Write();
  f_rootFile_forPlots->Close();


  return;

}
