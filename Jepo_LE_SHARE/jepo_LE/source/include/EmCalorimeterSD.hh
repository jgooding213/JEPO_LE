

#ifndef EmCalorimeterSD_h
#define EmCalorimeterSD_h 1

#include "G4VSensitiveDetector.hh"

#include "EmCalorimeterHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

/// EM calorimeter sensitive detector

class EmCalorimeterSD : public G4VSensitiveDetector
{   
  public:
    EmCalorimeterSD(G4String name);
    virtual ~EmCalorimeterSD();
    
    virtual void Initialize(G4HCofThisEvent*HCE);
    virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
    
  private:
    EmCalorimeterHitsCollection* fHitsCollection;
    G4int fHCID;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
