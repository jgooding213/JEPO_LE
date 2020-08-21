
#include "LGAD_SD.hh"
#include "LGAD_Hit.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LGAD_SD::LGAD_SD(G4String name)
: G4VSensitiveDetector(name), 
  fHitsCollection(nullptr), fHCID(-1)
{
  collectionName.insert( "hodoscopeColl");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LGAD_SD::~LGAD_SD()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LGAD_SD::Initialize(G4HCofThisEvent* hce)
{
  fHitsCollection = new LGAD_HitsCollection
  (SensitiveDetectorName,collectionName[0]);
  if (fHCID<0) { 
    fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection); 
  }
  hce->AddHitsCollection(fHCID,fHitsCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool LGAD_SD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
  auto edep = step->GetTotalEnergyDeposit();
  if (edep==0.) return true;
  
  auto preStepPoint = step->GetPreStepPoint();
  auto touchable = preStepPoint->GetTouchable();
  auto copyNo = touchable->GetVolume()->GetCopyNo();
  auto hitTime = preStepPoint->GetGlobalTime();
  auto worldPos = preStepPoint->GetPosition();
  
  // check if this finger already has a hit
  auto ix = -1;
  for (auto i=0;i<fHitsCollection->entries();i++) {
    if ((*fHitsCollection)[i]->GetID()==copyNo) {
      ix = i;
      break;
    }
  }

  if (ix>=0) {
    // if it has, then take the earlier time
    if ((*fHitsCollection)[ix]->GetTime()>hitTime) { 
      (*fHitsCollection)[ix]->SetTime(hitTime); 
    }
  }
  else {
    // if not, create a new hit and set it to the collection
    auto hit = new LGAD_Hit(copyNo,hitTime);
    auto physical = touchable->GetVolume();
    hit->SetLogV(physical->GetLogicalVolume());
    auto transform = touchable->GetHistory()->GetTopTransform();
    transform.Invert();
    hit->SetRot(transform.NetRotation());
    hit->SetPos(transform.NetTranslation());
    hit->SetWorldPos(worldPos);
    fHitsCollection->insert(hit);
      hit->AddEdep(edep);
  }    

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
