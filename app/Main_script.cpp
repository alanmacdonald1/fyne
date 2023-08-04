#include <stdio.h> 
#include <stdlib.h> 
#include <R.h> 
  

#include <Rmath.h> 
#include <iostream>
#include <string>
using namespace std;
#include <math.h>       /* exp */

#include "CONSTANTS.h"

// timestep is currently 1 day, ODE is solved using the Euler method 


 
  


// EXPORT = CONCENTRATION IN BOX *(1-PROB IT STAYS THERE)


	/**************/
	/* Variables */
	/**************/

extern "C" {double ECOSYSTEM_MODEL(	
	double PARAMETERS[NO_PARAS]
	) 
{
	
 

	/* there are 7 boxes  */
	
	int Boxes = 7 ; 
	
	
	
	double H[Boxes]; 
	memset( H, 0, Boxes*sizeof(double) );
 
	
	double Area[Boxes]; 
	memset( Area, 0, Boxes*sizeof(double) );
 
	double Volume[Boxes]; 
	memset( Volume, 0, Boxes*sizeof(double) ); 
 
		H[0] = H0 ; 
		H[1] = H1 ; 
		H[2] = H2 ; 
		H[3] = H3 ; 
		H[4] = H4 ; 
		H[5] = H5 ; 
		H[6] = H6 ; 

		
		Area[0] = Area0 ; 
		Area[1] = Area1 ; 
		Area[2] = Area2 ; 
		Area[3] = Area3 ; 
		Area[4] = Area4 ; 
		Area[5] = Area5 ; 
		Area[6] = Area6 ; 

 
		Volume[0] = Volume0 ; 
		Volume[1] = Volume1 ; 
		Volume[2] = Volume2 ; 
		Volume[3] = Volume3 ; 
		Volume[4] = Volume4 ; 
		Volume[5] = Volume5 ; 
		Volume[6] = Volume6 ; 

 
 
		double F[3][Boxes]; // Energy (J)
		memset( F, 0, 3*Boxes*sizeof(double) );
		
	


		double fish_feces[Boxes]; //Pelagic non-plankton organic carbon (mgC m−3)
		memset( fish_feces, 0, Boxes*sizeof(double) );
		
		
 		 	
			 
double POC_salmon_feces[Boxes]; //Pelagic non-plankton organic carbon (mgC m−3)
memset( POC_salmon_feces, 0, Boxes*sizeof(double) );
double PON_salmon_feces[Boxes]; //Pelagic non-plankton organic nitrogen (mgN m−3)
memset( PON_salmon_feces, 0, Boxes*sizeof(double) );
		
double POC_salmon_feed[Boxes]; //Pelagic non-plankton organic carbon (mgC m−3)
memset( POC_salmon_feed, 0, Boxes*sizeof(double) );
double PON_salmon_feed[Boxes]; //Pelagic non-plankton organic nitrogen (mgN m−3)
memset( PON_salmon_feed, 0, Boxes*sizeof(double) );
		
		
double POC_non_salmon_feces[Boxes]; //Pelagic non-plankton organic carbon (mgC m−3)
memset( POC_non_salmon_feces, 0, Boxes*sizeof(double) );
double PON_non_salmon_feces[Boxes]; //Pelagic non-plankton organic nitrogen (mgN m−3)
memset( PON_non_salmon_feces, 0, Boxes*sizeof(double) );
		
		
double POC_rate_change_non_salmon_feces;
double POC_rate_change_salmon_feces;
double POC_rate_change_salmon_feed ; 
		
double PON_rate_change_non_salmon_feces;
double PON_rate_change_salmon_feces;
double PON_rate_change_salmon_feed ; 
 
 
 
double POCmuss_non_salmon_feces[Boxes]; //Pelagic non-plankton organic nitrogen (mgN m−3)
memset( POCmuss_non_salmon_feces, 0, Boxes*sizeof(double) );
		
	
double POCmuss_salmon_feces[Boxes]; //Pelagic non-plankton organic nitrogen (mgN m−3)
memset( POCmuss_salmon_feces, 0, Boxes*sizeof(double) );
		
double POCmuss_rate_change_salmon_feces;
double POCmuss_rate_change_non_salmon_feces;	
		
		
 
		


     
	double E[3][Boxes]; // Energy (J)
	memset( E, 0, 3*Boxes*sizeof(double) );
	double E_R[3][Boxes]; // Reproductive energy (J)
	memset( E_R, 0, 3*Boxes*sizeof(double) );
	double V[3][Boxes]; // Biovolume (cm3)
	memset( V, 0, 3*Boxes*sizeof(double) );
	double N[3][Boxes]; // No. inds
	memset( N, 0, 3*Boxes*sizeof(double) );

	double CA[Boxes]; //Seaweed carbon (mgC m−3) 
	memset( CA, 0, Boxes*sizeof(double) );
	double NAs[Boxes]; //Seaweed nitrogen (mgN m−3) 
	memset( NAs, 0, Boxes*sizeof(double) );


  

	double CZ[Boxes]; //Zooplankton structure weight (mgC m−3)
	memset( CZ, 0, Boxes*sizeof(double) );
	double EZ[Boxes]; //Zooplankton reserves (mgC m−3)
	memset( EZ, 0, Boxes*sizeof(double) );
	
	double CP[Boxes]; //Phytoplankton carbon (mgC m−3)
	memset( CP, 0, Boxes*sizeof(double) );
	double NP[Boxes]; //Phytoplankton nitrogen (mgN m−3)
	memset( NP, 0, Boxes*sizeof(double) );
 	
	double POC[Boxes]; //Pelagic non-plankton organic carbon (mgC m−3)
	memset( POC, 0, Boxes*sizeof(double) );
	double PON[Boxes]; //Pelagic non-plankton organic nitrogen (mgN m−3)
	memset( PON, 0, Boxes*sizeof(double) );
	
	double ND[Boxes]; //Dissolved organic nitrogen (mgN m−3)
	memset( ND, 0, Boxes*sizeof(double) );
	
	double NH[Boxes]; //Ammonium nitrogen (mgN m−3)
	memset( NH, 0, Boxes*sizeof(double) );
	double NO[Boxes]; //Nitrate nitrogen (mgN m−3)
	memset( NO, 0, Boxes*sizeof(double) );
	
	double CS[Boxes]; //Sediment organic carbon (mgC m−2)
	memset( CS, 0, Boxes*sizeof(double) );
	double NS[Boxes]; //Sediment organic nitrogen (mgN m−2)
	memset( NS, 0, Boxes*sizeof(double) );
	
 
  
 

double ALA_COMP ;
double ARA_COMP ;
double EPA_COMP ;
double DHA_COMP ;
double DPA_COMP ;
double LIN_COMP ;
double OLA_COMP ;
double PAM_COMP ;


double ALA[Boxes]; 
memset( ALA, 0, Boxes*sizeof(double) );
double ARA[Boxes]; 
memset( ARA, 0, Boxes*sizeof(double) );
double EPA[Boxes]; 
memset( EPA, 0, Boxes*sizeof(double) );
double DHA[Boxes]; 
memset( DHA, 0, Boxes*sizeof(double) );
double LIN[Boxes]; 
memset( LIN, 0, Boxes*sizeof(double) );
  
 
  


double P_fat ; 
double P_NFE ; 
double P_fibre ; 
double P_phos ; 
double P_min  ; 


double P_fish_meal_protein_65   ; 
double P_fish_meal_protein_70 ;
double P_soybean_protein_concentrate_protein_70_90 ;
double  P_processed_animal_proteins_poultry_protein_70 ;
double P_whey_permeate ;
double P_Blood_meal ;
double P_wheat_gluten ;
double P_DL_methionine ;
double P_maize ;
double P_corn_gluten_meal;
double P_corn_gluten_feed ;
double P_Pea_protein_concentrate ;
double P_feather_meal ; 
double P_Potato_protein_concentrate ; 
 
 
int SalmonStart ; 
int SalmonEnd ; 
int MusselStart ; 
int MusselEnd ; 
int SeaweedStart ; 
int SeaweedEnd ; 

 
  
 
 
	// Secondary
	double W[3][Boxes]; // Wet weight (g)
	double L[3][Boxes]; // Length (cm)
	
	double B[3][Boxes]; // Biomass (tonnes)
	memset( B, 0, 3*Boxes*sizeof(double) );
	
	
	
	double FEED; // Feed 
	double T; // Temperature 
	
 	
 
	 
	
	
	for( int box = 0; box < Boxes; box++)
	{
		
			E[0][box] = PARAMETERS[box] ;  
			E[1][box] = PARAMETERS[box+Boxes] ;  
			E[2][box] = PARAMETERS[box+2*Boxes] ;
			E_R[0][box] = PARAMETERS[box+3*Boxes] ;
			E_R[1][box] = PARAMETERS[box+4*Boxes] ;
			E_R[2][box] = PARAMETERS[box+5*Boxes] ;
			V[0][box] = PARAMETERS[box+6*Boxes] ;
			V[1][box] = PARAMETERS[box+7*Boxes] ;
			V[2][box] = PARAMETERS[box+8*Boxes] ;
			N[0][box] = PARAMETERS[box+9*Boxes] ;
			N[1][box] = PARAMETERS[box+10*Boxes] ;
			N[2][box] = PARAMETERS[box+11*Boxes] ;
			CA[box] = PARAMETERS[box+12*Boxes] ;
			NAs[box] = PARAMETERS[box+13*Boxes] ;
			
			
		
		CZ[box] = PARAMETERS[box+14*Boxes] ;
	    EZ[box] = PARAMETERS[box+15*Boxes] ;
		CP[box] =PARAMETERS[box+16*Boxes] ;
		NP[box] = PARAMETERS[box+17*Boxes] ;
		POC[box] =PARAMETERS[box+18*Boxes] ;
		PON[box] = PARAMETERS[box+19*Boxes]  ;
	    ND[box] = PARAMETERS[box+20*Boxes] ;
		NH[box] = PARAMETERS[box+21*Boxes] ;
		NO[box] = PARAMETERS[box+22*Boxes] ;
		CS[box] = PARAMETERS[box+23*Boxes] ;
		NS[box] = PARAMETERS[box+24*Boxes] ;
			
		W[0][box] = PARAMETERS[box+25*Boxes] ;
		W[1][box] = PARAMETERS[box+26*Boxes] ;
		W[2][box] = PARAMETERS[box+27*Boxes] ;
		L[0][box] = PARAMETERS[box+28*Boxes] ;
		L[1][box] = PARAMETERS[box+29*Boxes] ;
		L[2][box] = PARAMETERS[box+30*Boxes] ;
			
	}



 
 
	ALA_COMP = PARAMETERS[31*Boxes] ;
	ARA_COMP = PARAMETERS[31*Boxes+1] ;
	EPA_COMP = PARAMETERS[31*Boxes+2]; 
	DHA_COMP = PARAMETERS[31*Boxes+3];
	DPA_COMP = PARAMETERS[31*Boxes+4];
	LIN_COMP = PARAMETERS[31*Boxes+5];
	OLA_COMP = PARAMETERS[31*Boxes+6];
	PAM_COMP = PARAMETERS[31*Boxes+7];
	 
	 
	
		 
	// Proportions of macronutrients
	 
	P_fat = PARAMETERS[31*Boxes+8];
	P_NFE = PARAMETERS[31*Boxes+9];
	P_fibre = PARAMETERS[31*Boxes+10];
	P_phos = PARAMETERS[31*Boxes+11];
	P_min = PARAMETERS[31*Boxes+12];
	
 
	
	
	
	P_fish_meal_protein_65 = PARAMETERS[31*Boxes+13];
	P_fish_meal_protein_70 = PARAMETERS[31*Boxes+14];
	P_soybean_protein_concentrate_protein_70_90 = PARAMETERS[31*Boxes+15];
	P_processed_animal_proteins_poultry_protein_70 = PARAMETERS[31*Boxes+16];
	P_whey_permeate = PARAMETERS[31*Boxes+17];
	P_Blood_meal = PARAMETERS[31*Boxes+18];
	P_wheat_gluten = PARAMETERS[31*Boxes+19];
	P_DL_methionine =PARAMETERS[31*Boxes+20];
	P_maize = PARAMETERS[31*Boxes+21];
	P_corn_gluten_meal =PARAMETERS[31*Boxes+22];
	P_corn_gluten_feed = PARAMETERS[31*Boxes+23];
	P_Pea_protein_concentrate = PARAMETERS[31*Boxes+24];
	P_feather_meal = PARAMETERS[31*Boxes+25];
	P_Potato_protein_concentrate = PARAMETERS[31*Boxes+26];
	
	SalmonStart = PARAMETERS[31*Boxes+27];
	MusselStart = PARAMETERS[31*Boxes+28];
	SeaweedStart = PARAMETERS[31*Boxes+29];
	  
	SalmonEnd = PARAMETERS[31*Boxes+30];
	MusselEnd = PARAMETERS[31*Boxes+31];
	SeaweedEnd = PARAMETERS[31*Boxes+32];
	
 
  	
	int TRANSPORT_LENGTH0 = 63 ; 
	
	
	double TRANSPORT[MaxDays*5*TRANSPORT_LENGTH0]; 	
   	
	for( int NUM = 0; NUM < MaxDays*5*TRANSPORT_LENGTH0; NUM++)
	{
	
	TRANSPORT[NUM] = PARAMETERS[5*MaxDays+NUM+31*Boxes+33] ; 
	
  
}

 
 
 
 
double background_plankton0 ; 
double background_NH0 ; 
double background_NO0 ; 
double background_DON0 ; 
double background_POC0 ; 
double background_zoo0 ; 

double background_plankton[MaxDays] ;
double background_NH[MaxDays] ;
double background_NO[MaxDays] ;
double background_DON[MaxDays] ;
double background_POC[MaxDays] ; 	
double background_zoo[MaxDays] ; 	


 

	
	for( int NUM = 0; NUM < MaxDays; NUM++)
	{
	background_plankton[NUM] = PARAMETERS[5*MaxDays+NUM+31*Boxes+33 + MaxDays*5*TRANSPORT_LENGTH0 ] ; 
	background_NH[NUM] = PARAMETERS[6*MaxDays+NUM+31*Boxes+33 + MaxDays*5*TRANSPORT_LENGTH0 ] ; 
	background_NO[NUM] = PARAMETERS[7*MaxDays+NUM+31*Boxes+33 + MaxDays*5*TRANSPORT_LENGTH0 ] ; 
	background_DON[NUM] = PARAMETERS[8*MaxDays+NUM+31*Boxes+33 + MaxDays*5*TRANSPORT_LENGTH0 ] ; 
	background_POC[NUM] = PARAMETERS[9*MaxDays+NUM+31*Boxes+33 + MaxDays*5*TRANSPORT_LENGTH0 ] ; 
	background_zoo[NUM] = PARAMETERS[10*MaxDays+NUM+31*Boxes+33 + MaxDays*5*TRANSPORT_LENGTH0 ] ; 


}

  
 


double CP_rate_change ;
double NP_rate_change ;
double CZ_rate_change ;
double EZ_rate_change ;
double POC_rate_change ;
double PON_rate_change ;
double NH_rate_change ;
double ND_rate_change ;
double NO_rate_change ;
 
double NS_rate_change ;
double CS_rate_change ;
 
  
	// dietary carbon (C) is lipids with a percentage of 77.6, followed by proteins and carbohydrates, with 52.9 and 44.4 %, respectively (Gnaiger and Bitterlich 1984), 
	
		
	// 0 for salmon, 1 for mussels, 2 for cucumber, 3 for seaweed, 4 for phytoplankton, 5 for zooplankton 
	
	/**************/
	/* Functions */
	/**************/

	// Cultured species functions
	double func_response[3]; // functional response (Dimensionless)
	double Temp_effect[6]; //Temperature-dependent rate of biological group (Dimensionless)
	
	
	double P_A[3]; // Assimilation rate (J d-1)
	double P_C[3]; //Catabolic rate (J d-1)
	double P_M[3]; // Maintenance rate (J d-1)
	double P_J[3]; //Maturity maintenance (J d-1)
	//double F[3]; //Faeces (mg C d-1)
	double M[3]; //C loss (mortality) of biological group (mg C d-1)
 	

	double U_f; // 
	double C_f; //  
	double A_f; //  
	 
	
	double U_mp; // Consumption rate of phytoplankton by mussels (mgC d−1)
	double U_mo; // Consumption rate of POC by mussels (mgC d−1)
	double U_d; // Consumption rate of sea cucumber (mgC d−1)
	
	
	
	double F_w; // Waste feed (mgC d−1)
	double F_excr; // Fish excretion (mgN d−1)
	double M_excr; // Shellfish excretion (mgN d−1)
	double D_excr; // Sea cucumber excretion (mgN d−1)

	
	
	double U_nha; //  Potential uptake of ammonium N by seaweed (d−1)
	double U_noa; //  Potential uptake of nitrate N by seaweed (d−1)
	double U_ca; // Uptake of C by seaweed (mgC d−1)
	double U_na; // Total uptake of N by seaweed (mgN d−1)
	double A_excr; // Seaweed excretion (mgN d−1)
	double W_a ;  // Seaweed biomass (kg m−3)
	
	double Q_s;  /* Sediment N quota */
	
	double Q_p;	 // Phytoplankton N quota (mgN mgC−1)

	double U_nhp; //Potential uptake of NH4 by phytoplankton (d-1)	
	double U_nop; //Potential uptake of NO3 by phytoplankton (d-1)
	double U_np; //Total uptake of N by phytoplankton (mgN d−1)
    double U_cp; //Uptake of C by phytoplankton (mgC d-1)
    double P_excr; // Phytoplankton excretion (mgN d−1)
	double M_p; // Phytoplankton C sinking rate (mgC d−1)
	
	double U_zp; // Uptake of phytoplankton C by zooplankton (mgC d−1)
	double U_zo; // Uptake of POC by zooplankton (mgC d−1)
	double G_z; //Zooplankton growth rate (mgC d−1)
	double Z_f; // Zooplankton faeces (mgC d−1)
	double EZ_rho; // C loss rate of zooplankton reserves (mgN d−1)
	double CZ_rho; // C loss rate of zooplankton structure weight (mgN d−1)
	double Z_excr; // Zooplankton excretion (mgN d−1)
	double M_z; // Zooplankton mortality (mgC d-1)
	double W_z; // Zooplankton biomass (mgC m−3) 
 
	double f_L; // Irradiance effect on C uptake (dimensionless)
	double Lfunc; 
 
 
	double Ed;
 
   
    double ALA_INTAKE;
    double ARA_INTAKE ; 
    double EPA_INTAKE ; 
    double DHA_INTAKE; 
    double DPA_INTAKE ; 
    double LIN_INTAKE ; 
    double OLA_INTAKE ; 
    double PAM_INTAKE ; 
	
	
	double RateChangeSalmonWeight;
	
	double ala_beta_oxidation_g_g_fish_day; 
	double ala_transformation_g_g_fish_day;
	double ala_egestion_g_g_fish_day;
	
	double ara_beta_oxidation_g_g_fish_day; 
	double ara_egestion_g_g_fish_day;
	double ara_transformation_g_g_fish_day ; 
	
	double dha_beta_oxidation_g_g_fish_day ; 
	double dha_egestion_g_g_fish_day ; 
	double dha_transformation_g_g_fish_day ; 
	
	double epa_beta_oxidation_g_g_fish_day ; 
	double epa_egestion_g_g_fish_day ; 
	double epa_transformation_g_g_fish_day ; 
	
	
	double lin_beta_oxidation_g_g_fish_day ; 
	double lin_egestion_g_g_fish_day ; 
	double lin_transformation_g_g_fish_day ; 
	
	double DHA_EPA_ratio;
	double n3_n6_ratio ; 

	
	

  
/********************/


	static const char filename11[] = "prop_salmon_waste_in_mussel_diet.txt";
    FILE *file11 = fopen ( filename11, "w" );
	
	static const char filename99[] = "ModOutput.txt";
    FILE *file99 = fopen ( filename99, "w" );
	
	
	// Initial conditions
	
	
	/*  // initial salmon length = 19.615 cm, weight =  150 g ; V = delta_m^3 L^3 = 70.957944  ; E = 7730*(W-V) = 301795.09288 */
	
 

for( int box = 0; box < Boxes; box++)
{
	
	V[0][box] = pow(delta_mf,3)*pow(L[0][box],3);    //70.957944 ; // Initial biovolume (cm3) 
	E[0][box] = mu_Ef*(W[0][box] - V[0][box]) ; //301795.09288; // Initial energy content (J)
	E_R[0][box] = 0; // Initial reproductive reserves (J)
	
	/*  // initial mussel length = 2cm, weight =  .3 g ; V = delta_m^3 L^3 =   ; E = 7730*(W-V) =  */
	
	V[1][box] = pow(delta_mm,3)*pow(L[1][box],3);    //70.957944 ; // Initial biovolume (cm3) 
	E[1][box] = mu_Em*(W[1][box] - V[1][box]) ; //301795.09288; // Initial energy content (J)
	E_R[1][box] = 0; // Initial reproductive reserves (J)
	
	/*  // initial sea cucumber length = 2cm, weight =  .2 g ; V = delta_m^3 L^3 =   ; E = 7730*(W-V) =  */
	
	V[2][box] = pow(delta_md,3)*pow(L[2][box],3);    //70.957944 ; // Initial biovolume (cm3) 
	E[2][box] = mu_Ef*(W[2][box] - V[2][box]) ; //301795.09288; // Initial energy content (J)
	E_R[2][box] = 0; // Initial reproductive reserves (J)

}
	 
 
	double LIGHT_at_day = 0 ;
	
	
	// proportion of FAs in poo
	double SALMON_POO_ALA_PROP ;
	double SALMON_POO_ARA_PROP ;
	double SALMON_POO_DHA_PROP ;
	double SALMON_POO_EPA_PROP ;
	double SALMON_POO_LIN_PROP ;
	

 	
 
 	

	double largeparticles_salmon[Boxes];
	memset( largeparticles_salmon, 0, Boxes*sizeof(double) );
	
	double largeparticles_salmon_prop[Boxes];
	memset( largeparticles_salmon_prop, 0, Boxes*sizeof(double) );


	double smallparticles_prop[Boxes];
	memset( smallparticles_prop, 0, Boxes*sizeof(double) );
	
	double largeparticles_prop[Boxes];
	memset( largeparticles_prop, 0, Boxes*sizeof(double) );
	
	double toolargeparticles_prop[Boxes];
	memset( toolargeparticles_prop, 0, Boxes*sizeof(double) );
	
	double smallparticle_zoo = 1 ;
	double largeparticle_zoo = 0;
	double toolargeparticle_zoo = 0 ;
	
	double smallparticle_salmon = 6.158176e-04 ; 
	double largeparticle_salmon = 0.05691783 ; 
	
	double toolargeparticle_salmon =  0.94 ; 
 
	double smallparticles[Boxes];
	memset( smallparticles, 0, Boxes*sizeof(double) );  
	
	double largeparticles[Boxes];
	memset( largeparticles, 0, Boxes*sizeof(double) );  
 
	double toolargeparticles[Boxes];
	memset( toolargeparticles, 0, Boxes*sizeof(double) );  
 
 
	double POCmuss[Boxes];
	memset( POCmuss, 0, Boxes*sizeof(double) );  
 
	
	
	
	double mantle_ALA_muss[Boxes];
	memset( mantle_ALA_muss, 0, Boxes*sizeof(double) );  
	
	double mantle_EPA_muss[Boxes];
	memset( mantle_EPA_muss, 0, Boxes*sizeof(double) );  
 
	double mantle_DHA_muss[Boxes];
	memset( mantle_DHA_muss, 0, Boxes*sizeof(double) );  
 
	double mantle_ARA_muss[Boxes];
	memset( mantle_ARA_muss, 0, Boxes*sizeof(double) );  
 
 	double mantle_LIN_muss[Boxes];
	memset( mantle_LIN_muss, 0, Boxes*sizeof(double) );  
	
	double gill_ALA_muss[Boxes];
	memset( gill_ALA_muss, 0, Boxes*sizeof(double) );  
	
	double gill_EPA_muss[Boxes];
	memset( gill_EPA_muss, 0, Boxes*sizeof(double) );  
 
	double gill_DHA_muss[Boxes];
	memset( gill_DHA_muss, 0, Boxes*sizeof(double) );  
 
	double gill_ARA_muss[Boxes];
	memset( gill_ARA_muss, 0, Boxes*sizeof(double) );  
 
 	double gill_LIN_muss[Boxes];
	memset( gill_LIN_muss, 0, Boxes*sizeof(double) );  
 
	double gland_ALA_muss[Boxes];
	memset( gland_ALA_muss, 0, Boxes*sizeof(double) );  
	
	double gland_EPA_muss[Boxes];
	memset( gland_EPA_muss, 0, Boxes*sizeof(double) );  
 
	double gland_DHA_muss[Boxes];
	memset( gland_DHA_muss, 0, Boxes*sizeof(double) );  
 
	double gland_ARA_muss[Boxes];
	memset( gland_ARA_muss, 0, Boxes*sizeof(double) );  
 
 	double gland_LIN_muss[Boxes];
	memset( gland_LIN_muss, 0, Boxes*sizeof(double) );  

 	
  	
 	
	double ALA_intake;	
	double ARA_intake ;
	double DHA_intake ; 
	double EPA_intake ; 
	double LIN_intake ; 
	
 
	 
   
	
	double Seaweed_ammonium_uptake ;  
	double Seaweed_nitrate_uptake ; 
	
	
	double CA_block ; 
	double f_L_seaweed ; 
 
	
	
	double asseff ;  // mussel AE 
	double asseff_poc ;  // mussel AE 
	double asseff_phyto ;  // mussel AE 
	
	
 	
	X_Hf = 26.02991 ; 
  	
 	
	      
	// MUSSEL FOOD
	
	double PROP_FOOD_SALMON_POO ; 
	double PROP_FOOD_ZOO ; 
	
	// carbon
	
	
	
double carbon_percentage ; 
	
carbon_percentage = 	(fish_meal_protein_65*P_fish_meal_protein_65*c_protein+
			fish_meal_protein_70*P_fish_meal_protein_70*c_protein+
				soybean_protein_concentrate_protein_70_90*P_soybean_protein_concentrate_protein_70_90*c_protein+
					processed_animal_proteins_poultry_protein_70*P_processed_animal_proteins_poultry_protein_70*c_protein+
						whey_permeate*P_whey_permeate*c_protein+
							Blood_meal*P_Blood_meal*c_protein+
								wheat_gluten*P_wheat_gluten*c_protein+
									DL_methionine*P_DL_methionine*c_protein+
										maize*P_maize*c_protein+
											corn_gluten_meal*P_corn_gluten_meal*c_protein+
												corn_gluten_feed*P_corn_gluten_feed*c_protein+
													Pea_protein_concentrate*P_Pea_protein_concentrate*c_protein+
														feather_meal*P_feather_meal*c_protein+
															Potato_protein_concentrate*P_Potato_protein_concentrate*c_protein+
																P_fat*c_fat+
																	P_NFE*c_NFE+
																		P_fibre*c_fibre +
																			P_phos*c_phos+
																				P_min*c_min) ; 
	
	
	
 
	
	
double ADC ; 
	
	
ADC = (ADC_fish_meal_protein_65*fish_meal_protein_65*P_fish_meal_protein_65*c_protein+
			ADC_fish_meal_protein_70*fish_meal_protein_70*P_fish_meal_protein_70*c_protein+
				ADC_soybean_protein_concentrate_protein_70_90*soybean_protein_concentrate_protein_70_90*P_soybean_protein_concentrate_protein_70_90*c_protein+
					ADC_processed_animal_proteins_poultry_protein_70*processed_animal_proteins_poultry_protein_70*P_processed_animal_proteins_poultry_protein_70*c_protein+
						ADC_whey_permeate*whey_permeate*P_whey_permeate*c_protein+
							ADC_Blood_meal*Blood_meal*P_Blood_meal*c_protein+
								ADC_wheat_gluten*wheat_gluten*P_wheat_gluten*c_protein+
									ADC_DL_methionine*DL_methionine*P_DL_methionine*c_protein+
										ADC_maize*maize*P_maize*c_protein+
											ADC_corn_gluten_meal*corn_gluten_meal*P_corn_gluten_meal*c_protein+
												ADC_corn_gluten_feed*corn_gluten_feed*P_corn_gluten_feed*c_protein+
													ADC_Pea_protein_concentrate*Pea_protein_concentrate*P_Pea_protein_concentrate*c_protein+
														ADC_feather_meal*feather_meal*P_feather_meal*c_protein+
															ADC_Potato_protein_concentrate*Potato_protein_concentrate*P_Potato_protein_concentrate*c_protein+
																ADC_fat*P_fat*c_fat+
																	ADC_NFE*P_NFE*c_NFE+
																		ADC_fibre*P_fibre*c_fibre +
																			ADC_phos*P_phos*c_phos+
																				ADC_min*P_min*c_min) ; 
	
	
double Ass_mult ; 


	Ass_mult =  (ADC_fish_meal_protein_65*fish_meal_protein_65*P_fish_meal_protein_65*j_protein+
				ADC_fish_meal_protein_70*fish_meal_protein_70*P_fish_meal_protein_70*j_protein+
					ADC_soybean_protein_concentrate_protein_70_90*soybean_protein_concentrate_protein_70_90*P_soybean_protein_concentrate_protein_70_90*j_protein+
						ADC_processed_animal_proteins_poultry_protein_70*processed_animal_proteins_poultry_protein_70*P_processed_animal_proteins_poultry_protein_70*j_protein+
							ADC_whey_permeate*whey_permeate*P_whey_permeate*j_protein+
								ADC_Blood_meal*Blood_meal*P_Blood_meal*j_protein+
									ADC_wheat_gluten*wheat_gluten*P_wheat_gluten*j_protein+
										ADC_DL_methionine*DL_methionine*P_DL_methionine*j_protein+
											ADC_maize*maize*P_maize*j_protein+
												ADC_corn_gluten_meal*corn_gluten_meal*P_corn_gluten_meal*j_protein+
													ADC_corn_gluten_feed*corn_gluten_feed*P_corn_gluten_feed*j_protein+
														ADC_Pea_protein_concentrate*Pea_protein_concentrate*P_Pea_protein_concentrate*j_protein+
															ADC_feather_meal*feather_meal*P_feather_meal*j_protein+
																ADC_Potato_protein_concentrate*Potato_protein_concentrate*P_Potato_protein_concentrate*j_protein+
																	ADC_fat*P_fat*j_fat+
																		ADC_NFE*P_NFE*j_NFE+
																			ADC_fibre*P_fibre*j_fibre +
																				ADC_phos*P_phos*j_phos+
																					ADC_min*P_min*j_min) ; 
 
 
	double Abundance_yesterday ; 
	double MORT_RATE ; 
	double HARVEST ; 
	 
 
	 
	
	for( int t = 0; t < MaxDays; t++)
	{
		
		
		
	/******************************/
	/*  Background concentrations */
	/******************************/	
		
		
	background_plankton0 = background_plankton[t] ; 
	background_NH0 = background_NH[t] ; 
	background_NO0 = background_NO[t] ; 
	background_DON0 = background_DON[t] ; 
	background_POC0 = background_POC[t] ; 
	background_zoo0 = background_zoo[t] ; 
	
	
 
		
		
	/********************/
	/*  Temperature */
	/********************/
		
	T = PARAMETERS[t+31*Boxes+33] ; 
		
 
		
	
	/********************/
	/*  Light */
	/********************/
	
	LIGHT_at_day = PARAMETERS[MaxDays+t+31*Boxes+33] ; 
	
 

	
	for( int box = 0; box < Boxes; box++)
	{
		
		
		
		// Irradiance effect on C uptake
		Lfunc =0 ;
		for(int DEPTH = 0; DEPTH < (H[box]+1); DEPTH++)
		{
			
			CA_block = 0 ; 
			if( DEPTH ==2) { CA_block = CA[box]*H[box]  ;  }
			
			Lfunc = Lfunc + (LIGHT_at_day*exp( - (k_back + k_p*(CP[box]+CA_block) )  *DEPTH ) ) / (LIGHT_at_day*exp( - (k_back + k_p*(CP[box]+CA_block) )  *DEPTH ) + X_l ) ; 
		}
		
		f_L = Lfunc/H[box] ;  
	
 
	
	// Irradiance effect on C uptake SEAWEED
		Lfunc =0 ;
		for(int DEPTH = 0; DEPTH < 2 ; DEPTH++)
		{
			Lfunc = Lfunc + (LIGHT_at_day*exp( - (k_back + k_p*(CP[box]) )  *DEPTH ) ) / (LIGHT_at_day*exp( - (k_back + k_p*(CP[box]) )  *DEPTH ) + X_l ) ; 
		}
		f_L_seaweed = Lfunc/2 ;  
		
		
	//	f_L = LIGHT_at_day ;
		
 
 
	
	
	/* Sediment N quota */
		Q_s = NS[box]/CS[box] ; 
		
		
/************************************/
/* Mortality - all cultured species */
/************************************/
		
		
		if(t< SalmonStart){N[0][box] = 0 ; }
		if(t==SalmonStart){ N[0][box] = PARAMETERS[box+9*Boxes] ; } 
			
		if(t>SalmonEnd){N[0][box] = 0 ; }
	
		if(t< SeaweedStart){CA[box] = 0 ; NAs[box] = 0 ; }
	    if(t==SeaweedStart){ CA[box] = PARAMETERS[box+12*Boxes] ;  NAs[box]= PARAMETERS[box+13*Boxes] ; } 
		
		if(t>SeaweedEnd){ CA[box] = 0 ; NAs[box] = 0 ; }
	
		if(t< MusselStart){N[1][box] = 0 ; }
	    if(t==MusselStart){ N[1][box] = PARAMETERS[box+10*Boxes] ; } 
		
		
		if(t>MusselEnd){N[1][box] = 0 ; }
	
		N[2][box] = N[2][box] - delta_rd*N[2][box] - delta_hd*N[2][box] ; 
 				
			
			
 
			
/********************/
/* Phytoplankton model */
/********************/
		
		 // Phytoplankton N quota (mgN mgC−1)
		Q_p = NP[box]/CP[box] ;	
		
		// Temperature effect on Phytoplankton rates	(checked)
		Temp_effect[4] = k_0*exp( (T_Ap/T_0p) -  (T_Ap/T) )* ( 1/ (1 + exp(  (T_ALp/T) -  (T_ALp/T_Lp) ) + exp(  (T_AHp/T_Hp) - (T_AHp/T)   )  ) )  ;
		
		//Potential uptake of NH4 by phytoplankton (checked)
		U_nhp = U_nhmp*(NH[box]/ (NH[box]+X_pnh) ) ;   
		
		//Potential uptake of NO3 by phytoplankton (checked)
		U_nop = U_nomp*(NO[box]/ (NO[box]+X_pno) ) ; 
		
		//Total uptake of N by phytoplankton
		U_np = (   NP[box]*Temp_effect[4]*(U_nhp+U_nop) )  / (     1 + exp(  (Q_p - Q_pmax)/Q_poff  ) ) ; 
		
		
		//Uptake of C by phytoplankton (mgC d-1)
		  U_cp = f_L*CP[box]*Temp_effect[4]*G_pm* std::max<double>(0,(1- (Q_pmin/Q_p) ) ) ; 
		
		   // U_cp = f_L*CP[box]*G_pm* std::max<double>(0,(1- (Q_pmin/Q_p) ) ) ; 
		
		
		//Phytoplankton excretion (mgN d−1)
		P_excr = (e_up*U_np) + (r_p*Temp_effect[4]*CP[box]*Q_p) ; 
		
		// Phytoplankton C sinking rate (mgC d−1)
		M_p = CP[box]*(delta_pmin + delta_p*std::max<double>(0, (Q_pmax - Q_p) ) )  ; 
	
 		
 		
		
/********************/
/* Zooplankton model */
/********************/
		
		
 
		
// Temperature effect on zooplankton rates		
		Temp_effect[5] = k_0*exp( (T_Az/T_0z) -  (T_Az/T) )* ( 1/ (1 + exp(  (T_ALz/T) -  (T_ALz/T_Lz) ) + exp(  (T_AHz/T_Hz) - (T_AHz/T)   )  ) )  ; 
		
// Uptake of phytoplankton C by zooplankton (mgC d−1)
		U_zp = CZ[box]*U_czm*(CP[box]/ (CP[box] + X_pz) )*min<double>(Q_p/Q_z, 1) ; 
		
// Uptake of POC by zooplankton (mgC d−1)
		U_zo = CZ[box]*U_poczm*( POC[box]/(POC[box] + X_pocz))*min<double>(Q_o/Q_z, 1) ;  

// Zooplankton growth rate (mgC d−1)
		G_z =  G_zm*EZ[box]*Temp_effect[5]*max<double>(0,1-R_zmin/(EZ[box]/(EZ[box]+CZ[box]))) ;  

// Zooplankton faeces (mgC d-1)
		Z_f = d_z*U_zp + d_z*U_zo ; 
		
//  C loss rate of zooplankton reserves (mgC d-1)
		EZ_rho = delta_z*EZ[box] + r_z*Temp_effect[5]*CZ[box] ; 
		
// C loss rate of zooplankton structure weight  (mgC d-1)
		CZ_rho = delta_z*CZ[box] ; 
		
//Zooplankton excretion (mgN d−1)
		Z_excr = e_uz*(U_zp+U_zo)*Q_z + r_z*Temp_effect[5]*CZ[box]*Q_z ; 

// Zooplankton mortality (mgC d−1)
		M_z = delta_z*(CZ[box]+EZ[box]) ;  
		
// Zooplankton biomass (mgC m-3)
		W_z = CZ[box]+EZ[box] ;  
		
			 
				
/********************/
/* Salmon DEB model */
/********************/
		
		
		
		FEED = PARAMETERS[2*MaxDays+t+31*Boxes+33] ; 
		
 
	   	
		// waste feed (mg C d-1)

 
		F_w =0 ; 
		M[0] = 0 ;
				
		F[0][box]  = 0 ; 
				
		if(t>= SalmonStart & t<= SalmonEnd & (box==2))
		{
		
			//N[0][box] = 1e-10 ; 	
			 
			
 		 
			if( N[0][box] < 1){ FEED = 0 ;  } 
		 
			func_response[0] = FEED /(FEED + X_Hf) ; 
 
 
 			
			
			// Temperature effect on salmon rates	
			Temp_effect[0] = k_0*exp( (T_Af/T_0) -  (T_Af/T) )* ( 1/ (1 + exp(  (T_ALf/T) -  (T_ALf/T_Lf) ) + exp(  (T_AHf/T_Hf) - (T_AHf/T)   )  ) )  ; 
			
			// Salmon consumption rate (mg d-1)
			U_f =  344.18967*Temp_effect[0]*func_response[0]*pow(W[0][box],0.50623)  ; 
 
  
  
 		
		
			F_w = 0 ; 	
				if(box==2)
					U_f  = std::min<double>(U_f, 55417.7*FEED /(N[0][box]) )  ; 
					F_w = carbon_percentage*55417.7*FEED - carbon_percentage*N[0][box]*U_f ;  
					F_w  = std::max<double>(F_w,0) ; 
	


//23079.9 3.47467E+08 
// feed is mg per m3
// F_w is total mgC feed waste
 		

// Salmon carbon consumption rate (mgC d-1)
 	C_f =   U_f*carbon_percentage ; 
	
 
// Salmon carbon assimilation rate (mgC d-1)

 	A_f =   U_f*ADC ; 
	

	
	// Salmon energy assimilation rate (j d-1)
	P_A[0] =   U_f*Ass_mult ; 
	
 
	
	// Salmon energy assimilation rate (j cm^-2 d^-1) 
	//p_Af =  2250 ; 
	p_Af =   (344.18967*pow(W[0][box],0.50623)* Ass_mult ) / (pow(V[0][box],0.66667 ) ) ; 
	
  	
   
 
 
	
	// Salmon energy density
	Ed = E[0][box]/V[0][box] ; 
	
	// Salmon catabolic rate
	P_C[0] = Temp_effect[0]*(Ed/ ( (kappa_f*Ed)+E_Gf))*(  ( (E_Gf*p_Af*pow(V[0][box],0.67)) / E_mf ) +p_Mf*V[0][box] ) ; 

 	
	
 	
	
	
	// Salmon maintenance rate
	P_M[0] = Temp_effect[0]* p_Mf * V[0][box] ; 
	
	// Salmon maturity maintenance
	P_J[0] = std::min(V[0][box], V_pf)*p_Mf*(1-kappa_f)/kappa_f;
	
	// Faeces model  mg C d^(-1)
	F[0][box]  = C_f-A_f ; 
	
	// FEED in mg per m3 d-1, U_f in mg d-1 	
	
	// 55417.7*FEED is the total feed 7/9 of it in box i , 2/9 in box 
	

	
 	
 	
	// Salmon excretions
	// Note that Q_ff is the N quota for feed mgN mgC−1	
	F_excr =  ( (P_C[0]-(1-kappa_Rf)*( (1-kappa_f)*P_C[0] -  P_J[0]) -mu_Vf*rho*( (kappa_f*P_C[0] -  P_M[0])*(1/E_Gf) ) )*Q_f + P_A[0]*std::max<double>(0,(Q_ff - Q_f)) )/mu_CJ ; 
	
 
	/* Update biovolume V and energy E  */
	
	// Salmon energy   
	E[0][box] = E[0][box] + (P_A[0] - P_C[0]) ;
	
	// Salmon reproductive reserves 
	E_R[0][box] = E_R[0][box] + (1-kappa_f)*P_C[0] -  P_J[0] ; 
	
	// Salmon biovolume 
	V[0][box] = V[0][box] + std::max<double>(0,(kappa_f*P_C[0] -  P_M[0]))*(1/E_Gf) ; 
	
	// Salmon Length 
	L[0][box] = (1/delta_mf)*pow(V[0][box],.333333333333) ; 	
	
	RateChangeSalmonWeight = 	(V[0][box]*rho + (E[0][box] + E_R[0][box]*kappa_Rf)/mu_Ef ) - W[0][box]  ; 
	
	
	
	if(	W[0][box] < 4600)
	{
	
	// Salmon weight
	W[0][box] = V[0][box]*rho + (E[0][box] + E_R[0][box]*kappa_Rf)/mu_Ef;
	

}

 
	
 

	// Salmon biomass after mortality
if(box==2){
	Abundance_yesterday = N[0][box] ; 
	B[0][box] = 1E-6*N[0][box]*W[0][box] - PARAMETERS[4*MaxDays+t+31*Boxes+33] ; // MORTALITY
	N[0][box] = B[0][box]/(1E-6*W[0][box]) ; 
	MORT_RATE = 1 - (N[0][box]/Abundance_yesterday) ; 
	
	//B[0][box] = PARAMETERS[3*MaxDays+t+31*Boxes+33] ;
	//N[0][box] = B[0][box]/(1E-6*W[0][box]) ; 
	
	if(W[0][box] > 4600){
		B[0][box] = 1e-10 ;
		N[0][box] = 1e-10 ; 
		
	//HARVEST = B[0][box] - PARAMETERS[3*MaxDays+t+31*Boxes+33] ; 
	//B[0][box] = B[0][box] -  HARVEST ; 
	//N[0][box] = B[0][box]/(1E-6*W[0][box]) ; 
}

}
 	
 
 

 
	
	// Salmon carbon loss IN mg C d-1
M[0] = MORT_RATE*Abundance_yesterday*(V[0][box]*rho*mu_Vf + (E[0][box]+E_R[0][box]*kappa_Rf) )/mu_CJ ; 
 
 
//N[0][box] = 1e-10 ; 
//F[0][box]  = 0 ;
//M[0] = 0 ;
//F_w =  0  ;
  
if( N[0][box] < 1){ B[0][box] = 1e-10 ;
		N[0][box] = 1e-10 ; 
		FEED = 0 ; 
	 F[0][box]   = 0 ;
	 M[0] = 0 ;
	 F_w =  0  ; }
 
 
/***************************/
/* Salmon Fatty Acid model */
/***************************/



	
	if(t ==0){ ALA[box] = W[0][box]*ALA_FRACTION_WHOLE_BODY ; 
		EPA[box] = W[0][box]*EPA_FRACTION_WHOLE_BODY ; 
		DHA[box] = W[0][box]*DHA_FRACTION_WHOLE_BODY ; 
		ARA[box] = W[0][box]*ARA_FRACTION_WHOLE_BODY ; 
		LIN[box] = W[0][box]*LIN_FRACTION_WHOLE_BODY ; }
	
 	
		
   
  ALA_INTAKE = 1e-3*U_f*ALA_COMP /	W[0][box]  ; 
  ARA_INTAKE = 1e-3*U_f*ARA_COMP /	W[0][box]  ; 
  EPA_INTAKE = 1e-3*U_f*EPA_COMP /	W[0][box]  ;  
  DHA_INTAKE = 1e-3*U_f*DHA_COMP /	W[0][box]  ;  
  DPA_INTAKE = 1e-3*U_f*DPA_COMP /	W[0][box]  ; 
  LIN_INTAKE = 1e-3*U_f*LIN_COMP /	W[0][box]  ; 
  OLA_INTAKE = 1e-3*U_f*OLA_COMP /	W[0][box]  ; 
  PAM_INTAKE = 1e-3*U_f*PAM_COMP /	W[0][box]  ; 
  
  
   
  
    DHA_EPA_ratio = DHA_INTAKE/EPA_INTAKE;
	n3_n6_ratio =  (ALA_COMP+DHA_COMP + DPA_COMP + EPA_COMP) /  (ARA_COMP+LIN_COMP) ; 
  
				
  // ALA update
 
                        
                                                                                                      
ala_beta_oxidation_g_g_fish_day =
	Intercept_ala_beta_oxidation_g_g_fish_day + 
		ALA_ala_beta_oxidation_g_g_fish_day*ALA_INTAKE+
	ARA_ala_beta_oxidation_g_g_fish_day*ARA_INTAKE+
	DHA_ala_beta_oxidation_g_g_fish_day*DHA_INTAKE+
	DPA_ala_beta_oxidation_g_g_fish_day*DPA_INTAKE+
	EPA_ala_beta_oxidation_g_g_fish_day*EPA_INTAKE+
	LIN_ala_beta_oxidation_g_g_fish_day*LIN_INTAKE+
	OLA_ala_beta_oxidation_g_g_fish_day*OLA_INTAKE+
	PAM_ala_beta_oxidation_g_g_fish_day*PAM_INTAKE+
		TEMP_ala_beta_oxidation_g_g_fish_day*(T-273.15) + 
		WEIGHT_ala_beta_oxidation_g_g_fish_day*W[0][box]+
		DHA_EPA_RATIO_ala_beta_oxidation_g_g_fish_day*DHA_EPA_ratio+
		N3_N6_RATIO_ala_beta_oxidation_g_g_fish_day*n3_n6_ratio ;   
 
 
 
 
  
 
ala_egestion_g_g_fish_day = 
	Intercept_ala_beta_oxidation_g_g_fish_day + 
		ALA_ala_egestion_g_g_fish_day*ALA_INTAKE+
	ARA_ala_egestion_g_g_fish_day*ARA_INTAKE+
	DHA_ala_egestion_g_g_fish_day*DHA_INTAKE+
	DPA_ala_egestion_g_g_fish_day*DPA_INTAKE+
	EPA_ala_egestion_g_g_fish_day*EPA_INTAKE+
	LIN_ala_egestion_g_g_fish_day*LIN_INTAKE+
	OLA_ala_egestion_g_g_fish_day*OLA_INTAKE+
	PAM_ala_egestion_g_g_fish_day*PAM_INTAKE+
		TEMP_ala_egestion_g_g_fish_day*(T-273.15)+ 
		WEIGHT_ala_egestion_g_g_fish_day*W[0][box]+
		DHA_EPA_RATIO_ala_egestion_g_g_fish_day*DHA_EPA_ratio+
		N3_N6_RATIO_ala_egestion_g_g_fish_day*n3_n6_ratio ;      


ala_transformation_g_g_fish_day = 
Intercept_ala_transformation_g_g_fish_day + 
	ALA_ala_transformation_g_g_fish_day*ALA_INTAKE+
ARA_ala_transformation_g_g_fish_day*ARA_INTAKE+
DHA_ala_transformation_g_g_fish_day*DHA_INTAKE+
DPA_ala_transformation_g_g_fish_day*DPA_INTAKE+
EPA_ala_transformation_g_g_fish_day*EPA_INTAKE+
LIN_ala_transformation_g_g_fish_day*LIN_INTAKE+
OLA_ala_transformation_g_g_fish_day*OLA_INTAKE+
PAM_ala_transformation_g_g_fish_day*PAM_INTAKE+
	TEMP_ala_transformation_g_g_fish_day*(T-273.15) + 
	WEIGHT_ala_transformation_g_g_fish_day*W[0][box]+
	DHA_EPA_RATIO_ala_transformation_g_g_fish_day*DHA_EPA_ratio+
	N3_N6_RATIO_ala_transformation_g_g_fish_day*n3_n6_ratio ;                                                            
 
                                                                                                                                     

  	

ala_egestion_g_g_fish_day = std::min<double>(ALA_INTAKE,ala_egestion_g_g_fish_day) ; 
	
	
 
	    ALA[box] = ALA[box] + ALA_INTAKE*W[0][box] - W[0][box]*ala_beta_oxidation_g_g_fish_day - W[0][box]*ala_egestion_g_g_fish_day + W[0][box]*ala_transformation_g_g_fish_day ; 
 
	
 	ALA[box] = std::max<double>(0,ALA[box]) ; 
 	
	
	                                           
  
	
  // ARA update
                                                                                             
                                                                                                      
	ara_beta_oxidation_g_g_fish_day =
		Intercept_ara_beta_oxidation_g_g_fish_day + 
			ALA_ara_beta_oxidation_g_g_fish_day*ALA_INTAKE+
		ARA_ara_beta_oxidation_g_g_fish_day*ARA_INTAKE+
		DHA_ara_beta_oxidation_g_g_fish_day*DHA_INTAKE+
		DPA_ara_beta_oxidation_g_g_fish_day*DPA_INTAKE+
		EPA_ara_beta_oxidation_g_g_fish_day*EPA_INTAKE+
		LIN_ara_beta_oxidation_g_g_fish_day*LIN_INTAKE+
		OLA_ara_beta_oxidation_g_g_fish_day*OLA_INTAKE+
		PAM_ara_beta_oxidation_g_g_fish_day*PAM_INTAKE+
			TEMP_ara_beta_oxidation_g_g_fish_day*(T-273.15) + 
			WEIGHT_ara_beta_oxidation_g_g_fish_day*W[0][box]+
			DHA_EPA_RATIO_ara_beta_oxidation_g_g_fish_day*DHA_EPA_ratio+
			N3_N6_RATIO_ara_beta_oxidation_g_g_fish_day*n3_n6_ratio ;   
 
 
 
 
	ara_egestion_g_g_fish_day = 
		Intercept_ara_egestion_g_g_fish_day + 
			ALA_ara_egestion_g_g_fish_day*ALA_INTAKE+
		ARA_ara_egestion_g_g_fish_day*ARA_INTAKE+
		DHA_ara_egestion_g_g_fish_day*DHA_INTAKE+
		DPA_ara_egestion_g_g_fish_day*DPA_INTAKE+
		EPA_ara_egestion_g_g_fish_day*EPA_INTAKE+
		LIN_ara_egestion_g_g_fish_day*LIN_INTAKE+
		OLA_ara_egestion_g_g_fish_day*OLA_INTAKE+
		PAM_ara_egestion_g_g_fish_day*PAM_INTAKE+
			TEMP_ara_egestion_g_g_fish_day*(T-273.15) + 
			WEIGHT_ara_egestion_g_g_fish_day*W[0][box]+
			DHA_EPA_RATIO_ara_egestion_g_g_fish_day*DHA_EPA_ratio+
			N3_N6_RATIO_ara_egestion_g_g_fish_day*n3_n6_ratio ;      




	ara_transformation_g_g_fish_day = 
	Intercept_ara_transformation_g_g_fish_day + 
		ALA_ara_transformation_g_g_fish_day*ALA_INTAKE+
	ARA_ara_transformation_g_g_fish_day*ARA_INTAKE+
	DHA_ara_transformation_g_g_fish_day*DHA_INTAKE+
	DPA_ara_transformation_g_g_fish_day*DPA_INTAKE+
	EPA_ara_transformation_g_g_fish_day*EPA_INTAKE+
	LIN_ara_transformation_g_g_fish_day*LIN_INTAKE+
	OLA_ara_transformation_g_g_fish_day*OLA_INTAKE+
	PAM_ara_transformation_g_g_fish_day*PAM_INTAKE+
		TEMP_ara_transformation_g_g_fish_day*(T-273.15) + 
		WEIGHT_ara_transformation_g_g_fish_day*W[0][box]+
		DHA_EPA_RATIO_ara_transformation_g_g_fish_day*DHA_EPA_ratio+
		N3_N6_RATIO_ara_transformation_g_g_fish_day*n3_n6_ratio ;                                                            
 
                                 
	
 
	ara_egestion_g_g_fish_day = std::min<double>(ARA_INTAKE,ara_egestion_g_g_fish_day) ; 
                 
	
	ara_egestion_g_g_fish_day = std::max<double>(0,ara_egestion_g_g_fish_day) ; 
 
	    ARA[box] = ARA[box]  + ARA_INTAKE*W[0][box] - W[0][box]*ara_beta_oxidation_g_g_fish_day - W[0][box]*ara_egestion_g_g_fish_day + W[0][box]*ara_transformation_g_g_fish_day ; 
 
	
	    ARA[box]  = max<double>(0,ARA[box] ) ; 
	
	
 
	
  // DHA update	
 
                                                                                                      
		dha_beta_oxidation_g_g_fish_day =
			Intercept_dha_beta_oxidation_g_g_fish_day + 
				ALA_dha_beta_oxidation_g_g_fish_day*ALA_INTAKE+
			ARA_dha_beta_oxidation_g_g_fish_day*ARA_INTAKE+
			DHA_dha_beta_oxidation_g_g_fish_day*DHA_INTAKE+
			DPA_dha_beta_oxidation_g_g_fish_day*DPA_INTAKE+
			EPA_dha_beta_oxidation_g_g_fish_day*EPA_INTAKE+
			LIN_dha_beta_oxidation_g_g_fish_day*LIN_INTAKE+
			OLA_dha_beta_oxidation_g_g_fish_day*OLA_INTAKE+
			PAM_dha_beta_oxidation_g_g_fish_day*PAM_INTAKE+
				TEMP_dha_beta_oxidation_g_g_fish_day*(T-273.15) + 
				WEIGHT_dha_beta_oxidation_g_g_fish_day*W[0][box]+
				DHA_EPA_RATIO_dha_beta_oxidation_g_g_fish_day*DHA_EPA_ratio+
				N3_N6_RATIO_dha_beta_oxidation_g_g_fish_day*n3_n6_ratio ;   
 
 
 
 
		dha_egestion_g_g_fish_day = 
			Intercept_dha_egestion_g_g_fish_day + 
				ALA_dha_egestion_g_g_fish_day*ALA_INTAKE+
			ARA_dha_egestion_g_g_fish_day*ARA_INTAKE+
			DHA_dha_egestion_g_g_fish_day*DHA_INTAKE+
			DPA_dha_egestion_g_g_fish_day*DPA_INTAKE+
			EPA_dha_egestion_g_g_fish_day*EPA_INTAKE+
			LIN_dha_egestion_g_g_fish_day*LIN_INTAKE+
			OLA_dha_egestion_g_g_fish_day*OLA_INTAKE+
			PAM_dha_egestion_g_g_fish_day*PAM_INTAKE+
				TEMP_dha_egestion_g_g_fish_day*(T-273.15) + 
				WEIGHT_dha_egestion_g_g_fish_day*W[0][box]+
				DHA_EPA_RATIO_dha_egestion_g_g_fish_day*DHA_EPA_ratio+
				N3_N6_RATIO_dha_egestion_g_g_fish_day*n3_n6_ratio ;      


		dha_transformation_g_g_fish_day = 
		Intercept_dha_transformation_g_g_fish_day + 
			ALA_dha_transformation_g_g_fish_day*ALA_INTAKE+
		ARA_dha_transformation_g_g_fish_day*ARA_INTAKE+
		DHA_dha_transformation_g_g_fish_day*DHA_INTAKE+
		DPA_dha_transformation_g_g_fish_day*DPA_INTAKE+
		EPA_dha_transformation_g_g_fish_day*EPA_INTAKE+
		LIN_dha_transformation_g_g_fish_day*LIN_INTAKE+
		OLA_dha_transformation_g_g_fish_day*OLA_INTAKE+
		PAM_dha_transformation_g_g_fish_day*PAM_INTAKE+
			TEMP_dha_transformation_g_g_fish_day*(T-273.15) + 
			WEIGHT_dha_transformation_g_g_fish_day*W[0][box]+
			DHA_EPA_RATIO_dha_transformation_g_g_fish_day*DHA_EPA_ratio+
			N3_N6_RATIO_dha_transformation_g_g_fish_day*n3_n6_ratio ;                                                            
                                                                                                                         
 
  
		dha_egestion_g_g_fish_day = std::min<double>(DHA_INTAKE,dha_egestion_g_g_fish_day) ; 
  
	
		//printf("%G %G %G %G\n",DHA_INTAKE*W[0][box],- W[0][box]*dha_beta_oxidation_g_g_fish_day ,- W[0][box]*dha_egestion_g_g_fish_day , W[0][box]*dha_transformation_g_g_fish_day) ; 
 
 
	    DHA[box] = DHA[box] + DHA_INTAKE*W[0][box] - W[0][box]*dha_beta_oxidation_g_g_fish_day - W[0][box]*dha_egestion_g_g_fish_day + W[0][box]*dha_transformation_g_g_fish_day ; 
 
	
		    DHA[box] = max<double>(0,DHA[box]) ; 
	 
	
 
  // EPA update	
		

                                                                                                      
		epa_beta_oxidation_g_g_fish_day =
			Intercept_epa_beta_oxidation_g_g_fish_day + 
				ALA_epa_beta_oxidation_g_g_fish_day*ALA_INTAKE+
			ARA_epa_beta_oxidation_g_g_fish_day*ARA_INTAKE+
			DHA_epa_beta_oxidation_g_g_fish_day*DHA_INTAKE+
			DPA_epa_beta_oxidation_g_g_fish_day*DPA_INTAKE+
			EPA_epa_beta_oxidation_g_g_fish_day*EPA_INTAKE+
			LIN_epa_beta_oxidation_g_g_fish_day*LIN_INTAKE+
			OLA_epa_beta_oxidation_g_g_fish_day*OLA_INTAKE+
			PAM_epa_beta_oxidation_g_g_fish_day*PAM_INTAKE+
				TEMP_epa_beta_oxidation_g_g_fish_day*(T-273.15) + 
				WEIGHT_epa_beta_oxidation_g_g_fish_day*W[0][box]+
				DHA_EPA_RATIO_epa_beta_oxidation_g_g_fish_day*DHA_EPA_ratio+
				N3_N6_RATIO_epa_beta_oxidation_g_g_fish_day*n3_n6_ratio ;   
 
 
 
 
		epa_egestion_g_g_fish_day = 
			Intercept_epa_egestion_g_g_fish_day + 
				ALA_epa_egestion_g_g_fish_day*ALA_INTAKE+
			ARA_epa_egestion_g_g_fish_day*ARA_INTAKE+
			DHA_epa_egestion_g_g_fish_day*DHA_INTAKE+
			DPA_epa_egestion_g_g_fish_day*DPA_INTAKE+
			EPA_epa_egestion_g_g_fish_day*EPA_INTAKE+
			LIN_epa_egestion_g_g_fish_day*LIN_INTAKE+
			OLA_epa_egestion_g_g_fish_day*OLA_INTAKE+
			PAM_epa_egestion_g_g_fish_day*PAM_INTAKE+
				TEMP_epa_egestion_g_g_fish_day*(T-273.15) + 
				WEIGHT_epa_egestion_g_g_fish_day*W[0][box]+
				DHA_EPA_RATIO_epa_egestion_g_g_fish_day*DHA_EPA_ratio+
				N3_N6_RATIO_epa_egestion_g_g_fish_day*n3_n6_ratio ;      


		epa_transformation_g_g_fish_day = 
		Intercept_epa_transformation_g_g_fish_day + 
			ALA_epa_transformation_g_g_fish_day*ALA_INTAKE+
		ARA_epa_transformation_g_g_fish_day*ARA_INTAKE+
		DHA_epa_transformation_g_g_fish_day*DHA_INTAKE+
		DPA_epa_transformation_g_g_fish_day*DPA_INTAKE+
		EPA_epa_transformation_g_g_fish_day*EPA_INTAKE+
		LIN_epa_transformation_g_g_fish_day*LIN_INTAKE+
		OLA_epa_transformation_g_g_fish_day*OLA_INTAKE+
		PAM_epa_transformation_g_g_fish_day*PAM_INTAKE+
			TEMP_epa_transformation_g_g_fish_day*(T-273.15) + 
			WEIGHT_epa_transformation_g_g_fish_day*W[0][box]+
			DHA_EPA_RATIO_epa_transformation_g_g_fish_day*DHA_EPA_ratio+
			N3_N6_RATIO_epa_transformation_g_g_fish_day*n3_n6_ratio ;                                                            
                                                                                                                         
 
 	
	
	

		epa_egestion_g_g_fish_day = std::min<double>(EPA_INTAKE,epa_egestion_g_g_fish_day) ; 
   
		epa_egestion_g_g_fish_day = std::max<double>(0,epa_egestion_g_g_fish_day) ; 
  	
 
	    EPA[box] =  EPA[box]  + EPA_INTAKE*W[0][box] -  W[0][box]*epa_beta_oxidation_g_g_fish_day -  W[0][box]*epa_egestion_g_g_fish_day + W[0][box]*epa_transformation_g_g_fish_day ; 
 
	     EPA[box]  = max<double>(0,EPA[box]) ; 
	


  		
// 	1/302.451 mols per gram in epa 			 
//there are 12.011 g/mol in carbon
// soo there is EPA_EGESTED_CARBON = 12.011* 1/302.451 * W[0][box]*epa_egestion_g_g_fish_day grams of carbon egested  per day
// but feces mgC d-1 is  F[0][box]
// so EPA content is EPA_EGESTED_CARBON/F[0][box]
		 
// printf("%G %G %G %G\n" ,EPA_INTAKE*W[0][box] , W[0][box]*epa_egestion_g_g_fish_day,F[0][box], ( ( (12.011/302.451)*W[0][box]*epa_egestion_g_g_fish_day) ) /(1e-3*F[0][box]) ) ; 
	
  // LIN update
 
                                                                                                      
		lin_beta_oxidation_g_g_fish_day =
			Intercept_lin_beta_oxidation_g_g_fish_day + 
				ALA_lin_beta_oxidation_g_g_fish_day*ALA_INTAKE+
			ARA_lin_beta_oxidation_g_g_fish_day*ARA_INTAKE+
			DHA_lin_beta_oxidation_g_g_fish_day*DHA_INTAKE+
			DPA_lin_beta_oxidation_g_g_fish_day*DPA_INTAKE+
			EPA_lin_beta_oxidation_g_g_fish_day*EPA_INTAKE+
			LIN_lin_beta_oxidation_g_g_fish_day*LIN_INTAKE+
			OLA_lin_beta_oxidation_g_g_fish_day*OLA_INTAKE+
			PAM_lin_beta_oxidation_g_g_fish_day*PAM_INTAKE+
				TEMP_lin_beta_oxidation_g_g_fish_day*(T-273.15) + 
				WEIGHT_lin_beta_oxidation_g_g_fish_day*W[0][box]+
				DHA_EPA_RATIO_lin_beta_oxidation_g_g_fish_day*DHA_EPA_ratio+
				N3_N6_RATIO_lin_beta_oxidation_g_g_fish_day*n3_n6_ratio ;   
 
 
 
 
		lin_egestion_g_g_fish_day = 
			Intercept_lin_egestion_g_g_fish_day + 
				ALA_lin_egestion_g_g_fish_day*ALA_INTAKE+
			ARA_lin_egestion_g_g_fish_day*ARA_INTAKE+
			DHA_lin_egestion_g_g_fish_day*DHA_INTAKE+
			DPA_lin_egestion_g_g_fish_day*DPA_INTAKE+
			EPA_lin_egestion_g_g_fish_day*EPA_INTAKE+
			LIN_lin_egestion_g_g_fish_day*LIN_INTAKE+
			OLA_lin_egestion_g_g_fish_day*OLA_INTAKE+
			PAM_lin_egestion_g_g_fish_day*PAM_INTAKE+
				TEMP_lin_egestion_g_g_fish_day*(T-273.15) + 
				WEIGHT_lin_egestion_g_g_fish_day*W[0][box]+
				DHA_EPA_RATIO_lin_egestion_g_g_fish_day*DHA_EPA_ratio+
				N3_N6_RATIO_lin_egestion_g_g_fish_day*n3_n6_ratio ;      


		lin_transformation_g_g_fish_day = 
		Intercept_lin_transformation_g_g_fish_day + 
			ALA_lin_transformation_g_g_fish_day*ALA_INTAKE+
		ARA_lin_transformation_g_g_fish_day*ARA_INTAKE+
		DHA_lin_transformation_g_g_fish_day*DHA_INTAKE+
		DPA_lin_transformation_g_g_fish_day*DPA_INTAKE+
		EPA_lin_transformation_g_g_fish_day*EPA_INTAKE+
		LIN_lin_transformation_g_g_fish_day*LIN_INTAKE+
		OLA_lin_transformation_g_g_fish_day*OLA_INTAKE+
		PAM_lin_transformation_g_g_fish_day*PAM_INTAKE+
			TEMP_lin_transformation_g_g_fish_day*(T-273.15) + 
			WEIGHT_lin_transformation_g_g_fish_day*W[0][box]+
			DHA_EPA_RATIO_lin_transformation_g_g_fish_day*DHA_EPA_ratio+
			N3_N6_RATIO_lin_transformation_g_g_fish_day*n3_n6_ratio ;                                                            
                                  
  


		lin_egestion_g_g_fish_day = std::min<double>(LIN_INTAKE,lin_egestion_g_g_fish_day) ; 
    
 
		 LIN[box]  = LIN[box] + LIN_INTAKE*W[0][box] - W[0][box]*lin_beta_oxidation_g_g_fish_day - W[0][box]*lin_egestion_g_g_fish_day + W[0][box]*lin_transformation_g_g_fish_day ; 
 
	    LIN[box] = max<double>(0,LIN[box]) ; 
 	
	 
		asseff= 	1/( POCmuss_non_salmon_feces[box]  +  POCmuss_salmon_feces[box])*(.4*POCmuss_non_salmon_feces[box] + .77*POCmuss_salmon_feces[box] ) ; 
 
 
 
		
	}
	
 
	
		
/********************/
/* Mussel DEB model */
/********************/

// ORIGINAL Functional response for mussels (Size-dependent functional response)
    //func_response[1] = CP /(CP + X_Hm) ;  
	
// NEW Functional response for mussels (Size-dependent functional response)


M[1] = 0 ; 
F[1][box]  = 0 ; 


 
if(t>= MusselStart & t<= MusselEnd & (box==0 | box==1 | box ==2) )
     // if(t>= MusselStart & t<= MusselEnd & ( box!=1 & box!=5) )
	{
		
		
 
		
	//	func_response[1]=(0.008487508*(RE_x1*smallparticles_prop[box]*POCmuss[box]+RE_x2*largeparticles_prop[box]*POCmuss[box]) )/(1+3.264499e-05*(RE_x1*smallparticles_prop[box]*POCmuss[box]+RE_x2*largeparticles_prop[box]*POCmuss[box]) )  ; 
		
		
 
 

		//func_response[1]=(0.0117*(RE_x1*smallparticles_prop[box]*POCmuss[box]+RE_x2*largeparticles_prop[box]*POCmuss[box]) )/(1+3.393e-05*(RE_x1*smallparticles_prop[box]*POCmuss[box]+RE_x2*largeparticles_prop[box]*POCmuss[box]) )  ; 


		func_response[1]=(0.0062*(9.09*RE_x1*smallparticles_prop[box]*POCmuss[box]+9.09*RE_x2*largeparticles_prop[box]*POCmuss[box]) )/(1+6.448e-07*(9.09*RE_x1*smallparticles_prop[box]*POCmuss[box]+9.09*RE_x2*largeparticles_prop[box]*POCmuss[box]) )  ; 


 func_response[1] = 0.11*func_response[1] ; 
	
	 	 
	 
	 // Temperature effect on mussel rates			
		Temp_effect[1] = k_0*exp( (T_Am/T_0) -  (T_Am/T) )* ( 1/ (1 + exp(  (T_ALm/T) -  (T_ALm/T_Lm) ) + exp(  (T_AHm/T_Hm) - (T_AHm/T)   )  ) )  ; 
		
//Consumption rate of phytoplankton by mussels
	U_mp =  Temp_effect[1]*U_mm*CP[box]*pow(V[1][box],0.67); 
		
// Consumption rate of POC by mussels
	U_mo = Temp_effect[1]*func_response[1]*pow(V[1][box],0.67); 
	
// Mussel assimilation rate (changed from Ren)
	// U_mp in mg C (whats the conversion to J? )
	// U_mo in mg C (whats the conversion to J? )
	// Ren - 48.8 J per mgC
//asseff= 	1/( POCmuss_non_salmon_feces[box]  +  POCmuss_salmon_feces[box])*(.4*POCmuss_non_salmon_feces[box] + .77*POCmuss_salmon_feces[box] ) ; 
 
asseff_poc = .54 ;  
//double ED_poc = 43.33333/20.42419; 

double ED_poc = 12.5; 


//Absorption efficiency of blue mussels (Mytilus edulis and M. trossulus) feeding on Atlantic salmon (Salmo salar) feed and fecal particulates: Implications for integrated multi-trophic aquaculture
 

asseff_phyto = .81 ;  

  
double asseff_salmon = .86 ;  
double ED_salmon_poo = 18.93381 ; 


PROP_FOOD_SALMON_POO = largeparticles_salmon_prop[box] *( RE_x2*largeparticles_prop[box] / (RE_x1*smallparticles_prop[box]+ RE_x2*largeparticles_prop[box] )  ) ; 
PROP_FOOD_ZOO = 1 - PROP_FOOD_SALMON_POO ; 


 
	 

//https://www.sciencedirect.com/science/article/pii/S0022098197001731?casa_token=W8DKAVdj8vQAAAAA:qJRiJdLeWKk7kL2QpoLsjOWQ7N2erhyKMEz3P5_i96NfVqfi53mcSOrVQ9wXzxq7LLGAZvTkcsQ
	
//   12.5 http://www.ecowin.org/pdf/documents/Brigolin%20et%20al%20gallo%20Chioggia%202009.pdf 
	   
//P_A[1] =12.5*asseff_phyto*(U_mp) +ED_poc*asseff*(PROP_FOOD_ZOO*U_mo) +ED_poc*asseff*(PROP_FOOD_SALMON_POO*U_mo) ; 

//printf("%G %G\n",U_mp,U_mo) ; 




P_A[1] =61.8*asseff_phyto*(U_mp) +ED_poc*asseff_poc*(PROP_FOOD_ZOO*U_mo) +  ED_salmon_poo*asseff_salmon*(PROP_FOOD_SALMON_POO*U_mo) ; 

// j cm-2 d-1

 	
//printf("here %G  %G %G %G %G  %G %G\n",P_A[1], p_Am*pow(V[1][box],0.67) ,
//43.33333*asseff_phyto*(U_mp) , PROP_FOOD_SALMON_POO, PROP_FOOD_ZOO, ED_poc*asseff_poc*(PROP_FOOD_ZOO*U_mo) ,
//ED_salmon_poo*asseff_salmon*(PROP_FOOD_SALMON_POO*U_mo ) ) ; 


if( p_Am*pow(V[1][box],0.67) < P_A[1] )
	
{
	P_A[1] = p_Am*pow(V[1][box],0.67) ; 

} 
 
//Phytoplankton, Zooplankton, and Detritus. 
//	We used prey energy density values of 2600 J g-1 wet mass, 2512 J g-1 wet mass, and 127.3 J g-1 wet mass 
//		for phytoplankton, zooplankton, and detritus, respectively (Anderson et al., 2015, 2016,
// det is 80% water
// phyto are 90% water and carbon content is 60% of dw
// 2600 J per g WW  = per .1 g DW =  0.06 gC  = 60 mg C  = 43.33333 J per mg C for phyto
 
 
//p_Am= 12.5*asseff*( U_mm*CP[box] + 69.15122 ) ; 
 

 
 
	
 	
// Mussel energy density
	Ed = E[1][box]/V[1][box] ; 
	
// Mussel catabolic rate
	P_C[1] = Temp_effect[1]*(Ed/ ( (kappa_m*Ed)+E_Gm))*(  ( (E_Gm*p_Am*pow(V[1][box],0.67)) / E_mm ) +p_Mm*V[1][box] ) ; 
	
	
// Mussel maintenance rate
	P_M[1] = Temp_effect[1]* p_Mm * V[1][box] ; 
	 
// Mussel maturity maintenance
	P_J[1] = std::min(V[1][box], V_pm)*p_Mm*(1-kappa_m)/kappa_m;
	
// Mussel faeces
	F[1][box] = U_mp + U_mo   - (P_A[1]/mu_CJ) ; 
	
// Mussel excretions
	M_excr =  ( (P_C[1]- (1 - kappa_Rm)*( (1-kappa_m)*P_C[1] -  P_J[1]) - mu_Vm*rho*( (kappa_m*P_C[1] - P_M[1])*(1/E_Gm) ) )*Q_m + P_A[1]*std::max<double>(0,(Q_p - Q_m) ) )/mu_CJ ; 
		
	
// Mussel carbon loss
	M[1] = delta_rm*N[1][box]*(V[1][box]*rho*mu_Vm + (E[1][box]+E_R[1][box]*kappa_Rm) )/mu_CJ ; 
	
// Mussel weight
	W[1][box] = V[1][box]*rho + (E[1][box] + E_R[1][box]*kappa_Rm)/mu_Em;
 		
		
/* Update biovolume V and energy E  */

// Mussel energy  
	E[1][box] = E[1][box] + (P_A[1] - P_C[1]) ;

// Mussel reproductive reserves 
	E_R[1][box] = E_R[1][box] + (1-kappa_m)*P_C[1] -  P_J[1] ; 

// Mussel biovolume 
	
	V[1][box] = V[1][box] + std::max<double>(0,(kappa_m*P_C[1] -  P_M[1]))*(1/E_Gm) ; 
	
	
	
	
// Mussel Length 
	L[1][box] = (1/delta_mm)*pow(V[1][box],0.33) ; 	
	
	
	
	
 	
	// Mussel fatty acids
	
	if(t ==MusselStart){ 
		
 
		mantle_ALA_muss[box]= 0.25*1e3*fraction_weight_mantle*W[1][box]*ALA_FRACTION_mantle ; 
		mantle_EPA_muss[box] = 0.25*1e3*fraction_weight_mantle*W[1][box]*EPA_FRACTION_mantle ; 
		mantle_DHA_muss[box] = 0.25*1e3*fraction_weight_mantle*W[1][box]*DHA_FRACTION_mantle ; 
		mantle_ARA_muss[box] =0.25* 1e3*fraction_weight_mantle*W[1][box]*ARA_FRACTION_mantle ; 
		mantle_LIN_muss[box] = 0.25*1e3*fraction_weight_mantle*W[1][box]*LIN_FRACTION_mantle ;  
		
		gill_ALA_muss[box]= 0.25*1e3*fraction_weight_gill*W[1][box]*ALA_FRACTION_gill ; 
				gill_EPA_muss[box] = 0.25*1e3*fraction_weight_gill*W[1][box]*EPA_FRACTION_gill ; 
				gill_DHA_muss[box] = 0.25*1e3*fraction_weight_gill*W[1][box]*DHA_FRACTION_gill ; 
				gill_ARA_muss[box] = 0.25*1e3*fraction_weight_gill*W[1][box]*ARA_FRACTION_gill ; 
				gill_LIN_muss[box] =0.25* 1e3*fraction_weight_gill*W[1][box]*LIN_FRACTION_gill ;  
				
				gland_ALA_muss[box]= 0.25*1e3*fraction_weight_gland*W[1][box]*ALA_FRACTION_gland ; 
						gland_EPA_muss[box] =0.25* 1e3*fraction_weight_gland*W[1][box]*EPA_FRACTION_gland ; 
						gland_DHA_muss[box] = 0.25*1e3*fraction_weight_gland*W[1][box]*DHA_FRACTION_gland ; 
						gland_ARA_muss[box] = 0.25*1e3*fraction_weight_gland*W[1][box]*ARA_FRACTION_gland ; 
						gland_LIN_muss[box] = 0.25*1e3*fraction_weight_gland*W[1][box]*LIN_FRACTION_gland ;  
					}
	
	
 //   xlab(expression(paste("Intake rate (mg ","mg"^-1, "d"^-1,")")))+
	
	// U_mo is the intake of POC in mg C d-1
    // the uptake of pOC in mg d-1 is 2*U_mo if carbon content is 50% of POC
					

 
 
	 /*				
	ALA_intake = (PROP_ALA_POC*2*U_mo +PROP_ALA_PHYTO*2*U_mp ) / 1000*W[1][box]  ; 
	ARA_intake = (PROP_ARA_POC*2*U_mo +PROP_ARA_PHYTO*2*U_mp ) / 1000*W[1][box]  ; 
	DHA_intake = (PROP_DHA_POC*2*U_mo +PROP_DHA_PHYTO*2*U_mp ) / 1000*W[1][box]  ; 
	EPA_intake = (PROP_EPA_POC*2*U_mo +PROP_EPA_PHYTO*2*U_mp ) / 1000*W[1][box]  ; 
	LIN_intake = (PROP_LIN_POC*2*U_mo +PROP_LIN_PHYTO*2*U_mp ) / 1000*W[1][box]  ; 
	 */
	
	  
 
SALMON_POO_ALA_PROP =  0 ; 
SALMON_POO_ARA_PROP = 0 ; 
SALMON_POO_DHA_PROP =  0 ; 
SALMON_POO_EPA_PROP = 0 ; 
SALMON_POO_LIN_PROP = 0 ; 

if(F[0][2]>1e-4)
{
	SALMON_POO_ALA_PROP =  ( ( (12.011/278.43)*W[0][2]*ala_egestion_g_g_fish_day) ) /(1e-3*F[0][2] )    ; 
	SALMON_POO_ARA_PROP =  ( ( (12.011/304.4669)*W[0][2]*ara_egestion_g_g_fish_day) ) /(1e-3*F[0][2] )   ; 
	SALMON_POO_DHA_PROP =  ( ( (12.011/328.488)*W[0][2]*dha_egestion_g_g_fish_day) ) /(1e-3*F[0][2] )   ; 
	SALMON_POO_EPA_PROP =  ( ( (12.011/302.451)*W[0][2]*epa_egestion_g_g_fish_day) ) /(1e-3*F[0][2] )   ; 
	SALMON_POO_LIN_PROP =  ( ( (12.011/280.4472)*W[0][2]*lin_egestion_g_g_fish_day) ) /(1e-3*F[0][2] )   ; 

	
    SALMON_POO_ALA_PROP = max<double>(0,SALMON_POO_ALA_PROP) ; 
    SALMON_POO_ARA_PROP = max<double>(0,SALMON_POO_ARA_PROP) ; 
    SALMON_POO_DHA_PROP = max<double>(0,SALMON_POO_DHA_PROP ) ; 
    SALMON_POO_EPA_PROP = max<double>(0,SALMON_POO_EPA_PROP ) ; 
    SALMON_POO_LIN_PROP = max<double>(0,SALMON_POO_LIN_PROP ) ; 
	
}
 
ALA_intake =0.25*(0.429)*(SALMON_POO_ALA_PROP*PROP_FOOD_SALMON_POO*U_mo + ZOO_ALA_PROP*PROP_FOOD_ZOO*U_mo +PHYTO_ALA_PROP*PHYTO_FA_PROP_OF_CARBON*U_mp ) / 1000*W[1][box]  ; 
ARA_intake =0.25*(0.429)* (SALMON_POO_ARA_PROP*PROP_FOOD_SALMON_POO*U_mo + ZOO_ARA_PROP*PROP_FOOD_ZOO*U_mo +PHYTO_ARA_PROP*PHYTO_FA_PROP_OF_CARBON*U_mp ) / 1000*W[1][box]  ; 
DHA_intake =0.25*(0.429)* (SALMON_POO_DHA_PROP*PROP_FOOD_SALMON_POO*U_mo + ZOO_DHA_PROP*PROP_FOOD_ZOO*U_mo +PHYTO_DHA_PROP*PHYTO_FA_PROP_OF_CARBON*U_mp ) / 1000*W[1][box]  ; 
EPA_intake =0.25*(0.429)* (SALMON_POO_EPA_PROP*PROP_FOOD_SALMON_POO*U_mo + ZOO_EPA_PROP*PROP_FOOD_ZOO*U_mo +PHYTO_EPA_PROP*PHYTO_FA_PROP_OF_CARBON*U_mp ) / 1000*W[1][box]  ; 
LIN_intake =0.25*(0.429)* (SALMON_POO_LIN_PROP*PROP_FOOD_SALMON_POO*U_mo + ZOO_LIN_PROP*PROP_FOOD_ZOO*U_mo +PHYTO_LIN_PROP*PHYTO_FA_PROP_OF_CARBON*U_mp ) / 1000*W[1][box]  ; 
	
	 
	 
	 
	 
	// mantle
		//mantle_ALA_muss[box]= mantle_ALA_muss[box] + 1e3*W[1][box]*( -0.00000110       +     0.00322  *ALA_intake) ; 
		//mantle_ARA_muss[box] = mantle_ARA_muss[box]+ 1e3*W[1][box]*( -0.00000125        +    0.0388*ARA_intake) ; 
		//mantle_DHA_muss[box] = mantle_DHA_muss[box]+ 1e3*W[1][box]*( -0.00000647    +        0.0289*DHA_intake) ; 
		//mantle_EPA_muss[box] = mantle_EPA_muss[box] + 1e3*W[1][box]*(-0.0000103     +        0.0269*EPA_intake ) ;
		//mantle_LIN_muss[box] = mantle_LIN_muss[box] + 1e3*W[1][box]*( -0.0000000369    +      0.00212*LIN_intake ) ; 



mantle_ALA_muss[box]= mantle_ALA_muss[box] + 0.25*(0.429)*1e3*W[1][box]*(        0.0194  *ALA_intake) ; 
mantle_ARA_muss[box] = mantle_ARA_muss[box]+ 0.25*(0.429)*1e3*W[1][box]*(         0.179*ARA_intake) ; 
mantle_DHA_muss[box] = mantle_DHA_muss[box]+ 0.25*(0.429)*1e3*W[1][box]*(     0.132 *DHA_intake) ; 
mantle_EPA_muss[box] = mantle_EPA_muss[box] +0.25* (0.429)*1e3*W[1][box]*(     0.0193*EPA_intake ) ;
mantle_LIN_muss[box] = mantle_LIN_muss[box] + 0.25*(0.429)*1e3*W[1][box]*(     0.0252*LIN_intake ) ;


 
 
 
 
 
		
	//	1 "ALA "        0.463  -72.2            0.00158
//		2 "ARA "        0.387  -73.8            0.0146 
//		3 "DHA "       -0.0241 -60.9            0.0107 
//		4 "DPA "        0.0365 -75.4            0.0118 
//		5 "EPA "       -0.491  -59.0            0.00157
//		6 "LIN "        0.798  -76.0            0.00205
//		7 "OLA "        0.685  -74.1            0.00201
		
		
	    mantle_ALA_muss[box] = max<double>(0,mantle_ALA_muss[box]) ; 
	    mantle_ARA_muss[box] = max<double>(0,mantle_ARA_muss[box]) ; 
	    mantle_DHA_muss[box] = max<double>(0,mantle_DHA_muss[box]) ; 
	    mantle_EPA_muss[box] = max<double>(0,mantle_EPA_muss[box]) ; 
	    mantle_LIN_muss[box] = max<double>(0,mantle_LIN_muss[box]) ; 
		
 
 		
	// digestive gland
		//gland_ALA_muss[box] = gland_ALA_muss[box] + 1e3*W[1][box]*( 0.00000729      +        0.0138*ALA_intake) ; 
		//gland_ARA_muss[box] = gland_ARA_muss[box] + 1e3*W[1][box]*( 0.000000310     +        0.0191*ARA_intake ); 
		//gland_DHA_muss[box] = gland_DHA_muss[box] + 1e3*W[1][box]*( -0.00000636       +       0.0414*DHA_intake) ; 
		//gland_EPA_muss[box] = gland_EPA_muss[box] + 1e3*W[1][box]*( -0.00000723        +      0.0244*EPA_intake) ; 
		//gland_LIN_muss[box] = gland_LIN_muss[box] + 1e3*W[1][box]*(  0.00000142   +           0.012*LIN_intake ); 
		
			
			
		gland_ALA_muss[box] = gland_ALA_muss[box] +0.25*(0.429)*1e3*W[1][box]*(       0.288*ALA_intake) ; 
		gland_ARA_muss[box] = gland_ARA_muss[box] +0.25*(0.429)*1e3*W[1][box]*(        0.292*ARA_intake ); 
		gland_DHA_muss[box] = gland_DHA_muss[box] +0.25* (0.429)*1e3*W[1][box]*(       0.275*DHA_intake) ; 
		gland_EPA_muss[box] = gland_EPA_muss[box] +0.25* (0.429)*1e3*W[1][box]*(       0.0773*EPA_intake) ; 
		gland_LIN_muss[box] = gland_LIN_muss[box] +0.25*(0.429)*1e3*W[1][box]*(         0.170*LIN_intake ); 
		
		
 
 
   
 
			
	    gland_ALA_muss[box] = max<double>(0,gland_ALA_muss[box]) ; 
	    gland_ARA_muss[box] = max<double>(0,gland_ARA_muss[box]) ; 
	    gland_DHA_muss[box] = max<double>(0,gland_DHA_muss[box]) ; 
	    gland_EPA_muss[box] = max<double>(0,gland_EPA_muss[box]) ; 
	    gland_LIN_muss[box] = max<double>(0,gland_LIN_muss[box]) ; 
		
 
 
	// gill
			//gill_ALA_muss[box] = gill_ALA_muss[box] + 1e3*W[1][box]*(   2.93e-7         -0.000145*ALA_intake ); 
			//gill_ARA_muss[box] = gill_ARA_muss[box] + 1e3*W[1][box]*(  -5.44e-8     +   0.00289 *ARA_intake) ; 
			//gill_DHA_muss[box] = gill_DHA_muss[box] + 1e3*W[1][box]*(  -1.08e-6       +  0.00146 *DHA_intake) ; 
			//gill_EPA_muss[box] = gill_EPA_muss[box] + 1e3*W[1][box]*(  -8.88e-7       +  0.000458*EPA_intake ); 
			//gill_LIN_muss[box] = gill_LIN_muss[box] + 1e3*W[1][box]*(   1.58e-7      +    0.000331*LIN_intake) ; 


		
			
		gill_ALA_muss[box] = gill_ALA_muss[box] + 0.25*(0.429)*1e3*W[1][box]*(    0.0124*ALA_intake ); 
		gill_ARA_muss[box] = gill_ARA_muss[box] + 0.25*(0.429)*1e3*W[1][box]*(  0.0781*ARA_intake) ; 
		gill_DHA_muss[box] = gill_DHA_muss[box] +0.25*(0.429)*1e3*W[1][box]*(   -0.0662*DHA_intake) ; 
		gill_EPA_muss[box] = gill_EPA_muss[box] +0.25* (0.429)*1e3*W[1][box]*(  -0.0732*EPA_intake ); 
		gill_LIN_muss[box] = gill_LIN_muss[box] +0.25* (0.429)*1e3*W[1][box]*(   0.0262*LIN_intake) ; 
			
  

     
		    gill_ALA_muss[box] = max<double>(0,gill_ALA_muss[box]) ; 
		    gill_ARA_muss[box] = max<double>(0,gill_ARA_muss[box]) ; 
		    gill_DHA_muss[box] = max<double>(0,gill_DHA_muss[box]) ; 
		    gill_EPA_muss[box] = max<double>(0,gill_EPA_muss[box]) ; 
		    gill_LIN_muss[box] = max<double>(0,gill_LIN_muss[box]) ; 
			 
  
  
		}
			   
	  	 
	
/********************/
/* Cucumber DEB model */
/********************/
	
	
	U_d = 0 ; 
	F[2][box] = 0 ; 
	D_excr = 0 ; 
	M[2] = 0 ; 
	
		if(t>999999999){
	
// Functional response for sea cucumber
    func_response[2] = POC[box] /(POC[box] + X_Hd) ; 
	
// Temperature effect on sea cucumber
	Temp_effect[2] = k_0*exp( (T_Ad/T_0) -  (T_Ad/T) )* ( 1/ (1 + exp(  (T_ALd/T) -  (T_ALd/T_Ld) ) + exp(  (T_AHd/T_Hd) - (T_AHd/T)   )  ) )  ; 
	
// Consumption rate of sea cucumber
	U_d = Temp_effect[2]*func_response[2]*U_md*pow(V[2][box],0.67);  
	
// sea cucumber assimilation rate
	P_A[2] = Temp_effect[2]*func_response[2]*p_Ad* pow(V[2][box],.67) ;
	
// sea cucumber energy density
	Ed = E[2][box]/V[2][box] ; 
	
// sea cucumber catabolic rate
	P_C[2] = Temp_effect[2]*(Ed/ ( (kappa_d*Ed)+E_Gd))*(  ( (E_Gd*p_Ad*pow(V[2][box],0.67)) / E_md ) +p_Md*V[2][box] ) ; 
	
// sea cucumber maintenance rate
	P_M[2] = Temp_effect[2]* p_Md * V[2][box] ; 
	
//  sea cucumber maturity maintenance
	P_J[2] = std::min(V[2][box], V_pd)*p_Md*(1-kappa_d)/kappa_d;
	
// sea cucumber faeces
	F[2][box] = U_d - (P_A[2]/mu_CJ) ; 
	
	
	
// sea cucumber excretions
	D_excr =  ( (P_C[2]- (1 - kappa_Rd)*( (1-kappa_d)*P_C[2] -  P_J[2]) - mu_Vd*rho*( (kappa_d*P_C[2] - P_M[2])*(1/E_Gd) ) )*Q_d + P_A[2]*std::max<double>(0,(Q_s - Q_d) ) )/mu_CJ ; 
	
	
	
// sea cucumber carbon loss
	M[2] = delta_rd*N[2][box]*(V[2][box]*rho*mu_Vd + (E[2][box]+E_R[2][box]*kappa_Rd) )/mu_CJ ; 
	
// sea cucumber weight
	W[2][box] = V[2][box]*rho + (E[2][box] + E_R[2][box]*kappa_Rd)/mu_Ed;
	
	
/* Update biovolume V and energy E  */

// sea cucumber energy density 
	E[2][box] = E[2][box] + (P_A[2] - P_C[2]) ;
	
// sea cucumber reproductive reserves 
	E_R[2][box] = E_R[2][box] + (1-kappa_d)*P_C[2] -  P_J[2] ; 
	
// sea cucumber biovolume 
	
	V[2][box] = V[2][box] + std::max<double>(0,(kappa_d*P_C[2] -  P_M[2]))*(1/E_Gd) ; 
	
	
// sea cucumber Length 
	L[2][box] = (1/delta_md)*pow(V[2][box],0.33) ; 	
	
	
}
	
	
/********************/
/* Seaweed model */
/********************/
	
	
	
	
	U_nha = 0 ; 
	U_noa= 0 ;
	U_ca = 0;
	U_na = 0 ; 

	A_excr = 0 ;
	 
	
	
if(t>= SeaweedStart & t<= SeaweedEnd & (box==0 | box ==2))
{
	
 
 
// Temperature effect on seaweed
	Temp_effect[3] = k_0*exp( (T_Aa/T_0) -  (T_Aa/T) )* ( 1/ (1 + exp(  (T_ALa/T) -  (T_ALa/T_La) ) + exp(  (T_AHa/T_Ha) - (T_AHa/T)   )  ) )  ; 
	
// Potential uptake of ammonium N by seaweed (d−1)
	U_nha =  U_nhma*(  NH[box] / (NH[box] + X_anh) ) ; 

//Potential uptake of nitrate N by seaweed (d−1)
	U_noa = U_noma* ( NO[box] / (NO[box] + X_ano)) ; 
	 	
//	Uptake of C by seaweed (mgC d−1)
	U_ca = f_L_seaweed*CA[box]*Temp_effect[3]*G_am* std::max<double>(0, (1 - (Q_amin/Q_a)) ) ; 	

	 //U_ca = f_L*CA[box]*G_am* std::max<double>(0, (1 - (Q_amin/Q_a)) ) ; 	

		
// Total uptake of N by seaweed (mgN d−1)
	U_na = NAs[box]*Temp_effect[3]*(U_nha + U_noa) / ( 1 + exp( (Q_a-Q_amax)/Q_aoff    )    ) ; 	
	
// Seaweed N quota (mgN mgC−1)
	Q_a = NAs[box]/CA[box] ; 
 
// Seaweed biomass (kg m−3)
	W_a = CA[box] / (mu_CA*pow(10,6)) ; 
	
// Seaweed excretion (mgN d−1)
	A_excr =  e_ua*U_na + r_a*Temp_effect[3]*CA[box]*Q_a ; 
	
	
/* Update carbon CA and nitrogen NAs  */
	
	CA[box] = CA[box] + U_ca - r_a*Temp_effect[3]*CA[box] - (delta_ra + delta_ha)*CA[box] ; 		
		
	NAs[box] = NAs[box] + (1-e_ua)*U_na - r_a*Temp_effect[3]*NAs[box] - (delta_ra + delta_ha)*NAs[box] ; 		
 
 
   
		
}
				
fish_feces[box] = 0 ;
  
  
	 	 
/* hydrodynamics */


  

  
   	
	

	
	
/***********************/
/* 	Pelagic organisms  */
/***********************/


CZ_rate_change  =  G_z - CZ_rho ; 
CZ[box]  = std::max<double>(CZ[box], 	0.000001 ) ; 


EZ_rate_change =  (1-d_z)*(U_zp+U_zo) - G_z-EZ_rho ;
EZ[box]  = std::max<double>(EZ[box], 	0.000001 ) ; 
 
	
	
/* Phytoplankton carbon */
 

CP_rate_change =  U_cp - r_p*Temp_effect[4]*CP[box] - U_zp - ((U_mp*N[1][box]) / Volume[box]) - M_p ; 

 
/* Phytoplankton nitrogen */

NP_rate_change =  (1-e_up)*U_np - r_p*Temp_effect[4]*NP[box] - Q_p*U_zp - (Q_p*U_mp*N[1][box])/Volume[box] - Q_p*M_p ; 

	

	
/***********************/
/* 	Particulates   */
/***********************/

fish_feces[box] = F[0][box] ; 

	
/* Pelagic non-plankton organic carbon */	
	
	
POC_rate_change_non_salmon_feces = (1-k_sr - k_db)*(Z_f - U_zo + (F[1][box]*N[1][box]/Volume[box]) - (U_mo*N[1][box]/Volume[box])  + (gamma_0*CS[box]/H[box]) -lambda_0*POC[box]) ; 
POC_rate_change_salmon_feces = (1-k_sr - k_db)*( (fish_feces[box]*N[0][box]/Volume[box])  ) ; 
POC_rate_change_salmon_feed = (1-k_sr - k_db)*(  (F_w/Volume[box]) ) ; 


	
POC_rate_change_non_salmon_feces  = std::max<double>(POC_rate_change_non_salmon_feces, 	0.000001 ) ; 
POC_rate_change_salmon_feces  = std::max<double>(POC_rate_change_salmon_feces, 	0.000001 ) ; 
POC_rate_change_salmon_feed  = std::max<double>(POC_rate_change_salmon_feed, 	0.000001 ) ; 

 
 	
/* Pelagic non-plankton organic nitrogen*/
	
PON_rate_change_non_salmon_feces = (1-k_sr - k_db)*(Q_z*Z_f - Q_o*U_zo +(Q_p*F[1][box]*N[1][box]/Volume[box]) -  (Q_o*U_mo*N[1][box]/Volume[box])  + (gamma_0*NS[box]/H[box]) -lambda_0*PON[box]) ; 
PON_rate_change_salmon_feces = (1-k_sr - k_db)*( (Q_f*fish_feces[box]*N[0][box]/Volume[box])  ) ; 
PON_rate_change_salmon_feed = (1-k_sr - k_db)*(  (Q_ff*F_w/Volume[box])  ) ; 
	
	
PON_rate_change_non_salmon_feces = std::max<double>(PON_rate_change_non_salmon_feces, 	0.000001 ) ; 	
PON_rate_change_salmon_feces  = std::max<double>(PON_rate_change_salmon_feces, 	0.000001 ) ; 
PON_rate_change_salmon_feed  = std::max<double>(PON_rate_change_salmon_feed, 	0.000001 ) ; 

 	
	
POC_non_salmon_feces[box] = POC_non_salmon_feces[box] + POC_rate_change_non_salmon_feces ; 
PON_non_salmon_feces[box] = PON_non_salmon_feces[box] + PON_rate_change_non_salmon_feces ; 

 
POC_salmon_feces[box] = POC_salmon_feces[box] + POC_rate_change_salmon_feces ; 
PON_salmon_feces[box] = PON_salmon_feces[box] + PON_rate_change_salmon_feces ; 


POC_salmon_feed[box] = POC_salmon_feed[box] + POC_rate_change_salmon_feed ; 
PON_salmon_feed[box] = PON_salmon_feed[box] + PON_rate_change_salmon_feed ; 


POC[box] = POC_non_salmon_feces[box]  +  POC_salmon_feces[box]   + POC_salmon_feed[box]    ; 
PON[box] = PON_non_salmon_feces[box]  +  PON_salmon_feces[box]  +  PON_salmon_feed[box]  ; 
 
 
 
 
 
 
/* Pelagic non-plankton organic carbon available for mussel consumption */	
		
POCmuss_rate_change_non_salmon_feces  =  (1-k_sr - k_db)*(Z_f - U_zo - (U_mo*N[1][box]/Volume[box])  + (gamma_0*CS[box]/H[box]) -lambda_0*POC[box]) ; 
	
 
 	
POCmuss_rate_change_non_salmon_feces  = std::max<double>(POCmuss_rate_change_non_salmon_feces, 	0.000001 ) ; 
 	
	
POCmuss_non_salmon_feces[box] = POCmuss_non_salmon_feces[box] + POCmuss_rate_change_non_salmon_feces ; 

POCmuss[box] = POCmuss_non_salmon_feces[box]  +  POC_salmon_feces[box]  ; 


smallparticle_zoo = 0.042577875 ;
largeparticle_zoo = 0.435643198;
toolargeparticle_zoo = 0.521778927;	
	
smallparticles[box] = smallparticles[box]+ smallparticle_zoo*POCmuss_non_salmon_feces[box] + smallparticle_salmon*(POC_salmon_feces[box] ) ; 

largeparticles[box] = largeparticles[box] + largeparticle_zoo*POCmuss_non_salmon_feces[box] + largeparticle_salmon*(POC_salmon_feces[box] ) ; 

largeparticles_salmon[box] =  largeparticles_salmon[box]  + largeparticle_salmon*(POC_salmon_feces[box] ) ; 
	
toolargeparticles[box] = toolargeparticle_zoo*POCmuss_non_salmon_feces[box] +toolargeparticle_salmon*(POC_salmon_feces[box]  ) + 1*POC_salmon_feed[box] ; 
						



 
smallparticles_prop[box] = smallparticles[box] / (smallparticles[box]+largeparticles[box]+toolargeparticles[box]) ; 
largeparticles_prop[box] = largeparticles[box] / (smallparticles[box]+largeparticles[box]+toolargeparticles[box]); 

largeparticles_prop[box] = 1 - smallparticles_prop[box] - largeparticles_prop[box] ; 

largeparticles_salmon_prop[box] = largeparticles_salmon[box] / (largeparticles[box])  ; 

	
/*
	
smallparticles[box] = smallparticles[box]+ smallparticle_zoo*Z_f + smallparticle_salmon*(POC_salmon_feces[box] ) ; 

largeparticles[box] = largeparticles[box] + largeparticle_zoo*Z_f + largeparticle_salmon*(POC_salmon_feces[box] ) ; 

largeparticles_salmon[box] =  largeparticles_salmon[box]  + largeparticle_salmon*(POC_salmon_feces[box] ) ; 

largeparticles_salmon_prop[box] = largeparticles_salmon[box] / largeparticles[box]  ; 
	
toolargeparticles[box] =
	(F[1][box]*N[1][box]/Volume[box] ) +
			         (F_w/Volume[box] )  +
					    toolargeparticle_zoo*Z_f +
								    toolargeparticle_salmon*(POC_salmon_feces[box] ) ; 
						



 
smallparticles_prop[box] = smallparticles[box] / (smallparticles[box]+largeparticles[box]) ; 
largeparticles_prop[box] = largeparticles[box] / (smallparticles[box]+largeparticles[box]); 
 
 
 */

//if(t>= MusselStart & t<= MusselEnd & (box==0) )
//	printf("%G %G %G\n",largeparticles_salmon_prop[box], smallparticles_prop[box],largeparticles_prop[box] ) ; 
		
/***********************/
/* 	Nitrogen   */
/***********************/		
		


/* Dissolved organic nitrogen */
	
	
ND_rate_change =  phi*(P_excr+A_excr) - k_or*ND[box] ;  
ND[box] = max<double>(0.001,ND[box]) ; 
 	

if((U_noa +U_nha) >0){
	Seaweed_ammonium_uptake = (U_na*U_nha)/(U_noa + U_nha) ; 
	Seaweed_nitrate_uptake = ( (U_na*U_noa) / (U_noa+U_nha) ) ; 
	}
	else {
	    Seaweed_ammonium_uptake=0 ; Seaweed_nitrate_uptake = 0 ;
	}
	
	 
if ((t< SeaweedStart) || (t>SeaweedEnd) ) { Seaweed_ammonium_uptake = 0  ;Seaweed_nitrate_uptake = 0  ; }
	
/* Ammonium nitrogen */
	
NH_rate_change =  (1-phi)*(P_excr + A_excr) -  (U_np*U_nhp)/(U_nop + U_nhp) - Seaweed_ammonium_uptake - 
		(k_nit*NH[box]) + (k_or*ND[box]) + (k_sr*(NS[box]/H[box]) ) + (k_sr*PON[box]) + (N[1][box]*M_excr + N[0][box]*F_excr)/Volume[box]  + Z_excr ; 
	
	 	
/* Nitrate nitrogen */
	
	NO_rate_change =  k_nit*NH[box] -  ( (U_np*U_nop) / (U_nop+U_nhp) ) -  Seaweed_nitrate_uptake - k_denit * NO[box] ; 
	
		    
 
	
		
		
		
		
		
/*********************************/
/*  Benthic carbon and nitrogen  */
/*********************************/
		

/* Sediment organic carbon */
		

CS_rate_change =  (lambda_0*POC[box] + M_p + M_z)*H[box]  + (M[1] + M[0] + delta_ra*CA[box] )/Area[box] - gamma_0*CS[box] - (k_sr + k_db)*CS[box] ; 

CS[box] = CS[box] + CS_rate_change ; 
 
CS[box] = max<double>(0,CS[box]) ; 
 
 
/* Sediment organic nitrogen */

NS_rate_change = (lambda_0*PON[box] + Q_p*M_p + Q_z*M_z )*H[box]  + (Q_m*M[1] + Q_f*M[0] + delta_ra*NAs[box])/Area[box] - gamma_0*NS[box] - (k_sr+k_db)*NS[box] ; 


NS[box] = NS[box] + NS_rate_change ;

NS[box] = max<double>(0,NS[box]) ; 
		
		
 
CP[box] = CP[box] + (1/1)*CP_rate_change ;
CP[box]  = std::max<double>(CP[box], 	0.000001 ) ; 


NP[box] = NP[box] + (1/1)*NP_rate_change ;
NP[box]  = std::max<double>(NP[box], .18*0.000001   ) ; 	

CZ[box] = CZ[box] + (1/1)*CZ_rate_change ;
EZ[box] = EZ[box] + (1/1)*EZ_rate_change ;
NH[box] = NH[box] + (1/1)*NH_rate_change ;
ND[box] = ND[box] + (1/1)*ND_rate_change ;
NO[box] = NO[box] + (1/1)*NO_rate_change ;

  
NH[box] = max<double>(0,NH[box]) ; 
ND[box] = max<double>(0,ND[box]) ;
NO[box] = max<double>(0,NO[box]) ; 
   
   
   
   

for( int NUM = 0; NUM < 1; NUM++)
{
	
 
	if(TRANSPORT[9*box+8+TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t]<1e-10) { POC_salmon_feces[box] = 0 ; PON_salmon_feces[box] = 0 ; }
	if(TRANSPORT[9*box+8+TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t]>1e-10) { 
		POC_salmon_feces[box] = (1/TRANSPORT[9*box+8+TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t])*(POC_salmon_feces[0]*TRANSPORT[9*box+TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] +
			 POC_salmon_feces[1]*TRANSPORT[9*box+1+TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] +
				 		 POC_salmon_feces[2]*TRANSPORT[9*box+2+TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] +
							 		 POC_salmon_feces[3]*TRANSPORT[9*box+3+TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] +
										 		 POC_salmon_feces[4]*TRANSPORT[9*box+4+TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] +
													 POC_salmon_feces[5]*TRANSPORT[9*box+5+TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] +
													 POC_salmon_feces[6]*TRANSPORT[9*box+6+TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] ) ; 
 
PON_salmon_feces[box] = Q_f*POC_salmon_feces[box] ; 
 
}


 
  
  

CP[box] = (1/TRANSPORT[9*box+3*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+8])*(CP[0]*TRANSPORT[9*box+3*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] +
	 CP[1]*TRANSPORT[9*box+3*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+1] +  CP[2]*TRANSPORT[9*box+3*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+2]  +
		 CP[3]*TRANSPORT[9*box+3*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+3]  + CP[4]*TRANSPORT[9*box+3*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+4]  +
			 CP[5]*TRANSPORT[9*box+3*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+5]  +
				 CP[6]*TRANSPORT[9*box+3*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+6]  +
		 1*background_plankton0*TRANSPORT[9*box+3*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+7] ) ; 
 

NP[box] = Q_p*CP[box] ; 
 
 
 
double ez_cz_ratio ;
ez_cz_ratio =  EZ[box]/CZ[box] ; 
 
 
  
CZ[box] = (1/TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+8])*(CZ[0]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] +
	 CZ[1]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+1] +  CZ[2]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+2]  +
		 CZ[3]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+3]  + CZ[4]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+4]  +
			 CZ[5]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+5]  +
				  CZ[6]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+6]  +
		 1*background_zoo0*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+7] ) ; 
 
 	 
EZ[box] = ez_cz_ratio*CZ[box]  ; 
 	
POC_non_salmon_feces[box] = (1/TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+8])*(POC_non_salmon_feces[0]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] +
	 POC_non_salmon_feces[1]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+1] +  POC_non_salmon_feces[2]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+2]  +
		 POC_non_salmon_feces[3]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+3]  + POC_non_salmon_feces[4]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+4]  +
			 POC_non_salmon_feces[5]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+5]  +
				  POC_non_salmon_feces[6]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+6]  +
		 1*background_POC0*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+7] ) ; 
  
	 	
PON_non_salmon_feces[box] = Q_f*POC_non_salmon_feces[box] ;
  
  
  
 	
POCmuss_non_salmon_feces[box] = (1/TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+8])*(POCmuss_non_salmon_feces[0]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] +
	 POCmuss_non_salmon_feces[1]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+1] +  POCmuss_non_salmon_feces[2]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+2]  +
		  POCmuss_non_salmon_feces[3]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+3] +  POCmuss_non_salmon_feces[4]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+4] +
			   POCmuss_non_salmon_feces[5]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+5] +
				    POCmuss_non_salmon_feces[6]*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+6] +
		 +1*background_POC0*TRANSPORT[9*box+2*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t+7] ) ; 
  
  
      
   
   
   
 
NH[box] = (1/TRANSPORT[9*box+8+ 5*TRANSPORT_LENGTH0*t])*(NH[0]*TRANSPORT[9*box+ 5*TRANSPORT_LENGTH0*t] + NH[1]*TRANSPORT[9*box+1+ 5*TRANSPORT_LENGTH0*t] +  NH[2]*TRANSPORT[9*box+2+ 5*TRANSPORT_LENGTH0*t] +  NH[3]*TRANSPORT[9*box+3+ 5*TRANSPORT_LENGTH0*t]+ 
	 NH[4]*TRANSPORT[9*box+4+ 5*TRANSPORT_LENGTH0*t] + 
		  NH[5]*TRANSPORT[9*box+5+ 5*TRANSPORT_LENGTH0*t] +
			   NH[6]*TRANSPORT[9*box+6+ 5*TRANSPORT_LENGTH0*t] +
		  1*background_NH0*TRANSPORT[9*box+7+ 5*TRANSPORT_LENGTH0*t] ) ; 
  
 
ND[box] = (1/TRANSPORT[9*box+8+ 5*TRANSPORT_LENGTH0*t])*(ND[0]*TRANSPORT[9*box+ 5*TRANSPORT_LENGTH0*t] + ND[1]*TRANSPORT[9*box+1+ 5*TRANSPORT_LENGTH0*t] + 
	 ND[2]*TRANSPORT[9*box+2+ 5*TRANSPORT_LENGTH0*t] +  ND[3]*TRANSPORT[9*box+3+ 5*TRANSPORT_LENGTH0*t]+ 
	 ND[4]*TRANSPORT[9*box+4+ 5*TRANSPORT_LENGTH0*t] + 
		  ND[5]*TRANSPORT[9*box+5+ 5*TRANSPORT_LENGTH0*t] +
			  		  ND[6]*TRANSPORT[9*box+6+ 5*TRANSPORT_LENGTH0*t] +
			   1*background_DON0*TRANSPORT[9*box+7+ 5*TRANSPORT_LENGTH0*t] ) ; 
  
  
 
NO[box] = (1/TRANSPORT[9*box+8+ 5*TRANSPORT_LENGTH0*t])*(NO[0]*TRANSPORT[9*box+ 5*TRANSPORT_LENGTH0*t] + NO[1]*TRANSPORT[9*box+1+ 5*TRANSPORT_LENGTH0*t] + 
	NO[2]*TRANSPORT[9*box+2+ 5*TRANSPORT_LENGTH0*t] +  NO[3]*TRANSPORT[9*box+3+ 5*TRANSPORT_LENGTH0*t]+ 
	 NO[4]*TRANSPORT[9*box+4+ 5*TRANSPORT_LENGTH0*t] + 
		  NO[5]*TRANSPORT[9*box+5+ 5*TRANSPORT_LENGTH0*t] +
			  		  NO[6]*TRANSPORT[9*box+6+ 5*TRANSPORT_LENGTH0*t] +
			   1*background_NO0*TRANSPORT[9*box+7+ 5*TRANSPORT_LENGTH0*t] ) ; 
  
 
 
// Feed transport
	if(TRANSPORT[9*box+8+4*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t]<1e-10) { POC_salmon_feed[box] = 0 ; PON_salmon_feed[box] = 0 ; }
	if(TRANSPORT[9*box+8+4*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t]>1e-10) { 
		POC_salmon_feed[box] = (1/TRANSPORT[9*box+8+4*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t])*(POC_salmon_feed[0]*TRANSPORT[9*box+4*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] +
			 POC_salmon_feed[1]*TRANSPORT[9*box+1+4*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] +
				 		 POC_salmon_feed[2]*TRANSPORT[9*box+2+4*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] +
							 		 POC_salmon_feed[3]*TRANSPORT[9*box+3+4*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] +
										 		 POC_salmon_feed[4]*TRANSPORT[9*box+4+4*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] +
													 POC_salmon_feed[5]*TRANSPORT[9*box+5+4*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] +
													 POC_salmon_feed[6]*TRANSPORT[9*box+6+4*TRANSPORT_LENGTH0 + 5*TRANSPORT_LENGTH0*t] ) ; 
 
PON_salmon_feed[box] = Q_ff*POC_salmon_feed[box] ; 
 
}
 
 
}
 
 
     
 
 
	
// EXPORT = CONCENTRATION IN BOX *(1-PROB IT STAYS THERE)
	
	
	// 0  6 8 9 10 1 2 3 4 5 7  

  


if(t==0 & box==0) 
	fprintf( file11,"box PROP_SALMON PROP_NON_SALMON POC_salmon_feces \n") ; 

fprintf( file11, "%d %G %G %G\n",
				box, PROP_FOOD_SALMON_POO, PROP_FOOD_ZOO,POC_salmon_feces[box] ) ; 
				
 
 

if(t==0 & box==0) 
	fprintf( file99,"BOX salmon_biomass FEED waste_feed fish_feces mantle_ALA_muss[box] mantle_ARA_muss[box] mantle_DHA_muss[box] mantle_EPA_muss[box] mantle_LIN_muss[box] gland_ALA_muss[box] gland_ARA_muss[box] gland_DHA_muss[box] gland_EPA_muss[box] gland_LIN_muss[box] gill_ALA_muss[box] gill_ARA_muss[box] gill_DHA_muss[box] gill_EPA_muss[box] gill_LIN_muss[box] salmon_ALA salmon_ARA salmon_EPA salmon_DHA salmon_LIN Time C_sediment N_sediment N_Nitrate N_DON N_Ammonium C_POC N_PON C_phytoplankton N_phytoplankton C_Zooplankton_structure C_Zooplankton_reserves C_seaweed N_seaweed No_salmon No_mussel No_sea_cucumber E_salmon E_mussel E_sea_cucumber E.R_salmon E.R_mussel E.R_sea_cucumber V_salmon V_mussel V_sea_cucumber L_salmon L_mussel L_sea_cucumber W_salmon W_mussel W_sea_cucumber \n") ; 

fprintf( file99, "%d %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %d %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G %G\n",
				box,	B[0][box], .5*1e3*FEED,F_w,N[0][box]*fish_feces[box],mantle_ALA_muss[box],mantle_ARA_muss[box],mantle_DHA_muss[box],mantle_EPA_muss[box],mantle_LIN_muss[box],
				gland_ALA_muss[box],gland_ARA_muss[box],gland_DHA_muss[box],gland_EPA_muss[box],gland_LIN_muss[box],
				gill_ALA_muss[box],gill_ARA_muss[box],gill_DHA_muss[box],gill_EPA_muss[box],gill_LIN_muss[box],
				ALA[box], ARA[box], EPA[box], DHA[box], LIN[box], t, CS[box], NS[box], NO[box], ND[box], NH[box],
				POC[box], PON[box], CP[box],NP[box],CZ[box],EZ[box],
				 CA[box],NAs[box], N[0][box],N[1][box],N[2][box],E[0][box],E[1][box],E[2][box],
				 	E_R[0][box],	E_R[1][box],	E_R[2][box] ,
					 V[0][box],	V[1][box],	V[2][box],
					 	L[0][box] ,	L[1][box] , 	L[2][box], W[0][box],W[1][box],W[2][box]  ) ; 
					 
 			

 	
	
} 
  
  			 
     				 
				 

}

printf("it ran");


fclose(file11) ;

fclose(file99) ;
	
  

return(0);


	}



}


