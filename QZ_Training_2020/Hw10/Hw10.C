/// \author 06/2020 - Qin Zhi


#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooAddPdf.h"
#include "RooMinimizer.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
using namespace RooFit ;


void Hw10()
{
  delete gRandom;
  // gRandom = new TRandom3(0);
  gRandom = new TRandom3(4869);


  // C r e a t e   m o d e l   a n d   d a t a s e t
  // -----------------------------------------------

  // Observable
  RooRealVar x("x","x",-20,20) ;

  // Model (intentional strong correlations)
  RooRealVar mean_toy("mean","mean of toy",0);
  RooRealVar sigma_toy("sigma","width of toy",1);
  RooGaussian g_toy("g","pdf of toy",x,mean_toy,sigma_toy);



  RooRealVar mean("mean","mean of fit",0,-10,10);
  RooRealVar sigma("sigma","width of fit",1,0.01,3);
  RooGaussian g0("g1","pdf of fit1",x,mean,sigma);
  RooGaussian g1("g2","pdf of fit2",x,RooConst(0),sigma);
  RooGaussian g2("g2","pdf of fit2",x,RooConst(0.05),sigma);
  RooGaussian g3("g3","pdf of fit3",x,RooConst(0.2),sigma);
  RooGaussian g4("g4","pdf of fit4",x,RooConst(0.5),sigma);



  TH1D *g0_mu = new TH1D("g0_mu","g0_mu(mu free)",100,-0.5,0.5);
  TH1D *g0_sigma = new TH1D("g0_sigma","g0_sigma(mu free)",100,0.5,1.5);
  TH1D *g0_minNll = new TH1D("g0_minNll","g0_minNll(mu free)",50,125,170);

  TH1D *g1_sigma = new TH1D("g1_sigma","g1_sigma(mu = 0)",100,0.5,1.5);
  TH1D *g1_minNll = new TH1D("g1_minNll","g1_minNll(mu = 0)",50,125,170);
  TH1D *g1_q_mu = new TH1D("g1_q_mu","g1_q_mu(mu = 0)",100,0,25);

  TH1D *g2_sigma = new TH1D("g2_sigma","g2_sigma(mu = 0.05)",100,0.5,1.5);
  TH1D *g2_minNll = new TH1D("g2_minNll","g2_minNll(mu = 0.05)",50,125,170);
  TH1D *g2_q_mu = new TH1D("g2_q_mu","g2_q_mu(mu = 0.05)",100,0,25);

  TH1D *g3_sigma = new TH1D("g3_sigma","g3_sigma(mu = 0.2)",100,0.5,1.5);
  TH1D *g3_minNll = new TH1D("g3_minNll","g3_minNll(mu = 0.2)",50,125,170);
  TH1D *g3_q_mu = new TH1D("g3_q_mu","g3_q_mu(mu = 0.2)",100,0,25);

  TH1D *g4_sigma = new TH1D("g4_sigma","g4_sigma(mu = 0.5)",100,0.5,1.5);
  TH1D *g4_minNll = new TH1D("g4_minNll","g4_minNll(mu = 0.5)",50,125,170);
  TH1D *g4_q_mu = new TH1D("g4_q_mu","g4_q_mu(mu = 0.5)",100,0,25);

  for(Int_t i=0; i<1000; i++){
    // Generate 100 events
    RooDataSet* data = g_toy.generate(x,100);

    RooFitResult* r0 = g0.fitTo(*data,Save());
    g0_mu->Fill(mean.getValV());
    g0_sigma->Fill(sigma.getValV());
    g0_minNll->Fill(r0->minNll());


    RooFitResult* r1 = g1.fitTo(*data,Save());
    g1_sigma->Fill(sigma.getValV());
    g1_minNll->Fill(r1->minNll());
    g1_q_mu->Fill(2*(r1->minNll()-r0->minNll()));

    RooFitResult* r2 = g2.fitTo(*data,Save());
    g2_sigma->Fill(sigma.getValV());
    cout<<"sigma.getValV()="<<sigma.getValV()<<endl;
    g2_minNll->Fill(r2->minNll());
    cout<<"g2_minNll="<<r2->minNll()<<endl;
    g2_q_mu->Fill(2*(r2->minNll()-r0->minNll()));

    RooFitResult* r3 = g3.fitTo(*data,Save());
    g3_sigma->Fill(sigma.getValV());
    g3_minNll->Fill(r3->minNll());
    g3_q_mu->Fill(2*(r3->minNll()-r0->minNll()));

    RooFitResult* r4 = g4.fitTo(*data,Save());
    g4_sigma->Fill(sigma.getValV());
    g4_minNll->Fill(r4->minNll());
    g4_q_mu->Fill(2*(r4->minNll()-r0->minNll()));

  }






  // Make canvas and draw RooPlots
  // //////<<Hw10-pll.png
  // TCanvas *c = new TCanvas("Hw10","Hw10-pll",800, 800);
  // c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame->GetYaxis()->SetTitleOffset(1.4) ; frame->Draw() ;
  // c->SaveAs("Hw10-pll.png");
  // //////Hw10-pll.png>>


  // Make canvas and draw RooPlots
  TCanvas *c = new TCanvas("Hw10","Hw10",1020, 1050);
  c->Divide(2,2);
  c->cd(1); gPad->SetLeftMargin(0.15);
    g0_mu->Draw();

  c->cd(2); gPad->SetLeftMargin(0.15);
    g0_sigma->Draw();
    g0_sigma->SetTitle("#sigma");
    g0_sigma->SetLineColor(kRed);
    g1_sigma->Draw("SAMES");
    g1_sigma->SetLineColor(kGreen);
    g2_sigma->Draw("SAMES");
    g2_sigma->SetLineColor(kYellow);
    g3_sigma->Draw("SAMES");
    g3_sigma->SetLineColor(kBlack);
    g4_sigma->Draw("SAMES");
    g3_sigma->SetLineColor(kBlue);

    TLegend *l2  = new TLegend(0.5,0.5,0.7,0.7);
    l2->AddEntry(g0_sigma,"#mu free","l");
    l2->AddEntry(g1_sigma,"#mu=0","l");
    l2->AddEntry(g2_sigma,"#mu=0.05","l");
    l2->AddEntry(g3_sigma,"#mu=0.2","l");
    l2->AddEntry(g4_sigma,"#mu=0.5","l");
    l2->Draw();
    c->Modified();


  c->cd(3); gPad->SetLeftMargin(0.15);
    g0_minNll->Draw();
    g0_minNll->SetTitle("minNll");
    g0_minNll->SetLineColor(kRed);
    g1_minNll->Draw("SAMES");
    g1_minNll->SetLineColor(kGreen);
    g2_minNll->Draw("SAMES");
    g2_minNll->SetLineColor(kYellow);
    g3_minNll->Draw("SAMES");
    g3_minNll->SetLineColor(kBlack);
    g4_minNll->Draw("SAMES");
    g4_minNll->SetLineColor(kBlue);

    TLegend *l3  = new TLegend(0.5,0.5,0.7,0.7);
    l3->AddEntry(g0_minNll,"#mu free","l");
    l3->AddEntry(g1_minNll,"#mu=0","l");
    l3->AddEntry(g2_minNll,"#mu=0.05","l");
    l3->AddEntry(g3_minNll,"#mu=0.2","l");
    l3->AddEntry(g4_minNll,"#mu=0.5","l");
    l3->Draw();
    c->Modified();


  c->cd(4); gPad->SetLeftMargin(0.15);
    g1_q_mu->Draw();
    g1_q_mu->SetTitle("q_{#mu}");
    g1_q_mu->SetLineColor(kGreen);
    g2_q_mu->Draw("SAMES");
    g2_q_mu->SetLineColor(kYellow);
    g3_q_mu->Draw("SAMES");
    g3_q_mu->SetLineColor(kBlack);
    g4_q_mu->Draw("SAMES");
    g4_q_mu->SetLineColor(kBlue);

    TLegend *l4  = new TLegend(0.5,0.5,0.7,0.7);
    l4->AddEntry(g1_q_mu,"#mu=0","l");
    l4->AddEntry(g2_q_mu,"#mu=0.05","l");
    l4->AddEntry(g3_q_mu,"#mu=0.2","l");
    l4->AddEntry(g4_q_mu,"#mu=0.5","l");
    l4->Draw();
    c->Modified();


  c->SaveAs("Hw10.png");

}
