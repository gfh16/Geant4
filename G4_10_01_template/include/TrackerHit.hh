#ifndef TrackerHit_h
#define TrackerHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

/// Tracker hit class
///
/// It defines data members to store the trackID, chamberNb, energy deposit,
/// and position of charged particles in a selected volume:
/// - fTrackID, fChamberNB, fEdep, fPos

class TrackerHit : public G4VHit
{
public:
  TrackerHit();
  TrackerHit(const TrackerHit&);
  virtual ~TrackerHit();

  // operators
  const TrackerHit& operator=(const TrackerHit&);
  G4int operator==(const TrackerHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  // methods from base class
  virtual void Draw();
  virtual void Print();

  // Set methods
  void SetTrackID(G4int track)		{ fTrackID = track; };
  void SetGEO_copyNum(G4int copyNum)	{ GEO_copyNum = copyNum; };
  void SetEdep(G4double de)		{ fEdep = de; };
  void SetPos(G4ThreeVector xyz)	{ fPos = xyz; };
  void SetTime(G4double time)		{ fTime = time; }

  // Get methods
  G4int GetTrackID() const	{ return fTrackID; };
  G4int GetGEO_copyNum() const	{ return GEO_copyNum; };
  G4double GetEdep() const	{ return fEdep; };
  G4ThreeVector GetPos() const	{ return fPos; };
  G4double GetTime() const	{ return fTime; }

private:
  G4int		fTrackID;
  G4int		GEO_copyNum;
  G4double	fEdep;
  G4ThreeVector	fPos;
  G4double	fTime;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<TrackerHit> TrackerHitsCollection;

extern G4ThreadLocal G4Allocator<TrackerHit>* TrackerHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* TrackerHit::operator new(size_t)
{
  if(!TrackerHitAllocator)
      TrackerHitAllocator = new G4Allocator<TrackerHit>;
  return (void *) TrackerHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void TrackerHit::operator delete(void *hit)
{
  TrackerHitAllocator->FreeSingle((TrackerHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
