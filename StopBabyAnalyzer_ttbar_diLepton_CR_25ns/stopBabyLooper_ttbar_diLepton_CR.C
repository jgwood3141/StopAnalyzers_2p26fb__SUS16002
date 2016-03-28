// Usage:
// > root -b doAll.C
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

int stopBabyLooper_ttbar_diLepton_CR( TChain* chain, TString output_file="histos.root", bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {

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
  // Decalre simplicity of analyzer
  //
  bool doNominalOnly = false;


  //
  // Declare output file
  //
  TFile *out_file = new TFile(output_file, "recreate");

  //
  // Declare Histograms
  //
  TH1::SetDefaultSumw2();

  histoHelper histos;
  
  int nClassifications = histos.classifications.size();
  int nSystematics = histos.systematics.size();
  int nCategories = histos.categories.size();
  
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


  bool isData = false;
  if( output_file.Contains("data") ) isData = true;

  //
  // Met Filter
  //
  eventFilter metFilterTxt; 
  if( output_file.Contains("data") ){
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
  bool applyBtagSFs     = true;
  bool applyLepSFs      = true;
  bool applyTopPtSFs    = false;
  bool applyTopPtUnc    = true;

  
  // Data and MC
  int nBins_pt = 200;
  double pt_min = 0.0;
  double pt_max = 200.0;

  int nBins_eta = 60;
  double eta_min = -3.0;
  double eta_max = 3.0;

  double met_max = 600.0;
  double sysPt_max = 600.0;
  double sysM_max = 1200.0;

  TH1D *h_lep1_pt_pass_metTrig_diLepSel = new TH1D("h_lep1_pt_pass_metTrig_diLepSel", "Leading lepton pT, passes MET trigger, diLepton Selection", nBins_pt, pt_min, pt_max);
  TH1D *h_lep1_eta_pass_metTrig_diLepSel = new TH1D("h_lep1_eta_pass_metTrig_diLepSel", "Leading lepton #eta, passes MET trigger, diLepton Selection", nBins_eta, eta_min, eta_max);
  
  TH1D *h_lep2_pt_pass_metTrig_diLepSel = new TH1D("h_lep2_pt_pass_metTrig_diLepSel", "Trailing lepton pT, passes MET trigger, diLepton Selection", nBins_pt, pt_min, pt_max);
  TH1D *h_lep2_eta_pass_metTrig_diLepSel = new TH1D("h_lep2_eta_pass_metTrig_diLepSel", "Trailing lepton #eta, passes MET trigger, diLepton Selection", nBins_eta, eta_min, eta_max);
  
  
  TH1D *h_lep1_pt_pass_metTrig_diLepSel_diLepTrig = new TH1D("h_lep1_pt_pass_metTrig_diLepSel_diLepTrig", "Leading lepton pT, passes MET trigger, diLepton Selection, diLepton trigger", nBins_pt, pt_min, pt_max);
  TH1D *h_lep1_eta_pass_metTrig_diLepSel_diLepTrig = new TH1D("h_lep1_eta_pass_metTrig_diLepSel_diLepTrig", "Leading lepton #eta, passes MET trigger, diLepton Selection, dilepton trigger", nBins_eta, eta_min, eta_max);
  
  TH1D *h_lep2_pt_pass_metTrig_diLepSel_diLepTrig = new TH1D("h_lep2_pt_pass_metTrig_diLepSel_diLepTrig", "Trailing lepton pT, passes MET trigger, diLepton Selection, diLepton trigger", nBins_pt, pt_min, pt_max);
  TH1D *h_lep2_eta_pass_metTrig_diLepSel_diLepTrig = new TH1D("h_lep2_eta_pass_metTrig_diLepSel_diLepTrig", "Trailing lepton #eta, passes MET trigger, diLepton Selection, dilepton trigger", nBins_eta, eta_min, eta_max);
  

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

  TH2D *h_gen_met_vs_sysPt = new TH2D("h_gen_met_vs_sysPt", "GEN: MET vs system pT;system pT;MET", 60, 0.0, sysPt_max, 60, 0.0, met_max);
  TH2D *h_gen_met_vs_sysM  = new TH2D("h_gen_met_vs_sysM", "GEN: MET vs system Mass;system Mass;MET", 120, 0.0, sysM_max, 60, 0.0, met_max);

  TH1D *h_reco_emu2b_pt = new TH1D("h_reco_emu2b_pt", "RECO: e,mu,b,b system pT", 60, 0.0, sysPt_max);
  
  
  //
  // Event Counters
  //
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if( nEvents >= 0 ) nEventsChain = nEvents;


  //
  // DiLepton Cutflow
  //
  unsigned int nEvents_pass_duplicate_removal = 0;

  bool doCut_dataFilter = true;
  unsigned int nEvents_pass_dataFilter = 0;
  double nEvents_pass_dataFilter_wgt = 0.0;

  bool doCut_nGoodLep = true;
  int cut_nGoodLep = 2;
  unsigned int nEvents_pass_1GoodLep = 0;
  double nEvents_pass_1GoodLep_wgt = 0.0;
  unsigned int nEvents_pass_nGoodLep = 0;
  double nEvents_pass_nGoodLep_wgt = 0.0;


  bool doCut_oppSignChargeLeps = true;
  unsigned int nEvents_pass_oppSignChargeLeps = 0;
  double nEvents_pass_oppSignChargeLeps_wgt = 0.0;


  bool doCut_leptonFlavour = false;
  int cut_leptonFlavour = 24; // sum of pdgId ee=22, emu=24, mumu=26
  unsigned int nEvents_pass_leptonFlavour = 0;
  double nEvents_pass_leptonFlavour_wgt = 0.0;


  bool doCut_trigger = true;
  unsigned int nEvents_pass_trigger = 0;
  double nEvents_pass_trigger_wgt = 0.0;


  bool doCut_diLepMass = true;
  double cut_diLepMass = 20.0;
  unsigned int nEvents_pass_diLepMass = 0;
  double nEvents_pass_diLepMass_wgt = 0.0;


  bool doCut_zMassWindow = true;
  double zMass = 91.1876;
  double zMassWindow_low = zMass - 15.0;
  double zMassWindow_high = zMass + 15.0;
  unsigned int nEvents_pass_zMassWindow = 0;
  double nEvents_pass_zMassWindow_wgt = 0.0;


  bool doCut_nJets = true;
  int cut_nJets = 2;
  unsigned int nEvents_pass_nJets = 0;
  double nEvents_pass_nJets_wgt = 0.0;


  bool doCut_nBTags = true;
  int cut_nBTags = 0;
  unsigned int nEvents_pass_nBTags = 0;
  double nEvents_pass_nBTags_wgt = 0.0;


  bool doCut_met = true;
  double cut_met = 50.0;
  unsigned int nEvents_pass_met = 0;
  double nEvents_pass_met_wgt = 0.0;


  unsigned int nEvents_pass_selection = 0;
  double nEvents_pass_selection_wgt = 0.0;

  unsigned int nEvents_pass_selection_elel = 0;
  double nEvents_pass_selection_elel_wgt = 0.0;

  unsigned int nEvents_pass_selection_elmu = 0;
  double nEvents_pass_selection_elmu_wgt = 0.0;

  unsigned int nEvents_pass_selection_mumu = 0;
  double nEvents_pass_selection_mumu_wgt = 0.0;
  

  unsigned int nEvents_pass_metTrigger_diLepSel = 0;
  double nEvents_pass_metTrigger_diLepSel_wgt = 0.0;

  unsigned int nEvents_pass_metTrigger_diLepSel_diLepTrigger = 0;
  double nEvents_pass_metTrigger_diLepSel_diLepTrigger_wgt = 0.0;


  long int max_run = 0;
  long int max_lumi = 0;
  

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
  TFile *f_mu_SF_id;
  TFile *f_mu_SF_iso;
  
  TH2D *h_el_SF = NULL;
  TH2D *h_mu_SF = NULL;
  
  if(applyLepSFs && !isData){
   
    f_el_SF     = new TFile("lepsf/kinematicBinSFele.root", "read");
    f_mu_SF_id  = new TFile("lepsf/TnP_MuonID_NUM_MediumID_DENOM_generalTracks_VAR_map_pt_eta.root", "read");
    f_mu_SF_iso = new TFile("lepsf/TnP_MuonID_NUM_MiniIsoTight_DENOM_LooseID_VAR_map_pt_eta.root");
    
    TH2D *h_el_SF_id_temp  = (TH2D*)f_el_SF->Get("CutBasedMedium");
    TH2D *h_el_SF_iso_temp = (TH2D*)f_el_SF->Get("MiniIso0p1_vs_AbsEta");
    TH2D *h_mu_SF_id_temp  = (TH2D*)f_mu_SF_id->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_tag_IsoMu20_pass");
    TH2D *h_mu_SF_iso_temp = (TH2D*)f_mu_SF_iso->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_tag_combRelIsoPF04dBeta_bin0_&_tag_pt_bin0_&_PF_pass_&_tag_IsoMu20_pass");

    out_file->cd();

    TH2D *h_el_SF_id  = (TH2D*)h_el_SF_id_temp->Clone("h_el_SF_id");
    TH2D *h_el_SF_iso = (TH2D*)h_el_SF_iso_temp->Clone("h_el_SF_iso");
    TH2D *h_mu_SF_id  = (TH2D*)h_mu_SF_id_temp->Clone("h_mu_SF_id");
    TH2D *h_mu_SF_iso = (TH2D*)h_mu_SF_iso_temp->Clone("h_mu_SF_iso");

    h_el_SF = (TH2D*)h_el_SF_id->Clone("h_el_SF");
    h_el_SF->Multiply(h_el_SF_iso);

    h_mu_SF = (TH2D*)h_mu_SF_id->Clone("h_mu_SF");
    h_mu_SF->Multiply(h_mu_SF_iso);

    f_el_SF->Close();
    f_mu_SF_id->Close();
    f_mu_SF_iso->Close();
    cout << "loaded lepton SFs" << endl;
  }

  
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

  
  //
  // Event list
  //
  FILE *evtList = NULL;
  if(isData){
    evtList = fopen("eventList__ttbar_CR__data.dat","w");
    fprintf(evtList,"RunNumber  LumiSec  EventNumber  CRid  MET  MET_phi  MT  MINDPHI  MT2W  lep1_pt  lep1_eta  lep1_phi  lep2_pt  lep2_eta  lep2_phi  passTrackIso  passTau  nSelJets  nBJets  jet1Pt  jet2Pt\n");
  }
  
  
  //
  // Get List of Files
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

      nEventsTotal++;
      
      
      //
      // Progress
      //
      stop_1l_babyAnalyzer::progress( nEventsTotal, nEventsChain );

      
      //
      // Duplicate Data Event removal
      //
      if( is_data() ) isData = true;
      
      if( is_data() ) {
	duplicate_removal::DorkyEventIdentifier id(run(), evt(), ls());
        if (is_duplicate(id) ) continue;
      }
      nEvents_pass_duplicate_removal++;

      bool printCutflow=false;
      if( (run()==259822 && ls()==451 && evt()==627724008) ||
	  (run()==257645 && ls()==678 && evt()==1035948603)    ) printCutflow=true;
      
      // Identify largest run and lumi number in data
      if( run()>max_run ){
	max_run = run();
	if(ls()>max_lumi ) max_lumi = ls();
      }
      
           
      
      //
      // Loop over systematics
      //
      for(int iSys=0; iSys<(int)histos.systematics.size(); iSys++){
	
	bool isNominal = (k_nominal==histos.systematics[iSys]->id);

	if( !histos.systematics[iSys]->isShapeSys ) continue;

	if( doNominalOnly && !isNominal ) continue;

	//
	// Get Event Weight
	//
	double wgt = 1.0;
	//wgt = scale1fb();
	//double scale1fb_reCalc = 1000.0*xsec()*kfactor()/h_counter->GetBinContent(22);
	double scale1fb_reCalc = scale1fb();
	if( is_amcnlo ) scale1fb_reCalc = scale1fb();
	wgt = scale1fb_reCalc;

	double lumi = 2.26; // Run 2012C+D
	//double lumi = 2.11; // Run 2012C+D
	wgt *= lumi;

	wgt *= histos.systematics[iSys]->yieldSF;
	
	// top pT weighting
	double wgt_topPt = 1.0;
	if( (applyTopPtSFs || applyTopPtUnc) && isTTbar && !is_data()){
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
	  if( nTopsFound!=2 )      cout << "    Did not find 2 tops for top pT reweighting, nFound=" << nTopsFound << endl;
	  
	  wgt_topPt = topPtWeight(genTopPt, genTopBarPt);

	  
	  if(applyTopPtSFs){
	    if(histos.systematics[iSys]->id==k_topPtSFUp) wgt *= ( (wgt_topPt-1)*2 + 1 );
	    else if(histos.systematics[iSys]->id==k_topPtSFDown) wgt *= 1.0;
	    else wgt *= wgt_topPt;
	  }
	  if(applyTopPtUnc){
	    if(histos.systematics[iSys]->id==k_topPtSFUp) wgt *= wgt_topPt;
	    else if(histos.systematics[iSys]->id==k_topPtSFDown) wgt *= 1.0;
	    else wgt *= 1.0;
	  }
	  
	}
	
	
	//
	// Data wgt always = 1.0
	//
	if( is_data() ) wgt = 1.0;

	
	//
	// Check number of hard process gen leptons
	//
	int nGenPromptLep = 0;
	int nGenPromptNu    = 0;
	
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
	  else if( is_0lep ){
	    for(int iClassy=0; iClassy<(int)histos.classifications.size(); iClassy++){
	      if( k_ee0lep == histos.classifications[iClassy]->id ) classy_idx.push_back(iClassy);
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
	// Selection
	//
	if(isNominal && printCutflow) cout << endl << endl << "    Beginning Cutflow for run=" << run() << ", evt=" << evt() << ", ls=" << ls() << endl;
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
	
	// MET monitoring trigger
	bool passMETTriggers = false;
	//if( HLT_MonoCentPFJet80_METNoMu90_MHTNoMu90_IDTight() ||
	//    HLT_MET90_MHT90_IDTight() ||
	//    HLT_METNoMu90_NoiseCleaned_MHTNoMu90_IDTight() ){
	//  passMETTriggers = true;
	//}
	if( HLT_MonoCentPFJet80_METNoMu90_MHTNoMu90_IDTight() ||
	    HLT_METNoMu90_NoiseCleaned_MHTNoMu90_IDTight()       ){
	  passMETTriggers = true;
	}
	if(isNominal && printCutflow) cout << "      Selected Lepton Info: lep1 pT=" << lep1_pt() << ", lep1 eta=" << lep1_eta() << ", lep1 phi=" << lep1_phi() << ", lep1 miniRelIsoEA=" << lep1_miniRelIsoEA() << ", lep1_is_mu=" << lep1_is_mu() << ", lep1_is_muoid_tight()=" << lep1_is_muoid_tight() << ", lep1_is_el()=" << lep1_is_el() << ", lep1_pass_mediumid=" << lep1_passMediumID() << endl;
	if(isNominal && printCutflow) cout << "      SecondLepVeto Info: lep2 pT=" << lep2_pt() << ", lep2 eta=" << lep2_eta() << ", lep2 phi=" << lep2_phi() << ", lep2_miniRelIso=" << lep2_miniRelIsoEA() << ", lep2_is_mu=" << lep2_is_mu() << ", lep2_is_muoid_tight()=" << lep2_is_muoid_tight() << ", lep2_is_el()=" << lep2_is_el() << ", lep2_pass_mediumid=" << lep2_passMediumID() << endl;

	// Lepton Selection
	int nSelectedLeptons         = 0; // counter
	
	double lep1_electron_pt_cut     = 30.0;
	//double lep1_electron_eta_cut    = 2.1;
	double lep1_electron_eta_cut    = 1.442;
	double lep1_electron_relIso_cut = 0.1;
	double lep1_muon_pt_cut         = 30.0;
	//double lep1_muon_eta_cut        = 2.1;
	double lep1_muon_eta_cut        = 2.4;
	double lep1_muon_relIso_cut     = 0.1;

	double lep2_electron_pt_cut     = 15.0;
	//double lep2_electron_pt_cut     = 20.0;
	//double lep2_electron_eta_cut    = 2.1;
	double lep2_electron_eta_cut    = 1.442;
	double lep2_electron_relIso_cut = 0.1;
	double lep2_muon_pt_cut         = 15.0;
	//double lep2_muon_pt_cut         = 20.0;
	//double lep2_muon_eta_cut        = 2.1;
	double lep2_muon_eta_cut        = 2.4;
	double lep2_muon_relIso_cut     = 0.1;
		
	TLorentzVector lep1_TLV( 0.0, 0.0, 0.0, 0.0);
	TLorentzVector lep2_TLV( 0.0, 0.0, 0.0, 0.0);
	if( doCut_nGoodLep ){
	
	  if( lep1_is_mu() ){
	    if( lep1_pt() > lep1_muon_pt_cut &&
		fabs(lep1_eta()) < lep1_muon_eta_cut &&
		lep1_is_muoid_tight() &&
		lep1_miniRelIsoEA() < lep1_muon_relIso_cut ){
	      nSelectedLeptons++;
	      lep1_TLV.SetPxPyPzE( lep1_p4().Px(), lep1_p4().Py(), lep1_p4().Pz(), lep1_p4().E() );
	    }
	  }
	
	  if( lep1_is_el() ){
	    if( lep1_pt() > lep1_electron_pt_cut &&
		fabs(lep1_eta()) < lep1_electron_eta_cut &&
		lep1_passMediumID() &&
		lep1_miniRelIsoEA() < lep1_electron_relIso_cut ){
	      nSelectedLeptons++;
	      lep1_TLV.SetPxPyPzE( lep1_p4().Px(), lep1_p4().Py(), lep1_p4().Pz(), lep1_p4().E() );
	    }
	  }

	  if( isNominal && nSelectedLeptons==1 ){
	    nEvents_pass_1GoodLep++;
	    nEvents_pass_1GoodLep_wgt+=wgt;
	  }

	  if( lep2_is_mu() ){
	    if( lep2_pt() > lep2_muon_pt_cut &&
		fabs(lep2_eta()) < lep2_muon_eta_cut &&
		lep2_is_muoid_tight() &&
		lep2_miniRelIsoEA() < lep2_muon_relIso_cut ){
	      nSelectedLeptons++;
	      lep2_TLV.SetPxPyPzE( lep2_p4().Px(), lep2_p4().Py(), lep2_p4().Pz(), lep2_p4().E() );
	    }
	  }

	  if( lep2_is_el() ){
	    if( lep2_pt() > lep2_electron_pt_cut &&
		fabs(lep2_eta()) < lep2_electron_eta_cut &&
		lep2_passMediumID() &&
		lep2_miniRelIsoEA() < lep2_electron_relIso_cut ){
	      nSelectedLeptons++;
	      lep2_TLV.SetPxPyPzE( lep2_p4().Px(), lep2_p4().Py(), lep2_p4().Pz(), lep2_p4().E() );
	    }
	  }

	  if( nSelectedLeptons != cut_nGoodLep ) continue;

	}
	if(isNominal && printCutflow) cout << "    Pass ==2 Good Leptons" << endl;
	double lepSF    = 1.0;
	double lepSF_Up = 1.0;
	double lepSF_Dn = 1.0;
	if(applyLepSFs && !is_data()){
	
	  float lepSF_pt_cutoff = 100.0;

	  // Lep1 SF
	  if(lep1_is_el()){
	    int binX = h_el_SF->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, lep1_p4().Pt()) );
	    int binY = h_el_SF->GetYaxis()->FindBin( fabs(lep1_p4().Eta()) );
	    lepSF    = h_el_SF->GetBinContent( binX, binY );
	    lepSF_Up = (lepSF + h_el_SF->GetBinError( binX, binY ));
	    lepSF_Dn = (lepSF - h_el_SF->GetBinError( binX, binY ));
	  }
	  if(lep1_is_mu()){
	    int binX = h_mu_SF->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, lep1_p4().Pt()) );
	    int binY = h_mu_SF->GetYaxis()->FindBin( fabs(lep1_p4().Eta()) );
	    lepSF    = h_mu_SF->GetBinContent( binX, binY );
	    lepSF_Up = (lepSF + h_mu_SF->GetBinError( binX, binY ));
	    lepSF_Dn = (lepSF - h_mu_SF->GetBinError( binX, binY ));
	  }

	  // Lep2 SF
	  if(lep2_is_el()){
	    int binX = h_el_SF->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, lep2_p4().Pt()) );
	    int binY = h_el_SF->GetYaxis()->FindBin( fabs(lep2_p4().Eta()) );
	    lepSF    *= h_el_SF->GetBinContent( binX, binY );
	    lepSF_Up *= (lepSF + h_el_SF->GetBinError( binX, binY ));
	    lepSF_Dn *= (lepSF - h_el_SF->GetBinError( binX, binY ));
	  }
	  if(lep2_is_mu()){
	    int binX = h_mu_SF->GetXaxis()->FindBin( std::min(lepSF_pt_cutoff, lep2_p4().Pt()) );
	    int binY = h_mu_SF->GetYaxis()->FindBin( fabs(lep2_p4().Eta()) );
	    lepSF    *= h_mu_SF->GetBinContent( binX, binY );
	    lepSF_Up *= (lepSF + h_mu_SF->GetBinError( binX, binY ));
	    lepSF_Dn *= (lepSF - h_mu_SF->GetBinError( binX, binY ));
	  }

	  
	  // Apply Weight
	  if(histos.systematics[iSys]->id==k_lepSFUp) wgt *= lepSF_Up;
	  else if(histos.systematics[iSys]->id==k_lepSFDown) wgt *= lepSF_Dn;
	  else wgt *= lepSF;
	  
   	} // end if apply lepSF
	

	if(isNominal){
	  nEvents_pass_nGoodLep++;
	  nEvents_pass_nGoodLep_wgt+=wgt;
	}

	
	// Opposite sign charge leptons
	if( doCut_oppSignChargeLeps ){
	  if( lep1_charge()*lep2_charge()>0 ) continue;
	}
	if(isNominal){
	  nEvents_pass_oppSignChargeLeps++;
	  nEvents_pass_oppSignChargeLeps_wgt+=wgt;
	}
	if(isNominal && printCutflow) cout << "    Pass Opp Sign Charge Cut" << endl;

	// Lepton flavour cut
	int diLepFlavour = abs(lep1_pdgid())+abs(lep2_pdgid());
	if( doCut_leptonFlavour ){
	  // cut_leptonFlavour is sum of pdgId: ee=22, emu=24, mumu=26
	  if( diLepFlavour!=cut_leptonFlavour ) continue;
	}
	if(isNominal){
	  nEvents_pass_leptonFlavour++;
	  nEvents_pass_leptonFlavour_wgt+=wgt;
	}
	if(isNominal && printCutflow) cout << "    Pass Flavour Cut" << endl;

	bool isMuMu = (diLepFlavour==26) ? true : false;
	bool isElMu = (diLepFlavour==24) ? true : false;
	bool isElEl = (diLepFlavour==22) ? true : false;
	
	// DiLepton Classification
	if(isElEl){
	  for(int iClassy=0; iClassy<(int)histos.classifications.size(); iClassy++){
	    if( k_elel == histos.classifications[iClassy]->id ) classy_idx.push_back(iClassy);
	    if( k_elel_ee1lep == histos.classifications[iClassy]->id && is_1lep ) classy_idx.push_back(iClassy);
	    if( k_elel_ge2lep == histos.classifications[iClassy]->id && is_2lep ) classy_idx.push_back(iClassy);
	  }	
	}
	else if(isElMu){
	  for(int iClassy=0; iClassy<(int)histos.classifications.size(); iClassy++){
	    if( k_elmu == histos.classifications[iClassy]->id ) classy_idx.push_back(iClassy);
	    if( k_elmu_ee1lep == histos.classifications[iClassy]->id && is_1lep ) classy_idx.push_back(iClassy);
	    if( k_elmu_ge2lep == histos.classifications[iClassy]->id && is_2lep ) classy_idx.push_back(iClassy);
	  }	
	}
	else if(isMuMu){
	  for(int iClassy=0; iClassy<(int)histos.classifications.size(); iClassy++){
	    if( k_mumu == histos.classifications[iClassy]->id ) classy_idx.push_back(iClassy);
	    if( k_mumu_ee1lep == histos.classifications[iClassy]->id && is_1lep ) classy_idx.push_back(iClassy);
	    if( k_mumu_ge2lep == histos.classifications[iClassy]->id && is_2lep ) classy_idx.push_back(iClassy);
	  }	
	}
	else{
	  cout << "No Flavour Classification found, lep1,2 pdgId = " << lep1_pdgid() << ", " << lep2_pdgid() << endl;
	}
	

	// Denominator of diLep Trigger Efficiency
	if(isNominal){
	  if( passMETTriggers ){
	    nEvents_pass_metTrigger_diLepSel++;
	    nEvents_pass_metTrigger_diLepSel_wgt+=wgt;
	  
	    h_lep1_pt_pass_metTrig_diLepSel->Fill( lep1_pt(), wgt );
	    h_lep1_eta_pass_metTrig_diLepSel->Fill( lep1_eta(), wgt );

	    h_lep2_pt_pass_metTrig_diLepSel->Fill( lep2_pt(), wgt );
	    h_lep2_eta_pass_metTrig_diLepSel->Fill( lep2_eta(), wgt );
	  }
	}
	
	
	// Trigger Cut
	if( doCut_trigger ){
	  if(  !( HLT_DiEl() || HLT_DiMu() || HLT_Mu8El17() || HLT_Mu17El12() )  ) continue;
	}
	if(isNominal){
	  nEvents_pass_trigger++;
	  nEvents_pass_trigger_wgt+=wgt;
	}
	if(isNominal && printCutflow) cout << "    Pass Trigger" << endl;

	// Numerator of diLep triger efficiency
	if(isNominal){
	  if( passMETTriggers ){
	    nEvents_pass_metTrigger_diLepSel_diLepTrigger++;
	    nEvents_pass_metTrigger_diLepSel_diLepTrigger_wgt+=wgt;
	
	    h_lep1_pt_pass_metTrig_diLepSel_diLepTrig->Fill( lep1_pt(), wgt );
	    h_lep1_eta_pass_metTrig_diLepSel_diLepTrig->Fill( lep1_eta(), wgt );
	    h_lep2_pt_pass_metTrig_diLepSel_diLepTrig->Fill( lep2_pt(), wgt );
	    h_lep2_eta_pass_metTrig_diLepSel_diLepTrig->Fill( lep2_eta(), wgt );
	  }
	}

      
	TLorentzVector diLepton_TLV( 0.0, 0.0, 0.0, 0.0);
	diLepton_TLV += lep1_TLV;
	diLepton_TLV += lep2_TLV;
	
	// diLepton Mass Cut
	if( doCut_diLepMass ){
	  if( diLepton_TLV.M() < cut_diLepMass ) continue;
	}
	if(isNominal){
	  nEvents_pass_diLepMass++;
	  nEvents_pass_diLepMass_wgt+=wgt;
	}
	if(isNominal && printCutflow) cout << "    Pass diLepMass" << endl;
	
	// Z mass window cut
	if( doCut_zMassWindow && !isElMu ){
	  if( diLepton_TLV.M() > zMassWindow_low &&
	      diLepton_TLV.M() < zMassWindow_high   ) continue;
	}
	if(isNominal){
	  nEvents_pass_zMassWindow++;
	  nEvents_pass_zMassWindow_wgt+=wgt;
	}
	if(isNominal && printCutflow) cout << "    Pass Z Window " << endl;
	
	// nJets cut
	int nSelectedJets = 0;
	
	double jet_pt_cut = 30.0;
	double jet_eta_cut = 2.4;
	vector<int> selJets_idx;
	vector<int> selBarrelJets_idx;
	vector<int> selEndcapJets_idx;

	double CSV_LOOSE_WP   = 0.605;
	int nTaggedJets_loose = 0;
	
	double CSV_MED_WP   = 0.890;
	int nTaggedJets_med = 0;
	
	double CSV_TIGHT_WP   = 0.970;
	int nTaggedJets_tight = 0;
	
	float btagprob_data = 1.;
	float btagprob_err_heavy_UP = 0.;
	float btagprob_err_heavy_DN = 0.;
	float btagprob_err_light_UP = 0.;
	float btagprob_err_light_DN = 0.;
	float btagprob_mc = 1.;

	if( doCut_nJets ){
	  for(int iJet=0; iJet<(int)ak4pfjets_p4().size(); iJet++){
	    if( ak4pfjets_p4().at(iJet).Pt() >= jet_pt_cut &&
		fabs(ak4pfjets_p4().at(iJet).Eta()) <= jet_eta_cut &&
		ak4pfjets_loose_pfid().at(iJet)                       ){
	      nSelectedJets++;
	      selJets_idx.push_back(iJet);
	      
	      int jetFlav = -99;
	      
	      float pt_cutoff = std::max(20.,std::min(399.,double(ak4pfjets_pt()[iJet])));
	      TH2D* h(0);
	      int binx=-99;
	      int biny=-99;
	      
	      if( !is_data() && applyBtagSFs ){
	      	
		jetFlav = ak4pfjets_parton_flavor()[iJet];
		
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
	      
	      if( ak4pfjets_CSV().at(iJet) > CSV_LOOSE_WP ) nTaggedJets_loose++;
	      if( ak4pfjets_CSV().at(iJet) > CSV_TIGHT_WP ) nTaggedJets_tight++;
	      if( ak4pfjets_CSV().at(iJet) > CSV_MED_WP ){
		nTaggedJets_med++;
		
		// btag SF - not final yet
		if (!is_data() && applyBtagSFs) {
		  
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
	      
	    } // end if good jet

	  } // end loop over pfJets
	  
	  if( nSelectedJets < cut_nJets ) continue;
	}
	if(isNominal && printCutflow) cout << "    Pass nJets Cut" << endl;
	if (!is_data() && applyBtagSFs) {
		  
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
	  
	} // end if apply bTag SFs
	
	if(isNominal){
	  nEvents_pass_nJets++;
	  nEvents_pass_nJets_wgt+=wgt;
	}

	
	if( doCut_nBTags ){
	  if( nTaggedJets_med < cut_nBTags ) continue;
	}
	if(isNominal){
	  nEvents_pass_nBTags++;
	  nEvents_pass_nBTags_wgt+=wgt;
	}
	if(isNominal && printCutflow) cout << "    Pass nTags Cut" << endl;

	if( doCut_met ){
	  if( pfmet()<cut_met ) continue;
	}
	if(isNominal){
	  nEvents_pass_met++;
	  nEvents_pass_met_wgt+=wgt;
	}
	if(isNominal && printCutflow) cout << "    Pass MET Cut" << endl;

	
	// MET resolution
	double metResSF     = 1.0;
	double metResSF_err = 0.0;
	if( !is_data() ){
	  if( nSelectedJets==2 ){

	    if( pfmet()>=250.0 && pfmet()<350.0 ){
	      metResSF     = 1.032;
	      metResSF_err = 0.009;

	      if     ( histos.systematics[iSys]->id==k_metRes_ee2j_met_250_350_Up )   wgt *= (metResSF + metResSF_err);
	      else if( histos.systematics[iSys]->id==k_metRes_ee2j_met_250_350_Down ) wgt *= (metResSF - metResSF_err);
	      else wgt *= metResSF;
	    } // 250<MET<350
	  
	    if( pfmet()>=350.0 ){
	      metResSF     = 0.913;
	      metResSF_err = 0.024;

	      if     ( histos.systematics[iSys]->id==k_metRes_ee2j_met_350_inf_Up )   wgt *= (metResSF + metResSF_err);
	      else if( histos.systematics[iSys]->id==k_metRes_ee2j_met_350_inf_Down ) wgt *= (metResSF - metResSF_err);
	      else wgt *= metResSF;
	    } // MET>350
	  
	  } // end if nSelectedJets==2

	
	  if( nSelectedJets==3 ){
	  
	    if( pfmet()>=250.0 && pfmet()<350.0 ){
	      metResSF     = 1.032;
	      metResSF_err = 0.014;

	      if     ( histos.systematics[iSys]->id==k_metRes_ee3j_met_250_350_Up )   wgt *= (metResSF + metResSF_err);
	      else if( histos.systematics[iSys]->id==k_metRes_ee3j_met_250_350_Down ) wgt *= (metResSF - metResSF_err);
	      else wgt *= metResSF;
	    } // 250<MET<350
	  
	  
	    if( pfmet()>=350.0 ){
	      metResSF     = 0.928;
	      metResSF_err = 0.030;

	      if     ( histos.systematics[iSys]->id==k_metRes_ee3j_met_350_inf_Up )   wgt *= (metResSF + metResSF_err);
	      else if( histos.systematics[iSys]->id==k_metRes_ee3j_met_350_inf_Down ) wgt *= (metResSF - metResSF_err);
	      else wgt *= metResSF;
	    } // MET>350

	  } // end if nSelectedJets==3

	
	  if( nSelectedJets >= 4 ){

	    if( MT2W()<200.0){

	      if( pfmet()>=250.0 && pfmet()<325.0 ){
		metResSF     = 1.048;
		metResSF_err = 0.025;

		if     ( histos.systematics[iSys]->id==k_metRes_ge4j_lt200mt2w_met_250_325_Up )   wgt *= (metResSF + metResSF_err);
		else if( histos.systematics[iSys]->id==k_metRes_ge4j_lt200mt2w_met_250_325_Down ) wgt *= (metResSF - metResSF_err);
		else wgt *= metResSF;
	      } // 250<MET<325

	      if( pfmet()>=325.0 ){
		metResSF     = 0.944;
		metResSF_err = 0.029;

		if     ( histos.systematics[iSys]->id==k_metRes_ge4j_lt200mt2w_met_325_inf_Up )   wgt *= (metResSF + metResSF_err);
		else if( histos.systematics[iSys]->id==k_metRes_ge4j_lt200mt2w_met_325_inf_Down ) wgt *= (metResSF - metResSF_err);
		else wgt *= metResSF;
	      } // MET>325
 
	    }  // end if MT2W<200

	    else{

	      if( pfmet()>=250.0 && pfmet()<350.0 ){
		metResSF     = 1.050;
		metResSF_err = 0.021;
	      
		if     ( histos.systematics[iSys]->id==k_metRes_ge4j_ge200mt2w_met_250_350_Up )   wgt *= (metResSF + metResSF_err);
		else if( histos.systematics[iSys]->id==k_metRes_ge4j_ge200mt2w_met_250_350_Down ) wgt *= (metResSF - metResSF_err);
		else wgt *= metResSF;
	      } // 250<MET<350
	  
	      if( pfmet()>=350.0 && pfmet()<450.0 ){
		metResSF     = 0.910;
		metResSF_err = 0.051;
	      
		if     ( histos.systematics[iSys]->id==k_metRes_ge4j_ge200mt2w_met_350_450_Up )   wgt *= (metResSF + metResSF_err);
		else if( histos.systematics[iSys]->id==k_metRes_ge4j_ge200mt2w_met_350_450_Down ) wgt *= (metResSF - metResSF_err);
		else wgt *= metResSF;
	      } // 350<MET<450
	  
	  
	      if( pfmet()>=450.0 ){
		metResSF     = 0.924;
		metResSF_err = 0.063;

		if     ( histos.systematics[iSys]->id==k_metRes_ge4j_ge200mt2w_met_450_inf_Up )   wgt *= (metResSF + metResSF_err);
		else if( histos.systematics[iSys]->id==k_metRes_ge4j_ge200mt2w_met_450_inf_Down ) wgt *= (metResSF - metResSF_err);
		else wgt *= metResSF;
	      } // MET>450
	    	    
	    } // end if MT2W>=200

	  } // end if nSelectedJets>=4
	} // end if not data		



	if(isNominal){
	  nEvents_pass_selection++;
	  nEvents_pass_selection_wgt+=wgt;

	  if( isElEl){
	    nEvents_pass_selection_elel++;
	    nEvents_pass_selection_elel_wgt+=wgt;
	  }
	  if( isElMu ){
	    nEvents_pass_selection_elmu++;
	    nEvents_pass_selection_elmu_wgt+=wgt;
	  }
	  if( isMuMu ){
	    nEvents_pass_selection_mumu++;
	    nEvents_pass_selection_mumu_wgt+=wgt;
	  }
	  
	} // end if nominal
	
	
	
	//
	// Fill weights histos
	//

	// bTag SF
	if( applyBtagSFs && !is_data() ){
	  if (histos.systematics[iSys]->id==k_bTagEffHFUp) h_wgt_btag_hf_up->Fill( weight_btagsf_heavy_UP, scale1fb_reCalc*lumi );
	  else if(histos.systematics[iSys]->id==k_bTagEffHFDown) h_wgt_btag_hf_dn->Fill( weight_btagsf_heavy_DN, scale1fb_reCalc*lumi );
	  else if(histos.systematics[iSys]->id==k_bTagEffLFUp) h_wgt_btag_lf_up->Fill( weight_btagsf_light_UP, scale1fb_reCalc*lumi );
	  else if(histos.systematics[iSys]->id==k_bTagEffLFDown) h_wgt_btag_lf_dn->Fill( weight_btagsf_light_DN, scale1fb_reCalc*lumi );
	  else h_wgt_btag->Fill( weight_btagsf, scale1fb_reCalc*lumi );
	}
	
	// lep SF
	if( applyLepSFs && !is_data() ){
	  if(histos.systematics[iSys]->id==k_lepSFUp) h_wgt_lepSF_up->Fill( lepSF_Up, scale1fb_reCalc*lumi );
	  else if(histos.systematics[iSys]->id==k_lepSFDown) h_wgt_lepSF_dn->Fill( lepSF_Dn, scale1fb_reCalc*lumi );
	  else h_wgt_lepSF->Fill( lepSF, scale1fb_reCalc*lumi );
	}
	
	// top pT 
	if( applyTopPtSFs && !is_data() ){
	  if(histos.systematics[iSys]->id==k_topPtSFUp) h_wgt_topPtSF_up->Fill( ((wgt_topPt-1)*2 + 1), scale1fb_reCalc*lumi );
	  else if(histos.systematics[iSys]->id==k_topPtSFDown) h_wgt_topPtSF_dn->Fill( 1.0, scale1fb_reCalc*lumi );
	  else h_wgt_topPtSF->Fill( wgt_topPt, scale1fb_reCalc*lumi );
	}
	if( applyTopPtUnc && !is_data() ){
	  if(histos.systematics[iSys]->id==k_topPtSFUp) h_wgt_topPtSF_up->Fill( wgt_topPt, scale1fb_reCalc*lumi );
	  else if(histos.systematics[iSys]->id==k_topPtSFDown) h_wgt_topPtSF_dn->Fill( 1.0, scale1fb_reCalc*lumi );
	  else h_wgt_topPtSF->Fill( 1.0, scale1fb_reCalc*lumi );
	}
	

	//
	// Get hard system pT
	//
	double genSysPt = 0.0;
	double genSysM  = 0.0;
	TLorentzVector genSystem( 0.0, 0.0, 0.0, 0.0 );
	if( !is_data() && && nTaggedJets_med>=1 ){
	  if(isTTbar){
	    for(int iGen=0; iGen<(int)gents_p4().size(); iGen++){
	      //if( !gents_isHardProcess().at(iGen) ) continue;
	      if( !gents_isLastCopy().at(iGen) ) continue;
	      TLorentzVector temp( 0.0, 0.0, 0.0, 0.0 );
	      temp.SetPxPyPzE( gents_p4().at(iGen).Px(), gents_p4().at(iGen).Py(), gents_p4().at(iGen).Pz(), gents_p4().at(iGen).E() );
	      genSystem += temp;
	    }
	  }

	  if(isSingleT){
	    for(int iGen=0; iGen<(int)gents_p4().size(); iGen++){
	      //if( !gents_isHardProcess().at(iGen) ) continue;
	      if( !gents_isLastCopy().at(iGen) ) continue;
	      TLorentzVector temp( 0.0, 0.0, 0.0, 0.0 );
	      temp.SetPxPyPzE( gents_p4().at(iGen).Px(), gents_p4().at(iGen).Py(), gents_p4().at(iGen).Pz(), gents_p4().at(iGen).E() );
	      genSystem += temp;
	    }

	    for(int iGen=0; iGen<(int)genbosons_p4().size(); iGen++){
	      if( abs(genbosons_id().at(iGen))!=24 ) continue;
	      if( genbosons_isfromt().at(iGen) ) continue;
	      //if( !genbosons_isHardProcess().at(iGen) ) continue;
	      if( !genbosons_isLastCopy().at(iGen) ) continue;
	      TLorentzVector temp( 0.0, 0.0, 0.0, 0.0 );
	      temp.SetPxPyPzE( genbosons_p4().at(iGen).Px(), genbosons_p4().at(iGen).Py(), genbosons_p4().at(iGen).Pz(), genbosons_p4().at(iGen).E() );
	      genSystem += temp;
	    }
	  }

	  genSysPt = genSystem.Pt();
	  genSysM  = genSystem.M();

	  h_gen_met_vs_sysPt->Fill( std::min(genSysPt, sysPt_max), std::min((double)genmet(),met_max), wgt );
	  h_gen_met_vs_sysM->Fill( std::min(genSysM, sysM_max), std::min((double)genmet(),met_max), wgt );
	
	}

	double recoSysPt = 0.0;
	TLorentzVector recoSystem( 0.0, 0.0, 0.0, 0.0 );
	TLorentzVector tempLV( 0.0, 0.0, 0.0, 0.0 );

	if( nSelectedJets==2 && nTaggedJets_med==2 ){
	  tempLV.SetPxPyPzE( lep1_p4().Px(), lep1_p4().Py(), lep1_p4().Pz(), lep1_p4().E() );
	  recoSystem += tempLV;
	  
	  tempLV.SetPxPyPzE( lep2_p4().Px(), lep2_p4().Py(), lep2_p4().Pz(), lep2_p4().E() );
	  recoSystem += tempLV;
	 
	  for(int iJet=0; iJet<(int)selJets_idx.size(); iJet++){
	    tempLV.SetPxPyPzE( ak4pfjets_p4().at(selJets_idx[iJet]).Px(), ak4pfjets_p4().at(selJets_idx[iJet]).Py(), ak4pfjets_p4().at(selJets_idx[iJet]).Pz(), ak4pfjets_p4().at(selJets_idx[iJet]).E() );
	    recoSystem += tempLV;
	  }
	  h_reco_emu2b_pt->Fill( std::min((double)recoSystem.Pt(),sysPt_max), wgt );
	}
      


	
	//
	// Determine Signal Region Category
	//
	std::vector<int> cat_idx;
	
	
	// Baseline
	for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  if(k_baseline == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	}
	
	
	// nJets==2 && nTags>=0
	if( nSelectedJets==2 && nTaggedJets_med>=0 ){
	  for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	    //if(k_ee2j_ge0t == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  }
	}

	// nJets==2 && nTags==0
	if( nSelectedJets==2 && nTaggedJets_med==0 ){
	  for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	    //if(k_ee2j_ee0t == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  }
	}

	// nJets==2 && nTags==1
	if( nSelectedJets==2 && nTaggedJets_med==1 ){
	  for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	    //if(k_ee2j_ee1t == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  }
	}
	
	// nJets==2 && nTags==2
	if( nSelectedJets==2 && nTaggedJets_med==2 ){
	  for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	    //if(k_ee2j_ee2t == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  }
	}

	// nJets>=2 && nTags>=0
	if( nSelectedJets>=2 && nTaggedJets_med>=0 ){
	  for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	    if(k_ge2j_ge0t_gt0met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  }

	  if( pfmet()>50 ){
	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      if(k_ge2j_ge0t_gt50met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }
	  }

	  if( pfmet()>100 ){
	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      if(k_ge2j_ge0t_gt100met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }
	  }

	  if( pfmet()>150 ){
	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      if(k_ge2j_ge0t_gt150met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }
	  }
	  

	  if( pfmet()>200 ){
	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      if(k_ge2j_ge0t_gt200met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }
	  }

	  if( pfmet()>250 ){
	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      //if(k_ge2j_ge0t_gt250met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }
	  }

	} // end if nJets>=2 && nTags>=0


	// nJets>=2 && nTags>=1
	if( nSelectedJets>=2 && nTaggedJets_med>=1 ){
	  for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	    if(k_ge2j_ge1t_gt0met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  }

	  if( pfmet()>50 ){
	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      if(k_ge2j_ge1t_gt50met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }
	  }

	  if( pfmet()>100 ){
	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      if(k_ge2j_ge1t_gt100met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }
	  }

	  if( pfmet()>150 ){
	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      if(k_ge2j_ge1t_gt150met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }
	  }
	  

	  if( pfmet()>200 ){
	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      if(k_ge2j_ge1t_gt200met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }
	  }

	  if( pfmet()>250 ){
	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      //if(k_ge2j_ge1t_gt250met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }
	  }

	} // end if nJets>=2 && nTags>=1



	// nJets>=2 && nTags>=2
	if( nSelectedJets>=2 && nTaggedJets_med>=2 ){
	  for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	    if(k_ge2j_ge2t_gt0met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  }

	  if( pfmet()>50 ){
	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      if(k_ge2j_ge2t_gt50met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }
	  }

	  if( pfmet()>100 ){
	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      if(k_ge2j_ge2t_gt100met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }
	  }

	  if( pfmet()>150 ){
	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      if(k_ge2j_ge2t_gt150met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }
	  }
	  

	  if( pfmet()>200 ){
	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      if(k_ge2j_ge2t_gt200met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }
	  }

	  if( pfmet()>250 ){
	    for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	      //if(k_ge2j_ge2t_gt250met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	    }
	  }

	} // end if nJet>=2 && nTags>=2



	// nJets>=3 && nTags>=0
	//if( nSelectedJets>=3 && nTaggedJets_med>=0 ){
	//for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	//  if(k_ge3j_ge0t_gt0met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	//}

	  //if( pfmet()>50 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge0t_gt50met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}
	  
	  //if( pfmet()>100 ){
	  //  for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //    if(k_ge3j_ge0t_gt100met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}

	  //if( pfmet()>150 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge0t_gt150met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}
	  

	  //if( pfmet()>200 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge0t_gt200met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}

	  //if( pfmet()>250 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge0t_gt250met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}
	
	//} // end if nJets>=3 && nTags>=0


	// nJets>=3 && nTags>=1
	//if( nSelectedJets>=3 && nTaggedJets_med>=1 ){
	//for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	//  if(k_ge3j_ge1t_gt0met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	//}

	  //if( pfmet()>50 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge1t_gt50met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}

	  //if( pfmet()>100 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge1t_gt100met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}

	  //if( pfmet()>150 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge1t_gt150met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}
	  

	  //if( pfmet()>200 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge1t_gt200met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}

	  //if( pfmet()>250 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge1t_gt250met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}

	//} // end if nJets>=3 && nTags>=1



	// nJets>=3 && nTags>=2
	//if( nSelectedJets>=3 && nTaggedJets_med>=2 ){
	//for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	//  if(k_ge3j_ge2t_gt0met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	//}

	  //if( pfmet()>50 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge2t_gt50met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}

	  //if( pfmet()>100 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge2t_gt100met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}

	  //if( pfmet()>150 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge2t_gt150met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}
	  

	  //if( pfmet()>200 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge2t_gt200met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}

	  //if( pfmet()>250 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge2t_gt250met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}

	//} // end if nJet>=2 && nTags>=2



	// nJets>=3 && nTags>=3
	//if( nSelectedJets>=3 && nTaggedJets_med>=3 ){
	//for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	//  if(k_ge3j_ge3t_gt0met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	//}

	  //if( pfmet()>50 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge3t_gt50met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}

	  //if( pfmet()>100 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge3t_gt100met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}

	  //if( pfmet()>150 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge3t_gt150met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}
	  

	  //if( pfmet()>200 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge3t_gt200met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}

	  //if( pfmet()>250 ){
	  //for(int iCat=0; iCat<(int)histos.categories.size(); iCat++){
	  //  if(k_ge3j_ge3t_gt250met == histos.categories[iCat]->id) cat_idx.push_back(iCat);
	  //}
	  //}

	//} // end if nJet>=3 && nTags>=3


	if(isData && isNominal && nSelectedJets>=2){
	  fprintf(evtList,"run=%d  ls=%d  evt=%d  met=%f  metPhi=%f  mt=%f  minDphi=%f  MT2W=%f  lep1Pt=%f  lep1Eta=%f  lep1Phi=%f  lep2Pt=%f  lep2Eta=%f  lep2Phi=%f  PassTrkVeto=%d  PassTauVeto=%d  nJets=%d  nBTags=%d  jet1Pt=%f  jet2Pt=%f \n", run(), ls(), evt(), pfmet(), pfmet_phi(), mt_met_lep(), mindphi_met_j1_j2(), MT2W(), lep1_p4().Pt(), lep1_p4().Eta(), lep1_p4().Phi(), lep2_p4().Pt(), lep2_p4().Eta(), lep2_p4().Phi(), PassTrackVeto_v3(), PassTauVeto(), nSelectedJets, nTaggedJets_med, ak4pfjets_pt()[selJets_idx[0]], ak4pfjets_pt()[selJets_idx[1]]); 
	  
	}

	      

	//
	// Compute any values for histos, on the fly
	//
	bool ee2tagEvent=false;
	double ttbar_px = 0.0;
	double ttbar_py = 0.0;
	double ttbar_pt = 0.0;
	if( nTaggedJets_med==2 ){
	  ee2tagEvent=true;

	  ttbar_px = lep1_p4().Px() + lep2_p4().Px();
	  ttbar_py = lep1_p4().Py() + lep2_p4().Py();
	  
	  for(int iJet=0; iJet<(int)selJets_idx.size(); iJet++){
	    if( ak4pfjets_CSV().at(selJets_idx[iJet]) > CSV_MED_WP ){
	      ttbar_px += ak4pfjets_p4().at(selJets_idx[iJet]).Px();
	      ttbar_py += ak4pfjets_p4().at(selJets_idx[iJet]).Py();
	    } // end if jet is bTagged
	  } // end if jet is selected

	  ttbar_px += pfmet()*cos(pfmet_phi());
	  ttbar_py += pfmet()*sin(pfmet_phi());

	  ttbar_pt = sqrt( pow(ttbar_px,2) + pow(ttbar_py,2) );
	}

	if( is_data() && nTaggedJets_med>=1 && diLepton_TLV.Pt()>200.0 && diLepton_TLV.Pt()<250.0 ){
	  //cout << "Run = " << run() << ", ls = " << ls() << ", evt = " << evt() << endl;
	}

	//
	// diNuetrino pT
	//
	TLorentzVector diNu_TLV(0.0, 0.0, 0.0, 0.0);
	if(!is_data()){
	  for(int iGen=0; iGen<(int)gennus_p4().size(); iGen++){
	    if( abs(gennus_id().at(iGen))!=12 &&
		abs(gennus_id().at(iGen))!=14 &&
		abs(gennus_id().at(iGen))!=16    ) continue;
	    if( !gennus_isLastCopy().at(iGen) ) continue;
	    if( !gennus_isHardProcess().at(iGen) ) continue;
	    TLorentzVector temp( 0.0, 0.0, 0.0, 0.0 );
	    temp.SetPxPyPzE( gennus_p4().at(iGen).Px(), gennus_p4().at(iGen).Py(), gennus_p4().at(iGen).Pz(), gennus_p4().at(iGen).E() );
	    diNu_TLV += temp;
	  }
	}

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
	    histos.var_diLep_pt->histo_[hist_idx]->Fill( diLepton_TLV.Pt(), wgt );
	    histos.var_met->histo_[hist_idx]->Fill( pfmet(), wgt );

	    histos.var_nJets->histo_[hist_idx]->Fill( nSelectedJets, wgt );

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
	      if(histos.systematics[iSys]->id==k_topPtSFUp) histos.var_yield_only_topPtSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi*((wgt_topPt-1)*2 + 1) );
	      else if(histos.systematics[iSys]->id==k_topPtSFDown) histos.var_yield_only_topPtSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi*1.0 );
	      else histos.var_yield_only_topPtSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi*wgt_topPt );
	    }
	    if( applyTopPtUnc && !is_data() ){
	      if(histos.systematics[iSys]->id==k_topPtSFUp) histos.var_yield_only_topPtSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi*wgt_topPt );
	      else if(histos.systematics[iSys]->id==k_topPtSFDown) histos.var_yield_only_topPtSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi*1.0 );
	      else histos.var_yield_only_topPtSF->histo_[hist_idx]->Fill( 1.0, scale1fb_reCalc*lumi*1.0 );
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


	    if(!is_data()){
	      histos.var_genDiNuPt->histo_[hist_idx]->Fill( diNu_TLV.Pt(), wgt );
	      if(mt_met_lep()>150) histos.var_genDiNuPt_highMT->histo_[hist_idx]->Fill( diNu_TLV.Pt(), wgt );
	      else histos.var_genDiNuPt_lowMT->histo_[hist_idx]->Fill( diNu_TLV.Pt(), wgt );
	    }

	    if(mt_met_lep()>150) histos.var_met_highMT->histo_[hist_idx]->Fill( pfmet(), wgt );
	    else histos.var_met_lowMT->histo_[hist_idx]->Fill( pfmet(), wgt );
	    if(isTTbar && is_2lep && nSelectedJets==3) histos.var_met_withK3K4->histo_[hist_idx]->Fill( pfmet(), wgt*1.10 );
	    else if(isTTbar && is_2lep && nSelectedJets>=4) histos.var_met_withK3K4->histo_[hist_idx]->Fill( pfmet(), wgt*0.94 );
	    else histos.var_met_withK3K4->histo_[hist_idx]->Fill( pfmet(), wgt );

	    /*
	    histos.var_nGenLep->histo_[hist_idx]->Fill( nGenPromptLep, wgt );
	    histos.var_nGenNu->histo_[hist_idx]->Fill( nGenPromptNu, wgt );

	    
	    //histos.var_nJets->histo_[hist_idx]->Fill( nSelectedJets, wgt );
	    //histos.var_nTags_loose->histo_[hist_idx]->Fill( nTaggedJets_loose, wgt );
	    histos.var_nTags_med->histo_[hist_idx]->Fill( nTaggedJets_med, wgt );
	    //histos.var_nTags_tight->histo_[hist_idx]->Fill( nTaggedJets_tight, wgt );

	    //histos.var_mt->histo_[hist_idx]->Fill( mt_met_lep(), wgt );
	    //histos.var_minDPhi->histo_[hist_idx]->Fill( mindphi_met_j1_j2(), wgt );
	    
	    //if( MT2W()<=200 ) histos.var_met_lowDM->histo_[hist_idx]->Fill( pfmet(), wgt );
	    //if( MT2W()>200  ) histos.var_met_highDM->histo_[hist_idx]->Fill( pfmet(), wgt );
	    histos.var_met_phi->histo_[hist_idx]->Fill( pfmet_phi(), wgt );

	    //histos.var_mt2w->histo_[hist_idx]->Fill( MT2W(), wgt );

	    //histos.var_hadTopChi2->histo_[hist_idx]->Fill( hadronic_top_chi2(), wgt );
	    //histos.var_htRatio->histo_[hist_idx]->Fill( ak4_htratiom(), wgt );

	    if( lep1_is_mu() ){
	      histos.var_mu_pt->histo_[hist_idx]->Fill( lep1_pt(), wgt );
	      histos.var_mu_eta->histo_[hist_idx]->Fill( lep1_eta(), wgt );
	      //histos.var_mu_phi->histo_[hist_idx]->Fill( lep1_phi(), wgt );
	    }
	    if( lep2_is_mu() ){
	      histos.var_mu_pt->histo_[hist_idx]->Fill( lep2_pt(), wgt );
	      histos.var_mu_eta->histo_[hist_idx]->Fill( lep2_eta(), wgt );
	      //histos.var_mu_phi->histo_[hist_idx]->Fill( lep2_phi(), wgt );
	    }
	    if( lep1_is_el() ){
	      histos.var_el_pt->histo_[hist_idx]->Fill( lep1_pt(), wgt );
	      histos.var_el_eta->histo_[hist_idx]->Fill( lep1_eta(), wgt );
	      //histos.var_el_phi->histo_[hist_idx]->Fill( lep1_phi(), wgt );
	    }
	    if( lep2_is_el() ){
	      histos.var_el_pt->histo_[hist_idx]->Fill( lep2_pt(), wgt );
	      histos.var_el_eta->histo_[hist_idx]->Fill( lep2_eta(), wgt );
	      //histos.var_el_phi->histo_[hist_idx]->Fill( lep2_phi(), wgt );
	    }
	    histos.var_lep1_pt->histo_[hist_idx]->Fill( lep1_pt(), wgt );
	    //histos.var_lep1_eta->histo_[hist_idx]->Fill( lep1_eta(), wgt );
	    //histos.var_lep1_phi->histo_[hist_idx]->Fill( lep1_phi(), wgt );

	    histos.var_lep2_pt->histo_[hist_idx]->Fill( lep2_pt(), wgt );
	    //histos.var_lep2_eta->histo_[hist_idx]->Fill( lep2_eta(), wgt );
	    //histos.var_lep2_phi->histo_[hist_idx]->Fill( lep2_phi(), wgt );

	    histos.var_diLep_mass->histo_[hist_idx]->Fill( diLepton_TLV.M(), wgt );
	    //histos.var_diLep_pt->histo_[hist_idx]->Fill( diLepton_TLV.Pt(), wgt );
	    
	    if( lep1_is_mu() ) histos.var_diLep_pt_mue->histo_[hist_idx]->Fill( diLepton_TLV.Pt(), wgt );
	    if( lep1_is_el() ) histos.var_diLep_pt_emu->histo_[hist_idx]->Fill( diLepton_TLV.Pt(), wgt );
	    
	    histos.var_deltaPt_lep1_lep2->histo_[hist_idx]->Fill( lep1_pt()-lep2_pt(), wgt );
	    histos.var_deltaPhi_lep1_lep2->histo_[hist_idx]->Fill( acos(cos(lep1_phi()-lep2_phi())), wgt );

	    for(int iJet=0; iJet<(int)selJets_idx.size(); iJet++){
	     
	      histos.var_jet_pt->histo_[hist_idx]->Fill( ak4pfjets_p4().at(selJets_idx[iJet]).Pt(), wgt );
	      histos.var_jet_csv->histo_[hist_idx]->Fill( ak4pfjets_CSV().at(selJets_idx[iJet]), wgt );

	      if(iJet==0){
		histos.var_jet_1_pt->histo_[hist_idx]->Fill( ak4pfjets_p4().at(selJets_idx[iJet]).Pt(), wgt );
	      }
	      if(iJet==1){
		histos.var_jet_2_pt->histo_[hist_idx]->Fill( ak4pfjets_p4().at(selJets_idx[iJet]).Pt(), wgt );
	      }

	    } // end loop over jets


	    if(ee2tagEvent){
	      histos.var_ttbar_px->histo_[hist_idx]->Fill( ttbar_px, wgt );
	      histos.var_ttbar_py->histo_[hist_idx]->Fill( ttbar_py, wgt );
	      histos.var_ttbar_pt->histo_[hist_idx]->Fill( ttbar_pt, wgt );
	      }
	    */

	  } // end loop over categories
	} // end loop over classifications
	
	
      } // end loop over systematics
      
    } // end loop over this file in chain

 
    // Clean Up
    delete tree;
    file.Close();
    
  }

  if ( nEventsChain != nEventsTotal ) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }


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
  cout << "===================================================================================" << endl;
  cout << "  Selection Cutflow:  diLepton CR " << endl;
  cout << "     nEvents in Chain                                  = " << nEventsChain << endl;
  cout << "     nEvents pass duplicate removal                    = " << nEvents_pass_duplicate_removal << endl;
  cout << "     nEvents Pass All Data Filters (wgt)               = " << nEvents_pass_dataFilter << " (" << nEvents_pass_dataFilter_wgt << "),  Eff = " << (double)nEvents_pass_dataFilter/(double)nEvents_pass_duplicate_removal << endl;
  cout << "     nEvents Pass lep1 is Good Leptons (wgt)           = " << nEvents_pass_1GoodLep << " (" <<  nEvents_pass_1GoodLep_wgt << "), Eff = " << (double)nEvents_pass_1GoodLep/(double)nEvents_pass_dataFilter << endl;

  cout << "     nEvents Pass ==2 Good Leptons (wgt)               = " << nEvents_pass_nGoodLep << " (" << nEvents_pass_nGoodLep_wgt << "),  Eff = " << (double)nEvents_pass_nGoodLep_wgt/nEvents_pass_dataFilter_wgt << endl;
  cout << "     nEvents Pass Opposite Sign Charge Veto (wgt)      = " << nEvents_pass_oppSignChargeLeps << " (" << nEvents_pass_oppSignChargeLeps_wgt << "),  Eff = " << (double)nEvents_pass_oppSignChargeLeps_wgt/nEvents_pass_nGoodLep_wgt << endl;
  cout << "     nEvents Pass Lep Flavour Veto (wgt)               = " << nEvents_pass_leptonFlavour << " (" << nEvents_pass_leptonFlavour_wgt << "),  Eff = " << (double)nEvents_pass_leptonFlavour_wgt/nEvents_pass_oppSignChargeLeps_wgt << endl;
  cout << "     nEvents Pass Trigger (wgt)                        = " << nEvents_pass_trigger << " (" << nEvents_pass_trigger_wgt << "),  Eff = " << (double)nEvents_pass_trigger_wgt/nEvents_pass_leptonFlavour_wgt << endl;
  cout << "     nEvents Pass diLepton Mass Cut (wgt)              = " << nEvents_pass_diLepMass << " (" << nEvents_pass_diLepMass_wgt << "),  Eff = " << (double)nEvents_pass_diLepMass_wgt/nEvents_pass_trigger_wgt << endl;
  cout << "     nEvents Pass Z Mass Window (wgt)                  = " << nEvents_pass_zMassWindow << " (" << nEvents_pass_zMassWindow_wgt << "),  Eff = " << (double)nEvents_pass_zMassWindow_wgt/nEvents_pass_diLepMass_wgt << endl;
  cout << "     nEvents Pass >=1 Selected Jet                     = " << nEvents_pass_nJets << " (" << nEvents_pass_nJets_wgt << "),  Eff = " << (double)nEvents_pass_nJets_wgt/nEvents_pass_zMassWindow_wgt << endl;
  cout << "     nEvents Pass >=1 bTagged Jet, CSV Medium WP (wgt) = " << nEvents_pass_nBTags << " (" << nEvents_pass_nBTags_wgt << "),  Eff = " << (double)nEvents_pass_nBTags_wgt/nEvents_pass_nJets_wgt << endl;
  cout << "     nEvents Pass MET>50 (wgt)                         = " << nEvents_pass_met << " (" << nEvents_pass_met_wgt << "),  Eff = " << (double)nEvents_pass_met_wgt/nEvents_pass_nBTags_wgt << endl;
  cout << "     nEvents Pass Selection (wgt)                       = " << nEvents_pass_selection << " (" << nEvents_pass_selection_wgt << "),  Total Efficiency = " << (double)nEvents_pass_selection/(double)nEvents_pass_duplicate_removal << endl;
  cout << "     nEvents Pass Selection, ee (wgt)                   = " << nEvents_pass_selection_elel << " (" << nEvents_pass_selection_elel_wgt << "),  Total Efficiency = " << (double)nEvents_pass_selection_elel/(double)nEvents_pass_duplicate_removal << endl;
  cout << "     nEvents Pass Selection, emu (wgt)                  = " << nEvents_pass_selection_elmu << " (" << nEvents_pass_selection_elmu_wgt << "),  Total Efficiency = " << (double)nEvents_pass_selection_elmu/(double)nEvents_pass_duplicate_removal << endl;
  cout << "     nEvents Pass Selection, mumu (wgt)                 = " << nEvents_pass_selection_mumu << " (" << nEvents_pass_selection_mumu_wgt << "),  Total Efficiency = " << (double)nEvents_pass_selection_mumu/(double)nEvents_pass_duplicate_removal << endl;
  cout << "===================================================================================" << endl;
  cout << endl;
  cout << endl;

  cout << "     nEvents pass MET trigger and diLep Selection (wgt)             = " << nEvents_pass_metTrigger_diLepSel << " (" << nEvents_pass_metTrigger_diLepSel_wgt << ")" << endl;
  cout << "     nEvents pass MET trigger, diLep Selection, diLep Trigger (wgt) = " << nEvents_pass_metTrigger_diLepSel_diLepTrigger << " (" << nEvents_pass_metTrigger_diLepSel_diLepTrigger_wgt << ")" << endl;

  cout << "     DiLepton Trigger Efficiency = " <<(double)nEvents_pass_metTrigger_diLepSel_diLepTrigger/nEvents_pass_metTrigger_diLepSel << endl;

  cout << "===================================================================================" << endl;
  cout << endl;
  cout << endl;

  cout << "     MAX RUN              = " << max_run << endl;
  cout << "     MAX LUMI, IN MAX RUN = " << max_lumi << endl;

  cout << "===================================================================================" << endl;
  cout << endl;
  cout << endl;


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
  // return
  //
  bmark->Stop("benchmark");
  cout << endl;
  cout << nEventsTotal << " Events Processed" << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:	" << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:	" << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  cout << "===================================================================================" << endl;
  cout << endl;


  delete bmark;
  return 0;
}
