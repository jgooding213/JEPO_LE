#ifndef BT2017CONMAN_h
#define BT2017CONMAN_h 1

////////////////////////////////////////////////////////////////////////////////
//   BT2017ConMan.hh for beamtest2017 of JEDI                                 //
//                                                                            //
//   This file is a header for BT2017ConMan class. It's a configuration       //
// manager for simulation. The class contains all configuration parameters    //
// for simulation configuration from a file.                                  //
//                                                                            //
//                    - 20. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <vector>
#include "globals.hh"

class BT2017ConMan
{
  public:
	// ructors and Destructor
	BT2017ConMan();
	BT2017ConMan(const char* fileName);
	~BT2017ConMan();

	// Initialize
	void Init(const char* fileName = 0);

	// Load configuration file
	bool Load(const char* fileName);
	void PrintConfiguration();

	// Set & get configurations: Computing
	void SetUseMTD( G4bool   useMTD);
	 G4bool   GetUseMTD();
	void SetNofTRD( G4int    nofTRD);
	 G4int    GetNofTRD();

	// Set & get configuration:  number of events and cycles
	void SetNumberEv( G4int   numberOfEvents);
	 G4int   GetNumberEv();

	// Set & get configurations: Physics
	void SetUseJED( G4bool   useJED);
	 G4bool   GetUseJED() ;
	// Set & get configurations: World
	void SetWorldX( G4double worldX);
	 G4double GetWorldX() ;
	void SetWorldY( G4double worldY);
	 G4double GetWorldY() ;
	void SetWorldZ( G4double worldZ);
	 G4double GetWorldZ() ;
	// Set & get configurations: Beam
	void SetBeamDX( G4double beamDX);
	G4double GetBeamDX() ;
	void SetBeamDY( G4double beamDY);
	G4double GetBeamDY() ;
	void SetBeamKE(G4double beamKE);
	G4double GetBeamKE() ;
	void SetBeamAX(G4double beamAX);
	G4double GetBeamAX() ;
	void SetBeamAY(G4double beamAY);
	G4double GetBeamAY() ;
	void SetBeamAZ(G4double beamAZ);
	G4double GetBeamAZ() ;
	void SetBeamPO(G4double beamPO);
	G4double GetBeamPO() ;
	void SetBeamPP(G4double beamPP);
	G4double GetBeamPP() ;
	void SetBeamAN(G4double beamAN);
	G4double GetBeamAN() ;
	// Particle
	void SetParName(std::string parname);
	std::string GetParName();
	void SetMinThe(G4double beamST);
	G4double GetMinThe();
	void SetMaxThe(G4double beamLT);
	G4double GetMaxThe();
	// Set & get configurations: Target
	void SetUseTar(G4bool   useTar);
	G4bool   GetUseTar() ;
	void SetTarMat(G4String tarMat);
	G4String GetTarMat() ;
	void SetTarThi(G4double tarThi);
	G4double GetTarThi() ;
	void SetTarXle(G4double tarXle);
	G4double GetTarXle() ;
	void SetTarYle(G4double tarYle);
	G4double GetTarYle() ;
	void SetTarPoX(G4double tarPoX);
	G4double GetTarPoX() ;
	void SetTarPoY(G4double tarPoY);
	G4double GetTarPoY() ;
	// E scintilator
	void SetExpand(G4double expand);
	G4double GetExpand();

	void Set_CYL_SQ_CONFIG(G4int CYL_SQ_CONFIG);
	G4int Get_CYL_SQ_CONFIG();


	void SetDET1THETA_MIN(G4double DET1THETA_MIN);
	G4double GetDET1THETA_MIN() ;
	void SetDET1THETA_MAX(G4double DET1THETA_MAX);
	G4double GetDET1THETA_MAX() ;

	void SetDET2THETA_MIN(G4double DET2THETA_MIN);
	G4double GetDET2THETA_MIN() ;
	void SetDET2THETA_MAX(G4double DET2THETA_MAX);
	G4double GetDET2THETA_MAX() ;




	void SetRAD0(G4double RAD0);
	G4double GetRAD0() ;
	void SetRAD1(G4double RAD1);
	G4double GetRAD1() ;
	void SetRAD2(G4double RAD2);
	G4double GetRAD2() ;

	void SetDETLAY1_THICKNESS(G4double DETLAY1_THICKNESS);
	G4double GetDETLAY1_THICKNESS() ;

	void SetDETLAY2_THICKNESS(G4double DETLAY2_THICKNESS);
	G4double GetDETLAY2_THICKNESS() ;

	void SetDETLAY3_THICKNESS(G4double DETLAY3_THICKNESS);
	G4double GetDETLAY3_THICKNESS() ;


	void SetDETLAY1_MAT(G4String DETLAY1_MAT);
	G4String GetDETLAY1_MAT() ;

	void SetDETLAY2_MAT(G4String DETLAY2_MAT);
	G4String GetDETLAY2_MAT() ;

	void SetDETLAY3_MAT(G4String DETLAY3_MAT);
	G4String GetDETLAY3_MAT() ;


	// Set & get configurations: Crystals
	void SetDetSet(std::vector<G4bool> detSet);
	std::vector<G4bool> GetDetSet() ;
	void SetDetPoX(G4double detPoX);
	G4double GetDetPoX() ;
	void SetDetPoY(G4double detPoY);
	G4double GetDetPoY() ;
	void SetDetPoZ(G4double detPoZ);
	G4double GetDetPoZ() ;
	void SetDetAng(G4double detAng);
	G4double GetDetAng() ;




	// Turn on and off differents parts
	void SetUseVB0(G4bool SetUsVB0);
	G4bool   GetUseVB0() ;
	void SetUseVB1(G4bool SetUsVB1);
	G4bool   GetUseVB1() ;
	void SetUseVB2(G4bool SetUsVB2);
	G4bool   GetUseVB2() ;
	void SetUseVB3(G4bool SetUsVB3);
	G4bool   GetUseVB3() ;
	void SetUseVBV(G4bool SetUsVBV);
	G4bool   GetUseVBV() ;
	void SetUseVBW(G4bool SetUsVBW);
	G4bool   GetUseVBW() ;

	// Does the line start with specific word?
	bool StartsWith(const std::string& line, const std::string& token);

  private:
	void SetDefault();

	// Computing resource
	std::string m_SUseMTD; G4bool   m_UseMTD;
	std::string m_SNofTRD; G4int    m_NofTRD;
	// events and cycles
	std::string m_SNumEve; G4int m_NumEve;
	// Physics
	std::string m_SUseJED; G4bool   m_UseJED;
	// World
	std::string m_SWorldX; G4double m_WorldX;
	std::string m_SWorldY; G4double m_WorldY;
	std::string m_SWorldZ; G4double m_WorldZ;
	// Beam
	std::string m_SBeamDX; G4double m_BeamDX;
	std::string m_SBeamDY; G4double m_BeamDY;
	std::string m_SBeamKE; G4double m_BeamKE;
	std::string m_SBeamAX; G4double m_BeamAX;
	std::string m_SBeamAY; G4double m_BeamAY;
	std::string m_SBeamAZ; G4double m_BeamAZ;
	std::string m_SBeamPO; G4double m_BeamPO;
	std::string m_SBeamPP; G4double m_BeamPP;
	std::string m_SBeamAN; G4double m_BeamAN;
	// Particle
	std::string m_SParName;
	std::string m_SBeamST; G4double m_BeamST;
	std::string m_SBeamLT; G4double m_BeamLT;
	// Target
	std::string m_SUseTar; G4bool   m_UseTar;
	std::string m_STarMat; G4String m_TarMat;
	std::string m_STarThi; G4double m_TarThi;
	std::string m_STarXle; G4double m_TarXle;
	std::string m_STarYle; G4double m_TarYle;
	std::string m_STarPoX; G4double m_TarPoX;
	std::string m_StarPoY; G4double m_TarPoY;



    // Detector configuration
	std::string m_SCYL_SQ_CONFIG; G4double m_CYL_SQ_CONFIG;


	std::string m_SDET1THETA_MIN; G4double m_DET1THETA_MIN;
	std::string m_SDET1THETA_MAX; G4double m_DET1THETA_MAX;	
	std::string m_SDET2THETA_MIN; G4double m_DET2THETA_MIN;
	std::string m_SDET2THETA_MAX; G4double m_DET2THETA_MAX;	

	std::string m_SRAD0; G4double m_RAD0;	
	std::string m_SRAD1; G4double m_RAD1;	
	std::string m_SRAD2; G4double m_RAD2;	

	std::string m_SDETLAY1_THICKNESS; G4double m_DETLAY1_THICKNESS;		
	std::string m_SDETLAY2_THICKNESS; G4double m_DETLAY2_THICKNESS;	
	std::string m_SDETLAY3_THICKNESS; G4double m_DETLAY3_THICKNESS;	

	std::string m_SDETLAY1_MAT; G4double m_DETLAY1_MAT;	
	std::string m_SDETLAY2_MAT; G4double m_DETLAY2_MAT;	
	std::string m_SDETLAY3_MAT; G4double m_DETLAY3_MAT;	











/*
USELESS? ->
*/

	// Parts of construction
	std::string m_SUseVB0; G4bool   m_UseVB0;
	std::string m_SUseVB1; G4bool   m_UseVB1;
	std::string m_SUseVB2; G4bool   m_UseVB2;
	std::string m_SUseVB3; G4bool   m_UseVB3;
	std::string m_SUseVBV; G4bool   m_UseVBV;
	std::string m_SUseVBW; G4bool   m_UseVBW;


	//	E scintilator
	std::string m_SSciEpx; G4double m_SciEpx;
	// Crystals
	std::string m_SDetSet; std::vector<G4bool> m_DetSet;
	std::string m_SDetPoX; G4double m_DetPoX;
	std::string m_SDetPoY; G4double m_DetPoY;
	std::string m_SDetPoZ; G4double m_DetPoZ;
	std::string m_SDetAng; G4double m_DetAng;

	std::string m_SDet_dim_X; G4double m_Det_dim_X;
	std::string m_SDet_dim_Y; G4double m_Det_dim_Y;
	std::string m_SDet_dim_Z; G4double m_Det_dim_Z;



	// GEM
	std::string m_SUseGEM; G4bool   m_UseGEM;
	std::string m_SGEMPoX; G4double m_GEMPoX;
	std::string m_SGEMPoY; G4double m_GEMPoY;
	std::string m_SGEMPoZ; G4double m_GEMPoZ;


};

#endif
