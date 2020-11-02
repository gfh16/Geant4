#include "TH1.h"
#include "TF1.h"
#include "TMath.h"
#include "TStyle.h"
#include "TSystem.h"


Double_t Gaus_fc(Double_t *x,Double_t *para) {
    //Double_t f = N*4*TMath::Pi()*pow(para[0]/(2*TMath::Pi()),1.5)*TMath::Exp(-para[0]*v[0]*v[0]/2)*v[0]*v[0]*dV_of_bin;
    Double_t f = para[0]*TMath::Exp(-0.5*((x[0]-para[1])/para[2])*((x[0]-para[1])/para[2]));
    return f;
}

void Hw7()
{
  // TCanvas *c1 = new TCanvas("c1","c1",0,0,1020,550);
  TCanvas *c1 = new TCanvas("c1","c1",0,0,1520,550);
  c1->SetCanvasSize(1500,500);
  c1->SetFixedAspectRatio(kTRUE);
  c1->Divide(3,1);
  c1->cd(1);


  TH1D *f1_mu = new TH1D("f1_mu","f1_mu",50,-0.5,0.5);
  TH1D *f1_sigma = new TH1D("f1_sigma","f1_sigma",50,0,3);
  TH1D *f1_chi2ndf = new TH1D("f1_chi2ndf","f1_chi2ndf",40,0,4);
  TH1D *f2_sigma = new TH1D("f2_sigma","f2_sigma",50,0,3);
  TH1D *f2_chi2ndf = new TH1D("f2_chi2ndf","f2_chi2ndf",40,0,4);

  // TF1  *f1 = new TF1("f1",fitfunction,-5,5,3);
  TF1  *f1 = new TF1("f1","gaus",-5,5);
  TF1  *f2 = new TF1("f2","gaus",-5,5);
  TF1  *f3 = new TF1("f3",Gaus_fc,-5,5,3);
  // f3->FixParameter(1,0.05);
  f3->SetParLimits(2,0.5,1.5);

  // f2->SetParameter(1, 0.05);
  f2->FixParameter(1,0.05);
  f2->SetParLimits(2,0.5,1.5);
  delete gRandom;
  // gRandom = new TRandom3(0);
  gRandom = new TRandom3(4869);
  // TH1D *h1 = new TH1D("h1","h1",20,-3,3);
  // for (Int_t j=0; j<100; j++) h1->Fill(gRandom->Gaus(0,1));
  // // https://root.cern/doc/master/TH1_8cxx_source.html#l03807
  // // https://root.cern/doc/master/classTH1.html#a63eb028df86bc86c8e20c989eb23fb2a
  // // h1->Fit("f1","WW");
  // h1->Fit("f3","BWW");
  // cout<<"f3NDF="<<f3->GetNDF()<<"\n";
  // h1->Fit("f1","W");
  // cout<<"f1NDF="<<f1->GetNDF()<<"\n";
  // f1_mu->Fill(f1->GetParameter(1));
  // f1_sigma->Fill(f1->GetParameter(2));
  // f1_chi->Fill(f1->GetChisquare()/17.0);
  // cout<<"f1NDF="<<f1->GetNDF()<<"\t";
  // h1->Fit("f2","B"); //"B" means with fixed parameters;"L" means using likelihood method to fit.
  // f2_sigma->Fill(f2->GetParameter(2));
  // f2_chi->Fill(f2->GetChisquare()/18.0);
  // cout<<"f2NDF="<<f2->GetNDF()<<"\n";

  for (Int_t i=0; i<1000; i++)
  {
    TH1D *h1 = new TH1D("h1","h1",20,-5,5);
    for (Int_t j=0; j<100; j++) h1->Fill(gRandom->Gaus(0,1));
    h1->Fit("f1");
    f1_mu->Fill(f1->GetParameter(1));
    f1_sigma->Fill(f1->GetParameter(2));
    // f1_chi2ndf->Fill(f1->GetChisquare()/17.0);
    f1_chi2ndf->Fill(f1->GetChisquare()/f1->GetNDF());
    // https://root.cern/doc/master/TH1_8cxx_source.html#l03807
    // https://root.cern/doc/master/classTH1.html#a63eb028df86bc86c8e20c989eb23fb2a
    h1->Fit("f2","B"); //"B" means with fixed parameters
    f2_sigma->Fill(f2->GetParameter(2));
    // f2_chi2ndf->Fill(f2->GetChisquare()/18.0);
    f2_chi2ndf->Fill(f2->GetChisquare()/f2->GetNDF());
  }

  gStyle->SetOptStat(1111);


  f1_mu->Draw();
  f1_mu->SetTitle("mu(free)");
  c1->cd(2);
  f1_sigma->Draw();
  f1_sigma->SetLineColor(kRed);
  f1_sigma->SetTitle("sigma");
  gPad->Update();
  TPaveStats *statsbox = (TPaveStats*)gPad->GetPrimitive("stats");
  // get (default) y position of stats box (histo h1)
  double y1 = statsbox->GetY1NDC(); // (lower) y start position of stats box
  double y2 = statsbox->GetY2NDC(); // (upper) y start position of stats box
  // set new position of stats box (histo h1)
  double newy1 = 2 * y1 - y2;   // new (lower) y start position of stats box
  double newy2 = y1;            // new (upper) y start position of stats box
  statsbox->SetY1NDC(newy1);    //set new y start position
  statsbox->SetY2NDC(newy2);    //set new y end position

  f2_sigma->Draw("sames");
  f2_sigma->SetLineColor(kGreen);
  // Draw options:
  // "same"  : draw histogram on same canvas, do not redraw stats box
  // "sames" : draw histogram on same canvas, draw stats box (in default position)

  TLegend *l1  = new TLegend(0.5,0.5,0.7,0.7);
  l1->AddEntry(f1_sigma,"#mu free","l");
  l1->AddEntry(f2_sigma,"#mu=0.05","l");
  l1->Draw();

  // TPaveStats *ps1 = (TPaveStats*)f1_sigma->GetListOfFunctions()->FindObject("stats");
  // ps1->SetX1NDC(0.4); ps1->SetX2NDC(0.6);
  c1->Modified();


  c1->cd(3);
  f1_chi2ndf->Draw();
  f1_chi2ndf->SetLineColor(kRed);
  f1_chi2ndf->SetTitle("chi2ndf");
  gPad->Update();
  statsbox = (TPaveStats*)gPad->GetPrimitive("stats");
  // get (default) y position of stats box (histo h1)
  y1 = statsbox->GetY1NDC(); // (lower) y start position of stats box
  statsbox->SetY1NDC(2*statsbox->GetY1NDC()-statsbox->GetY2NDC());    //set new y start position
  statsbox->SetY2NDC(y1);    //set new y end position

  f2_chi2ndf->Draw("sames");
  f2_chi2ndf->SetLineColor(kGreen);
  // c1->SetTitle("AAA");
  // gPad->SetTitle("BBB");

  TLegend *l2  = new TLegend(0.5,0.5,0.7,0.7);
  l2->AddEntry(f1_chi2ndf,"#mu free","l");
  l2->AddEntry(f2_chi2ndf,"#mu=0.05","l");
  l2->Draw();

  c1->Modified();




  c1->SaveAs("Hw7.png");
}
