//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "RunAction.hh"
#include "G4Run.hh"
#include "Config.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{
  f1_data = 0;
  t1_data = 0;
  FileNo = 0;
  h1_Src_ESpec = new TH1D("h1_Src_ESpec","h1_Src_ESpec",10000,0,1000);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
  if(t1_data!=0) { t1_data->Delete(); t1_data=0; }
  if(f1_data!=0) { f1_data->Delete(); f1_data=0; }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  FileNo = 0;
  FileName = (Config::Get_Config_Man())->Get_ConfigValue_string("Output_FileName");
  Open_NewFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " end." << G4endl;
  if(t1_data!=0) { t1_data->Write(); }
  if(t1_data!=0) { t1_data->Delete(); t1_data=0; }
  if(f1_data!=0) 
  { 
    cout<<f1_data->GetName()<<" Closed!"<<endl;
    h1_Src_ESpec->Write("",TObject::kOverwrite);
    f1_data->Close(); f1_data->Delete(); f1_data=0; 
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::Open_NewFile()
{
  if(t1_data!=0) { t1_data->Write(); }
  if(t1_data!=0) { t1_data->Delete(); t1_data=0; }
  if(f1_data!=0) 
  { 
    cout<<f1_data->GetName()<<" Closed!"<<endl;
    h1_Src_ESpec->Write("",TObject::kOverwrite);
    f1_data->Close(); f1_data->Delete(); f1_data=0; 
  }  

  char FileName_tem[300];
  sprintf(FileName_tem,"%s%d.root",FileName.c_str(),FileNo);
  
  cout<<"File: "<<FileName_tem<<" Opened !"<<endl;
  
  f1_data = new TFile(FileName_tem,"recreate");
  t1_data = new TTree("t1","Gamma Detection");
  h1_Src_ESpec->Reset();
  
  t1_data->Branch("Src_PosX",&Src_PosX,"Src_PosX/D");
  t1_data->Branch("Src_PosY",&Src_PosY,"Src_PosY/D");
  t1_data->Branch("Src_PosZ",&Src_PosZ,"Src_PosZ/D");
  t1_data->Branch("Energy_Origin",&Energy_Origin,"Energy_Origin/D");
  t1_data->Branch("Energy_Detect",&Energy_Detect,"Energy_Detect/D");
  t1_data->Branch("EvtID",&EvtID,"EvtID/I");
  
  FileNo++;
}
