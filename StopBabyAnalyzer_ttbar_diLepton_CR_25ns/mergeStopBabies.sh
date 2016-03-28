#! /bin/sh

DATA_DIR=./Histos/Nominal/

# Merge data samples
#hadd -f $DATA_DIR/histos__data_25ns.root $DATA_DIR/histos__data_muon_eg_2015CD_25ns.root 
hadd -f $DATA_DIR/histos__data_25ns.root $DATA_DIR/histos__data_diLep_2015CD_25ns.root 

TOP_DIR=./Histos/

for x in `/bin/ls $TOP_DIR`;
do
    if [ -d "$TOP_DIR/$x" ]; 
    then 
 
	BASE_DIR=$TOP_DIR/$x

	       
        # Merge TTV 
	hadd -f $BASE_DIR/histos__TTV_25ns.root $BASE_DIR/histos__TTWJetsToLNu_amcnlo_pythia8_25ns.root $BASE_DIR/histos__TTWJetsToQQ_amcnlo_pythia8_25ns.root $BASE_DIR/histos__TTZToQQ_amcnlo_pythia8_25ns.root $BASE_DIR/histos__TTZToLLNuNu_M-10_amcnlo_pythia8_25ns.root 

        # Merge tZq
	hadd -f $BASE_DIR/histos__tZq_25ns.root $BASE_DIR/histos__tZq_ll_4f_amcnlo_pythia8_25ns.root $BASE_DIR/histos__tZq_nunu_4f_amcnlo_pythia8_25ns.root

        # Merge diBoson
	hadd -f $BASE_DIR/histos__diBoson_25ns.root $BASE_DIR/histos__WW_2l2nu_powheg_25ns.root $BASE_DIR/histos__WW_lnuqq_powheg_25ns.root $BASE_DIR/histos__WZTo3LNu_powheg_pythia8_25ns.root $BASE_DIR/histos__WZTo2L2Q_amcnlo_pythia8_25ns.root $BASE_DIR/histos__WZTo1Lnu2Q_amcnlo_pythia8_25ns.root $BASE_DIR/histos__WZTo1L3Nu_amcnlo_pythia8_25ns.root $BASE_DIR/histos__ZZTo4L_powheg_pythia8_25ns.root $BASE_DIR/histos__ZZTo2L2Q_amcnlo_pythia8_25ns.root $BASE_DIR/histos__ZZTo2L2Nu_powheg_pythia8_25ns.root $BASE_DIR/histos__ZZTo2Q2Nu_amcnlo_pythia8_25ns.root 

        # Merge Rare decay samples
	hadd -f $BASE_DIR/histos__rare_25ns.root $BASE_DIR/histos__TTV_25ns.root $BASE_DIR/histos__tZq_25ns.root $BASE_DIR/histos__diBoson_25ns.root

        # Merge Single Top
	hadd -f $BASE_DIR/histos__singleT_25ns.root $BASE_DIR/histos__T_tbarW_5f_powheg_pythia8_25ns.root $BASE_DIR/histos__T_tW_5f_powheg_pythia8_25ns.root  $BASE_DIR/histos__T_tch_4f_powheg_pythia8_25ns.root $BASE_DIR/histos__Tbar_tch_4f_powheg_pythia8_25ns.root $BASE_DIR/histos__T_sch_4f_amcnlo_pythia8_25ns.root

        # Merge DY
	hadd -f $BASE_DIR/histos__DYJets_25ns.root $BASE_DIR/histos__DYJetsToLL_m10to50_amcnlo_pythia8_25ns.root $BASE_DIR/histos__DYJetsToLL_m50_amcnlo_pythia8_25ns.root

        # Merge WJets
	#hadd -f $BASE_DIR/histos__WJets_25ns.root $BASE_DIR/histos__WJetsToLNu_HT100To200_madgraph_pythia8_25ns_reScaled.root $BASE_DIR/histos__WJetsToLNu_HT200To400_madgraph_pythia8_25ns_reScaled.root $BASE_DIR/histos__WJetsToLNu_HT400To600_madgraph_pythia8_25ns_reScaled.root $BASE_DIR/histos__WJetsToLNu_HT600To800_madgraph_pythia8_25ns.root $BASE_DIR/histos__WJetsToLNu_HT800To1200_madgraph_pythia8_25ns.root $BASE_DIR/histos__WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns.root $BASE_DIR/histos__WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns.root
	hadd -f $BASE_DIR/histos__WJets_25ns.root $BASE_DIR/histos__WJetsToLNu_HT100To200_madgraph_pythia8_25ns.root $BASE_DIR/histos__WJetsToLNu_HT200To400_madgraph_pythia8_25ns.root $BASE_DIR/histos__WJetsToLNu_HT400To600_madgraph_pythia8_25ns.root $BASE_DIR/histos__WJetsToLNu_HT600To800_madgraph_pythia8_25ns.root $BASE_DIR/histos__WJetsToLNu_HT800To1200_madgraph_pythia8_25ns.root $BASE_DIR/histos__WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns.root $BASE_DIR/histos__WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns.root


        # ttbar madgraph, large stats samples
        #hadd -f $BASE_DIR/histos__ttbar_25ns.root $BASE_DIR/histos__ttbar_singleLeptFromT_madgraph_pythia8_ext1_25ns.root $BASE_DIR/histos__ttbar_singleLeptFromTbar_madgraph_pythia8_25ns.root $BASE_DIR/histos__ttbar_diLept_madgraph_pythia8_ext1_25ns.root

        # ttbar powheg pythia8
        #hadd -f $BASE_DIR/histos__ttbar_25ns.root $BASE_DIR/histos__ttbar_powheg_pythia8_25ns.root

        # ttbar powheg pythia8 ext
	hadd -f $BASE_DIR/histos__ttbar_25ns.root $BASE_DIR/histos__ttbar_powheg_pythia8_ext3_25ns.root

        # Merge nonTTbar backgrounds
	hadd -f $BASE_DIR/histos__nonTTbarBkg_25ns.root $BASE_DIR/histos__DYJets_25ns.root $BASE_DIR/histos__WJets_25ns.root $BASE_DIR/histos__singleT_25ns.root $BASE_DIR/histos__rare_25ns.root

        # Merge all backgrounds
	hadd -f $BASE_DIR/histos__allBkg_25ns.root $BASE_DIR/histos__ttbar_25ns.root $BASE_DIR/histos__DYJets_25ns.root $BASE_DIR/histos__WJets_25ns.root $BASE_DIR/histos__singleT_25ns.root $BASE_DIR/histos__rare_25ns.root

    fi

done