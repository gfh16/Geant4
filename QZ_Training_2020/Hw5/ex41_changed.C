//to write a simple tree
//to run: root -l ex41.C
//by yangzw, 2008.03.20
//
//changed by qinzhi-2018311383, 2020
//to run: root -l ex41_changed.C

void ex41_changed() {
  TFile *f = new TFile("tree_test.root","recreate");
  TTree *t1 = new TTree("tree_test","test tree");
  gRandom->SetSeed(0);
  Float_t px,py,pz;
  Double_t random;
  Int_t i;
  //Set the Branches of tree
  t1->Branch("px",&px,"px/F");
  t1->Branch("py",&py,"py/F");
  t1->Branch("pz",&pz,"pz/F");
  t1->Branch("random",&random,"random/D");
  t1->Branch("i",&i,"i/I");
  for (i=0;i<5000;i++) {
    gRandom->Rannor(px,py);
    pz = px*px + py*py;
    random = gRandom->Rndm();
    t1->Fill();//Fill tree
  }
  t1->Write();
}



// root -l tree_test.root
// .ls
// tree_test->Show(0);
// tree_test->GetEntries();
// tree_test->Scan();
// tree_test->Print();
// tree_test->Draw("px");
// TH1F *h1;
// tree_test->Draw("px>>h1");
// tree_test->Draw("px+py","px>0","same");
// TH2D h2("h2","h2",10,0,10,10,0,10);
// tree_test->Project("h2","px:py","pz>0");
// h2.Draw("Colz");
// TH2D *h3 = new TH2D("h3","h3",10,-5,5,10,-5,5);
// tree_test->Project("h3","px:py","pz>0");
// h3->Draw();
// h3->Draw("Colz");


// TFile f("tree_test.root");
// tree_test->StartViewer();
