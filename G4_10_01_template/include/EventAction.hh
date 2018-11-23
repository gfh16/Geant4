//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "RunAction.hh"
#include "iostream"

class G4Event;
class G4DigiManager;

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EventAction : public G4UserEventAction
{
public:
  EventAction(RunAction* m_Run_tem);
  ~EventAction();

public:
  G4DigiManager* m_DM;
  RunAction* m_Run;
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
    
  void SetEnergy_Src(double E_tem) { m_Run->SetEnergy_Src(E_tem); }
  void SetPos_Src(double PosX_tem,double PosY_tem,double PosZ_tem)
  { m_Run->SetPos_Src(PosX_tem,PosY_tem,PosZ_tem); }
  void SetEnergy_Detect(double E_tem) { m_Run->SetEnergy_Detect(E_tem); }
  void SetEvtID(int ID_tem) { m_Run->SetEvtID(ID_tem); }
    
  int EvtNum_singleFile;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif