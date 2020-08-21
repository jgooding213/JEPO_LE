

#include "LGAD_Hit.hh"

#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal G4Allocator<LGAD_Hit>* LGAD_HitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LGAD_Hit::LGAD_Hit(G4int id,G4double time)
: G4VHit(), 
  fId(id), fTime(time), fPos(0.), fPLogV(nullptr)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LGAD_Hit::~LGAD_Hit()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LGAD_Hit::LGAD_Hit(const LGAD_Hit &right)
: G4VHit(),
  fId(right.fId),
  fTime(right.fTime),
  fPos(right.fPos),
  fRot(right.fRot),
  fPLogV(right.fPLogV)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const LGAD_Hit& LGAD_Hit::operator=(const LGAD_Hit &right)
{
  fId = right.fId;
  fTime = right.fTime;
  fPos = right.fPos;
  fRot = right.fRot;
  fPLogV = right.fPLogV;
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int LGAD_Hit::operator==(const LGAD_Hit &/*right*/) const
{
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LGAD_Hit::Draw()
{
  auto visManager = G4VVisManager::GetConcreteInstance();
  if (! visManager) return;

  G4Transform3D trans(fRot.inverse(),fPos);
  G4VisAttributes attribs;
  auto pVA = fPLogV->GetVisAttributes();
  if (pVA) attribs = *pVA;
  G4Colour colour(0.,1.,1.);
  attribs.SetColour(colour);
  attribs.SetForceSolid(true);
  visManager->Draw(*fPLogV,attribs,trans);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const std::map<G4String,G4AttDef>* LGAD_Hit::GetAttDefs() const
{
  G4bool isNew;
  auto store = G4AttDefStore::GetInstance("LGAD_Hit",isNew);

  if (isNew) {
    (*store)["HitType"] 
      = G4AttDef("HitType","Hit Type","Physics","","G4String");
    
    (*store)["ID"] 
      = G4AttDef("ID","ID","Physics","","G4int");
    
    (*store)["Time"] 
      = G4AttDef("Time","Time","Physics","G4BestUnit","G4double");
    
    (*store)["Pos"] 
      = G4AttDef("Pos","Position","Physics","G4BestUnit","G4ThreeVector");
    
    (*store)["LVol"] 
      = G4AttDef("LVol","Logical Volume","Physics","","G4String");
  }
  return store;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<G4AttValue>* LGAD_Hit::CreateAttValues() const
{
  auto values = new std::vector<G4AttValue>;
  
  values
    ->push_back(G4AttValue("HitType","HodoscopeHit",""));
  values
    ->push_back(G4AttValue("ID",G4UIcommand::ConvertToString(fId),""));
  values
    ->push_back(G4AttValue("Time",G4BestUnit(fTime,"Time"),""));
  values
    ->push_back(G4AttValue("Pos",G4BestUnit(fPos,"Length"),""));
  
  if (fPLogV)
    values->push_back(G4AttValue("LVol",fPLogV->GetName(),""));
  else
    values->push_back(G4AttValue("LVol"," ",""));
  
  return values;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LGAD_Hit::Print()
{
  G4cout << "  Hodoscope[" << fId << "] " << fTime/ns << " (nsec)" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
