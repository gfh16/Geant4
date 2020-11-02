#define MakeClass_t3_cxx
#include "MakeClass_t3.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <cmath>


bool operator< (MakeClass_t3::trackdata_t& l, MakeClass_t3::trackdata_t& r)
{
   return l.px < r.px;
}

void MakeClass_t3::Loop()
{
//   In a ROOT session, you can do:
//      root> .L MakeClass_t3.C
//      root> MakeClass_t3 t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   TCanvas *c1 = new TCanvas("c1","c1",0,0,1020,550);
   c1->SetCanvasSize(1000,500);
   c1->SetFixedAspectRatio(kTRUE);
   c1->Divide(2,1);
   TH1D *h1 = new TH1D("h1","p_tot",20,0,8);
   TH1D *h2 = new TH1D("h2","p_tot(ntrack<20)",20,0,8);

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      Float_t px_tot=0,py_tot=0;
      for(Int_t i=0; i<ntrack; i++)
      {
        trackdata_t data;
        data.entry = jentry;
        data.trackid = i;
        data.px = px[i];
        data.py = py[i];

        vec_track.push_back(data);
        px_tot = px_tot+px[i];
        py_tot = py_tot+py[i];

        h1->Fill(std::sqrt(px[i]*px[i]+py[i]*py[i]));
        if(ntrack<20){
          h2->Fill(std::sqrt(px[i]*px[i]+py[i]*py[i]));
        }
      }
      // h1->Fill(std::sqrt(px_tot*px_tot+py_tot*py_tot));
      // if(ntrack<20){
      //   h2->Fill(std::sqrt(px_tot*px_tot+py_tot*py_tot));
      // }
      px_tot=0;
      py_tot=0;
   }
   c1->cd(1);
   h1->Draw();
   c1->cd(2);
   h2->Draw();
   c1->SaveAs("ex42_p_tot-2.png");
   // c1->Print("ex42_p_tot.png");


   std::cout<<"before sort(first 20 of vector_track):"<<std::endl;
   for(std::vector<trackdata_t>::iterator it = vec_track.begin(); it!=vec_track.end()&&it!=vec_track.begin()+20;++it){
     std::cout<<"entry:"<<(*it).entry<<"\t"<<"trackid:"<<(*it).trackid<<"\t"<<"px:"<<(*it).px<<"\t"<<"py:"<<(*it).py<<"\n";
   }
   std::cout<<"\n"<<std::endl;
   std::sort(vec_track.begin(), vec_track.end());
   std::cout<<"after sort by px(first 20 of vector_track):"<<std::endl;
   for(std::vector<trackdata_t>::iterator it = vec_track.begin(); it!=vec_track.end()&&it!=vec_track.begin()+20;++it){
     std::cout<<"entry:"<<(*it).entry<<"\t"<<"trackid:"<<(*it).trackid<<"\t"<<"px:"<<(*it).px<<"\t"<<"py:"<<(*it).py<<"\n";
   }
   std::cout<<"\n"<<std::endl;
}
