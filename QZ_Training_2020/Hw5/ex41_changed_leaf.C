//to write a simple tree
//to run: root -l ex41.C
//by yangzw, 2008.03.20
//
//changed by qinzhi-2018311383, 2020
//to run: root -l ex41_changed.C

class Event{
public:
  Event(){};
  Event(Float_t ppx,Float_t ppy,Float_t ppz);
  Float_t  px;
  Float_t  py;
  Float_t  pz;
};
Event::Event(Float_t ppx,Float_t ppy,Float_t ppz){
  px = ppx;
  py = ppy;
  pz = ppz;
}


void ex41_changed_leaf() {
  TFile *f = new TFile("tree_leaf_test.root","recreate");
  TTree *t1 = new TTree("tree_leaf_test","test tree&leaf");
  gRandom->SetSeed(0);
  Event *event = new Event;
  Double_t random;
  Int_t i;
  //Set the Branches of tree
  // t1->Branch("Ev_Branch",&event,"px/F:py/F:pz/F");
  t1->Branch("Ev_Branch",&event);
  t1->Branch("random",&random,"random/D");
  t1->Branch("i",&i,"i/I");
  for (i=0;i<5000;i++) {
    Float_t px,py,pz;
    gRandom->Rannor(px,py);
    pz = px*px + py*py;
    event->px = px;
    event->py = py;
    event->pz = pz;
    random = gRandom->Rndm();
    t1->Fill();//Fill tree
  }
  t1->Write();
}



// root -l tree_test.root
// .ls
// tree_leaf_test->Show(0);
// tree_leaf_test->GetEntries();
// tree_leaf_test->Scan();
// tree_leaf_test->Print();
// tree_leaf_test->Draw("px");



// TFile f("tree_leaf_test.root");
// tree_leaf_test->StartViewer();
