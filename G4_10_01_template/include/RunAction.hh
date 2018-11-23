//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "TFile.h"
#include "TTree.h"
#include "iostream"
#include "TH1D.h"

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
   ~RunAction();

  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
    
  public:
    TFile* f1_data;
    TTree* t1_data;
    double Src_PosX; double Src_PosY; double Src_PosZ;
    double Energy_Origin;
    double Energy_Detect;
    int EvtID;
    TH1D* h1_Src_ESpec;
    
    void SetEnergy_Src(double E_tem) { Energy_Origin = E_tem; h1_Src_ESpec->Fill(E_tem);}
    void SetEnergy_Detect(double E_tem) { Energy_Detect = E_tem; }
    void SetPos_Src(double PosX_tem,double PosY_tem,double PosZ_tem)
    { Src_PosX = PosX_tem; Src_PosY = PosY_tem; Src_PosZ = PosZ_tem; }
    void SetEvtID(int ID_tem) { EvtID = ID_tem; }
    
    void FillData(){ t1_data->Fill(); }
    
  public:
    int FileNo;
    string FileName;
    void Open_NewFile();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
