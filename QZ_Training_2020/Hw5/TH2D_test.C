
{
  auto file = new TFile("TH2D_test.root", "RECREATE");
  auto histo = new TH2D("H2D_Gaus", "A 2D Histogram", 1024, 0., 1024., 1024, 0., 1024.);
  for(int i=0; i<10000; i++){
    histo->Fill(gRandom->Gaus(512., 128.), gRandom->Gaus(512., 64.));
  }
  file->WriteTObject(histo);
  file->Close(); file->Delete(); file=NULL; histo=NULL;

  std::cout << "TH2D_test.root Created." << std::endl;

 // Load the saved one
 file = new TFile("TH2D_test.root", "READ");
 histo=(TH2D*)file->GetObjectChecked("H2D_Gaus", "TH2D");
 histo->Draw();


 file->ls();
 auto c=new TCanvas("Canvas","Canvas",800,800);
 c->Divide(2,2);
 c->cd(1); H2D_Gaus->Draw("Cont1");
 c->cd(2); H2D_Gaus->Draw("Colz");
 c->cd(3); H2D_Gaus->Draw("Lego2");
 c->cd(4); H2D_Gaus->Draw("Surf3");
 c->Print("TH2D_test.png")

 new TBrowser();

 //return 0;
}
