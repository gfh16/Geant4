#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4PhysListFactory.hh"

#include "Randomize.hh"

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#include "Config.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  Config* configure = Config::Get_Config_Man();
  
  G4UIExecutive* ui = 0;
  if ( argc == 1 ){ ui = new G4UIExecutive(argc, argv); }

  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  // Construct the default run manager
  //
#ifdef G4MULTITHREADED  
  G4MTRunManager* runManager = new G4MTRunManager;
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  // Set mandatory initialization classes
  //
  runManager->SetUserInitialization(new DetectorConstruction());
  
  if(configure->Get_ConfigValue_string("PhysicsList")=="FTFP_BERT")
  {
    G4VModularPhysicsList* physicsList = new FTFP_BERT;
    physicsList->RegisterPhysics(new G4StepLimiterPhysics());
    runManager->SetUserInitialization(physicsList);
  }
  else if( configure->Get_ConfigValue_string("PhysicsList")=="Shielding" )
  {
    G4VUserPhysicsList* physics = 0;
    G4int verbose = 1;
    G4PhysListFactory factory;
    physics = factory.GetReferencePhysList("Shielding");
    physics->SetVerboseLevel(verbose);
    runManager->SetUserInitialization(physics);
  }
  
  // Set user action classes
  runManager->SetUserInitialization(new ActionInitialization());
  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    if(configure->Get_ConfigValue_int("Is_Geo_Tracking")==0)
    {
      UImanager->ApplyCommand("/control/execute ./macro/init_vis.mac");
    }
    else
    {
      UImanager->ApplyCommand("/control/execute ./macro/init_vis.mac");
      UImanager->ApplyCommand("/control/execute ./macro/vis.mac");
      if (ui->IsGUI()) {
        UImanager->ApplyCommand("/control/execute ./macro/gui.mac");
      }
    }
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !
  //
  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
