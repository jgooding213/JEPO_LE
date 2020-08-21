////////////////////////////////////////////////////////////////////////////////
//   BT2017ConMan.cc for beamtest2017 of JEDI                                 //
//                                                                            //
//   Definitions of BT2017ConMan class's member functions                     //
//                                                                            //
//                    - 20. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "BT2017ConMan.hh"
#include "G4SystemOfUnits.hh"

//////////////////////////////////////////////////
//   Constructors and destructor                //
//////////////////////////////////////////////////
BT2017ConMan::BT2017ConMan()
{
	Init();
}


BT2017ConMan::BT2017ConMan(const char* fileName)
{
	Init(fileName);
}


BT2017ConMan::~BT2017ConMan()
{
}


//////////////////////////////////////////////////
//   Initialization function                    //
//////////////////////////////////////////////////
void BT2017ConMan::Init(const char* fileName)
{
	if ( !fileName ) SetDefault();
	else if ( !Load(fileName) ) SetDefault();
//	SetDefault();
}

void BT2017ConMan::SetDefault()
{
	// When the class fails to find configuration file, this setup is applied.

	// Computing
	m_UseMTD =        true;
	m_NofTRD =           4;
	// Physics
	m_UseJED =        true;	
	// World
	m_WorldX = 2400.0 * mm;
	m_WorldY = 2400.0 * mm;
	m_WorldZ = 2400.0 * mm;
	// Beam
	m_BeamDX =   10.0 * mm;
	m_BeamDY =   10.0 * mm;
	m_BeamKE = 270.0 * MeV;
	m_BeamAX =         0.0;
	m_BeamAY =         0.0;
	m_BeamAZ =         0.0;
	m_BeamPO =         0.0;
	m_BeamPP =   0.0 * deg;
	m_BeamAN =         0.5;
    
	// Particle
	m_SParName ="proton";
	m_BeamST =			 3;
	m_BeamLT =			22;

    // Target
	m_TarMat =         "C";
	m_TarThi =    5.0 * mm; // thickness
	m_TarXle =   20.0 * mm;
	m_TarYle =   20.0 * mm;
	m_TarPoX =	  0.0 * mm;
	m_TarPoY =    0.0 * mm;



    m_DET1THETA_MIN = 40.*deg;
    m_DET1THETA_MAX = 60.*deg;

    m_DET2THETA_MIN = 70.*deg;
    m_DET2THETA_MAX = 90.*deg;

    
	// Scintilator
	//m_SciEpx = 	  630 * mm;

    // Crystals
	//m_DetSet.assign(120, false);
	//m_DetPoX =    0.0 * mm;
	//m_DetPoY =    0.0 * mm;
	//m_DetPoZ =  690.0 * mm;
	//m_DetAng =    0.0 * deg;

    // parts of construction
	//m_UseVB0 =		  true;
	//m_UseVB1 =		  true;
	//m_UseVB2 =		  true;
	//m_UseVB3 =		  true;
	//m_UseVBV =		  true;
	//m_UseVBW =		  true;
	//JG
}


//////////////////////////////////////////////////
//   Load configuration file                    //
//////////////////////////////////////////////////
bool BT2017ConMan::Load(const char* fileName)
{
	// Open file
	std::ifstream file(fileName, std::ifstream::in);
	if ( !file.is_open() ) return false;

	// Read line by line
	std::string line;
	m_DetSet.assign(120, false);
	while ( std::getline(file, line) )
	{
		if ( StartsWith(line, "#") ) continue;

		// Read configurations: Computing
		if ( StartsWith(line, "USEMULTITHREADS") )
		{
			char hfile[1000];
			sscanf(line.data(), "USEMULTITHREADS %s", hfile);
			m_SUseMTD = hfile;
			if      ( m_SUseMTD == "ON"  ) m_UseMTD = true;
			else if ( m_SUseMTD == "OFF" ) m_UseMTD = false;
		}
		if ( StartsWith(line, "NTHREADS") )
		{
			char hfile[1000];
			sscanf(line.data(), "NTHREADS %s", hfile);
			m_SNofTRD = hfile;
			m_NofTRD = std::stoi(m_SNofTRD);
		}
		// Read configurations: events and cycles
		if ( StartsWith(line, "EVENTS") )
		{
			char hfile[1000];
			sscanf(line.data(), "EVENTS %s", hfile);
			m_SNumEve = hfile;
			m_NumEve = std::stoi(m_SNumEve);
		}
		// Read configurations: Physics
		if ( StartsWith(line, "USEJEDIPHYSICS") )
		{
			char hfile[1000];
			sscanf(line.data(), "USEJEDIPHYSICS %s", hfile);
			m_SUseJED = hfile;
			if      ( m_SUseJED == "ON"  ) m_UseJED = true;
			else if ( m_SUseJED == "OFF" ) m_UseJED = false;

		}
		// Read configurations: World
		if ( StartsWith(line, "WORLDX") )
		{
			char hfile[1000];
			sscanf(line.data(), "WORLDX %s", hfile);
			m_SWorldX = hfile;
			m_WorldX = std::stod(m_SWorldX) * mm;
		}
		if ( StartsWith(line, "WORLDY") )
		{
			char hfile[1000];
			sscanf(line.data(), "WORLDY %s", hfile);
			m_SWorldY = hfile;
			m_WorldY = std::stod(m_SWorldY) * mm;
		}
		if ( StartsWith(line, "WORLDZ") )
		{
			char hfile[1000];
			sscanf(line.data(), "WORLDZ %s", hfile);
			m_SWorldZ = hfile;
			m_WorldZ = std::stod(m_SWorldZ) * mm;
		}
		// Read configurations: Beam
		if ( StartsWith(line, "BEAMDELTAX") )
		{
			char hfile[1000];
			sscanf(line.data(), "BEAMDELTAX %s", hfile);
			m_SBeamDX = hfile;
			m_BeamDX = std::stod(m_SBeamDX) * mm;
		}
		if ( StartsWith(line, "BEAMDELTAY") )
		{
			char hfile[1000];
			sscanf(line.data(), "BEAMDELTAY %s", hfile);
			m_SBeamDY = hfile;
			m_BeamDY = std::stod(m_SBeamDY) * mm;
		}
		if ( StartsWith(line, "BEAMKINETICENERGY") )
		{
			char hfile[1000];
			sscanf(line.data(), "BEAMKINETICENERGY %s", hfile);
			m_SBeamKE = hfile;
			m_BeamKE = std::stod(m_SBeamKE) * MeV;
		}
		if ( StartsWith(line, "BEAMAXISX") )
		{
			char hfile[1000];
			sscanf(line.data(), "BEAMAXISX %s", hfile);
			m_SBeamAX = hfile;
			m_BeamAX = std::stod(m_SBeamAX);
		}
		if ( StartsWith(line, "BEAMAXISY") )
		{
			char hfile[1000];
			sscanf(line.data(), "BEAMAXISY %s", hfile);
			m_SBeamAY = hfile;
			m_BeamAY = std::stod(m_SBeamAY);
		}
		if ( StartsWith(line, "BEAMAXISZ") )
		{
			char hfile[1000];
			sscanf(line.data(), "BEAMAXISZ %s", hfile);
			m_SBeamAZ = hfile;
			m_BeamAZ = std::stod(m_SBeamAZ);
		}
		if ( StartsWith(line, "BEAMPOLARIZATION") )
		{
			char hfile[1000];
			sscanf(line.data(), "BEAMPOLARIZATION %s", hfile);
			m_SBeamPO = hfile;
			m_BeamPO = std::stod(m_SBeamPO);
		}
		if ( StartsWith(line, "BEAMPHIPOLARIZATION") )
		{
			char hfile[1000];
			sscanf(line.data(), "BEAMPHIPOLARIZATION %s", hfile);
			m_SBeamPP = hfile;
			m_BeamPP = std::stod(m_SBeamPP);
		}
		if ( StartsWith(line, "AVERAGEANALYZINGPOWER") )
		{
			char hfile[1000];
			sscanf(line.data(), "AVERAGEANALYZINGPOWER %s", hfile);
			m_SBeamAN = hfile;
			m_BeamAN = std::stod(m_SBeamAN);
		}
		// Particle
		if ( StartsWith(line, "PARTICLENAME") )
		{
			char hfile[1000];
			sscanf(line.data(), "PARTICLENAME %s", hfile);
			m_SParName = hfile;
		}
		if ( StartsWith(line, "MINTHETA") )
		{
			char hfile[1000];
			sscanf(line.data(), "MINTHETA %s", hfile);
			m_SBeamST = hfile;
			m_BeamST = std::stod(m_SBeamST);
		}
		if ( StartsWith(line, "MAXTHETA") )
		{
			char hfile[1000];
			sscanf(line.data(), "MAXTHETA %s", hfile);
			m_SBeamLT = hfile;
			m_BeamLT = std::stod(m_SBeamLT);
		}












		if ( StartsWith(line, "DET1THETA_MIN") )
		{
			char hfile[1000];
			sscanf(line.data(), "DET1THETA_MIN %s", hfile);
			m_SDET1THETA_MIN = hfile;
			m_DET1THETA_MIN = std::stod(m_SDET1THETA_MIN);
		}

		if ( StartsWith(line, "DET1THETA_MAX") )
		{
			char hfile[1000];
			sscanf(line.data(), "DET1THETA_MAX %s", hfile);
			m_SDET1THETA_MAX = hfile;
			m_DET1THETA_MAX = std::stod(m_SDET1THETA_MAX);
		}

		if ( StartsWith(line, "DET2THETA_MIN") )
		{
			char hfile[1000];
			sscanf(line.data(), "DET2THETA_MIN %s", hfile);
			m_SDET2THETA_MIN = hfile;
			m_DET2THETA_MIN = std::stod(m_SDET2THETA_MIN);
		}

		if ( StartsWith(line, "DET2THETA_MAX") )
		{
			char hfile[1000];
			sscanf(line.data(), "DET2THETA_MAX %s", hfile);
			m_SDET2THETA_MAX = hfile;
			m_DET2THETA_MAX = std::stod(m_SDET2THETA_MAX);
		}


		if ( StartsWith(line, "DETLAY1_THICKNESS") )
		{
			char hfile[1000];
			sscanf(line.data(), "DETLAY1_THICKNESS %s", hfile);
			m_SDETLAY1_THICKNESS = hfile;
			m_DETLAY1_THICKNESS = std::stod(m_SDETLAY1_THICKNESS);
		}




		if ( StartsWith(line, "DETLAY2_THICKNESS") )
		{
			char hfile[1000];
			sscanf(line.data(), "DETLAY2_THICKNESS %s", hfile);
			m_SDETLAY2_THICKNESS = hfile;
			m_DETLAY2_THICKNESS = std::stod(m_SDETLAY2_THICKNESS);
		}



		if ( StartsWith(line, "DETLAY3_THICKNESS") )
		{
			char hfile[1000];
			sscanf(line.data(), "DETLAY3_THICKNESS %s", hfile);
			m_SDETLAY3_THICKNESS = hfile;
			m_DETLAY3_THICKNESS = std::stod(m_SDETLAY3_THICKNESS);
		}


		if ( StartsWith(line, "DETLAY1_MAT") )
		{
			char hfile[1000];
			sscanf(line.data(), "DETLAY1_MAT %s", hfile);
			m_SDETLAY1_MAT = hfile;
		}

		if ( StartsWith(line, "DETLAY2_MAT") )
		{
			char hfile[1000];
			sscanf(line.data(), "DETLAY2_MAT %s", hfile);
			m_SDETLAY2_MAT = hfile;
		}


		if ( StartsWith(line, "DETLAY3_MAT") )
		{
			char hfile[1000];
			sscanf(line.data(), "DETLAY3_MAT %s", hfile);
			m_SDETLAY3_MAT = hfile;
		}



		if ( StartsWith(line, "RAD0") )
		{
			char hfile[1000];
			sscanf(line.data(), "RAD0 %s", hfile);
			m_SRAD0 = hfile;
			m_RAD0 = std::stod(m_SRAD0);
		}

		if ( StartsWith(line, "RAD1") )
		{
			char hfile[1000];
			sscanf(line.data(), "RAD1 %s", hfile);
			m_SRAD1 = hfile;
			m_RAD1 = std::stod(m_SRAD1);
		}


		if ( StartsWith(line, "RAD2") )
		{
			char hfile[1000];
			sscanf(line.data(), "RAD2 %s", hfile);
			m_SRAD2 = hfile;
			m_RAD2 = std::stod(m_SRAD2);
		}






		// Read configurations: Target
		if ( StartsWith(line, "USETARGET") )
		{
			char hfile[1000];
			sscanf(line.data(), "USETARGET %s", hfile);
			m_SUseTar = hfile;
			if      ( m_SUseTar == "ON"  ) m_UseTar = true;
			else if ( m_SUseTar == "OFF" ) m_UseTar = false;
		}
		if ( StartsWith(line, "TARGETMATERIAL") )
		{
			char hfile[1000];
			sscanf(line.data(), "TARGETMATERIAL %s", hfile);
			m_STarMat = hfile;
			m_TarMat = m_STarMat;
		}
		if ( StartsWith(line, "TARGETTHICKNESS") )
		{
			char hfile[1000];
			sscanf(line.data(), "TARGETTHICKNESS %s", hfile);
			m_STarThi = hfile;
			m_TarThi = std::stod(m_STarThi) * mm;
		}
		if ( StartsWith(line, "TARGETXLENGTH") )
		{
			char hfile[1000];
			sscanf(line.data(), "TARGETXLENGTH %s", hfile);
			m_STarXle = hfile;
			m_TarXle = std::stod(m_STarXle) * mm;
		}
		if ( StartsWith(line, "TARGETYLENGTH") )
		{
			char hfile[1000];
			sscanf(line.data(), "TARGETYLENGTH %s", hfile);
			m_STarYle = hfile;
			m_TarYle = std::stod(m_STarYle) * mm;
		}
		if ( StartsWith(line, "TARGETPOX") )
		{
			char hfile[1000];
			sscanf(line.data(), "TARGETPOX %s", hfile);
			m_STarPoX = hfile;
			m_TarPoX = std::stod(m_STarPoX) * mm;
		}
		if ( StartsWith(line, "TARGETPOY") )
		{
			char hfile[1000];
			sscanf(line.data(), "TARGETPOY %s", hfile);
			m_StarPoY = hfile;
			m_TarPoY = std::stod(m_StarPoY) * mm;
		}

		
		// E Scintilators
		if ( StartsWith(line, "EXPAND") )
		{
			char hfile[1000];
			sscanf(line.data(), "EXPAND %s", hfile);
			m_SSciEpx = hfile;
			m_SciEpx = std::stod(m_SSciEpx) * mm;
		}
		
/*		// Read configurations: Crystals
		if ( StartsWith(line, "DETECTORSETUP") )
		{
			char hfile[1000];
			sscanf(line.data(), "DETECTORSETUP %s", hfile);
			m_SDetSet = hfile;
			if ( m_SDetSet.length() != 120 ) m_DetSet.assign(120, false);
			else
			{
				int temp;
				for ( int i = 0; i < 120; i++ )
				{
					temp = m_SDetSet.data()[i];
					if ( temp == 48 ) m_DetSet[i] = false;
					else m_DetSet[i] = true;
				}
			}
		}
*/		
/*

		// Read configurations: silicon
		if ( StartsWith(line, "DETECTORSETUP_Si") )
		{
			char hfile[1000];
			sscanf(line.data(), "DETECTORSETUP_Si %s", hfile);
			m_SDetSet = hfile;
			if ( m_SDetSet.length() != 120 ) m_DetSet.assign(120, false);
			else
			{
				int temp;
				for ( int i = 0; i < 120; i++ )
				{
					temp = m_SDetSet.data()[i];
					if ( temp == 48 ) m_DetSet[i] = false;
					else m_DetSet[i] = true;
				}
			}
		}
		

		if ( StartsWith(line, "Si_dim_x") )
		{
			char hfile[1000];
			sscanf(line.data(), "Si_dim_x %s", hfile);
			m_SDet_dim_X = hfile;
			m_Det_dim_X = std::stod(m_SDet_dim_X) * mm;
		}

		if ( StartsWith(line, "Si_dim_y") )
		{
			char hfile[1000];
			sscanf(line.data(), "Si_dim_y %s", hfile);
			m_SDet_dim_Y = hfile;
			m_Det_dim_Y = std::stod(m_SDet_dim_Y) * mm;
		}

		if ( StartsWith(line, "Si_dim_z") )
		{
			char hfile[1000];
			sscanf(line.data(), "Si_dim_z %s", hfile);
			m_SDet_dim_Z = hfile;
			m_Det_dim_Z = std::stod(m_SDet_dim_Z) * um;
		}

*/







		if ( StartsWith(line, "DETECTORPOSITIONX") )
		{
			char hfile[1000];
			sscanf(line.data(), "DETECTORPOSITIONX %s", hfile);
			m_SDetPoX = hfile;
			m_DetPoX = std::stod(m_SDetPoX) * mm;
		}
		if ( StartsWith(line, "DETECTORPOSITIONY") )
		{
			char hfile[1000];
			sscanf(line.data(), "DETECTORPOSITIONY %s", hfile);
			m_SDetPoY = hfile;
			m_DetPoY = std::stod(m_SDetPoY) * mm;
		}
		if ( StartsWith(line, "DETECTORPOSITIONZ") )
		{
			char hfile[1000];
			sscanf(line.data(), "DETECTORPOSITIONZ %s", hfile);
			m_SDetPoZ = hfile;
			m_DetPoZ = std::stod(m_SDetPoZ) * mm;
		}
		if ( StartsWith(line, "DETECTORANGLE") )
		{
			char hfile[1000];
			sscanf(line.data(), "DETECTORANGLE %s", hfile);
			m_SDetAng = hfile;
			m_DetAng = std::stod(m_SDetAng) * mm;
		}




		if ( StartsWith(line, "CYL_SQ_CONFIG") )
		{
			char hfile[1000];
			sscanf(line.data(), "CYL_SQ_CONFIG %s", hfile);
			m_SCYL_SQ_CONFIG = hfile;
			m_CYL_SQ_CONFIG = std::stod(m_SCYL_SQ_CONFIG);
		}




/*JG		
		// parts of construction
		if ( StartsWith(line, "TARGETTUBEB0") )
		{
			char hfile[1000];
			sscanf(line.data(), "TARGETTUBEB0 %s", hfile);
			m_SUseVB0 = hfile;
			if      ( m_SUseVB0 == "ON"  ) m_UseVB0 = true;
			else if ( m_SUseVB0 == "OFF" ) m_UseVB0 = false;
		}
		if ( StartsWith(line, "SMALLBARRELB1") )
		{
			char hfile[1000];
			sscanf(line.data(), "SMALLBARRELB1 %s", hfile);
			m_SUseVB1 = hfile;
			if      ( m_SUseVB1 == "ON"  ) m_UseVB1 = true;
			else if ( m_SUseVB1 == "OFF" ) m_UseVB1 = false;
		}
		if ( StartsWith(line, "LARGEBARRELB2") )
		{
			char hfile[1000];
			sscanf(line.data(), "LARGEBARRELB2 %s", hfile);
			m_SUseVB2 = hfile;
			if      ( m_SUseVB2 == "ON"  ) m_UseVB2 = true;
			else if ( m_SUseVB2 == "OFF" ) m_UseVB2 = false;
		}
		if ( StartsWith(line, "NARROWTUBEB3") )
		{
			char hfile[1000];
			sscanf(line.data(), "NARROWTUBEB3 %s", hfile);
			m_SUseVB3 = hfile;
			if      ( m_SUseVB3 == "ON"  ) m_UseVB3 = true;
			else if ( m_SUseVB3 == "OFF" ) m_UseVB3 = false;
		}
		if ( StartsWith(line, "BEAMTUBEBV") )
		{
			char hfile[1000];
			sscanf(line.data(), "BEAMTUBEBV %s", hfile);
			m_SUseVBV = hfile;
			if      ( m_SUseVBV == "ON"  ) m_UseVBV = true;
			else if ( m_SUseVBV == "OFF" ) m_UseVBV = false;
		}
		if ( StartsWith(line, "EXITWINDOWBW") )
		{
			char hfile[1000];
			sscanf(line.data(), "EXITWINDOWBW %s", hfile);
			m_SUseVBW = hfile;
			if      ( m_SUseVBW == "ON"  ) m_UseVBW = true;
			else if ( m_SUseVBW == "OFF" ) m_UseVBW = false;
		}
*/		
	}

	PrintConfiguration();

	return true;
}

void BT2017ConMan::PrintConfiguration()
{
	// Computing
	printf(" BT2017ConMan::Load() => USEMULTITHREADS   			%s\n", m_SUseMTD.data());
	printf(" BT2017ConMan::Load() => NTHREADS           		%s\n", m_SNofTRD.data());
	// Physics                                          	
	printf(" BT2017ConMan::Load() => USEJEDIPHYSICS    	 		%s\n", m_SUseJED.data());
	// World                                            	
	printf(" BT2017ConMan::Load() => WORLDX             		%s\n", m_SWorldX.data());
	printf(" BT2017ConMan::Load() => WORLDY             		%s\n", m_SWorldY.data());
	printf(" BT2017ConMan::Load() => WORLDZ             		%s\n", m_SWorldZ.data());
	// Beam                                             	
	printf(" BT2017ConMan::Load() => BEAMDELTAX         		%s\n", m_SBeamDX.data());
	printf(" BT2017ConMan::Load() => BEAMDELTAY         		%s\n", m_SBeamDY.data());
	printf(" BT2017ConMan::Load() => BEAMKINETICENERGY  		%s\n", m_SBeamKE.data());
	printf(" BT2017ConMan::Load() => BEAMAXISX  				%s\n", m_SBeamAX.data());
	printf(" BT2017ConMan::Load() => BEAMAXISY  				%s\n", m_SBeamAY.data());
	printf(" BT2017ConMan::Load() => BEAMAXISZ  				%s\n", m_SBeamAZ.data());
	printf(" BT2017ConMan::Load() => BEAMPOLARIZATION  			%s\n", m_SBeamPO.data());
	printf(" BT2017ConMan::Load() => BEAMPOLARIZATIONPHI  		%s\n", m_SBeamPP.data());
	printf(" BT2017ConMan::Load() => AVERAGEANALYZINGPOWER  	%s\n", m_SBeamAN.data());
	// Particle
	printf(" BT2017ConMan::Load() => PARTICLENAME  		   	   %s\n", m_SParName.data());
	printf(" BT2017ConMan::Load() => MINTHETA  					%s\n", m_SBeamST.data());
	printf(" BT2017ConMan::Load() => MAXTHETA 					%s\n", m_SBeamLT.data());
	// Target                                           	
	printf(" BT2017ConMan::Load() => USETARGET          		%s\n", m_SUseTar.data());
	printf(" BT2017ConMan::Load() => TARGETMATERIAL     		%s\n", m_STarMat.data());
	printf(" BT2017ConMan::Load() => TARGETTHICKNESS    		%s\n", m_STarThi.data());
	printf(" BT2017ConMan::Load() => TARGETXLENGTH    			%s\n", m_STarXle.data());
	printf(" BT2017ConMan::Load() => TARGETYLENGTH    			%s\n", m_STarYle.data());
	printf(" BT2017ConMan::Load() => TARGETPOX    				%s\n", m_STarPoX.data());
	printf(" BT2017ConMan::Load() => TARGETPOY    				%s\n", m_StarPoY.data());
	// E Scintilators	
	printf(" BT2017ConMan::Load() => EXPAND		        		%s\n", m_SSciEpx.data());
	// Crystals	
//	printf(" BT2017ConMan::Load() => DETECTORSETUP      		%s\n", m_SDetSet.data());
	printf(" BT2017ConMan::Load() => DETECTORPOSITIONX  		%s\n", m_SDetPoX.data());
	printf(" BT2017ConMan::Load() => DETECTORPOSITIONY  		%s\n", m_SDetPoY.data());
	printf(" BT2017ConMan::Load() => DETECTORPOSITIONZ  		%s\n", m_SDetPoZ.data());
	printf(" BT2017ConMan::Load() => DETECTORANGLE      		%s\n", m_SDetAng.data());

	printf(" BT2017ConMan::Load() => DETECTORSETUP_si      		%s\n", m_SDetSet.data());

//	printf(" BT2017ConMan::Load() => silicon dimensions x      		%s\n", m_SDet_dim_X.data());
//	printf(" BT2017ConMan::Load() => silicon dimensions y      		%s\n", m_SDet_dim_Y.data());
//	printf(" BT2017ConMan::Load() => silicon dimensions z      		%s\n", m_SDet_dim_Z.data());

	printf(" BT2017ConMan::Load() => Detector configuration      		%s\n", m_SCYL_SQ_CONFIG.data());

	printf("\n");

	printf("picture of detector setup: \n	 \n                 ====== A2 ======                              ====== B2 ====== \n                  *                                             * \n                *                                      * \n            ====== A1 ======                  ====== B1 ====== \n             *                           * \n         ==== A0 ====            ==== B0 ====    \n          *                *  \n        * DET2THETA  *    DET1THETA   \n      PG-> --------------------------------------------------------------------- \n                  \n                  \n         ==== A0 ====            ==== B0 ====                  \n                \n            ===== A1 ======                   ====== B1 ======                         \n                                           \n \n                ====== A2 ======                               ====== B2 ====== \n");

	printf("\n");
	printf(" BT2017ConMan::Load() => Det theta 1 Min		%s\n", m_SDET1THETA_MIN.data());
	printf(" BT2017ConMan::Load() => Det theta 1 Max		%s\n", m_SDET1THETA_MAX.data());
	printf(" BT2017ConMan::Load() => Det theta 2 Min		%s\n", m_SDET2THETA_MIN.data());
	printf(" BT2017ConMan::Load() => Det theta 2 Max		%s\n", m_SDET2THETA_MAX.data());

	printf(" BT2017ConMan::Load() => DETLAY1_THICKNESS		%s\n", m_SDETLAY1_THICKNESS.data());
	printf(" BT2017ConMan::Load() => DETLAY2_THICKNESS		%s\n", m_SDETLAY2_THICKNESS.data());
	printf(" BT2017ConMan::Load() => DETLAY3_THICKNESS		%s\n", m_SDETLAY3_THICKNESS.data());

	printf(" BT2017ConMan::Load() => DETLAY1_MAT		%s\n", m_SDETLAY1_MAT.data());

	printf(" BT2017ConMan::Load() => RAD0		%s\n", m_SRAD0.data());
	printf(" BT2017ConMan::Load() => RAD1		%s\n", m_SRAD1.data());
	printf(" BT2017ConMan::Load() => RAD2		%s\n", m_SRAD2.data());	

}	


//////////////////////////////////////////////////
//   Set & get configurations                   //
//////////////////////////////////////////////////
// Computing
void BT2017ConMan::SetUseMTD(G4bool useMTD){m_UseMTD = useMTD;}
G4bool BT2017ConMan::GetUseMTD() {return m_UseMTD;}
void BT2017ConMan::SetNofTRD(G4int nofTRD){m_NofTRD = nofTRD;}
G4int BT2017ConMan::GetNofTRD() {return m_NofTRD;}
// events and cycles
void BT2017ConMan::SetNumberEv(G4int numEve){m_NumEve = numEve;}	 
G4int BT2017ConMan::GetNumberEv() {return m_NumEve;} 
// Physics
void BT2017ConMan::SetUseJED(G4bool useJED){m_TarMat = useJED;}
G4bool BT2017ConMan::GetUseJED() {return m_UseJED;}
// World
void BT2017ConMan::SetWorldX(G4double worldX){m_WorldX = worldX;}
G4double BT2017ConMan::GetWorldX() {return m_WorldX;}
void BT2017ConMan::SetWorldY(G4double worldY){m_WorldY = worldY;}
G4double BT2017ConMan::GetWorldY() {return m_WorldY;}
void BT2017ConMan::SetWorldZ(G4double worldZ){m_WorldZ = worldZ;}
G4double BT2017ConMan::GetWorldZ() {return m_WorldZ;}
// Beam
void BT2017ConMan::SetBeamDX(G4double beamDX){m_BeamDX = beamDX;}
G4double BT2017ConMan::GetBeamDX() {return m_BeamDX;}
void BT2017ConMan::SetBeamDY(G4double beamDY){m_BeamDY = beamDY;}
G4double BT2017ConMan::GetBeamDY() {return m_BeamDY;}
void BT2017ConMan::SetBeamKE(G4double beamKE){m_BeamKE = beamKE;}
G4double BT2017ConMan::GetBeamKE() {return m_BeamKE;}
void BT2017ConMan::SetBeamAX(G4double beamAX){m_BeamAX = beamAX;}
G4double BT2017ConMan::GetBeamAX() {return m_BeamAX;}
void BT2017ConMan::SetBeamAY(G4double beamAY){m_BeamAY = beamAY;}
G4double BT2017ConMan::GetBeamAY() {return m_BeamAY;}
void BT2017ConMan::SetBeamAZ(G4double beamAZ){m_BeamAZ = beamAZ;}
G4double BT2017ConMan::GetBeamAZ() {return m_BeamAZ;}
void BT2017ConMan::SetBeamPO(G4double beamPO){m_BeamPO = beamPO;}
G4double BT2017ConMan::GetBeamPO() {return m_BeamPO;}
void BT2017ConMan::SetBeamPP(G4double beamPP){m_BeamPP = beamPP;}
G4double BT2017ConMan::GetBeamPP() {return m_BeamPP;}
void BT2017ConMan::SetBeamAN(G4double beamAN){m_BeamAN = beamAN;}
G4double BT2017ConMan::GetBeamAN() {return m_BeamAN;}
// Particle
void BT2017ConMan::SetParName(std::string parname){m_SParName = parname;}
std::string BT2017ConMan::GetParName() {return m_SParName;}
void BT2017ConMan::SetMinThe(G4double beamST){m_BeamST = beamST;}
G4double BT2017ConMan::GetMinThe() {return m_BeamST;}
void BT2017ConMan::SetMaxThe(G4double beamLT){m_BeamLT = beamLT;}
G4double BT2017ConMan::GetMaxThe() {return m_BeamLT;}
// Target
void BT2017ConMan::SetUseTar(G4bool useTar){m_UseTar = useTar;}
G4bool BT2017ConMan::GetUseTar() {return m_UseTar;}
void BT2017ConMan::SetTarMat(G4String tarMat){m_TarMat = tarMat;}
G4String BT2017ConMan::GetTarMat() {return m_TarMat;}
void BT2017ConMan::SetTarThi(G4double tarThi){m_TarThi = tarThi;}
G4double BT2017ConMan::GetTarThi() {return m_TarThi;}
void BT2017ConMan::SetTarXle(G4double tarXle){m_TarXle = tarXle;}
G4double BT2017ConMan::GetTarXle() {return m_TarXle;}
void BT2017ConMan::SetTarYle(G4double tarYle){m_TarYle = tarYle;}
G4double BT2017ConMan::GetTarYle() {return m_TarYle;}
void BT2017ConMan::SetTarPoX(G4double tarPoX){m_TarPoX = tarPoX;}
G4double BT2017ConMan::GetTarPoX() {return m_TarPoX;}
void BT2017ConMan::SetTarPoY(G4double tarPoY){m_TarPoY = tarPoY;}
G4double BT2017ConMan::GetTarPoY() {return m_TarPoY;}




void BT2017ConMan::SetRAD0(G4double RAD0){m_RAD0 = RAD0;}
G4double BT2017ConMan::GetRAD0() {return m_RAD0;}
void BT2017ConMan::SetRAD1(G4double RAD1){m_RAD1 = RAD1;}
G4double BT2017ConMan::GetRAD1() {return m_RAD1;}
void BT2017ConMan::SetRAD2(G4double RAD2){m_RAD2 = RAD2;}
G4double BT2017ConMan::GetRAD2() {return m_RAD2;}


void BT2017ConMan::SetDETLAY1_THICKNESS(G4double DETLAY1_THICKNESS){m_DETLAY1_THICKNESS = DETLAY1_THICKNESS;}
G4double BT2017ConMan::GetDETLAY1_THICKNESS() {return m_DETLAY1_THICKNESS;}

void BT2017ConMan::SetDETLAY2_THICKNESS(G4double DETLAY2_THICKNESS){m_DETLAY2_THICKNESS = DETLAY2_THICKNESS;}
G4double BT2017ConMan::GetDETLAY2_THICKNESS() {return m_DETLAY2_THICKNESS;}

void BT2017ConMan::SetDETLAY3_THICKNESS(G4double DETLAY3_THICKNESS){m_DETLAY3_THICKNESS = DETLAY3_THICKNESS;}
G4double BT2017ConMan::GetDETLAY3_THICKNESS() {return m_DETLAY3_THICKNESS;}





void BT2017ConMan::SetDET1THETA_MIN(G4double DET1THETA_MIN){m_DET1THETA_MIN = DET1THETA_MIN;}
G4double BT2017ConMan::GetDET1THETA_MIN() {return m_DET1THETA_MIN;}

void BT2017ConMan::SetDET1THETA_MAX(G4double DET1THETA_MAX){m_DET1THETA_MAX = DET1THETA_MAX;}
G4double BT2017ConMan::GetDET1THETA_MAX() {return m_DET1THETA_MAX;}


void BT2017ConMan::SetDET2THETA_MIN(G4double DET2THETA_MIN){m_DET2THETA_MIN = DET2THETA_MIN;}
G4double BT2017ConMan::GetDET2THETA_MIN() {return m_DET2THETA_MIN;}

void BT2017ConMan::SetDET2THETA_MAX(G4double DET2THETA_MAX){m_DET2THETA_MAX = DET2THETA_MAX;}
G4double BT2017ConMan::GetDET2THETA_MAX() {return m_DET2THETA_MAX;}

/*

void BT2017ConMan::SetDETLAY1_MAT(G4String DETLAY1_MAT){m_DETLAY1_MAT = DETLAY1_MAT;}
G4double BT2017ConMan::GetDETLAY1_MAT() {return m_DETLAY1_MAT;}

void BT2017ConMan::SetDETLAY2_MAT(G4String DETLAY2_MAT){m_DETLAY2_MAT = DETLAY2_MAT;}
G4double BT2017ConMan::GetDETLAY2_MAT() {return m_DETLAY2_MAT;}

void BT2017ConMan::SetDETLAY3_MAT(G4String DETLAY3_MAT){m_DETLAY3_MAT = DETLAY3_MAT;}
G4double BT2017ConMan::GetDETLAY3_MAT() {return m_DETLAY3_MAT;}

*/



// Scintilator
void BT2017ConMan::SetExpand(G4double expand){m_SciEpx = expand;}
G4double BT2017ConMan::GetExpand() {return m_SciEpx;}



// Crystals
void BT2017ConMan::SetDetSet(std::vector<G4bool> detSet){m_DetSet = detSet;}
std::vector<G4bool> BT2017ConMan::GetDetSet() {return m_DetSet;}
void BT2017ConMan::SetDetPoX(G4double detPoX){m_DetPoX = detPoX;}
G4double BT2017ConMan::GetDetPoX() {return m_DetPoX;}
void BT2017ConMan::SetDetPoY(G4double detPoY){m_DetPoY = detPoY;}
G4double BT2017ConMan::GetDetPoY() {return m_DetPoY;}
void BT2017ConMan::SetDetPoZ(G4double detPoZ){m_DetPoZ = detPoZ;}
G4double BT2017ConMan::GetDetPoZ() {return m_DetPoZ;}
void BT2017ConMan::SetDetAng(G4double detAng){m_DetAng = detAng;}
G4double BT2017ConMan::GetDetAng() {return m_DetAng;}



//Silicon Layers
void BT2017ConMan::Set_CYL_SQ_CONFIG(G4int CYL_SQ_CONFIG){m_CYL_SQ_CONFIG = CYL_SQ_CONFIG;}
G4int BT2017ConMan::Get_CYL_SQ_CONFIG() {return m_CYL_SQ_CONFIG;}




/*
void BT2017ConMan::SetDetSet(std::vector<G4bool> detSet){m_DetSet = detSet;}
std::vector<G4bool> BT2017ConMan::GetDetSet() {return m_DetSet;}
void BT2017ConMan::SetDetPoX(G4double detPoX){m_DetPoX = detPoX;}
G4double BT2017ConMan::GetDetPoX() {return m_DetPoX;}
void BT2017ConMan::SetDetPoY(G4double detPoY){m_DetPoY = detPoY;}
G4double BT2017ConMan::GetDetPoY() {return m_DetPoY;}
void BT2017ConMan::SetDetPoZ(G4double detPoZ){m_DetPoZ = detPoZ;}
G4double BT2017ConMan::GetDetPoZ() {return m_DetPoZ;}
void BT2017ConMan::SetDetAng(G4double detAng){m_DetAng = detAng;}
G4double BT2017ConMan::GetDetAng() {return m_DetAng;}
*/






// steel construction
void BT2017ConMan::SetUseVB0(G4bool SetUsVB0){m_UseVB0 = SetUsVB0;}
G4bool BT2017ConMan::GetUseVB0() {return m_UseVB0;}
void BT2017ConMan::SetUseVB1(G4bool SetUsVB1){m_UseVB1 = SetUsVB1;}
G4bool BT2017ConMan::GetUseVB1() {return m_UseVB1;}
void BT2017ConMan::SetUseVB2(G4bool SetUsVB2){m_UseVB2 = SetUsVB2;}
G4bool BT2017ConMan::GetUseVB2() {return m_UseVB2;}
void BT2017ConMan::SetUseVB3(G4bool SetUsVB3){m_UseVB3 = SetUsVB3;}
G4bool BT2017ConMan::GetUseVB3() {return m_UseVB3;}
void BT2017ConMan::SetUseVBV(G4bool SetUsVBV){m_UseVBV = SetUsVBV;}
G4bool BT2017ConMan::GetUseVBV() {return m_UseVBV;}
void BT2017ConMan::SetUseVBW(G4bool SetUsVBW){m_UseVBW = SetUsVBW;}
G4bool BT2017ConMan::GetUseVBW() {return m_UseVBW;}

//////////////////////////////////////////////////
//   Test whether a line starts with ...        //
//////////////////////////////////////////////////
bool BT2017ConMan::StartsWith(const std::string& text, const std::string& token)
{
	if ( text.length() < token.length() ) return false;
	return ( text.compare(0, token.length(), token) == 0 );
}
