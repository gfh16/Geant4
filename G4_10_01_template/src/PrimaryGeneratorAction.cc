#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction(EventAction* m_EvtAction_tem)
:m_EvtAction(m_EvtAction_tem)
{
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);
  particle = 0;
  
  //for the gun direction
  gun_direct = new Gun_Dir();
  Direction_Mode = configure->Get_ConfigValue_string("Direction_Mode");
  if(Direction_Mode=="FixedDir"){ Direction_Mode_Num = 0; }
  else if(Direction_Mode=="4pi_Iso"){ Direction_Mode_Num = 1; }
  else if(Direction_Mode=="Const_Dir"){ Direction_Mode_Num = 2; }
  else
  {
    cout<<"The work Mode that you Figure, is not defined in Gun_Dir"<<endl;
    getchar();
    Direction_Mode_Num = 0;
  }
  gun_direct->Set_WorkMode(Direction_Mode.c_str());
  if(Direction_Mode_Num!=1)
  { configure->Get_ConfigValue_doubleArray("FixedDir",0,2,FixedDir); }
  
  if(Direction_Mode_Num==0)
  { gun_direct->Init_FixedDir(FixedDir); }
  else if(Direction_Mode_Num==2)
  {
    configure->Get_ConfigValue_doubleArray("Const_Dir_Theta",0,1,Const_Dir_Theta_Range);
    configure->Get_ConfigValue_doubleArray("Const_Dir_Phi",0,1,Const_Dir_Phi_Range);
    for(int i=0;i<2;i++)
    {
      Const_Dir_Phi_Range[i] = Const_Dir_Phi_Range[i]*DegToRad();
      Const_Dir_Theta_Range[i] = Const_Dir_Theta_Range[i]*DegToRad();
    }
    gun_direct->Set_Const_Theta_Phi(Const_Dir_Theta_Range,Const_Dir_Phi_Range);
    gun_direct->Cal_Trans_Matrix(FixedDir);
  }
  
  //for the source position
  configure->Get_ConfigValue_doubleArray("Source_Pos",0,2,Source_Pos);
  
  //for the source energy
  Is_Certain_E = configure->Get_ConfigValue_int("Is_Certain_E");
  if(Is_Certain_E==1){ Particle_CertainEnergy = configure->Get_ConfigValue_double("Certain_Energy")*MeV; }
  else
  {
    string File_ESpec_Name = configure->Get_ConfigValue_string("Root_FileName"); 
    string Histo_ESpec_Name = configure->Get_ConfigValue_string("Histogram_Name");
    f1_Src_ESpec = new TFile(File_ESpec_Name.c_str());
    h1_Src_ESpec = (TH1D*) f1_Src_ESpec->Get(Histo_ESpec_Name.c_str());
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // default particle
  if(particle==0)
  {
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    particle = particleTable->FindParticle((configure->Get_ConfigValue_string("Particle")).c_str());
    particleGun->SetParticleDefinition(particle);
  }
  
  G4double PosX = 0; G4double PosY = 0; G4double PosZ = 0;
  Get_Pos(&PosX,&PosY,&PosZ);
  particleGun->SetParticlePosition(G4ThreeVector(PosX,PosY,PosZ));
  
  double Dir_XYZ_tem[3] = {0,0,1};
  gun_direct->Get_Gun_Dir(Dir_XYZ_tem);
  particleGun->SetParticleMomentumDirection(G4ThreeVector(Dir_XYZ_tem[0],Dir_XYZ_tem[1],Dir_XYZ_tem[2]));

  G4double ParticleEnergy = 0*MeV;
  Get_Energy(&ParticleEnergy);
  particleGun->SetParticleEnergy(ParticleEnergy);

  particleGun->GeneratePrimaryVertex(anEvent);

  m_EvtAction->SetPos_Src(PosX/mm,PosY/mm,PosZ/mm);
  m_EvtAction->SetEnergy_Src(ParticleEnergy/MeV);

}

void PrimaryGeneratorAction::Get_Energy(G4double* Energy_tem)
{
  if(Is_Certain_E==1){ *Energy_tem = Particle_CertainEnergy*MeV; }
  else{ *Energy_tem = h1_Src_ESpec->GetRandom()*MeV; }
}

void PrimaryGeneratorAction::Get_Pos(G4double* x_tem,G4double* y_tem,G4double* z_tem)
{
  *x_tem = Source_Pos[0]*mm; *y_tem = Source_Pos[1]*mm; *z_tem = Source_Pos[2]*mm;
}