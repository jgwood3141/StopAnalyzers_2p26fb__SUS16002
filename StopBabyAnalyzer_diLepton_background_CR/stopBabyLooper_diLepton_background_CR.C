// Usage:
// > root -b scanAllChains.C

// C++
#include <iostream>
#include <vector>

// ROOT
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTreeCache.h"
#include "TLorentzVector.h"
#include "TString.h"

// stop_1l_babyAnalyzer
#include "stop_1l_babyAnalyzer.cc"

// duplicate data event removal
#include "../../CORE/Tools/dorky/dorky.cc"

// met filters
#include "../../CORE/Tools/badEventFilter.cc"

// bTag SF
#include "../../CORE/Tools/btagsf/BTagCalibrationStandalone.h"

// top pT reweighting
#include "../../CORE/MCSelections.h"

// histoHelper
#include "histoHelper.h"

using namespace std;
using namespace tas;
using namespace stop_1l;


//
// Main
//

int stopBabyLooper_diLepton_background_CR( TChain* chain, TString output_file="histos.root", bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {

  //
  // Intro
  //
  cout << "=========================================" << endl;
  cout << "  WELCOME TO STOP BABY ANALYZER! " << endl;
  cout << endl;
  cout << "     Output written to: " << output_file << endl;
  cout << "=========================================" << endl;

  //
  // Benchmark
  //
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  //
  // Output File
  //
  TFile *out_file = new TFile(output_file, "recreate");

  //
  // Declare histoHelper
  //
  TH1::SetDefaultSumw2();

  histoHelper histos;

  int nClassifications = histos.classifications.size();
  int nSystematics = histos.systematics.size();
  int nCategories = histos.categories.size();
  

  double matched_dr = 0.1;

  double eps = 0.00001;

  int nBins_dr = 100;
  double min_dr = 0.0;
  double max_dr = 1.0;

  TH1D *h_genLep_matchedTo_selLep_dr = new TH1D("h__secondLep__genLep_matchedTo_selLep_dr", "#DeltaR(genLep, selLep)", nBins_dr, min_dr, max_dr+eps);
  TH1D *h_genLep_matchedTo_selLep_isMatched = new TH1D("h__secondLep__genLep_matchedTo_selLep_isMatched", "selLep is matched", 2, -0.5, 1.5);
  
  TH1D *h_nFound_secondLeptons = new TH1D("h__secondLep__nFound_secondLeptons", "nFound, lost leptons", 6, -0.5, 5.5);

  TH1D *h_gen_secondLepton_id = new TH1D("h__secondLep__gen_secondLepton_id", "Gen Lost Lepton, pdgId", 7, 0, 7);
  h_gen_secondLepton_id->GetXaxis()->SetBinLabel(1, "ele");
  h_gen_secondLepton_id->GetXaxis()->SetBinLabel(2, "mu");
  h_gen_secondLepton_id->GetXaxis()->SetBinLabel(3, "lep tau, ele");
  h_gen_secondLepton_id->GetXaxis()->SetBinLabel(4, "lep tau, mu");
  h_gen_secondLepton_id->GetXaxis()->SetBinLabel(5, "had tau, 1 prong");
  h_gen_secondLepton_id->GetXaxis()->SetBinLabel(6, "had tau, 3 prong");
  h_gen_secondLepton_id->GetXaxis()->SetBinLabel(7, "\"other\" tau");

  TH1D *h_CR4_dr_gen_reco_secondLep_ee2j = new TH1D("h__secondLep__CR4_dr_gen_reco_secondLep_ee2j", "CR4, #DeltaR(gen secondLep, reco secondLep), ==2 jets", nBins_dr, min_dr, max_dr+eps);
  TH1D *h_CR5_dr_gen_reco_secondLep_ee2j = new TH1D("h__secondLep__CR5_dr_gen_reco_secondLep_ee2j", "CR5, #DeltaR(gen secondLep, reco secondLep), ==2 jets", nBins_dr, min_dr, max_dr+eps);
  TH1D *h_CR6_dr_gen_reco_secondLep_ee2j = new TH1D("h__secondLep__CR6_dr_gen_reco_secondLep_ee2j", "CR6, #DeltaR(gen secondLep, reco secondLep), ==2 jets", nBins_dr, min_dr, max_dr+eps);

  TH1D *h_CR4_dr_gen_reco_secondLep_ee3j = new TH1D("h__secondLep__CR4_dr_gen_reco_secondLep_ee3j", "CR4, #DeltaR(gen secondLep, reco secondLep), ==3 jets", nBins_dr, min_dr, max_dr+eps);
  TH1D *h_CR5_dr_gen_reco_secondLep_ee3j = new TH1D("h__secondLep__CR5_dr_gen_reco_secondLep_ee3j", "CR5, #DeltaR(gen secondLep, reco secondLep), ==3 jets", nBins_dr, min_dr, max_dr+eps);
  TH1D *h_CR6_dr_gen_reco_secondLep_ee3j = new TH1D("h__secondLep__CR6_dr_gen_reco_secondLep_ee3j", "CR6, #DeltaR(gen secondLep, reco secondLep), ==3 jets", nBins_dr, min_dr, max_dr+eps);

  TH1D *h_CR4_dr_gen_reco_secondLep_ge4j = new TH1D("h__secondLep__CR4_dr_gen_reco_secondLep_ge4j", "CR4, #DeltaR(gen secondLep, reco secondLep), >=4 jets", nBins_dr, min_dr, max_dr+eps);
  TH1D *h_CR5_dr_gen_reco_secondLep_ge4j = new TH1D("h__secondLep__CR5_dr_gen_reco_secondLep_ge4j", "CR5, #DeltaR(gen secondLep, reco secondLep), >=4 jets", nBins_dr, min_dr, max_dr+eps);
  TH1D *h_CR6_dr_gen_reco_secondLep_ge4j = new TH1D("h__secondLep__CR6_dr_gen_reco_secondLep_ge4j", "CR6, #DeltaR(gen secondLep, reco secondLep), >=4 jets", nBins_dr, min_dr, max_dr+eps);

  TH1D *h_wgt_btag = new TH1D("h_wgt_btag", "bTag Scale Factor;wgt", 20, 0.0, 2.0);
  TH1D *h_wgt_btag_hf_up = new TH1D("h_wgt_btag_hf_up", "bTag Scale Factor, Heavy Flavour, Up;wgt", 20, 0.0, 2.0);
  TH1D *h_wgt_btag_hf_dn = new TH1D("h_wgt_btag_hf_dn", "bTag Scale Factor, Heavy Flavour, Down;wgt", 20, 0.0, 2.0);
  TH1D *h_wgt_btag_lf_up = new TH1D("h_wgt_btag_lf_up", "bTag Scale Factor, Light Flavour, Up;wgt", 20, 0.0, 2.0);
  TH1D *h_wgt_btag_lf_dn = new TH1D("h_wgt_btag_lf_dn", "bTag Scale Factor, Light Flavour, Down;wgt", 20, 0.0, 2.0);
  
  TH1D *h_wgt_lepSF    = new TH1D("h_wgt_lepSF", "Lepton Scale Factor;wgt", 20, 0.0, 2.0);
  TH1D *h_wgt_lepSF_up = new TH1D("h_wgt_lepSF_up", "Lepton Scale Factor, Up;wgt", 20, 0.0, 2.0);
  TH1D *h_wgt_lepSF_dn = new TH1D("h_wgt_lepSF_dn", "Lepton Scale Factor, Down;wgt", 20, 0.0, 2.0);

  TH1D *h_wgt_topPtSF    = new TH1D("h_wgt_topPtSF", "top pT Scale Factor;wgt", 20, 0.0, 2.0);
  TH1D *h_wgt_topPtSF_up = new TH1D("h_wgt_topPtSF_up", "top pT Scale Factor, Up;wgt", 20, 0.0, 2.0);
  TH1D *h_wgt_topPtSF_dn = new TH1D("h_wgt_topPtSF_dn", "top pT Scale Factor, Down;wgt", 20, 0.0, 2.0);
  

   
  bool isTTbar   = false;
  bool isDYJets  = false;
  bool isWJets   = false;
  bool isSingleT = false;
  bool isWW      = false;
  bool isWZ      = false;
  bool isZZ      = false;
  bool isTTW     = false;
  bool isTTZ     = false;
  bool isTTG     = false;
  bool isTZq     = false;
  bool isTG      = false;
  bool isStop    = false;
  if( output_file.Contains("ttbar") )  isTTbar = true;
  if( output_file.Contains("DYJets") ) isDYJets = true;
  if( output_file.Contains("WJets") )  isWJets = true;
  if( output_file.Contains("_T_") ||
      output_file.Contains("_Tbar_") ) isSingleT = true;
  if( output_file.Contains("WW") )  isWW = true;
  if( output_file.Contains("WZ") )  isWZ = true;
  if( output_file.Contains("ZZ") )  isZZ = true;
  if( output_file.Contains("TTW") )  isTTW = true;
  if( output_file.Contains("TTZ") )  isTTZ = true;
  if( output_file.Contains("TTG") )  isTTG = true;
  if( output_file.Contains("tZq") )  isTZq = true;
  if( output_file.Contains("tG") )  isTG = true;
  if( output_file.Contains("T2tt") ) isStop = true;

  bool isFastsim = false;
  if( output_file.Contains("fastSim")  || 
      output_file.Contains("FSPremix") || 
      output_file.Contains("FastAsympt25ns") ) isFastsim = true;
  
  bool isData=false;
  if( output_file.Contains("data") ) isData=true;

  //
  // Met Filter
  //
  eventFilter metFilterTxt; 
  if(isData){
    cout<<"Loading bad event files ..."<<endl;
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_DoubleEG_csc2015.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_DoubleMuon_csc2015.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_HTMHT_csc2015.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_JetHT_csc2015.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_MET_csc2015.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_MuonEG_csc2015.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_SingleElectron_csc2015.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_SingleMuon_csc2015.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/eventlist_SinglePhoton_csc2015.txt");
    // new lists: supposed to include above but do not always
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/DoubleEG_csc2015.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/DoubleMuon_csc2015.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/HTMHT_csc2015.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/JetHT_csc2015.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/MET_csc2015.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/MuonEG_csc2015.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/SingleElectron_csc2015.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/SingleMuon_csc2015.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/SinglePhoton_csc2015.txt");
    // not all samples have events which failed the ecal SC filter
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/DoubleEG_ecalscn1043093.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/HTMHT_ecalscn1043093.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/JetHT_ecalscn1043093.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/MET_ecalscn1043093.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/SinglePhoton_ecalscn1043093.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/SingleElectron_ecalscn1043093.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/SingleMuon_ecalscn1043093.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/csc2015_Dec01.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/ecalscn1043093_Dec01.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/badResolutionTrack_Jan13.txt");
    metFilterTxt.loadBadEventList("/nfs-6/userdata/mt2utils/muonBadTrack_Jan13.txt");
    cout<<" ... finished!"<<endl;
  }

  
  //
  // Scale Factor Bools
  //
  
  // turn on to apply btag sf to central value
  bool applyBtagSFs  = true;
  bool applyLepSFs   = true;
  bool applyTopPtSFs = true;


  //
  // Event Counters
  //
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if( nEvents >= 0 ) nEventsChain = nEvents;

  //
  // Stop 1 Lepton Selection Cutflow
  //
  unsigned int nEvents_pass_duplicate_removal = 0;
  
  bool doCut_dataFilter = true;
  unsigned int nEvents_pass_dataFilter = 0;
  double nEvents_pass_dataFilter_wgt = 0.0;

  bool doCut_trigger = true;
  unsigned int nEvents_pass_trigger = 0;
  double nEvents_pass_trigger_wgt = 0.0;

  bool doCut_nVtx = true;
  int cut_nVtx = 1;
  unsigned int nEvents_pass_nVtx = 0;
  double nEvents_pass_nVtx_wgt = 0.0;
  
  bool doCut_nGoodLep = true;
  int cut_nGoodLep = 1;
  unsigned int nEvents_pass_nGoodLep = 0;
  double nEvents_pass_nGoodLep_wgt = 0.0;
  
  bool doCut_nSelLep = true;
  int cut_nSelLep = 1;
  unsigned int nEvents_pass_nSelLep = 0;
  double nEvents_pass_nSelLep_wgt = 0.0;
  unsigned int nEvents_pass_nSelLep_isMu = 0;
  double nEvents_pass_nSelLep_isMu_wgt = 0.0;
  unsigned int nEvents_pass_nSelLep_isEle = 0;
  double nEvents_pass_nSelLep_isEle_wgt = 0.0;
  
  bool doCut_invertDiLeptonVeto = true;
  int cut_nVetoLep = 1;
  unsigned int nEvents_pass_diLeptonSel = 0;
  double nEvents_pass_diLeptonSel_wgt = 0.0;

  bool doCut_nJets = true;
  int cut_nJets = 2;
  unsigned int nEvents_pass_nJets = 0;
  double nEvents_pass_nJets_wgt = 0.0;

  bool doCut_nBJets = true; 
  int cut_nBJets = 1;
  unsigned int nEvents_pass_nBJets = 0;
  double nEvents_pass_nBJets_wgt = 0.0;

  bool doCut_met = true;
  double cut_met = 250.0;
  unsigned int nEvents_pass_met = 0;
  double nEvents_pass_met_wgt = 0.0;

  bool doCut_mt = true;
  double cut_mt = 150.0;
  unsigned int nEvents_pass_mtCut = 0;
  double nEvents_pass_mtCut_wgt = 0.0;

  bool doCut_minDPhi = true;
  double cut_minDPhi = 0.8;
  unsigned int nEvents_pass_minDPhi = 0;
  double nEvents_pass_minDPhi_wgt = 0.0;
  
  unsigned int nEvents_pass_baseline = 0;
  double nEvents_pass_baseline_wgt = 0.0;

  unsigned int nEvents_pass_baseline_isMu = 0;
  double nEvents_pass_baseline_isMu_wgt = 0.0;

  unsigned int nEvents_pass_baseline_isEle = 0;
  double nEvents_pass_baseline_isEle_wgt = 0.0;

  unsigned int nEvents_pass_baseline_is_ee0lep = 0;
  double nEvents_pass_baseline_is_ee0lep_wgt = 0;

  unsigned int nEvents_pass_baseline_is_ee1lep = 0;
  double nEvents_pass_baseline_is_ee1lep_wgt = 0;

  unsigned int nEvents_pass_baseline_is_ge2lep = 0;
  double nEvents_pass_baseline_is_ge2lep_wgt = 0;

  unsigned int nEvents_pass_baseline_is_ZtoNuNu = 0;
  double nEvents_pass_baseline_is_ZtoNuNu_wgt = 0;

  unsigned int nEvents_pass_CR4 = 0;
  double nEvents_pass_CR4_wgt = 0.0;
  
  unsigned int nEvents_pass_CR5 = 0;
  double nEvents_pass_CR5_wgt = 0.0;

  unsigned int nEvents_pass_CR6 = 0;
  double nEvents_pass_CR6_wgt = 0.0;

  //
  // Yields for pdf, scale weights
  //
  bool sampleHasGenWgts = false;
    
  const int nClassyCats = nClassifications*nCategories;
  double nominal[nClassyCats];
  double alphasUp[nClassyCats];
  double alphasDn[nClassyCats];
  double q2Up[nClassyCats];
  double q2Dn[nClassyCats];
  double pdfs[nPDFs][nClassyCats];
  for(int iClassyCat=0; iClassyCat<nClassyCats; iClassyCat++){
    nominal[iClassyCat] = 0.0;
    alphasUp[iClassyCat] = 0.0;
    alphasDn[iClassyCat] = 0.0;
    q2Up[iClassyCat] = 0.0;
    q2Dn[iClassyCat] = 0.0;
    for(int iPDF=0; iPDF<nPDFs; iPDF++){
      pdfs[iPDF][iClassyCat] = 0.0;
    }
  }
  
  double nom_incl_yield=0.0;
  double metResUp_yield=0.0;
  double metResDn_yield=0.0;
  double diNuSFUp_yield=0.0;
  double diNuSFDn_yield=0.0;
  

  //
  // Set Up SF files
  //

  // for applying btagging SFs, using Method 1a from the twiki below:
  //   https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagSFMethods#1a_Event_reweighting_using_scale
  //   https://twiki.cern.ch/twiki/pub/CMS/BTagSFMethods/Method1aExampleCode_CSVM.cc.txt
  double weight_btagsf    = 1.0;
  double weight_btagsf_heavy_UP = 1.0;
  double weight_btagsf_heavy_DN = 1.0;
  double weight_btagsf_light_UP = 1.0;
  double weight_btagsf_light_DN = 1.0;
  
  BTagCalibration* calib = NULL;
  BTagCalibrationReader* reader_heavy = NULL;
  BTagCalibrationReader* reader_heavy_UP = NULL;
  BTagCalibrationReader* reader_heavy_DN = NULL;
  BTagCalibrationReader* reader_light = NULL;
  BTagCalibrationReader* reader_light_UP = NULL;
  BTagCalibrationReader* reader_light_DN = NULL;

  TH2D* h_btag_eff_b    = NULL;
  TH2D* h_btag_eff_c    = NULL;
  TH2D* h_btag_eff_udsg = NULL;
  
  BTagCalibration* calib_fastsim = NULL;
  BTagCalibrationReader* reader_fastsim    = NULL;
  BTagCalibrationReader* reader_fastsim_UP = NULL;
  BTagCalibrationReader* reader_fastsim_DN = NULL;

  TH2D* h_btag_eff_b_fastsim    = NULL;
  TH2D* h_btag_eff_c_fastsim    = NULL;
  TH2D* h_btag_eff_udsg_fastsim = NULL;
  if (applyBtagSFs && !isData) {
    // setup btag calibration readers
    calib           = new BTagCalibration("csvv2", "../../CORE/Tools/btagsf/data/run2_25ns/CSVv2.csv"); // 25s version of SFs
    reader_heavy    = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "mujets", "central"); // central, hf
    reader_heavy_UP = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "mujets", "up");      // sys up, hf
    reader_heavy_DN = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "mujets", "down");    // sys down, hf
    reader_light    = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "central");   // central, lf
    reader_light_UP = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "up");        // sys up, lf
    reader_light_DN = new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "down");      // sys down, lf

    // get btag efficiencies
    TFile* f_btag_eff = new TFile("../../CORE/Tools/btagsf/data/run2_25ns/btageff__ttbar_powheg_pythia8_25ns.root");
    TH2D* h_btag_eff_b_temp    = (TH2D*) f_btag_eff->Get("h2_BTaggingEff_csv_med_Eff_b");
    TH2D* h_btag_eff_c_temp    = (TH2D*) f_btag_eff->Get("h2_BTaggingEff_csv_med_Eff_c");
    TH2D* h_btag_eff_udsg_temp = (TH2D*) f_btag_eff->Get("h2_BTaggingEff_csv_med_Eff_udsg");
    out_file->cd();
    h_btag_eff_b = (TH2D*) h_btag_eff_b_temp->Clone("h_btag_eff_b");
    h_btag_eff_c = (TH2D*) h_btag_eff_c_temp->Clone("h_btag_eff_c");
    h_btag_eff_udsg = (TH2D*) h_btag_eff_udsg_temp->Clone("h_btag_eff_udsg");
    f_btag_eff->Close();
    std::cout << "loaded fullsim btag SFs" << std::endl;
    
    // extra copy for fastsim -> fullsim SFs
    if (isFastsim) {
      // setup btag calibration readers
      calib_fastsim = new BTagCalibration("CSV", "../../CORE/Tools/btagsf/data/run2_fastsim/CSV_13TEV_Combined_20_11_2015.csv"); // 25ns fastsim version of SFs
      reader_fastsim = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "central"); // central
      reader_fastsim_UP = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "up");  // sys up
      reader_fastsim_DN = new BTagCalibrationReader(calib_fastsim, BTagEntry::OP_MEDIUM, "fastsim", "down");  // sys down

      // get btag efficiencies
      TFile* f_btag_eff_fastsim = new TFile("../../CORE/Tools/btagsf/data/run2_fastsim/btageff__SMS-T1bbbb-T1qqqq_fastsim.root");
      TH2D* h_btag_eff_b_fastsim_temp = (TH2D*) f_btag_eff_fastsim->Get("h2_BTaggingEff_csv_med_Eff_b");
      TH2D* h_btag_eff_c_fastsim_temp = (TH2D*) f_btag_eff_fastsim->Get("h2_BTaggingEff_csv_med_Eff_c");
      TH2D* h_btag_eff_udsg_fastsim_temp = (TH2D*) f_btag_eff_fastsim->Get("h2_BTaggingEff_csv_med_Eff_udsg");
      out_file->cd();
      h_btag_eff_b_fastsim = (TH2D*) h_btag_eff_b_fastsim_temp->Clone("h_btag_eff_b_fastsim");
      h_btag_eff_c_fastsim = (TH2D*) h_btag_eff_c_fastsim_temp->Clone("h_btag_eff_c_fastsim");
      h_btag_eff_udsg_fastsim = (TH2D*) h_btag_eff_udsg_fastsim_temp->Clone("h_btag_eff_udsg_fastsim");
      f_btag_eff_fastsim->Close();
      
      std::cout << "loaded fastsim btag SFs" << std::endl;
    } // if (isFastsim)
      
  } // end if applyBtagSFs
   

  //
  // Open lepton SF histos
  //
  TFile *f_el_SF;
  TFile *f_mu_SF_sel_id;
  TFile *f_mu_SF_sel_iso;
  TFile *f_mu_SF_veto_id;
  TFile *f_mu_SF_veto_iso;
  
  TH2D *h_el_SF_sel  = NULL;
  TH2D *h_mu_SF_sel  = NULL;
  TH2D *h_el_SF_veto = NULL;
  TH2D *h_mu_SF_veto = NULL;
  
  if(applyLepSFs && !isData){
    
    f_el_SF          = new TFile("lepsf/kinematicBinSFele.root", "read");
    f_mu_SF_sel_id   = new TFile("lepsf/TnP_MuonID_NUM_MediumID_DENOM_generalTracks_VAR_map_pt_eta.root", "read");
    f_mu_SF_sel_iso  = new TFile("lepsf/TnP_MuonID_NUM_MiniIsoTight_DENOM_LooseID_VAR_map_pt_eta.root");
    f_mu_SF_veto_id  = new TFile("lepsf/TnP_MuonID_NUM_LooseID_DENOM_generalTracks_VAR_map_pt_eta.root", "read");
    f_mu_SF_veto_iso = new TFile("lepsf/TnP_MuonID_NUM_MiniIsoTight_DENOM_LooseID_VAR_map_pt_eta.root");
    
    TH2D *h_el_SF_sel_id_temp   = (TH2D*)f_el_SF->Get("CutBasedMedium");
    TH2D *h_el_SF_sel_iso_temp  = (TH2D*)f_el_SF->Get("MiniIso0p1_vs_AbsEta");
    TH2D *h_el_SF_veto_id_temp  = (TH2D*)f_el_SF->Get("CutBasedVeto");
    TH2D *h_el_SF_veto_iso_temp = (TH2D*)f_el_SF->Get("MiniIso0p4_vs_AbsEta");

    TH2D *h_mu_SF_sel_id_temp  = (TH2D*)f_mu_SF_sel_id->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_tag_IsoMu20_pass");
    TH2D *h_mu_SF_sel_iso_temp = (TH2D*)f_mu_SF_sel_iso->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_PF_pass_&_tag_IsoMu20_pass");

    TH2D *h_mu_SF_veto_id_temp  = (TH2D*)f_mu_SF_veto_id->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_tag_IsoMu20_pass");
    TH2D *h_mu_SF_veto_iso_temp = (TH2D*)f_mu_SF_veto_iso->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_PF_pass_&_tag_IsoMu20_pass");

    out_file->cd();

    TH2D *h_el_SF_sel_id   = (TH2D*)h_el_SF_sel_id_temp->Clone("h_el_SF_sel_id");
    TH2D *h_el_SF_sel_iso  = (TH2D*)h_el_SF_sel_iso_temp->Clone("h_el_SF_sel_iso");
    TH2D *h_el_SF_veto_id  = (TH2D*)h_el_SF_veto_id_temp->Clone("h_el_SF_veto_id");
    TH2D *h_el_SF_veto_iso = (TH2D*)h_el_SF_veto_iso_temp->Clone("h_el_SF_veto_iso");

    TH2D *h_mu_SF_sel_id   = (TH2D*)h_mu_SF_sel_id_temp->Clone("h_mu_SF_sel_id");
    TH2D *h_mu_SF_sel_iso  = (TH2D*)h_mu_SF_sel_iso_temp->Clone("h_mu_SF_sel_iso");
    TH2D *h_mu_SF_veto_id  = (TH2D*)h_mu_SF_veto_id_temp->Clone("h_mu_SF_veto_id");
    TH2D *h_mu_SF_veto_iso = (TH2D*)h_mu_SF_veto_iso_temp->Clone("h_mu_SF_veto_iso");

    h_el_SF_sel = (TH2D*)h_el_SF_sel_id->Clone("h_el_SF_sel");
    h_el_SF_sel->Multiply(h_el_SF_sel_iso);
    h_el_SF_veto = (TH2D*)h_el_SF_veto_id->Clone("h_el_SF_veto");
    h_el_SF_veto->Multiply(h_el_SF_veto_iso);

    h_mu_SF_sel = (TH2D*)h_mu_SF_sel_id->Clone("h_mu_SF_sel");
    h_mu_SF_sel->Multiply(h_mu_SF_sel_iso);
    h_mu_SF_veto = (TH2D*)h_mu_SF_veto_id->Clone("h_mu_SF_veto");
    h_mu_SF_veto->Multiply(h_mu_SF_veto_iso);

    f_el_SF->Close();
    f_mu_SF_sel_id->Close();
    f_mu_SF_sel_iso->Close();
    f_mu_SF_veto_id->Close();
    f_mu_SF_veto_iso->Close();
    
  }


  //
  // Event list
  //
  FILE *evtList = NULL;
  if(isData){
    evtList = fopen("eventList__diLepton_CR__data.dat","w");
    fprintf(evtList,"RunNumber  LumiSec  EventNumber  CRid  MET  MET_phi  MT  MINDPHI  MT2W  lep1_pt  lep1_eta  lep1_phi  lep2_pt  lep2_eta  lep2_phi  passTrackIso  passTau  nSelJets  nBJets  jet1Pt  jet2Pt\n");
  }
  

  //
  // Grab list of files
  //
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  //
  // File Loop
  //
  while ( (currentFile = (TFile*)fileIter.Next()) ) {

    //
    // Get File Content
    //
    TFile file( currentFile->GetTitle() );
    TTree *tree = (TTree*)file.Get("t");
    if(fast) TTreeCache::SetLearnEntries(10);
    if(fast) tree->SetCacheSize(128*1024*1024);
    babyAnalyzer.Init(tree);

    bool is_amcnlo = false;
    TString test_amcnlo = currentFile->GetTitle();
    if( test_amcnlo.Contains("amcnlo") ) is_amcnlo = true;
    
    //
    // Get h_counter histogram for inclusive yields
    //
    TH1D *h_counter = (TH1D*)file.Get("h_counter");


    //
    // Loop over Events in current file
    //
    if( nEventsTotal >= nEventsChain ) continue;
    unsigned int nEventsTree = tree->GetEntriesFast();
    for( unsigned int event = 0; event < nEventsTree; ++event) {

      //
      // Get Event Content
      //
      if( nEventsTotal >= nEventsChain ) continue;
      if(fast) tree->LoadTree(event);
      babyAnalyzer.GetEntry(event);
      ++nEventsTotal;

      
      //
      // Progress
      //
      stop_1l_babyAnalyzer::progress( nEventsTotal, nEventsChain );


      //
      // Duplicate Data Event removal
      //
      if( is_data() ) {
	duplicate_removal::DorkyEventIdentifier id(run(), evt(), ls());
        if (is_duplicate(id) ) continue;
      }
      nEvents_pass_duplicate_removal++;

      bool printCutflow=false;
      
      // Events in new file not in old
      /*
      if( (run()==258177 && evt()==1229963834) ||
	  (run()==258745 && evt()==333234362 ) ||
	  (run()==258440 && evt()==678196078 ) ||
	  (run()==259822 && evt()==519082897 ) ||
	  (run()==259891 && evt()==65386853 ) ||
	  (run()==260532 && evt()==446591842) ||
	  (run()==260538 && evt()==319255485) ||
	  (run()==260576 && evt()==12442177) ||
	  (run()==260627 && evt()==1859602873) || 
	  (run()==258158 && evt()==28676567) ||
	  (run()==257968 && evt()==330180769) ||
	  (run()==258158 && evt()==833633757) ||
	  (run()==260424 && evt()==1023117342) ||
	  (run()==258749 && evt()==212856349) ||
	  (run()==259685 && evt()==8353342) ||
	  (run()==260627 && evt()==2885338256)  ) printCutflow=true;
      */
      if( (run()==260627 && evt()==2885338256)  ) printCutflow=true;
      
      //
      // Loop over systematics
      //
      for(int iSys=0; iSys<(int)histos.systematics.size(); iSys++){

	bool isNominal = (k_nominal==histos.systematics[iSys]->id);

	if( !histos.systematics[iSys]->isShapeSys ) continue;


	//
	// Get Event Weight
	//

	double wgt = 1.0;
	//wgt = scale1fb();
	double scale1fb_reCalc = 1000.0*xsec()*kfactor()/h_counter->GetBinContent(22);
	//double scale1fb_reCalc = scale1fb();
	if( is_amcnlo ) scale1fb_reCalc = scale1fb();
	wgt = scale1fb_reCalc;

	double lumi = 2.26; // Run 2012C+D
	//double lumi = 2.11; // Run 2012C+D
	wgt *= lumi;

	wgt *= histos.systematics[iSys]->yieldSF;

	// top pT weighting
	double wgt_topPt = 1.0;
	if(applyTopPtSFs && isTTbar && !is_data()){
	  float genTopPt    = 0.0;
	  float genTopBarPt = 0.0;
	  int nTopsFound = 0;
	  for(int iTop=0; iTop<(int)gents_p4().size(); iTop++){
	    if(!gents_isLastCopy().at(iTop)) continue;
	    if(gents_id().at(iTop)==6){
	      genTopPt = gents_p4().at(iTop).Pt();
	      nTopsFound++;
	    }
	    if(gents_id().at(iTop)==-6){
	      genTopBarPt = gents_p4().at(iTop).Pt();
	      nTopsFound++;
	    }
	  }
	  if( !(genTopPt>0.0) )    cout << "    Did not find gen top for top pT reweighting" << endl;
	  if( !(genTopBarPt>0.0) ) cout << "    Did not find gen topBar for top pT reweighting" << endl;
	  if( nTopsFound!=2 )      cout << "    Did not find 2 tops for top pT reweighting" << endl;

	  wgt_topPt = topPtWeight(genTopPt, genTopBarPt);

	  if(histos.systematics[iSys]->id==k_topPtSFUp) wgt *= wgt_topPt;
	  else if(histos.systematics[iSys]->id==k_topPtSFDown) wgt *= 1.0;
	  else wgt *= 1.0;
	  //else wgt *= wgt_topPt;
	  
	}
	

	//
	// Data wgt always = 1.0
	//
	if( is_data() ) wgt = 1.0;

	
	//
	// Check number of hard process gen leptons
	//
	int nGenPromptNu  = 0;
	int nGenPromptLep = 0;
	if( !is_data() ){
	  nGenPromptLep = genLepsHardProcess();
	  nGenPromptNu  = genNusHardProcess();
	}
      
	vector<int> classy_idx;
	
	// Inclusive selection
	for(int iClassy=0; iClassy<(int)histos.classifications.size(); iClassy++){
	  if( k_incl == histos.classifications[iClassy]->id ) classy_idx.push_back(iClassy);
	}


	// Gen Decay Type Splitting
	bool is_0lep    = false;
	bool is_1lep    = false;
	bool is_2lep    = false;
	bool is_ZtoNuNu = false;
	if( !is_data() ){

	  is_0lep = is0lep();
	  is_1lep = is1lep();
	  is_2lep = is2lep();
	  is_ZtoNuNu = isZtoNuNu();

	  if( is_ZtoNuNu ){
	    for(int iClassy=0; iClassy<(int)histos.classifications.size(); iClassy++){
	      if( k_ZtoNuNu == histos.classifications[iClassy]->id ) classy_idx.push_back(iClassy);
	    }
	  }       
	  else if( is_1lep ){
	    for(int iClassy=0; iClassy<(int)histos.classifications.size(); iClassy++){
	      if( k_ee1lep == histos.classifications[iClassy]->id ) classy_idx.push_back(iClassy);
	    }
	  } 
	  else if( is_2lep ){
	    for(int iClassy=0; iClassy<(int)histos.classifications.size(); iClassy++){
	      if( k_ge2lep == histos.classifications[iClassy]->id ) classy_idx.push_back(iClassy);
	    }
	  } 
	
	
	} // end if !is_data()
      
	
	//
	// Pre-Selection
	//
	if(isNominal && printCutflow) cout << endl << endl << "    Beginning Cutflow for run=" << run() << ", evt=" << evt() << ", ls=" << ls() << endl;
	// Data Filter
	if( doCut_dataFilter && is_data() ){
	  bool filt_badevents = !(metFilterTxt.eventFails(run(), ls(), evt()));
	  if(!filt_badevents) continue;
	  
	  if( !filt_cscbeamhalo() ||
              !filt_eebadsc() ||
              !filt_goodvtx() ||
              !filt_hbhenoise()      ) continue;
	  
	}
	if(isNominal){
	  nEvents_pass_dataFilter++;
	  nEvents_pass_dataFilter_wgt+=wgt;
	}
	if(isNominal && printCutflow) cout << "    Pass Data Filter" << endl;

	// Trigger
	if( doCut_trigger && is_data() ){
	  if(  ( HLT_SingleEl27() + HLT_SingleMu20() + HLT_MET170()) < 1 ) continue;
	}
	if(isNominal){
	  nEvents_pass_trigger++;
	  nEvents_pass_trigger_wgt+=wgt;
	}
	if(isNominal && printCutflow) cout << "    Pass Trigger" << endl;

	// 1 good vertex
	if( doCut_nVtx && nvtxs()<cut_nVtx ) continue;
	if(isNominal){
	  nEvents_pass_nVtx++;
	  nEvents_pass_nVtx_wgt+=wgt;
	}
	if(isNominal && printCutflow) cout << "    Pass Good Vertex" << endl;
	
	// ==1 good lep
	if( doCut_nGoodLep && ngoodleps()<cut_nGoodLep ) continue;
	if(isNominal){
	  nEvents_pass_nGoodLep++;
	  nEvents_pass_nGoodLep_wgt+=wgt;
	}
	if(isNominal && printCutflow) cout << "    Pass at least 1 good lep" << endl;
	
	// ==1 good lep, passing selection
	int nSelLeptons = 0;
	TLorentzVector selLep_TLV(0.0, 0.0, 0.0, 0.0);
	
	//double sel_pt_mu = 30.0;
	//double sel_pt_el = 40.0;
	double sel_pt_mu = 20.0;
	double sel_pt_el = 20.0;
	
	//double sel_eta_mu = 2.1;
	double sel_eta_mu = 2.4;
	//double sel_eta_el = 2.1;
	double sel_eta_el = 1.442;
	
	double sel_miniRelIso_mu = 0.1;
	double sel_miniRelIso_el = 0.1;

	bool lep1_isSel = false;

	TLorentzVector genLep_matchedTo_selLep_TLV(0.0, 0.0, 0.0, 0.0);
	int genLep_matchedTo_selLep_idx = -99;
	bool selLep_isMatched_toGen = false;
	bool selLep_isMatched_toGenTau = false;
	double genLep_matchedTo_selLep_dr = 999.9;

	if(isNominal && printCutflow) cout << "      Selected Lepton Info: lep1 pT=" << lep1_pt() << ", lep1 eta=" << lep1_eta() << ", lep1 phi=" << lep1_phi() <<  endl;
	if( doCut_nSelLep ){
	  
	  if( lep1_is_mu() ){
	    if( lep1_pt()>sel_pt_mu &&
		fabs(lep1_eta())<sel_eta_mu &&
		lep1_is_muoid_tight() &&
		lep1_miniRelIsoEA()<sel_miniRelIso_mu ){
	      nSelLeptons++;
	      selLep_TLV.SetPxPyPzE( lep1_p4().Px(), lep1_p4().Py(), lep1_p4().Pz(), lep1_p4().E() );
	      nEvents_pass_nSelLep_isMu++;
	      nEvents_pass_nSelLep_isMu_wgt+=wgt;
	      lep1_isSel=true;

	      // Match to gen_mu
	      for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++){
		if( !genleps_isLastCopy().at(iGen) ) continue;
		if( abs(genleps_id().at(iGen))!=13 ) continue;
		TLorentzVector gen_TLV(0.0, 0.0, 0.0, 0.0);
		gen_TLV.SetPxPyPzE( genleps_p4().at(iGen).Px(), genleps_p4().at(iGen).Py(), genleps_p4().at(iGen).Pz(), genleps_p4().at(iGen).E() ); 
		if( selLep_TLV.DeltaR(gen_TLV)<genLep_matchedTo_selLep_dr ){
		  genLep_matchedTo_selLep_dr  = selLep_TLV.DeltaR(gen_TLV);
		  genLep_matchedTo_selLep_TLV = gen_TLV;
		  genLep_matchedTo_selLep_idx = genleps__genpsidx().at(iGen);
		  if(genLep_matchedTo_selLep_dr<matched_dr) selLep_isMatched_toGen=true;
		}
	      }
	      
	      // Match to gen_tau
	      if(!selLep_isMatched_toGen){
		for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++){
		  if( !genleps_isLastCopy().at(iGen) ) continue;
		  if( abs(genleps_id().at(iGen))!=15 ) continue;
		  TLorentzVector gen_TLV(0.0, 0.0, 0.0, 0.0);
		  gen_TLV.SetPxPyPzE( genleps_p4().at(iGen).Px(), genleps_p4().at(iGen).Py(), genleps_p4().at(iGen).Pz(), genleps_p4().at(iGen).E() ); 
		  if( selLep_TLV.DeltaR(gen_TLV)<genLep_matchedTo_selLep_dr ){
		    genLep_matchedTo_selLep_dr  = selLep_TLV.DeltaR(gen_TLV);
		    genLep_matchedTo_selLep_TLV = gen_TLV;
		    genLep_matchedTo_selLep_idx = genleps__genpsidx().at(iGen);
		    if(genLep_matchedTo_selLep_dr<matched_dr){
		      selLep_isMatched_toGen=true;
		      selLep_isMatched_toGenTau=true;
		    }

		  }
		}
	      } // end if not matched to muon

	    } // end if good muon
	  }
       
	  if( lep1_is_el() ){
	    if( lep1_pt()>sel_pt_el &&
		fabs(lep1_eta())<sel_eta_el &&
		lep1_passMediumID() &&
		lep1_miniRelIsoEA()<sel_miniRelIso_el ){
	      nSelLeptons++;
	      selLep_TLV.SetPxPyPzE( lep1_p4().Px(), lep1_p4().Py(), lep1_p4().Pz(), lep1_p4().E() );
	      nEvents_pass_nSelLep_isEle++;
	      nEvents_pass_nSelLep_isEle_wgt+=wgt;
	      lep1_isSel=true;

	      // Match to gen_el
	      for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++){
		if( !genleps_isLastCopy().at(iGen) ) continue;
		if( abs(genleps_id().at(iGen))!=11 ) continue;
		TLorentzVector gen_TLV(0.0, 0.0, 0.0, 0.0);
		gen_TLV.SetPxPyPzE( genleps_p4().at(iGen).Px(), genleps_p4().at(iGen).Py(), genleps_p4().at(iGen).Pz(), genleps_p4().at(iGen).E() ); 
		if( selLep_TLV.DeltaR(gen_TLV)<genLep_matchedTo_selLep_dr ){
		  genLep_matchedTo_selLep_dr  = selLep_TLV.DeltaR(gen_TLV);
		  genLep_matchedTo_selLep_TLV = gen_TLV;
		  genLep_matchedTo_selLep_idx = genleps__genpsidx().at(iGen);
		  if(genLep_matchedTo_selLep_dr<matched_dr) selLep_isMatched_toGen=true;
		}
	      }
	      
	      // Match to gen_tau
	      if(!selLep_isMatched_toGen){
		for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++){
		  if( !genleps_isLastCopy().at(iGen) ) continue;
		  if( abs(genleps_id().at(iGen))!=15 ) continue;
		  TLorentzVector gen_TLV(0.0, 0.0, 0.0, 0.0);
		  gen_TLV.SetPxPyPzE( genleps_p4().at(iGen).Px(), genleps_p4().at(iGen).Py(), genleps_p4().at(iGen).Pz(), genleps_p4().at(iGen).E() ); 
		  if( selLep_TLV.DeltaR(gen_TLV)<genLep_matchedTo_selLep_dr ){
		    genLep_matchedTo_selLep_dr  = selLep_TLV.DeltaR(gen_TLV);
		    genLep_matchedTo_selLep_TLV = gen_TLV;
		    genLep_matchedTo_selLep_idx = genleps__genpsidx().at(iGen);
		    if(genLep_matchedTo_selLep_dr<matched_dr){
		      selLep_isMatched_toGen=true;
		      selLep_isMatched_toGenTau=true;
		    }

		  }
		}

	      }

	      
	    } // end if good electron
	  } // end if lep1_isEl


	  if( !lep1_isSel ){

	    if( lep2_is_mu() ){
	      if( lep2_pt()>sel_pt_mu &&
		  fabs(lep2_eta())<sel_eta_mu &&
		  lep2_is_muoid_tight() &&
		  lep2_miniRelIsoEA()<sel_miniRelIso_mu ){
		nSelLeptons++;
		selLep_TLV.SetPxPyPzE( lep2_p4().Px(), lep2_p4().Py(), lep2_p4().Pz(), lep2_p4().E() );
		nEvents_pass_nSelLep_isMu++;
		nEvents_pass_nSelLep_isMu_wgt+=wgt;
		
		// Match to gen_mu
		for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++){
		  if( !genleps_isLastCopy().at(iGen) ) continue;
		  if( abs(genleps_id().at(iGen))!=13 ) continue;
		  TLorentzVector gen_TLV(0.0, 0.0, 0.0, 0.0);
		  gen_TLV.SetPxPyPzE( genleps_p4().at(iGen).Px(), genleps_p4().at(iGen).Py(), genleps_p4().at(iGen).Pz(), genleps_p4().at(iGen).E() ); 
		  if( selLep_TLV.DeltaR(gen_TLV)<genLep_matchedTo_selLep_dr ){
		    genLep_matchedTo_selLep_dr  = selLep_TLV.DeltaR(gen_TLV);
		    genLep_matchedTo_selLep_TLV = gen_TLV;
		    genLep_matchedTo_selLep_idx = genleps__genpsidx().at(iGen);
		    if(genLep_matchedTo_selLep_dr<matched_dr) selLep_isMatched_toGen=true;
		  }
		}
	      
		// Match to gen_tau
		if(!selLep_isMatched_toGen){
		  for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++){
		    if( !genleps_isLastCopy().at(iGen) ) continue;
		    if( abs(genleps_id().at(iGen))!=15 ) continue;
		    TLorentzVector gen_TLV(0.0, 0.0, 0.0, 0.0);
		    gen_TLV.SetPxPyPzE( genleps_p4().at(iGen).Px(), genleps_p4().at(iGen).Py(), genleps_p4().at(iGen).Pz(), genleps_p4().at(iGen).E() ); 
		    if( selLep_TLV.DeltaR(gen_TLV)<genLep_matchedTo_selLep_dr ){
		      genLep_matchedTo_selLep_dr  = selLep_TLV.DeltaR(gen_TLV);
		      genLep_matchedTo_selLep_TLV = gen_TLV;
		      genLep_matchedTo_selLep_idx = genleps__genpsidx().at(iGen);
		      if(genLep_matchedTo_selLep_dr<matched_dr){
			selLep_isMatched_toGen=true;
			selLep_isMatched_toGenTau=true;
		      }

		    }
		  }
		} // end if not matched to muon

	      } // end if good muon
	    }
       
	    if( lep2_is_el() ){
	      if( lep2_pt()>sel_pt_el &&
		  fabs(lep2_eta())<sel_eta_el &&
		  lep2_passMediumID() &&
		  lep2_miniRelIsoEA()<sel_miniRelIso_el ){
		nSelLeptons++;
		selLep_TLV.SetPxPyPzE( lep2_p4().Px(), lep2_p4().Py(), lep2_p4().Pz(), lep2_p4().E() );
		nEvents_pass_nSelLep_isEle++;
		nEvents_pass_nSelLep_isEle_wgt+=wgt;
		
		// Match to gen_el
		for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++){
		  if( !genleps_isLastCopy().at(iGen) ) continue;
		  if( abs(genleps_id().at(iGen))!=11 ) continue;
		  TLorentzVector gen_TLV(0.0, 0.0, 0.0, 0.0);
		  gen_TLV.SetPxPyPzE( genleps_p4().at(iGen).Px(), genleps_p4().at(iGen).Py(), genleps_p4().at(iGen).Pz(), genleps_p4().at(iGen).E() ); 
		  if( selLep_TLV.DeltaR(gen_TLV)<genLep_matchedTo_selLep_dr ){
		    genLep_matchedTo_selLep_dr  = selLep_TLV.DeltaR(gen_TLV);
		    genLep_matchedTo_selLep_TLV = gen_TLV;
		    genLep_matchedTo_selLep_idx = genleps__genpsidx().at(iGen);
		    if(genLep_matchedTo_selLep_dr<matched_dr) selLep_isMatched_toGen=true;
		  }
		}
	      
		// Match to gen_tau
		if(!selLep_isMatched_toGen){
		  for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++){
		    if( !genleps_isLastCopy().at(iGen) ) continue;
		    if( abs(genleps_id().at(iGen))!=15 ) continue;
		    TLorentzVector gen_TLV(0.0, 0.0, 0.0, 0.0);
		    gen_TLV.SetPxPyPzE( genleps_p4().at(iGen).Px(), genleps_p4().at(iGen).Py(), genleps_p4().at(iGen).Pz(), genleps_p4().at(iGen).E() ); 
		    if( selLep_TLV.DeltaR(gen_TLV)<genLep_matchedTo_selLep_dr ){
		      genLep_matchedTo_selLep_dr  = selLep_TLV.DeltaR(gen_TLV);
		      genLep_matchedTo_selLep_TLV = gen_TLV;
		      genLep_matchedTo_selLep_idx = genleps__genpsidx().at(iGen);
		      if(genLep_matchedTo_selLep_dr<matched_dr){
			selLep_isMatched_toGen=true;
			selLep_isMatched_toGenTau=true;
		      }

		    }
		  }

		}

	      
	      } // end if good electron
	    } // end if lep2_isEl


	  } // end if !lep1_isSel

	  if( nSelLeptons != cut_nSelLep ) continue;
	}
	if(isNominal){
	  nEvents_pass_nSelLep++;
	  nEvents_pass_nSelLep_wgt+=wgt;
	}
	if(isNominal && printCutflow) cout << "    Pass lep1 is selected" << endl;
	
	if(is_2lep){
	 
	  h_genLep_matchedTo_selLep_dr->Fill( std::min(genLep_matchedTo_selLep_dr,max_dr), wgt );
	  
	  if( selLep_isMatched_toGen ) h_genLep_matchedTo_selLep_isMatched->Fill( 1.0, wgt );
	  else                         h_genLep_matchedTo_selLep_isMatched->Fill( 0.0, wgt );

	}


	
	// check for and classify the second lepton
	bool isCR4 = false; // 2 selected leptons
	bool isCR5 = false; // 1 selected, 1 veto lepton
	bool isCR6 = false; // 1 selected, isoTrack OR tauHad

	int nVetoLeptons = 0;
	TLorentzVector vetoLep_TLV(0.0, 0.0, 0.0, 0.0);

	//double veto_pt_mu = 5.0;
	//double veto_pt_el = 5.0;
	double veto_pt_mu = 10.0;
	double veto_pt_el = 10.0;
	
	double veto_eta_mu = 2.4;
	double veto_eta_el = 2.4;
	
	double veto_miniRelIso_mu = 0.2;
	double veto_miniRelIso_el = 0.2;

	bool secondLep_isSel  = false;
	bool secondLep_isVeto = false;
		
	if( doCut_invertDiLeptonVeto ){

	  if( lep1_isSel){
	  
	    if( lep2_is_mu() ){

	      if( lep2_pt()>sel_pt_mu &&
		  fabs(lep2_eta())<sel_eta_mu &&
		  lep2_is_muoid_tight() &&
		  lep2_miniRelIsoEA()<sel_miniRelIso_mu ){
		vetoLep_TLV.SetPxPyPzE( lep2_p4().Px(), lep2_p4().Py(), lep2_p4().Pz(), lep2_p4().E() );
		if( selLep_TLV.DeltaR( vetoLep_TLV ) > 0.01 ){
		  nVetoLeptons++;
		  secondLep_isSel = true;
		}
		else vetoLep_TLV.SetPxPyPzE( 0.0, 0.0, 0.0, 0.0 );
	      } // end if good muon
	      else if( lep2_pt()>veto_pt_mu &&
		       fabs(lep2_eta())<veto_eta_mu &&
		       lep2_passVeto() &&
		       lep2_miniRelIsoEA()<veto_miniRelIso_mu ){
		vetoLep_TLV.SetPxPyPzE( lep2_p4().Px(), lep2_p4().Py(), lep2_p4().Pz(), lep2_p4().E() );
		if( selLep_TLV.DeltaR( vetoLep_TLV ) > 0.01 ){
		  nVetoLeptons++;
		  secondLep_isVeto = true;
		}
		else vetoLep_TLV.SetPxPyPzE( 0.0, 0.0, 0.0, 0.0 );
	      } // end if veto muon

	    }
       
	    if( lep2_is_el() ){

	      if( lep2_pt()>sel_pt_el &&
		  fabs(lep2_eta())<sel_eta_el &&
		  lep2_passMediumID() &&
		  lep2_miniRelIsoEA()<sel_miniRelIso_el ){
		vetoLep_TLV.SetPxPyPzE( lep2_p4().Px(), lep2_p4().Py(), lep2_p4().Pz(), lep2_p4().E() );
		if( selLep_TLV.DeltaR( vetoLep_TLV ) > 0.01 ){
		  nVetoLeptons++;
		  secondLep_isSel = true;
		}
		else vetoLep_TLV.SetPxPyPzE( 0.0, 0.0, 0.0, 0.0 );
	      } // end if good electron
	      else if( lep2_pt()>veto_pt_el &&
		       fabs(lep2_eta())<veto_eta_el &&
		       lep2_passVeto() &&
		       lep2_miniRelIsoEA()<veto_miniRelIso_el ){
		vetoLep_TLV.SetPxPyPzE( lep2_p4().Px(), lep2_p4().Py(), lep2_p4().Pz(), lep2_p4().E() );
		if( selLep_TLV.DeltaR( vetoLep_TLV ) > 0.01 ){
		  nVetoLeptons++;
		  secondLep_isVeto = true;
		}
		else vetoLep_TLV.SetPxPyPzE( 0.0, 0.0, 0.0, 0.0 );
	      } // end if veto electron

	    }

	  } // end if lep1_isSel

	  else{
	  
	    if( lep1_is_mu() ){

	      if( lep1_pt()>sel_pt_mu &&
		  fabs(lep1_eta())<sel_eta_mu &&
		  lep1_is_muoid_tight() &&
		  lep1_miniRelIsoEA()<sel_miniRelIso_mu ){
		vetoLep_TLV.SetPxPyPzE( lep1_p4().Px(), lep1_p4().Py(), lep1_p4().Pz(), lep1_p4().E() );
		if( selLep_TLV.DeltaR( vetoLep_TLV ) > 0.01 ){
		  nVetoLeptons++;
		  secondLep_isSel = true;
		}
		else vetoLep_TLV.SetPxPyPzE( 0.0, 0.0, 0.0, 0.0 );
	      } // end if good muon
	      else if( lep1_pt()>veto_pt_mu &&
		       fabs(lep1_eta())<veto_eta_mu &&
		       lep1_passVeto() &&
		       lep1_miniRelIsoEA()<veto_miniRelIso_mu ){
		vetoLep_TLV.SetPxPyPzE( lep1_p4().Px(), lep1_p4().Py(), lep1_p4().Pz(), lep1_p4().E() );
		if( selLep_TLV.DeltaR( vetoLep_TLV ) > 0.01 ){
		  nVetoLeptons++;
		  secondLep_isVeto = true;
		}
		else vetoLep_TLV.SetPxPyPzE( 0.0, 0.0, 0.0, 0.0 );
	      } // end if veto muon

	    }
       
	    if( lep1_is_el() ){

	      if( lep1_pt()>sel_pt_el &&
		  fabs(lep1_eta())<sel_eta_el &&
		  lep1_passMediumID() &&
		  lep1_miniRelIsoEA()<sel_miniRelIso_el ){
		vetoLep_TLV.SetPxPyPzE( lep1_p4().Px(), lep1_p4().Py(), lep1_p4().Pz(), lep1_p4().E() );
		if( selLep_TLV.DeltaR( vetoLep_TLV ) > 0.01 ){
		  nVetoLeptons++;
		  secondLep_isSel = true;
		}
		else vetoLep_TLV.SetPxPyPzE( 0.0, 0.0, 0.0, 0.0 );
	      } // end if good electron
	      else if( lep1_pt()>veto_pt_el &&
		       fabs(lep1_eta())<veto_eta_el &&
		       lep1_passVeto() &&
		       lep1_miniRelIsoEA()<veto_miniRelIso_el ){
		vetoLep_TLV.SetPxPyPzE( lep1_p4().Px(), lep1_p4().Py(), lep1_p4().Pz(), lep1_p4().E() );
		if( selLep_TLV.DeltaR( vetoLep_TLV ) > 0.01 ){
		  nVetoLeptons++;
		  secondLep_isVeto = true;
		}
		else vetoLep_TLV.SetPxPyPzE( 0.0, 0.0, 0.0, 0.0 );
	      } // end if veto electron

	    }

	  } // end if !lep1_isSel

	  if(isNominal && printCutflow) cout << "      SecondLepVeto Info: lep2 pT=" << lep2_pt() << ", lep2 eta=" << lep2_eta() << ", lep2 phi=" << lep2_phi() << ", lep2_miniRelIso=" << lep2_miniRelIsoEA() << ", passTrackVeto=" << PassTrackVeto_v3() << ", PassTauVeto=" << PassTauVeto() << endl;
	  if( nVetoLeptons < cut_nVetoLep &&
	      PassTrackVeto_v3()          &&
	      PassTauVeto()                   ) continue;
	  
	  // Classify Second Lepton
	  if     ( secondLep_isSel        ) isCR4 = true;
	  else if( secondLep_isVeto       ) isCR5 = true;
	  else if( !PassTrackVeto_v3() || 
		   !PassTauVeto()         ) isCR6 = true;
 	  
	}
	if(isNominal && printCutflow) cout << "    Pass Second lepton" << endl;

	if( isCR4 ){
	  for(int iClassy=0; iClassy<(int)histos.classifications.size(); iClassy++){
	    if( k_NCR4 == histos.classifications[iClassy]->id ) classy_idx.push_back(iClassy);
	  }
	}
	if( isCR5 ){
	  for(int iClassy=0; iClassy<(int)histos.classifications.size(); iClassy++){
	    if( k_NCR5 == histos.classifications[iClassy]->id ) classy_idx.push_back(iClassy);
	  }
	}
	if( isCR6 ){
	  for(int iClassy=0; iClassy<(int)histos.classifications.size(); iClassy++){
	    if( k_NCR6 == histos.classifications[iClassy]->id ) classy_idx.push_back(iClassy);
	  }
	}
	

	//
	// Lepton SFs
	//
	double lepSF    = 1.0;
	double lepSF_Up = 1.0;
	double lepSF_Dn = 1.0;
	if(applyLepSFs && !is_data()){

	  float lepSF_pt_cutoff = 100.0;

	  // Lep1 SF
	  if(lep1_is_el()){
	    int binX = h_el_SF_sel->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, lep1_p4().Pt()) );
	    int binY = h_el_SF_sel->GetYaxis()->FindBin( fabs(lep1_p4().Eta()) );
	    lepSF    = h_el_SF_sel->GetBinContent( binX, binY );
	    lepSF_Up = (lepSF + h_el_SF_sel->GetBinError( binX, binY ));
	    lepSF_Dn = (lepSF - h_el_SF_sel->GetBinError( binX, binY ));
	  }
	  if(lep1_is_mu()){
	    int binX = h_mu_SF_sel->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, lep1_p4().Pt()) );
	    int binY = h_mu_SF_sel->GetYaxis()->FindBin( fabs(lep1_p4().Eta()) );
	    lepSF    = h_mu_SF_sel->GetBinContent( binX, binY );
	    lepSF_Up = (lepSF + h_mu_SF_sel->GetBinError( binX, binY ));
	    lepSF_Dn = (lepSF - h_mu_SF_sel->GetBinError( binX, binY ));
	  }

	  // Lep2 SF

	  // if Lep2 is Sel lep
	  if( secondLep_isSel ){
	    if(lep2_is_el()){
	      int binX = h_el_SF_sel->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, lep2_p4().Pt()) );
	      int binY = h_el_SF_sel->GetYaxis()->FindBin( fabs(lep2_p4().Eta()) );
	      lepSF    *= h_el_SF_sel->GetBinContent( binX, binY );
	      lepSF_Up *= (lepSF + h_el_SF_sel->GetBinError( binX, binY ));
	      lepSF_Dn *= (lepSF - h_el_SF_sel->GetBinError( binX, binY ));
	    }
	    if(lep2_is_mu()){
	      int binX = h_mu_SF_sel->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, lep2_p4().Pt()) );
	      int binY = h_mu_SF_sel->GetYaxis()->FindBin( fabs(lep2_p4().Eta()) );
	      lepSF    *= h_mu_SF_sel->GetBinContent( binX, binY );
	      lepSF_Up *= (lepSF + h_mu_SF_sel->GetBinError( binX, binY ));
	      lepSF_Dn *= (lepSF - h_mu_SF_sel->GetBinError( binX, binY ));
	    }
	    
	  } // end if 2nd lep is sel

	  // if 2nd lep is veto
	  if( secondLep_isVeto ){
	    	    
	    if(lep2_is_el()){
	      int binX = h_el_SF_veto->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, lep2_p4().Pt()) );
	      int binY = h_el_SF_veto->GetYaxis()->FindBin( fabs(lep2_p4().Eta()) );
	      lepSF    *= h_el_SF_veto->GetBinContent( binX, binY );
	      lepSF_Up *= (lepSF + h_el_SF_veto->GetBinError( binX, binY ));
	      lepSF_Dn *= (lepSF - h_el_SF_veto->GetBinError( binX, binY ));
	    }
	    if(lep2_is_mu()){
	      int binX = h_mu_SF_veto->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, lep2_p4().Pt()) );
	      int binY = h_mu_SF_veto->GetYaxis()->FindBin( fabs(lep2_p4().Eta()) );
	      lepSF    *= h_mu_SF_veto->GetBinContent( binX, binY );
	      lepSF_Up *= (lepSF + h_mu_SF_veto->GetBinError( binX, binY ));
	      lepSF_Dn *= (lepSF - h_mu_SF_veto->GetBinError( binX, binY ));
	    }

	  } // end if 2nd lep is veto
	    
	  // Apply Weight
	  if(histos.systematics[iSys]->id==k_lepSFUp) wgt *= lepSF_Up;
	  else if(histos.systematics[iSys]->id==k_lepSFDown) wgt *= lepSF_Dn;
	  else wgt *= lepSF;
	  
   	} // end if apply lepSF


	if(isNominal){
	  nEvents_pass_diLeptonSel++;
	  nEvents_pass_diLeptonSel_wgt+=wgt;
	}

	
	// Pass nJet Selection
	int nSelJets = 0;
	int nTagJets = 0;
	double btag_med_wp = 0.890; 
	std::vector<int> selJet_index;
	std::vector<int> tagJet_index;

	float btagprob_data = 1.;
	float btagprob_err_heavy_UP = 0.;
	float btagprob_err_heavy_DN = 0.;
	float btagprob_err_light_UP = 0.;
	float btagprob_err_light_DN = 0.;
	float btagprob_mc = 1.;
	
	if( doCut_nJets ){
	  for( int iJet=0; iJet<(int)ngoodjets(); iJet++){
	    
	    if( ak4pfjets_p4()[iJet].Pt()>30.0 &&
		fabs(ak4pfjets_p4()[iJet].Eta())<2.4 &&
		ak4pfjets_loose_pfid()[iJet] ){
	      nSelJets++;
	      selJet_index.push_back(iJet);
	      
	      int jetFlav = ak4pfjets_parton_flavor()[iJet];
	      float pt_cutoff = std::max(20.,std::min(399.,double(ak4pfjets_pt()[iJet])));
	      TH2D* h(0);
	      int binx=-99;
	      int biny=-99;
	      if( !is_data() && applyBtagSFs ){
		if (abs(jetFlav) == 5) {
		  h = isFastsim ? h_btag_eff_b_fastsim : h_btag_eff_b;
		  // use pt bins up to 600 GeV for b
		  pt_cutoff = std::max(20.,std::min(599.,double(ak4pfjets_pt()[iJet])));
		}
		else if (abs(jetFlav) == 4) {
		  h = isFastsim ? h_btag_eff_c_fastsim : h_btag_eff_c;
		}
		else {
		  h = isFastsim ? h_btag_eff_udsg_fastsim : h_btag_eff_udsg;
		}
		binx = h->GetXaxis()->FindBin(pt_cutoff);
		biny = h->GetYaxis()->FindBin(fabs(ak4pfjets_eta()[iJet]));
	      }

	      if( ak4pfjets_CSV()[iJet] > btag_med_wp ){
		nTagJets++;
		tagJet_index.push_back(iJet);
	     
		// btag SF - not final yet
		if (!is_data() && applyBtagSFs) {
		  
		  //float eff = getBtagEffFromFile(jet_pt[njet], jet_eta[njet], jet_hadronFlavour[njet], isFastsim);
		  float eff =  h->GetBinContent(binx,biny);
		  
		  BTagEntry::JetFlavor     flavor = BTagEntry::FLAV_UDSG;
		  if(abs(jetFlav)==5)      flavor = BTagEntry::FLAV_B;
		  else if(abs(jetFlav)==4) flavor = BTagEntry::FLAV_C;
		  
		  pt_cutoff = std::max(30.,std::min(669.,double(ak4pfjets_pt()[iJet])));
		  float eta_cutoff = std::min(2.39,fabs(double(ak4pfjets_eta()[iJet])));
		  float weight_cent(1.), weight_UP(1.), weight_DN(1.);
		  
		  if (flavor == BTagEntry::FLAV_UDSG) {
		    weight_cent = reader_light->eval(flavor, eta_cutoff, pt_cutoff);
		    weight_UP   = reader_light_UP->eval(flavor, eta_cutoff, pt_cutoff);
		    weight_DN   = reader_light_DN->eval(flavor, eta_cutoff, pt_cutoff);
		  } 
		  else {
		    weight_cent = reader_heavy->eval(flavor, eta_cutoff, pt_cutoff);
		    weight_UP   = reader_heavy_UP->eval(flavor, eta_cutoff, pt_cutoff);
		    weight_DN   = reader_heavy_DN->eval(flavor, eta_cutoff, pt_cutoff);
		  }

		  // extra SF for fastsim
		  if (isFastsim) {
		    weight_cent *= reader_fastsim->eval(flavor, eta_cutoff, pt_cutoff);
		    weight_UP   *= reader_fastsim_UP->eval(flavor, eta_cutoff, pt_cutoff);
		    weight_DN   *= reader_fastsim_DN->eval(flavor, eta_cutoff, pt_cutoff);
		  }

		  btagprob_data *= weight_cent * eff;
		  btagprob_mc   *= eff;
		  float abserr_UP = weight_UP - weight_cent;
		  float abserr_DN = weight_cent - weight_DN;
		  if (flavor == BTagEntry::FLAV_UDSG) {
		    btagprob_err_light_UP += abserr_UP/weight_cent;
		    btagprob_err_light_DN += abserr_DN/weight_cent;
		  } 
		  else {
		    btagprob_err_heavy_UP += abserr_UP/weight_cent;
		    btagprob_err_heavy_DN += abserr_DN/weight_cent;
		  }
		}
		
	      } // end if tagged jet
	      else if (!is_data() && applyBtagSFs) { // fail med btag -- needed for SF event weights
		
		//float eff = getBtagEffFromFile(jet_pt[njet], jet_eta[njet], jet_hadronFlavour[njet], isFastsim);
		float eff =  h->GetBinContent(binx,biny);
		
		BTagEntry::JetFlavor flavor = BTagEntry::FLAV_UDSG;
		if      (abs(jetFlav) == 5) flavor = BTagEntry::FLAV_B;
	        else if (abs(jetFlav) == 4) flavor = BTagEntry::FLAV_C;
	      
		pt_cutoff = std::max(30.,std::min(669.,double(ak4pfjets_pt()[iJet])));
		float eta_cutoff = std::min(2.39,fabs(double(ak4pfjets_eta()[iJet])));
		float weight_cent(1.), weight_UP(1.), weight_DN(1.);
		if (flavor == BTagEntry::FLAV_UDSG) {
		  weight_cent = reader_light->eval(flavor, eta_cutoff, pt_cutoff);
		  weight_UP = reader_light_UP->eval(flavor, eta_cutoff, pt_cutoff);
		  weight_DN = reader_light_DN->eval(flavor, eta_cutoff, pt_cutoff);
		} 
		else {
		  weight_cent = reader_heavy->eval(flavor, eta_cutoff, pt_cutoff);
		  weight_UP = reader_heavy_UP->eval(flavor, eta_cutoff, pt_cutoff);
		  weight_DN = reader_heavy_DN->eval(flavor, eta_cutoff, pt_cutoff);
		}
		// extra SF for fastsim
		if (isFastsim) {
		  weight_cent *= reader_fastsim->eval(flavor, eta_cutoff, pt_cutoff);
		  weight_UP *= reader_fastsim_UP->eval(flavor, eta_cutoff, pt_cutoff);
		  weight_DN *= reader_fastsim_DN->eval(flavor, eta_cutoff, pt_cutoff);
		}
		btagprob_data *= (1. - weight_cent * eff);
		btagprob_mc   *= (1. - eff);
		float abserr_UP = weight_UP - weight_cent;
		float abserr_DN = weight_cent - weight_DN;
		if (flavor == BTagEntry::FLAV_UDSG) {
		  btagprob_err_light_UP += (-eff * abserr_UP)/(1 - eff * weight_cent);
		  btagprob_err_light_DN += (-eff * abserr_DN)/(1 - eff * weight_cent);
		} 
		else {
		  btagprob_err_heavy_UP += (-eff * abserr_UP)/(1 - eff * weight_cent);
		  btagprob_err_heavy_DN += (-eff * abserr_DN)/(1 - eff * weight_cent);
		}
		
		
	      } // fail med btag

	      
	    } // end if selected jet					 
	  } // end loop over good jets
	  
	  if( nSelJets<cut_nJets ) continue;
	}
	
	if (!is_data() && applyBtagSFs) {
	  /*
	  weight_btagsf    = (btagprob_data / btagprob_mc);
          weight_btagsf_heavy_UP = (weight_btagsf + btagprob_err_heavy_UP*weight_btagsf);
          weight_btagsf_light_UP = (weight_btagsf + btagprob_err_light_UP*weight_btagsf);
          weight_btagsf_heavy_DN = (weight_btagsf - btagprob_err_heavy_DN*weight_btagsf);
          weight_btagsf_light_DN = (weight_btagsf - btagprob_err_light_DN*weight_btagsf);       
	  */
	  weight_btagsf    = (btagprob_data / btagprob_mc)*(h_counter->GetBinContent(22)/h_counter->GetBinContent(14));
	  weight_btagsf_heavy_UP = (weight_btagsf + btagprob_err_heavy_UP*weight_btagsf)*(h_counter->GetBinContent(22)/h_counter->GetBinContent(15));
	  weight_btagsf_light_UP = (weight_btagsf + btagprob_err_light_UP*weight_btagsf)*(h_counter->GetBinContent(22)/h_counter->GetBinContent(16));
	  weight_btagsf_heavy_DN = (weight_btagsf - btagprob_err_heavy_DN*weight_btagsf)*(h_counter->GetBinContent(22)/h_counter->GetBinContent(17));
	  weight_btagsf_light_DN = (weight_btagsf - btagprob_err_light_DN*weight_btagsf)*(h_counter->GetBinContent(22)/h_counter->GetBinContent(18));
	  
	  if (histos.systematics[iSys]->id==k_bTagEffHFUp) wgt *= weight_btagsf_heavy_UP;
	  else if(histos.systematics[iSys]->id==k_bTagEffHFDown) wgt *= weight_btagsf_heavy_DN;
	  else if(histos.systematics[iSys]->id==k_bTagEffLFUp) wgt *= weight_btagsf_light_UP;
	  else if(histos.systematics[iSys]->id==k_bTagEffLFDown) wgt *= weight_btagsf_light_DN;
	  else wgt *= weight_btagsf;
	  
	}
	
	// K3, K4 SFs
	double K3     = 1.08;
	//double K3     = 1.10;
	double K3_err = 0.06;
        double K4     = 0.92;
	//double K4     = 0.94;
        double K4_err = 0.06;
	if( isTTbar && is_2lep && nSelJets==3 ){
	  if (histos.systematics[iSys]->id==k_nJetsSFK3Up) wgt *= (K3+K3_err);
	  else if(histos.systematics[iSys]->id==k_nJetsSFK3Down) wgt *= (K3-K3_err);
	  else wgt *= K3;
	}
	if( isTTbar && is_2lep && nSelJets>=4 ){
	  if (histos.systematics[iSys]->id==k_nJetsSFK4Up) wgt *= (K4+K4_err);
	  else if(histos.systematics[iSys]->id==k_nJetsSFK4Down) wgt *= (K4-K4_err);
	  else wgt *= K4;
	}

	
	if(isNominal){
	  nEvents_pass_nJets++;
	  nEvents_pass_nJets_wgt+=wgt;
	}
	if(isNominal && printCutflow) cout << "    Pass nJets" << endl;
	
	// ==1 btag cut
	if( doCut_nBJets && nTagJets<cut_nBJets ) continue;
	if(isNominal){
	  nEvents_pass_nBJets++;
	  nEvents_pass_nBJets_wgt+=wgt;
	}
	if(isNominal && printCutflow) cout << "    Pass nBJets" << endl;
	
	//
	// Baseline Selection
	//
	
	// MET cut
	if( doCut_met && pfmet()<=cut_met ) continue;
	if(isNominal){
	  nEvents_pass_met++;
	  nEvents_pass_met_wgt+=wgt;
	}

	if(isNominal && printCutflow) cout << "    Pass MET" << endl;
	if(isNominal && printCutflow) cout << "         MT=" << mt_met_lep() << endl;

	// MET resolution
	double metResSF     = 1.0;
	double metResSF_err = 0.0;

	if( !is_data() ){

	  if( nSelJets==2 ){
	  
	    if( pfmet()>=250.0 && pfmet()<350.0 ){
	      metResSF     = 1.032;
	      metResSF_err = 0.009;

	      //if     ( histos.systematics[iSys]->id==k_metRes_ee2j_met_250_350_Up )   wgt *= (metResSF + metResSF_err);
	      //else if( histos.systematics[iSys]->id==k_metRes_ee2j_met_250_350_Down ) wgt *= (metResSF - metResSF_err);
	      if     ( histos.systematics[iSys]->id==k_metRes_Up )   wgt *= (metResSF + metResSF_err);
	      else if( histos.systematics[iSys]->id==k_metRes_Down ) wgt *= (metResSF - metResSF_err);
	      else wgt *= metResSF;
	    } // 250<MET<350
	  
	    if( pfmet()>=350.0 ){
	      metResSF     = 0.913;
	      metResSF_err = 0.024;

	      //if     ( histos.systematics[iSys]->id==k_metRes_ee2j_met_350_inf_Up )   wgt *= (metResSF + metResSF_err);
	      //else if( histos.systematics[iSys]->id==k_metRes_ee2j_met_350_inf_Down ) wgt *= (metResSF - metResSF_err);
	      if     ( histos.systematics[iSys]->id==k_metRes_Up )   wgt *= (metResSF + metResSF_err);
	      else if( histos.systematics[iSys]->id==k_metRes_Down ) wgt *= (metResSF - metResSF_err);
	      else wgt *= metResSF;
	    } // MET>350
	  
	  } // end if nSelJets==2

	
	  if( nSelJets==3 ){
	  
	    if( pfmet()>=250.0 && pfmet()<350.0 ){
	      metResSF     = 1.032;
	      metResSF_err = 0.014;

	      //if     ( histos.systematics[iSys]->id==k_metRes_ee3j_met_250_350_Up )   wgt *= (metResSF + metResSF_err);
	      //else if( histos.systematics[iSys]->id==k_metRes_ee3j_met_250_350_Down ) wgt *= (metResSF - metResSF_err);
	      if     ( histos.systematics[iSys]->id==k_metRes_Up )   wgt *= (metResSF + metResSF_err);
	      else if( histos.systematics[iSys]->id==k_metRes_Down ) wgt *= (metResSF - metResSF_err);
	      else wgt *= metResSF;
	    } // 250<MET<350
	  
	  
	    if( pfmet()>=350.0 ){
	      metResSF     = 0.928;
	      metResSF_err = 0.030;

	      //if     ( histos.systematics[iSys]->id==k_metRes_ee3j_met_350_inf_Up )   wgt *= (metResSF + metResSF_err);
	      //else if( histos.systematics[iSys]->id==k_metRes_ee3j_met_350_inf_Down ) wgt *= (metResSF - metResSF_err);
	      if     ( histos.systematics[iSys]->id==k_metRes_Up )   wgt *= (metResSF + metResSF_err);
	      else if( histos.systematics[iSys]->id==k_metRes_Down ) wgt *= (metResSF - metResSF_err);
	      else wgt *= metResSF;
	    } // MET>350

	  } // end if nSelJets==3

	
	  if( nSelJets >= 4 ){

	    if( MT2W()<200.0){

	      if( pfmet()>=250.0 && pfmet()<325.0 ){
		metResSF     = 1.048;
		metResSF_err = 0.025;

		//if     ( histos.systematics[iSys]->id==k_metRes_ge4j_lt200mt2w_met_250_325_Up )   wgt *= (metResSF + metResSF_err);
		//else if( histos.systematics[iSys]->id==k_metRes_ge4j_lt200mt2w_met_250_325_Down ) wgt *= (metResSF - metResSF_err);
		if     ( histos.systematics[iSys]->id==k_metRes_Up )   wgt *= (metResSF + metResSF_err);
		else if( histos.systematics[iSys]->id==k_metRes_Down ) wgt *= (metResSF - metResSF_err);
		else wgt *= metResSF;
	      } // 250<MET<325

	      if( pfmet()>=325.0 ){
		metResSF     = 0.944;
		metResSF_err = 0.029;

		//if     ( histos.systematics[iSys]->id==k_metRes_ge4j_lt200mt2w_met_325_inf_Up )   wgt *= (metResSF + metResSF_err);
		//else if( histos.systematics[iSys]->id==k_metRes_ge4j_lt200mt2w_met_325_inf_Down ) wgt *= (metResSF - metResSF_err);
		if     ( histos.systematics[iSys]->id==k_metRes_Up )   wgt *= (metResSF + metResSF_err);
		else if( histos.systematics[iSys]->id==k_metRes_Down ) wgt *= (metResSF - metResSF_err);
		else wgt *= metResSF;
	      } // MET>325
 
	    }  // end if MT2W<200

	    else{

	      if( pfmet()>=250.0 && pfmet()<350.0 ){
		metResSF     = 1.050;
		metResSF_err = 0.021;
	      
		//if     ( histos.systematics[iSys]->id==k_metRes_ge4j_ge200mt2w_met_250_350_Up )   wgt *= (metResSF + metResSF_err);
		//else if( histos.systematics[iSys]->id==k_metRes_ge4j_ge200mt2w_met_250_350_Down ) wgt *= (metResSF - metResSF_err);
		if     ( histos.systematics[iSys]->id==k_metRes_Up )   wgt *= (metResSF + metResSF_err);
		else if( histos.systematics[iSys]->id==k_metRes_Down ) wgt *= (metResSF - metResSF_err);
		else wgt *= metResSF;
	      } // 250<MET<350
	  
	      if( pfmet()>=350.0 && pfmet()<450.0 ){
		metResSF     = 0.910;
		metResSF_err = 0.051;
	      
		//if     ( histos.systematics[iSys]->id==k_metRes_ge4j_ge200mt2w_met_350_450_Up )   wgt *= (metResSF + metResSF_err);
		//else if( histos.systematics[iSys]->id==k_metRes_ge4j_ge200mt2w_met_350_450_Down ) wgt *= (metResSF - metResSF_err);
		if     ( histos.systematics[iSys]->id==k_metRes_Up )   wgt *= (metResSF + metResSF_err);
		else if( histos.systematics[iSys]->id==k_metRes_Down ) wgt *= (metResSF - metResSF_err);
		else wgt *= metResSF;
	      } // 350<MET<450
	  
	  
	      if( pfmet()>=450.0 ){
		metResSF     = 0.924;
		metResSF_err = 0.063;

		//if     ( histos.systematics[iSys]->id==k_metRes_ge4j_ge200mt2w_met_450_inf_Up )   wgt *= (metResSF + metResSF_err);
		//else if( histos.systematics[iSys]->id==k_metRes_ge4j_ge200mt2w_met_450_inf_Down ) wgt *= (metResSF - metResSF_err);
		if     ( histos.systematics[iSys]->id==k_metRes_Up )   wgt *= (metResSF + metResSF_err);
		else if( histos.systematics[iSys]->id==k_metRes_Down ) wgt *= (metResSF - metResSF_err);
		else wgt *= metResSF;
	      } // MET>450
	    	    
	    } // end if MT2W>=200

	  } // end if nSelJets>=4

	} // end if not data


	//
	// diNuetrino SFs
	//
	double diNuSF     = 1.0;
	double diNuSF_err = 0.0;
	
	if( !is_data() && isTTbar && is_2lep ){
	 
	  if( pfmet()>=250.0 && pfmet()<350.0 ){
	    //diNuSF     = 1.04981;   // from fit
	    //diNuSF_err = 0.0622787; // from fit
	    diNuSF     = 1.054;  // from binned
	    diNuSF_err = 0.043;  // from binned
	    
	    //if     ( histos.systematics[iSys]->id==k_diNuSF_met_250_350_Up )   wgt *= (diNuSF + diNuSF_err);
	    //else if( histos.systematics[iSys]->id==k_diNuSF_met_250_350_Down ) wgt *= (diNuSF - diNuSF_err);
	    if     ( histos.systematics[iSys]->id==k_diNuSF_Up )   wgt *= (diNuSF + diNuSF_err);
	    else if( histos.systematics[iSys]->id==k_diNuSF_Down ) wgt *= (diNuSF - diNuSF_err);
	    else wgt *= diNuSF;

	  } // 250<MET<350
	
	  if( pfmet()>=350.0 && pfmet()<450.0 ){
	    //diNuSF     = 0.897238; // from fit
	    //diNuSF_err = 0.114122; // from fit
	    diNuSF     = 0.947;  // from binned
	    diNuSF_err = 0.201;  // from binned
	    
	    //if     ( histos.systematics[iSys]->id==k_diNuSF_met_350_450_Up )   wgt *= (diNuSF + diNuSF_err);
	    //else if( histos.systematics[iSys]->id==k_diNuSF_met_350_450_Down ) wgt *= (diNuSF - diNuSF_err);
	    if     ( histos.systematics[iSys]->id==k_diNuSF_Up )   wgt *= (diNuSF + diNuSF_err);
	    else if( histos.systematics[iSys]->id==k_diNuSF_Down ) wgt *= (diNuSF - diNuSF_err);
	    else wgt *= diNuSF;

	  } // 350<MET<450
	
	  if( pfmet()>=450.0 ){
	    //diNuSF     = 0.744662; // from fit
	    //diNuSF_err = 0.169365; // from fit
	    diNuSF     = 0.729;  // from binned
	    diNuSF_err = 0.320;  // from binned
	    
	    //if     ( histos.systematics[iSys]->id==k_diNuSF_met_450_inf_Up )   wgt *= (diNuSF + diNuSF_err);
	    //else if( histos.systematics[iSys]->id==k_diNuSF_met_450_inf_Down ) wgt *= (diNuSF - diNuSF_err);
	    if     ( histos.systematics[iSys]->id==k_diNuSF_Up )   wgt *= (diNuSF + diNuSF_err);
	    else if( histos.systematics[iSys]->id==k_diNuSF_Down ) wgt *= (diNuSF - diNuSF_err);
	    else wgt *= diNuSF;

	  } // MET>450
	  
	} // end if not data


	if(!is_data()){
	  if( histos.systematics[iSys]->id==k_metRes_Up ) metResUp_yield+=scale1fb_reCalc*(metResSF + metResSF_err);
	  if( histos.systematics[iSys]->id==k_metRes_Down ) metResDn_yield+=scale1fb_reCalc*(metResSF - metResSF_err);
	  if( histos.systematics[iSys]->id==k_diNuSF_Up ) diNuSFUp_yield+=scale1fb_reCalc*(diNuSF + diNuSF_err);
	  if( histos.systematics[iSys]->id==k_diNuSF_Down ) diNuSFDn_yield+=scale1fb_reCalc*(diNuSF - diNuSF_err);
	  if( histos.systematics[iSys]->id==k_nominal ) nom_incl_yield+=scale1fb_reCalc;
	}
	

	// MT cut
	if( doCut_mt && mt_met_lep()<=cut_mt ) continue;
	if(isNominal){
	  nEvents_pass_mtCut++;
	  nEvents_pass_mtCut_wgt+=wgt;
	}
	if(isNominal && printCutflow) cout << "    Pass MT" << endl;
	if(isNominal && printCutflow) cout << "        minDPhi=" << mindphi_met_j1_j2() << endl;
	// minDPhi(met, j1/j2) cut
	if( doCut_minDPhi && mindphi_met_j1_j2()<=cut_minDPhi ) continue;
	if(isNominal){
	  nEvents_pass_minDPhi++;
	  nEvents_pass_minDPhi_wgt+=wgt;
	}
	if(isNominal && printCutflow) cout << "    Pass minDPhi" << endl;
	//
	// This completes the baseline selection
	//
	
	if(isNominal){
	  nEvents_pass_baseline++;
	  nEvents_pass_baseline_wgt+=wgt;
       	
	  if( lep1_is_mu() ){
	    nEvents_pass_baseline_isMu++;
	    nEvents_pass_baseline_isMu_wgt+=wgt;
	  }
	  if( lep1_is_el() ){
	    nEvents_pass_baseline_isEle++;
	    nEvents_pass_baseline_isEle_wgt+=wgt;
	  }

	  if( is_ZtoNuNu ){
	      nEvents_pass_baseline_is_ZtoNuNu++;
	      nEvents_pass_baseline_is_ZtoNuNu_wgt+=wgt;
	  }
	  else if( is_0lep ){
	    nEvents_pass_baseline_is_ee0lep++;
	    nEvents_pass_baseline_is_ee0lep_wgt+=wgt;
	  }
	  else if( is_1lep ){
	    nEvents_pass_baseline_is_ee1lep++;
	    nEvents_pass_baseline_is_ee1lep_wgt+=wgt;
	  }
	  else if( is_2lep ){
	    nEvents_pass_baseline_is_ge2lep++;
	    nEvents_pass_baseline_is_ge2lep_wgt+=wgt;
	  }

	  if(nSelJets>=3){
	    if(isCR4){
	      nEvents_pass_CR4++;
	      nEvents_pass_CR4_wgt+=wgt;
	    }
	    if(isCR5){
	      nEvents_pass_CR5++;
	      nEvents_pass_CR5_wgt+=wgt;
	    }
	    if(isCR6){
	      nEvents_pass_CR6++;
	      nEvents_pass_CR6_wgt+=wgt;
	    }
	  }

	}


	//
	// Fill weights histos
	//

	// top pT 
	if( applyTopPtSFs && !is_data() ){
	  if(histos.systematics[iSys]->id==k_topPtSFUp) h_wgt_topPtSF_up->Fill( 2*wgt_topPt, 1.0 );
	  else if(histos.systematics[iSys]->id==k_topPtSFDown) h_wgt_topPtSF_dn->Fill( 1.0, 1.0 );
	  else h_wgt_topPtSF->Fill( wgt_topPt, 1.0 );
	}

	// lep SF
	if( applyLepSFs && !is_data() ){
	  if(histos.systematics[iSys]->id==k_lepSFUp) h_wgt_lepSF_up->Fill( lepSF_Up, 1.0 );
	  else if(histos.systematics[iSys]->id==k_lepSFDown) h_wgt_lepSF_dn->Fill( lepSF_Dn, 1.0 );
	  else h_wgt_lepSF->Fill( lepSF, 1.0 );
 	}

	// bTag SF
	if( applyBtagSFs && !is_data() ){
	  if (histos.systematics[iSys]->id==k_bTagEffHFUp) h_wgt_btag_hf_up->Fill( weight_btagsf_heavy_UP, 1.0 );
	  else if(histos.systematics[iSys]->id==k_bTagEffHFDown) h_wgt_btag_hf_dn->Fill( weight_btagsf_heavy_DN, 1.0 );
	  else if(histos.systematics[iSys]->id==k_bTagEffLFUp) h_wgt_btag_lf_up->Fill( weight_btagsf_light_UP, 1.0 );
	  else if(histos.systematics[iSys]->id==k_bTagEffLFDown) h_wgt_btag_lf_dn->Fill( weight_btagsf_light_DN, 1.0 );
	  else h_wgt_btag->Fill( weight_btagsf, 1.0 );
	}


	
	// If is_2lep event, then find second gen lepton
	TLorentzVector genSecondLep_TLV(0.0, 0.0, 0.0, 0.0);
	int genSecondLep_idx = -99;
	int genSecondLep_pdgId = -99;
	int nFound_genSecondLep = 0;
	bool genSecondLep_isMatched = false;

	bool genSecondLep_isMatched_toTau = false;
	int genSecondLep_isMatched_toTau_decayType = -99;
	if(is_2lep){

	  // Check electrons and muons
	  for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++){
	    if( !genleps_fromHardProcessFinalState().at(iGen) ) continue;
	    if( !genleps_isLastCopy().at(iGen) ) continue;
	    if( abs(genleps_id().at(iGen))!=11 && abs(genleps_id().at(iGen))!=13  ) continue;
	    if( genleps__genpsidx().at(iGen)==genLep_matchedTo_selLep_idx ) continue;
	    TLorentzVector gen_TLV(0.0, 0.0, 0.0, 0.0);
	    gen_TLV.SetPxPyPzE( genleps_p4().at(iGen).Px(), genleps_p4().at(iGen).Py(), genleps_p4().at(iGen).Pz(), genleps_p4().at(iGen).E() );

	    genSecondLep_idx = genleps__genpsidx().at(iGen);
	    genSecondLep_TLV = gen_TLV;
	    genSecondLep_pdgId = genleps_id().at(iGen);
	    genSecondLep_isMatched = true;
	    nFound_genSecondLep++;
	  }

	  // Check taus
	  if(!genSecondLep_isMatched){
	    for(int iGen=0; iGen<(int)genleps_p4().size(); iGen++){
	      if( !genleps_fromHardProcessDecayed().at(iGen) ) continue;
	      if( !genleps_isLastCopy().at(iGen) ) continue;
	      if( abs(genleps_id().at(iGen))!=15 ) continue;
	      if( genleps__genpsidx().at(iGen)==genLep_matchedTo_selLep_idx ) continue;
	      TLorentzVector gen_TLV(0.0, 0.0, 0.0, 0.0);
	      gen_TLV.SetPxPyPzE( genleps_p4().at(iGen).Px(), genleps_p4().at(iGen).Py(), genleps_p4().at(iGen).Pz(), genleps_p4().at(iGen).E() );

	      genSecondLep_idx = genleps__genpsidx().at(iGen);
	      genSecondLep_TLV = gen_TLV;
	      genSecondLep_pdgId = genleps_id().at(iGen);
	      genSecondLep_isMatched_toTau_decayType = genleps_gentaudecay().at(iGen);
	      genSecondLep_isMatched = true;
	      genSecondLep_isMatched_toTau = true;
	      nFound_genSecondLep++;
	    }
	  }

	  h_nFound_secondLeptons->Fill(nFound_genSecondLep, wgt);

	  if(genSecondLep_isMatched){
	    if(abs(genSecondLep_pdgId)==11) h_gen_secondLepton_id->Fill("ele", wgt);
	    if(abs(genSecondLep_pdgId)==13) h_gen_secondLepton_id->Fill("mu", wgt);
	    if(abs(genSecondLep_pdgId)==15){
	      if(genSecondLep_isMatched_toTau_decayType==1) h_gen_secondLepton_id->Fill("lep tau, ele", wgt);
	      if(genSecondLep_isMatched_toTau_decayType==2) h_gen_secondLepton_id->Fill("lep tau, mu", wgt);
	      if(genSecondLep_isMatched_toTau_decayType==3) h_gen_secondLepton_id->Fill("had tau, 1 prong", wgt);
	      if(genSecondLep_isMatched_toTau_decayType==4) h_gen_secondLepton_id->Fill("had tau, 3 prong", wgt);
	      if(genSecondLep_isMatched_toTau_decayType==5) h_gen_secondLepton_id->Fill("\"other\" tau", wgt);
	    }
	  }


	  if(isCR4){
	    if( nSelJets==2 ) h_CR4_dr_gen_reco_secondLep_ee2j->Fill( std::min( genSecondLep_TLV.DeltaR( vetoLep_TLV ), max_dr ), wgt );
	    if( nSelJets==3 ) h_CR4_dr_gen_reco_secondLep_ee3j->Fill( std::min( genSecondLep_TLV.DeltaR( vetoLep_TLV ), max_dr ), wgt );
	    if( nSelJets>=4 ) h_CR4_dr_gen_reco_secondLep_ge4j->Fill( std::min( genSecondLep_TLV.DeltaR( vetoLep_TLV ), max_dr ), wgt );
	  }
	  if(isCR5){
	    if( nSelJets==2) h_CR5_dr_gen_reco_secondLep_ee2j->Fill( std::min( genSecondLep_TLV.DeltaR( vetoLep_TLV ), max_dr ), wgt );
	    if( nSelJets==3) h_CR5_dr_gen_reco_secondLep_ee3j->Fill( std::min( genSecondLep_TLV.DeltaR( vetoLep_TLV ), max_dr ), wgt );
	    if( nSelJets>=4) h_CR5_dr_gen_reco_secondLep_ge4j->Fill( std::min( genSecondLep_TLV.DeltaR( vetoLep_TLV ), max_dr ), wgt );
	  }
	  if(isCR6){
	    if(!PassTrackVeto_v3()){
	      double minDr=99.9;
	      for(int iTrk=0; iTrk<(int)isoTracks_p4().size(); iTrk++){
		if(!isoTracks_isVetoTrack_v3().at(iTrk)) continue;
		TLorentzVector isoTrk_TLV(0.0, 0.0, 0.0, 0.0);
		isoTrk_TLV.SetPxPyPzE( isoTracks_p4().at(iTrk).Px(), isoTracks_p4().at(iTrk).Py(), isoTracks_p4().at(iTrk).Pz(), isoTracks_p4().at(iTrk).E() );
		if(genSecondLep_TLV.DeltaR( isoTrk_TLV )<minDr) minDr=genSecondLep_TLV.DeltaR( isoTrk_TLV );
	      }
	      if( nSelJets==2 ) h_CR6_dr_gen_reco_secondLep_ee2j->Fill( std::min( minDr, max_dr ), wgt );
	      if( nSelJets==3 ) h_CR6_dr_gen_reco_secondLep_ee3j->Fill( std::min( minDr, max_dr ), wgt );
	      if( nSelJets>=4 ) h_CR6_dr_gen_reco_secondLep_ge4j->Fill( std::min( minDr, max_dr ), wgt );
	    }
	    else{
	      double minDr=99.9;
	      for(int iTau=0; iTau<(int)tau_p4().size(); iTau++){
		if(!tau_isVetoTau().at(iTau)) continue;
		TLorentzVector tau_TLV(0.0, 0.0, 0.0, 0.0);
		tau_TLV.SetPxPyPzE( tau_p4().at(iTau).Px(), tau_p4().at(iTau).Py(), tau_p4().at(iTau).Pz(), tau_p4().at(iTau).E() );
		if(genSecondLep_TLV.DeltaR( tau_TLV )<minDr ) minDr=genSecondLep_TLV.DeltaR( tau_TLV );
	      }
	      if( nSelJets==2 ) h_CR6_dr_gen_reco_secondLep_ee2j->Fill( std::min( minDr, max_dr ), wgt );
	      if( nSelJets==3 ) h_CR6_dr_gen_reco_secondLep_ee3j->Fill( std::min( minDr, max_dr ), wgt );
	      if( nSelJets>=4 ) h_CR6_dr_gen_reco_secondLep_ge4j->Fill( std::min( minDr, max_dr ), wgt );
	      
	    } // end if is tau

	  } // end if isCR6


	} // end if is_2lep

	
	if(isData && isNominal && ( (nSelJets>=3) || (nSelJets==2 && topnessMod()>6.4) ) ){
	  if(isCR4) fprintf(evtList,"run=%d  ls=%d  evt=%d  CR=%d  met=%f  metPhi=%f  mt=%f  minDphi=%f  MT2W=%f  lep1Pt=%f  lep1Eta=%f  lep1Phi=%f  lep2Pt=%f  lep2Eta=%f  lep2Phi=%f  PassTrkVeto=%d  PassTauVeto=%d  nJets=%d  nBTags=%d  jet1Pt=%f  jet2Pt=%f \n", run(), ls(), evt(), 4, pfmet(), pfmet_phi(), mt_met_lep(), mindphi_met_j1_j2(), MT2W(), lep1_p4().Pt(), lep1_p4().Eta(), lep1_p4().Phi(), lep2_p4().Pt(), lep2_p4().Eta(), lep2_p4().Phi(), PassTrackVeto_v3(), PassTauVeto(), nSelJets, nTagJets, ak4pfjets_pt()[selJet_index[0]], ak4pfjets_pt()[selJet_index[1]]); 

	  if(isCR5) fprintf(evtList,"run=%d  ls=%d  evt=%d  CR=%d  met=%f  metPhi=%f  mt=%f  minDphi=%f  MT2W=%f  lep1Pt=%f  lep1Eta=%f  lep1Phi=%f  lep2Pt=%f  lep2Eta=%f  lep2Phi=%f  PassTrkVeto=%d  PassTauVeto=%d  nJets=%d  nBTags=%d  jet1Pt=%f  jet2Pt=%f \n", run(), ls(), evt(), 5, pfmet(), pfmet_phi(), mt_met_lep(), mindphi_met_j1_j2(), MT2W(), lep1_p4().Pt(), lep1_p4().Eta(), lep1_p4().Phi(), lep2_p4().Pt(), lep2_p4().Eta(), lep2_p4().Phi(), PassTrackVeto_v3(), PassTauVeto(), nSelJets, nTagJets, ak4pfjets_pt()[selJet_index[0]], ak4pfjets_pt()[selJet_index[1]]); 
	  
	  if(isCR6) fprintf(evtList,"run=%d  ls=%d  evt=%d  CR=%d  met=%f  metPhi=%f  mt=%f  minDphi=%f  MT2W=%f  lep1Pt=%f  lep1Eta=%f  lep1Phi=%f  lep2Pt=%f  lep2Eta=%f  lep2Phi=%f  PassTrkVeto=%d  PassTauVeto=%d  nJets=%d  nBTags=%d  jet1Pt=%f  jet2Pt=%f \n", run(), ls(), evt(), 6, pfmet(), pfmet_phi(), mt_met_lep(), mindphi_met_j1_j2(), MT2W(), lep1_p4().Pt(), lep1_p4().Eta(), lep1_p4().Phi(), lep2_p4().Pt(), lep2_p4().Eta(), lep2_p4().Phi(), PassTrackVeto_v3(), PassTauVeto(), nSelJets, nTagJets, ak4pfjets_pt()[selJet_index[0]], ak4pfjets_pt()[selJet_index[1]]); 

	  
	}

	//
	// Determine Signal Region Category
	//
	std::vector<int> cat_idx;
	
	// Baseline
	for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  if(k_baseline == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	}

	// Other categories
	if( pfmet() >= 250 ){

	  // ==2 jets
	  if( nSelJets == 2 ){

	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      if(k_ee2j_ge250met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }

	    if( topnessMod()>=6.4 ){
	      for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	       if(k_ee2j_ge250met_ge6p4modTop == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	      } 
	    }

	  } // end if ==2 jets


	  // ==2 jets
	  if( nSelJets >= 2 ){
	    
	    if( topnessMod()>=6.4 ){
	      for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	       if(k_ge2j_ge250met_ge6p4modTop == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	      } 
	    }

	  } // end if >=2 jets


	  // ==3 jets
	  if( nSelJets == 3 ){

	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      if(k_ee3j_ge250met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }

	  } // end if ==3 jets

	  if( nSelJets >= 3 ){

	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      if(k_ge3j_ge250met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }

	    if( pfmet()>=250 && pfmet()<275 ){
	      for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
		if(k_ge3j_met_250_275 == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	      }
	    }
	    
	    if( pfmet()>=275 && pfmet()<325 ){
	      for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
		if(k_ge3j_met_275_325 == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	      }
	    }
	    
	    if( pfmet()>=325 ){
	      for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
		if(k_ge3j_met_325_inf == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	      }
	    }
	    
	    if( MT2W()>=200 ){
	      for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
		if(k_ge3j_ge250met_ge200mt2w == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	      }
	    }
	    if( MT2W()<200 ){
	      for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
		if(k_ge3j_ge250met_lt200mt2w == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	      }
	    }
	    
	    
	  } // end if >=3j
	  
     

	  // >=4 jets
	  if( nSelJets >= 4 ){

	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      if(k_ge4j_ge250met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }

	  } // end if >=4 jets

	  
	  
	} // end if MET>=250


		
	
	//
	// Compute any values for histos, on the fly
	//

	
	//
	// Fill Histos
	//
	for(int iClassy=0; iClassy<(int)classy_idx.size(); iClassy++){
	  for(int iCat=0; iCat<(int)cat_idx.size(); iCat++){

	    int hist_idx = classy_idx[iClassy]*nSystematics*nCategories;
	    hist_idx += iSys*nCategories;
	    hist_idx += cat_idx[iCat];

	    int classyCat_idx = classy_idx[iClassy]*nCategories + cat_idx[iCat];

	    histos.var_yield->histo_[hist_idx]->Fill( 1.0, wgt );

	    /*
	    if( !is_data() ){
	      histos.var_yield_noSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi );
	    }
	    
	    if( applyBtagSFs && !is_data() ){
	      if (histos.systematics[iSys]->id==k_bTagEffHFUp) histos.var_yield_only_bTagSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi*weight_btagsf_heavy_UP );
	      else if(histos.systematics[iSys]->id==k_bTagEffHFDown) histos.var_yield_only_bTagSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi*weight_btagsf_heavy_DN );
	      else if(histos.systematics[iSys]->id==k_bTagEffLFUp) histos.var_yield_only_bTagSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi*weight_btagsf_light_UP );
	      else if(histos.systematics[iSys]->id==k_bTagEffLFDown) histos.var_yield_only_bTagSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi*weight_btagsf_light_DN );
	      else histos.var_yield_only_bTagSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi*weight_btagsf );
	    }
	    

	    if( applyLepSFs && !is_data() ){
	      if(histos.systematics[iSys]->id==k_lepSFUp) histos.var_yield_only_lepSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi*lepSF_Up );
	      else if(histos.systematics[iSys]->id==k_lepSFDown) histos.var_yield_only_lepSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi*lepSF_Dn );
	      else histos.var_yield_only_lepSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi*lepSF );
	    }

	    
	    if( applyTopPtSFs && !is_data() ){
	      if(histos.systematics[iSys]->id==k_topPtSFUp) histos.var_yield_only_topPtSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi*wgt_topPt );
	      else if(histos.systematics[iSys]->id==k_topPtSFDown) histos.var_yield_only_topPtSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi*1.0 );
	      else histos.var_yield_only_topPtSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi*wgt_topPt );
	    }
	    */

	    if( !isNominal ) continue;
	    
	    if( !is_data() ){
	      if( stop_1l::genweights().size()>110 && 
		  h_counter->GetBinContent(1)>0 &&
		  h_counter->GetBinContent(12)>0 &&
		  h_counter->GetBinContent(13)>0 &&
		  h_counter->GetBinContent(5)>0 && 
		  h_counter->GetBinContent(9)>0     ){
		
		
		sampleHasGenWgts = true;

		// Nominal
		nominal[classyCat_idx] += stop_1l::genweights().at(0)*scale1fb_reCalc*lumi/h_counter->GetBinContent(1);
		// AlphaS
		alphasUp[classyCat_idx] += stop_1l::genweights().at(109)*scale1fb_reCalc*lumi/h_counter->GetBinContent(12);
		alphasDn[classyCat_idx] += stop_1l::genweights().at(110)*scale1fb_reCalc*lumi/h_counter->GetBinContent(13);
		// Factorization/Renormalization Scale, aka Q2
		q2Up[classyCat_idx] += stop_1l::genweights().at(4)*scale1fb_reCalc*lumi/h_counter->GetBinContent(5);
		q2Dn[classyCat_idx] += stop_1l::genweights().at(8)*scale1fb_reCalc*lumi/h_counter->GetBinContent(9);

		for(int iPDF=0; iPDF<nPDFs; iPDF++){
		  pdfs[iPDF][classyCat_idx] += stop_1l::genweights().at(iPDF+9)*scale1fb_reCalc*lumi;
		}
		
		
	      } // end if sample contains gen weights
	    } // end if not data
	    
	    
	    histos.var_nGenLep->histo_[hist_idx]->Fill( nGenPromptLep, wgt );
	    histos.var_nGenNu->histo_[hist_idx]->Fill( nGenPromptNu, wgt );


	    histos.var_nJets->histo_[hist_idx]->Fill( nSelJets, wgt );
	    histos.var_nTags->histo_[hist_idx]->Fill( nTagJets, wgt );

	    histos.var_mt->histo_[hist_idx]->Fill( mt_met_lep(), wgt );
	    histos.var_minDPhi->histo_[hist_idx]->Fill( mindphi_met_j1_j2(), wgt );
	    
	    histos.var_met->histo_[hist_idx]->Fill( pfmet(), wgt );
	    if( MT2W()<=200 ) histos.var_met_lowDM->histo_[hist_idx]->Fill( pfmet(), wgt );
	    if( MT2W()>200  ) histos.var_met_highDM->histo_[hist_idx]->Fill( pfmet(), wgt );

	    histos.var_mt2w->histo_[hist_idx]->Fill( MT2W(), wgt );
	    histos.var_mt2w_max->histo_[hist_idx]->Fill( std::max(MT2W(), MT2W_lep2()), wgt );

	    histos.var_modTopness->histo_[hist_idx]->Fill( topnessMod(), wgt );
	    
	    
	  } // end loop over categories
	} // end loop over 
	    

      } // end loop over systematics

    } // end loop over events


      
    //
    // Clean Up
    //
    delete tree;
    file.Close();
  }
  if ( nEventsChain != nEventsTotal ) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }
  
  if(isData) fclose(evtList);

  //
  // Clone nominal backgrounds for systematics that aren't shape-based
  //
  int nom_sys = 0;
  for(int iSys=0; iSys<(int)histos.systematics.size(); iSys++){
    if( histos.systematics[iSys]->id == k_nominal ){
      nom_sys = iSys;
      break;
    }
  }
  
  // 
  // Get Std Dev of PDF Variations
  //
  double pdfSFUp[nClassifications][nCategories];
  double pdfSFDn[nClassifications][nCategories];
  double alphasSFUp[nClassifications][nCategories];
  double alphasSFDn[nClassifications][nCategories];
  double q2SFUp[nClassifications][nCategories];
  double q2SFDn[nClassifications][nCategories];
  for(int iClassy=0; iClassy<nClassifications; iClassy++){
    for(int iCat=0; iCat<nCategories; iCat++){
      pdfSFUp[iClassy][iCat] = 1.0;
      alphasSFUp[iClassy][iCat] = 1.0;
      q2SFUp[iClassy][iCat] = 1.0;

      pdfSFDn[iClassy][iCat] = 1.0;
      alphasSFDn[iClassy][iCat] = 1.0;
      q2SFDn[iClassy][iCat] = 1.0;
    }
  }

  if(!isData && sampleHasGenWgts){
    for(int iClassy=0; iClassy<(int)histos.classifications.size(); iClassy++){
      for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
      
	int h_nom_idx = iClassy*nSystematics*nCategories;
	h_nom_idx += nom_sys*nCategories;
	h_nom_idx += iCat;

	
	int classyCat_idx = iClassy*nCategories + iCat;

	double sum   = 0.0;
	double sumSq = 0.0;
	for(int iPDF=0; iPDF<nPDFs; iPDF++){
	  sum   += pdfs[iPDF][classyCat_idx];
	  sumSq += pow( pdfs[iPDF][classyCat_idx], 2 );
	}//  end loop over pdf variations

	if( sum > 0.0 ){
	  double avg     = sum/nPDFs;
	  double std_dev = sqrt( (sumSq/nPDFs)-pow(avg,2) );
	  
	  // Cat Yield
	  double yield = histos.var_yield->histo_[h_nom_idx]->Integral(0,-1);
	
	  // Nominal
	  double nom = nominal[classyCat_idx];
	  // AlphaS
	  double alphaSUp = alphasUp[classyCat_idx];
	  double alphaSDn = alphasDn[classyCat_idx];
	  alphasSFUp[iClassy][iCat] = (1.0+((alphaSUp-nom)/nom));
	  alphasSFDn[iClassy][iCat] = (1.0+((alphaSDn-nom)/nom));

	  // Factorization/Renormalization Scale, aka Q2
	  double Q2Up = q2Up[classyCat_idx];
	  double Q2Dn = q2Dn[classyCat_idx];
	  q2SFUp[iClassy][iCat] = (1.0+((Q2Up-nom)/nom));
	  q2SFDn[iClassy][iCat] = (1.0+((Q2Dn-nom)/nom));
	  
	  
	  double pdfUp = nom*((avg+std_dev)/avg);
	  double pdfDn = nom*((avg-std_dev)/avg);
	  pdfSFUp[iClassy][iCat] = (1.0+((pdfUp-nom)/nom));
	  pdfSFDn[iClassy][iCat] = (1.0+((pdfDn-nom)/nom));
	}
	
      } // end loop over categories
    } // end loop over classifications
  } // if not isData



  //
  // Clone nominal backgrounds for systematics that aren't shape-based
  //
  for(int iVar=0; iVar<(int)histos.vars_1D.size(); iVar++){
      
    for(int iClassy=0; iClassy<(int)histos.classifications.size(); iClassy++){
      for(int iSys=0; iSys<(int)histos.systematics.size(); iSys++){
	  
	if(histos.systematics[iSys]->isShapeSys) continue;

	if( histos.systematics[iSys]->id!=k_nominal &&
	    !histos.vars_1D[iVar]->fillAllSys           ) continue;
		  
	for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	    
	  int h_nom_idx = iClassy*nSystematics*nCategories;
	  h_nom_idx += nom_sys*nCategories;
	  h_nom_idx += iCat;

	  int h_idx = iClassy*nSystematics*nCategories;
	  h_idx += iSys*nCategories;
	  h_idx += iCat;

	  TString hName_label = "h__";
	  hName_label += histos.vars_1D[iVar]->label;
	  hName_label += "__";
	  hName_label += histos.classifications[iClassy]->label;
	  hName_label += "__";
	  hName_label += histos.systematics[iSys]->label;
	  hName_label += "__";
	  hName_label += histos.categories[iCat]->label;

	  TString hName_title = histos.vars_1D[iVar]->title;
	    
	  TString hName_titleX = histos.vars_1D[iVar]->titleX;

	  histos.vars_1D[iVar]->histo_[ h_idx ] = (TH1D*)histos.vars_1D[iVar]->histo_[ h_nom_idx ]->Clone(hName_label);

	  histos.vars_1D[iVar]->histo_[h_idx ]->SetDirectory(out_file);

	  histos.vars_1D[iVar]->histo_[ h_idx ]->SetTitle(hName_title);

	  histos.vars_1D[iVar]->histo_[ h_idx ]->GetXaxis()->SetTitle(hName_titleX);

	  if( histos.systematics[iSys]->id == k_pdfUp ){
	    histos.vars_1D[iVar]->histo_[ h_idx ]->Scale( pdfSFUp[iClassy][iCat] );
	  }
	  else if( histos.systematics[iSys]->id == k_pdfDown ){
	    histos.vars_1D[iVar]->histo_[ h_idx ]->Scale( pdfSFDn[iClassy][iCat] );
	  }
	  else if( histos.systematics[iSys]->id == k_alphasUp ){
	    histos.vars_1D[iVar]->histo_[ h_idx ]->Scale( alphasSFUp[iClassy][iCat] );
	  }
	  else if( histos.systematics[iSys]->id == k_alphasDown ){
	    histos.vars_1D[iVar]->histo_[ h_idx ]->Scale( alphasSFDn[iClassy][iCat] );
	  }
	  else if( histos.systematics[iSys]->id == k_q2Up ){
	    histos.vars_1D[iVar]->histo_[ h_idx ]->Scale( q2SFUp[iClassy][iCat] );
	  }
	  else if( histos.systematics[iSys]->id == k_q2Down ){
	    histos.vars_1D[iVar]->histo_[ h_idx ]->Scale( q2SFDn[iClassy][iCat] );
	  }
	  else histos.vars_1D[iVar]->histo_[ h_idx ]->Scale( histos.systematics[iSys]->yieldSF );
	    
	} // end loop over categories
      } // end loop over systematics
    } // end loop over classifications
  } // end loop over variables

  /*
  //
  // Normalize metResSF and diNuSF Up/Down to Nominal Yield
  //
  for(int iVar=0; iVar<(int)histos.vars_1D.size(); iVar++){
    if( !histos.vars_1D[iVar]->fillAllSys ) continue;
    for(int iClassy=0; iClassy<(int)histos.classifications.size(); iClassy++){
      for(int iSys=0; iSys<(int)histos.systematics.size(); iSys++){
	if( histos.systematics[iSys]->id!=k_metRes_Up &&
	    histos.systematics[iSys]->id!=k_metRes_Down &&
	    histos.systematics[iSys]->id!=k_diNuSF_Up &&
	    histos.systematics[iSys]->id!=k_diNuSF_Down     ) continue;
	for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  
	  int h_nom_idx = iClassy*nSystematics*nCategories;
	  h_nom_idx += nom_sys*nCategories;
	  h_nom_idx += iCat;
	  
	  int h_idx = iClassy*nSystematics*nCategories;
	  h_idx += iSys*nCategories;
	  h_idx += iCat;
	  
	  if( histos.systematics[iSys]->id==k_metRes_Up ) histos.vars_1D[iVar]->histo_[ h_idx ]->Scale( nom_incl_yield/metResUp_yield );
	  else if( histos.systematics[iSys]->id==k_metRes_Down ) histos.vars_1D[iVar]->histo_[ h_idx ]->Scale( nom_incl_yield/metResDn_yield );
	  else if( histos.systematics[iSys]->id==k_diNuSF_Up ) histos.vars_1D[iVar]->histo_[ h_idx ]->Scale( nom_incl_yield/diNuSFUp_yield );
	  else if( histos.systematics[iSys]->id==k_diNuSF_Down ) histos.vars_1D[iVar]->histo_[ h_idx ]->Scale( nom_incl_yield/diNuSFDn_yield );

	} // end loop over categories
      } // end loop over systematics
    } // end loop over classifications
  } // end loop over variables
  */
  cout << "  For metResUp  nom/metResUp = " << nom_incl_yield/metResUp_yield << endl;
  cout << "  For metResDn  nom/metResDn = " << nom_incl_yield/metResDn_yield << endl;
  cout << "  For diNuSFUp  nom/diNuSFUp = " << nom_incl_yield/diNuSFUp_yield << endl;
  cout << "  For diNuSFDn  nom/diNuSFDn = " << nom_incl_yield/diNuSFDn_yield << endl;

  
  //
  // Close Output File
  //
  out_file->Write();
  out_file->Close();

  if(isData) duplicate_removal::clear_list();
  
  //
  // Print Selection Cutflow
  //
  cout << endl;
  cout << "=====================================================" << endl;
  cout << "Selection Cutflow" << endl;
  cout << "    nEvents Processed                    = " << nEventsChain << endl;
  cout << "    nEvents pass duplicate removal       = " << nEvents_pass_duplicate_removal << endl;
  cout << "    nEvents pass data filter (wgt)       = " << nEvents_pass_dataFilter << " (" << nEvents_pass_dataFilter_wgt << "),  Eff = " << (double)nEvents_pass_dataFilter/(double)nEvents_pass_duplicate_removal << endl;
  cout << "    nEvents pass trigger (wgt)           = " << nEvents_pass_trigger << " (" << nEvents_pass_trigger_wgt << "),  Eff = " << (double)nEvents_pass_trigger/(double)nEvents_pass_dataFilter << endl;
  cout << "    nEvents Pass >1 Vertex (wgt)         = " << nEvents_pass_nVtx << " (" << nEvents_pass_nVtx_wgt << "),  Eff = " << (double)nEvents_pass_nVtx/(double)nEvents_pass_dataFilter << endl;
  cout << "    nEvents Pass 1 Good Lepton (wgt)     = " << nEvents_pass_nGoodLep << " (" << nEvents_pass_nGoodLep_wgt << "),  Eff = " << (double)nEvents_pass_nGoodLep/(double)nEvents_pass_nVtx << endl;
  cout << "    nEvents Pass 1 Selected Lepton (wgt) = " << nEvents_pass_nSelLep << " (" << nEvents_pass_nSelLep_wgt << "),  Eff = " << (double)nEvents_pass_nSelLep/(double)nEvents_pass_nGoodLep << endl;
  cout << "                     nMuons (wgt)        = " << nEvents_pass_nSelLep_isMu << " (" << nEvents_pass_nSelLep_isMu_wgt << ")" << endl;
  cout << "                     nElectrons (wgt)    = " << nEvents_pass_nSelLep_isEle << " (" << nEvents_pass_nSelLep_isEle_wgt << ")" << endl;
  cout << "    nEvents Pass diLep Veto Inversion (wgt) = " << nEvents_pass_diLeptonSel << " (" << nEvents_pass_diLeptonSel_wgt << "),  Eff = " << (double)nEvents_pass_diLeptonSel/(double)nEvents_pass_nSelLep << endl;
  cout << "    nEvents Pass >=2 Selected Jets (wgt) = " << nEvents_pass_nJets << " (" << nEvents_pass_nJets_wgt << "),  Eff = " << (double)nEvents_pass_nJets/(double)nEvents_pass_diLeptonSel_wgt << endl;
  cout << "    nEvents Pass >=1 BTagged Jets (wgt)  = " << nEvents_pass_nBJets << " (" << nEvents_pass_nBJets_wgt << "),  Eff = " << (double)nEvents_pass_nBJets/nEvents_pass_nJets << endl;
  cout << "    nEvents Pass Met>200.0 (wgt)         = " << nEvents_pass_met << " (" << nEvents_pass_met_wgt << "),  Eff = " << (double)nEvents_pass_met/(double)nEvents_pass_nBJets << endl;
  cout << "    nEvents Pass MT>150.0 (wgt)          = " << nEvents_pass_mtCut << " (" << nEvents_pass_mtCut_wgt << "),  Eff = " << (double)nEvents_pass_mtCut/(double)nEvents_pass_met << endl;
  cout << "    nEvents Pass minDeltaPhi>0.8 (wgt)   = " << nEvents_pass_minDPhi << " (" << nEvents_pass_minDPhi_wgt << "),  Eff = " << (double)nEvents_pass_minDPhi/(double)nEvents_pass_mtCut << endl;
  cout << endl;
  cout << "    nEvents Pass Baseline (wgt)          = " << nEvents_pass_baseline << " (" << nEvents_pass_baseline_wgt << ")" << endl;
  cout << "                    nMuons (wgt)         = " << nEvents_pass_baseline_isMu << " (" << nEvents_pass_baseline_isMu_wgt << ")" << endl;
  cout << "                    nElectrons (wgt)     = " << nEvents_pass_baseline_isEle << " (" << nEvents_pass_baseline_isEle_wgt << ")" << endl;
  cout << endl;
  cout << "                    n_0lep (wgt)         = " << nEvents_pass_baseline_is_ee0lep << " (" << nEvents_pass_baseline_is_ee0lep_wgt << ")" << endl;
  cout << "                    n_1lep (wgt)         = " << nEvents_pass_baseline_is_ee1lep << " (" << nEvents_pass_baseline_is_ee1lep_wgt << ")" << endl;
  cout << "                    n_2lep (wgt)         = " << nEvents_pass_baseline_is_ge2lep << " (" << nEvents_pass_baseline_is_ge2lep_wgt << ")" << endl;
  cout << "                    n_ZtoNuNu (wgt)      = " << nEvents_pass_baseline_is_ZtoNuNu << " (" << nEvents_pass_baseline_is_ZtoNuNu_wgt << ")" << endl;
  cout << "                   >=3j n_CR4 (wgt)      = " << nEvents_pass_CR4 << " (" << nEvents_pass_CR4_wgt << ")" << endl;
  cout << "                   >=3j n_CR5 (wgt)      = " << nEvents_pass_CR5 << " (" << nEvents_pass_CR5_wgt << ")" << endl;
  cout << "                   >=3j n_CR6 (wgt)      = " << nEvents_pass_CR6 << " (" << nEvents_pass_CR6_wgt << ")" << endl;
  cout << "=====================================================" << endl;


  // Clean up bTagging
  if (applyBtagSFs && !isData) {
    delete calib;
    delete reader_heavy;
    delete reader_heavy_UP;
    delete reader_heavy_DN;
    delete reader_light;
    delete reader_light_UP;
    delete reader_light_DN;
    if (isFastsim) {
      delete calib_fastsim;
      delete reader_fastsim;
      delete reader_fastsim_UP;
      delete reader_fastsim_DN;
    }
  }


  //
  // Benchmark Reporting
  //
  bmark->Stop("benchmark");
  cout << endl;
  cout << nEventsTotal << " Events Processed" << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:	" << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:	" << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;
 
  //
  // Return!
  //
  return 0;

}
