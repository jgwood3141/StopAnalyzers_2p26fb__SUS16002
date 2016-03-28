{

  //TString fName = "Histos/histos__ttbar_2l_powheg_pythia8_50ns.root";
  TString fName = "Histos/histos__allBkg.root";

  cout << "Examining file: " << fName << endl;
  cout << endl;

  TFile *f = new TFile(fName, "read");
 

  TH2D *h = (TH2D*)f->Get("h_partonFlavour_tagJet_vs_probeJet");
  //TH2D *h = (TH2D*)f->Get("h_partonFlavour_tagJet_vs_probeJet_barrelJets");
  
  double mis_c = 0.12;
  double mis_j = 0.015;

  vector<int> lf;
  lf.push_back(0);
  lf.push_back(1);
  lf.push_back(2);
  lf.push_back(3);
  lf.push_back(21);
  
  double tBpB = h->GetBinContent( h->FindBin(5,5) );
  
  double tBpC = h->GetBinContent( h->FindBin(4,5) );

  double tBpJ = 0.0;
  for(int i=0; i<(int)lf.size(); i++){
    tBpJ += h->GetBinContent( h->FindBin(lf[i],5) );
  }

  double tCpB = h->GetBinContent( h->FindBin(5,4) );

  double tJpB = 0.0;
  for(int i=0; i<(int)lf.size(); i++){
    tJpB += h->GetBinContent( h->FindBin(5,lf[i]) );
  }

  double tCpC = h->GetBinContent( h->FindBin(4,4) );

  double tCpJ = 0.0;
  for(int i=0; i<(int)lf.size(); i++){
    tCpJ += h->GetBinContent( h->FindBin(lf[i],4) );
  }

  double tJpC = 0.0;
  for(int i=0; i<(int)lf.size(); i++){
    tJpC += h->GetBinContent( h->FindBin(4,lf[i]) );
  }

  double tJpJ = 0.0;
  for(int i=0; i<(int)lf.size(); i++){
    for(int j=0; j<(int)lf.size(); j++){
      tJpJ += h->GetBinContent( h->FindBin(lf[i],j) );
    }
  }


  cout << "probes tagged = ( tBpB*eff^2 + tBpC*eff*mis_c + tBpJ*eff*mis_j + tCpB*mis_c*eff + tJpB*mis_j*eff + tCpC*mis_c*mis_c + tCpJ*mis_c*mis_j + tJpC*mis_j*mis_c + tJpJ*mis_j*mis_j )" << endl;
  cout << "probes        = ( eff*tBpB + tBpC*eff + tBpJ*eff + tCpB*mis_c + tJpB*mis + tCpC*mis_c + tCtJ*mis_c + tJpC*mis_j + tJpJ*mis_j )" << endl;
  cout << endl;

  TString eq = "( ";
  eq += Form("%2.3f", tBpB);
  eq += "*eff^2";
  eq += " + ";
  eq += Form("%2.3f*%2.3f",tBpC,mis_c);
  eq += "*eff";
  eq += " + ";
  eq += Form("%2.3f*%2.3f",tBpJ,mis_j);
  eq += "*eff";
  eq += " + ";
  eq += Form("%2.3f*%2.3f",tCpB,mis_c);
  eq += "*eff";
  eq += " + ";
  eq += Form("%2.3f*%2.3f",tJpB,mis_j);
  eq += "*eff";
  eq += " + ";
  eq += Form("%2.3f*%2.3f",tCpC,pow(mis_c,2));
  eq += " + ";
  eq += Form("%2.3f*%2.3f",tCpJ,mis_c*mis_j);
  eq += " + ";
  eq += Form("%2.3f*%2.3f",tJpC,mis_j*mis_c);
  eq += " + ";
  eq += Form("%2.3f*%2.5f",tJpJ,pow(mis_j,2));
  eq += " ) / ";

  cout << eq << endl;

  eq = "( ";
  eq += Form("%2.3f", tBpB);
  eq += "*eff";
  eq += " + ";
  eq += Form("%2.3f",tBpC);
  eq += "*eff";
  eq += " + ";
  eq += Form("%2.3f",tBpJ);
  eq += "*eff";
  eq += " + ";
  eq += Form("%2.3f*%2.3f",tCpB,mis_c);
  eq += " + ";
  eq += Form("%2.3f*%2.3f",tJpB,mis_j);
  eq += " + ";
  eq += Form("%2.3f*%2.3f",tCpC,mis_c);
  eq += " + ";
  eq += Form("%2.3f*%2.3f",tCpJ,mis_c);
  eq += " + ";
  eq += Form("%2.3f*%2.3f",tJpC,mis_j);
  eq += " + ";
  eq += Form("%2.3f*%2.3f",tJpJ,mis_j);
  eq += " ) ";

  cout << eq << endl;

  cout << endl;
  cout << endl;


  // Combine everything but eff
  eq = "( ";
  eq += Form("%2.5f", tBpB);
  eq += "*X^2";
  eq += " + ";
  eq += Form("%2.5f",tBpC*mis_c + tBpJ*mis_j + tCpB*mis_c + tJpB*mis_j);
  eq += "*X";
  eq += " + ";
  eq += Form("%2.5f",tCpC*pow(mis_c,2) + tCpJ*mis_c*mis_j + tJpC*mis_j*mis_c + tJpJ*pow(mis_j,2));
  eq += " ) / ";

  cout << eq << endl;

  eq = "( ";
  eq += Form("%2.3f", tBpB + tBpC + tBpJ);
  eq += "*X";
  eq += " + ";
  eq += Form("%2.3f",tCpB*mis_c + tJpB*mis_j + tCpC*mis_c + tCpJ*mis_c + tJpC*mis_j + tJpJ*mis_j);
  eq += " ) ";

  cout << eq << endl;
  
  cout << "======================================================" << endl;
  cout << endl;

  // N_1 = L * sigma_tt * eff_emu * 2 * eff_b * (1-C_b*eff_b) + N_1_bkg
  // N_2 = L * sigma_tt * eff_emu * C_b * eff_b^2 + N_2_bkg

  TString f_ttbar_2l_name = "Histos/histos__ttbar_2l_powheg_pythia8_50ns.root";

  //TString f_allBkg_name = "Histos/histos__ttbar_2l_powheg_pythia8_50ns.root";
  //TString f_allBkg_name = "Histos/histos__allBkg.root";
  TString f_allBkg_name = "Histos/histos__data.root";
  
  TString f_nonTTbarBkg_name = "Histos/histos__nonTTbar2lBkg.root";
  
  TString f_data_name = "Histos/histos__data.root";

  
  //TString hName = "h_nTags_medium_barrelJets__diLeptonCR";
  TString hName = "h_nTags_medium__diLeptonCR";

  double L = 40.024*1e-3;

  double C_b = 1.0;
  //double C_b = 1.0008;
  //double C_b = 0.9793069354;
  //double C_b = 0.915312;

  TFile *f_ttbar_2l = new TFile(f_ttbar_2l_name, "read");
  TH1F *h_nTags_ttbar_2l = (TH1F*)f_ttbar_2l->Get(hName);
  double eff_emu = (double)h_nTags_ttbar_2l->GetEntries()/19665194.0;
  
 
  TFile *f_allBkg = new TFile(f_allBkg_name, "read");
  TH1F *h_nTags_allBkg = (TH1F*)f_allBkg->Get(hName);

  double N_1 = h_nTags_allBkg->GetBinContent( h_nTags_allBkg->FindBin(1.0) );
  double N_2 = h_nTags_allBkg->GetBinContent( h_nTags_allBkg->FindBin(2.0) );

  TFile *f_nonTTbarBkg = new TFile(f_nonTTbarBkg_name, "read");
  TH1F *h_nTags_nonTTbarBkg = (TH1F*)f_nonTTbarBkg->Get(hName);
  
  double N_1_bkg = h_nTags_nonTTbarBkg->GetBinContent( h_nTags_nonTTbarBkg->FindBin( 1.0 ) );
  //double N_1_bkg = 0.0;

  double N_2_bkg = h_nTags_nonTTbarBkg->GetBinContent( h_nTags_nonTTbarBkg->FindBin( 2.0 ) );
  //double N_2_bkg = 0.0;
  
  
  

  cout << "Testing ttbar xsec/eff_b in sum of all bkg" << endl;
  cout << "    N_1 = ( L * sigma_tt * eff_emu * 2 * eff_b * (1 - C_b*eff_b) ) + N_1_bkg" << endl;
  cout << "    N_2 = ( L * sigma_tt * eff_emu * C_b * eff_b^2 ) + N_2_bkg" << endl;
  cout << "         X=sigma_tt,  Y=eff_b" << endl << endl;
  
  cout << N_1 << " = (" << L << " * X * " << eff_emu*2 << " * Y * (" << 1 << "-" << C_b << "*Y) ) + " << N_1_bkg << endl << endl;
  cout << N_2 << " = (" << L << " * X * " << eff_emu*C_b << " * Y^2) + " << N_2_bkg << endl;
  
  
}

