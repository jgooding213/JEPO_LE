#ifndef BT2017EVEACT_h
#define BT2017EVEACT_h 1

////////////////////////////////////////////////////////////////////////////////
//   BT2017EveAct.hh for beamtest2017 of JEDI                                 //
//                                                                            //
//   This file is a header for BT2017EveAct class. User can add user-defined  //
// event action in this class.                                                //
//                                                                            //
//                    - 22. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4UserEventAction.hh"
#include "G4String.hh"
#include <map>

#include "BT2017PriGenAct.hh"

#include "BT2017ConMan.hh"

class G4Event;

class BT2017ConMan;

class BT2017EveAct: public G4UserEventAction
{
  public:
	BT2017EveAct(BT2017ConMan* CM, BT2017PriGenAct* prigenact);
	virtual ~BT2017EveAct();

	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(  const G4Event*);

	void AddEDepCry(G4int, G4double);
	void AddEDepdE( G4int, G4double);
	void AddXcoordinate (G4double);
	void AddX2coordinate (G4double);  
	void AddY2coordinate (G4double);
  private:
	std::map<G4int, G4double> m_EDepCry;
	std::map<G4int, G4double> m_EDepdE;
	G4double xcoor;
  
	G4double y2coor;  
	G4double x2coor;	
//	G4double m_EDepdE;

	BT2017ConMan* m_CM;
	std::vector<G4bool> m_DetSet;
	BT2017PriGenAct* m_prigenact;




    G4int fHodHC1ID;
    G4int fHodHC2ID;
    G4int fHodHC3ID;
    G4int fHodHC4ID;

    G4int fHVCMOSHCID;
    G4int fHVCMOSHCID_dep;


    G4int fHodHC1ID_dep;
    G4int fHodHC2ID_dep;	
};

#endif
