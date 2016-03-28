void nJetsSF_plot()
{
//=========Macro generated from canvas: can/can
//=========  (Thu Mar 10 17:08:47 2016) by ROOT version6.02/05
   TCanvas *can = new TCanvas("can", "can",0,0,800,1000);
   gStyle->SetOptStat(0);
   can->Range(25,0.304675,275,1.737925);
   can->SetFillColor(0);
   can->SetBorderMode(0);
   can->SetBorderSize(2);
   can->SetFrameBorderMode(0);
   can->SetFrameBorderMode(0);
   Double_t xAxis1[5] = {50, 100, 150, 200, 250}; 
   
   TH1D *h_k31 = new TH1D("h_k31","nJets Scale Factors, for E_{T}^{miss} > bin low edge",4, xAxis1);
   h_k31->SetBinContent(1,1.08);
   h_k31->SetBinContent(2,1.06);
   h_k31->SetBinContent(3,1.17);
   h_k31->SetBinContent(4,1.02);
   h_k31->SetBinError(1,0.06);
   h_k31->SetBinError(2,0.1);
   h_k31->SetBinError(3,0.24);
   h_k31->SetBinError(4,0.52);
   h_k31->SetEntries(4);
   h_k31->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   h_k31->SetLineColor(ci);
   h_k31->GetXaxis()->SetTitle("E_{T}^{miss}[GeV]");
   h_k31->GetXaxis()->SetLabelFont(42);
   h_k31->GetXaxis()->SetLabelSize(0.035);
   h_k31->GetXaxis()->SetTitleSize(0.035);
   h_k31->GetXaxis()->SetTitleFont(42);
   h_k31->GetYaxis()->SetTitle("nJets Scale Factor");
   h_k31->GetYaxis()->SetLabelFont(42);
   h_k31->GetYaxis()->SetLabelSize(0.035);
   h_k31->GetYaxis()->SetTitleSize(0.035);
   h_k31->GetYaxis()->SetTitleOffset(1.5);
   h_k31->GetYaxis()->SetTitleFont(42);
   h_k31->GetZaxis()->SetLabelFont(42);
   h_k31->GetZaxis()->SetLabelSize(0.035);
   h_k31->GetZaxis()->SetTitleSize(0.035);
   h_k31->GetZaxis()->SetTitleFont(42);
   h_k31->Draw("e1");
   TLine *line = new TLine(50,1.08,250,1.08);

   ci = TColor::GetColor("#ff9933");
   line->SetLineColor(ci);
   line->SetLineWidth(3);
   line->Draw();
   line = new TLine(50,0.92,250,0.92);

   ci = TColor::GetColor("#66ccff");
   line->SetLineColor(ci);
   line->SetLineWidth(3);
   line->Draw();
   Double_t xAxis2[5] = {50, 100, 150, 200, 250}; 
   
   TH1D *h_k32 = new TH1D("h_k32","nJets Scale Factors, for E_{T}^{miss} > bin low edge",4, xAxis2);
   h_k32->SetBinContent(1,1.08);
   h_k32->SetBinContent(2,1.06);
   h_k32->SetBinContent(3,1.17);
   h_k32->SetBinContent(4,1.02);
   h_k32->SetBinError(1,0.06);
   h_k32->SetBinError(2,0.1);
   h_k32->SetBinError(3,0.24);
   h_k32->SetBinError(4,0.52);
   h_k32->SetEntries(4);
   h_k32->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   h_k32->SetLineColor(ci);
   h_k32->GetXaxis()->SetTitle("E_{T}^{miss}[GeV]");
   h_k32->GetXaxis()->SetLabelFont(42);
   h_k32->GetXaxis()->SetLabelSize(0.035);
   h_k32->GetXaxis()->SetTitleSize(0.035);
   h_k32->GetXaxis()->SetTitleFont(42);
   h_k32->GetYaxis()->SetTitle("nJets Scale Factor");
   h_k32->GetYaxis()->SetLabelFont(42);
   h_k32->GetYaxis()->SetLabelSize(0.035);
   h_k32->GetYaxis()->SetTitleSize(0.035);
   h_k32->GetYaxis()->SetTitleOffset(1.5);
   h_k32->GetYaxis()->SetTitleFont(42);
   h_k32->GetZaxis()->SetLabelFont(42);
   h_k32->GetZaxis()->SetLabelSize(0.035);
   h_k32->GetZaxis()->SetTitleSize(0.035);
   h_k32->GetZaxis()->SetTitleFont(42);
   h_k32->Draw("e1 same");
   Double_t xAxis3[5] = {50, 100, 150, 200, 250}; 
   
   TH1D *h_k43 = new TH1D("h_k43","nJets Scale Factors vs E_{T}^{miss}",4, xAxis3);
   h_k43->SetBinContent(1,0.92);
   h_k43->SetBinContent(2,0.93);
   h_k43->SetBinContent(3,1.11);
   h_k43->SetBinContent(4,1.07);
   h_k43->SetBinError(1,0.06);
   h_k43->SetBinError(2,0.09);
   h_k43->SetBinError(3,0.22);
   h_k43->SetBinError(4,0.48);
   h_k43->SetEntries(4);
   h_k43->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   h_k43->SetLineColor(ci);
   h_k43->GetXaxis()->SetTitle("E_{T}^{miss}[GeV]");
   h_k43->GetXaxis()->SetLabelFont(42);
   h_k43->GetXaxis()->SetLabelSize(0.035);
   h_k43->GetXaxis()->SetTitleSize(0.035);
   h_k43->GetXaxis()->SetTitleFont(42);
   h_k43->GetYaxis()->SetTitle("nJets Scale Factor");
   h_k43->GetYaxis()->SetLabelFont(42);
   h_k43->GetYaxis()->SetLabelSize(0.035);
   h_k43->GetYaxis()->SetTitleSize(0.035);
   h_k43->GetYaxis()->SetTitleFont(42);
   h_k43->GetZaxis()->SetLabelFont(42);
   h_k43->GetZaxis()->SetLabelSize(0.035);
   h_k43->GetZaxis()->SetTitleSize(0.035);
   h_k43->GetZaxis()->SetTitleFont(42);
   h_k43->Draw("e1 same");
   
   TLegend *leg = new TLegend(0.15,0.7,0.4,0.87,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_k3","nJets Scale Factor, K3","l");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("h_k4","nJets Scale Factor, K4","l");

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.15,0.9221605,0.85,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *AText = pt->AddText("nJets Scale Factors, for E_{T}^{miss} > bin low edge");
   pt->Draw();
   can->Modified();
   can->cd();
   can->SetSelected(can);
}
