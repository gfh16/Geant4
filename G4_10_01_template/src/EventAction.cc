//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#include "EventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4DigiManager.hh"
#include "TrackerHit.hh"
#include "Config.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
EventAction::EventAction(RunAction* m_Run_tem)
{
  m_Run = m_Run_tem;
  m_DM = G4DigiManager::GetDMpointer();
  EvtNum_singleFile = (Config::Get_Config_Man())->Get_ConfigValue_int("EvtNum_OutPut_Unit");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void EventAction::BeginOfEventAction(const G4Event*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void EventAction::EndOfEventAction(const G4Event* evt)
{
  G4int event_id = evt->GetEventID();
  if(event_id%100000==0) { cout<<"EvtID: "<<event_id<<endl; }
  if( EvtNum_singleFile>0 && (event_id>=EvtNum_singleFile &&  event_id%EvtNum_singleFile==0)) { m_Run->Open_NewFile(); }
  
  G4int HCI = -1;
  HCI = m_DM->GetHitsCollectionID("NaI_HitsCollection");

  if(HCI>=0)
  {
    TrackerHitsCollection* HC = 0;
    HC = (TrackerHitsCollection*) (m_DM->GetHitsCollection(HCI));
    G4int n_hit = HC->entries();
    if(n_hit>0)
    {
      double Edep_total = 0;
      for(G4int i=0;i<n_hit;i++)
      {
        Edep_total += ((*HC)[i]->GetEdep());
      }
      SetEnergy_Detect(Edep_total);
      SetEvtID(event_id);
      m_Run->FillData();
    }  
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
