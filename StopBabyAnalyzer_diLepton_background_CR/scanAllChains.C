 {
   
   gSystem->Load("../../CORE/CMS3_CORE.so");
   gROOT->ProcessLine(".L stopBabyLooper_diLepton_background_CR.C++");


   std::vector<TString> inDirs;
   std::vector<TString> outDirs;
   
   // Nominal
   //TString input_dir_nom  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/Skims_CR_2lep__20151211/";  
   //TString input_dir_nom  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/";  
   TString input_dir_nom  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v9__20160127/merged_files/Skims_CR_2lep__20160202/";  
   //TString input_dir_nom  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v9__20160127/merged_files/";  
   TString output_dir_nom = "Histos/Nominal/";
   
   inDirs.push_back(input_dir_nom);
   outDirs.push_back(output_dir_nom);
   
   // JESup
   //TString input_dir_jesUp  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies_JECup__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/Skims_CR_2lep__JECup__20151211/";  
   TString input_dir_jesUp  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies_JECup__CMS3_V070411__BabyMaker_V0704X_v9__20160127/merged_files/";  
   TString output_dir_jesUp = "Histos/JESup/";
   
   inDirs.push_back(input_dir_jesUp);
   outDirs.push_back(output_dir_jesUp);
   
   // JESdown
   //TString input_dir_jesDn  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies_JECdown__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/Skims_CR_2lep__JECdown__20151211/";  
   TString input_dir_jesDn  = "/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies_JECdown__CMS3_V070411__BabyMaker_V0704X_v9__20160127/merged_files/";
   TString output_dir_jesDn = "Histos/JESdown/";
   
   inDirs.push_back(input_dir_jesDn);
   outDirs.push_back(output_dir_jesDn);
   
   
   
   TChain *ch;
   
   TString input_name  = "";
   TString output_name = "";
   
   //
   // Data
   //
   
   output_name = output_dir_nom+"histos__data_singleEl_singleMu_2015CD_25ns.root";
   ch = new TChain("t");
   
   ch->Add(input_dir_nom+"data_met_2015D_promptRecoV4_25ns*.root");
   ch->Add(input_dir_nom+"data_met_2015D_05Oct2015_v1_25ns*.root");
   ch->Add(input_dir_nom+"data_met_2015C_25ns*.root");
  
   ch->Add(input_dir_nom+"data_single_electron_2015D_promptRecoV4_25ns*.root");
   ch->Add(input_dir_nom+"data_single_electron_2015D_05Oct2015_v1_25ns*.root");
   //ch->Add(input_dir_nom+"data_single_electron_2015D_promptRecoV3_25ns*.root");
   ch->Add(input_dir_nom+"data_single_electron_2015C_25ns*.root");

   ch->Add(input_dir_nom+"data_single_muon_2015D_promptRecoV4_25ns*.root");
   ch->Add(input_dir_nom+"data_single_muon_2015D_05Oct2015_v1_25ns*.root");
   //ch->Add(input_dir_nom+"data_single_muon_2015D_promptRecoV3_25ns*.root");
   ch->Add(input_dir_nom+"data_single_muon_2015C_25ns*.root");
   
   /*
   ch->Add("/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/data_met_2015D_promptRecoV4_25ns*.root");
   ch->Add("/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/data_met_2015D_05Oct2015_v1_25ns*.root");
   ch->Add("/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/data_met_2015C_25ns*.root");
  
   ch->Add("/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/data_single_electron_2015D_promptRecoV4_25ns*.root");
   ch->Add("/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/data_single_electron_2015D_05Oct2015_v1_25ns*.root");
   //ch->Add("/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/data_single_electron_2015D_promptRecoV3_25ns*.root");
   ch->Add("/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/data_single_electron_2015C_25ns*.root");

   ch->Add("/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/data_single_muon_2015D_promptRecoV4_25ns*.root");
   ch->Add("/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/data_single_muon_2015D_05Oct2015_v1_25ns*.root");
   //ch->Add("/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/data_single_muon_2015D_promptRecoV3_25ns*.root");
   ch->Add("/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/data_single_muon_2015C_25ns*.root");
   */
   
   stopBabyLooper_diLepton_background_CR(ch, output_name); 
   ch->~TChain();
   
   
   //
   // Loop over sets of babies to analze
   //
   bool doMC = true;
   if(doMC){
     for(int iBaby=0; iBaby<(int)inDirs.size(); iBaby++){

       TString input_dir  = inDirs[iBaby];
       TString output_dir = outDirs[iBaby];
     

  
       //
       // Signal samples
       //

       //
       // T2tt
       //
       /*
       // T2tt, mStop 850, mLSP 100
       input_name  = input_dir+"T2tt_2J_mStop_850_mLSP_100_25ns*.root";
       //input_name  = "/home/users/jgwood/Stop_1Lepton/phys14Samples_cmssw74x_babyMaker/CMSSW_7_2_0/src/StopAnalysis/StopBabyMaker/stop_850_100.root";
       output_name = output_dir+"histos__T2tt_2J_mStop_850_mLSP_100_25ns.root";
       //ch = new TChain("t");
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name);
       ch->~TChain();   

       // T2tt, mStop 650, mLSP 325
       input_name  = input_dir+"T2tt_2J_mStop_650_mLSP_325_25ns*.root";
       //input_name  = "/home/users/jgwood/Stop_1Lepton/phys14Samples_cmssw74x_babyMaker/CMSSW_7_2_0/src/StopAnalysis/StopBabyMaker/stop_650_325.root";
       output_name = output_dir+"histos__T2tt_2J_mStop_650_mLSP_325_25ns.root";
       ch = new TChain("t");
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name);
       ch->~TChain();   

       // T2tt, mStop 500, mLSP 325
       input_name  = input_dir+"T2tt_2J_mStop_500_mLSP_325_25ns*.root";
       //input_name  = "/home/users/jgwood/Stop_1Lepton/phys14Samples_cmssw74x_babyMaker/CMSSW_7_2_0/src/StopAnalysis/StopBabyMaker/stop_500_325.root";
       output_name = output_dir+"histos__T2tt_2J_mStop_500_mLSP_325_25ns.root";
       ch = new TChain("t");
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name);
       ch->~TChain();   

       // T2tt, mStop 425, mLSP 325
       input_name  = input_dir+"T2tt_2J_mStop_425_mLSP_325_25ns*.root";
       //input_name  = "/home/users/jgwood/Stop_1Lepton/phys14Samples_cmssw74x_babyMaker/CMSSW_7_2_0/src/StopAnalysis/StopBabyMaker/stop_425_325.root";
       output_name = output_dir+"histos__T2tt_2J_mStop_425_mLSP_325_25ns.root";
       ch = new TChain("t");
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name);
       ch->~TChain();   


       //
       // T6 bbWW
       //
   
       // T6 bbWW, mCh 400, mLSP 50
       //input_name  = input_dir+"T6bbWW_mStop425_mCh400_mLSP50.root";
       //output_name = output_dir+"histos__T6bbWW_mStop425_mCh400_mLSP50.root";
       //ch = new TChain("t"); 
       //ch->Add(input_name);
       //stopBabyLooper_diLepton_background_CR(ch, output_name); 
       //ch->~TChain();
  
       */

    
       //
       // Background samples
       //
    
       //
       // ttbar
       //
       /*
       // ttbar madgraph pythia8, singleLep from t
       input_name  = input_dir+"ttbar_singleLeptFromT_madgraph_pythia8_25ns*.root";
       output_name = output_dir+"histos__ttbar_singleLeptFromT_madgraph_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // ttbar madgraph pythia8, singleLep from t, ext1
       input_name  = input_dir+"ttbar_singleLeptFromT_madgraph_pythia8_ext1_25ns*.root";
       output_name = output_dir+"histos__ttbar_singleLeptFromT_madgraph_pythia8_ext1_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // ttbar madgraph pythia8, singleLep from tbar
       input_name  = input_dir+"ttbar_singleLeptFromTbar_madgraph_pythia8_25ns*.root";
       output_name = output_dir+"histos__ttbar_singleLeptFromTbar_madgraph_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // ttbar madgraph pythia8, singleLep from tbar
       input_name  = input_dir+"ttbar_singleLeptFromTbar_madgraph_pythia8_25ns*.root";
       output_name = output_dir+"histos__ttbar_singleLeptFromTbar_madgraph_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // ttbar madgraph pythia8, singleLep from tbar, ext1
       input_name  = input_dir+"ttbar_singleLeptFromTbar_madgraph_pythia8_ext1_25ns*.root";
       output_name = output_dir+"histos__ttbar_singleLeptFromTbar_madgraph_pythia8_ext1_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // ttbar madgraph pythia8, diLepton
       input_name  = input_dir+"ttbar_diLept_madgraph_pythia8_25ns*.root";
       output_name = output_dir+"histos__ttbar_diLept_madgraph_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // ttbar madgraph pythia8, diLepton, ext1
       input_name  = input_dir+"ttbar_diLept_madgraph_pythia8_ext1_25ns*.root";
       output_name = output_dir+"histos__ttbar_diLept_madgraph_pythia8_ext1_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
       */
       
       // ttbar powheg pythia8
       input_name  = input_dir+"ttbar_powheg_pythia8_25ns*.root";
       output_name = output_dir+"histos__ttbar_powheg_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
       
       // ttbar powheg pythia8, ext3
       input_name  = input_dir+"ttbar_powheg_pythia8_ext3_25ns*.root";
       output_name = output_dir+"histos__ttbar_powheg_pythia8_ext3_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
       
       
       //
       // DYJets
       //
  
       // DYJets, m50
       input_name  = input_dir+"DYJetsToLL_m50_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__DYJetsToLL_m50_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
    
       // DYJets, m10-50
       input_name  = input_dir+"DYJetsToLL_m10To50_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__DYJetsToLL_m10to50_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
    
    
       //
       // WJets
       //
    
       // WJets -> LNu, amcnlo pythia8
       input_name  = input_dir+"WJetsToLNu_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__WJetsToLNu_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // WJets -> LNu, HT 100-200, madgraph pythia8
       input_name  = input_dir+"WJetsToLNu_HT100To200_madgraph_pythia8_25ns*.root";
       output_name = output_dir+"histos__WJetsToLNu_HT100To200_madgraph_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // WJets -> LNu, HT 200-400, madgraph pythia8
       input_name  = input_dir+"WJetsToLNu_HT200To400_madgraph_pythia8_25ns*.root";
       output_name = output_dir+"histos__WJetsToLNu_HT200To400_madgraph_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // WJets -> LNu, HT 400-600, madgraph pythia8
       input_name  = input_dir+"WJetsToLNu_HT400To600_madgraph_pythia8_25ns*.root";
       output_name = output_dir+"histos__WJetsToLNu_HT400To600_madgraph_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
    
       // WJets -> LNu, HT 600-Inf, madgraph pythia8
       input_name  = input_dir+"WJetsToLNu_HT600ToInf_madgraph_pythia8_25ns*.root";
       output_name = output_dir+"histos__WJetsToLNu_HT600ToInf_madgraph_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
  
       // WJets -> LNu, HT 600-800, madgraph pythia8
       input_name  = input_dir+"WJetsToLNu_HT600To800_madgraph_pythia8_25ns*.root";
       output_name = output_dir+"histos__WJetsToLNu_HT600To800_madgraph_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // WJets -> LNu, HT 800-1200, madgraph pythia8
       input_name  = input_dir+"WJetsToLNu_HT800To1200_madgraph_pythia8_25ns*.root";
       output_name = output_dir+"histos__WJetsToLNu_HT800To1200_madgraph_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // WJets -> LNu, HT 1200-2500, madgraph pythia8
       input_name  = input_dir+"WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns*.root";
       output_name = output_dir+"histos__WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // WJets -> LNu, HT 2500-Inf, madgraph pythia8
       input_name  = input_dir+"WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns*.root";
       output_name = output_dir+"histos__WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
    

       //
       // Single t
       //

       // Single t, s-channel, 4f, amcnlo pythia8
       input_name  = input_dir+"t_sch_4f_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__T_sch_4f_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // Single tbar, t-channel, 4f, powheg pythia8
       input_name  = input_dir+"tbar_tch_4f_powheg_pythia8_25ns*.root";
       output_name = output_dir+"histos__Tbar_tch_4f_powheg_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // Single t, t-channel, 4f, powheg pythia8
       input_name  = input_dir+"t_tch_4f_powheg_pythia8_25ns*.root";
       output_name = output_dir+"histos__T_tch_4f_powheg_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
  
       // Single tbar, tW channel, 5f, powheg pythia8
       input_name  = input_dir+"t_tbarW_5f_powheg_pythia8_25ns*.root";
       output_name = output_dir+"histos__T_tbarW_5f_powheg_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // Single t, tW channel, 5f, powheg pythia8
       input_name  = input_dir+"t_tW_5f_powheg_pythia8_25ns*.root";
       output_name = output_dir+"histos__T_tW_5f_powheg_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

    
       //
       // diBoson
       //

       // WW, pythia8
       input_name  = input_dir+"WW_pythia8_25ns*.root";
       output_name = output_dir+"histos__WW_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
    
       // WW -> 2l 2Nu, powheg
       input_name  = input_dir+"WWTo2l2Nu_powheg_25ns*.root";
       output_name  = output_dir+"histos__WW_2l2nu_powheg_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
    
       // WW -> LNu QQ, powheg
       input_name  = input_dir+"WWToLNuQQ_powheg_25ns*.root";
       output_name = output_dir+"histos__WWToLNuQQ_powheg_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
    
       // WZ, pythia8
       input_name  = input_dir+"WZ_pythia8_25ns*.root";
       output_name = output_dir+"histos__WZ_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // WZ, amcnlo pythia8
       input_name  = input_dir+"WZ_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__WZ_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // WZ -> 3L 1Nu, powheg pythia8
       input_name  = input_dir+"WZTo3LNu_powheg_pythia8_25ns*.root";
       output_name = output_dir+"histos__WZTo3LNu_powheg_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
    
       // WZ -> 2L 2Q, amcnlo pythia8
       input_name  = input_dir+"WZTo2L2Q_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__WZTo2L2Q_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // WZ -> 1LNu 2Q, amcnlo pythia8
       input_name  = input_dir+"WZTo1LNu2Q_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__WZTo1Lnu2Q_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // WZ -> 1L 3Nu, amcnlo pythia8
       input_name  = input_dir+"WZTo1L3Nu_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__WZTo1L3Nu_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();


       // ZZ, pythia8
       input_name  = input_dir+"ZZ_pythia8_25ns*.root";
       output_name = output_dir+"histos__ZZ_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // ZZ -> 4L, powheg pythia8
       input_name  = input_dir+"ZZTo4L_powheg_pythia8_25ns*.root";
       output_name = output_dir+"histos__ZZTo4L_powheg_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
  
       // ZZ -> 2L 2Q, amcnlo pythia8
       input_name  = input_dir+"ZZTo2L2Q_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__ZZTo2L2Q_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // ZZ -> 2L 2Nu, powheg pythia8
       input_name  = input_dir+"ZZTo2L2Nu_powheg_pythia8_25ns*.root";
       output_name = output_dir+"histos__ZZTo2L2Nu_powheg_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
    
       // ZZ -> 2Q 2Nu, amcnlo pythia8
       input_name  = input_dir+"ZZTo2Q2Nu_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__ZZTo2Q2Nu_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

    
       //
       // TTV
       //
    
       // TTW -> LNu, amcnlo pythia8
       input_name  = input_dir+"TTWJetsToLNu_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__TTWJetsToLNu_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // TTW -> QQ, amcnlo pythia8
       input_name  = input_dir+"TTWJetsToQQ_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__TTWJetsToQQ_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();  
    
       // TTZ -> QQ, amcnlo pythia8
       input_name  = input_dir+"TTZToQQ_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__TTZToQQ_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
    
       // TTZ -> 2L 2Nu, amcnlo pythia8
       input_name  = input_dir+"TTZToLLNuNu_M-10_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__TTZToLLNuNu_M-10_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
   
       // TTG amcnlo pythia8
       input_name  = input_dir+"TTGJets_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__TTGJets_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
 
    
       //
       // tZq
       //

       // tZq -> 2L, amcnlo pythia8
       input_name  = input_dir+"tZq_ll_4f_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__tZq_ll_4f_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();

       // tZq -> 2Nu, amcnlo pythia8
       input_name  = input_dir+"tZq_nunu_4f_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__tZq_nunu_4f_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
    
       //
       // tGJets
       //

       // tGJets, amcnlo pythia8
       input_name  = input_dir+"tGJets_amcnlo_pythia8_25ns*.root";
       output_name = output_dir+"histos__tGJets_amcnlo_pythia8_25ns.root";
       ch = new TChain("t"); 
       ch->Add(input_name);
       stopBabyLooper_diLepton_background_CR(ch, output_name); 
       ch->~TChain();
       
     } // end loop over babies
   } // end if do MC  
}
