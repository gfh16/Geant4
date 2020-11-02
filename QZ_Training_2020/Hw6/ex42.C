#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"
#include "TCanvas.h"

TString rootfile("ex42.root");

void ex42w() {
// Example of a Tree where branches are variable length arrays
// Run this script with
//   .x ex42.C
// or,
//   .L ex42.C
//   ex42w()
//   ex42r()
//   ex42r2()
//   by yangzw, 2008.03.22

   const Int_t kMaxTrack = 50;
   Int_t ntrack;
   Float_t px[kMaxTrack];
   Float_t py[kMaxTrack];
   Float_t zv[kMaxTrack];
   Double_t pv[3];

   TFile f(rootfile,"recreate");
   TTree *t3 = new TTree("t3","Reconst events");
   t3->Branch("ntrack",&ntrack,"ntrack/I");
   t3->Branch("px",px,"px[ntrack]/F");
   t3->Branch("py",py,"py[ntrack]/F");
   t3->Branch("zv",zv,"zv[ntrack]/F");
   t3->Branch("pv",pv,"pv[3]/D");

   gRandom->SetSeed(0);
   for (Int_t i=0;i<1000;i++) {
      Int_t nt = gRandom->Rndm()*(kMaxTrack-1);
      ntrack = nt;
      for (Int_t n=0;n<nt;n++) {
         px[n]   = gRandom->Gaus(0,1);
         py[n]   = gRandom->Gaus(0,2);
         zv[n]   = gRandom->Gaus(100,2);
      }
	for (Int_t j=0;j<3;j++) pv[j] = gRandom->Gaus(0,1+j);
      t3->Fill();
   }
   f.cd();
   t3->Write();
}

void ex42r()
{
   TFile *f = new TFile(rootfile);
   TTree *t3 = (TTree*)f->Get("t3");
   // TH1F *htemp = new TH1F("hpx","",100,-5,5);
   // t3->Draw("sqrt(px*px+py*py)>>htemp");
   // htemp->SetLineColor(2);
   // TH1F *htemp = new TH1F();
   t3->Draw("sqrt(px*px+py*py)");
   htemp->SetLineColor(2);
   t3->Draw("sqrt(px*px+py*py)","zv>100","sames");
}

void ex42r2()
{
   TFile *f = new TFile(rootfile);
   TTree *t3 = (TTree*)f->Get("t3");
   const Int_t kMaxTrack = 100;
   Int_t ntrack;
   Float_t px[kMaxTrack];	//[ntrack]
   Float_t py[kMaxTrack];	//[ntrack]
   Float_t zv[kMaxTrack];	//[ntrack]
   Double_t pv[3];

   //TBranch *b_pv;	//!


   t3->SetBranchAddress("ntrack", &ntrack);
   t3->SetBranchAddress("px", px);
   t3->SetBranchAddress("py", py);
   t3->SetBranchAddress("zv", zv);
   t3->SetBranchAddress("pv", pv);

   Int_t nentries = t3->GetEntries();
   cout << "nentries = " << nentries << endl;
   TH1I *hntrack = new TH1I("hntrack","num of track",25,0,50);
   TH1F *hpt     = new TH1F("hpt"    ,"pt of track" ,100,0,10);
   for (int i=0;i<nentries;i++) {
	t3->GetEntry(i);
	hntrack->Fill( ntrack );
	for (int j=0;j<ntrack;j++) {
	   Float_t pt = sqrt(px[j]*px[j]+py[j]*py[j]);
	   hpt->Fill( pt );
	}
   }
   TCanvas *myC = new TCanvas("myC","",10,10,600,400);
   hntrack->Draw("e");
   hntrack->GetYaxis()->SetRangeUser(0,60);
   TCanvas *myC1 = new TCanvas("myC1","",10,10,600,400);
   hpt->Draw();
}

void ex42()
{
   ex42w();
   // ex42r();
   // ex42r2();
}
