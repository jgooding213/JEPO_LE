
//#define eMin 0
//#define eMax 270
//#define phiMin 0
//#define phiMax 20

#define detLen 100 //mm
#define particleType 1 // 0 = p 1 = d

#define u_MeV 931.49410242 // MeV/c^2
#define c  299792458 //m/s

#define verbose 1//m/s

#define M 938.272 //(1.007276466879 * u_MeV)
#define LGAD_error = 0

#include <iostream>
#include <math.h>
#include <sstream>
#include <random>
#define PI 3.14159265
//#define filename "v2_silicon_layer/protonFiltered/protonC-39MeV_t0.root"
//#define filename "v3_vac/protonEmpty-39MeV_t0.root"
//#define filename "v2_vacuum_layer/protonC-39MeV_t0.root"
//#define filename "v3_Si_100umC/protonC-39MeV_t0.root"
//#define filename "protonC-39MeV_t0.root"
//#define filename "protonEmpty-39MeV_t0.root"
//#define filename "v3_vac/protonC-39MeV_t0.root"
#define filename "unPol/protonEmpty-39MeV_t0.root"
#define filename1 "unPol/protonEmpty-39MeV_t1.root"
#define filename2 "unPol/protonEmpty-39MeV_t2.root"
#define filename3 "unPol/protonEmpty-39MeV_t3.root"
#define filename4 "unPol/protonEmpty-39MeV_t4.root"

#define stop 1000000000

#include "TH1F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPad.h"
#include "TString.h"

#include "TF1.h"
#include "TF2.h"



////////////////////////////////////////////////////////////
// Functions //
////////////////////////////////////////////////////////////

//TH1D*<double> getToF (string fileName, int stopPoint);
//vector<double> getToF (string fileNam int bins, double min, double maxe, int stopPoint);



vector<double> getToF (string fileName, int stopPoint, char addError, double Err);
vector<double> getDist (string fileName, int stopPoint);
vector<double> getTheta (string fileName, int stopPoint, double Errx1,double Erry1,double Errx2,double Erry2,double Errx3,double Erry3);
vector<double> getPhi (string fileName, int stopPoint, double Errx1,double Erry1,double Errx2,double Erry2,double Errx3,double Erry3);
vector<double> getE (vector<double> ToF , vector<double> d, int stopPoint);
vector<double> getp (vector<double> ToF , vector<double> d, int stopPoint);


vector<double> getKE (string fileName,  int stopPoint);
vector<double> getEDEP (string fileName,  int stopPoint, int layer);

TH1D* plotHistVec(vector<double> ToF, double minLim, double maxLim, int bins, string xlabel, string ylabel, string title, string canvName);
vector<double> doCuts (char output,vector<double> EDEP, vector<double> KE, vector<double> E, vector<double> theta,
                                   vector<double> phi, double thetaMin, double thetaMax, double Emin, double Emax);
vector<double> compareVecs( vector<double> vec1, vector<double> vec2);

double getFOM(vector<double> phi, char type);


double getAsym(vector<double> phi, char type);
double getAsymErr(vector<double> phi, char type);

vector<double> getTarPos(vector<double> theta , vector<double> phi, int stopPoint, char xy);



TH2D * plot2DHistVec(vector<double> vec1,vector<double> vec2, double minLimX, double maxLimX, int binsX,  double minLimY, double maxLimY, int binsY,string xlabel, string ylabel, string title, string canvName);

/*
vector<double> getp (string fileName, double detectorLen, int stopPoint);
vector<double> getE (string fileName, double detectorLen, int stopPoint);
vector<double> getThetaDist (string fileName, double detectorLen, int stopPoint);
vector<double> getPhiDist (string fileName, double detectorLen, int stopPoint);
TH1D* getVal(int part, int type,  int bins, double min, double max);
TH2D* get2D_Dist(string fileName,  int bins , double min, double max, double LGAD1_r, double LGAD2_r, double HVCMOS_r);
double getP(int particleID, double x1, double y1, double z1, double x2, double y2, double z2, double time1, double time2);
double getAsym(int part, double phi_min, double phi_max, double E_min, double E_max);
*/

TH2D* get2D_Dist(string fileName, int stopPoint);


////////////////////////////////////////////////////////////
// MAIN //
/////
///
////////////////////////////////////////////////////////////
//////////

void protonReader_v2() {


  int momentumRun;
  int deuteronRun;

  
  double time;

  char fileBool;
  double detectorLen = 0.100;
  

vector<double> tof_0 =  getToF(filename, stop, 'y', 0);
vector<double> d_0 =  getDist(filename, stop);
vector<double> theta_0 =  getTheta(filename, stop, 0,0,0,0,0,0);
vector<double> phi_0 =  getPhi(filename, stop, 0,0,0,0,0,0);
vector<double> E_0 =  getE(tof_0 , d_0, stop);
vector<double> p_0 =  getp(tof_0 , d_0, stop);
vector<double> KE_0 =  getKE(filename, stop);
vector<double> HVCMOS_EDEP_0 =  getEDEP(filename, stop, 1);


vector<double> tof_1 =  getToF(filename1, stop, 'y', 0);
vector<double> d_1 =  getDist(filename1, stop);
vector<double> theta_1 =  getTheta(filename1, stop, 0,0,0,0,0,0);
vector<double> phi_1 =  getPhi(filename1, stop, 0,0,0,0,0,0);
vector<double> E_1 =  getE(tof_1 , d_1, stop);
vector<double> p_1 =  getp(tof_1 , d_1, stop);
vector<double> KE_1 =  getKE(filename1, stop);
vector<double> HVCMOS_EDEP_1 =  getEDEP(filename1, stop, 1);


// vector<double> tof_2 =  getToF(filename2, stop, 'y', 0);
// vector<double> d_2 =  getDist(filename2, stop);
// vector<double> theta_2 =  getTheta(filename2, stop, 0,0,0,0,0,0);
// vector<double> phi_2 =  getPhi(filename2, stop, 0,0,0,0,0,0);
// vector<double> E_2 =  getE(tof_2 , d_2, stop);
// vector<double> p_2 =  getp(tof_2 , d_2, stop);
// vector<double> KE_2 =  getKE(filename2, stop);
// vector<double> HVCMOS_EDEP_2 =  getEDEP(filename2, stop, 1);


// vector<double> tof_3 =  getToF(filename3, stop, 'y', 0);
// vector<double> d_3 =  getDist(filename3, stop);
// vector<double> theta_3 =  getTheta(filename3, stop, 0,0,0,0,0,0);
// vector<double> phi_3 =  getPhi(filename3, stop, 0,0,0,0,0,0);
// vector<double> E_3 =  getE(tof_3 , d_3, stop);
// vector<double> p_3 =  getp(tof_3 , d_3, stop);
// vector<double> KE_3 =  getKE(filename3, stop);
// vector<double> HVCMOS_EDEP_3 =  getEDEP(filename3, stop, 1);



// vector<double> tof_4 =  getToF(filename4, stop, 'y', 0);
// vector<double> d_4 =  getDist(filename4, stop);
// vector<double> theta_4 =  getTheta(filename4, stop, 0,0,0,0,0,0);
// vector<double> phi_4 =  getPhi(filename4, stop, 0,0,0,0,0,0);
// vector<double> E_4 =  getE(tof_4 , d_4, stop);
// vector<double> p_4 =  getp(tof_4 , d_4, stop);
// vector<double> KE_4 =  getKE(filename4, stop);
// vector<double> HVCMOS_EDEP_4 =  getEDEP(filename4, stop, 1);

//int beforeSize  = tof_1.size();

tof_0.insert(tof_0.end(),tof_1.begin(),tof_1.end());
//tof_0.insert(tof_0.end(),tof_2.begin(),tof_2.end());
//tof_0.insert(tof_0.end(),tof_3.begin(),tof_3.end());
//tof_0.insert(tof_0.end(),tof_4.begin(),tof_4.end());


d_0.insert(d_0.end(),d_1.begin(),d_1.end());
//d_0.insert(d_0.end(),d_2.begin(),d_2.end());
//d_0.insert(d_0.end(),d_3.begin(),d_3.end());
//d_0.insert(d_0.end(),d_4.begin(),d_4.end());

theta_0.insert(theta_0.end(),theta_1.begin(),theta_1.end());
//theta_0.insert(theta_0.end(),theta_2.begin(),theta_2.end());
//theta_0.insert(theta_0.end(),theta_3.begin(),theta_3.end());
//theta_0.insert(theta_0.end(),theta_4.begin(),theta_4.end());

phi_0.insert(phi_0.end(),phi_1.begin(),phi_1.end());
//phi_0.insert(phi_0.end(),phi_2.begin(),phi_2.end());
//phi_0.insert(phi_0.end(),phi_3.begin(),phi_3.end());
//phi_0.insert(phi_0.end(),phi_4.begin(),phi_4.end());


E_0.insert(E_0.end(),E_1.begin(),E_1.end());
//E_0.insert(E_0.end(),E_2.begin(),E_2.end());
//E_0.insert(E_0.end(),E_3.begin(),E_3.end());
//E_0.insert(E_0.end(),E_4.begin(),E_4.end());


p_0.insert(p_0.end(),p_1.begin(),p_1.end());
//p_0.insert(p_0.end(),p_2.begin(),p_2.end());
//p_0.insert(p_0.end(),p_3.begin(),p_3.end());
//p_0.insert(p_0.end(),p_4.begin(),p_4.end());


KE_0.insert(KE_0.end(),KE_1.begin(),KE_1.end());
//KE_0.insert(KE_0.end(),KE_2.begin(),KE_2.end());
//KE_0.insert(KE_0.end(),KE_3.begin(),KE_3.end());
//KE_0.insert(KE_0.end(),KE_4.begin(),KE_4.end());

HVCMOS_EDEP_0.insert(HVCMOS_EDEP_0.end(),HVCMOS_EDEP_1.begin(),HVCMOS_EDEP_1.end());
//HVCMOS_EDEP_0.insert(HVCMOS_EDEP_0.end(),HVCMOS_EDEP_2.begin(),HVCMOS_EDEP_2.end());
//HVCMOS_EDEP_0.insert(HVCMOS_EDEP_0.end(),HVCMOS_EDEP_3.begin(),HVCMOS_EDEP_3.end());
//HVCMOS_EDEP_0.insert(HVCMOS_EDEP_0.end(),HVCMOS_EDEP_4.begin(),HVCMOS_EDEP_4.end());


//,tof_3.begin(),tof_3.end(),tof_4.begin(),tof_4.end()
// d_0 
// theta_0 
// phi_0 
// E_0 
// p_0 
// KE_0 
// HVCMOS_EDEP_0 



double angMin = 1.2*40;
double angMax = 70;


vector<double> phi = doCuts ('p', HVCMOS_EDEP_0 , KE_0, E_0, theta_0, phi_0, angMin, angMax, 0 , 50); 
vector<double> E = doCuts ('E', HVCMOS_EDEP_0 , KE_0, E_0, theta_0, phi_0, angMin, angMax, 0 , 50); 
vector<double> theta = doCuts ('t', HVCMOS_EDEP_0  , KE_0, E_0, theta_0, phi_0,angMin , angMax, 0 , 50); 
vector<double> HVCMOS_EDEP = doCuts ('d', HVCMOS_EDEP_0  , KE_0, E_0, theta_0, phi_0,angMin , angMax , 0 , 50); 
vector<double> KE = doCuts ('k', HVCMOS_EDEP_0 , KE_0, E_0, theta_0, phi_0,angMin , angMax, 0 , 50); 

vector<double> p = doCuts ('k', HVCMOS_EDEP_0 , p_0, E_0, theta_0, phi_0,angMin , angMax, 0 , 50); 
//vector<double> Eerror = compareVecs( KE, E);
TH2D* xyhist = get2D_Dist(filename, stop);

TCanvas *canvxy = new TCanvas("xydist","xydist (HVCMOS at 430mm from target)",200,10,500,500);
gStyle->SetOptStat(1111111);
canvxy->Draw("xyhist");
xyhist->Draw("colz");
xyhist->SetTitle("xydist (HVCMOS at 80mm from target)");

 xyhist->GetXaxis()->SetTitle("Pos x (mm)");
 xyhist->GetYaxis()->SetTitle("Pos y (mm)");
canvxy->SetLogz();


//TH2D * PID_Hist = plot2DHistVec(E, HVCMOS_EDEP, 0, 50, 100, 0, 0, 50, "Energy (ToF)MeV", "Edep in HVCMOS (MeV)", "E vs EDEP Distribution", "PID_Canvas");
//TH1D * p_hist = plotHistVec(p_0, 0, 350, 500, "Momentum MeV/c", "Entries", "p Distribution", "p_Canvas");
//TH2D * p_vs_theta_Hist = plot2DHistVec(p, theta, 0, 300, 50, 0, 90, 50, "Momentum (ToF) MeV/c", "theta (degrees)", "Momentum vs theta Distribution", "pvt_Canvas");
// double minLimX, double maxLimX, int binsX,  double minLimY, double maxLimY, int binsY




double asymGraph[35];
double asymGraphErr[35];

double asymGraph_x[35] = {10, 11, 12 , 13, 14, 15, 16, 26, 27, 28, 29, 30, 31,32, 33, 34, 35, 36, 37, 38, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58}; // , 49 , 55, 61, 67, 73, 79};
double asymGraph_xErr[35] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0 };
double rangeSize = 1;

char axis = 'x';



int dataPoints = 30;
double asymGraph_y[dataPoints];



asymGraph[0] = 0;
asymGraph[1] = 0;
asymGraph[2] = 0;
asymGraph[3] = 0;
asymGraph[4] = 0;
asymGraph[5] = 0;
asymGraph[6] = 0;
asymGraph[7] = 0;




asymGraph[8] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[8] + 0.00001 - (rangeSize/2), asymGraph_x[8] + (rangeSize/2), 0, 250), axis);
asymGraph[9] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[9] + 0.00001 - (rangeSize/2), asymGraph_x[9] + (rangeSize/2), 0, 250), axis);

asymGraph[10] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[10] + 0.00001 - (rangeSize/2), asymGraph_x[10] + (rangeSize/2), 0, 250), axis);
asymGraph[11] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[11] + 0.00001 - (rangeSize/2), asymGraph_x[11] + (rangeSize/2), 0, 250), axis);
asymGraph[12] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[12] + 0.00001 - (rangeSize/2), asymGraph_x[12] + (rangeSize/2), 0, 250), axis);
asymGraph[13] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[13] + 0.00001 - (rangeSize/2), asymGraph_x[13] + (rangeSize/2), 0, 250), axis);
asymGraph[14] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[14] + 0.00001 - (rangeSize/2), asymGraph_x[14] + (rangeSize/2), 0, 250), axis);
asymGraph[15] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[15] + 0.00001 - (rangeSize/2), asymGraph_x[15] + (rangeSize/2), 0, 250), axis);
asymGraph[16] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[16] + 0.00001 - (rangeSize/2), asymGraph_x[16] + (rangeSize/2), 0, 250), axis);
asymGraph[17] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[17] + 0.00001 - (rangeSize/2), asymGraph_x[17] + (rangeSize/2), 0, 250), axis);
asymGraph[18] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[18] + 0.00001 - (rangeSize/2), asymGraph_x[18] + (rangeSize/2), 0, 250), axis);
asymGraph[19] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[19] + 0.00001 - (rangeSize/2), asymGraph_x[19] + (rangeSize/2), 0, 250), axis);

//asymGraph[20] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[20] + 0.00001 - (rangeSize/2), asymGraph_x[20] + (rangeSize/2), 0, 250), axis);
//asymGraph[21] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[21] + 0.00001 - (rangeSize/2), asymGraph_x[21] + (rangeSize/2), 0, 250), axis);
asymGraph[20] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[20] + 0.00001 - (rangeSize/2), asymGraph_x[20] + (rangeSize/2), 0, 250), axis);
asymGraph[21] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[21] + 0.00001 - (rangeSize/2), asymGraph_x[21] + (rangeSize/2), 0, 250), axis);
asymGraph[22] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[22] + 0.00001 - (rangeSize/2), asymGraph_x[22] + (rangeSize/2), 0, 250), axis);
asymGraph[23] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[23] + 0.00001 - (rangeSize/2), asymGraph_x[23] + (rangeSize/2), 0, 250), axis);
asymGraph[24] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[24] + 0.00001 - (rangeSize/2), asymGraph_x[24] + (rangeSize/2), 0, 250), axis);
asymGraph[25] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[25] + 0.00001 - (rangeSize/2), asymGraph_x[25] + (rangeSize/2), 0, 250), axis);
asymGraph[26] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[26] + 0.00001 - (rangeSize/2), asymGraph_x[26] + (rangeSize/2), 0, 250), axis);
asymGraph[27] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[27] + 0.00001 - (rangeSize/2), asymGraph_x[27] + (rangeSize/2), 0, 250), axis);

asymGraph[28] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[28] + 0.00001 - (rangeSize/2), asymGraph_x[28] + (rangeSize/2), 0, 250), axis);
asymGraph[29] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[29] + 0.00001 - (rangeSize/2), asymGraph_x[29] + (rangeSize/2), 0, 250), axis);
asymGraph[30] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[30] + 0.00001 - (rangeSize/2), asymGraph_x[30] + (rangeSize/2), 0, 250), axis);
//asymGraph[33] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[33] + 0.00001 - (rangeSize/2), asymGraph_x[33] + (rangeSize/2), 0, 250), axis);
//asymGraph[34] = getAsym(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[34] + 0.00001 - (rangeSize/2), asymGraph_x[34] + (rangeSize/2), 0, 250), axis);






asymGraphErr[0] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[0] + 0.00001 - (rangeSize/2), asymGraph_x[0] + (rangeSize/2), 0, 250), axis);
asymGraphErr[1] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[1] + 0.00001 - (rangeSize/2), asymGraph_x[1] + (rangeSize/2), 0, 250), axis);
asymGraphErr[2] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[2] + 0.00001 - (rangeSize/2), asymGraph_x[2] + (rangeSize/2), 0, 250), axis);
asymGraphErr[3] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[3] + 0.00001 - (rangeSize/2), asymGraph_x[3] + (rangeSize/2), 0, 250), axis);
asymGraphErr[4] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[4] + 0.00001 - (rangeSize/2), asymGraph_x[4] + (rangeSize/2), 0, 250), axis);
asymGraphErr[5] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[5] + 0.00001 - (rangeSize/2), asymGraph_x[5] + (rangeSize/2), 0, 250), axis);
asymGraphErr[6] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[6] + 0.00001 - (rangeSize/2), asymGraph_x[6] + (rangeSize/2), 0, 250), axis);
asymGraphErr[7] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[7] + 0.00001 - (rangeSize/2), asymGraph_x[7] + (rangeSize/2), 0, 250), axis);
asymGraphErr[8] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[8] + 0.00001 - (rangeSize/2), asymGraph_x[8] + (rangeSize/2), 0, 250), axis);
asymGraphErr[9] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[9] + 0.00001 - (rangeSize/2), asymGraph_x[9] + (rangeSize/2), 0, 250), axis);


asymGraphErr[10] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[10] + 0.00001 - (rangeSize/2), asymGraph_x[10] + (rangeSize/2), 0, 250), axis);
asymGraphErr[11] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[11] + 0.00001 - (rangeSize/2), asymGraph_x[11] + (rangeSize/2), 0, 250), axis);
asymGraphErr[12] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[12] + 0.00001 - (rangeSize/2), asymGraph_x[12] + (rangeSize/2), 0, 250), axis);
asymGraphErr[13] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[13] + 0.00001 - (rangeSize/2), asymGraph_x[13] + (rangeSize/2), 0, 250), axis);
asymGraphErr[14] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[14] + 0.00001 - (rangeSize/2), asymGraph_x[14] + (rangeSize/2), 0, 250), axis);
asymGraphErr[15] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[15] + 0.00001 - (rangeSize/2), asymGraph_x[15] + (rangeSize/2), 0, 250), axis);
asymGraphErr[16] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[16] + 0.00001 - (rangeSize/2), asymGraph_x[16] + (rangeSize/2), 0, 250), axis);
asymGraphErr[17] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[17] + 0.00001 - (rangeSize/2), asymGraph_x[17] + (rangeSize/2), 0, 250), axis);
asymGraphErr[18] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[18] + 0.00001 - (rangeSize/2), asymGraph_x[18] + (rangeSize/2), 0, 250), axis);
asymGraphErr[19] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[19] + 0.00001 - (rangeSize/2), asymGraph_x[19] + (rangeSize/2), 0, 250), axis);


//asymGraphErr[20] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[20] + 0.00001 - (rangeSize/2), asymGraph_x[20] + (rangeSize/2), 0, 250), axis);
//asymGraphErr[21] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[21] + 0.00001 - (rangeSize/2), asymGraph_x[21] + (rangeSize/2), 0, 250), axis);
asymGraphErr[20] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[20] + 0.00001 - (rangeSize/2), asymGraph_x[20] + (rangeSize/2), 0, 250), axis);
asymGraphErr[21] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[21] + 0.00001 - (rangeSize/2), asymGraph_x[21] + (rangeSize/2), 0, 250), axis);
asymGraphErr[22] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[22] + 0.00001 - (rangeSize/2), asymGraph_x[22] + (rangeSize/2), 0, 250), axis);
asymGraphErr[23] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[23] + 0.00001 - (rangeSize/2), asymGraph_x[23] + (rangeSize/2), 0, 250), axis);
asymGraphErr[24] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[24] + 0.00001 - (rangeSize/2), asymGraph_x[24] + (rangeSize/2), 0, 250), axis);
asymGraphErr[25] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[25] + 0.00001 - (rangeSize/2), asymGraph_x[25] + (rangeSize/2), 0, 250), axis);
asymGraphErr[26] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[26] + 0.00001 - (rangeSize/2), asymGraph_x[26] + (rangeSize/2), 0, 250), axis);
asymGraphErr[27] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[27] + 0.00001 - (rangeSize/2), asymGraph_x[27] + (rangeSize/2), 0, 250), axis);


asymGraphErr[28] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[28] + 0.00001 - (rangeSize/2), asymGraph_x[28] + (rangeSize/2), 0, 250), axis);
asymGraphErr[29] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[29] + 0.00001 - (rangeSize/2), asymGraph_x[29] + (rangeSize/2), 0, 250), axis);
asymGraphErr[30] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[30] + 0.00001 - (rangeSize/2), asymGraph_x[30] + (rangeSize/2), 0, 250), axis);
//asymGraphErr[33] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[33] + 0.00001 - (rangeSize/2), asymGraph_x[33] + (rangeSize/2), 0, 250), axis);
//asymGraphErr[34] = getAsymErr(doCuts ('p',HVCMOS_EDEP_0 ,KE_0, E, theta, phi, asymGraph_x[34] + 0.00001 - (rangeSize/2), asymGraph_x[34] + (rangeSize/2), 0, 250), axis);





cout << "GET ASYM CAN BE DONE IN OTHER METHODS" << endl;



    TF1 *fAy = new TF1("fAy","1*(0.9294 *sin( 0.02346*x -0.7128 ) + 0.2668*sin(0.1586 *x-1.385 )+ 0.05528 *sin(0.3124 *x -2.653 ))",10,80);

   TCanvas *cg = new TCanvas("cg","Asym graph",200,10,500,300);
   TGraph* gr = new TGraphErrors(31,asymGraph_x,asymGraph,asymGraph_xErr,asymGraphErr);
   gr->Draw("A*");
  gr->SetTitle("Asymettry LR");

 gr->GetXaxis()->SetTitle("Theta (deg)");
 gr->GetYaxis()->SetTitle("asym (R-L)/(R+L)");







//vector<double> EDEP = getEdep (filename,  stop, 0);
//TH1D * EDEP_hist = plotHistVec(EDEP, 0, 1, 100, "EDEP (MeV)", "Entries", "EDEP Distribution", "EDEP_Canvas");

TH1D * thetaHist = plotHistVec(theta, 0, 80, 50, "Theta (deg)", "Entries", "Theta Distribution", "thetaCanvas");
TH1D * phiHist = plotHistVec(phi, -10, 370, 50, "Phi (deg)", "Entries", "Phi Distribution", "phiCanvas");
TH1D * E_Hist = plotHistVec(E, 0, 50, 1000, "Energy MeV", "Entries", "E Distribution", "E1_Canvas");
E_Hist ->Fit("gaus","V","E1",35,42);




//TH1D * E_noCut = plotHistVec(E_0, 30, 50, 100, "Energy MeV", "Entries", "E Distribution (no Cuts)", "E_noCuts_Canvas");
//E_noCut ->Fit("gaus","V","E1",30,50);



//TH1D * E_error = plotHistVec(Eerror, -10, 10, 100, "Energy MeV", "Entries", "E_error Distribution", "E_error_Canvas");
//E_error ->Fit("gaus","V","Eerror",20,20);


//TH1D * KE_hist = plotHistVec(KE_0, 0, 50, 50, "Energy MeV", "Entries", "KE Distribution", "KE_Canvas");



//TF1 *gfit = (TF1 *)E->GetFunction("gaus");
//double mean = gfit->GetParameter(0);
//double stdDev = gfit->GetParameter(1);
//double error = gfit->GetParError(0);

//cout << "Asym: " << asym_10_11 << "," << asym_11_12 << "," << asym_12_13 << "," << asym_13_14 << "," << asym_14_15 << endl;

//int testTot = beforeSize + tof_2.size() + tof_3.size() ;//+ tof_4.size();

//cout << testTot << "    " << tof_1.size();

}


TH2D* get2D_Dist(string fileName, int stopPoint){
  TH2D *hist = new TH2D(" ","  " , 50, -90 , 90 , 50, -90 , 90 );
  double HVCMOS_x, HVCMOS_y, HVCMOS_z;
      double LGAD1_x, LGAD1_y, LGAD1_z;
      double LGAD2_x, LGAD2_y, LGAD2_z;


      cout << "Filename: " << fileName << endl;
      cout << "2D distribution in mm" <<endl;

    TFile *g = new TFile(fileName.c_str(),"read");
    TTree *hits      = (TTree*) g->Get("hits");
    int Nsig = hits->GetEntries();
    int sample = std::min(Nsig,stopPoint)/10;

        hits->SetBranchAddress("HVCMOS_x", &HVCMOS_x);
        hits->SetBranchAddress("HVCMOS_y", &HVCMOS_y);
        hits->SetBranchAddress("HVCMOS_z", &HVCMOS_z);



    cout << "distance function works " << endl;
    vector<double> d(std::min(Nsig,stopPoint),0);

//    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//    // fill loop
    int min;
    int max;
    int highBin = 0;
    int currentBin;

    for (int i=0; i <std::min(Nsig/sample,stopPoint/sample); ++i){
    min = i*sample;
    max = i*sample + (sample -1);
    cout << "distance input: " << i << "/" << (std::min(Nsig,stopPoint)/sample)   << endl;

double check;
                for (int n=min; n < max; ++n) {
                hits->GetEntry(n);

                   // cout << HVCMOS_x << " " << HVCMOS_y << " " << HVCMOS_z << endl;
                  if((HVCMOS_z < 400)){
                  //  cout << "bad dist hit" << endl;  
check = abs(HVCMOS_x)+abs(HVCMOS_y);

                            if((check > 70)){
                              hist->Fill(HVCMOS_x, HVCMOS_y);
                              cout << HVCMOS_x << " " << HVCMOS_y << " " << HVCMOS_z << endl;  
                            }                              
                  } 

                }
        
    }


for (int xi = 0; xi < 49; ++xi){

for (int yi = 0; yi < 49; ++yi){
currentBin = hist->GetBinContent(xi, yi);

  if(( currentBin > highBin)){
    highBin = currentBin;
    cout << "High overwrite  " << highBin << endl;
  }

}
}

  
  return hist;







}


vector<double> getTarPos (vector<double> theta , vector<double> phi, int stopPoint, char xy)
{

    

    int Nsig = theta.size();
    int sample = std::min(Nsig,stopPoint)/10;

    cout << "Caluclating target Pos in um" << endl;
    vector<double> pos(std::min(Nsig,stopPoint),0);




//    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//    // fill loop
    int min;
    int max;


    for (int i=0; i <std::min(Nsig/sample,stopPoint/sample); ++i){
    min = i*sample;
    max = i*sample + (sample -1);
    cout << "target position calculation: " << i << "/" << (std::min(Nsig,stopPoint)/sample)   << endl;


                for (int n=min; n < max; ++n) {

                }
        
    }

  
  return pos;
}







// Functions
// ...o0o...o0o...o0o...o0o...o0o...


vector<double> compareVecs( vector<double> vec1, vector<double> vec2){

vector<double> ErrVec(vec1.size());


    for (int i=0; i < vec1.size(); ++i){

        ErrVec[i] = vec1[i] - vec2[i];
    }

cout << "no functionallity for differently sized vectors" << endl;
return ErrVec;
}


vector<double> getEDEP (string fileName,  int stopPoint, int layer){

 double HVCMOS_E, LGAD1_E, LGAD2_E;


        cout << "Filename: " << fileName << endl;
        cout << "EDEP_input " <<endl;

    TFile *g = new TFile(fileName.c_str(),"read");
    TTree *hits      = (TTree*) g->Get("hits");
    int Nsig = hits->GetEntries();
    int sample = std::min(Nsig,stopPoint)/10;

    hits->SetBranchAddress("HVCMOS_E", &HVCMOS_E);
    hits->SetBranchAddress("LGAD1_E", &LGAD1_E);
    hits->SetBranchAddress("LGAD2_E", &LGAD2_E);


    vector<double> EDEP(std::min(Nsig,stopPoint),0);
    int min;
    int max;


    for (int i=0; i <std::min(Nsig/sample,stopPoint/sample); ++i){
    min = i*sample;
    max = i*sample + (sample -1);
    cout << "EDEP input: " << i << "/" << (std::min(Nsig,stopPoint)/sample)   << endl;

            for (int n=min; n < max; ++n) {
                hits->GetEntry(n);

                      switch (layer)
                      {
                      case 1:
                            EDEP[n] = HVCMOS_E;
                        break;
                      case 2:
                            EDEP[n] = LGAD1_E;
                        break;
                      case 3:
                            EDEP[n] = LGAD2_E;
                        break;
                      
                      default:
                        break;
                      }

                }
        
    }

  
  return EDEP;


}

vector<double> getKE (string fileName,  int stopPoint){

 double Kinetic_Energy;


        cout << "Filename: " << fileName << endl;
        cout << "KE_input " <<endl;

    TFile *g = new TFile(fileName.c_str(),"read");
    TTree *hits      = (TTree*) g->Get("hits");
    int Nsig = hits->GetEntries();
    int sample = std::min(Nsig,stopPoint)/10;

    hits->SetBranchAddress("Kinetic_Energy", &Kinetic_Energy);

    vector<double> KE(std::min(Nsig,stopPoint),0);
    int min;
    int max;


    for (int i=0; i <std::min(Nsig/sample,stopPoint/sample); ++i){
    min = i*sample;
    max = i*sample + (sample -1);
    cout << "KE input: " << i << "/" << (std::min(Nsig,stopPoint)/sample)   << endl;

            for (int n=min; n < max; ++n) {
                hits->GetEntry(n);
                            KE[n] = Kinetic_Energy;
                }
        
    }

  
  return KE;
}


/*

vector<double> getEdep (string fileName,  int stopPoint, int layer)
{
 double LGAD1_E, LGAD2_E, HVCMOS_E;


        cout << "Filename: " << fileName << endl;
        cout << "Edep calculating in ps " <<endl;

    TFile *g = new TFile(fileName.c_str(),"read");
    TTree *hits      = (TTree*) g->Get("hits");
    int Nsig = hits->GetEntries();
    int sample = std::min(Nsig,stopPoint)/10;

    hits->SetBranchAddress("LGAD1_E", &LGAD1_E);
    hits->SetBranchAddress("LGAD2_E", &LGAD2_E);
    hits->SetBranchAddress("HVCMOS_E", &HVCMOS_E);

    vector<double> Edep(std::min(Nsig,stopPoint),0);
    int min;
    int max;


    for (int i=0; i <std::min(Nsig/sample,stopPoint/sample); ++i){
    min = i*sample;
    max = i*sample + (sample -1);
    cout << "Edep input: " << i << "/" << (std::min(Nsig,stopPoint)/sample)   << endl;


                for (int n=min; n < max; ++n) {
                hits->GetEntry(n);
                

                        switch (layer)
                        {
                        case 0:
                            Edep[n] = HVCMOS_E;
                            break;

                        case 1:
                            Edep[n] = LGAD1_E;
                            break;

                         case 2:
                            Edep[n] = LGAD2_E;
                            break;                       
                        }

                }
        
    }

  
  return Edep;

}

*/


vector<double> getToF (string fileName, int stopPoint, char addError, double Err)
{

 double LGAD1_t, LGAD2_t, tErr;


  std::default_random_engine generator;
  std::normal_distribution<double> distribution(0,Err);



        cout << "Filename: " << fileName << endl;
        cout << "ToF calculating in ps " <<endl;

    TFile *g = new TFile(fileName.c_str(),"read");
    TTree *hits      = (TTree*) g->Get("hits");
    int Nsig = hits->GetEntries();
    int sample = std::min(Nsig,stopPoint)/10;

    hits->SetBranchAddress("LGAD1_t", &LGAD1_t);
    hits->SetBranchAddress("LGAD2_t", &LGAD2_t);


    vector<double> ToF(std::min(Nsig,stopPoint),0);

//    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//    // fill loop
    int min;
    int max;
int check;

    for (int i=0; i <std::min(Nsig/sample,stopPoint/sample); ++i){
    min = i*sample;
    max = i*sample + (sample -1);
    cout << "Time of flight input: " << i << "/" << (std::min(Nsig,stopPoint)/sample)   << endl;


                for (int n=min; n < max; ++n) {
                hits->GetEntry(n);
                ToF[n] = abs(LGAD2_t - LGAD1_t);
                //cout << ToF[n] << " : " << LGAD1_t << " : " << LGAD2_t << " : " << endl;
                        switch (addError)
                        {
                        case 'y':
                            //cout << "add in gaussian error" << endl;
                            tErr = distribution(generator);
                            ToF[n] = ToF[n] + tErr;
                            //cout << tErr << endl;
                            break;
                        }

                if((LGAD1_t == 0) || (LGAD2_t == 0) ){        
                ToF[n] = 0;
                check = n;
                }              
                }
       
    }
//                cout << ToF[check] << endl;
  
  return ToF;
}


vector<double> getDist (string fileName, int stopPoint)
{

      double LGAD1_x, LGAD1_y, LGAD1_z;
      double LGAD2_x, LGAD2_y, LGAD2_z;


      cout << "Filename: " << fileName << endl;
      cout << "ToF distance calculated in mm" <<endl;

    TFile *g = new TFile(fileName.c_str(),"read");
    TTree *hits      = (TTree*) g->Get("hits");
    int Nsig = hits->GetEntries();
    int sample = std::min(Nsig,stopPoint)/10;

        hits->SetBranchAddress("LGAD1_x", &LGAD1_x);
        hits->SetBranchAddress("LGAD1_y", &LGAD1_y);
        hits->SetBranchAddress("LGAD1_z", &LGAD1_z);

        hits->SetBranchAddress("LGAD2_x", &LGAD2_x);
        hits->SetBranchAddress("LGAD2_y", &LGAD2_y);
        hits->SetBranchAddress("LGAD2_z", &LGAD2_z);



    cout << "distance function works " << endl;
    vector<double> d(std::min(Nsig,stopPoint),0);

//    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//    // fill loop
    int min;
    int max;


    for (int i=0; i <std::min(Nsig/sample,stopPoint/sample); ++i){
    min = i*sample;
    max = i*sample + (sample -1);
    cout << "distance input: " << i << "/" << (std::min(Nsig,stopPoint)/sample)   << endl;


                for (int n=min; n < max; ++n) {
                hits->GetEntry(n);
                d[n] = sqrt( pow((LGAD2_x - LGAD1_x),2)  +   pow((LGAD2_y - LGAD1_y),2)  +   pow((LGAD2_z - LGAD1_z),2));
                //cout << "d, z1, z2   " << d[n] << " : " << LGAD1_z << " : " << LGAD2_z << endl;

                  if((LGAD1_z == 0 ) || (LGAD2_z == 0)){
                    d[n] = 0;
                //cout << "BAD hit removed   " << d[n] << " : " << LGAD1_z << " : " << LGAD2_z << endl;                    
                  } 

                }
        
    }

  
  return d;
}


vector<double> getTheta(string fileName, int stopPoint, double Errx1,double Erry1,double Errx2,double Erry2,double Errx3,double Erry3)
{
//if( (Errx1 > 0)){
  std::default_random_engine generator;
  std::normal_distribution<double> distribution_x1(0,Errx1/1000);
  std::normal_distribution<double> distribution_y1(0,Erry1/1000);
  std::normal_distribution<double> distribution_x2(0,Errx2/1000);
  std::normal_distribution<double> distribution_y2(0,Erry2/1000);
  std::normal_distribution<double> distribution_x3(0,Errx3/1000);
  std::normal_distribution<double> distribution_y3(0,Erry3/1000);  
//}


      double HVCMOS_x, HVCMOS_y, HVCMOS_z;
      double LGAD1_x, LGAD1_y, LGAD1_z;
      double LGAD2_x, LGAD2_y, LGAD2_z;

      double x1, y1, x2, y2, x3, y3;




      cout << "Filename: " << fileName << endl;
      cout << "Theta distance calculated in degrees" <<endl;

    TFile *g = new TFile(fileName.c_str(),"read");
    TTree *hits      = (TTree*) g->Get("hits");
    int Nsig = hits->GetEntries();
    int sample = std::min(Nsig,stopPoint)/10;



        hits->SetBranchAddress("HVCMOS_x", &HVCMOS_x);
        hits->SetBranchAddress("HVCMOS_y", &HVCMOS_y);
        hits->SetBranchAddress("HVCMOS_z", &HVCMOS_z);

        hits->SetBranchAddress("LGAD1_x", &LGAD1_x);
        hits->SetBranchAddress("LGAD1_y", &LGAD1_y);
        hits->SetBranchAddress("LGAD1_z", &LGAD1_z);

        hits->SetBranchAddress("LGAD2_x", &LGAD2_x);
        hits->SetBranchAddress("LGAD2_y", &LGAD2_y);
        hits->SetBranchAddress("LGAD2_z", &LGAD2_z);



    cout << "distance function works " << endl;
    vector<double> theta(std::min(Nsig,stopPoint),0);
    double r;

//    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//    // fill loop
    int min;
    int max;


    for (int i=0; i <std::min(Nsig/sample,stopPoint/sample); ++i){
    min = i*sample;
    max = i*sample + (sample -1);

        if((verbose ==1)){
        cout << "Theta input: " << i << "/" << (std::min(Nsig,stopPoint)/sample)   << endl;
        }

                for (int n=min; n < max; ++n) {
                hits->GetEntry(n);
                if( (Errx1 > 0)){
                    x1 = HVCMOS_x + distribution_x1(generator);
                    y1 = HVCMOS_y + distribution_y1(generator);
                    x2 = LGAD1_x + distribution_x2(generator);
                    y2 = LGAD1_y + distribution_y2(generator);
                    x3 = LGAD2_x + distribution_x3(generator);
                    y3 = LGAD2_y + distribution_y3(generator);
                }
                else {
                  x1 = HVCMOS_x;
                  y1 = HVCMOS_y;
                  x2 = LGAD1_x;
                  y2 = LGAD1_y;                  
                  x3 = LGAD2_x;
                  y3 = LGAD2_y;
                }

                //r = sqrt( pow((LGAD2_x - LGAD1_x),2)  +   pow((LGAD2_y - LGAD1_y),2) );
                r = sqrt( pow((x3 - x2),2)  +   pow((y3 - y2),2) );                
                theta[n] = (180/PI)*atan(r/(LGAD2_z-LGAD1_z));
                //cout << theta[n] << endl;
                //d[n] = sqrt( pow((LGAD_E2_x - LGAD_E1_x),2)  +   pow((LGAD_E2_y - LGAD_E1_y),2)  +   pow((LGAD_E2_z - LGAD_E1_z),2));
                }
        
    }

  
  return theta;
}


vector<double> getE (vector<double> ToF , vector<double> d, int stopPoint)
{

    

    int Nsig = ToF.size();
    int sample = std::min(Nsig,stopPoint)/10;

    cout << "Caluclating E in MeV" << endl;
    vector<double> E(std::min(Nsig,stopPoint),0);
    vector<double> KE(std::min(Nsig,stopPoint),0);    
    vector<double> p(std::min(Nsig,stopPoint),0);  
    vector<double> v(std::min(Nsig,stopPoint),0);  
    double beta;



//    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//    // fill loop
    int min;
    int max;


    for (int i=0; i <std::min(Nsig/sample,stopPoint/sample); ++i){
    min = i*sample;
    max = i*sample + (sample -1);
    cout << "E calculation: " << i << "/" << (std::min(Nsig,stopPoint)/sample)   << endl;


                for (int n=min; n < max; ++n) {
                  
                    beta = (d[n]/(ToF[n]/1000000000))/c;
	                p[n] = sqrt(M*M*pow(beta,2)/(1-pow(beta,2)));
	                E[n] = sqrt((p[n]*p[n]) + (M*M)) - M;      
                  
                  v[n] = d[n]/(ToF[n]/1000000000);
                  KE[n] = (0.5 * (M) * (v[n]*v[n]))/pow(c,2);

                   //cout << "d, tof, v , KE, p, E, beta " << d[n] << " : " << ToF[n] << " : " << v[n] << " : " << KE[n] << " : "<< p[n] << " : " << E[n] <<  " : " << beta << endl;
                if((ToF[n] = 0 ) || (d[n] = 0)){
                  E[n] = 0;
                  
                }
                }
        
    }

  
  return E;
}




vector<double> getp (vector<double> ToF , vector<double> d, int stopPoint)
{

    

    int Nsig = ToF.size();
    int sample = std::min(Nsig,stopPoint)/10;

    cout << "Caluclating p in MeV/c" << endl;
  
    vector<double> p(std::min(Nsig,stopPoint),0);  

    double beta;



//    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//    // fill loop
    int min;
    int max;


    for (int i=0; i <std::min(Nsig/sample,stopPoint/sample); ++i){
    min = i*sample;
    max = i*sample + (sample -1);
    cout << "p calculation: " << i << "/" << (std::min(Nsig,stopPoint)/sample)   << endl;


                for (int n=min; n < max; ++n) {
                  
                    beta = (d[n]/(ToF[n]/1000000000))/c;
	                p[n] = sqrt(M*M*pow(beta,2)/(1-pow(beta,2)));

                  
                 }
        
    }

  
  return p;
}




vector<double> doCuts (char output,vector<double> EDEP, vector<double> KE, vector<double> E, vector<double> theta, vector<double> phi, double thetaMin, double thetaMax, double Emin, double Emax)
{

vector<double> output_vec;
output_vec.resize(E.size());
int vecCount = 0;

//cout << "docuts started " << endl;

for (int n = 0; n < E.size(); n++)
{
//cout << "loop started " << endl;
        if( (isnan(theta[n]))  || (isnan(E[n])) ){

        //    cout << "bad event" << endl;
        }
        else{
                    if((theta[n] < thetaMax) && (theta[n] > thetaMin) && (E[n] < Emax) && (E[n] > Emin))
                    {
                            //cout << Emin << " : " << E[n] << endl;
                            //output_vec[vecCount] = theta[n];
                            switch (output)
                            {
                            case 't': 
                            output_vec[vecCount] = theta[n]; 
                            break;
                            case 'E': 
                            output_vec[vecCount] = E[n]; 
                            break;   
                            case  'p': 
                            output_vec[vecCount] = phi[n]; 
                            break;  
                            case  'd': 
                            output_vec[vecCount] = EDEP[n]; 
                            break;  
                            case  'k': 
                            output_vec[vecCount] = KE[n]; 
                            break;  


                            }
                            vecCount++;
                    }
                    else
                    { 
                        //cout << "condition not met" << endl;
                    }


        }

}


output_vec.erase(    std::remove(output_vec.begin(), output_vec.end(), 0),      output_vec.end());

cout << "removed " << E.size() - vecCount << " events" << endl;

//output_vec.shrink_to_fit();
return output_vec;
}

vector<double> getPhi (string fileName, int stopPoint, double Errx1,double Erry1,double Errx2,double Erry2,double Errx3,double Erry3)
{
//cout << "get Phi assumes a 0 position of scattering" << endl;

//if( (Errx1 > 0)){
  std::default_random_engine generator;
  std::normal_distribution<double> distribution_x1(0,Errx1/1000);
  std::normal_distribution<double> distribution_y1(0,Erry1/1000);
  std::normal_distribution<double> distribution_x2(0,Errx2/1000);
  std::normal_distribution<double> distribution_y2(0,Erry2/1000);
  std::normal_distribution<double> distribution_x3(0,Errx3/1000);
  std::normal_distribution<double> distribution_y3(0,Erry3/1000);  
//}


      double HVCMOS_x, HVCMOS_y, HVCMOS_z;
      double LGAD1_x, LGAD1_y, LGAD1_z;
double x1, y1, x2, y2, x3, y3;

      cout << "Filename: " << fileName << endl;
      cout << "Phi angle calculated in degrees" <<endl;

    TFile *g = new TFile(fileName.c_str(),"read");
    TTree *hits      = (TTree*) g->Get("hits");
    int Nsig = hits->GetEntries();
    int sample = std::min(Nsig,stopPoint)/10;

        hits->SetBranchAddress("HVCMOS_x", &HVCMOS_x);
        hits->SetBranchAddress("HVCMOS_y", &HVCMOS_y);


    vector<double> phi(std::min(Nsig,stopPoint),0);

//    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//    // fill loop
    int min;
    int max;


    for (int i=0; i <std::min(Nsig/sample,stopPoint/sample); ++i){
    min = i*sample;
    max = i*sample + (sample -1);
    cout << "phi input: " << i << "/" << (std::min(Nsig,stopPoint)/sample)   << endl;


                for (int n=min; n < max; ++n) {
                hits->GetEntry(n);


                if( (Errx1 > 0)){
                    x2 = HVCMOS_x + distribution_x1(generator);
                    y2 = HVCMOS_y + distribution_y1(generator);
                    x1 = LGAD1_x + distribution_x2(generator);
                    y1 = LGAD1_y + distribution_y2(generator);
                    // x3 = LGAD2_x + distribution_x3(generator);
                    // y3 = LGAD2_y + distribution_y3(generator);
                }
                else {
                  x2 = HVCMOS_x;
                  y2 = HVCMOS_y;
                  x1 = LGAD1_x;
                  y1 = LGAD1_y;                  
                  // x3 = LGAD2_x;
                  // y3 = LGAD2_y;
                }




                //phi[n] = (180/PI)*atan(LGAD1_y/LGAD1_x);
                phi[n] = (180/PI)*atan(y2/x2);               
                //cout << "x : Y : phi" << LGAD_E1_x << " : " << LGAD_E1_y << " : " << phi[n] << endl;



                  if((x2 > 0) && (y2 > 0)){
                    phi[n] = 90 - phi[n];
                  //  cout << "top right" << endl;
                  }
                  else if ((x2 >0) && (y2 < 0)){
                    phi[n] = 90 - phi[n];
                  //  cout << "bottom right" << endl;                  
                  }
                  else if ((x2 <0) && (y2 < 0)){
                    phi[n] =  270 - phi[n];
                 //   cout << "bottom left" << endl;
                  }
                  else if ((x2 < 0) && (y2 > 0)){
                    phi[n] =  270 - phi[n];
                  //  cout << "top left" << endl;
                  }
                  else {
                //  cout << "x, y, phi  " << LGAD_E1_x << " : " << LGAD_E1_y << " : " << phi[n] << endl;      
                 // cout << "ERRRROOOOORRRR" << endl;
                  phi[n] = 0;
                  }


                //cout << "x : Y : phi" << LGAD_E1_x << " : " << LGAD_E1_y << " : " << phi[n] << endl;



                }
        
    }

  
  return phi;
}



double getAsym(vector<double> phi, char type){
int upCount = 0;
int rightCount = 0;
int leftCount = 0;
int downCount = 0;
int anyCount = 0;

for (int i = 0; i < phi.size(); i++)
{
            if ((phi[i] > 315) || ( phi[i] < 45))
            {
                upCount++;
            }
            else if ((phi[i] > 45) && ( phi[i] < 135))
            {
                rightCount++;
            }   
            else if ((phi[i] > 135) && ( phi[i] < 225))
            {
                downCount++;
            }
            else if ((phi[i] > 225) && ( phi[i] < 315))
            {
                leftCount++;
            }
            anyCount++;
}




double asym;

switch (type)
{
case 'x':
    asym = ((double)rightCount - (double)leftCount)  /  ((double)rightCount + (double)leftCount);
    break;

case 'y':
    asym = ((double)upCount - (double)downCount)  /  ((double)upCount + (double)downCount);
    break;

}

//cout << "ASYM: " << asym << "  " << anyCount << " Counts" << endl; 
return asym;
}







double getAsymErr(vector<double> phi, char type){
int upCount = 0;
int rightCount = 0;
int leftCount = 0;
int downCount = 0;
int anyCount = 0;

for (int i = 0; i < phi.size(); i++)
{
            if ((phi[i] > 315) || ( phi[i] < 45))
            {
                upCount++;
            }
            else if ((phi[i] > 45) && ( phi[i] < 135))
            {
                rightCount++;
            }   
            else if ((phi[i] > 135) && ( phi[i] < 225))
            {
                downCount++;
            }
            else if ((phi[i] > 225) && ( phi[i] < 315))
            {
                leftCount++;
            }
            anyCount++;
}


//Scale factor

upCount = upCount * 1;
downCount = downCount * 1;
leftCount = leftCount * 1;
rightCount = rightCount * 1;



double asym;
double asymErr;
double numer, denom;
double uErr;
switch (type)
{
case 'x':
numer = (double)rightCount - (double)leftCount;
denom = (double)rightCount + (double)leftCount;

    asym = ((double)rightCount - (double)leftCount)  /  ((double)rightCount + (double)leftCount);
uErr = sqrt(pow(sqrt((double)rightCount),2) + pow(sqrt((double)leftCount),2));
asymErr = abs(asym * sqrt(  pow(   (uErr/numer)   ,2)    +     pow(   (uErr/denom)  ,2)           ));
    break;

case 'y':

numer = (double)upCount - (double)downCount;
denom = (double)upCount + (double)downCount;

    asym = ((double)upCount - (double)downCount)  /  ((double)upCount + (double)downCount);
uErr = sqrt(pow(sqrt((double)upCount),2) + pow(sqrt((double)downCount),2));
asymErr = abs(asym* sqrt(  pow(   (uErr/numer)   ,2)    +     pow(   (uErr/denom)  ,2)           ));

//cout << numer << " : " << denom << " : " << uErr << " : " << asym << " : " << asymErr << endl; 
    break;

}
cout << " L/R  " << leftCount << ", " << rightCount << endl;
cout << " U/D  " << upCount << ", " << downCount << endl;
cout << numer << " : " << denom << " : " << uErr << " : " << asym << endl;
cout << "asym, total L-R-U-D counts and error: " << asym << ", " << anyCount << ", " << asymErr << endl; 

return asymErr;
}















TH1D * plotHistVec(vector<double> vec, double minLim, double maxLim, int bins, string xlabel, string ylabel, string title, string canvName){
  TH1D *hist = new TH1D(canvName.c_str()," Layer 1 " , bins, minLim , maxLim );
   cout << "Filling Histogram " << endl;


 int len =  vec.size();
 int sample = len/10;
 int min, max;
 cout << " Len: " <<  len << endl;
 
      for (int i=0; i < len/sample; ++i){
            min = i*sample;
            max = i*sample + (sample -1);
            cout << "Vector into hist: " << i << "/" << len/sample  << endl;

            for (int n=min; n < max; ++n) { hist->Fill(vec[n]); }
     }


      TCanvas *canv = new TCanvas(canvName.c_str(),"Energy",200,10,500,500);
gStyle->SetOptStat(1111111);
canv->Draw("hist");
canv->SetLogy();
hist->Draw("colz");
 hist->SetTitle(title.c_str());

 hist->GetXaxis()->SetTitle(xlabel.c_str());
 hist->GetYaxis()->SetTitle(ylabel.c_str());
//f.Write();


   return hist;
}



TH2D * plot2DHistVec(vector<double> vec1,vector<double> vec2, double minLimX, double maxLimX, int binsX,  double minLimY, double maxLimY, int binsY,string xlabel, string ylabel, string title, string canvName){
  TH2D *hist = new TH2D(canvName.c_str(),"  " , binsX, minLimX , maxLimX , binsY, minLimY , maxLimY );
   cout << "Filling Histogram " << endl;


 int len =  vec1.size();
 int sample = len/10;
 int min, max;
 cout << " Len: " <<  len << endl;
 
      for (int i=0; i < len/sample; ++i){
            min = i*sample;
            max = i*sample + (sample -1);
            cout << "Vector into hist: " << i << "/" << len/sample  << endl;

            for (int n=min; n < max; ++n) { hist->Fill(vec1[n],vec2[n]); }
     }


      TCanvas *canv = new TCanvas(canvName.c_str(),"Energy",200,10,500,500);
gStyle->SetOptStat(1111111);
canv->Draw("hist");
//canv->SetLogy();
hist->Draw("colz");
 hist->SetTitle(title.c_str());

 hist->GetXaxis()->SetTitle(xlabel.c_str());
 hist->GetYaxis()->SetTitle(ylabel.c_str());
//f.Write();


   return hist;
}
