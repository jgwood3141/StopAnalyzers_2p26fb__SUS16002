// ROOT
#include "TROOT.h"
#include "Riostream.h"
#include "TChain.h"
#include "TFile.h"
#include "TTreeCache.h"
#include "TString.h"

// babyAnalyzer
#include "stop_1l_babyAnalyzer.cc"

using namespace std;
using namespace stop_1l;

//
// Declare Functions
//
void skimThisBaby(TString inPath, TString inFileName, TString inTreeName, TString outPath);

//
// Main
//
void skimBaby_CR_emu(){
  

  //
  // I/O
  //

  vector<TString> inDirs;
  vector<TString> outDirs;

  // Nominal
  //TString in_dir  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/";
  //TString out_dir = "/data/tmp/jgwood/temp_stopBabies__SKIMS__20151211/Skims_CR_emu__20151211/";
  TString in_dir  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v9__20160127/merged_files/";
  TString out_dir = "/data/tmp/jgwood/temp_stopBabies__SKIMS__20160202/Skims_CR_emu__20160202/";

  inDirs.push_back(in_dir);
  outDirs.push_back(out_dir);


  // JECup
  //in_dir       = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies_JECup__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/";
  //out_dir      = "/data/tmp/jgwood/temp_stopBabies__SKIMS__20151211/Skims_CR_emu__JECup__20151211/";
  in_dir       = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies_JECup__CMS3_V070411__BabyMaker_V0704X_v9__20160127/merged_files/";
  out_dir      = "/data/tmp/jgwood/temp_stopBabies__SKIMS__20160202/Skims_CR_emu__JECup__20160202/";

  //inDirs.push_back(in_dir);
  //outDirs.push_back(out_dir);


  // JECdown
  //in_dir       = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies_JECdown__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/";
  //out_dir      = "/data/tmp/jgwood/temp_stopBabies__SKIMS__20151211/Skims_CR_emu__JECdown__20151211/";
  in_dir       = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies_JECdown__CMS3_V070411__BabyMaker_V0704X_v9__20160127/merged_files/";
  out_dir      = "/data/tmp/jgwood/temp_stopBabies__SKIMS__20160202/Skims_CR_emu__JECdown__20160202/";

  //inDirs.push_back(in_dir);
  //outDirs.push_back(out_dir);



  TString in_tree_name = "t";
    
  //
  // Data
  //
  
  // Single Ele
  skimThisBaby(inDirs[0],"data_single_electron_2015D_promptRecoV4_25ns*.root", in_tree_name, outDirs[0]);
  skimThisBaby(inDirs[0],"data_single_electron_2015D_05Oct2015_v1_25ns*.root", in_tree_name, outDirs[0]);
  //skimThisBaby(inDirs[0],"data_single_electron_2015D_promptRecoV3_25ns*.root", in_tree_name, outDirs[0]);
  skimThisBaby(inDirs[0],"data_single_electron_2015C_25ns*.root", in_tree_name, outDirs[0]);

  // Single Mu
  skimThisBaby(inDirs[0],"data_single_muon_2015D_promptRecoV4_25ns*.root", in_tree_name, outDirs[0]);
  skimThisBaby(inDirs[0],"data_single_muon_2015D_05Oct2015_v1_25ns*.root", in_tree_name, outDirs[0]);
  //skimThisBaby(inDirs[0],"data_single_muon_2015D_promptRecoV3_25ns*.root", in_tree_name, outDirs[0]);
  skimThisBaby(inDirs[0],"data_single_muon_2015C_25ns*.root", in_tree_name, outDirs[0]);

  // MET
  skimThisBaby(inDirs[0],"data_met_2015D_promptRecoV4_25ns*.root", in_tree_name, outDirs[0]);
  skimThisBaby(inDirs[0],"data_met_2015D_05Oct2015_v1_25ns*.root", in_tree_name, outDirs[0]);
  //skimThisBaby(inDirs[0],"data_met_2015D_promptRecoV3_25ns*.root", in_tree_name, outDirs[0]);
  skimThisBaby(inDirs[0],"data_met_2015C_25ns*.root", in_tree_name, outDirs[0]);

  // Double Ele
  skimThisBaby(inDirs[0],"data_double_eg_2015D_promptRecoV4_25ns*.root", in_tree_name, outDirs[0]);
  skimThisBaby(inDirs[0],"data_double_eg_2015D_05Oct2015_v1_25ns*.root", in_tree_name, outDirs[0]);
  //skimThisBaby(inDirs[0],"data_double_eg_2015D_promptRecoV3_25ns*.root", in_tree_name, outDirs[0]);
  skimThisBaby(inDirs[0],"data_double_eg_2015C_25ns*.root", in_tree_name, outDirs[0]);

  // Muon EG
  skimThisBaby(inDirs[0],"data_muon_eg_2015D_promptRecoV4_25ns*.root", in_tree_name, outDirs[0]);
  skimThisBaby(inDirs[0],"data_muon_eg_2015D_05Oct2015_v2_25ns*.root", in_tree_name, outDirs[0]);
  skimThisBaby(inDirs[0],"data_muon_eg_2015D_05Oct2015_v1_25ns*.root", in_tree_name, outDirs[0]);
  //skimThisBaby(inDirs[0],"data_muon_eg_2015D_promptRecoV3_25ns*.root", in_tree_name, outDirs[0]);
  skimThisBaby(inDirs[0],"data_muon_eg_2015C_25ns*.root", in_tree_name, outDirs[0]);

  // Double Muon
  skimThisBaby(inDirs[0],"data_double_mu_2015D_promptRecoV4_25ns*.root", in_tree_name, outDirs[0]);
  skimThisBaby(inDirs[0],"data_double_mu_2015D_05Oct2015_v1_25ns*.root", in_tree_name, outDirs[0]);
  //skimThisBaby(inDirs[0],"data_double_mu_2015D_promptRecoV3_25ns*.root", in_tree_name, outDirs[0]);
  skimThisBaby(inDirs[0],"data_double_mu_2015C_25ns*.root", in_tree_name, outDirs[0]);
  
  for(int iDir=0; iDir<(int)inDirs.size(); iDir++){

    //
    // Signal
    //

    // T2tt
    //skimThisBaby(inDirs[iDir],"T2tt_2J_mStop_850_mLSP_100_25ns*.root", in_tree_name, outDirs[iDir]);
    //skimThisBaby(inDirs[iDir],"T2tt_2J_mStop_650_mLSP_325_25ns*.root", in_tree_name, outDirs[iDir]);
    //skimThisBaby(inDirs[iDir],"T2tt_2J_mStop_500_mLSP_325_25ns*.root", in_tree_name, outDirs[iDir]);
    //skimThisBaby(inDirs[iDir],"T2tt_2J_mStop_425_mLSP_325_25ns*.root", in_tree_name, outDirs[iDir]);

    // T6bbWW
    //skimThisBaby(inDirs[iDir],"T6bbWW_mStop425_mCh400_mLSP50*.root", in_tree_name, outDirs[iDir]);


    //
    // Backgrounds
    //
  
    // ttbar
    skimThisBaby(inDirs[iDir],"ttbar_powheg_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"ttbar_powheg_pythia8_ext3_25ns*.root", in_tree_name, outDirs[iDir]);
    //skimThisBaby(inDirs[iDir],"ttbar_singleLeptFromT_madgraph_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    //skimThisBaby(inDirs[iDir],"ttbar_singleLeptFromT_madgraph_pythia8_ext1_25ns*.root", in_tree_name, outDirs[iDir]);
    //skimThisBaby(inDirs[iDir],"ttbar_singleLeptFromTbar_madgraph_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    //skimThisBaby(inDirs[iDir],"ttbar_singleLeptFromTbar_madgraph_pythia8_ext1_25ns*.root", in_tree_name, outDirs[iDir]);
    //skimThisBaby(inDirs[iDir],"ttbar_diLept_madgraph_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    //skimThisBaby(inDirs[iDir],"ttbar_diLept_madgraph_pythia8_ext1_25ns*.root", in_tree_name, outDirs[iDir]);
    //skimThisBaby(inDirs[iDir],"ttbarTo2L2Nu_powheg_25ns*.root", in_tree_name, outDirs[iDir]);
  
    // single top
    skimThisBaby(inDirs[iDir],"t_sch_4f_amcnlo_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"t_tch_4f_powheg_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"tbar_tch_4f_powheg_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"t_tW_5f_powheg_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"t_tbarW_5f_powheg_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
  
    // wJets
    skimThisBaby(inDirs[iDir],"WJetsToLNu_madgraph_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"WJetsToLNu_HT100To200_madgraph_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"WJetsToLNu_HT200To400_madgraph_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"WJetsToLNu_HT400To600_madgraph_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"WJetsToLNu_HT600ToInf_madgraph_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"WJetsToLNu_HT600To800_madgraph_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"WJetsToLNu_HT800To1200_madgraph_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);

    // zJets
    skimThisBaby(inDirs[iDir],"DYJetsToLL_m10To50_amcnlo_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"DYJetsToLL_m50_amcnlo_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);

    // WW
    skimThisBaby(inDirs[iDir],"WW_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"WWToLNuQQ_powheg_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"WWTo2l2Nu_powheg_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"WWToLNuQQ_amcnlo_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);

    // WZ
    skimThisBaby(inDirs[iDir],"WZ_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"WZ_amcnlo_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"WZTo3LNu_powheg_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"WZTo2L2Q_amcnlo_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"WZTo1LNu2Q_amcnlo_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"WZTo1L3Nu_amcnlo_pythia8*.root", in_tree_name, outDirs[iDir]);

    // ZZ
    skimThisBaby(inDirs[iDir],"ZZ_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"ZZTo4L_powheg_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"ZZTo2Q2Nu_amcnlo_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"ZZTo2L2Q_amcnlo_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"ZZTo2L2Nu_powheg_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    
    // TTV
    skimThisBaby(inDirs[iDir],"TTWJetsToLNu_amcnlo_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"TTWJetsToQQ_amcnlo_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"TTZToLLNuNu_M-10_amcnlo_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"TTZToQQ_amcnlo_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"TTGJets_amcnlo_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    
    // TV
    skimThisBaby(inDirs[iDir],"tZq_ll_4f_amcnlo_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"tZq_nunu_4f_amcnlo_pythia8_25ns*.root", in_tree_name, outDirs[iDir]);
    skimThisBaby(inDirs[iDir],"tGJets_amcnlo_pythia8_25ns*.root", in_tree_name, outDirs[iDir]); 
        
  }  
  
  return;
}


//
// Fucntions
//
void skimThisBaby(TString inPath, TString inFileName, TString inTreeName, TString outPath){

  // Talk to user
  cout << "  Skimming: "<< endl;
  cout << "     " << inPath+inFileName <<endl;
  
  // Load input TChain
  TChain *ch = new TChain(inTreeName);
  TString inFile = inPath;
  inFile += inFileName;
  ch->Add(inFile);
  Long64_t nentries = ch->GetEntries();
  TTreeCache::SetLearnEntries(10);
  ch->SetCacheSize(128*1024*1024);

  // Initialize Branches
  babyAnalyzer.Init(ch->GetTree());
  babyAnalyzer.LoadAllBranches();
  
  // Setup output file name and path
  TString outFileName = outPath;
  outFileName += inFileName;
  outFileName.ReplaceAll("*", "");
  outFileName.ReplaceAll(".root", "_skimmed.root");

  cout << "  Output will be written to: " << endl;
  cout << "      "  << outFileName << endl << endl;

  // Open outputfile and Clone input TTree
  TFile *newfile = new TFile(outFileName, "recreate");
  TTree *newtree  = (TTree*)ch->GetTree()->CloneTree(0);
  if(!newtree) cout << "BAD TTREE CLONE" << endl;
  
  TH1D *newCounter=NULL;

  // Get nEntries
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = ch->GetEntries();
  
  // Grab list of files
  TObjArray *listOfFiles = ch->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  // File Loop
  int iFile=0;
  while ( (currentFile = (TFile*)fileIter.Next()) ) {

    // Get File Content
    TFile *file = new TFile( currentFile->GetTitle() );
    TTree *tree = (TTree*)file->Get("t");
    TTreeCache::SetLearnEntries(10);
    tree->SetCacheSize(128*1024*1024);
    babyAnalyzer.Init(tree);

    if(iFile==0){
      TH1D *temp = (TH1D*)file->Get("h_counter");
      newCounter = (TH1D*)temp->Clone("h_counter");
      newCounter->SetDirectory(newfile);
    }
    //else{
    //TH1D *temp = (TH1D*)file->Get("h_counter");
    //newCounter->Add(temp);
    //}
    
    // Loop over Events in current file 
    if( nEventsTotal >= nEventsChain ) continue;
    unsigned int nEventsTree = tree->GetEntriesFast();
    for( unsigned int event = 0; event < nEventsTree; ++event) {
      
      // Progress
      stop_1l_babyAnalyzer::progress( nEventsTotal, nEventsChain );
    
      // Load Tree
      tree->LoadTree(event);
      babyAnalyzer.GetEntry(event);
      ++nEventsTotal;

      // Selection
      if(nvetoleps()<1) continue;
      //if(nvetoleps()<2 && PassTrackVeto_v3() && PassTauVeto()) continue;
      if(lep1_p4().Pt()<30.0) continue;
      if(lep1_miniRelIsoEA()>0.1) continue;
      if(lep2_p4().Pt()<15.0) continue;
      if(lep2_miniRelIsoEA()>0.1) continue;
      if( (lep1_p4()+lep2_p4()).M()<20.0 ) continue;
      if(ngoodjets()<2) continue;
      
      // Turn on all branches on input
      babyAnalyzer.LoadAllBranches();      
      
      // Fill output tree
      newtree->Fill();
    
    } // end loop over entries
    
  } // end loop over files in TChain

  // Clean up
  //newtree->Print();
  //newtree->AutoSave();
  newfile->Write();
  newfile->Close();
  delete ch;
  delete newfile;

}
