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


///////////////////////////////////////////////
//
// Global Vars
//
///////////////////////////////////////////////
const int nClassy = 7;
const int nSys    = 25; // was 45
const int nCats   = 12;

const int nHists  = nClassy*nSys*nCats;

const int nPDFs = 100;

///////////////////////////////////////////////
//
// enums for classification
//
///////////////////////////////////////////////


///////////////////////////////////////////////
enum classy_id{ k_ee1lep, 
		k_ge2lep, 
		k_ZtoNuNu,
		k_incl,
		k_NCR4,
		k_NCR5,
		k_NCR6
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
	     k_nJetsSFK3Up,
	     k_nJetsSFK3Down,
	     k_nJetsSFK4Up,
	     k_nJetsSFK4Down,
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
	     k_metRes_ge4j_ge200mt2w_met_450_inf_Down,
	     k_diNuSF_met_250_350_Up,
	     k_diNuSF_met_250_350_Down,
	     k_diNuSF_met_350_450_Up,
	     k_diNuSF_met_350_450_Down,
	     k_diNuSF_met_450_inf_Up,
	     k_diNuSF_met_450_inf_Down,
	     k_metRes_Up,
	     k_metRes_Down,
	     k_diNuSF_Up,
	     k_diNuSF_Down
};

///////////////////////////////////////////////
enum cats_id{ k_baseline,
	      k_ee2j_ge250met,
	      k_ee2j_ge250met_ge6p4modTop,
	      k_ge2j_ge250met,
	      k_ge2j_ge250met_ge6p4modTop,
	      k_ee3j_ge250met,
	      k_ee3j_ge250met_lt200mt2w,
	      k_ee3j_ge250met_ge200mt2w,
	      k_ge3j_ge250met,
	      k_ge3j_met_250_275,
	      k_ge3j_met_275_325,
	      k_ge3j_met_325_inf,
	      k_ge3j_ge250met_lt200mt2w,
	      k_ge3j_ge250met_ge200mt2w,
	      k_ge4j_ge250met,
	      k_ge4j_ge250met_lt200mt2w,
	      k_ge4j_met_250_325_lt200mt2w,
	      k_ge4j_met_325_inf_lt200mt2w,
	      k_ge4j_ge250met_ge200mt2w,
	      k_ge4j_met_250_350_ge200mt2w,
	      k_ge4j_met_350_450_ge200mt2w,
	      k_ge4j_met_450_inf_ge200mt2w
    
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

    case(k_NCR4):
      id = whichClassy;
      title = "==2 selected leptons";
      tex = "==2~selected~leptons";
      label = "ncr4";
      break;

    case(k_NCR5):
      id = whichClassy;
      title = "==1 selected lepton, ==1 veto lepton";
      tex = "==1~selected~lepton,~==1~veto~lepton";
      label = "ncr5";
      break;

    case(k_NCR6):
      id = whichClassy;
      title = "==1 selected lepton, pfCH || tau ";
      tex = "==1~selected~lepton,~pfCH~or~hadTau";
      label = "ncr6";
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
      yieldSF = 1.046;
      break;
      
    case(k_lumiDown):
      id = whichSys;
      title = "Lumi, Scale Down";
      tex = "Lumi,~Scale~Down";
      label = "lumi_scaleDown";
      isShapeSys = false;
      yieldSF = 0.954;
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

    case(k_nJetsSFK3Up):
      id = whichSys;
      title = "nJets SFs, K3, Scale Up";
      tex = "nJets~SF,~K3,~Scale~Up";
      label = "nJetsSFK3_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_nJetsSFK3Down):
      id = whichSys;
      title = "nJets SFs, K3, Scale Down";
      tex = "nJets~SF,~K3,~Scale~Down";
      label = "nJetsSFK3_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_nJetsSFK4Up):
      id = whichSys;
      title = "nJets SFs, K4, Scale Up";
      tex = "nJets~SF,~K4,~Scale~Up";
      label = "nJetsSFK4_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_nJetsSFK4Down):
      id = whichSys;
      title = "nJets SFs, K4, Scale Down";
      tex = "nJets~SF,~K4,~Scale~Down";
      label = "nJetsSFK4_scaleDown";
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

    case(k_diNuSF_met_250_350_Up):
      id = whichSys;
      title = "diNu SF, 250<MET<350, Scale Up";
      tex = "diNuetrino SF,~250<MET<350,~Scale~Up";
      label = "diNuSF_met_250_350_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;
      
    case(k_diNuSF_met_250_350_Down):
      id = whichSys;
      title = "diNu SF, 250<MET<350, Scale Down";
      tex = "diNuetrino SF,~250<MET<350,~Scale~Down";
      label = "diNuSF_met_250_350_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_diNuSF_met_350_450_Up):
      id = whichSys;
      title = "diNu SF, 350<MET<450, Scale Up";
      tex = "diNuetrino SF,~350<MET<450,~Scale~Up";
      label = "diNuSF_met_350_450_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;
      
    case(k_diNuSF_met_350_450_Down):
      id = whichSys;
      title = "diNu SF, 350<MET<450, Scale Down";
      tex = "diNuetrino SF,~350<MET<450,~Scale~Down";
      label = "diNuSF_met_350_450_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_diNuSF_met_450_inf_Up):
      id = whichSys;
      title = "diNu SF, MET>450, Scale Up";
      tex = "diNuetrino SF,~MET>450,~Scale~Up";
      label = "diNuSF_met_450_inf_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;
      
    case(k_diNuSF_met_450_inf_Down):
      id = whichSys;
      title = "diNu SF, MET>450, Scale Down";
      tex = "diNuetrino SF,~MET>450,~Scale~Down";
      label = "diNuSF_met_450_inf_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;
      
    case(k_metRes_Up):
      id = whichSys;
      title = "MET Resolution SF, Scale Up";
      tex = "MET~Resolution~SF,~Scale~Up";
      label = "metRes_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_metRes_Down):
      id = whichSys;
      title = "MET Resolution SF, Scale Down";
      tex = "MET~Resolution~SF,~Scale~Down";
      label = "metRes_scaleDown";
      isShapeSys = true;
      yieldSF = 1.0;
      break;

    case(k_diNuSF_Up):
      id = whichSys;
      title = "diNu SF, Scale Up";
      tex = "diNuetrino~SF,~Scale~Up";
      label = "diNuSF_scaleUp";
      isShapeSys = true;
      yieldSF = 1.0;
      break;
      
    case(k_diNuSF_Down):
      id = whichSys;
      title = "diNu SF, Scale Down";
      tex = "diNuetrino~SF,~Scale~Down";
      label = "diNuSF_scaleDown";
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

    case(k_ee2j_ge250met):
      id = whichCat;
      title = "==2 jets";
      tex = "$==2~jets$";
      label = "ee2j_ge250met";
      break;
      
    case(k_ee3j_ge250met):
      id = whichCat;
      title = "==3 jets";
      tex = "$==3~jets$";
      label = "ee3j_ge250met";
      break;
    
    case(k_ge3j_ge250met):
      id = whichCat;
      title = ">=3 jets";
      tex = "$\\ge3~jets$";
      label = "ge3j_ge250met";
      break;
    
    case(k_ge4j_ge250met):
      id = whichCat;
      title = ">=4 jets";
      tex = "${\\ge}4~jets$";
      label = "ge4j_ge250met";
      break;

    case(k_ee2j_ge250met_ge6p4modTop):
      id = whichCat;
      title = "NCR 4,5,6, ==2 jets, ModifiedTopness>=6.4";
      tex = "$NCR~4,~5,~6,~==2~jets,~ModifiedTopness\\ge6.4$";
      label = "ee2j_ge250met_ge6p4modTop";
      break;

    case(k_ge2j_ge250met_ge6p4modTop):
      id = whichCat;
      title = "NCR 4,5,6, >=2 jets, ModifiedTopness>=6.4";
      tex = "$NCR~4,~5,~6,~\\ge2~jets,~ModifiedTopness\\ge6.4$";
      label = "ge2j_ge250met_ge6p4modTop";
      break;
      
    case(k_ge3j_ge250met_ge200mt2w):
      id = whichCat;
      title = "NCR 4,5,6, >=3 jets, MT2W>=200";
      tex = "$NCR~4,~5,~6,~\\ge3~jets,~MT2W\\ge200$";
      label = "ge3j_ge250met_ge200mt2w";
      break;

    case(k_ge3j_ge250met_lt200mt2w):
      id = whichCat;
      title = "NCR 4,5,6, >=3 jets, MT2W<200";
      tex = "$NCR~4,~5,~6,~\\ge3~jets,~MT2W<200$";
      label = "ge3j_ge250met_lt200mt2w";
      break;

    case(k_ge3j_met_250_275):
      id = whichCat;
      title = "NCR 4,5,6, >=3 jets, 250<=MET<275";
      tex = "$NCR~4,~5,~6,~\\ge3~jets,~250<MET<275$";
      label = "ge3j_met_250_275";
      break;

    case(k_ge3j_met_275_325):
      id = whichCat;
      title = "NCR 4,5,6, >=3 jets, 275<=MET<325";
      tex = "$NCR~4,~5,~6,~\\ge3~jets,~275<MET<325$";
      label = "ge3j_met_275_325";
      break;
      
    case(k_ge3j_met_325_inf):
      id = whichCat;
      title = "NCR 4,5,6, >=3 jets, MET>325";
      tex = "$NCR~4,~5,~6,~\\ge3~jets,~MET>325$";
      label = "ge3j_met_325_inf";
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
  classyInfo *classy_ee1lep;
  classyInfo *classy_ge2lep;
  classyInfo *classy_ZtoNuNu;
  classyInfo *classy_incl;
  classyInfo *classy_NCR4;
  classyInfo *classy_NCR5;
  classyInfo *classy_NCR6;

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
  sysInfo *sys_nJetsSFK3_scaleUp;
  sysInfo *sys_nJetsSFK3_scaleDown;
  sysInfo *sys_nJetsSFK4_scaleUp;
  sysInfo *sys_nJetsSFK4_scaleDown;
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
  sysInfo *sys_diNuSF_met_250_350_Up;
  sysInfo *sys_diNuSF_met_250_350_Down;
  sysInfo *sys_diNuSF_met_350_450_Up;
  sysInfo *sys_diNuSF_met_350_450_Down;
  sysInfo *sys_diNuSF_met_450_inf_Up;
  sysInfo *sys_diNuSF_met_450_inf_Down;
  sysInfo *sys_metRes_Up;
  sysInfo *sys_metRes_Down;
  sysInfo *sys_diNuSF_Up;
  sysInfo *sys_diNuSF_Down;
  
  std::vector<catInfo*> categories;
  catInfo *cat_baseLine;
  catInfo *cat_ee2j_ge250met;
  catInfo *cat_ee3j_ge250met;
  catInfo *cat_ge3j_ge250met;
  catInfo *cat_ge4j_ge250met;
  catInfo *cat_ee2j_ge250met_ge6p4modTop;
  catInfo *cat_ge2j_ge250met_ge6p4modTop;
  catInfo *cat_ge3j_ge250met_ge200mt2w;
  catInfo *cat_ge3j_ge250met_lt200mt2w;
  catInfo *cat_ge3j_met_250_275;
  catInfo *cat_ge3j_met_275_325;
  catInfo *cat_ge3j_met_325_inf;


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
  varInfo_1D *var_nTags;
  varInfo_1D *var_mt;
  varInfo_1D *var_minDPhi;
  varInfo_1D *var_met;
  varInfo_1D *var_met_lowDM;
  varInfo_1D *var_met_highDM;
  varInfo_1D *var_mt2w;
  varInfo_1D *var_mt2w_max;
  varInfo_1D *var_modTopness;
  
  histoHelper(){

    // Declare classifications
    classy_ee1lep  = new classyInfo( k_ee1lep );
    classy_ge2lep  = new classyInfo( k_ge2lep );
    classy_ZtoNuNu = new classyInfo( k_ZtoNuNu );
    classy_incl    = new classyInfo( k_incl );
    classy_NCR4    = new classyInfo( k_NCR4 );
    classy_NCR5    = new classyInfo( k_NCR5 );
    classy_NCR6    = new classyInfo( k_NCR6 );

    // Fill classifications vector
    classifications.push_back( classy_ee1lep );
    classifications.push_back( classy_ge2lep );
    classifications.push_back( classy_ZtoNuNu );
    classifications.push_back( classy_incl );
    classifications.push_back( classy_NCR4 );
    classifications.push_back( classy_NCR5 );
    classifications.push_back( classy_NCR6 );


    // Declare systematics
    sys_nominal             = new sysInfo( k_nominal );
    sys_lumi_scaleUp        = new sysInfo( k_lumiUp );
    sys_lumi_scaleDown      = new sysInfo( k_lumiDown );
    sys_bTagEffHF_scaleUp   = new sysInfo( k_bTagEffHFUp );
    sys_bTagEffHF_scaleDown = new sysInfo( k_bTagEffHFDown );
    sys_bTagEffLF_scaleUp   = new sysInfo( k_bTagEffLFUp );
    sys_bTagEffLF_scaleDown = new sysInfo( k_bTagEffLFDown );
    sys_lepSF_scaleUp       = new sysInfo( k_lepSFUp );
    sys_lepSF_scaleDown     = new sysInfo( k_lepSFDown );
    sys_topPtSF_scaleUp     = new sysInfo( k_topPtSFUp );
    sys_topPtSF_scaleDown   = new sysInfo( k_topPtSFDown );
    sys_nJetsSFK3_scaleUp   = new sysInfo( k_nJetsSFK3Up );
    sys_nJetsSFK3_scaleDown = new sysInfo( k_nJetsSFK3Down );
    sys_nJetsSFK4_scaleUp   = new sysInfo( k_nJetsSFK4Up );
    sys_nJetsSFK4_scaleDown = new sysInfo( k_nJetsSFK4Down );
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
    sys_diNuSF_met_250_350_Up   = new sysInfo( k_diNuSF_met_250_350_Up );
    sys_diNuSF_met_250_350_Down = new sysInfo( k_diNuSF_met_250_350_Down );
    sys_diNuSF_met_350_450_Up   = new sysInfo( k_diNuSF_met_350_450_Up );
    sys_diNuSF_met_350_450_Down = new sysInfo( k_diNuSF_met_350_450_Down );
    sys_diNuSF_met_450_inf_Up   = new sysInfo( k_diNuSF_met_450_inf_Up );
    sys_diNuSF_met_450_inf_Down = new sysInfo( k_diNuSF_met_450_inf_Down );
    sys_metRes_Up   = new sysInfo( k_metRes_Up );
    sys_metRes_Down = new sysInfo( k_metRes_Down );
    sys_diNuSF_Up   = new sysInfo( k_diNuSF_Up );
    sys_diNuSF_Down = new sysInfo( k_diNuSF_Down );
    

    // Fill systematics vector
    systematics.push_back( sys_nominal );
    systematics.push_back( sys_lumi_scaleUp );
    systematics.push_back( sys_lumi_scaleDown );
    systematics.push_back( sys_bTagEffHF_scaleUp );
    systematics.push_back( sys_bTagEffHF_scaleDown );
    systematics.push_back( sys_bTagEffLF_scaleUp );
    systematics.push_back( sys_bTagEffLF_scaleDown );
    systematics.push_back( sys_lepSF_scaleUp );
    systematics.push_back( sys_lepSF_scaleDown );
    systematics.push_back( sys_topPtSF_scaleUp );
    systematics.push_back( sys_topPtSF_scaleDown );
    systematics.push_back( sys_nJetsSFK3_scaleUp );
    systematics.push_back( sys_nJetsSFK3_scaleDown );
    systematics.push_back( sys_nJetsSFK4_scaleUp );
    systematics.push_back( sys_nJetsSFK4_scaleDown );
    systematics.push_back( sys_pdf_scaleUp );
    systematics.push_back( sys_pdf_scaleDown );
    systematics.push_back( sys_alphas_scaleUp );
    systematics.push_back( sys_alphas_scaleDown );
    systematics.push_back( sys_q2_scaleUp );
    systematics.push_back( sys_q2_scaleDown );
    /*
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
    systematics.push_back( sys_diNuSF_met_250_350_Up );
    systematics.push_back( sys_diNuSF_met_250_350_Down );
    systematics.push_back( sys_diNuSF_met_350_450_Up );
    systematics.push_back( sys_diNuSF_met_350_450_Down );
    systematics.push_back( sys_diNuSF_met_450_inf_Up );
    systematics.push_back( sys_diNuSF_met_450_inf_Down );
    */						
    systematics.push_back( sys_metRes_Up );
    systematics.push_back( sys_metRes_Down );
    systematics.push_back( sys_diNuSF_Up );
    systematics.push_back( sys_diNuSF_Down );
    
    // Declare categories
    cat_baseLine                = new catInfo( k_baseline );
    cat_ee2j_ge250met           = new catInfo( k_ee2j_ge250met );
    cat_ee3j_ge250met           = new catInfo( k_ee3j_ge250met );
    cat_ge3j_ge250met           = new catInfo( k_ge3j_ge250met );
    cat_ge4j_ge250met           = new catInfo( k_ge4j_ge250met );
    cat_ee2j_ge250met_ge6p4modTop = new catInfo( k_ee2j_ge250met_ge6p4modTop );
    cat_ge2j_ge250met_ge6p4modTop = new catInfo( k_ge2j_ge250met_ge6p4modTop );
    cat_ge3j_ge250met_ge200mt2w = new catInfo( k_ge3j_ge250met_ge200mt2w );
    cat_ge3j_ge250met_lt200mt2w = new catInfo( k_ge3j_ge250met_lt200mt2w );
    cat_ge3j_met_250_275        = new catInfo( k_ge3j_met_250_275 );
    cat_ge3j_met_275_325        = new catInfo( k_ge3j_met_275_325 );
    cat_ge3j_met_325_inf        = new catInfo( k_ge3j_met_325_inf );
    
    // Fill categories vector
    categories.push_back( cat_baseLine );
    categories.push_back( cat_ee2j_ge250met );
    categories.push_back( cat_ee3j_ge250met );
    categories.push_back( cat_ge3j_ge250met );
    categories.push_back( cat_ge4j_ge250met );
    categories.push_back( cat_ee2j_ge250met_ge6p4modTop );
    categories.push_back( cat_ge2j_ge250met_ge6p4modTop );
    categories.push_back( cat_ge3j_ge250met_ge200mt2w );
    categories.push_back( cat_ge3j_ge250met_lt200mt2w );
    categories.push_back( cat_ge3j_met_250_275 );
    categories.push_back( cat_ge3j_met_275_325 );
    categories.push_back( cat_ge3j_met_325_inf );
    
    
    // Declare variables

    //   var_x = new varInfo_1D( TString v_title, TString v_titleX, TString v_tex, TString v_label, int v_nBins, double v_min, double v_max );

    var_yield     = new varInfo_1D( "Yields", "yields", "Yields", "yields", 1, 0.5, 1.5, true );
    //var_yield_noSF = new varInfo_1D( "Yields, no Scale Factors", "Yields", "Yields,~no~Scale~Factors", "yields_noSF", 1, 0.5, 1.5 );
    //var_yield_only_bTagSF  = new varInfo_1D( "Yields, only bTag Scale Factors", "Yields", "Yields,~only~bTag~Scale~Factors", "yields_only_bTagSF", 1, 0.5, 1.5 );
    //var_yield_only_lepSF   = new varInfo_1D( "Yields, only lepton Scale Factors", "Yields", "Yields,~only~lepton~Scale~Factors", "yields_only_lepSF", 1, 0.5, 1.5 );
    //var_yield_only_topPtSF = new varInfo_1D( "Yields, only top Scale Factors", "Yields", "Yields,~only~topPt~Scale~Factors", "yields_only_topPtSF", 1, 0.5, 1.5 );
    
    var_nGenLep    = new varInfo_1D( "Number of Gen Leptons from Hard Process", "nGenLeptons", "Number of Gen Leptons from Hard Process", "nGenLeptons", 6, 0, 6 );
    var_nGenNu     = new varInfo_1D( "Number of Gen Nuetrinos from Hard Process", "nGenNeutrinos", "Number of Gen Neutrinos from Hard Process", "nGenNuetrinos", 6, 0, 6 );
    var_nJets      = new varInfo_1D( "Number of Selected Jets", "nJets", "Number of Selected Jets", "nJets", 11, -0.5, 10.5 );
    var_nTags      = new varInfo_1D( "Number of b-Tagged Jets", "nBTaggedJets", "Number of b-Tagged Jets", "nTags", 7, -0.5, 6.5 );
    var_mt         = new varInfo_1D( "M_{T}", "M_{T} [GeV]",  "$M_{T}$", "mt", 100, 0.0, 500.0 );
    var_minDPhi    = new varInfo_1D( "Min. #Delta#Phi( MET, j1,2 )", "#Delta#Phi", "$Min.~\\Delta\\Phi(MET,~j1,2)$", "minDPhi", 100, 0.0, 6.0 );
    var_met        = new varInfo_1D( "MET", "MET [GeV]", "MET", "met", 30, 200.0, 800.0 );
    var_met_lowDM  = new varInfo_1D( "MET, low #DeltaM", "MET [GeV]", "$MET,~low~{\\delta}M$", "met_lowDM", 30, 200.0, 800.0 );
    var_met_highDM = new varInfo_1D( "MET, high #DeltaM", "MET [GeV]", "$MET,~high~{\\delta}M$", "met_highDM", 30, 200.0, 800.0 );
    var_mt2w       = new varInfo_1D( "MT2W", "MT2W [GeV]", "$M_{T2}^{W}$", "mt2w", 24, 0.0, 600.0 );
    var_mt2w_max   = new varInfo_1D( "MT2W (max of lep1, lep2)", "MT2W Max [GeV]", "$M_{T2}^{W} Max$", "mt2w_max", 24, 0.0, 600.0 );
    var_modTopness = new varInfo_1D( "Modified Topness", "Modified Topness", "$Topness_{Mod}$", "modTopness", 20, -20.0, 20.0 );
    
    
    // Fill variables vector
    vars_1D.push_back( var_yield );
    //vars_1D.push_back( var_yield_noSF );
    //vars_1D.push_back( var_yield_only_bTagSF );
    //vars_1D.push_back( var_yield_only_lepSF );
    //vars_1D.push_back( var_yield_only_topPtSF );
    vars_1D.push_back( var_nGenLep );
    vars_1D.push_back( var_nGenNu );
    vars_1D.push_back( var_nJets );
    vars_1D.push_back( var_nTags );
    vars_1D.push_back( var_mt );
    vars_1D.push_back( var_minDPhi );
    vars_1D.push_back( var_met );
    vars_1D.push_back( var_met_lowDM );
    vars_1D.push_back( var_met_highDM );
    vars_1D.push_back( var_mt2w );
    vars_1D.push_back( var_mt2w_max );
    vars_1D.push_back( var_modTopness );
    
    //vars_1D.push_back( var_met );

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
