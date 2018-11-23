#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "tls.hh"
#include "Config.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;
class G4GlobalMagFieldMessenger;

class DetectorMessenger;

/// Detector construction class to define materials, geometry
/// and global uniform magnetic field.

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  virtual ~DetectorConstruction();

public:
  virtual G4VPhysicalVolume* Construct();
  virtual void ConstructSDandField();
  Config* configure;
public://for the materials
  G4Material* Air;
  G4Material* Pb;
  G4Material* Xenon;
  G4Material* Water_Natural;
  G4Material* CaCO3;
  G4Material* Fe;
  G4Material* Silicon;
  G4Material* Rubber_Natural;
  G4Material* NaI;
  G4Material* CsI;
  G4Material* Vacuum;
  G4Material* IsoButane;
  G4Material* Mylar;
  G4Material* _3He;
  G4Material* Paraffin;
  G4Material* Polyethylene;
  G4Material* Teflon;  
  void DefineMaterials();

private:// methods
  G4VPhysicalVolume* DefineVolumes();
  G4LogicalVolume*   NaI_Det_LV;     // pointer to the logical Target

  G4UserLimits* fStepLimit;            // pointer to user step limits

  DetectorMessenger*  fMessenger;   // messenger
  static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger;  // magnetic field messenger    
  G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif