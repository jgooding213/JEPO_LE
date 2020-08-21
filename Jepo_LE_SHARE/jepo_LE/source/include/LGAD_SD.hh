
#ifndef LGAD_SD_h
#define LGAD_SD_h 1

#include "G4VSensitiveDetector.hh"
#include "LGAD_Hit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

/// Hodoscope sensitive detector

class LGAD_SD : public G4VSensitiveDetector
{
  public:
    LGAD_SD(G4String name);
    virtual ~LGAD_SD();
    
    virtual void Initialize(G4HCofThisEvent*HCE);
    virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
    
  private:
    LGAD_HitsCollection* fHitsCollection;
    G4int fHCID;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
