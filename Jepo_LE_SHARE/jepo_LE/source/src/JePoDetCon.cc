////////////////////////////////////////////////////////////////////////////////
//   JePoDetCon.cc for beamtest2017 of JEDI                                 //
//                                                                            //
//   Definitions of JePoDetCon class's member functions.                    //
// And it describes geometry of simulation.                                   //
//                                                                            //
//                    - 20. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////
#define PI 3.14159265359

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4UIcommand.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Polycone.hh"

#include "JePoDetCon.hh"
#include "LGAD_SD.hh"
#include "EmCalorimeterSD.hh"



#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4GenericMessenger.hh"


#include "G4SDParticleFilter.hh"
//////////////////////////////////////////////////
//   Constructor and destructor                 //
//////////////////////////////////////////////////
JePoDetCon::JePoDetCon(BT2017ConMan* CM)
	: m_CM(CM)
{
	ConstructMaterials();
	DefineDimensions();
}


JePoDetCon::~JePoDetCon()
{
	DestructMaterials();
}


//////////////////////////////////////////////////
//   Define dimensions                          //
//////////////////////////////////////////////////
void JePoDetCon::DefineDimensions()
{

	// World dimensions
	// // Laboratory size
	labX = m_CM -> GetWorldX(); // World x dimension
	labY = m_CM -> GetWorldY(); // World y dimension
	labZ = m_CM -> GetWorldZ(); // World z dimension

	// Target dimensions
	tarT = m_CM -> GetTarThi(); // Thickness along Y axis
	tarX = m_CM -> GetTarXle(); // length along X axis
	tarY = m_CM -> GetTarYle(); // length along Y axis
	tarxP= m_CM -> GetTarPoX(); // target X position
	taryP= m_CM -> GetTarPoY(); // target Y position


// GET SILICON DIMENSIONS... JG



}


//////////////////////////////////////////////////
//   Construct everything                       //
//////////////////////////////////////////////////
G4VPhysicalVolume* JePoDetCon::Construct()
{
	// World
	labSolid = new G4Box("labSolid", labX/2, labY/2, labZ/2);
	labLV = new G4LogicalVolume(labSolid, m_VacMat, "labLV");
	labPV = new G4PVPlacement(0, G4ThreeVector(), "labPV", labLV, 0, false, 0);

	// Perpendicular target
	target = new G4Box("target", tarX/2, tarY/2, tarT/2);
	tarLV = new G4LogicalVolume(target, m_TarMat, "tarLV");
	if ( m_CM -> GetUseTar() )
		new G4PVPlacement(0, G4ThreeVector(tarxP, taryP, 0), "tarPV", tarLV, labPV, false, 0);	

	// Material and VisAttribute initialization for symmetric volumes
	symVolMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_STAINLESS-STEEL") ;
	steelVis = new G4VisAttributes(G4Colour(0.75,0.75,0.75)) ;
	steelVis->SetVisibility(true) ;



	CYL_SQ_CONFIG = m_CM -> Get_CYL_SQ_CONFIG(); // target Y position



    G4double Rad0 = 80.*mm ;
    G4double Rad1 = 100.*mm ;
    G4double Rad2 = 200.*mm ;
    G4double Rad3 = 220.*mm ;




//  auto ts   = new G4Box("solid", 20.*mm , 20.*mm , 20.*mm );
//  auto inBox   = new G4Box("solid", 15.*mm , 15.*mm , 21.*mm );
// G4VSolid* subtract = new G4SubtractionSolid("Box-Cylinder", ts, inBox,0, G4ThreeVector(0,0.,0.));
//  logicDet_A0 = new G4LogicalVolume(subtract, m_CMOS_DetMat, "DET_LV"); 
 
//  G4VPhysicalVolume* 	test_PV = new G4PVPlacement(0,G4ThreeVector(0,0,0.*mm), "layer13",logicDet_A0,labPV, false,0);




if (CYL_SQ_CONFIG == 0)
{


printf("Box configuration used \n");

	RAD0 = m_CM -> GetRAD0();
	RAD1 = m_CM -> GetRAD1();	
	RAD2 = m_CM -> GetRAD2();
	DET1THETA_MIN = m_CM -> GetDET1THETA_MIN();
	DET1THETA_MAX = m_CM -> GetDET1THETA_MAX();
	DET2THETA_MIN = m_CM -> GetDET2THETA_MIN();
	DET2THETA_MAX = m_CM -> GetDET2THETA_MAX();	

	DETLAY1_THICKNESS = m_CM -> GetDETLAY1_THICKNESS();
	DETLAY2_THICKNESS = m_CM -> GetDETLAY2_THICKNESS();
	DETLAY3_THICKNESS = m_CM -> GetDETLAY3_THICKNESS();



   G4double detA0len = RAD0* (tan(PI*(90-DET2THETA_MIN)/180) - tan(PI*(90-DET2THETA_MAX)/180))*mm;
   G4double detA0pos = RAD0* (tan(PI*(90-DET2THETA_MIN)/180) + tan(PI*(90-DET2THETA_MAX)/180))*0.5*mm;


   G4double detA1len = RAD1* (tan(PI*(90-DET2THETA_MIN)/180) - tan(PI*(90-DET2THETA_MAX)/180))*mm;
   G4double detA1pos = RAD1* (tan(PI*(90-DET2THETA_MIN)/180) + tan(PI*(90-DET2THETA_MAX)/180))*0.5*mm;


   G4double detA2len = RAD2* (tan(PI*(90-DET2THETA_MIN)/180) - tan(PI*(90-DET2THETA_MAX)/180))*mm;
   G4double detA2pos = RAD2* (tan(PI*(90-DET2THETA_MIN)/180) + tan(PI*(90-DET2THETA_MAX)/180))*0.5*mm;





   G4double detB0len = RAD0* (tan(PI*(90-DET1THETA_MIN)/180) - tan(PI*(90-DET1THETA_MAX)/180))*mm;
   G4double detB0pos = RAD0* (tan(PI*(90-DET1THETA_MIN)/180) + tan(PI*(90-DET1THETA_MAX)/180))*0.5*mm;


   G4double detB1len = RAD1* (tan(PI*(90-DET1THETA_MIN)/180) - tan(PI*(90-DET1THETA_MAX)/180))*mm;
   G4double detB1pos = RAD1* (tan(PI*(90-DET1THETA_MIN)/180) + tan(PI*(90-DET1THETA_MAX)/180))*0.5*mm;


   G4double detB2len = RAD2* (tan(PI*(90-DET1THETA_MIN)/180) - tan(PI*(90-DET1THETA_MAX)/180))*mm;
   G4double detB2pos = RAD2* (tan(PI*(90-DET1THETA_MIN)/180) + tan(PI*(90-DET1THETA_MAX)/180))*0.5*mm;



   G4double layer1thick = DETLAY1_THICKNESS*um;
   G4double layer2thick = DETLAY2_THICKNESS*um;
   G4double layer3thick = DETLAY3_THICKNESS*um;


    auto A0_UD_Solid   = new G4Box("B0_solid", RAD0 , layer1thick/2 , detA0len/2 );
	logicDet_A0_UD = new G4LogicalVolume(A0_UD_Solid, m_CMOS_DetMat, "lV");
    new G4PVPlacement(0, G4ThreeVector(0,  RAD0+ (layer1thick/2)   , detA0pos), "A0_UD_PV", logicDet_A0_UD, labPV, false, 0);	
    new G4PVPlacement(0, G4ThreeVector(0,  -(RAD0+ (layer1thick/2))   , detA0pos), "A0_UD_PV", logicDet_A0_UD, labPV, false, 0);


    auto A0_LR_Solid   = new G4Box("B0_solid", layer1thick/2 , RAD0 ,  detA0len/2 );
	logicDet_A0_LR = new G4LogicalVolume(A0_LR_Solid, m_CMOS_DetMat, "lV");
    new G4PVPlacement(0, G4ThreeVector( RAD0+ (layer1thick/2)   , 0, detA0pos), "A0_LR_PV", logicDet_A0_LR, labPV, false, 0);	
    new G4PVPlacement(0, G4ThreeVector( -(RAD0+ (layer1thick/2))   , 0, detA0pos), "A0_LR_PV", logicDet_A0_LR, labPV, false, 0);


    auto A1_UD_Solid   = new G4Box("A1_solid", RAD1 , layer1thick/2 , detA1len/2 );
	logicDet_A1_UD = new G4LogicalVolume(A1_UD_Solid, m_CMOS_DetMat, "lV");
    new G4PVPlacement(0, G4ThreeVector(0,  RAD1+ (layer1thick/2)   , detA1pos), "A1_UD_PV", logicDet_A1_UD, labPV, false, 0);	
    new G4PVPlacement(0, G4ThreeVector(0,  -(RAD1+ (layer1thick/2))   , detA1pos), "A1_UD_PV", logicDet_A1_UD, labPV, false, 0);


    auto A1_LR_Solid   = new G4Box("A1_solid", layer1thick/2 , RAD1 ,  detA1len/2 );
	logicDet_A1_LR = new G4LogicalVolume(A1_LR_Solid, m_CMOS_DetMat, "lV");
    new G4PVPlacement(0, G4ThreeVector( RAD1+ (layer1thick/2)   , 0, detA1pos), "A1_LR_PV", logicDet_A1_LR, labPV, false, 0);	
    new G4PVPlacement(0, G4ThreeVector( -(RAD1+ (layer1thick/2))   , 0, detA1pos), "A1_LR_PV", logicDet_A1_LR, labPV, false, 0);



    auto A2_UD_Solid   = new G4Box("A2_solid", RAD2 , layer1thick/2 , detA2len/2 );
	logicDet_A2_UD = new G4LogicalVolume(A2_UD_Solid, m_CMOS_DetMat, "lV");
    new G4PVPlacement(0, G4ThreeVector(0,  RAD2+ (layer1thick/2)   , detA2pos), "A2_UD_PV", logicDet_A2_UD, labPV, false, 0);	
    new G4PVPlacement(0, G4ThreeVector(0,  -(RAD2+ (layer1thick/2))   , detA2pos), "A2_UD_PV", logicDet_A2_UD, labPV, false, 0);


    auto A2_LR_Solid   = new G4Box("A2_solid", layer1thick/2 , RAD2 ,  detA2len/2 );
	logicDet_A2_LR = new G4LogicalVolume(A2_LR_Solid, m_CMOS_DetMat, "lV");
    new G4PVPlacement(0, G4ThreeVector( RAD2+ (layer1thick/2)   , 0, detA2pos), "A2_LR_PV", logicDet_A2_LR, labPV, false, 0);	
    new G4PVPlacement(0, G4ThreeVector( -(RAD2+ (layer1thick/2))   , 0, detA2pos), "A2_LR_PV", logicDet_A2_LR, labPV, false, 0);









    auto B0_UD_Solid   = new G4Box("B0_solid", RAD0 , layer1thick/2 , detB0len/2 );
	logicDet_B0_UD = new G4LogicalVolume(B0_UD_Solid, m_CMOS_DetMat, "lV");
    new G4PVPlacement(0, G4ThreeVector(0,  RAD0+ (layer1thick/2)   , detB0pos), "B0_UD_PV", logicDet_B0_UD, labPV, false, 0);	
    new G4PVPlacement(0, G4ThreeVector(0,  -(RAD0+ (layer1thick/2))   , detB0pos), "B0_UD_PV", logicDet_B0_UD, labPV, false, 0);


    auto B0_LR_Solid   = new G4Box("B0_solid", layer1thick/2 , RAD0 ,  detB0len/2 );
	logicDet_B0_LR = new G4LogicalVolume(B0_LR_Solid, m_CMOS_DetMat, "lV");
    new G4PVPlacement(0, G4ThreeVector( RAD0+ (layer1thick/2)   , 0, detB0pos), "B0_LR_PV", logicDet_B0_LR, labPV, false, 0);	
    new G4PVPlacement(0, G4ThreeVector( -(RAD0+ (layer1thick/2))   , 0, detB0pos), "B0_LR_PV", logicDet_B0_LR, labPV, false, 0);


    auto B1_UD_Solid   = new G4Box("B1_solid", RAD1 , layer1thick/2 , detB1len/2 );
	logicDet_B1_UD = new G4LogicalVolume(B1_UD_Solid, m_CMOS_DetMat, "lV");
    new G4PVPlacement(0, G4ThreeVector(0,  RAD1+ (layer1thick/2)   , detB1pos), "B1_UD_PV", logicDet_B1_UD, labPV, false, 0);	
    new G4PVPlacement(0, G4ThreeVector(0,  -(RAD1+ (layer1thick/2))   , detB1pos), "B1_UD_PV", logicDet_B1_UD, labPV, false, 0);


    auto B1_LR_Solid   = new G4Box("B1_solid", layer1thick/2 , RAD1 ,  detB1len/2 );
	logicDet_B1_LR = new G4LogicalVolume(B1_LR_Solid, m_CMOS_DetMat, "lV");
    new G4PVPlacement(0, G4ThreeVector( RAD1+ (layer1thick/2)   , 0, detB1pos), "B1_LR_PV", logicDet_B1_LR, labPV, false, 0);	
    new G4PVPlacement(0, G4ThreeVector( -(RAD1+ (layer1thick/2))   , 0, detB1pos), "B1_LR_PV", logicDet_B1_LR, labPV, false, 0);



    auto B2_UD_Solid   = new G4Box("B2_solid", RAD2 , layer1thick/2 , detB2len/2 );
	logicDet_B2_UD = new G4LogicalVolume(B2_UD_Solid, m_CMOS_DetMat, "lV");
    new G4PVPlacement(0, G4ThreeVector(0,  RAD2+ (layer1thick/2)   , detB2pos), "B2_UD_PV", logicDet_B2_UD, labPV, false, 0);	
    new G4PVPlacement(0, G4ThreeVector(0,  -(RAD2+ (layer1thick/2))   , detB2pos), "B2_UD_PV", logicDet_B2_UD, labPV, false, 0);


    auto B2_LR_Solid   = new G4Box("B2_solid", layer1thick/2 , RAD2 ,  detB2len/2 );
	logicDet_B2_LR = new G4LogicalVolume(B2_LR_Solid, m_CMOS_DetMat, "lV");
    new G4PVPlacement(0, G4ThreeVector( RAD2+ (layer1thick/2)   , 0, detB2pos), "B2_LR_PV", logicDet_B2_LR, labPV, false, 0);	
    new G4PVPlacement(0, G4ThreeVector( -(RAD2+ (layer1thick/2))   , 0, detB2pos), "B2_LR_PV", logicDet_B2_LR, labPV, false, 0);








}
else{





    auto A0_Solid   = new G4Box("A0_solid", 50.*um , 20.*mm , 20.*mm );
    auto B0_Solid   = new G4Box("B0_solid", 50.*um , 20.*mm , 40.*mm );

    auto A1_Solid   = new G4Box("A1_solid", 50.*um , 20.*mm , 20.*mm );
    auto B1_Solid   = new G4Box("B1_solid", 50.*um , 20.*mm , 60.*mm );

    auto A2_Solid   = new G4Box("A2_solid", 50.*um , 20.*mm , 40.*mm );
    auto B2_Solid   = new G4Box("B2_solid", 50.*um , 20.*mm , 100.*mm );





   logicDet_A0 = new G4LogicalVolume(A0_Solid, m_CMOS_DetMat, "DET_LV"); 
   logicDet_A1 = new G4LogicalVolume(A1_Solid, m_CMOS_DetMat, "DET_LV"); 
   logicDet_A2 = new G4LogicalVolume(A2_Solid, m_CMOS_DetMat, "DET_LV"); 

   logicDet_B0 = new G4LogicalVolume(B0_Solid, m_CMOS_DetMat, "DET_LV"); 
   logicDet_B1 = new G4LogicalVolume(B1_Solid, m_CMOS_DetMat, "DET_LV"); 
   logicDet_B2 = new G4LogicalVolume(B2_Solid, m_CMOS_DetMat, "DET_LV"); 



    G4LogicalVolume* logicPCB_A0 = new G4LogicalVolume(A0_Solid, m_PCBMat, "PCB_LV");  
    G4LogicalVolume* logicPCB_A1 = new G4LogicalVolume(A1_Solid, m_PCBMat, "PCB_LV");
    G4LogicalVolume* logicPCB_A2 = new G4LogicalVolume(A2_Solid, m_PCBMat, "PCB_LV");
    G4LogicalVolume* logicPCB_B0 = new G4LogicalVolume(B0_Solid, m_PCBMat, "PCB_LV");
    G4LogicalVolume* logicPCB_B1 = new G4LogicalVolume(B1_Solid, m_PCBMat, "PCB_LV");
    G4LogicalVolume* logicPCB_B2 = new G4LogicalVolume(B2_Solid, m_PCBMat, "PCB_LV");	


  G4LogicalVolume* logicCu_A0 = new G4LogicalVolume(A0_Solid, m_CoaMat, "CopperCoating_LV");
  G4LogicalVolume* logicCu_A1 = new G4LogicalVolume(A1_Solid, m_CoaMat, "CopperCoating_LV");
  G4LogicalVolume* logicCu_A2 = new G4LogicalVolume(A2_Solid, m_CoaMat, "CopperCoating_LV");
  G4LogicalVolume* logicCu_B0 = new G4LogicalVolume(B0_Solid, m_CoaMat, "CopperCoating_LV");
  G4LogicalVolume* logicCu_B1 = new G4LogicalVolume(B1_Solid, m_CoaMat, "CopperCoating_LV");
  G4LogicalVolume* logicCu_B2 = new G4LogicalVolume(B2_Solid, m_CoaMat, "CopperCoating_LV");


  G4LogicalVolume* logicStructure_A0 = new G4LogicalVolume(A0_Solid, m_PipMat, "steelCooling_LV");
  G4LogicalVolume* logicStructure_A1 = new G4LogicalVolume(A1_Solid, m_PipMat, "steelCooling_LV");
  G4LogicalVolume* logicStructure_A2 = new G4LogicalVolume(A2_Solid, m_PipMat, "steelCooling_LV");
  G4LogicalVolume* logicStructure_B0 = new G4LogicalVolume(B0_Solid, m_PipMat, "steelCooling_LV");
  G4LogicalVolume* logicStructure_B1 = new G4LogicalVolume(B1_Solid, m_PipMat, "steelCooling_LV");
  G4LogicalVolume* logicStructure_B2 = new G4LogicalVolume(B2_Solid, m_PipMat, "steelCooling_LV");


   //logicDet3 = new G4LogicalVolume(Si_Solid, m_CMOS_DetMat, "DET_LV");


    G4RotationMatrix rotShingle  = G4RotationMatrix();
    rotShingle.rotateZ(10.*deg);
	//G4ThreeVector detInMod_position = G4ThreeVector(0,0,0);	

    G4Transform3D shingleTransform_det = G4Transform3D(rotShingle,G4ThreeVector(0,0,0));
    G4Transform3D shingleTransform_Cu = G4Transform3D(rotShingle,G4ThreeVector(100.*um,0,0));
    G4Transform3D shingleTransform_PCB = G4Transform3D(rotShingle,G4ThreeVector(200.*um,0,0));
    G4Transform3D shingleTransform_struct = G4Transform3D(rotShingle,G4ThreeVector(300.*um,0,0));



G4Box* solidModule = new  G4Box("solidBox", 20.*mm , 20.*mm , 20.*mm );



G4LogicalVolume* logicModuleA0 =  new G4LogicalVolume(solidModule, m_VacMat, "Ring"); 
new G4PVPlacement(shingleTransform_det, logicDet_A0, "module", logicModuleA0, false, 0, 0);
new G4PVPlacement(shingleTransform_Cu, logicCu_A0, "module", logicModuleA0, false, 0, 0);
new G4PVPlacement(shingleTransform_PCB, logicPCB_A0, "module", logicModuleA0, false, 0, 0);
new G4PVPlacement(shingleTransform_struct, logicStructure_A0, "module", logicModuleA0, false, 0, 0);


G4LogicalVolume* logicModuleA1 =  new G4LogicalVolume(solidModule, m_VacMat, "Ring"); 
new G4PVPlacement(shingleTransform_det, logicDet_A1, "module", logicModuleA1, false, 0, 0);
new G4PVPlacement(shingleTransform_Cu, logicCu_A1, "module", logicModuleA1, false, 0, 0);
new G4PVPlacement(shingleTransform_PCB, logicPCB_A1, "module", logicModuleA1, false, 0, 0);
new G4PVPlacement(shingleTransform_struct, logicStructure_A1, "module", logicModuleA1, false, 0, 0);


G4LogicalVolume* logicModuleA2 =  new G4LogicalVolume(solidModule, m_VacMat, "Ring"); 
new G4PVPlacement(shingleTransform_det, logicDet_A2, "module", logicModuleA2, false, 0, 0);
new G4PVPlacement(shingleTransform_Cu, logicCu_A2, "module", logicModuleA2, false, 0, 0);
new G4PVPlacement(shingleTransform_PCB, logicPCB_A2, "module", logicModuleA2, false, 0, 0);
new G4PVPlacement(shingleTransform_struct, logicStructure_A2, "module", logicModuleA2, false, 0, 0);


G4LogicalVolume* logicModuleB0 =  new G4LogicalVolume(solidModule, m_VacMat, "Ring"); 
new G4PVPlacement(shingleTransform_det, logicDet_B0, "module", logicModuleB0, false, 0, 0);
new G4PVPlacement(shingleTransform_Cu, logicCu_B0, "module", logicModuleB0, false, 0, 0);
new G4PVPlacement(shingleTransform_PCB, logicPCB_B0, "module", logicModuleB0, false, 0, 0);
new G4PVPlacement(shingleTransform_struct, logicStructure_B0, "module", logicModuleB0, false, 0, 0);


G4LogicalVolume* logicModuleB1 =  new G4LogicalVolume(solidModule, m_VacMat, "Ring"); 
new G4PVPlacement(shingleTransform_det, logicDet_B1, "module", logicModuleB1, false, 0, 0);
new G4PVPlacement(shingleTransform_Cu, logicCu_B1, "module", logicModuleB1, false, 0, 0);
new G4PVPlacement(shingleTransform_PCB, logicPCB_B1, "module", logicModuleB1, false, 0, 0);
new G4PVPlacement(shingleTransform_struct, logicStructure_B1, "module", logicModuleB1, false, 0, 0);


G4LogicalVolume* logicModuleB2 =  new G4LogicalVolume(solidModule, m_VacMat, "Ring"); 
new G4PVPlacement(shingleTransform_det, logicDet_B2, "module", logicModuleB2, false, 0, 0);
new G4PVPlacement(shingleTransform_Cu, logicCu_B2, "module", logicModuleB2, false, 0, 0);
new G4PVPlacement(shingleTransform_PCB, logicPCB_B2, "module", logicModuleB2, false, 0, 0);
new G4PVPlacement(shingleTransform_struct, logicStructure_B2, "module", logicModuleB2, false, 0, 0);

















// G4LogicalVolume* logicModule1 =  new G4LogicalVolume(solidModule, m_VacMat, "Ring"); 
// new G4PVPlacement(shingleTransform_det, logicDet0, "module", logicModule1, false, 0, 0);
// new G4PVPlacement(shingleTransform_Cu, logicCu, "module", logicModule1, false, 0, 0);
// new G4PVPlacement(shingleTransform_PCB, logicPCB, "module", logicModule1, false, 0, 0);
// new G4PVPlacement(shingleTransform_struct, logicDet0, "module", logicModule1, false, 0, 0);





// G4LogicalVolume* logicModule2 =  new G4LogicalVolume(solidModule, m_VacMat, "Ring"); 
// new G4PVPlacement(shingleTransform_det, logicDet0, "module", logicModule2, false, 0, 0);
// new G4PVPlacement(shingleTransform_Cu, logicCu, "module", logicModule2, false, 0, 0);
// new G4PVPlacement(shingleTransform_PCB, logicPCB, "module", logicModule2, false, 0, 0);
// new G4PVPlacement(shingleTransform_struct, logicDet0, "module", logicModule2, false, 0, 0);




// G4LogicalVolume* logicModule3 =  new G4LogicalVolume(solidModule, m_VacMat, "Ring"); 
// new G4PVPlacement(shingleTransform_det, logicDet0, "module", logicModule3, false, 0, 0);
// new G4PVPlacement(shingleTransform_Cu, logicCu, "module", logicModule3, false, 0, 0);
// new G4PVPlacement(shingleTransform_PCB, logicPCB, "module", logicModule3, false, 0, 0);
// new G4PVPlacement(shingleTransform_struct, logicDet0, "module", logicModule3, false, 0, 0);













    //G4RotationMatrix rotm  = G4RotationMatrix();



G4Tubs* solidRing0 = new G4Tubs("Ring", Rad0, Rad0 + 1.*mm, 500.*mm, 0., 360.*deg);
G4LogicalVolume* logicRing0 =  new G4LogicalVolume(solidRing0, m_VacMat, "Ring"); 

  for (G4int icrys = 0; icrys < 18 ; icrys++) {
    G4double phi = icrys*20.*deg;	
    G4RotationMatrix rotm  = G4RotationMatrix();
    rotm.rotateZ(phi);

    G4ThreeVector A0z = G4ThreeVector(Rad0*std::cos(phi),  Rad0*std::sin(phi),55.*mm);     	
    G4Transform3D transform_A0 = G4Transform3D(rotm,A0z);
    new G4PVPlacement(transform_A0, logicModuleA0, "Silicon inner ring position A", logicRing0, false, icrys, 0);


    G4ThreeVector B0z = G4ThreeVector(Rad0*std::cos(phi),  Rad0*std::sin(phi),135.*mm);     	
    G4Transform3D transform_B0 = G4Transform3D(rotm,B0z);
    new G4PVPlacement(transform_B0, logicModuleB0, "Silicon inner ring position A", logicRing0, false, icrys, 0);


  }

  	G4VPhysicalVolume* 	ring0_PV = new G4PVPlacement(0,G4ThreeVector(0,0,0.*mm), "layer13",logicRing0,labPV, false,0);











G4Tubs* solidRing1 = new G4Tubs("Ring", Rad1, Rad1+1.*mm, 500.*mm, 0., 360.*deg);
G4LogicalVolume* logicRing1 =  new G4LogicalVolume(solidRing1, m_VacMat, "Ring"); 



  for (G4int icrys = 0; icrys < 18 ; icrys++) {
    G4double phi = icrys*20.*deg;	
    G4RotationMatrix rotm  = G4RotationMatrix();
    rotm.rotateZ(phi);

    G4ThreeVector A1z = G4ThreeVector(Rad1*std::cos(phi),  Rad1*std::sin(phi),70.*mm);     	
    G4Transform3D transform_A1 = G4Transform3D(rotm,A1z);
    new G4PVPlacement(transform_A1, logicModuleA1, "Silicon middle ring position A", logicRing1, false, icrys, 0);


    G4ThreeVector B1z = G4ThreeVector(Rad1*std::cos(phi),  Rad1*std::sin(phi),165.*mm);     	
    G4Transform3D transform_B1 = G4Transform3D(rotm,B1z);
    new G4PVPlacement(transform_B1, logicModuleB1, "Silicon middle ring position B", logicRing1, false, icrys, 0);


  }

G4VPhysicalVolume* 	ring1_PV = new G4PVPlacement(0,G4ThreeVector(0,0,0.*mm), "layer13",logicRing1,labPV, false,0);











G4Tubs* solidRing2 = new G4Tubs("Ring", Rad2, Rad2 + 1.*mm, 1000.*mm, 0., 360.*deg);
G4LogicalVolume* logicRing2 =  new G4LogicalVolume(solidRing2, m_VacMat, "Ring"); 


  for (G4int icrys = 0; icrys < 36 ; icrys++) {
    G4double phi = icrys*10.*deg;	
    G4RotationMatrix rotm  = G4RotationMatrix();
    rotm.rotateZ(phi);

   G4ThreeVector A2z = G4ThreeVector(Rad2*std::cos(phi),  Rad2*std::sin(phi),145.*mm);     	
   G4Transform3D transform_A2 = G4Transform3D(rotm,A2z);
   new G4PVPlacement(transform_A2, logicModuleA2, "Silicon outer ring position A", logicRing2, false, icrys, 0);


   G4ThreeVector B2z = G4ThreeVector(Rad2*std::cos(phi),  Rad2*std::sin(phi),325.*mm);     	
   G4Transform3D transform_B2 = G4Transform3D(rotm,B2z);
   new G4PVPlacement(transform_B2, logicModuleB2, "Silicon outer ring position B", logicRing2, false, icrys, 0);


  }


G4VPhysicalVolume* 	ring2_PV = new G4PVPlacement(0,G4ThreeVector(0,0,0.*mm), "layer13",logicRing2,labPV, false,0);






// Possible extra layer

G4Tubs* solidRing3 = new G4Tubs("Ring", 220.*mm, 221.*mm, 500.*mm, 0., 360.*deg);
G4LogicalVolume* logicRing3 =  new G4LogicalVolume(solidRing3, m_VacMat, "Ring"); 
//G4VPhysicalVolume* 	ring3_PV = new G4PVPlacement(0,G4ThreeVector(0,0,655.*mm), "layer13",logicRing0,labPV, false,0);















  logicRing0->SetVisAttributes (G4VisAttributes::GetInvisible());
  logicRing1->SetVisAttributes (G4VisAttributes::GetInvisible());
  logicRing2->SetVisAttributes (G4VisAttributes::GetInvisible()); 
  logicRing3->SetVisAttributes (G4VisAttributes::GetInvisible());
  logicModuleA0->SetVisAttributes (G4VisAttributes::GetInvisible());    
  logicModuleA1->SetVisAttributes (G4VisAttributes::GetInvisible()); 
  logicModuleA2->SetVisAttributes (G4VisAttributes::GetInvisible()); 
  logicModuleB0->SetVisAttributes (G4VisAttributes::GetInvisible());    
  logicModuleB1->SetVisAttributes (G4VisAttributes::GetInvisible()); 
  logicModuleB2->SetVisAttributes (G4VisAttributes::GetInvisible()); 

}
  //logicModule3->SetVisAttributes (G4VisAttributes::GetInvisible()); 



	return labPV;
}

void JePoDetCon::ConstructSDandField()
{


  // sensitive detectors -----------------------------------------------------
  auto sdManager = G4SDManager::GetSDMpointer();
  G4String SDname;


  auto HVCMOS = new LGAD_SD(SDname="/HVCMOS");
  sdManager->AddNewDetector(HVCMOS);
  logicDet_A0_LR->SetSensitiveDetector(HVCMOS);
  logicDet_A0_UD->SetSensitiveDetector(HVCMOS);  
  logicDet_B0_LR->SetSensitiveDetector(HVCMOS); 
  logicDet_B0_UD->SetSensitiveDetector(HVCMOS); 


  auto hodoscope1 = new LGAD_SD(SDname="/hodoscope1");
  sdManager->AddNewDetector(hodoscope1);
  //logicDet_A1->SetSensitiveDetector(hodoscope1);
  //logicDet_B1->SetSensitiveDetector(hodoscope1);  
  logicDet_A1_LR->SetSensitiveDetector(hodoscope1);
  logicDet_A1_UD->SetSensitiveDetector(hodoscope1);  
  logicDet_B1_LR->SetSensitiveDetector(hodoscope1); 
  logicDet_B1_UD->SetSensitiveDetector(hodoscope1); 


  auto hodoscope2 = new LGAD_SD(SDname="/hodoscope2");
  sdManager->AddNewDetector(hodoscope2);
  //logicDet_A2->SetSensitiveDetector(hodoscope2);
  //logicDet_B2->SetSensitiveDetector(hodoscope2);
  logicDet_A2_LR->SetSensitiveDetector(hodoscope2);
  logicDet_A2_UD->SetSensitiveDetector(hodoscope2);  
  logicDet_B2_LR->SetSensitiveDetector(hodoscope2); 
  logicDet_B2_UD->SetSensitiveDetector(hodoscope2); 







  auto HVCMOS_dep = new EmCalorimeterSD(SDname="/HVCMOS_dep");
  sdManager->AddNewDetector(HVCMOS_dep);
  //logicDet_A0->SetSensitiveDetector(HVCMOS_dep);

  auto hodoscope1_dep = new EmCalorimeterSD(SDname="/hodoscope1_dep");
  sdManager->AddNewDetector(hodoscope1_dep);
  //logicDet_A0->SetSensitiveDetector(hodoscope1_dep);

  auto hodoscope2_dep = new EmCalorimeterSD(SDname="/hodoscope2_dep");
  sdManager->AddNewDetector(hodoscope2_dep);
  //logicDet_A0->SetSensitiveDetector(hodoscope2_dep);




      G4String fltName,particleName;
/*
 G4SDParticleFilter* protonFilter = 
      new G4SDParticleFilter(fltName="protonFilter", particleName="proton");
	  //protonFilter  -> add("e-");



	  

  hodoscope1->SetFilter(protonFilter);
  hodoscope2->SetFilter(protonFilter);
  hodoscope1_dep->SetFilter(protonFilter);
  hodoscope2_dep->SetFilter(protonFilter);
  HVCMOS->SetFilter(protonFilter);
  HVCMOS_dep->SetFilter(protonFilter);
*/


/*
G4SDParticleFilter* photonFilter = 
      new G4SDParticleFilter(fltName="photonFilter", particleName="gamma");	  
   hodoscope1->SetFilter(photonFilter);
  hodoscope2->SetFilter(photonFilter);
  hodoscope1_dep->SetFilter(photonFilter);
  hodoscope2_dep->SetFilter(photonFilter);
  HVCMOS->SetFilter(photonFilter);
  HVCMOS_dep->SetFilter(photonFilter);
*/
/*
 G4SDParticleFilter* backgroundFilter = 
      new G4SDParticleFilter(fltName="photonFilter", particleName="e-");	 
		backgroundFilter  -> add("e+");
		backgroundFilter  -> add("gamma");
		backgroundFilter  -> add("neutron");
   hodoscope1->SetFilter(backgroundFilter);
  hodoscope2->SetFilter(backgroundFilter);
  hodoscope1_dep->SetFilter(backgroundFilter);
  hodoscope2_dep->SetFilter(backgroundFilter);
  HVCMOS->SetFilter(backgroundFilter);
  HVCMOS_dep->SetFilter(backgroundFilter);
*/




}    

void JePoDetCon::ConstructMaterials()
{
	const G4double labTemp = 300.0 * kelvin;
	// Elements to be used to construct materials
	m_ElH  = new G4Element( "Hydrogen",  "H",  1,   1.00794*g/mole);
	m_ElC  = new G4Element(   "Carbon",  "C",  6,  12.011  *g/mole);
	m_ElN  = new G4Element( "Nitrogen",  "N",  7,  14.00674*g/mole);
	m_ElO  = new G4Element(   "Oxygen",  "O",  8,  15.9994 *g/mole);
	m_ElF  = new G4Element( "Fluorine",  "F",  9,  18.9984 *g/mole);
	m_ElMg = new G4Element("Magnesium", "Mg", 12,  24.3050 *g/mole);
	m_ElAl = new G4Element( "Aluminum", "Al", 13,  26.98154*g/mole);
	m_ElSi = new G4Element(  "Silicon", "Si", 14,  28.0855 *g/mole);
	m_ElAr = new G4Element(    "Argon", "Ar", 18,  39.948  *g/mole);
	m_ElCr = new G4Element("Chromuium", "Cr", 24,  51.9961 *g/mole);
	m_ElFe = new G4Element(     "Iron", "Fe", 26,  55.845  *g/mole);
	m_ElNi = new G4Element(   "Nickel", "Ni", 28,  58.9634 *g/mole);
	m_ElCu = new G4Element(   "Copper", "Cu", 29,  63.546  *g/mole);
	m_ElZn = new G4Element(     "Zinc", "Zn", 30,  65.38   *g/mole);
	m_ElY  = new G4Element(  "Yttrium",  "Y", 39,  88.90585*g/mole);
	m_ElSn = new G4Element(      "Tin", "Sn", 50, 118.71   *g/mole);
	m_ElCe = new G4Element(   "Cerium", "Ce", 58, 140.116  *g/mole);
	m_ElLu = new G4Element( "Lutetium", "Lu", 71, 176.944  *g/mole);

	// Air material
	m_AirMat = new G4Material("Air", 1.1839e-3*g/cm3, 3, kStateGas, labTemp); // Density at 1 atm
	m_AirMat -> AddElement(m_ElN, 75.47/99.95);
	m_AirMat -> AddElement(m_ElO, 23.20/99.95);
	m_AirMat -> AddElement(m_ElAr, 1.28/99.95);

	// Target material
	G4String targetMaterial = m_CM -> GetTarMat();
	if ( targetMaterial == "C" )
	{
		m_TarMat = new G4Material("Graphite", 1.7*g/cm3, 3, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElC, 99.0/100.0);
		m_TarMat -> AddElement(m_ElN,  0.7/100.0);
		m_TarMat -> AddElement(m_ElO,  0.3/100.0);
	}
	else if ( targetMaterial == "Mg" )
	{
		m_TarMat = new G4Material("Magnesium", 1.738*g/cm3, 1, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElMg, 1.0);
	}
	else if ( targetMaterial == "Al" )
	{
		m_TarMat = new G4Material("Aluminum", 2.70*g/cm3, 1, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElAl, 1.0);
	}
	else if ( targetMaterial == "Sn" )
	{
		m_TarMat = new G4Material("Tin", 5.769*g/cm3, 1, kStateSolid, labTemp); // Gray tin?
		m_TarMat -> AddElement(m_ElSn, 1.0);
	}
	else if ( targetMaterial == "Si" )
	{
		m_TarMat = new G4Material("Silicon", 2.329*g/cm3, 1, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElSi, 1.0);
	}
	else if ( targetMaterial == "Ni" )
	{
		m_TarMat = new G4Material("Nickel", 8.908*g/cm3, 1, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElNi, 1.0);
	}
	else if ( targetMaterial == "Zn" )
	{
		m_TarMat = new G4Material("Zinc", 7.14*g/cm3, 1, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElZn, 1.0);
	}
	else if ( targetMaterial == "CH2" )
	{
		m_TarMat = new G4Material("Polyethelene", 0.92*g/cm3, 2, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElC, 1);
		m_TarMat -> AddElement(m_ElH, 2);
	}
	else
	{
		std::stringstream message;
		message << "Could not find target material with name " << targetMaterial;
		G4Exception("JePoDetCon::ConstructMaterials()", "", FatalException, message.str().c_str());
	}

    // Silicon Material
		m_SiMat = new G4Material("Silicon", 2.329*g/cm3, 1, kStateSolid, labTemp);
		m_SiMat -> AddElement(m_ElSi, 1.0);


        m_CMOS_DetMat = new G4Material("Det Silicon", 2.329*g/cm3, 1, kStateSolid, labTemp);
        m_CMOS_DetMat -> AddElement(m_ElSi, 1.0);

/*
		m_CMOS_DetMat = new G4Material("DetVacumm", 1.1839e-10*g/cm3, 3, kStateGas, labTemp);
		m_CMOS_DetMat -> AddElement(m_ElN, 75.47/99.95);
		m_CMOS_DetMat -> AddElement(m_ElO, 23.20/99.95);
		m_CMOS_DetMat -> AddElement(m_ElAr, 1.28/99.95);
*/



	// Crystal scintillator material
	m_DetMat = new G4Material("LYSO", 7.1*g/cm3, 5, kStateSolid, labTemp);
	m_DetMat -> AddElement(m_ElLu, 71.43/100.0);
	m_DetMat -> AddElement(m_ElY,   4.03/100.0);
	m_DetMat -> AddElement(m_ElSi,  6.37/100.0);
	m_DetMat -> AddElement(m_ElO,  18.14/100.0);
	m_DetMat -> AddElement(m_ElCe,  0.02/100.0);

	// Plastic scintillator material
	m_CouMat = new G4Material("PlasticScint", 1.032*g/cm3, 2, kStateSolid, labTemp);
	m_CouMat -> AddElement(m_ElC, 10);
	m_CouMat -> AddElement(m_ElH, 11);

	// Pipe material
	m_PipMat = new G4Material("StainlessSteel", 8.03*g/cm3, 3, kStateSolid, labTemp);
	m_PipMat -> AddElement(m_ElFe, 70.0/100.0);
	m_PipMat -> AddElement(m_ElCr, 20.0/100.0);
	m_PipMat -> AddElement(m_ElNi, 10.0/100.0);

	// Vacuum material
	m_VacMat = new G4Material("Vacumm", 1.1839e-10*g/cm3, 3, kStateGas, labTemp);
	m_VacMat -> AddElement(m_ElN, 75.47/99.95);
	m_VacMat -> AddElement(m_ElO, 23.20/99.95);
	m_VacMat -> AddElement(m_ElAr, 1.28/99.95);

	// Teflon material
	m_TefMat = new G4Material("Teflon", 2.2*g/cm3, 2, kStateSolid, labTemp);
	m_TefMat -> AddElement(m_ElC, 1);
	m_TefMat -> AddElement(m_ElF, 2);

	// Tedlar material
	m_TedMat = new G4Material("Tedlar", 1.545*g/cm3, 3, kStateSolid, labTemp);
	m_TedMat -> AddElement(m_ElC, 2);
	m_TedMat -> AddElement(m_ElH, 3);
	m_TedMat -> AddElement(m_ElF, 1);

	// Kapton mateiral
	m_KapMat = new G4Material("Kapton", 1.39*g/cm3, 3, kStateSolid, labTemp);
	m_KapMat -> AddElement(m_ElC, 5);
	m_KapMat -> AddElement(m_ElO, 2);
	m_KapMat -> AddElement(m_ElH, 4);

	// Ar+CO2 gas material
	m_GasMat = new G4Material("Gas", 1.184*kg/m3, 3, kStateGas, labTemp);
	m_GasMat -> AddElement(m_ElAr, 12);
	m_GasMat -> AddElement(m_ElC,   1);
	m_GasMat -> AddElement(m_ElO,   2);

	// PCB material
	m_PCBMat = new G4Material("PCB", 2.0*g/cm3, 2, kStateSolid, labTemp);
	m_PCBMat -> AddElement(m_ElSi, 1);
	m_PCBMat -> AddElement(m_ElO,  2);

	// Copper coating material
	m_CoaMat = new G4Material("Coating", 8.96*g/cm3, 1, kStateSolid, labTemp);
	m_CoaMat -> AddElement(m_ElCu, 1);
}

void JePoDetCon::DestructMaterials()
{
	delete m_CoaMat;
	delete m_PCBMat;
	delete m_GasMat;
	delete m_KapMat;
	delete m_TedMat;
	delete m_TefMat;
	delete m_VacMat;
	delete m_PipMat;
	delete m_CouMat;
	delete m_TarMat;
	delete m_AirMat;

	delete m_ElLu;
	delete m_ElCe;
	delete m_ElSn;
	delete m_ElY;
	delete m_ElZn;
	delete m_ElCu;
	delete m_ElNi;
	delete m_ElFe;
	delete m_ElCr;
	delete m_ElAr;
	delete m_ElSi;
	delete m_ElAl;
	delete m_ElMg;
	delete m_ElF;
	delete m_ElO;
	delete m_ElN;
	delete m_ElC;
	delete m_ElH;

	delete m_CMOS_DetMat;

}


/*
USELESS
*/

/*
void JePoDetCon::ConstructSymmetricVolume(G4String name, G4int symVolID, G4double f1, G4double f2){
	// define name of symmetric volume
	symVolName[symVolID] = name + "_steel";											

	// Define configuration for a structure
	G4int num = 0;
	G4double	*zz = new G4double[1] {0};
	G4double	*Rmin = new G4double[1] {0}; 
	G4double	*Rmax = new G4double[1] {0};
	if(name == "B0"){
		num = nz0; zz = zz0; Rmin = Rmin0; Rmax = Rmax0;
	}else if(name == "B1"){
		num = nz1; zz = zz1; Rmin = Rmin1; Rmax = Rmax1;
	}else if(name == "B2"){
		num = nz2; zz = zz2; Rmin = Rmin2; Rmax = Rmax2;
	}else if(name == "B3"){
		num = nz3; zz = zz3; Rmin = Rmin3; Rmax = Rmax3;
	}else if(name == "Bv"){
		num = nzv; zz = zzv; Rmin = Rminv; Rmax = Rmaxv;
	}else if(name == "Bw"){
		num = nzw; zz = zzw; Rmin = Rminw; Rmax = Rmaxw;
	}

	// construcs symmetric volume
	symVol[symVolID] = new G4Polycone(name, f1, f2-f1, num, zz, Rmin, Rmax) ;
 	symVolLog[symVolID] = new G4LogicalVolume(symVol[symVolID], symVolMaterial, symVolName[symVolID]) ;
	symVolLog[symVolID]->SetVisAttributes(steelVis) ;

	// define the position of next simetric cristal
	if(name == "B0")
		symVolZpos[symVolID + 1] = symVolZpos[symVolID] + (zz[num - 1] - zz[0])/2;
	else if(name == "B1")
		symVolZpos[symVolID + 1] = symVolZpos[symVolID] + (zz[num - 1] - zz[0]);
	else if(name == "B2")
		symVolZpos[symVolID + 1] = symVolZpos[symVolID] + (zz[num - 1] - zz[0]);
	else if(symVolID != 5)
		symVolZpos[symVolID + 1] = symVolZpos[symVolID];
	

	// is constructed
	symVolConstructed[symVolID] = true;
}
*/
