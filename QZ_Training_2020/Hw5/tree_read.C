void tree_read(){
  TFile *f = new TFile("tree_test.root");
  TTree *tree_test = (TTree*)f->Get("tree_test");
  Float_t px, py, pz;
  tree_test->SetBranchAddress("px",&px);
  tree_test->SetBranchAddress("py",&py);
  tree_test->SetBranchAddress("pz",&pz);

  TH1F *hpx = new TH1F("hpx","px distribution",100,-3,3);
  TH2F *hpxpy = new TH2F("hpxpy","py vs px",30,-3,3,30,-3,3);

  Int_t nentries = (Int_t)tree_test->GetEntries();
  cout<<"nentries: "<<nentries<<endl;

  for (Int_t i=0;i<nentries;i++) {
    tree_test->GetEntry(i);
    hpx->Fill(px);
    hpxpy->Fill(px,py);
  }
  hpx->Draw();
  hpxpy->Draw("ColZ");
}
