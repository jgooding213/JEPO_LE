////////////////////////////////////////////////////////////////////////////////
//   BT2017EveAct.cc for beamtest2017 of JEDI                                 //
//                                                                            //
//   Definitions of BT2017EveAct class's member functions. Details of user    //
// actions are here.                                                          //
//                                                                            //
//                    - 20. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include <math.h> 

#include "BT2017EveAct.hh"
#include "BT2017Ana.hh"
#include "LGAD_Hit.hh"
#include "EmCalorimeterHit.hh"

//////////////////////////////////////////////////
//   Constructor                                //
//////////////////////////////////////////////////
BT2017EveAct::BT2017EveAct(BT2017ConMan* CM,BT2017PriGenAct* prigenact)
	: m_CM(CM),m_prigenact(prigenact)
{
	m_DetSet = m_CM -> GetDetSet();
fHodHC1ID = -1;
fHodHC2ID = -1;
fHodHC3ID = -1;
fHodHC4ID = -1;
fHVCMOSHCID = -1;
fHVCMOSHCID_dep = -1;
fHodHC1ID_dep = -1;
fHodHC2ID_dep = -1;

}

//////////////////////////////////////////////////
//   Destructor                                 //
//////////////////////////////////////////////////
BT2017EveAct::~BT2017EveAct()
{
}

//////////////////////////////////////////////////
//   Begin of event action                      //
//////////////////////////////////////////////////
void BT2017EveAct::BeginOfEventAction(const G4Event* /*anEvent*/)
{

  if (fHodHC1ID==-1) {
    auto sdManager = G4SDManager::GetSDMpointer();
    fHodHC1ID = sdManager->GetCollectionID("hodoscope1/hodoscopeColl");
    fHodHC2ID = sdManager->GetCollectionID("hodoscope2/hodoscopeColl");
    fHodHC1ID_dep = sdManager->GetCollectionID("hodoscope1_dep/EMcalorimeterColl");
    fHodHC2ID_dep = sdManager->GetCollectionID("hodoscope2_dep/EMcalorimeterColl");

    fHVCMOSHCID = sdManager->GetCollectionID("HVCMOS/hodoscopeColl");
    fHVCMOSHCID_dep = sdManager->GetCollectionID("HVCMOS_dep/EMcalorimeterColl");
//    fHodHC3ID = sdManager->GetCollectionID("hodoscope3/hodoscopeColl"); 
//    fHodHC4ID = sdManager->GetCollectionID("hodoscope4/hodoscopeColl"); 




  }


	// Initialize
	m_EDepCry.clear();
	m_EDepdE.clear();
	for ( int i = 0; i < 120; i++ ) 	m_EDepCry[i]  = 0.0;
	for ( int i = 0; i <   4; i++ ) 	 m_EDepdE[i]  = 0.0;		
}

//////////////////////////////////////////////////
//   End of event action                        //
//////////////////////////////////////////////////
void BT2017EveAct::EndOfEventAction(const G4Event* anEvent)
{

 auto hce = anEvent->GetHCofThisEvent();
  if (!hce) {
      G4ExceptionDescription msg;
      msg << "No hits collection of this event found." << G4endl; 
      G4Exception("EventAction::EndOfEventAction()",
                  "Code001", JustWarning, msg);
      return;
  }


  // Get hits collections 
  auto hHC1  = static_cast<LGAD_HitsCollection*>(hce->GetHC(fHodHC1ID));
  auto hHC2  = static_cast<LGAD_HitsCollection*>(hce->GetHC(fHodHC2ID));

  auto hHC1_dep  = static_cast<EmCalorimeterHitsCollection*>(hce->GetHC(fHodHC1ID_dep));
  auto hHC2_dep  = static_cast<EmCalorimeterHitsCollection*>(hce->GetHC(fHodHC2ID_dep));

  auto HVCMOSHC  = static_cast<LGAD_HitsCollection*>(hce->GetHC(fHVCMOSHCID));
  auto HVCMOSHC_dep  = static_cast<EmCalorimeterHitsCollection*>(hce->GetHC(fHVCMOSHCID_dep));

	// Get analysis manager
	G4AnalysisManager* AM = G4AnalysisManager::Instance();

	// Fill ntuple with result
	G4int eID = m_prigenact -> GetGenEventID();
	AM -> FillNtupleIColumn(0, eID);

	G4int iDet = 1;

	// input parameters
	AM -> FillNtupleDColumn(iDet++, m_prigenact -> GetParticle());   // 1
	AM -> FillNtupleDColumn(iDet++, m_prigenact -> GetKinEgy());     // 2
	AM -> FillNtupleDColumn(iDet++, m_prigenact -> GetTheta());      // 3
	AM -> FillNtupleDColumn(iDet++, m_prigenact -> GetPhi());        // 4

	// filling initial parameters from generator
	
	//for ( int i = 0; i < 120; i++ )
	//	if ( m_DetSet[i] )
	//		AM -> FillNtupleDColumn(iDet++, m_EDepCry[i]);

	// dE filling
	//for(int i = 0; i < 4; i++)
	//	AM -> FillNtupleDColumn(iDet++, m_EDepdE[i]);
	
	AM -> FillNtupleDColumn(iDet++, xcoor);                          // 5

	G4double zHVCMOS = 70;
	G4double phi = m_prigenact -> GetPhi();
	G4double theta = m_prigenact -> GetTheta();

    G4double r = zHVCMOS * tan(m_prigenact -> GetTheta());
	G4double xHVCMOS = r * sin(m_prigenact -> GetPhi());
    G4double yHVCMOS = r * cos(m_prigenact -> GetPhi());









    auto nhit  = HVCMOSHC->entries();
    //analysisManager->FillH1(0, nhit );

  

  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 for (auto i=0;i<nhit ;i++) {
    auto hit = (*HVCMOSHC)[i];
    auto posh = hit->GetWorldPos();

   AM->FillNtupleDColumn(6, posh[0]/mm);
   AM->FillNtupleDColumn(7, posh[1]/mm);
   AM->FillNtupleDColumn(8, posh[2]/mm);
   AM->FillNtupleDColumn(9,(*HVCMOSHC)[i]->GetTime()/ps);
   AM->FillNtupleDColumn(10,(*HVCMOSHC_dep)[i]->GetEdep()/MeV);
  
  }




    nhit  = hHC1->entries();
    G4double check0; 

  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 for (auto i=0;i<nhit ;i++) {
    auto hit = (*hHC1)[i]; 
    auto worldPos = hit->GetWorldPos();
	AM->FillH2(0, worldPos.x(), worldPos.y());
    auto posh = hit->GetWorldPos();

    AM->FillNtupleDColumn(11, posh[0]/mm);
    AM->FillNtupleDColumn(12, posh[1]/mm);
    AM->FillNtupleDColumn(13, posh[2]/mm);
	AM->FillNtupleDColumn(14,(*hHC1)[i]->GetTime()/ps);
    AM->FillNtupleDColumn(15,(*hHC1_dep)[i]->GetEdep()/MeV);
  
  }




 // // ECEnergy
 //  G4int totalEmHit = 0;
 //  G4double totalEmE = 0.;
 //  //std::vector<G4double> fEmCalPos;
 //  for (auto i=0;i<kNofEmCells;i++) {
 //    auto hit = (*ecHC)[i];
 //    auto edep = hit->GetEdep();
 //    if (edep>0.) {
 //      totalEmHit++;
 //      totalEmE += edep;
 //    }
 //    fEmCalEdep[i] = edep;

  
 //  }
 //  //    G4cout << " DEBUG .. " << pos << G4endl;
 //  analysisManager->FillNtupleDColumn(24, totalEmE);












 nhit  = hHC2->entries();
 for (auto i=0;i<nhit ;i++) {
    auto hit = (*hHC2)[i];
    auto posh = hit->GetWorldPos();
    check0 = posh[0];

          AM->FillNtupleDColumn(16, posh[0]/mm);
          AM->FillNtupleDColumn(17, posh[1]/mm);
          AM->FillNtupleDColumn(18, posh[2]/mm);	
		  AM->FillNtupleDColumn(19,(*hHC2)[i]->GetTime()/ps);	
          AM->FillNtupleDColumn(20,(*hHC2_dep)[i]->GetEdep()/MeV);            
  }

/*
 nhit  = hHC3->entries();
 for (auto i=0;i<nhit ;i++) {
    auto hit = (*hHC3)[i];
    auto posh = hit->GetWorldPos();

	auto worldPos = hit->GetWorldPos();
	//	AM->FillH2(0, worldPos.x(), worldPos.y());
    check0 = posh[0];

          AM->FillNtupleDColumn(14, posh[0]/mm);
          AM->FillNtupleDColumn(15, posh[1]/mm);
          AM->FillNtupleDColumn(16, posh[2]/mm);	
		  AM->FillNtupleDColumn(17, hit->GetTime()/ps);	 	  
  }


 nhit  = hHC4->entries();
 for (auto i=0;i<nhit ;i++) {
    auto hit = (*hHC4)[i];
    auto posh = hit->GetWorldPos();

	auto worldPos = hit->GetWorldPos();
	//	AM->FillH2(0, worldPos.x(), worldPos.y());
    check0 = posh[0];

          AM->FillNtupleDColumn(18, posh[0]/mm);
          AM->FillNtupleDColumn(19, posh[1]/mm);
          AM->FillNtupleDColumn(20, posh[2]/mm);	
		  AM->FillNtupleDColumn(21,hit->GetTime()/ps);	 	  
  }
*/


 //   G4cout << r << " : " << phi << " : " << xHVCMOS << " : " << yHVCMOS << G4endl;


	//G4double xHVCMOS = zHVCMOS * tan(m_prigenact -> GetTheta());
	//G4double yHVCMOS = xHVCMOS * tan(xcoor);

	//  G4double xHVCMOS = xcoor; //zHVCMOS * tan(m_prigenact -> GetTheta());

	//	G4cout << theta*57 << " : " << phi*57 << " : " << xHVCMOS << "   theta phi tantheta CHECK" << G4endl;
	
    G4double counter = (int)((double)eID/(1000));


	//G4cout << "Progress |....................................................................................................|";


    //G4double pol = primary -> GetPolarization();
	//G4cout << counter << "/100" << G4endl;
	// G4cout << xcoor << " : " << x2coor << "xcoor  : x2coor " << G4endl;
	

	
//	AM -> FillNtupleDColumn(iDet++, xHVCMOS);                   // 6
//	AM -> FillNtupleDColumn(iDet++, yHVCMOS);                   // 7
	
	//AM -> FillNtupleDColumn(6, xHVCMOS);                   // 6
	//AM -> FillNtupleDColumn(7, yHVCMOS);                   // 7


	   
	//	AM->FillH2(0, xHVCMOS, yHVCMOS);
		AM->FillH2(1, theta , phi); 
	AM -> AddNtupleRow();
}

//////////////////////////////////////////////////
//   Add energy deposition  to crystals         //
//////////////////////////////////////////////////
void BT2017EveAct::AddEDepCry(G4int id, G4double eD)
{
	m_EDepCry[id] += eD;
}

//////////////////////////////////////////////////
//   Add energy deposition  to scintillators    //
//////////////////////////////////////////////////
void BT2017EveAct::AddEDepdE(G4int id, G4double eD)
{
	m_EDepdE[id] += eD;
}

void BT2017EveAct::AddXcoordinate(G4double Xcoor)
{
	xcoor = Xcoor;
}

void BT2017EveAct::AddY2coordinate(G4double Y2coor)
{
	y2coor = Y2coor;
	
}void BT2017EveAct::AddX2coordinate(G4double X2coor)
{
	x2coor = X2coor;
}
