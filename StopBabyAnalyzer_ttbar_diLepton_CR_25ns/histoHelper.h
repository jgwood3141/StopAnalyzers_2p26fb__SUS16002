#ifndef histoHelper_H
#define histoHelper_H

// ROOT
#include "TLorentzVector.h"
#include "TH1.h"
#include "TH2.h"

// std
#include <vector>

// stop analysis
#include "stop_1l_babyAnalyzer.h"

//using namespace stop_1l;

///////////////////////////////////////////////
//
// Global Vars
//
///////////////////////////////////////////////
const int nClassy = 14;
const int nSys    = 21; // was 35, -14 for quick run
const int nCats   = 13; 

const int nHists  = nClassy*nSys*nCats;

const int nPDFs = 100;

///////////////////////////////////////////////
//
// enums for classification
//
///////////////////////////////////////////////


///////////////////////////////////////////////
enum classy_id{ k_ee0lep, 
		k_ee1lep, 
		k_ge2lep, 
		k_ZtoNuNu,
		k_incl,
		k_elel,
		k_elel_ee1lep,
		k_elel_ge2lep,
		k_elmu,
		k_elmu_ee1lep,
		k_elmu_ge2lep,
		k_mumu,
		k_mumu_ee1lep,
		k_mumu_ge2lep
};


///////////////////////////////////////////////
enum sys_id{ k_nominal,
	     k_bTagEffHFUp,
	     k_bTagEffHFDown,
	     k_bTagEffLFUp,
	     k_bTagEffLFDown,
	     k_lepSFUp,
	     k_lepSFDown,
	     k_topPtSFUp,
	     k_topPtSFDown,
	     k_lumiUp,
	     k_lumiDown,
	     k_pdfUp,
	     k_pdfDown,
	     k_alphasUp,
	     k_alphasDown,
	     k_q2Up,
	     k_q2Down,
	     k_metRes_ee2j_met_250_350_Up,
	     k_metRes_ee2j_met_250_350_Down,
	     k_metRes_ee2j_met_350_inf_Up,
	     k_metRes_ee2j_met_350_inf_Down,
	     k_metRes_ee3j_met_250_350_Up,
	     k_metRes_ee3j_met_250_350_Down,
	     k_metRes_ee3j_met_350_inf_Up,
	     k_metRes_ee3j_met_350_inf_Down,
	     k_metRes_ge4j_lt200mt2w_met_250_325_Up,
	     k_metRes_ge4j_lt200mt2w_met_250_325_Down,
	     k_metRes_ge4j_lt200mt2w_met_325_inf_Up,
	     k_metRes_ge4j_lt200mt2w_met_325_inf_Down,
	     k_metRes_ge4j_ge200mt2w_met_250_350_Up,
	     k_metRes_ge4j_ge200mt2w_met_250_350_Down,
	     k_metRes_ge4j_ge200mt2w_met_350_450_Up,
	     k_metRes_ge4j_ge200mt2w_met_350_450_Down,
	     k_metRes_ge4j_ge200mt2w_met_450_inf_Up,
	     k_metRes_ge4j_ge200mt2w_met_450_inf_Down
};

///////////////////////////////////////////////
enum cats_id{ k_baseline,
	      k_ee2j_ge0t,
	      k_ee2j_ee0t,
	      k_ee2j_ee1t,
	      k_ee2j_ee2t,
	      k_ge2j_ge0t_gt0met,
	      k_ge2j_ge0t_gt50met,
	      k_ge2j_ge0t_gt100met,
	      k_ge2j_ge0t_gt150met,
	      k_ge2j_ge0t_gt200met,
	      k_ge2j_ge0t_gt250met,
	      k_ge2j_ge1t_gt0met,
	      k_ge2j_ge1t_gt50met,
	      k_ge2j_ge1t_gt100met,
	      k_ge2j_ge1t_gt150met,
	      k_ge2j_ge1t_gt200met,
	      k_ge2j_ge1t_gt250met,
	      k_ge2j_ge2t_gt0met,
	      k_ge2j_ge2t_gt50met,
	      k_ge2j_ge2t_gt100met,
	      k_ge2j_ge2t_gt150met,
	      k_ge2j_ge2t_gt200met,
	      k_ge2j_ge2t_gt250met,
	      k_ge3j_ge0t_gt0met,
	      k_ge3j_ge0t_gt50met,
	      k_ge3j_ge0t_gt100met,
	      k_ge3j_ge0t_gt150met,
	      k_ge3j_ge0t_gt200met,
	      k_ge3j_ge0t_gt250met,
	      k_ge3j_ge1t_gt0met,
	      k_ge3j_ge1t_gt50met,
	      k_ge3j_ge1t_gt100met,
	      k_ge3j_ge1t_gt150met,
	      k_ge3j_ge1t_gt200met,
	      k_ge3j_ge1t_gt250met,
	      k_ge3j_ge2t_gt0met,
	      k_ge3j_ge2t_gt50met,
	      k_ge3j_ge2t_gt100met,
	      k_ge3j_ge2t_gt150met,
	      k_ge3j_ge2t_gt200met,
	      k_ge3j_ge2t_gt250met,
	      k_ge3j_ge3t_gt0met,
	      k_ge3j_ge3t_gt50met,
	      k_ge3j_ge3t_gt100met,
	      k_ge3j_ge3t_gt150met,
	      k_ge3j_ge3t_gt200met,
	      k_ge3j_ge3t_gt250met  
};

///////////////////////////////////////////////
//
// Utility Class
//
///////////////////////////////////////////////

///////////////////////////////////////////////
class classyInfo{

 public:
  classy_id id;
  TString   title;
  TString   tex;
  TString   label;

  classyInfo(classy_id whichClassy){

    switch(whichClassy){
    
    case(k_ee0lep):
      id = whichClassy;
      title = "==0 gen leptons";
      tex = "$==0 gen leptons$";
      label = "ee0lep";
      break;

    case(k_ee1lep):
      id = whichClassy;
      title = "==1 gen leptons";
      tex = "$==1 gen leptons$";
      label = "ee1lep";
      break;

    case(k_ge2lep):
      id = whichClassy;
      title = ">=2 gen leptons";
      tex = "$\\ge2 gen leptons$";
      label = "ge2lep";
      break;

    case(k_ZtoNuNu):
      id = whichClassy;
      title = "Z to #nu#nu";
      tex = "$Z \\rightarrow \\nu\\nu$";
      label = "ZtoNuNu";
      break;

    case(k_incl):
      id = whichClassy;
      title = "Inclusive Gen Selection";
      tex = "$Inclusivse~Gen~Selection$";
      label = "incl";
      break;
      
    case(k_elel):
      id = whichClassy;
      title = "Reco ElEl Event";
      tex = "$Reco~ElEl~Event$";
      label = "elel";
      break;

    case(k_elel_ee1lep):
      id = whichClassy;
      title = "Reco ElEl Event, ==1 gen lepton";
      tex = "$Reco~ElEl~Event, ==1 gen lepton$";
      label = "elel_ee1lep";
      break;
      
    case(k_elel_ge2lep):
      id = whichClassy;
      title = "Reco ElEl Event, >=2 gen lepton";
      tex = "$Reco~ElEl~Event, {\\ge}2 gen lepton$";
      label = "elel_ge2lep";
      break;
      
    case(k_elmu):
      id = whichClassy;
      title = "Reco ElMu Event";
      tex = "$Reco~ElMu~Event$";
      label = "elmu";
      break;

    case(k_elmu_ee1lep):
      id = whichClassy;
      title = "Reco ElMu Event, ==1 gen lepton";
      tex = "$Reco~ElMu~Even, ==1 gen leptont$";
      label = "elmu_ee1lep";
      break;

    case(k_elmu_ge2lep):
      id = whichClassy;
      title = "Reco ElMu Event, >=2 gen lepton";
      tex = "$Reco~ElMu~Even, {\\ge}2 gen leptont$";
      label = "elmu_ge2lep";
      break;

    case(k_mumu):
      id = whichClassy;
      title = "Reco MuMu Event";
      tex = "$Reco~MuMu~Event$";
      label = "mumu";
      break;

    case(k_mumu_ee1lep):
      id = whichClassy;
      title = "Reco MuMu Event, ==1 gen lepton";
      tex = "$Reco~MuMu~Event, ==1 gen lepton$";
      label = "mumu_ee1lep";
      break;

    case(k_mumu_ge2lep):
      id = whichClassy;
      title = "Reco MuMu Event, >=2 gen lepton";
      tex = "$Reco~MuMu~Event, {\\ge}2 gen lepton$";
      label = "mumu_ge2lep";
      break;

    default:
      cout << "No Gen Classification Chosen!" << endl;
      break;

    } // end switch

  } // end constructor

}; // end class Definition

///////////////////////////////////////////////
class sysInfo{

 public:
  sys_id  id;
  TString title;
  TString tex;
  TString label;
  bool    isShapeSys;
  double  yieldSF;

  sysInfo(sys_id whichSys){

    switch(whichSys){
    
    case(k_nominal):
      id = whichSys;
      title = "Nominal";
      tex = "Nominal";
      label = "nominal";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_lumiUp):
      id = whichSys;
      title = "Lumi, Scale Up";
      tex = "Lumi,~Scale~Up";
      label = "lumi_scaleUp";
      isShapeSys = false;
      yieldSF = 1.044;
      break;
      
    case(k_lumiDown):
      id = whichSys;
      title = "Lumi, Scale Down";
      tex = "Lumi,~Scale~Down";
      label = "lumi_scaleDown";
      isShapeSys = false;
      yieldSF = 0.956;
      break;

    case(k_bTagEffHFUp):
      id = whichSys;
      title = "bTag Efficiency, Heavy Flavour, Scale Up";
      tex = "bTag~Efficiency,~Heavy~Flavour,~Scale~Up";
      label = "bTagEffHF_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;
      
    case(k_bTagEffHFDown):
      id = whichSys;
      title = "bTag Efficiency, Heavy Flavour, Scale Down";
      tex = "bTag~Efficiency,~Heavy~Flavour,~Scale~Down";
      label = "bTagEffHF_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_bTagEffLFUp):
      id = whichSys;
      title = "bTag Efficiency, Light Flavour, Scale Up";
      tex = "bTag~Efficiency,~Light~Flavour,~Scale~Up";
      label = "bTagEffLF_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;
      
    case(k_bTagEffLFDown):
      id = whichSys;
      title = "bTag Efficiency, Light Flavour, Scale Down";
      tex = "bTag~Efficiency,~Light~Flavour,~Scale~Down";
      label = "bTagEffLF_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;
   
    case(k_lepSFUp):
      id = whichSys;
      title = "lepton SF, Scale Up";
      tex = "lepton~SF,~Scale~Up";
      label = "lepSF_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_lepSFDown):
      id = whichSys;
      title = "lepton SF, Scale Down";
      tex = "lepton~SF,~Scale~Down";
      label = "lepSF_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_topPtSFUp):
      id = whichSys;
      title = "top pT SF, Scale Up";
      tex = "top~pT~SF,~Scale~Up";
      label = "topPt_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_topPtSFDown):
      id = whichSys;
      title = "top pT SF, Scale Down";
      tex = "top~pT~SF,~Scale~Down";
      label = "topPt_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_pdfUp):
      id = whichSys;
      title = "PDF, Scale Up";
      tex = "PDF,~Scale~Up";
      label = "pdf_scaleUp";
      isShapeSys = false;
      yieldSF = 1.0;
      break;

    case(k_pdfDown):
      id = whichSys;
      title = "PDF, Scale Down";
      tex = "PDF,~Scale~Down";
      label = "pdf_scaleDown";
      isShapeSys = false;
      yieldSF = 1.0;
      break;
      
    case(k_alphasUp):
      id = whichSys;
      title = "alpha s, Scale Up";
      tex = "\\alpha_{s},~Scale~Up";
      label = "alphaS_scaleUp";
      isShapeSys = false;
      yieldSF = 1.0;
      break;

    case(k_alphasDown):
      id = whichSys;
      title = "alpha s, Scale Down";
      tex = "\\alpha_{s},~Scale~Down";
      label = "alphaS_scaleDown";
      isShapeSys = false;
      yieldSF = 1.0;
      break;

    case(k_q2Up):
      id = whichSys;
      title = "Q^2, Scale Up";
      tex = "Q^{2},~Scale~Up";
      label = "q2_scaleUp";
      isShapeSys = false;
      yieldSF = 1.0;
      break;

    case(k_q2Down):
      id = whichSys;
      title = "Q^2, Scale Down";
      tex = "Q^{2},~Scale~Down";
      label = "q2_scaleDown";
      isShapeSys = false;
      yieldSF = 1.0;
      break;

    
    case(k_metRes_ee2j_met_250_350_Up):
      id = whichSys;
      title = "MET Resolution, ==2j, 250<MET<350, Scale Up";
      tex = "MET~Resolution,~==2j,~250<MET<350,~Scale~Up";
      label = "metRes_ee2j_met_250_350_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_metRes_ee2j_met_250_350_Down):
      id = whichSys;
      title = "MET Resolution, ==2j, 250<MET<350, Scale Down";
      tex = "MET~Resolution,~==2j,~250<MET<350,~Scale~Down";
      label = "metRes_ee2j_met_250_350_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_metRes_ee2j_met_350_inf_Up):
      id = whichSys;
      title = "MET Resolution, ==2j, MET>350, Scale Up";
      tex = "MET~Resolution,~==2j,~MET>350,~Scale~Up";
      label = "metRes_ee2j_met_350_inf_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_metRes_ee2j_met_350_inf_Down):
      id = whichSys;
      title = "MET Resolution, ==2j, MET>350, Scale Down";
      tex = "MET~Resolution,~==2j,~MET>350,~Scale~Down";
      label = "metRes_ee2j_met_350_inf_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;


    case(k_metRes_ee3j_met_250_350_Up):
      id = whichSys;
      title = "MET Resolution, ==3j, 250<MET<350, Scale Up";
      tex = "MET~Resolution,~==3j,~250<MET<350,~Scale~Up";
      label = "metRes_ee3j_met_250_350_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_metRes_ee3j_met_250_350_Down):
      id = whichSys;
      title = "MET Resolution, ==3j, 250<MET<350, Scale Down";
      tex = "MET~Resolution,~==3j,~250<MET<350,~Scale~Down";
      label = "metRes_ee3j_met_250_350_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_metRes_ee3j_met_350_inf_Up):
      id = whichSys;
      title = "MET Resolution, ==3j, MET>350, Scale Up";
      tex = "MET~Resolution,~==3j,~MET>350,~Scale~Up";
      label = "metRes_ee3j_met_350_inf_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_metRes_ee3j_met_350_inf_Down):
      id = whichSys;
      title = "MET Resolution, ==3j, MET>350, Scale Down";
      tex = "MET~Resolution,~==3j,~MET>350,~Scale~Down";
      label = "metRes_ee3j_met_350_inf_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;


    case(k_metRes_ge4j_lt200mt2w_met_250_325_Up):
      id = whichSys;
      title = "MET Resolution, >=4j, 250<MET<325, Scale Up";
      tex = "MET~Resolution,~\\ge4j,~250<MET<325,~Scale~Up";
      label = "metRes_ge4j_lt200mt2w_met_250_325_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_metRes_ge4j_lt200mt2w_met_250_325_Down):
      id = whichSys;
      title = "MET Resolution, >=4j, 250<MET<325, Scale Down";
      tex = "MET~Resolution,~\\ge4j,~250<MET<325,~Scale~Down";
      label = "metRes_ge4j_lt200mt2w_met_250_325_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_metRes_ge4j_lt200mt2w_met_325_inf_Up):
      id = whichSys;
      title = "MET Resolution, >=4j, MET>325, Scale Up";
      tex = "MET~Resolution,~\\ge4j,~MET>325,~Scale~Up";
      label = "metRes_ge4j_lt200mt2w_met_325_inf_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_metRes_ge4j_lt200mt2w_met_325_inf_Down):
      id = whichSys;
      title = "MET Resolution, >=4j, MET>325, Scale Down";
      tex = "MET~Resolution,~\\ge4j,~MET>325,~Scale~Down";
      label = "metRes_ge4j_lt200mt2w_met_325_inf_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_metRes_ge4j_ge200mt2w_met_250_350_Up):
      id = whichSys;
      title = "MET Resolution, >=4j, 250<MET<350, Scale Up";
      tex = "MET~Resolution,~\\ge4j,~250<MET<350,~Scale~Up";
      label = "metRes_ge4j_ge200mt2w_met_250_350_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_metRes_ge4j_ge200mt2w_met_250_350_Down):
      id = whichSys;
      title = "MET Resolution, >=4j, 250<MET<350, Scale Down";
      tex = "MET~Resolution,~\\ge4j,~250<MET<350,~Scale~Down";
      label = "metRes_ge4j_ge200mt2w_met_250_350_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_metRes_ge4j_ge200mt2w_met_350_450_Up):
      id = whichSys;
      title = "MET Resolution, >=4j, 350<MET<450, Scale Up";
      tex = "MET~Resolution,~\\ge4j,~350<MET<450,~Scale~Up";
      label = "metRes_ge4j_ge200mt2w_met_350_450_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_metRes_ge4j_ge200mt2w_met_350_450_Down):
      id = whichSys;
      title = "MET Resolution, >=4j, 350<MET<450, Scale Down";
      tex = "MET~Resolution,~\\ge4j,~350<MET<450,~Scale~Down";
      label = "metRes_ge4j_ge200mt2w_met_350_450_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_metRes_ge4j_ge200mt2w_met_450_inf_Up):
      id = whichSys;
      title = "MET Resolution, >=4j, MET>450, Scale Up";
      tex = "MET~Resolution,~\\ge4j,~MET>450,~Scale~Up";
      label = "metRes_ge4j_ge200mt2w_met_450_inf_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_metRes_ge4j_ge200mt2w_met_450_inf_Down):
      id = whichSys;
      title = "MET Resolution, >=4j, MET>450, Scale Down";
      tex = "MET~Resolution,~\\ge4j,~MET>450,~Scale~Down";
      label = "metRes_ge4j_ge200mt2w_met_450_inf_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

      
        
    default:
      cout << "NO Systematic Chosen: " << endl;
      
      
    } // switch

  } // end constructor


}; // end class


///////////////////////////////////////////////
class catInfo{

 public:
  cats_id id;
  TString title;
  TString tex;
  TString label;

  catInfo(cats_id whichCat){

    switch(whichCat){
    
    case(k_baseline):
      id = whichCat;
      title = "Baseline";
      tex = "Baseline";
      label = "baseline";
      break;

    case(k_ee2j_ge0t):
      id = whichCat;
      title = "CR4, ==2 Jets, >=0 Tags";
      tex = "$CR4,~==2~Jets,~\\ge0~Tags$";
      label = "ee2j_ge0t";
      break;

    case(k_ee2j_ee0t):
      id = whichCat;
      title = "CR4, ==2 Jets, ==0 Tags";
      tex = "$CR4,~==2~Jets,~==0~Tags$";
      label = "ee2j_ee0t";
      break;

    case(k_ee2j_ee1t):
      id = whichCat;
      title = "CR4, ==2 Jets, ==1 Tags";
      tex = "$CR4,~==2~Jets,~==1~Tags$";
      label = "ee2j_ee1t";
      break;

    case(k_ee2j_ee2t):
      id = whichCat;
      title = "CR4, ==2 Jets, ==2 Tags";
      tex = "$CR4,~==2~Jets,~==2~Tags$";
      label = "ee2j_ee2t";
      break;

    case(k_ge2j_ge0t_gt0met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=0 Tags";
      tex = "$CR4,~\\ge2~Jets,~\\ge0~Tags$";
      label = "ge2j_ge0t_gt0met";
      break;
      
    case(k_ge2j_ge0t_gt50met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=0 Tags, MET>50";
      tex = "$CR4,~\\ge2~Jets,~\\ge0~Tags,~MET>50$";
      label = "ge2j_ge0t_gt50met";
      break;

    case(k_ge2j_ge0t_gt100met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=0 Tags, MET>100";
      tex = "$CR4,~\\ge2~Jets,~\\ge0~Tags,~MET>100$";
      label = "ge2j_ge0t_gt100met";
      break;

    case(k_ge2j_ge0t_gt150met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=0 Tags, MET>150";
      tex = "$CR4,~\\ge2~Jets,~\\ge0~Tags,~MET>150$";
      label = "ge2j_ge0t_gt150met";
      break;

    case(k_ge2j_ge0t_gt200met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=0 Tags, MET>200";
      tex = "$CR4,~\\ge2~Jets,~\\ge0~Tags,~MET>200$";
      label = "ge2j_ge0t_gt200met";
      break;

    case(k_ge2j_ge0t_gt250met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=0 Tags, MET>250";
      tex = "$CR4,~\\ge2~Jets,~\\ge0~Tags,~MET>250$";
      label = "ge2j_ge0t_gt250met";
      break;

    case(k_ge2j_ge1t_gt0met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=1 Tags";
      tex = "$CR4,~\\ge2~Jets,~\\ge1~Tags$";
      label = "ge2j_ge1t_gt0met";
      break;

    case(k_ge2j_ge1t_gt50met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=1 Tags, MET>50";
      tex = "$CR4,~\\ge2~Jets,~\\ge1~Tags,~MET>50$";
      label = "ge2j_ge1t_gt50met";
      break;

    case(k_ge2j_ge1t_gt100met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=1 Tags, MET>100";
      tex = "$CR4,~\\ge2~Jets,~\\ge1~Tags,~MET>100$";
      label = "ge2j_ge1t_gt100met";
      break;

    case(k_ge2j_ge1t_gt150met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=1 Tags, MET>150";
      tex = "$CR4,~\\ge2~Jets,~\\ge1~Tags,~MET>150$";
      label = "ge2j_ge1t_gt150met";
      break;

    case(k_ge2j_ge1t_gt200met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=1 Tags, MET>200";
      tex = "$CR4,~\\ge2~Jets,~\\ge1~Tags,~MET>200$";
      label = "ge2j_ge1t_gt200met";
      break;

    case(k_ge2j_ge1t_gt250met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=1 Tags, MET>250";
      tex = "$CR4,~\\ge2~Jets,~\\ge1~Tags,~MET>250$";
      label = "ge2j_ge1t_gt250met";
      break;

    case(k_ge2j_ge2t_gt0met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=2 Tags";
      tex = "$CR4,~\\ge2~Jets,~\\ge2~Tags$";
      label = "ge2j_ge2t_gt0met";
      break;

    case(k_ge2j_ge2t_gt50met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=2 Tags, MET>50";
      tex = "$CR4,~\\ge2~Jets,~\\ge2~Tags,~MET>50$";
      label = "ge2j_ge2t_gt50met";
      break;

    case(k_ge2j_ge2t_gt100met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=2 Tags, MET>100";
      tex = "$CR4,~\\ge2~Jets,~\\ge2~Tags,~MET>100$";
      label = "ge2j_ge2t_gt100met";
      break;

    case(k_ge2j_ge2t_gt150met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=2 Tags, MET>150";
      tex = "$CR4,~\\ge2~Jets,~\\ge2~Tags,~MET>150$";
      label = "ge2j_ge2t_gt150met";
      break;

    case(k_ge2j_ge2t_gt200met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=2 Tags, MET>200";
      tex = "$CR4,~\\ge2~Jets,~\\ge2~Tags,~MET>200$";
      label = "ge2j_ge2t_gt200met";
      break;

    case(k_ge2j_ge2t_gt250met):
      id = whichCat;
      title = "CR4, >=2 Jets, >=2 Tags, MET>250";
      tex = "$CR4,~\\ge2~Jets,~\\ge2~Tags,~MET>250$";
      label = "ge2j_ge2t_gt250met";
      break;

    case(k_ge3j_ge0t_gt0met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=0 Tags";
      tex = "$CR4,~\\ge3~Jets,~\\ge0~Tags$";
      label = "ge3j_ge0t_gt0met";
      break;

    case(k_ge3j_ge0t_gt50met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=0 Tags, MET>50";
      tex = "$CR4,~\\ge3~Jets,~\\ge0~Tags,~MET>50$";
      label = "ge3j_ge0t_gt50met";
      break;

    case(k_ge3j_ge0t_gt100met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=0 Tags, MET>100";
      tex = "$CR4,~\\ge3~Jets,~\\ge0~Tags,~MET>100$";
      label = "ge3j_ge0t_gt100met";
      break;

    case(k_ge3j_ge0t_gt150met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=0 Tags, MET>150";
      tex = "$CR4,~\\ge3~Jets,~\\ge0~Tags,~MET>150$";
      label = "ge3j_ge0t_gt150met";
      break;

    case(k_ge3j_ge0t_gt200met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=0 Tags, MET>200";
      tex = "$CR4,~\\ge3~Jets,~\\ge0~Tags,~MET>200$";
      label = "ge3j_ge0t_gt200met";
      break;

    case(k_ge3j_ge0t_gt250met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=0 Tags, MET>250";
      tex = "$CR4,~\\ge3~Jets,~\\ge0~Tags,~MET>250$";
      label = "ge3j_ge0t_gt250met";
      break;

    case(k_ge3j_ge1t_gt0met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=1 Tags";
      tex = "$CR4,~\\ge3~Jets,~\\ge1~Tags$";
      label = "ge3j_ge1t_gt0met";
      break;

    case(k_ge3j_ge1t_gt50met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=1 Tags, MET>50";
      tex = "$CR4,~\\ge3~Jets,~\\ge1~Tags,~MET>50$";
      label = "ge3j_ge1t_gt50met";
      break;

    case(k_ge3j_ge1t_gt100met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=1 Tags, MET>100";
      tex = "$CR4,~\\ge3~Jets,~\\ge1~Tags,~MET>100$";
      label = "ge3j_ge1t_gt100met";
      break;

    case(k_ge3j_ge1t_gt150met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=1 Tags, MET>150";
      tex = "$CR4,~\\ge3~Jets,~\\ge1~Tags,~MET>150$";
      label = "ge3j_ge1t_gt150met";
      break;

    case(k_ge3j_ge1t_gt200met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=1 Tags, MET>200";
      tex = "$CR4,~\\ge3~Jets,~\\ge1~Tags,~MET>200$";
      label = "ge3j_ge1t_gt200met";
      break;

    case(k_ge3j_ge1t_gt250met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=1 Tags, MET>250";
      tex = "$CR4,~\\ge3~Jets,~\\ge1~Tags,~MET>250$";
      label = "ge3j_ge1t_gt250met";
      break;

    case(k_ge3j_ge2t_gt0met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=2 Tags";
      tex = "$CR4,~\\ge3~Jets,~\\ge2~Tags$";
      label = "ge3j_ge2t_gt0met";
      break;

    case(k_ge3j_ge2t_gt50met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=2 Tags, MET>50";
      tex = "$CR4,~\\ge3~Jets,~\\ge2~Tags,~MET>50$";
      label = "ge3j_ge2t_gt50met";
      break;

    case(k_ge3j_ge2t_gt100met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=2 Tags, MET>100";
      tex = "$CR4,~\\ge3~Jets,~\\ge2~Tags,~MET>100$";
      label = "ge3j_ge2t_gt100met";
      break;

    case(k_ge3j_ge2t_gt150met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=2 Tags, MET>150";
      tex = "$CR4,~\\ge3~Jets,~\\ge2~Tags,~MET>150$";
      label = "ge3j_ge2t_gt150met";
      break;

    case(k_ge3j_ge2t_gt200met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=2 Tags, MET>200";
      tex = "$CR4,~\\ge3~Jets,~\\ge2~Tags,~MET>200$";
      label = "ge3j_ge2t_gt200met";
      break;

    case(k_ge3j_ge2t_gt250met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=2 Tags, MET>250";
      tex = "$CR4,~\\ge3~Jets,~\\ge2~Tags,~MET>250$";
      label = "ge3j_ge2t_gt250met";
      break;

    case(k_ge3j_ge3t_gt0met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=3 Tags";
      tex = "$CR4,~\\ge3~Jets,~\\ge3~Tags$";
      label = "ge3j_ge3t_gt0met";
      break;

    case(k_ge3j_ge3t_gt50met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=3 Tags, MET>50";
      tex = "$CR4,~\\ge3~Jets,~\\ge3~Tags,~MET>50$";
      label = "ge3j_ge3t_gt50met";
      break;

    case(k_ge3j_ge3t_gt100met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=3 Tags, MET>100";
      tex = "$CR4,~\\ge3~Jets,~\\ge3~Tags,~MET>100$";
      label = "ge3j_ge3t_gt100met";
      break;

    case(k_ge3j_ge3t_gt150met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=3 Tags, MET>150";
      tex = "$CR4,~\\ge3~Jets,~\\ge3~Tags,~MET>150$";
      label = "ge3j_ge3t_gt150met";
      break;

    case(k_ge3j_ge3t_gt200met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=3 Tags, MET>200";
      tex = "$CR4,~\\ge3~Jets,~\\ge3~Tags,~MET>200$";
      label = "ge3j_ge3t_gt200met";
      break;

    case(k_ge3j_ge3t_gt250met):
      id = whichCat;
      title = "CR4, >=3 Jets, >=3 Tags, MET>250";
      tex = "$CR4,~\\ge3~Jets,~\\ge3~Tags,~MET>250$";
      label = "ge3j_ge3t_gt250met";
      break;

    default:
      cout << "NO Category Chosen" << endl;

    } // end cat switch
	 
  } // end constructor



}; // end classInfo class 

///////////////////////////////////////////////
class varInfo_1D{

 public:

  TH1D*   histo_[nHists];
  TString title;
  TString titleX;
  TString tex;
  TString label;
  int     nBins;
  double  bin_min;
  double  bin_max;
  bool    fillAllSys;

  varInfo_1D( TString v_title, TString v_titleX, TString v_tex, TString v_label, int v_nBins, double v_min, double v_max, bool v_fillAllSys=false ){
    title   = v_title;
    titleX  = v_titleX;
    tex     = v_tex;
    label   = v_label;
    nBins   = v_nBins;
    bin_min = v_min;
    bin_max = v_max;
    fillAllSys = v_fillAllSys;

  } // end constructor
  
};


///////////////////////////////////////////////
//
// Main Analysis Class
//
///////////////////////////////////////////////

///////////////////////////////////////////////
class histoHelper{
 
public:
 
  //
  // Event Categories
  //
  std::vector<classyInfo*> classifications;
  classyInfo *classy_ee0lep;
  classyInfo *classy_ee1lep;
  classyInfo *classy_ge2lep;
  classyInfo *classy_ZtoNuNu;
  classyInfo *classy_incl;
  classyInfo *classy_elel;
  classyInfo *classy_elel_ee1lep;
  classyInfo *classy_elel_ge2lep;
  classyInfo *classy_elmu;
  classyInfo *classy_elmu_ee1lep;
  classyInfo *classy_elmu_ge2lep;
  classyInfo *classy_mumu;
  classyInfo *classy_mumu_ee1lep;
  classyInfo *classy_mumu_ge2lep;

  std::vector<sysInfo*> systematics;
  sysInfo *sys_nominal;
  sysInfo *sys_lumi_scaleUp;
  sysInfo *sys_lumi_scaleDown;
  sysInfo *sys_bTagEffHF_scaleUp;
  sysInfo *sys_bTagEffHF_scaleDown;
  sysInfo *sys_bTagEffLF_scaleUp;
  sysInfo *sys_bTagEffLF_scaleDown;
  sysInfo *sys_lepSF_scaleUp;
  sysInfo *sys_lepSF_scaleDown;
  sysInfo *sys_topPtSF_scaleUp;
  sysInfo *sys_topPtSF_scaleDown;
  sysInfo *sys_pdf_scaleUp;
  sysInfo *sys_pdf_scaleDown;
  sysInfo *sys_alphas_scaleUp;
  sysInfo *sys_alphas_scaleDown;
  sysInfo *sys_q2_scaleUp;
  sysInfo *sys_q2_scaleDown;
  sysInfo *sys_metRes_ee2j_met_250_350_Up;
  sysInfo *sys_metRes_ee2j_met_250_350_Down;
  sysInfo *sys_metRes_ee2j_met_350_inf_Up;
  sysInfo *sys_metRes_ee2j_met_350_inf_Down;
  sysInfo *sys_metRes_ee3j_met_250_350_Up;
  sysInfo *sys_metRes_ee3j_met_250_350_Down;
  sysInfo *sys_metRes_ee3j_met_350_inf_Up;
  sysInfo *sys_metRes_ee3j_met_350_inf_Down;
  sysInfo *sys_metRes_ge4j_lt200mt2w_met_250_325_Up;
  sysInfo *sys_metRes_ge4j_lt200mt2w_met_250_325_Down;
  sysInfo *sys_metRes_ge4j_lt200mt2w_met_325_inf_Up;
  sysInfo *sys_metRes_ge4j_lt200mt2w_met_325_inf_Down;
  sysInfo *sys_metRes_ge4j_ge200mt2w_met_250_350_Up;
  sysInfo *sys_metRes_ge4j_ge200mt2w_met_250_350_Down;
  sysInfo *sys_metRes_ge4j_ge200mt2w_met_350_450_Up;
  sysInfo *sys_metRes_ge4j_ge200mt2w_met_350_450_Down;
  sysInfo *sys_metRes_ge4j_ge200mt2w_met_450_inf_Up;
  sysInfo *sys_metRes_ge4j_ge200mt2w_met_450_inf_Down;


  std::vector<catInfo*> categories;
  catInfo *cat_baseLine;
  //catInfo *cat_ee2j_ge0t;
  //catInfo *cat_ee2j_ee0t;
  //catInfo *cat_ee2j_ee1t;
  //catInfo *cat_ee2j_ee2t;
  catInfo *cat_ge2j_ge0t_gt0met;
  //catInfo *cat_ge2j_ge0t_gt50met;
  catInfo *cat_ge2j_ge0t_gt100met;
  catInfo *cat_ge2j_ge0t_gt150met;
  catInfo *cat_ge2j_ge0t_gt200met;
  //catInfo *cat_ge2j_ge0t_gt250met;
  catInfo *cat_ge2j_ge1t_gt0met;
  //catInfo *cat_ge2j_ge1t_gt50met;
  catInfo *cat_ge2j_ge1t_gt100met;
  catInfo *cat_ge2j_ge1t_gt150met;
  catInfo *cat_ge2j_ge1t_gt200met;
  //catInfo *cat_ge2j_ge1t_gt250met;
  catInfo *cat_ge2j_ge2t_gt0met;
  //catInfo *cat_ge2j_ge2t_gt50met;
  catInfo *cat_ge2j_ge2t_gt100met;
  catInfo *cat_ge2j_ge2t_gt150met;
  catInfo *cat_ge2j_ge2t_gt200met;
  //catInfo *cat_ge2j_ge2t_gt250met;
  //catInfo *cat_ge3j_ge0t_gt0met;
  //catInfo *cat_ge3j_ge0t_gt50met;
  //catInfo *cat_ge3j_ge0t_gt100met;
  //catInfo *cat_ge3j_ge0t_gt150met;
  //catInfo *cat_ge3j_ge0t_gt200met;
  //catInfo *cat_ge3j_ge0t_gt250met;
  //catInfo *cat_ge3j_ge1t_gt0met;
  //catInfo *cat_ge3j_ge1t_gt50met;
  //catInfo *cat_ge3j_ge1t_gt100met;
  //catInfo *cat_ge3j_ge1t_gt150met;
  //catInfo *cat_ge3j_ge1t_gt200met;
  //catInfo *cat_ge3j_ge1t_gt250met;
  //catInfo *cat_ge3j_ge2t_gt0met;
  //catInfo *cat_ge3j_ge2t_gt50met;
  //catInfo *cat_ge3j_ge2t_gt100met;
  //catInfo *cat_ge3j_ge2t_gt150met;
  //catInfo *cat_ge3j_ge2t_gt200met;
  //catInfo *cat_ge3j_ge2t_gt250met;
  //catInfo *cat_ge3j_ge3t_gt0met;
  //catInfo *cat_ge3j_ge3t_gt50met;
  //catInfo *cat_ge3j_ge3t_gt100met;
  //catInfo *cat_ge3j_ge3t_gt150met;
  //catInfo *cat_ge3j_ge3t_gt200met;
  //catInfo *cat_ge3j_ge3t_gt250met; 


  //
  // Bin Information
  //
  std::vector<varInfo_1D*> vars_1D;
  varInfo_1D *var_yield;
  //varInfo_1D *var_yield_noSF;
  //varInfo_1D *var_yield_only_bTagSF;
  //varInfo_1D *var_yield_only_lepSF;
  //varInfo_1D *var_yield_only_topPtSF;
  varInfo_1D *var_nGenLep;
  varInfo_1D *var_nGenNu;
  varInfo_1D *var_nJets;
  //varInfo_1D *var_nTags_loose;
  varInfo_1D *var_nTags_med;
  //varInfo_1D *var_nTags_tight;
  //varInfo_1D *var_mt;
  //varInfo_1D *var_minDPhi;
  varInfo_1D *var_met;
  varInfo_1D *var_met_highMT;
  varInfo_1D *var_met_lowMT;
  varInfo_1D *var_met_withK3K4;
  varInfo_1D *var_genDiNuPt;
  varInfo_1D *var_genDiNuPt_highMT;
  varInfo_1D *var_genDiNuPt_lowMT;
  //varInfo_1D *var_met_lowDM;
  //varInfo_1D *var_met_highDM;
  varInfo_1D *var_met_phi;
  //varInfo_1D *var_mt2w;
  //varInfo_1D *var_hadTopChi2;
  //varInfo_1D *var_htRatio;
  varInfo_1D *var_mu_pt;
  varInfo_1D *var_mu_eta;
  //varInfo_1D *var_mu_phi;
  varInfo_1D *var_el_pt;
  varInfo_1D *var_el_eta;
  //varInfo_1D *var_el_phi;
  varInfo_1D *var_lep1_pt;
  //varInfo_1D *var_lep1_eta;
  //varInfo_1D *var_lep1_phi;
  varInfo_1D *var_lep2_pt;
  //varInfo_1D *var_lep2_eta;
  //varInfo_1D *var_lep2_phi;
  varInfo_1D *var_diLep_mass;
  varInfo_1D *var_diLep_pt;
  varInfo_1D *var_diLep_pt_emu;
  varInfo_1D *var_diLep_pt_mue;
  varInfo_1D *var_deltaPt_lep1_lep2;
  varInfo_1D *var_deltaPhi_lep1_lep2;
  varInfo_1D *var_jet_pt;
  varInfo_1D *var_jet_csv;
  varInfo_1D *var_jet_1_pt;
  varInfo_1D *var_jet_2_pt;
  varInfo_1D *var_ttbar_px;
  varInfo_1D *var_ttbar_py;
  varInfo_1D *var_ttbar_pt;
  
  histoHelper(){

    // Declare classifications
    classy_ee0lep      = new classyInfo( k_ee0lep );
    classy_ee1lep      = new classyInfo( k_ee1lep );
    classy_ge2lep      = new classyInfo( k_ge2lep );
    classy_ZtoNuNu     = new classyInfo( k_ZtoNuNu );
    classy_incl        = new classyInfo( k_incl );
    classy_elel        = new classyInfo( k_elel );
    classy_elel_ee1lep = new classyInfo( k_elel_ee1lep );
    classy_elel_ge2lep = new classyInfo( k_elel_ge2lep );
    classy_elmu        = new classyInfo( k_elmu );
    classy_elmu_ee1lep = new classyInfo( k_elmu_ee1lep );
    classy_elmu_ge2lep = new classyInfo( k_elmu_ge2lep );
    classy_mumu        = new classyInfo( k_mumu );
    classy_mumu_ee1lep = new classyInfo( k_mumu_ee1lep );
    classy_mumu_ge2lep = new classyInfo( k_mumu_ge2lep );

    
    // Fill classifications vector
    classifications.push_back( classy_ee0lep );
    classifications.push_back( classy_ee1lep );
    classifications.push_back( classy_ge2lep );
    classifications.push_back( classy_ZtoNuNu );
    classifications.push_back( classy_incl );
    classifications.push_back( classy_elel );
    classifications.push_back( classy_elel_ee1lep );
    classifications.push_back( classy_elel_ge2lep );
    classifications.push_back( classy_elmu );
    classifications.push_back( classy_elmu_ee1lep );
    classifications.push_back( classy_elmu_ge2lep );
    classifications.push_back( classy_mumu );
    classifications.push_back( classy_mumu_ee1lep );
    classifications.push_back( classy_mumu_ge2lep );


    // Declare systematics
    sys_nominal           = new sysInfo( k_nominal );
    sys_lumi_scaleUp      = new sysInfo( k_lumiUp );
    sys_lumi_scaleDown    = new sysInfo( k_lumiDown );
    sys_bTagEffHF_scaleUp   = new sysInfo( k_bTagEffHFUp );
    sys_bTagEffHF_scaleDown = new sysInfo( k_bTagEffHFDown );
    sys_bTagEffLF_scaleUp   = new sysInfo( k_bTagEffLFUp );
    sys_bTagEffLF_scaleDown = new sysInfo( k_bTagEffLFDown );
    sys_lepSF_scaleUp       = new sysInfo( k_lepSFUp );
    sys_lepSF_scaleDown     = new sysInfo( k_lepSFDown );
    sys_topPtSF_scaleUp     = new sysInfo( k_topPtSFUp );
    sys_topPtSF_scaleDown   = new sysInfo( k_topPtSFDown );
    sys_pdf_scaleUp         = new sysInfo( k_pdfUp );
    sys_pdf_scaleDown       = new sysInfo( k_pdfDown );
    sys_alphas_scaleUp      = new sysInfo( k_alphasUp );
    sys_alphas_scaleDown    = new sysInfo( k_alphasDown );
    sys_q2_scaleUp          = new sysInfo( k_q2Up );
    sys_q2_scaleDown        = new sysInfo( k_q2Down );
    sys_metRes_ee2j_met_250_350_Up             = new sysInfo( k_metRes_ee2j_met_250_350_Up ); 
    sys_metRes_ee2j_met_250_350_Down           = new sysInfo( k_metRes_ee2j_met_250_350_Down );
    sys_metRes_ee2j_met_350_inf_Up             = new sysInfo( k_metRes_ee2j_met_350_inf_Up );
    sys_metRes_ee2j_met_350_inf_Down           = new sysInfo( k_metRes_ee2j_met_350_inf_Down );
    sys_metRes_ee3j_met_250_350_Up             = new sysInfo( k_metRes_ee3j_met_250_350_Up );
    sys_metRes_ee3j_met_250_350_Down           = new sysInfo( k_metRes_ee3j_met_250_350_Down );
    sys_metRes_ee3j_met_350_inf_Up             = new sysInfo( k_metRes_ee3j_met_350_inf_Up );
    sys_metRes_ee3j_met_350_inf_Down           = new sysInfo( k_metRes_ee3j_met_350_inf_Down );
    sys_metRes_ge4j_lt200mt2w_met_250_325_Up   = new sysInfo( k_metRes_ge4j_lt200mt2w_met_250_325_Up );
    sys_metRes_ge4j_lt200mt2w_met_250_325_Down = new sysInfo( k_metRes_ge4j_lt200mt2w_met_250_325_Down );
    sys_metRes_ge4j_lt200mt2w_met_325_inf_Up   = new sysInfo( k_metRes_ge4j_lt200mt2w_met_325_inf_Up );
    sys_metRes_ge4j_lt200mt2w_met_325_inf_Down = new sysInfo( k_metRes_ge4j_lt200mt2w_met_325_inf_Down );
    sys_metRes_ge4j_ge200mt2w_met_250_350_Up   = new sysInfo( k_metRes_ge4j_ge200mt2w_met_250_350_Up );
    sys_metRes_ge4j_ge200mt2w_met_250_350_Down = new sysInfo( k_metRes_ge4j_ge200mt2w_met_250_350_Down );
    sys_metRes_ge4j_ge200mt2w_met_350_450_Up   = new sysInfo( k_metRes_ge4j_ge200mt2w_met_350_450_Up );
    sys_metRes_ge4j_ge200mt2w_met_350_450_Down = new sysInfo( k_metRes_ge4j_ge200mt2w_met_350_450_Down );
    sys_metRes_ge4j_ge200mt2w_met_450_inf_Up   = new sysInfo( k_metRes_ge4j_ge200mt2w_met_450_inf_Up );
    sys_metRes_ge4j_ge200mt2w_met_450_inf_Down = new sysInfo( k_metRes_ge4j_ge200mt2w_met_450_inf_Down );


    // Fill systematics vector
    systematics.push_back( sys_nominal );
    //systematics.push_back( sys_lumi_scaleUp );
    //systematics.push_back( sys_lumi_scaleDown );
    //systematics.push_back( sys_bTagEffHF_scaleUp );
    //systematics.push_back( sys_bTagEffHF_scaleDown );
    //systematics.push_back( sys_bTagEffLF_scaleUp );
    //systematics.push_back( sys_bTagEffLF_scaleDown );
    //systematics.push_back( sys_lepSF_scaleUp );
    //systematics.push_back( sys_lepSF_scaleDown );
    systematics.push_back( sys_topPtSF_scaleUp );
    systematics.push_back( sys_topPtSF_scaleDown );
    //systematics.push_back( sys_pdf_scaleUp );
    //systematics.push_back( sys_pdf_scaleDown );
    //systematics.push_back( sys_alphas_scaleUp );
    //systematics.push_back( sys_alphas_scaleDown );
    //systematics.push_back( sys_q2_scaleUp );
    //systematics.push_back( sys_q2_scaleDown );
    systematics.push_back( sys_metRes_ee2j_met_250_350_Up );
    systematics.push_back( sys_metRes_ee2j_met_250_350_Down );
    systematics.push_back( sys_metRes_ee2j_met_350_inf_Up );
    systematics.push_back( sys_metRes_ee2j_met_350_inf_Down );
    systematics.push_back( sys_metRes_ee3j_met_250_350_Up );
    systematics.push_back( sys_metRes_ee3j_met_250_350_Down );
    systematics.push_back( sys_metRes_ee3j_met_350_inf_Up );
    systematics.push_back( sys_metRes_ee3j_met_350_inf_Down );
    systematics.push_back( sys_metRes_ge4j_lt200mt2w_met_250_325_Up );
    systematics.push_back( sys_metRes_ge4j_lt200mt2w_met_250_325_Down );
    systematics.push_back( sys_metRes_ge4j_lt200mt2w_met_325_inf_Up );
    systematics.push_back( sys_metRes_ge4j_lt200mt2w_met_325_inf_Down );
    systematics.push_back( sys_metRes_ge4j_ge200mt2w_met_250_350_Up );
    systematics.push_back( sys_metRes_ge4j_ge200mt2w_met_250_350_Down );
    systematics.push_back( sys_metRes_ge4j_ge200mt2w_met_350_450_Up );
    systematics.push_back( sys_metRes_ge4j_ge200mt2w_met_350_450_Down );
    systematics.push_back( sys_metRes_ge4j_ge200mt2w_met_450_inf_Up );
    systematics.push_back( sys_metRes_ge4j_ge200mt2w_met_450_inf_Down );


    // Declare categories
    cat_baseLine           = new catInfo( k_baseline );
    //cat_ee2j_ge0t          = new catInfo( k_ee2j_ge0t );
    //cat_ee2j_ee0t          = new catInfo( k_ee2j_ee0t );
    //cat_ee2j_ee1t          = new catInfo( k_ee2j_ee1t );
    //cat_ee2j_ee2t          = new catInfo( k_ee2j_ee2t );
    cat_ge2j_ge0t_gt0met   = new catInfo( k_ge2j_ge0t_gt0met );
    //cat_ge2j_ge0t_gt50met  = new catInfo( k_ge2j_ge0t_gt50met );
    cat_ge2j_ge0t_gt100met = new catInfo( k_ge2j_ge0t_gt100met );
    cat_ge2j_ge0t_gt150met = new catInfo( k_ge2j_ge0t_gt150met );
    cat_ge2j_ge0t_gt200met = new catInfo( k_ge2j_ge0t_gt200met );
    //cat_ge2j_ge0t_gt250met = new catInfo( k_ge2j_ge0t_gt250met );
    cat_ge2j_ge1t_gt0met   = new catInfo( k_ge2j_ge1t_gt0met );
    //cat_ge2j_ge1t_gt50met  = new catInfo( k_ge2j_ge1t_gt50met );
    cat_ge2j_ge1t_gt100met = new catInfo( k_ge2j_ge1t_gt100met );
    cat_ge2j_ge1t_gt150met = new catInfo( k_ge2j_ge1t_gt150met );
    cat_ge2j_ge1t_gt200met = new catInfo( k_ge2j_ge1t_gt200met );
    //cat_ge2j_ge1t_gt250met = new catInfo( k_ge2j_ge1t_gt250met );
    cat_ge2j_ge2t_gt0met   = new catInfo( k_ge2j_ge2t_gt0met );
    //cat_ge2j_ge2t_gt50met  = new catInfo( k_ge2j_ge2t_gt50met );
    cat_ge2j_ge2t_gt100met = new catInfo( k_ge2j_ge2t_gt100met );
    cat_ge2j_ge2t_gt150met = new catInfo( k_ge2j_ge2t_gt150met );
    cat_ge2j_ge2t_gt200met = new catInfo( k_ge2j_ge2t_gt200met );
    //cat_ge2j_ge2t_gt250met = new catInfo( k_ge2j_ge2t_gt250met );
    //cat_ge3j_ge0t_gt0met   = new catInfo( k_ge3j_ge0t_gt0met );
    //cat_ge3j_ge0t_gt50met  = new catInfo( k_ge3j_ge0t_gt50met );
    //cat_ge3j_ge0t_gt100met = new catInfo( k_ge3j_ge0t_gt100met );
    //cat_ge3j_ge0t_gt150met = new catInfo( k_ge3j_ge0t_gt150met );
    //cat_ge3j_ge0t_gt200met = new catInfo( k_ge3j_ge0t_gt200met );
    //cat_ge3j_ge0t_gt250met = new catInfo( k_ge3j_ge0t_gt250met );
    //cat_ge3j_ge1t_gt0met   = new catInfo( k_ge3j_ge1t_gt0met );
    //cat_ge3j_ge1t_gt50met  = new catInfo( k_ge3j_ge1t_gt50met );
    //cat_ge3j_ge1t_gt100met = new catInfo( k_ge3j_ge1t_gt100met );
    //cat_ge3j_ge1t_gt150met = new catInfo( k_ge3j_ge1t_gt150met );
    //cat_ge3j_ge1t_gt200met = new catInfo( k_ge3j_ge1t_gt200met );
    //cat_ge3j_ge1t_gt250met = new catInfo( k_ge3j_ge1t_gt250met );
    //cat_ge3j_ge2t_gt0met   = new catInfo( k_ge3j_ge2t_gt0met );
    //cat_ge3j_ge2t_gt50met  = new catInfo( k_ge3j_ge2t_gt50met );
    //cat_ge3j_ge2t_gt100met = new catInfo( k_ge3j_ge2t_gt100met );
    //cat_ge3j_ge2t_gt150met = new catInfo( k_ge3j_ge2t_gt150met );
    //cat_ge3j_ge2t_gt200met = new catInfo( k_ge3j_ge2t_gt200met );
    //cat_ge3j_ge2t_gt250met = new catInfo( k_ge3j_ge2t_gt250met );
    //cat_ge3j_ge3t_gt0met   = new catInfo( k_ge3j_ge3t_gt0met );
    //cat_ge3j_ge3t_gt50met  = new catInfo( k_ge3j_ge3t_gt50met );
    //cat_ge3j_ge3t_gt100met = new catInfo( k_ge3j_ge3t_gt100met );
    //cat_ge3j_ge3t_gt150met = new catInfo( k_ge3j_ge3t_gt150met );
    //cat_ge3j_ge3t_gt200met = new catInfo( k_ge3j_ge3t_gt200met );
    //cat_ge3j_ge3t_gt250met = new catInfo( k_ge3j_ge3t_gt250met );

    // Fill categories vector
    categories.push_back( cat_baseLine );
    //categories.push_back( cat_ee2j_ge0t );
    //categories.push_back( cat_ee2j_ee0t );
    //categories.push_back( cat_ee2j_ee1t );
    //categories.push_back( cat_ee2j_ee2t );
    categories.push_back( cat_ge2j_ge0t_gt0met );
    //categories.push_back( cat_ge2j_ge0t_gt50met );
    categories.push_back( cat_ge2j_ge0t_gt100met );
    categories.push_back( cat_ge2j_ge0t_gt150met );
    categories.push_back( cat_ge2j_ge0t_gt200met );
    //categories.push_back( cat_ge2j_ge0t_gt250met );
    categories.push_back( cat_ge2j_ge1t_gt0met );
    //categories.push_back( cat_ge2j_ge1t_gt50met );
    categories.push_back( cat_ge2j_ge1t_gt100met );
    categories.push_back( cat_ge2j_ge1t_gt150met );
    categories.push_back( cat_ge2j_ge1t_gt200met );
    //categories.push_back( cat_ge2j_ge1t_gt250met );
    categories.push_back( cat_ge2j_ge2t_gt0met );
    //categories.push_back( cat_ge2j_ge2t_gt50met );
    categories.push_back( cat_ge2j_ge2t_gt100met );
    categories.push_back( cat_ge2j_ge2t_gt150met );
    categories.push_back( cat_ge2j_ge2t_gt200met );
    //categories.push_back( cat_ge2j_ge2t_gt250met );
    //categories.push_back( cat_ge3j_ge0t_gt0met );
    //categories.push_back( cat_ge3j_ge0t_gt50met );
    //categories.push_back( cat_ge3j_ge0t_gt100met );
    //categories.push_back( cat_ge3j_ge0t_gt150met );
    //categories.push_back( cat_ge3j_ge0t_gt200met );
    //categories.push_back( cat_ge3j_ge0t_gt250met );
    //categories.push_back( cat_ge3j_ge1t_gt0met );
    //categories.push_back( cat_ge3j_ge1t_gt50met );
    //categories.push_back( cat_ge3j_ge1t_gt100met );
    //categories.push_back( cat_ge3j_ge1t_gt150met );
    //categories.push_back( cat_ge3j_ge1t_gt200met );
    //categories.push_back( cat_ge3j_ge1t_gt250met );
    //categories.push_back( cat_ge3j_ge2t_gt0met );
    //categories.push_back( cat_ge3j_ge2t_gt50met );
    //categories.push_back( cat_ge3j_ge2t_gt100met );
    //categories.push_back( cat_ge3j_ge2t_gt150met );
    //categories.push_back( cat_ge3j_ge2t_gt200met );
    //categories.push_back( cat_ge3j_ge2t_gt250met );
    //categories.push_back( cat_ge3j_ge3t_gt0met );
    //categories.push_back( cat_ge3j_ge3t_gt50met );
    //categories.push_back( cat_ge3j_ge3t_gt100met );
    //categories.push_back( cat_ge3j_ge3t_gt150met );
    //categories.push_back( cat_ge3j_ge3t_gt200met );
    //categories.push_back( cat_ge3j_ge3t_gt250met );


    // Declare variables

    //var_x = new varInfo_1D( TString v_title, TString v_titleX, TString v_tex, TString v_label, int v_nBins, double v_min, double v_max );

    var_yield              = new varInfo_1D( "Yields", "Yields", "Yields", "yields", 1, 0.5, 1.5, true );
    //var_yield_noSF         = new varInfo_1D( "Yields, no Scale Factors", "Yields", "Yields,~no~Scale~Factors", "yields_noSF", 1, 0.5, 1.5 );
    //var_yield_only_bTagSF  = new varInfo_1D( "Yields, only bTag Scale Factors", "Yields", "Yields,~only~bTag~Scale~Factors", "yields_only_bTagSF", 1, 0.5, 1.5 );
    //var_yield_only_lepSF   = new varInfo_1D( "Yields, only lepton Scale Factors", "Yields", "Yields,~only~lepton~Scale~Factors", "yields_only_lepSF", 1, 0.5, 1.5 );
    //var_yield_only_topPtSF = new varInfo_1D( "Yields, only top Scale Factors", "Yields", "Yields,~only~topPt~Scale~Factors", "yields_only_topPtSF", 1, 0.5, 1.5 );
    /*
    var_nGenLep     = new varInfo_1D( "Number of Gen Leptons from Hard Process", "nGenLeptons", "Number of Gen Leptons from Hard Process", "nGenLeptons", 6, 0, 6 );
    var_nGenNu      = new varInfo_1D( "Number of Gen Nuetrinos from Hard Process", "nGenNeutrinos", "Number of Gen Neutrinos from Hard Process", "nGenNuetrinos", 6, 0, 6 );
    */
    var_nJets       = new varInfo_1D( "Number of Selected Jets", "nJets", "Number of Selected Jets", "nJets", 11, -0.5, 10.5, true );
    /*
    //var_nTags_loose = new varInfo_1D( "Number of b-Tagged Jets, loose WP", "nBTaggedJets loose WP", "Number of b-Tagged Jets, loose WP", "nTagsLoose", 7, -0.5, 6.5 );
    var_nTags_med   = new varInfo_1D( "Number of b-Tagged Jets, medium WP", "nBTaggedJets medium WP", "Number of b-Tagged Jets, medium WP", "nTagsMed", 7, -0.5, 6.5 );
    //var_nTags_tight = new varInfo_1D( "Number of b-Tagged Jets, tight WP", "nBTaggedJets tight WP", "Number of b-Tagged Jets, tight WP", "nTagsTight", 7, -0.5, 6.5 );

    //var_mt          = new varInfo_1D( "M_{T}", "M_{T} [GeV]",  "$M_{T}$", "mt", 40, 0.0, 400.0 );
    //var_minDPhi     = new varInfo_1D( "Min. #Delta#Phi( MET, j1,2 )", "#Delta#Phi", "$Min.~\\Delta\\Phi(MET,~j1,2)$", "minDPhi", 20, 0.0, 3.2 );
    */
    var_met         = new varInfo_1D( "MET", "MET [GeV]", "MET", "met", 50, 0.0, 500.0, true );
    var_met_highMT  = new varInfo_1D( "MET, high MT", "MET [GeV]", "MET, high MT", "met_highMT", 50, 0.0, 500.0 );
    var_met_lowMT   = new varInfo_1D( "MET, low MT", "MET [GeV]", "MET, low MT", "met_lowMT", 50, 0.0, 500.0 );
    var_met_withK3K4= new varInfo_1D( "MET, with K3 K4", "MET [GeV]", "MET, with K3 K4", "met_withK3K4", 50, 0.0, 500.0 );
    var_genDiNuPt   = new varInfo_1D( "diNuPt", "p_{T} [GeV]", "diNuPt", "diNuPt", 50, 0.0, 500.0 );
    var_genDiNuPt_highMT = new varInfo_1D( "diNuPt, MT>150", "p_{T} [GeV]", "diNuPt, MT>150", "diNuPt_highMT", 50, 0.0, 500.0 );
    var_genDiNuPt_lowMT = new varInfo_1D( "diNuPt, MT<150", "p_{T} [GeV]", "diNuPt, MT<150", "diNuPt_lowMT", 50, 0.0, 500.0 );
    
    /*
    //var_met_lowDM   = new varInfo_1D( "MET, low #DeltaM", "MET [GeV]", "$MET,~low~{\\delta}M$", "met_lowDM", 50, 0.0, 500.0 );
    //var_met_highDM  = new varInfo_1D( "MET, high #DeltaM", "MET [GeV]", "$MET,~high~{\\delta}M$", "met_highDM", 50, 0.0, 500.0 );
    var_met_phi     = new varInfo_1D( "MET #phi", "MET #phi", "$MET \\phi$", "met_phi", 20, -3.2, 3.2 );
    //var_mt2w        = new varInfo_1D( "MT2W", "MT2W [GeV]", "$M_{T2}^{W}$", "mt2w", 50, 0.0, 510.0 );
    //var_hadTopChi2  = new varInfo_1D( "Hadronic Top #Chi^{2}", "#Chi^{2}", "$hadronic~t~\\chi^{2}$", "hadTopChi2", 20, 0.0, 100 );
    //var_htRatio     = new varInfo_1D( "H_{T} Ratio", "H_{T} Ratio", "$H_{T} Ratio$", "htRatio", 25, 0.0, 1.0 );
    
    var_mu_pt     = new varInfo_1D( "Muon, p_{T}", "p_{T} [GeV]", "$Muon,~p_{T}$", "mu_pt", 30, 0.0, 300.0 );
    var_mu_eta    = new varInfo_1D( "Muon, #eta", "#eta", "$Muon,~\\eta$", "mu_eta", 20, -3.0, 3.0 );
    //var_mu_phi    = new varInfo_1D( "Muon, #phi", "#phi", "$Muon,~\\phi$", "mu_phi", 20, -3.2, 3.2 );
    var_el_pt     = new varInfo_1D( "Electron, p_{T}", "p_{T} [GeV]", "$Electron,~p_{T}$", "el_pt", 30, 0.0, 300.0 );
    var_el_eta    = new varInfo_1D( "Electron, #eta", "#eta", "$Electron,~\\eta$", "el_eta", 20, -3.0, 3.0 );
    //var_el_phi    = new varInfo_1D( "Electron, #phi", "#phi", "$Electron,~\\phi$", "el_phi", 20, -3.2, 3.2 );
    var_lep1_pt     = new varInfo_1D( "Leading lepton, p_{T}", "p_{T} [GeV]", "$Leading lepton,~p_{T}$", "lep1_pt", 30, 0.0, 300.0 );
    //var_lep1_eta    = new varInfo_1D( "Leading lepton, #eta", "#eta", "$Leading lepton,~\\eta$", "lep1_eta", 20, -3.0, 3.0 );
    //var_lep1_phi    = new varInfo_1D( "Leading lepton, #phi", "#phi", "$Leading lepton,~\\phi$", "lep1_phi", 20, -3.2, 3.2 );
    var_lep2_pt     = new varInfo_1D( "Trailing lepton, p_{T}", "p_{T} [GeV]", "$Trailing lepton,~p_{T}$", "lep2_pt", 20, 0.0, 200.0 );
    //var_lep2_eta    = new varInfo_1D( "Trailing lepton, #eta", "#eta", "$Trailing lepton,~\\eta$", "lep2_eta", 20, -3.0, 3.0 );
    //var_lep2_phi    = new varInfo_1D( "Trailing lepton, #phi", "#phi", "$Trailing lepton,~\\phi$", "lep2_phi", 20, -3.2, 3.2 );
    var_diLep_mass  = new varInfo_1D( "DiLepton Invariant Mass", "Mass [GeV]", "$Dilepton~Invariant~Mass$", "diLep_mass", 50, 0, 500.0 );
    */
    var_diLep_pt  = new varInfo_1D( "DiLepton p_{T}", "p_{T} [GeV]", "$Dilepton~p_{T}$", "diLep_pt", 20, 0, 500.0, true );
    /*
    var_diLep_pt_emu  = new varInfo_1D( "DiLepton p_{T}, emu", "p_{T} [GeV]", "$Dilepton~p_{T},~emu$", "diLep_pt_emu", 20, 0, 500.0 );
    var_diLep_pt_mue  = new varInfo_1D( "DiLepton p_{T}, mue", "p_{T} [GeV]", "$Dilepton~p_{T},~mue$", "diLep_pt_mue", 20, 0, 500.0 );
    var_deltaPt_lep1_lep2  = new varInfo_1D( "#Delta p_{T}, lep1, lep2", "p_{T} [GeV]", "$\\Delta~p_{T},~lep1,~lep2$", "deltaPt_lep1_lep2", 100, -500, 500.0 );
    var_deltaPhi_lep1_lep2  = new varInfo_1D( "#Delta #phi, lep1, lep2", "#phi", "$\\Delta~\\phi,~lep1,~lep2$", "deltaPhi_lep1_lep2", 16, 0, 3.2 );

    var_jet_pt     = new varInfo_1D( "Jet, p_{T}", "p_{T} [GeV]", "$Jet,~p_{T}$", "jet_pt", 30, 0.0, 300.0 );
    var_jet_csv    = new varInfo_1D( "Jet, bTag Discriminant, CSV", "CSV", "$Jet,~b-Tag~discriminant,~CSV$", "jet_csv", 30, -0.1, 1.1 );
    var_jet_1_pt     = new varInfo_1D( "Leading Jet, p_{T}", "p_{T} [GeV]", "$Leading~Jet,~p_{T}$", "jet_1_pt", 30, 0.0, 300.0 );
    var_jet_2_pt     = new varInfo_1D( "2nd Leading Jet, p_{T}", "p_{T} [GeV]", "$2nd~Leading~Jet,~p_{T}$", "jet_2_pt", 30, 0.0, 300.0 );
    var_ttbar_px     = new varInfo_1D( "ttbar p_{X}", "p_{X} [GeV]", "$t\\bar{t}~p_{X}$", "ttbar_pX", 20, 0, 500.0 );
    var_ttbar_py     = new varInfo_1D( "ttbar p_{Y}", "p_{Y} [GeV]", "$t\\bar{t}~p_{Y}$", "ttbar_pY", 20, 0, 500.0 );
    var_ttbar_pt     = new varInfo_1D( "ttbar p_{T}", "p_{T} [GeV]", "$t\\bar{t}~p_{T}$", "ttbar_pT", 20, 0, 500.0 );
    */
    
    // Fill variables vector
    vars_1D.push_back( var_yield );
    //vars_1D.push_back( var_yield_noSF );
    //vars_1D.push_back( var_yield_only_bTagSF );
    //vars_1D.push_back( var_yield_only_lepSF );
    //vars_1D.push_back( var_yield_only_topPtSF );
    /*
    vars_1D.push_back( var_nGenLep );
    vars_1D.push_back( var_nGenNu );
    */
    vars_1D.push_back( var_nJets );
    /*
    //vars_1D.push_back( var_nTags_loose );
    vars_1D.push_back( var_nTags_med );
    //vars_1D.push_back( var_nTags_tight );
    //vars_1D.push_back( var_mt );
    //vars_1D.push_back( var_minDPhi );
    */
    vars_1D.push_back( var_met );
    vars_1D.push_back( var_met_highMT );
    vars_1D.push_back( var_met_lowMT );
    vars_1D.push_back( var_met_withK3K4 );
    vars_1D.push_back( var_genDiNuPt );
    vars_1D.push_back( var_genDiNuPt_highMT );
    vars_1D.push_back( var_genDiNuPt_lowMT );
    /*
    //vars_1D.push_back( var_met_lowDM );
    //vars_1D.push_back( var_met_highDM );
    vars_1D.push_back( var_met_phi );
    //vars_1D.push_back( var_mt2w );
    //vars_1D.push_back( var_hadTopChi2 );
    //vars_1D.push_back( var_htRatio );
    vars_1D.push_back( var_mu_pt );
    vars_1D.push_back( var_mu_eta );
    //vars_1D.push_back( var_mu_phi );
    vars_1D.push_back( var_el_pt );
    vars_1D.push_back( var_el_eta );
    //vars_1D.push_back( var_el_phi );
    vars_1D.push_back( var_lep1_pt );
    //vars_1D.push_back( var_lep1_eta );
    //vars_1D.push_back( var_lep1_phi );
    vars_1D.push_back( var_lep2_pt );
    //vars_1D.push_back( var_lep2_eta );
    //vars_1D.push_back( var_lep2_phi );
    vars_1D.push_back( var_diLep_mass );
    */
    vars_1D.push_back( var_diLep_pt );
    /*
    vars_1D.push_back( var_diLep_pt_emu );
    vars_1D.push_back( var_diLep_pt_mue );
    vars_1D.push_back( var_deltaPt_lep1_lep2 );
    vars_1D.push_back( var_deltaPhi_lep1_lep2 );
    vars_1D.push_back( var_jet_pt );
    vars_1D.push_back( var_jet_csv );
    vars_1D.push_back( var_jet_1_pt );
    vars_1D.push_back( var_jet_2_pt );
    vars_1D.push_back( var_ttbar_px );
    vars_1D.push_back( var_ttbar_py );
    vars_1D.push_back( var_ttbar_pt );
    */
    //
    // Histogram Contructors
    //
    for(int iVar=0; iVar<(int)vars_1D.size(); iVar++){
      
      for(int iClassy=0; iClassy<(int)classifications.size(); iClassy++){
	for(int iSys=0; iSys<(int)systematics.size(); iSys++){

	  if(!systematics[iSys]->isShapeSys) continue;
	  
	  for(int iCat=0; iCat<(int)categories.size(); iCat++){
	    
	    int h_idx = iClassy*nSys*nCats + iSys*nCats + iCat;
	    
	    if( systematics[iSys]->id != k_nominal && 
		!(vars_1D[iVar]->fillAllSys)          )  continue;
	    
	    vars_1D[iVar]->histo_[ h_idx ] = new TH1D( "h__"+vars_1D[iVar]->label+"__"+classifications[iClassy]->label+"__"+systematics[iSys]->label+"__"+categories[iCat]->label, vars_1D[iVar]->title+";"+vars_1D[iVar]->titleX, vars_1D[iVar]->nBins, vars_1D[iVar]->bin_min, vars_1D[iVar]->bin_max );

	  } // end loop over categories
	} // end loop over systematics
      } // end loop over classifications

    } // end loop over vars

    
  } // end constructor
      
  
}; // end class histoHelper

#endif
