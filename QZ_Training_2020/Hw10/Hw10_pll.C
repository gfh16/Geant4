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


void Hw10_pll()
{
  delete gRandom;
  // gRandom = new TRandom3(0);
  gRandom = new TRandom3(4869);


  // C r e a t e   m o d e l   a n d   d a t a s e t
  // -----------------------------------------------

  // Observable
  RooRealVar x("x","x",-20,20) ;

  // Model (intentional strong correlations)
  RooRealVar mean0("mean","mean of test",0);
  RooRealVar sigma0("sigma","width of test",1);
  RooGaussian g0("g0","pdf of test",x,mean0,sigma0);



  RooRealVar mean("mean","mean of fit",0,-10,10);
  RooRealVar sigma("sigma","width of fit",1,0.01,3);
  RooGaussian g1("g1","pdf of fit1",x,mean,sigma);
  RooGaussian g2("g2","pdf of fit2",x,RooConst(0.05),sigma);
  RooGaussian g3("g3","pdf of fit3",x,RooConst(0.2),sigma);
  RooGaussian g4("g4","pdf of fit4",x,RooConst(0.5),sigma);




  // Generate 100 events
  RooDataSet* data = g0.generate(x,100);

  RooFitResult* r = g1.fitTo(*data,Save());
  cout << "-log(L) at minimum = " << r->minNll() << endl;
  mean.Print();
  cout << "mean = " << mean.getValV()<< endl;


  // C o n s t r u c t   p l a i n   l i k e l i h o o d
  // ---------------------------------------------------

  // Construct unbinned likelihood
  RooAbsReal* nll = g1.createNLL(*data,NumCPU(4));

  // Minimize likelihood w.r.t all parameters before making plots
  RooMinuit m(*nll);
  m.migrad();
  RooFitResult* r_nll = m.save();
  cout << "-log(L) at minimum = " << r_nll->minNll() << endl;
  mean.Print();


  // Plot likelihood scan mean
  RooPlot* frame = mean.frame(Bins(10),Range(-0.2,0.3),Title("LL and profileLL in mean"));
  nll->plotOn(frame,ShiftToZero());



  // C o n s t r u c t   p r o f i l e   l i k e l i h o o d   i n   f r a c
  // -----------------------------------------------------------------------

  // The profile likelihood estimator on nll for mean will minimize nll w.r.t
  // all floating parameters except mean for each evaluation

  RooAbsReal* pll = nll->createProfile(mean);

  // Plot the profile likelihood in mean
  pll->plotOn(frame,LineColor(kRed));

  // Adjust frame maximum for visual clarity
  frame->SetMinimum(0);
  frame->SetMaximum(3);






  // Make canvas and draw RooPlots
  //////<<Hw10-pll.png
  TCanvas *c = new TCanvas("Hw10","Hw10-pll",800, 800);
  c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame->GetYaxis()->SetTitleOffset(1.4) ; frame->Draw() ;
  c->SaveAs("Hw10-pll.png");
  //////Hw10-pll.png>>


  // // Make canvas and draw RooPlots
  // TCanvas *c = new TCanvas("Hw10","Hw10-pll",800, 800);
  // c->Divide(2);
  // c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame->GetYaxis()->SetTitleOffset(1.4) ; frame->Draw() ;
  // // c->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
  // c->SaveAs("Hw10.png");

  delete pll;
  delete nll;
}
