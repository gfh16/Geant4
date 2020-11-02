//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file MyDetectorConstruction.cc
/// \brief Implementation of the MyDetectorConstruction class

#include "MyDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SDManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyDetectorConstruction::MyDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyDetectorConstruction::~MyDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  G4bool isotopes = false;

  G4Element*  O = nist->FindOrBuildElement("O" , isotopes);
  G4Element* Si = nist->FindOrBuildElement("Si", isotopes);
  G4Element* Lu = nist->FindOrBuildElement("Lu", isotopes);

  G4Material* LSO = new G4Material("Lu2SiO5", 7.4*g/cm3, 3);
  LSO->AddElement(Lu, 2);
  LSO->AddElement(Si, 1);
  LSO->AddElement(O , 5);

  G4Element* Cs = nist->FindOrBuildElement(55, isotopes);
  G4Element* I  = nist->FindOrBuildElement(53,  isotopes);
  G4Material* CsI = new G4Material("CsI", 3.4079*g/cm3, 2);
  CsI->AddElement(Cs, 1);
  CsI->AddElement(I, 1);


  G4bool fCheckOverlaps = true;


  G4LogicalVolumeStore* LVs=G4LogicalVolumeStore::GetInstance();
  G4int nb_cryst = 20;
  G4int nb_rings = 20;

  G4double dPhi = twopi/nb_cryst;

  G4double ring_R1 = 0.8*m, &R_in=ring_R1;
  G4double ring_R2 = 1.1*m, &R_out=ring_R2;

  G4double detector_dZ = 2.*m;
  G4double cryst_length = detector_dZ / nb_rings;



  //
  G4Material* default_mat = nist->FindOrBuildMaterial("G4_AIR");
  //G4Material* cryst_mat   = nist->FindOrBuildMaterial("Lu2SiO5");
  G4Material* cryst_mat   = nist->FindOrBuildMaterial("CsI");

  //
  // World
  //
  G4double world_sizeXY = 2.4*ring_R2;
  G4double world_sizeZ  = 1.2*detector_dZ;

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ); //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        default_mat,         //its material
                        "World");            //its name
  LVs->Register(logicWorld);

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      fCheckOverlaps);       // checking overlaps

  //
  // ring
  //
  G4Tubs* solidRing =
    new G4Tubs("Ring", ring_R1, ring_R2, cryst_length, 0., twopi);

  G4LogicalVolume* logicRing =
    new G4LogicalVolume(solidRing,           //its solid
                        default_mat,         //its material
                        "Ring");             //its name
  LVs->Register(logicRing);
  //
  // define crystal
  //
  G4double gap = 0.5*mm;        //a gap for wrapping
  G4double real_cryst_length = cryst_length - gap;//, dY = cryst_dY - gap;
  //G4Box* solidCryst = new G4Box("crystal", dX/2, dY/2, cryst_dZ/2);
  G4Tubs* solidCryst = new G4Tubs("crystal", R_in, R_out, real_cryst_length, -dPhi, dPhi);

  G4LogicalVolume* logicCryst =
    new G4LogicalVolume(solidCryst,          //its solid
                        cryst_mat,           //its material
                        "CrystalLV");        //its name
  LVs->Register(logicCryst);

  fScoringVolume = logicCryst;

  // place crystals within a ring
  //
  for (G4int icrys = 0; icrys < nb_cryst ; icrys++) {
    G4double phi = icrys*dPhi;
    G4RotationMatrix rotm  = G4RotationMatrix();
    //rotm.rotateY(90*deg);
    rotm.rotateZ(phi);
    //G4ThreeVector uz = G4ThreeVector(std::cos(phi),  std::sin(phi),0.);
    G4ThreeVector uz = G4ThreeVector(0., 0., 0.);
    G4ThreeVector position = (ring_R1+cryst_length)*uz;
    G4Transform3D transform = G4Transform3D(rotm,position);

    new G4PVPlacement(transform,             //rotation,position
                      logicCryst,            //its logical volume
                      "crystal",             //its name
                      logicRing,             //its mother  volume
                      false,                 //no boolean operation
                      icrys,                 //copy number
                      fCheckOverlaps);       // checking overlaps
  }

  //
  // full detector
  //
  G4Tubs* solidDetector =
    new G4Tubs("Detector", ring_R1, ring_R2, 0.5*detector_dZ, 0., twopi);

  G4LogicalVolume* logicDetector =
    new G4LogicalVolume(solidDetector,       //its solid
                        default_mat,         //its material
                        "Detector");         //its name
  LVs->Register(logicDetector);
  //
  // place rings within detector
  //
  G4double OG = -0.5*(detector_dZ + cryst_length);
  for (G4int iring = 0; iring < nb_rings ; iring++) {
    OG += cryst_length;
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(0,0,OG), //position
                      logicRing,             //its logical volume
                      "ring",                //its name
                      logicDetector,         //its mother  volume
                      false,                 //no boolean operation
                      iring,                 //copy number
                      fCheckOverlaps);       // checking overlaps
  }

  //
  // place detector in world
  //
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicDetector,           //its logical volume
                    "Detector",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    fCheckOverlaps);         // checking overlaps

                    logicRing->SetVisAttributes (G4VisAttributes::GetInvisible());
                    logicDetector->SetVisAttributes (G4VisAttributes::GetInvisible());

  // Print materials
  // G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  //always return the physical World
  //
  return physWorld;

}



void MyDetectorConstruction::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  G4LogicalVolumeStore* LVs=G4LogicalVolumeStore::GetInstance();


  G4UniformMagField* field = new G4UniformMagField(G4ThreeVector(0., 0., 0.5*tesla));
  G4FieldManager* fieldManager = new G4FieldManager(field);
  LVs->GetVolume("World")->SetFieldManager(fieldManager, true);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
