#! /bin/bash

# This will track the settings used in the makeCMS3ClassFiles.C
#UPDATED_BABY_FILE=/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070403_BabyMaker_V0704X_v4__run25ns__20150812/merged_files/ttbar_powheg_pythia8_25ns.root
#UPDATED_BABY_FILE=/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070403_BabyMaker_V0704X_v5__run25ns__20150827/merged_files/ttbar_powheg_pythia8_25ns.root
#UPDATED_BABY_FILE=/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v6__20151123/merged_files/ttbar_powheg_pythia8_25ns_mergedBaby_1.root
#UPDATED_BABY_FILE=/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v7__20151208/merged_files/ttbar_powheg_pythia8_25ns.root
UPDATED_BABY_FILE=/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V070411__BabyMaker_V0704X_v9__20160127/merged_files/ttbar_powheg_pythia8_25ns.root
TREE=t
CLASS_NAME=stop_1l_babyAnalyzer
NAMESPACE=stop_1l
OBJECT=babyAnalyzer

root -l -b -q makeCMS3ClassFiles.C++'("'$UPDATED_BABY_FILE'","'$TREE'","'$CLASS_NAME'","'$NAMESPACE'","'$OBJECT'")'
rm ScanChain.C
rm doAll.C