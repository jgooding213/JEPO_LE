
#ifndef LGAD_Hit_h
#define LGAD_Hit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

class G4AttDef;
class G4AttValue;

/// Hodoscope hit
///
/// It records:
/// - the strip ID
/// - the particle time
/// - the strip logical volume, its position and rotation

class LGAD_Hit : public G4VHit
{
  public:
    LGAD_Hit(G4int i,G4double t);
    LGAD_Hit(const LGAD_Hit &right);
    virtual ~LGAD_Hit();

    const LGAD_Hit& operator=(const LGAD_Hit &right);
    int operator==(const LGAD_Hit &right) const;
    
    inline void *operator new(size_t);
    inline void operator delete(void*aHit);
    
    void Draw();
    virtual const std::map<G4String,G4AttDef>* GetAttDefs() const;
    virtual std::vector<G4AttValue>* CreateAttValues() const;
    void Print();
    
    G4int GetID() const { return fId; }

    void SetTime(G4double val) { fTime = val; }
    G4double GetTime() const { return fTime; }

    void SetPos(G4ThreeVector xyz) { fPos = xyz; }
    G4ThreeVector GetPos() const { return fPos; }

    void SetWorldPos(G4ThreeVector xyz) { fWorldPos = xyz; }
    G4ThreeVector GetWorldPos() const { return fWorldPos; }
  

    void SetRot(G4RotationMatrix rmat) { fRot = rmat; }
    G4RotationMatrix GetRot() const { return fRot; }

    void SetLogV(G4LogicalVolume* val) { fPLogV = val; }
    const G4LogicalVolume* GetLogV() const { return fPLogV; }


    void SetEdep(G4double de) { fEdep = de; }
    void AddEdep(G4double de) { fEdep += de; }
    G4double GetEdep() const { return fEdep; }

    
  private:
    G4int fId;
    G4double fTime;
    G4ThreeVector fPos;
    G4ThreeVector fWorldPos;  
    G4RotationMatrix fRot;
    const G4LogicalVolume* fPLogV;
    G4double fEdep;
};

using LGAD_HitsCollection = G4THitsCollection<LGAD_Hit>;

extern G4ThreadLocal G4Allocator<LGAD_Hit>* LGAD_HitAllocator;

inline void* LGAD_Hit::operator new(size_t)
{
  if (!LGAD_HitAllocator) {
       LGAD_HitAllocator = new G4Allocator<LGAD_Hit>;
  }
  return (void*)LGAD_HitAllocator->MallocSingle();
}

inline void LGAD_Hit::operator delete(void*aHit)
{
  LGAD_HitAllocator->FreeSingle((LGAD_Hit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
