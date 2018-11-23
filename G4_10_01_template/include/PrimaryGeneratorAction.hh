//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "TMath.h"
#include "TF1.h"
#include "TFile.h"
#include "TH1D.h"
#include "TRandom.h"
#include "iostream"
#include "EventAction.hh"
#include "G4ParticleDefinition.hh"
#include "Config.hh"
#include "Gun_Dir.hh"

class DetectorConstruction;
class G4ParticleGun;
class G4Event;

using namespace TMath;
using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction(EventAction* m_EvtAction_tem);    
 ~PrimaryGeneratorAction();

public:
  void GeneratePrimaries(G4Event*);
  void Get_Pos(G4double* x_tem,G4double* y_tem,G4double* z_tem);
  void Get_Energy(G4double* Energy_tem);
  
public:
  Gun_Dir* gun_direct;
  G4ParticleGun* particleGun;
  G4ParticleDefinition* particle;
  EventAction* m_EvtAction;

public:
  Config* configure;
  double Source_Pos[3]; //unit: mm
  
  int Is_Certain_E;
  G4double Particle_CertainEnergy;
  TFile* f1_Src_ESpec;
  TH1D* h1_Src_ESpec;
  
  //the direction of source
  string Direction_Mode;
  int Direction_Mode_Num; //0: FixedDir  1: 4pi_Iso  2: Const_Dir
  double FixedDir[3]; //except the 4pi_Iso, this vector is used for FixedDir and Const_Dir;
  double Const_Dir_Theta_Range[2];
  double Const_Dir_Phi_Range[2];
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


