#include "TGraph.h"
#include "TH1.h"
#include "TMath.h"
#include "TCanvas.h"



void Hw8()
{
  delete gRandom;
  // gRandom = new TRandom3(0); //seed=0 (time)
  gRandom = new TRandom3(4869); //seed=4869

  auto c1 = new TCanvas("c1","c1",0,0,1020,550);
  c1->SetCanvasSize(1000, 500);
  c1->SetFixedAspectRatio(kTRUE);
  c1->Divide(2,1);
  TGraph *Graph_R = new TGraph();
  TH1D *Len_Distribution =new TH1D("Len_Distribution_hist","length Distribution",100,0,2.5);

  c1->cd(1);

  // Graph_R->Set(0);
  Graph_R->SetPoint(0,0,0);
  Graph_R->SetLineColor(1);
  //Graph_R->SetLineWidth(4);
  Graph_R->SetMarkerColor(2);
  Graph_R->SetMarkerStyle(20);
  Graph_R->SetMarkerSize(0.5);
  Graph_R->SetTitle("MC");
  Graph_R->GetXaxis()->SetTitle("X");
  Graph_R->GetYaxis()->SetTitle("Y");
  Graph_R->GetYaxis()->SetTitleOffset(1);
  Int_t Ndiv = 510;
  Graph_R->GetXaxis()->SetNdivisions(Ndiv,kFALSE);
  Graph_R->GetYaxis()->SetNdivisions(Ndiv,kFALSE);
  Graph_R->GetXaxis()->SetLimits(0,2);
  Graph_R->SetMinimum(-1);
  Graph_R->SetMaximum(1);
  Graph_R->Draw("ACP");
  // Graph_R->Draw("AL");



  for(Int_t i=0;i<100;i++){
    Bool_t alive = true;
    Int_t n = 0;
    Int_t n_max = 1000;
    Double_t x=0,y=0,theta=0,l_tot=0;

    TGraph *Graph_i = new TGraph();
    Graph_i->Set(0);
    Graph_i->SetLineColor(1);
    //Graph_i->SetLineWidth(4);

    Graph_i->SetMarkerColor(2);
    Graph_i->SetMarkerStyle(20);
    Graph_i->SetMarkerSize(0.5);

    Graph_i->SetPoint(0,x,y);n=1;

    while(alive&&n<n_max){
      Double_t l1,l2,l3;
      l1=-0.1*TMath::Log(gRandom->Rndm());
      l2=-5.0*TMath::Log(gRandom->Rndm());
      l3=-0.3*TMath::Log(gRandom->Rndm());
      if(l1<=l2&&l1<=l3){
        x = x+l1*TMath::Cos(theta);
        y = y+l1*TMath::Sin(theta);
        Graph_i->SetPoint(n,x,y);
        cout<<"i="<<i<<"\t"<<"n="<<n<<endl;
        cout<<"x="<<x<<"\t"<<"y="<<y<<endl;
        cout<<"theta="<<theta<<"\t";
        l_tot = l_tot+l1;
        theta = theta + gRandom->Uniform(-TMath::TwoPi()/12,TMath::TwoPi()/12);
        cout<<"theta="<<theta<<endl;
      }
      if(l2<l1&&l2<=l3){
        x = x+l2*TMath::Cos(theta);
        y = y+l2*TMath::Sin(theta);
        Graph_i->SetPoint(n,x,y);

        l_tot = l_tot+l2;
        alive = false;
      }
      if(l3<l1&&l3<=l2){
        x = x+l3*TMath::Cos(theta);
        y = y+l3*TMath::Sin(theta);
        Graph_i->SetPoint(n,x,y);

        l_tot = l_tot+l3;
        alive = false;
      }
      n++;
    }
    Graph_i->Draw("CL");
    Len_Distribution->Fill(l_tot);
  }

  c1->cd(2);
  Len_Distribution->Draw();

  c1->Print("Hw8_simulation.png");

}
