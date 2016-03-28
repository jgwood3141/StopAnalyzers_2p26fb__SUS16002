#include "Riostream.h"
#include "TFile.h"
#include "TH1.h"
#include "TString.h"

#include <vector>

#include "histoHelper.h"

void nJets_SF_extractor(){

  // Open Files and Get Histos
  TString outDir = "Plots/";
  
  TString inDir   = "Histos/Nominal/";
  TFile *f_data   = new TFile(inDir+"histos__data_25ns.root", "read");
  TFile *f_tt2l   = new TFile(inDir+"histos__ttbar_25ns.root", "read");
  TFile *f_allBkg = new TFile(inDir+"histos__allBkg_25ns.root", "read");

  TString inDir_jesUp   = "Histos/JESup/";
  TFile *f_tt2l_jesUp   = new TFile(inDir_jesUp+"histos__ttbar_25ns.root", "read");
  TFile *f_allBkg_jesUp = new TFile(inDir_jesUp+"histos__allBkg_25ns.root", "read");

  TString inDir_jesDown   = "Histos/JESdown/";
  TFile *f_tt2l_jesDown   = new TFile(inDir_jesDown+"histos__ttbar_25ns.root", "read");
  TFile *f_allBkg_jesDown = new TFile(inDir_jesDown+"histos__allBkg_25ns.root", "read");

  
  TFile *f_dummy = new TFile(inDir+"dummy.root", "recreate");
  
  TH1D *h_data=NULL;
  TH1D *h_tt2l=NULL;
  TH1D *h_allBkg=NULL;
  TH1D *h_non_tt2l=NULL;
  
  // HistoHelper for histNames
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

  

  // Hist name for nJets
  TString hNameBase = "h__nJets";

  // Categories for each table
  std::vector<int> cats_ge0t, cats_ge1t, cats_ge2t;
  for(int iCat=0; iCat<(int)h_helper.categories.size(); iCat++){
    if(h_helper.categories[iCat]->id==k_ge2j_ge0t_gt0met   ||
       h_helper.categories[iCat]->id==k_ge2j_ge0t_gt50met  || 
       h_helper.categories[iCat]->id==k_ge2j_ge0t_gt100met ||
       h_helper.categories[iCat]->id==k_ge2j_ge0t_gt150met ||
       h_helper.categories[iCat]->id==k_ge2j_ge0t_gt200met    ) cats_ge0t.push_back(iCat);

    if(h_helper.categories[iCat]->id==k_ge2j_ge1t_gt0met   ||
       h_helper.categories[iCat]->id==k_ge2j_ge1t_gt50met  || 
       h_helper.categories[iCat]->id==k_ge2j_ge1t_gt100met ||
       h_helper.categories[iCat]->id==k_ge2j_ge1t_gt150met ||
       h_helper.categories[iCat]->id==k_ge2j_ge1t_gt200met    ) cats_ge1t.push_back(iCat);

    if(h_helper.categories[iCat]->id==k_ge2j_ge2t_gt0met   ||
       h_helper.categories[iCat]->id==k_ge2j_ge2t_gt50met  || 
       h_helper.categories[iCat]->id==k_ge2j_ge2t_gt100met ||
       h_helper.categories[iCat]->id==k_ge2j_ge2t_gt150met ||
       h_helper.categories[iCat]->id==k_ge2j_ge2t_gt200met    ) cats_ge2t.push_back(iCat);
    
  }

  // Vector of tables  
  std::vector< std::vector<int> > tables;
  tables.push_back(cats_ge0t);
  tables.push_back(cats_ge1t);
  tables.push_back(cats_ge2t);

  for(int iFlav=0; iFlav<(int)flav_loop.size(); iFlav++){
    
    TString hName_flav = flav_loop[iFlav];
    TString hName_flav_tt1l = tt1l_flav_loop[iFlav];
    TString hName_flav_tt2l = tt2l_flav_loop[iFlav];
    
      
    // Loop over tables 
    FILE *outFile_metBins;
    FILE *outFile_SFuncs;
    for(int iTable=0; iTable<(int)tables.size(); iTable++){
      
      //
      // Tex File for nJetsSF vs MET
      //
      TString fileName_metBins = outDir;
      fileName_metBins += "nJets_SF__";
      fileName_metBins += h_helper.categories[tables[iTable][0]]->label;
      fileName_metBins += "__";
      fileName_metBins += hName_flav;
      fileName_metBins += ".tex";
      outFile_metBins = fopen(fileName_metBins.Data(), "w");
      
      // Tex File Formatting
      fprintf(outFile_metBins, "\\documentclass{article}\n");
      fprintf(outFile_metBins, "\\usepackage[landscape]{geometry}\n");
      fprintf(outFile_metBins, "\\usepackage{chngpage}\n\n");
      fprintf(outFile_metBins, "\\begin{document}\n");
      //fprintf(outFile_metBins, "\\small\n");
      fprintf(outFile_metBins, "\\tiny\n");
      
      // Get number of collumns for table - ie categories
      fprintf(outFile_metBins, "\\begin{tabular}{|l|c|c|");
      fprintf(outFile_metBins, "} \\hline \n");
      
      fprintf(outFile_metBins, "Category & $nJets=3 (K_{3})$ & $nJets>=4 (K_{4})$ ");
      fprintf(outFile_metBins, "\\"); fprintf(outFile_metBins, "\\ \\hline \n");


      
      for(int iCat=0; iCat<(int)tables[iTable].size(); iCat++){
      
	int cat_idx = tables[iTable][iCat];
	
	fprintf(outFile_metBins, "$%s$ ", h_helper.categories[cat_idx]->title.Data());
	cout << "Category: " << h_helper.categories[cat_idx]->title.Data() << endl;

	
	//
	// Tex File for nJetsSF Uncertain
	//
	TString fileName_SFuncs = outDir;
	fileName_SFuncs += "nJets_SF_Uncertainties__";
	fileName_SFuncs += h_helper.categories[cat_idx]->label;
	fileName_SFuncs += "__";
	fileName_SFuncs += hName_flav;
	fileName_SFuncs += ".tex";
	outFile_SFuncs = fopen(fileName_SFuncs.Data(), "w");
	
	// Tex File Formatting
	fprintf(outFile_SFuncs, "\\documentclass{article}\n");
	fprintf(outFile_SFuncs, "\\usepackage[landscape]{geometry}\n");
	fprintf(outFile_SFuncs, "\\usepackage{chngpage}\n\n");
	fprintf(outFile_SFuncs, "\\begin{document}\n");
	//fprintf(outFile_SFuncs, "\\small\n");
	fprintf(outFile_SFuncs, "\\tiny\n");
	
	// Get number of collumns for table - ie categories
	fprintf(outFile_SFuncs, "\\begin{tabular}{|l|c|c|c|c|c|c|");
	fprintf(outFile_SFuncs, "} \\hline \n");
	
	fprintf(outFile_SFuncs, "Systematatic & $K_{3}$ Up & $K_{3}$ Down & $K_{3}~\\%%~Uncertainty$ & $K_{4}$ Up & $K_{4}$ Down & $K_{4}~\\%%~Uncertainty$ ");
	fprintf(outFile_SFuncs, "\\"); fprintf(outFile_SFuncs, "\\ \\hline \n");
	
	
	
	// Get Histograms for nJets
	
	// Data
	TString hNameData = hNameBase;
	hNameData += "__";
	hNameData += hName_flav;
	hNameData += "__";
	hNameData += hName_nominal_sys;
	hNameData += "__";
	hNameData += h_helper.categories[cat_idx]->label;
	
	// Incl
	TString hNameIncl = hNameBase;
	hNameIncl += "__";
	hNameIncl += hName_flav;
	hNameIncl += "__";
	hNameIncl += hName_nominal_sys;
	hNameIncl += "__";
	hNameIncl += h_helper.categories[cat_idx]->label;
	
	// 2lep
	TString hName2Lep = hNameBase;
	hName2Lep += "__";
	hName2Lep += hName_flav_tt2l;
	hName2Lep += "__";
	hName2Lep += hName_nominal_sys;
	hName2Lep += "__";
	hName2Lep += h_helper.categories[cat_idx]->label;
      
	cout << "hNameData = " << hNameData << endl;
	cout << "hNameIncl = " << hNameIncl << endl;
	cout << "hName2Lep = " << hName2Lep << endl;
	
	cout << __LINE__ << endl;
	// 2 jet bin
	h_data = (TH1D*)f_data->Get(hNameData);
	cout << __LINE__ << endl;
	if(!h_data) cout << "BAD DATA HISTO: " << hNameData << endl;
	cout << __LINE__ << endl;
	double ee2j_data = h_data->GetBinContent( h_data->FindBin(2) );
	cout << __LINE__ << endl;
	double ee2j_data_err = sqrt( ee2j_data );
	
	cout << __LINE__ << endl;
	h_tt2l = (TH1D*)f_tt2l->Get(hName2Lep);
	cout << __LINE__ << endl;
	if(!h_tt2l) cout << "BAD TT2L HISTO, 2j: " << hName2Lep << endl;
	cout << __LINE__ << endl;
	double ee2j_tt2l = h_tt2l->GetBinContent( h_tt2l->FindBin(2) );
	cout << __LINE__ << endl;
	double ee2j_tt2l_err = h_tt2l->GetBinError( h_tt2l->FindBin(2) );
	
	cout << __LINE__ << endl;
	h_allBkg = (TH1D*)f_allBkg->Get(hNameIncl);
	cout << __LINE__ << endl;
	if(!h_allBkg) cout << "BAD ALLBKG HISTO, 2j: " << hNameIncl << endl;
	cout << __LINE__ << endl;
	double ee2j_allBkg = h_allBkg->GetBinContent( h_allBkg->FindBin(2) );
	cout << __LINE__ << endl;
	double ee2j_allBkg_err = h_allBkg->GetBinError( h_allBkg->FindBin(2) );
	cout << __LINE__ << endl;
	h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameIncl+"__non_tt2l");
	cout << __LINE__ << endl;
	h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
	cout << __LINE__ << endl;
	double ee2j_non_tt2l = h_non_tt2l->GetBinContent( h_non_tt2l->FindBin(2) );
	cout << __LINE__ << endl;
	double ee2j_non_tt2l_err = h_non_tt2l->GetBinError( h_non_tt2l->FindBin(2) );
	
	double ee2j_data_min_non_tt2l = ee2j_data - ee2j_non_tt2l;
	double ee2j_data_min_non_tt2l_err = sqrt( pow(ee2j_data_err,2) + pow(ee2j_non_tt2l_err,2) );
	
	double SF2 = ee2j_data_min_non_tt2l/ee2j_tt2l;
	double SF2_err = SF2*sqrt( pow( ee2j_data_min_non_tt2l_err/ee2j_data_min_non_tt2l, 2 ) + pow( ee2j_tt2l_err/ee2j_tt2l,2 ) );
	cout << __LINE__ << endl;
	
	// 3 jet bin
	h_data = (TH1D*)f_data->Get(hNameData);
	if(!h_data) cout << "BAD DATA HISTO,3j: " << hNameData << endl;
	double ee3j_data = h_data->GetBinContent( h_data->FindBin(3) );
	double ee3j_data_err = sqrt( ee3j_data );
	
	h_tt2l = (TH1D*)f_tt2l->Get(hName2Lep);
	if(!h_tt2l) cout << "BAD TT2L HISTO, 3j: " << hName2Lep << endl;
	double ee3j_tt2l = h_tt2l->GetBinContent( h_tt2l->FindBin(3) );
	double ee3j_tt2l_err = h_tt2l->GetBinError( h_tt2l->FindBin(3) );
	
	h_allBkg = (TH1D*)f_allBkg->Get(hNameIncl);
	if(!h_allBkg) cout << "BAD ALLBKG HISTO, 3j: " << hNameIncl << endl;
	double ee3j_allBkg = h_allBkg->GetBinContent( h_allBkg->FindBin(3) );
	double ee3j_allBkg_err = h_allBkg->GetBinError( h_allBkg->FindBin(3) );
	h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameIncl+"__non_tt2l");
	h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
	double ee3j_non_tt2l = h_non_tt2l->GetBinContent( h_non_tt2l->FindBin(3) );
	double ee3j_non_tt2l_err = h_non_tt2l->GetBinError( h_non_tt2l->FindBin(3) );
	
	double ee3j_data_min_non_tt2l = ee3j_data - ee3j_non_tt2l;
	double ee3j_data_min_non_tt2l_err = sqrt( pow(ee3j_data_err,2) + pow(ee3j_non_tt2l_err,2) );

	double SF3 = ee3j_data_min_non_tt2l/ee3j_tt2l;	
	double SF3_err = SF3*sqrt( pow( ee3j_data_min_non_tt2l_err/ee3j_data_min_non_tt2l, 2 ) + pow( ee3j_tt2l_err/ee3j_tt2l,2 ) );
	
	cout << __LINE__ << endl;
	// >=4 jet bin
	h_data = (TH1D*)f_data->Get(hNameData);
	if(!h_data) cout << "BAD DATA HISTO:, 4j " << hNameData << endl;
	double ge4j_data = h_data->Integral( h_data->FindBin(4), -1 );
	double ge4j_data_err = sqrt( ge4j_data );
	
	h_tt2l = (TH1D*)f_tt2l->Get(hName2Lep);
	if(!h_tt2l) cout << "BAD TT2L HISTO,4j: " << hName2Lep << endl;
	double ge4j_tt2l_err = 0.0;
	double ge4j_tt2l = h_tt2l->IntegralAndError( h_tt2l->FindBin(4), -1, ge4j_tt2l_err );
	
	h_allBkg = (TH1D*)f_allBkg->Get(hNameIncl);
	if(!h_allBkg) cout << "BAD ALLBKG HISTO: " << hNameIncl << endl;
	double ge4j_allBkg_err = 0.0;
	double ge4j_allBkg = h_allBkg->IntegralAndError( h_allBkg->FindBin(4), -1, ge4j_allBkg_err );
	
	h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameIncl+"__non_tt2l");
	h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
	double ge4j_non_tt2l_err = 0.0;
	double ge4j_non_tt2l = h_non_tt2l->IntegralAndError( h_non_tt2l->FindBin(4), -1, ge4j_non_tt2l_err );
        
	double ge4j_data_min_non_tt2l = ge4j_data - ge4j_non_tt2l;
	double ge4j_data_min_non_tt2l_err = sqrt( pow(ge4j_data_err,2) + pow(ge4j_non_tt2l_err,2) );

	// SF4
	double SF4 = ge4j_data_min_non_tt2l/ge4j_tt2l;
	double SF4_err = SF4*sqrt( pow( ge4j_data_min_non_tt2l_err/ge4j_data_min_non_tt2l, 2 ) + pow( ge4j_tt2l_err/ge4j_tt2l,2 ) );
	
	
	// K3
	double K3 = SF3/SF2;
	double K3_err = K3*sqrt( pow(SF3_err/SF3,2) + pow(SF2_err/SF2,2) );
	double K3_errSq = pow( K3_err, 2 );
	double K3_stat_err = K3_err;

	// K4
	double K4 = SF4/SF2;
	double K4_err = K4*sqrt( pow(SF4_err/SF4,2) + pow(SF2_err/SF2,2) );
	double K4_errSq = pow( K4_err, 2 );
	double K4_stat_err = K4_err;

	fprintf(outFile_SFuncs, "Nominal & %.2f & %.2f &  & %.2f & %.2f & ", K3, K3, K4, K4);
	fprintf(outFile_SFuncs, "\\"); fprintf(outFile_SFuncs, "\\ \\hline \n");
	
	fprintf(outFile_SFuncs, "Statistical & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f ", K3+K3_err,K3-K3_err, 100*K3_err/K3, K4+K4_err, K4-K4_err, 100*K4_err/K4 );
	fprintf(outFile_SFuncs, "\\"); fprintf(outFile_SFuncs, "\\ \\hline \n");
	cout << __LINE__ << endl;
	
	//
	// Loop over systematics
	//
	
	for(int iSys=1; iSys<(int)h_helper.systematics.size(); iSys+=2){
	  cout << "iSYS=" << iSys << ", sys=" << h_helper.systematics[iSys]->label << endl;
	  // Incl, Up Systematic
	  TString hNameInclUp = hNameBase;
	  hNameInclUp += "__";
	  hNameInclUp += hName_flav;
	  hNameInclUp += "__";
	  hNameInclUp += h_helper.systematics[iSys]->label;
	  hNameInclUp += "__";
	  hNameInclUp += h_helper.categories[cat_idx]->label;
	  cout << __LINE__ << endl;
	  // 2lep
	  TString hName2LepUp = hNameBase;
	  hName2LepUp += "__";
	  hName2LepUp += hName_flav_tt2l;
	  hName2LepUp += "__";
	  hName2LepUp += h_helper.systematics[iSys]->label;
	  hName2LepUp += "__";
	  hName2LepUp += h_helper.categories[cat_idx]->label;
	  cout << __LINE__ << endl;

	  cout << " hNameInclUp= " << hNameInclUp << endl;
	  cout << " hName2LepUp= " << hName2LepUp << endl;
	  // == 2jet bin, Up
	  h_tt2l = (TH1D*)f_tt2l->Get(hName2LepUp);
	  double ee2j_tt2l_up = h_tt2l->GetBinContent( h_tt2l->FindBin(2) );
	  cout << __LINE__ << endl;
	  h_allBkg = (TH1D*)f_allBkg->Get(hNameInclUp);
	  h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameInclUp+"__non_tt2l");
	  h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
	  double ee2j_non_tt2l_up = h_non_tt2l->GetBinContent( h_non_tt2l->FindBin(2) );
	  cout << __LINE__ << endl;
	  double ee2j_data_min_non_tt2l_up = ee2j_data - ee2j_non_tt2l_up;
	  
	  double SF2_up = ee2j_data_min_non_tt2l_up/ee2j_tt2l_up;

	  cout << __LINE__ << endl;
	  // ==3 jet bin, Up
	  h_tt2l = (TH1D*)f_tt2l->Get(hName2LepUp);
	  double ee3j_tt2l_up = h_tt2l->GetBinContent( h_tt2l->FindBin(3) );
	  cout << __LINE__ << endl;
	  h_allBkg = (TH1D*)f_allBkg->Get(hNameInclUp);
	  h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameInclUp+"__non_tt2l");
	  h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
	  double ee3j_non_tt2l_up = h_non_tt2l->GetBinContent( h_non_tt2l->FindBin(3) );
	  
	  double ee3j_data_min_non_tt2l_up = ee3j_data - ee3j_non_tt2l_up;
	  
	  double SF3_up = ee3j_data_min_non_tt2l_up/ee3j_tt2l_up;
	  cout << __LINE__ << endl;
	  
	  // >=4 jet bin, Up
	  h_tt2l = (TH1D*)f_tt2l->Get(hName2LepUp);
	  double ge4j_tt2l_up = h_tt2l->Integral( h_tt2l->FindBin(4), -1 );
	  
	  h_allBkg = (TH1D*)f_allBkg->Get(hNameInclUp);
	  double ge4j_allBkg_up = h_allBkg->Integral( h_allBkg->FindBin(4), -1 );
	  
	  h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameInclUp+"__non_tt2l");
	  h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
	  double ge4j_non_tt2l_up = h_non_tt2l->Integral( h_non_tt2l->FindBin(4), -1 );
	  
	  double ge4j_data_min_non_tt2l_up = ge4j_data - ge4j_non_tt2l_up;
	  cout << __LINE__ << endl;
	  
	  // SF4, Up
	  double SF4_up = ge4j_data_min_non_tt2l_up/ge4j_tt2l_up;
	  
	  // K3, Up
	  double K3_up = SF3_up/SF2_up;
	
	  // K4, Up
	  double K4_up = SF4_up/SF2_up;
	  
	  cout << "iSYS=" << iSys+1 << ", sys=" << h_helper.systematics[iSys+1]->label << endl;

	  // Incl, Down systematic
	  TString hNameInclDown = hNameBase;
	  hNameInclDown += "__";
	  hNameInclDown += hName_flav;
	  hNameInclDown += "__";
	  hNameInclDown += h_helper.systematics[iSys+1]->label;
	  hNameInclDown += "__";
	  hNameInclDown += h_helper.categories[cat_idx]->label;
	
	  // 2lep
	  TString hName2LepDown = hNameBase;
	  hName2LepDown += "__";
	  hName2LepDown += hName_flav_tt2l;
	  hName2LepDown += "__";
	  hName2LepDown += h_helper.systematics[iSys+1]->label;
	  hName2LepDown += "__";
	  hName2LepDown += h_helper.categories[cat_idx]->label;
	  
	  
	  // == 2jet bin, Down
	  h_tt2l = (TH1D*)f_tt2l->Get(hName2LepDown);
	  double ee2j_tt2l_down = h_tt2l->GetBinContent( h_tt2l->FindBin(2) );
	  
	  h_allBkg = (TH1D*)f_allBkg->Get(hNameInclDown);
	  h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameInclDown+"__non_tt2l");
	  h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
	  double ee2j_non_tt2l_down = h_non_tt2l->GetBinContent( h_non_tt2l->FindBin(2) );
	  
	  double ee2j_data_min_non_tt2l_down = ee2j_data - ee2j_non_tt2l_down;
      
	  double SF2_down = ee2j_data_min_non_tt2l_down/ee2j_tt2l_down;
	  
	  
	  // ==3 jet bin, Down
	  h_tt2l = (TH1D*)f_tt2l->Get(hName2LepDown);
	  double ee3j_tt2l_down = h_tt2l->GetBinContent( h_tt2l->FindBin(3) );
	  
	  h_allBkg = (TH1D*)f_allBkg->Get(hNameInclDown);
	  h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameInclDown+"__non_tt2l");
	  h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
	  double ee3j_non_tt2l_down = h_non_tt2l->GetBinContent( h_non_tt2l->FindBin(3) );
	
	  double ee3j_data_min_non_tt2l_down = ee3j_data - ee3j_non_tt2l_down;
	  
	  double SF3_down = ee3j_data_min_non_tt2l_down/ee3j_tt2l_down;
	  
	  
	  // >=4 jet bin, Down
	  h_tt2l = (TH1D*)f_tt2l->Get(hName2LepDown);
	  double ge4j_tt2l_down = h_tt2l->Integral( h_tt2l->FindBin(4), -1 );
	
	  h_allBkg = (TH1D*)f_allBkg->Get(hNameInclDown);
	  double ge4j_allBkg_down = h_allBkg->Integral( h_allBkg->FindBin(4), -1 );
	  
	  h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameInclDown+"__non_tt2l");
	  h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
	  double ge4j_non_tt2l_down = h_non_tt2l->Integral( h_non_tt2l->FindBin(4), -1 );
	  
	  double ge4j_data_min_non_tt2l_down = ge4j_data - ge4j_non_tt2l_down;

	
	  // SF4, Down
	  double SF4_down = ge4j_data_min_non_tt2l_down/ge4j_tt2l_down;
	  
	  // K3, Down
	  double K3_down = SF3_down/SF2_down;
	  
	  // K4, Down
	  double K4_down = SF4_down/SF2_down;
	  
	  
	  // K3 err
	  double K3_maxDiff = fabs(K3-K3_up);
	  K3_maxDiff = std::max( K3_maxDiff, fabs(K3-K3_down) );
	  K3_errSq += pow( K3_maxDiff, 2 );
	  
	  // K4 err
	  double K4_maxDiff = fabs(K4-K4_up);
	  K4_maxDiff = std::max( K4_maxDiff, fabs(K4-K4_down) );
	  K4_errSq += pow( K4_maxDiff, 2 );
	  
	  
	  TString sys_label_tex = h_helper.systematics[iSys+1]->tex;
	  sys_label_tex.ReplaceAll(",~Scale~Up","");
	  sys_label_tex.ReplaceAll(",~Scale~Down","");
	  
	  fprintf(outFile_SFuncs, "$%s$ & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f ", sys_label_tex.Data(), K3_up, K3_down, 100*K3_maxDiff/K3, K4_up, K4_down, 100*K4_maxDiff/K4 );
	  fprintf(outFile_SFuncs, "\\"); fprintf(outFile_SFuncs, "\\ \\hline \n");
	  
	} // end loop over systematics in histoHelper
	cout << __LINE__ << endl;
	

	/*
	//
	// JES uncertainty
	//
	
	// 2 jet bin, jesUp
	h_tt2l = (TH1D*)f_tt2l_jesUp->Get(hName2Lep);
	double ee2j_tt2l_jesUp = h_tt2l->GetBinContent( h_tt2l->FindBin(2) );
            
	h_allBkg = (TH1D*)f_allBkg_jesUp->Get(hNameIncl);
	h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameIncl+"__non_tt2l__jesUp");
	h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
	double ee2j_non_tt2l_jesUp = h_non_tt2l->GetBinContent( h_non_tt2l->FindBin(2) );
	
	double ee2j_data_min_non_tt2l_jesUp = ee2j_data - ee2j_non_tt2l_jesUp;
      
	double SF2_jesUp = ee2j_data_min_non_tt2l_jesUp/ee2j_tt2l_jesUp;
	
	
	// 3 jet bin, jesUp
	h_tt2l = (TH1D*)f_tt2l_jesUp->Get(hName2Lep);
	double ee3j_tt2l_jesUp = h_tt2l->GetBinContent( h_tt2l->FindBin(3) );
	
	h_allBkg = (TH1D*)f_allBkg_jesUp->Get(hNameIncl);
	h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameIncl+"__non_tt2l__jesUp");
	h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
	double ee3j_non_tt2l_jesUp = h_non_tt2l->GetBinContent( h_non_tt2l->FindBin(3) );
	
	double ee3j_data_min_non_tt2l_jesUp = ee3j_data - ee3j_non_tt2l_jesUp;
      
	double SF3_jesUp = ee3j_data_min_non_tt2l_jesUp/ee3j_tt2l_jesUp;
	
	
	// >=4 jet bin, jesUp
	h_tt2l = (TH1D*)f_tt2l_jesUp->Get(hName2Lep);
	double ge4j_tt2l_jesUp = h_tt2l->Integral( h_tt2l->FindBin(4), -1 );
	
	h_allBkg = (TH1D*)f_allBkg_jesUp->Get(hNameIncl);
	double ge4j_allBkg_jesUp = h_allBkg->Integral( h_allBkg->FindBin(4), -1 );
	
	h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameIncl+"__non_tt2l__jesUp");
	h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
	double ge4j_non_tt2l_jesUp = h_non_tt2l->Integral( h_non_tt2l->FindBin(4), -1 );
        
	double ge4j_data_min_non_tt2l_jesUp = ge4j_data - ge4j_non_tt2l_jesUp;
	
	// SF4, jesUp
	double SF4_jesUp = ge4j_data_min_non_tt2l_jesUp/ge4j_tt2l_jesUp;
	
	// K3, jesUp
	double K3_jesUp = SF3_jesUp/SF2_jesUp;
	
	// K4, jesUp
	double K4_jesUp = SF4_jesUp/SF2_jesUp;
	
	
	
	// 2 jet bin, jesDown
	h_tt2l = (TH1D*)f_tt2l_jesDown->Get(hName2Lep);
	double ee2j_tt2l_jesDown = h_tt2l->GetBinContent( h_tt2l->FindBin(2) );
	
	h_allBkg = (TH1D*)f_allBkg_jesDown->Get(hNameIncl);
	h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameIncl+"__non_tt2l__jesDown");
	h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
	double ee2j_non_tt2l_jesDown = h_non_tt2l->GetBinContent( h_non_tt2l->FindBin(2) );
	
	double ee2j_data_min_non_tt2l_jesDown = ee2j_data - ee2j_non_tt2l_jesDown;
      
	double SF2_jesDown = ee2j_data_min_non_tt2l_jesDown/ee2j_tt2l_jesDown;
	
	
	// 3 jet bin, jesDown
	h_tt2l = (TH1D*)f_tt2l_jesDown->Get(hName2Lep);
	double ee3j_tt2l_jesDown = h_tt2l->GetBinContent( h_tt2l->FindBin(3) );
	
	h_allBkg = (TH1D*)f_allBkg_jesDown->Get(hNameIncl);
	h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameIncl+"__non_tt2l__jesDown");
	h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
	double ee3j_non_tt2l_jesDown = h_non_tt2l->GetBinContent( h_non_tt2l->FindBin(3) );
	
	double ee3j_data_min_non_tt2l_jesDown = ee3j_data - ee3j_non_tt2l_jesDown;
	
	double SF3_jesDown = ee3j_data_min_non_tt2l_jesDown/ee3j_tt2l_jesDown;
	
	
	// >=4 jet bin, jesDown
	h_tt2l = (TH1D*)f_tt2l_jesDown->Get(hName2Lep);
	double ge4j_tt2l_jesDown = h_tt2l->Integral( h_tt2l->FindBin(4), -1 );
            
	h_allBkg = (TH1D*)f_allBkg_jesDown->Get(hNameIncl);
	double ge4j_allBkg_jesDown = h_allBkg->Integral( h_allBkg->FindBin(4), -1 );
	
	h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameIncl+"__non_tt2l__jesDown");
	h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
	double ge4j_non_tt2l_jesDown = h_non_tt2l->Integral( h_non_tt2l->FindBin(4), -1 );
        
	double ge4j_data_min_non_tt2l_jesDown = ge4j_data - ge4j_non_tt2l_jesDown;
      
	// SF4, jesDown
	double SF4_jesDown = ge4j_data_min_non_tt2l_jesDown/ge4j_tt2l_jesDown;
      
	// K3, jesDown
	double K3_jesDown = SF3_jesDown/SF2_jesDown;
	
	// K4, jesDown
	double K4_jesDown = SF4_jesDown/SF2_jesDown;
	

	// K3 err
	double K3_maxDiff_jes = fabs(K3-K3_jesUp);
	K3_maxDiff_jes = std::max( K3_maxDiff_jes, fabs(K3-K3_jesDown) );
	K3_errSq += pow( K3_maxDiff_jes, 2 );
	
	// K4 err
	double K4_maxDiff_jes = fabs(K4-K4_jesUp);
	K4_maxDiff_jes = std::max( K4_maxDiff_jes, fabs(K4-K4_jesDown) );
	K4_errSq += pow( K4_maxDiff_jes, 2 );
	
	
	fprintf(outFile_SFuncs, "JES & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f ", K3_jesUp, K3_jesDown, 100*K3_maxDiff_jes/K3, K4_jesUp, K4_jesDown, 100*K4_maxDiff_jes/K4 );
	fprintf(outFile_SFuncs, "\\"); fprintf(outFile_SFuncs, "\\ \\hline \n");
	*/
	
	
	//
	// K3, K4 errors almost done...
	//
	K3_err = sqrt(K3_errSq);
	K4_err = sqrt(K4_errSq);
	

	//
	// Print Calc to Screen
	//
	
	// == 2jet
	cout << "  Data ==2j: " << ee2j_data << ", err: " << ee2j_data_err << endl;
	cout << "  tt2l ==2j: " << ee2j_tt2l << ", err: " << ee2j_tt2l_err << endl;
	cout << "  allBkg ==2j: " << h_allBkg->GetBinContent( h_allBkg->FindBin(2) ) << ", err: " << h_allBkg->GetBinError( h_allBkg->FindBin(2) ) << endl;
	cout << "  SF2: " << SF2 << endl;
	cout << endl;
	
	// ==3 jet 
	cout << "  Data ==3j: " << ee3j_data << ", err: " << ee3j_data_err << endl;
	cout << "  tt2l ==3j: " << ee3j_tt2l << ", err: " << ee3j_tt2l_err << endl;
	cout << "  allBkg ==3j: " << h_allBkg->GetBinContent( h_allBkg->FindBin(3) ) << ", err: " << h_allBkg->GetBinError( h_allBkg->FindBin(3) ) << endl;
	cout << "  SF3: " << SF3 << endl;
	cout << endl;
	
	// ==4 jet
	cout << "  Data >=4j: " << ge4j_data << ", err: " << ge4j_data_err << endl;
	cout << "  tt2l >=4j: " << ge4j_tt2l << ", err: " << ge4j_tt2l_err << endl;
	cout << "  allBkg >=4j: " << ge4j_allBkg << ", err: " << ge4j_allBkg_err << endl;
	cout << "  SF4: " << SF4 << endl;
	cout << endl;
	
	// K3, K4      
	cout << "  K3: " << K3 << ", err: " << K3_err << endl;
	cout << "  K4: " << K4 << ", err: " << K4_err << endl;
	cout << endl;
	cout << endl;
	
	
	// Print Results to tex file
	//fprintf(outFile_metBins, " & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f", K3, K3_err, K4, K4_err);
	fprintf(outFile_metBins, " & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f", K3, K3_stat_err, K4, K4_stat_err);	
	fprintf(outFile_metBins, "\\"); fprintf(outFile_metBins, "\\ \\hline \n");
	
	
	fprintf(outFile_SFuncs, "Final Uncertainty & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f ", K3+K3_err, K3-K3_err, 100*K3_err/K3, K4+K4_err, K4-K4_err, 100*K4_err/K4 );
	fprintf(outFile_SFuncs, "\\"); fprintf(outFile_SFuncs, "\\ \\hline \n");

	
	fprintf(outFile_SFuncs, "\\end{tabular} \n");
	fprintf(outFile_SFuncs, "\\end{document} \n");
	fclose(outFile_SFuncs);
	
	cout << endl;
	cout << "Table of nJets SF Uncertainties written to: " << fileName_SFuncs << endl;
	cout << endl;
    
      


      } // end loop over categories

      fprintf(outFile_metBins, "\\end{tabular} \n");
      fprintf(outFile_metBins, "\\end{document} \n");
      fclose(outFile_metBins);
        
      cout << endl;
      cout << "Table of nJets SF vs MET written to: " << fileName_metBins << endl;
      cout << endl;
    
      
    }  // end loop over tables

  } // end loop over flavours
    
  return;
}
