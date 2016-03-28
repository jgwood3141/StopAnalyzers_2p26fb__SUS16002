#include "Riostream.h"
#include "TFile.h"
#include "TH1.h"
#include "TString.h"

#include <vector>

#include "histoHelper.h"

void nJets_SF_extractor(){

  // Open Files and Get Histos
  TString inDir  = "Histos/Nominal/";
  TString outDir = "Plots/";
  
  TFile *f_data   = new TFile(inDir+"histos__data_25ns.root", "read");
  TFile *f_tt2l   = new TFile(inDir+"histos__ttbar_25ns.root", "read");
  TFile *f_allBkg = new TFile(inDir+"histos__allBkg_25ns.root", "read");
  
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

  // Loop over tables 
  FILE *outFile;
  for(int iTable=0; iTable<(int)tables.size(); iTable++){

    TString fileName = outDir;
    fileName += "nJets_SF__";
    fileName += h_helper.categories[tables[iTable][0]]->label;
    fileName += ".tex";
    outFile = fopen(fileName.Data(), "w");
      
    // Tex File Formatting
    fprintf(outFile, "\\documentclass{article}\n");
    fprintf(outFile, "\\usepackage[landscape]{geometry}\n");
    fprintf(outFile, "\\usepackage{chngpage}\n\n");
    fprintf(outFile, "\\begin{document}\n");
    //fprintf(outFile, "\\small\n");
    fprintf(outFile, "\\tiny\n");
    
    // Get number of collumns for table - ie categories
    fprintf(outFile, "\\begin{tabular}{|l|c|c|");
    fprintf(outFile, "} \\hline \n");
    
    fprintf(outFile, "Category & $nJets=3 (K_{3})$ & $nJets>=4 (K_{4})$ ");
    fprintf(outFile, "\\"); fprintf(outFile, "\\ \\hline \n");
  
    
    for(int iCat=0; iCat<(int)tables[iTable].size(); iCat++){
      
      int cat_idx = tables[iTable][iCat];

      fprintf(outFile, "$%s$ ", h_helper.categories[cat_idx]->title.Data());
      cout << "Category: " << h_helper.categories[cat_idx]->title.Data() << endl;

      // Get Histograms for nJets
      
      // Data
      TString hNameData = hNameBase;
      hNameData += "__";
      hNameData += hName_incl;
      hNameData += "__";
      hNameData += hName_nominal_sys;
      hNameData += "__";
      hNameData += h_helper.categories[cat_idx]->label;
      

      // Incl
      TString hNameIncl = hNameBase;
      hNameIncl += "__";
      hNameIncl += hName_incl;
      hNameIncl += "__";
      hNameIncl += hName_nominal_sys;
      hNameIncl += "__";
      hNameIncl += h_helper.categories[cat_idx]->label;
      
    
      // 2lep
      TString hName2Lep = hNameBase;
      hName2Lep += "__";
      hName2Lep += hName_2lep;
      hName2Lep += "__";
      hName2Lep += hName_nominal_sys;
      hName2Lep += "__";
      hName2Lep += h_helper.categories[cat_idx]->label;
      
      //cout << "hNameData = " << hNameData << endl;
      //cout << "hNameIncl = " << hNameIncl << endl;
      //cout << "hName2Lep = " << hName2Lep << endl;

      
      // 2 jet bin
      h_data = (TH1D*)f_data->Get(hNameData);
      if(!h_data) cout << "BAD DATA HISTO: " << hNameData << endl;
      double ee2j_data = h_data->GetBinContent( h_data->FindBin(2) );
      double ee2j_data_err = sqrt( ee2j_data );
      
      h_tt2l = (TH1D*)f_tt2l->Get(hName2Lep);
      double ee2j_tt2l = h_tt2l->GetBinContent( h_tt2l->FindBin(2) );
      double ee2j_tt2l_err = h_tt2l->GetBinError( h_tt2l->FindBin(2) );
            
      h_allBkg = (TH1D*)f_allBkg->Get(hNameIncl);
      h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameIncl+"__non_tt2l");
      h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
      double ee2j_non_tt2l = h_non_tt2l->GetBinContent( h_non_tt2l->FindBin(2) );
      double ee2j_non_tt2l_err = h_non_tt2l->GetBinError( h_non_tt2l->FindBin(2) );
      
      double ee2j_data_min_non_tt2l = ee2j_data - ee2j_non_tt2l;
      double ee2j_data_min_non_tt2l_err = sqrt( pow(ee2j_data_err, 2) + pow(ee2j_non_tt2l_err, 2) );
      
      double SF2 = ee2j_data_min_non_tt2l/ee2j_tt2l;
      double SF2_err = SF2*sqrt( pow( ee2j_data_min_non_tt2l_err/ee2j_data_min_non_tt2l, 2 ) + pow( ee2j_tt2l_err/ee2j_tt2l, 2 ) );
      
      
      // 3 jet bin
      h_data = (TH1D*)f_data->Get(hNameData);
      double ee3j_data = h_data->GetBinContent( h_data->FindBin(3) );
      double ee3j_data_err = sqrt( ee3j_data );
      
      h_tt2l = (TH1D*)f_tt2l->Get(hName2Lep);
      double ee3j_tt2l = h_tt2l->GetBinContent( h_tt2l->FindBin(3) );
      double ee3j_tt2l_err = h_tt2l->GetBinError( h_tt2l->FindBin(3) );
      
      h_allBkg = (TH1D*)f_allBkg->Get(hNameIncl);
      h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameIncl+"__non_tt2l");
      h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
      double ee3j_non_tt2l = h_non_tt2l->GetBinContent( h_non_tt2l->FindBin(3) );
      double ee3j_non_tt2l_err = h_non_tt2l->GetBinError( h_non_tt2l->FindBin(3) );
      
      double ee3j_data_min_non_tt2l = ee3j_data - ee3j_non_tt2l;
      double ee3j_data_min_non_tt2l_err = sqrt( pow(ee3j_data_err, 2) + pow(ee3j_non_tt2l_err, 2) );
      
      double SF3 = ee3j_data_min_non_tt2l/ee3j_tt2l;
      double SF3_err = SF3*sqrt( pow( ee3j_data_min_non_tt2l_err/ee3j_data_min_non_tt2l, 2 ) + pow( ee3j_tt2l_err/ee3j_tt2l, 2 ) );
      
      
      // >=4 jet bin
      h_data = (TH1D*)f_data->Get(hNameData);
      double ge4j_data = h_data->Integral( h_data->FindBin(4), -1 );
      double ge4j_data_err = sqrt( ge4j_data );
      
      h_tt2l = (TH1D*)f_tt2l->Get(hName2Lep);
      double ge4j_tt2l_err = 0.0;
      double ge4j_tt2l = h_tt2l->IntegralAndError( h_tt2l->FindBin(4), -1, ge4j_tt2l_err );
            
      h_allBkg = (TH1D*)f_allBkg->Get(hNameIncl);
      double ge4j_allBkg_err = 0.0;
      double ge4j_allBkg = h_allBkg->IntegralAndError( h_allBkg->FindBin(4), -1, ge4j_allBkg_err );

      h_non_tt2l = (TH1D*)h_allBkg->Clone(hNameIncl+"__non_tt2l");
      h_non_tt2l->Add(h_allBkg, h_tt2l, 1, -1);
      double ge4j_non_tt2l_err = 0.0;
      double ge4j_non_tt2l = h_non_tt2l->IntegralAndError( h_non_tt2l->FindBin(4), -1, ge4j_non_tt2l_err );
        
      double ge4j_data_min_non_tt2l = ge4j_data - ge4j_non_tt2l;
      double ge4j_data_min_non_tt2l_err = sqrt( pow(ge4j_data_err, 2) + pow(ge4j_non_tt2l_err, 2) );
      
      // SF4
      double SF4 = ge4j_data_min_non_tt2l/ge4j_tt2l;
      double SF4_err = SF3*sqrt( pow( ge4j_data_min_non_tt2l_err/ge4j_data_min_non_tt2l, 2 ) + pow( ge4j_tt2l_err/ge4j_tt2l, 2 ) );
      
      // K3
      double K3 = SF3/SF2;
      double K3_err = K3*sqrt( pow( SF3_err/SF3, 2 ) + pow( SF2_err/SF2, 2 ) );
      
      // K4
      double K4 = SF4/SF2;
      double K4_err = K4*sqrt( pow( SF4_err/SF4, 2 ) + pow( SF2_err/SF2, 2 ) );
 
      //
      // Print Calc to Screen
      //

      // == 2jet
      cout << "  Data ==2j: " << ee2j_data << ", err: " << ee2j_data_err << endl;
      cout << "  tt2l ==2j: " << ee2j_tt2l << ", err: " << ee2j_tt2l_err << endl;
      cout << "  allBkg ==2j: " << h_allBkg->GetBinContent( h_allBkg->FindBin(2) ) << ", err: " << h_allBkg->GetBinError( h_allBkg->FindBin(2) ) << endl;
      cout << "  nonTT2l ==2j: " << ee2j_non_tt2l << ", err: " << ee2j_non_tt2l_err << endl;
      cout << "  data-nonTT2l ==2j: " << ee2j_data_min_non_tt2l << ", err: " << ee2j_data_min_non_tt2l_err << endl;
      cout << "  SF2: " << SF2 << ", err: " << SF2_err << endl;
      cout << endl;
      
      // ==3 jet 
      cout << "  Data ==3j: " << ee3j_data << ", err: " << ee3j_data_err << endl;
      cout << "  tt2l ==3j: " << ee3j_tt2l << ", err: " << ee3j_tt2l_err << endl;
      cout << "  allBkg ==3j: " << h_allBkg->GetBinContent( h_allBkg->FindBin(3) ) << ", err: " << h_allBkg->GetBinError( h_allBkg->FindBin(3) ) << endl;
      cout << "  nonTT2l ==3j: " << ee3j_non_tt2l << ", err: " << ee3j_non_tt2l_err << endl;
      cout << "  data-nonTT2l ==3j: " << ee3j_data_min_non_tt2l << ", err: " << ee3j_data_min_non_tt2l_err << endl;
      cout << "  SF3: " << SF3 << ", err: " << SF3_err << endl;
      cout << endl;

      // ==4 jet
      cout << "  Data >=4j: " << ge4j_data << ", err: " << ge4j_data_err << endl;
      cout << "  tt2l >=4j: " << ge4j_tt2l << ", err: " << ge4j_tt2l_err << endl;
      cout << "  allBkg >=4j: " << ge4j_allBkg << ", err: " << ge4j_allBkg_err << endl;
      cout << "  nonTT2l >=4j: " << ge4j_non_tt2l << ", err: " << ge4j_non_tt2l_err << endl;
      cout << "  data-nonTT2l >=4j: " << ge4j_data_min_non_tt2l << ", err: " << ge4j_data_min_non_tt2l_err << endl;
      cout << "  SF4: " << SF4 << ", err: " << SF4_err << endl;
      cout << endl;

      // K3, K4      
      cout << "  K3: " << K3 << ", err: " << K3_err << endl;
      cout << "  K4: " << K4 << ", err: " << K4_err << endl;
      cout << endl;
      cout << endl;
      

      // Print Results to tex file
      fprintf(outFile, " & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f", K3, K3_err, K4, K4_err);
      
      fprintf(outFile, "\\"); fprintf(outFile, "\\ \\hline \n");

    } // end loop over categories

    fprintf(outFile, "\\end{tabular} \n");
    fprintf(outFile, "\\end{document} \n");
    fclose(outFile);
    
    
    cout << endl;
    cout << "Table of nJets SF written to: " << fileName << endl;
    cout << endl;
    
  }  // end loop over tables
    

  return;
}
