#pragma once

// #ifndef JEPODETCON_h
// #define JEPODETCON_h 1

////////////////////////////////////////////////////////////////////////////////
//   JePoDetCon.hh for beamtest2017 of JEDI                                 //
//                                                                            //
//   This file is a header for JePoDetCon class. It's for construction of   //
// whole geometry of simulation, which includes target geometry and detector  //
// geometry. Details of configuration can be set at config.cfg file. The      //
// configuration is tranfered at main function and used here to generate      //
// world of simulation.                                                       //
//                                                                            //
//                    - 20. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////


#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4SubtractionSolid.hh"

#include "BT2017ConMan.hh"
#include "G4RotationMatrix.hh"

class G4VPhysicalVolume;

class BT2017ConMan;

class JePoDetCon : public G4VUserDetectorConstruction
{
  public:
	JePoDetCon(BT2017ConMan* CM);
	virtual ~JePoDetCon();
	virtual G4VPhysicalVolume* Construct();
	virtual void ConstructSDandField();

  private:
	void DefineDimensions();
	void ConstructMaterials();
	void DestructMaterials();
	void ConstructCrystal(G4String, G4int, G4int, G4int, G4int);
	void ConstructScintillator(G4String, G4int, G4double);
//	void ConstructBeamPipe(G4double f1 = 0, G4double f2 = 2.0*M_PI);

    //void ConstructSymmetricVolume(G4String, G4int, G4double f1 = M_PI/2, G4double f2 = 1.5*M_PI);
	void ConstructSymmetricVolume(G4String, G4int, G4double f1 = 0, G4double f2 = 2*M_PI);

  private:
	// Configuration manager
	BT2017ConMan* m_CM;

	// Elements
	G4Element* m_ElH;
	G4Element* m_ElC;
	G4Element* m_ElN;
	G4Element* m_ElO;
	G4Element* m_ElF;
	G4Element* m_ElMg;
	G4Element* m_ElAl;
	G4Element* m_ElSi;
	G4Element* m_ElAr;
	G4Element* m_ElCr;
	G4Element* m_ElFe;
	G4Element* m_ElNi;
	G4Element* m_ElCu;
	G4Element* m_ElZn;
	G4Element* m_ElY;
	G4Element* m_ElSn;
	G4Element* m_ElCe;
	G4Element* m_ElLu;

	// Materials
	G4Material* m_AirMat;
	G4Material* m_TarMat;
	G4Material* m_DetMat;
	G4Material* m_CouMat;
	G4Material* m_PipMat;
	G4Material* m_VacMat;
	G4Material* m_TefMat;
	G4Material* m_TedMat;
	G4Material* m_KapMat;
	G4Material* m_GasMat;
	G4Material* m_PCBMat;
	G4Material* m_CoaMat;

	G4Material* m_CMOS_DetMat;	

	G4Material* m_SiMat;

	// Dimensions and detector setup
	G4double labX, labY, labZ;
	G4double tarX, tarY, tarT, tarxP, taryP;
	G4double coud, couD, couT;
	G4double scXL, scYL, scZL;
	G4double detE, detL, detG;
	G4double detX, detY, detZ, detA;
	std::vector<G4bool> detS;
	G4double tefT, tedT, kapT;
	G4double ka0Z, ka1Z, ka2Z, ka3Z, ka4Z;
	G4double co0Z, co1Z, co2Z, co3Z, co4Z, co5Z, co6Z, co7Z;
	G4double ga0Z, ga1Z, ga2Z, ga3Z, pcbZ;


    G4double RAD0, RAD1, RAD2;
    G4double DET1THETA_MIN, DET1THETA_MAX, DET2THETA_MIN, DET2THETA_MAX;
    G4double DETLAY1_THICKNESS, DETLAY2_THICKNESS, DETLAY3_THICKNESS;


	G4int CYL_SQ_CONFIG;

	// Geometry objects
	G4Box* 				labSolid;
	G4LogicalVolume*   	labLV;
	G4VPhysicalVolume* 	labPV;

	G4Box* 				target;
	G4LogicalVolume* 	tarLV;


    G4RotationMatrix* fSensorRotation;


    G4LogicalVolume* fHodoscope1Logical_dep;
    G4LogicalVolume* fHodoscope2Logical_dep;
    G4LogicalVolume* fHodoscope1Logical;
    G4LogicalVolume* fHodoscope2Logical;

    G4LogicalVolume* fHVCMOSLogical_dep;
    G4LogicalVolume* fHVCMOSLogical;




    G4LogicalVolume* logicDet_A0_UD;
    G4LogicalVolume* logicDet_A1_UD;
    G4LogicalVolume* logicDet_A2_UD;
    G4LogicalVolume* logicDet_A3_UD;

    G4LogicalVolume* logicDet_B0_UD;
    G4LogicalVolume* logicDet_B1_UD;
    G4LogicalVolume* logicDet_B2_UD;
    G4LogicalVolume* logicDet_B3_UD;

    G4LogicalVolume* logicDet_A0_LR;
    G4LogicalVolume* logicDet_A1_LR;
    G4LogicalVolume* logicDet_A2_LR;
    G4LogicalVolume* logicDet_A3_LR;

    G4LogicalVolume* logicDet_B0_LR;
    G4LogicalVolume* logicDet_B1_LR;
    G4LogicalVolume* logicDet_B2_LR;
    G4LogicalVolume* logicDet_B3_LR;






    G4LogicalVolume* logicDet_A0;
    G4LogicalVolume* logicDet_A1;
    G4LogicalVolume* logicDet_A2;
    G4LogicalVolume* logicDet_A3;


    G4LogicalVolume* logicDet_B0;
    G4LogicalVolume* logicDet_B1;
    G4LogicalVolume* logicDet_B2;
    G4LogicalVolume* logicDet_B3;




    G4LogicalVolume*   f11Logical;  
	G4LogicalVolume*   f12Logical;  
	G4LogicalVolume*   f11Logical_dep;  
	G4LogicalVolume*   f12Logical_dep; 

	G4LogicalVolume*   f13Logical;  
	G4LogicalVolume*   f13Logical_dep;  


    G4LogicalVolume*   f21Logical;  
	G4LogicalVolume*   f22Logical;  
	G4LogicalVolume*   f21Logical_dep;  
	G4LogicalVolume*   f22Logical_dep; 

		G4LogicalVolume*   f23Logical;  
	G4LogicalVolume*   f23Logical_dep;  

    G4LogicalVolume*   f31Logical;  
	G4LogicalVolume*   f32Logical;  
	G4LogicalVolume*   f31Logical_dep;  
	G4LogicalVolume*   f32Logical_dep; 

	G4LogicalVolume*   f33Logical;  
	G4LogicalVolume*   f33Logical_dep;  



    G4LogicalVolume* testLV;


    G4VPhysicalVolume* testPV;








	G4Box* 				kaptonBase;
	G4SubtractionSolid* kapton;

	G4LogicalVolume* 	kapLV[120];
	G4ThreeVector    	kapPos[120];

	G4Box* 				tedlarBase;
	G4SubtractionSolid* tedlar;

	G4LogicalVolume* 	tedLV[120];
	G4ThreeVector    	tedPos[120];

	G4Box* 				teflonBase;
	G4SubtractionSolid* teflon;

	G4LogicalVolume* 	tefLV[120];
	G4ThreeVector    	tefPos[120];

	G4String         	cryName[120];
	G4Box*           	crystal;
	G4LogicalVolume* 	cryLV[120];
	G4ThreeVector    	cryPos[120];

	G4bool 				isConstructed[120] = {false};

	// new pl. dE, 4 arms
	G4String			sciName[4];
	G4Box*				scintillator;
	G4LogicalVolume*	sciLV[4];
	G4ThreeVector		vector[4];
	G4bool				sciIsConstructed[4] = {false};
	G4RotationMatrix* 	pRot[4];

	G4Tubs*          	vacSolid;
	G4LogicalVolume* 	vacLV;

	G4Box* 				kapFil[5];
	G4Box* 				copCoa[8];
	G4Box* 				gasGap[4];
	G4Box* 				pcb;
	G4LogicalVolume* 	kapFilLV[5];
	G4LogicalVolume* 	copCoaLV[8];
	G4LogicalVolume* 	gasGapLV[4];
	G4LogicalVolume* 	pcbLV;

	// Rotation for crystals
	G4RotationMatrix* 	cryRot;

	// construction of symetric volumes
	G4VisAttributes	*steelVis ;
	G4double			symVolZpos[6] = {0.0};
	G4Material*			symVolMaterial;
	G4Polycone*			symVol[6];
	G4LogicalVolume*	symVolLog[6];
	G4String			symVolName[6];
	G4bool				symVolIsON[6];
	G4bool				symVolConstructed[6] = {false};

	// volume B0
	const	static G4int		nz0 = 7 ;
	G4double*			zz0;
	G4double*			Rmin0;
	G4double*			Rmax0;

	// volume B1
	const	static G4int 		nz1 = 6 ;
	G4double*			zz1;
	G4double*			Rmin1;
	G4double*			Rmax1;

	// volume B2
	const	static G4int 		nz2 = 6 ;
	G4double*			zz2;
	G4double*			Rmin2;
	G4double*			Rmax2;

	// volume B3
	const	static G4int 		nz3 = 6 ;
	G4double*			zz3;
	G4double*			Rmin3;
	G4double*			Rmax3; 

	// volume Bv
	const	static G4int 		nzv = 10 ;
	G4double*			zzv;
	G4double*			Rminv;
	G4double*			Rmaxv;

	// volume Bw
	const	static G4int 		nzw = 6 ;
	G4double*			zzw;
	G4double*			Rminw;
	G4double*			Rmaxw;
};
// #endif
