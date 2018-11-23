#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "TrackerSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
G4ThreadLocal 
G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = 0;

DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction(),fStepLimit(NULL),fCheckOverlaps(true)
{
  fMessenger = new DetectorMessenger(this);
  configure = Config::Get_Config_Man();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
DetectorConstruction::~DetectorConstruction()
{
  delete fStepLimit;
  delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
//--------- Material definition --------- 
  G4NistManager* nistManager = G4NistManager::Instance();
  nistManager->SetVerbose(1);
  
  Air = nistManager->FindOrBuildMaterial("G4_AIR");
  Pb  = nistManager->FindOrBuildMaterial("G4_Pb");
  Xenon = nistManager->FindOrBuildMaterial("G4_Xe");
  Water_Natural = nistManager->FindOrBuildMaterial("G4_WATER");
  
  CaCO3 = nistManager->FindOrBuildMaterial("G4_CALCIUM_CARBONATE");
  Fe = nistManager->FindOrBuildMaterial("G4_Fe");
  Silicon = nistManager->FindOrBuildMaterial("G4_Si");
  Rubber_Natural = nistManager->FindOrBuildMaterial("G4_RUBBER_NATURAL");
  NaI = nistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  CsI = nistManager->FindOrBuildMaterial("G4_CESIUM_IODIDE");
  Vacuum = nistManager->FindOrBuildMaterial("G4_Galactic");
  IsoButane = nistManager->FindOrBuildMaterial("G4_BUTANE");
  Mylar = nistManager->FindOrBuildMaterial("G4_MYLAR");
  Paraffin = nistManager->FindOrBuildMaterial("G4_PARAFFIN");
  Teflon = nistManager->FindOrBuildMaterial("G4_TEFLON");
  
  G4int protons = 2; G4int neutrons = 1; G4int nucleons = protons+neutrons;
  G4int isotopes = 1; G4int elements = 1;
  G4double atomicMass = 3.016*g/mole;
  G4Isotope* he3 = new G4Isotope("He3", protons, nucleons, atomicMass);
  G4Element* He3 = new G4Element("Helium3", "He3", isotopes=1);
  He3->AddIsotope(he3, 100*perCent);
  G4double pressure = 4*bar; //4 Atmospheric pressure, 100% He3
  
  G4double temperature = 293.15*kelvin;
  G4double density = 0.5358*mg/cm3; //this is the most important parameter
  _3He = new G4Material("Helium3", density, elements=1, kStateGas, temperature, pressure);
  _3He->AddElement(He3, 100*perCent); 
  
  // Print all the materials defined.
  G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  G4double worldLength = (configure->Get_ConfigValue_double("worldLength"))*mm;
  // Definitions of Solids, Logical Volumes, Physical Volumes

  // World
  G4GeometryManager::GetInstance()->SetWorldMaximumExtent(worldLength);
  G4cout << "Computed tolerance = "
         << G4GeometryTolerance::GetInstance()->GetSurfaceTolerance()/mm
         << " mm" << G4endl;
  
  G4Box* worldS = new G4Box("worldS",worldLength/2,worldLength/2,worldLength/2);
  G4LogicalVolume* worldLV = new G4LogicalVolume(worldS,Air,"worldLV"); 
  G4VPhysicalVolume* worldPV = new G4PVPlacement(
                 0,               // no rotation
                 G4ThreeVector(), // at (0,0,0)
                 worldLV,         // its logical volume
                 "WorldPV",         // its name
                 0,               // its mother  volume
                 false,           // no boolean operations
                 0,               // copy number
                 fCheckOverlaps); // checking overlaps 

  // NaI-Det
  double Pos_NaI_Det[3];
  configure->Get_ConfigValue_doubleArray("Pos_NaI_Det",0,2,Pos_NaI_Det);
  G4ThreeVector position_NaI_Det = G4ThreeVector(Pos_NaI_Det[0]*mm,Pos_NaI_Det[1]*mm,Pos_NaI_Det[2]*mm);
  G4double Rmax_NaI_Det = configure->Get_ConfigValue_double("Rmax_NaI_Det")*mm;
  G4double Length_NaI_Det = configure->Get_ConfigValue_double("Length_NaI_Det")*mm;
  G4Tubs* NaI_Det_S = new G4Tubs("NaI_Det_S",0.,Rmax_NaI_Det,0.5*Length_NaI_Det,0.*deg,360.*deg);
  NaI_Det_LV = new G4LogicalVolume(NaI_Det_S, NaI,"NaI_Det_LV",0,0,0);
  new G4PVPlacement(0,               // no rotation
                    position_NaI_Det,  // at (x,y,z)
                    NaI_Det_LV,    // its logical volume
                    "NaI_Det_PV",        // its name
                    worldLV,         // its mother volume
                    false,           // no boolean operations
                    1,               // copy number
                    fCheckOverlaps); // checking overlaps 

  // Visualization attributes

  G4VisAttributes* World_VisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  G4VisAttributes* NaI_Det_VisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));

  worldLV	->SetVisAttributes(World_VisAtt);
  NaI_Det_LV	->SetVisAttributes(NaI_Det_VisAtt);

  G4double maxStep = 0.5*Length_NaI_Det*mm;
  fStepLimit = new G4UserLimits(maxStep);
  NaI_Det_LV->SetUserLimits(fStepLimit);

  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void DetectorConstruction::ConstructSDandField()
{
  // Sensitive detectors
  G4String trackerChamberSDname = "NaISD";
  TrackerSD* aTrackerSD = new TrackerSD(trackerChamberSDname,
                                            "NaI_HitsCollection");
  // Setting aTrackerSD to all logical volumes with the same name 
  // of "Chamber_LV".
  SetSensitiveDetector("NaI_Det_LV", aTrackerSD, true);

  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue = G4ThreeVector(0,0,0);
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);
  
  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}