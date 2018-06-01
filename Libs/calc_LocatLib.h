/*
 * calc_LocatLib.h
 *
 *  Created on: 9 mar. 2018
 *      Author: rpita
 */

#ifndef APPLICATION_CORE_RPITA_LIBS_CALC_LOCATLIB_H_
#define APPLICATION_CORE_RPITA_LIBS_CALC_LOCATLIB_H_

#include "generic_list.h"
#include "althLoc_comm.h"

//Parámetros para el cáculo de la distancia con RSSI

#define V_LUZ 3e8
#define LOSS_EXP 2 // free-space=2  Relatively lossy enviroments=4  interior areas=6
#define POT_433_dbm 11
#define FREC_433 433e6
//#define INTERIOR 1
#define EXTERIOR 1

//#define PRECISION_GPS 1e-6

//Parámetros recta de ajuste
#if INTERIOR
#define A	2.9065
#define B	7.6813
#endif

#if EXTERIOR
#define A	8.8392
#define B	-5.4325
#endif

void get_PosOBU(gen_list* node_List,pos_OBU_t* pos_OBU);
void calc_dist_RSU(gen_list* node_List);
void calc_dist_OBU(gen_list* node_List);
void calc_region_OBU(gen_list* node_List);
void calc_COG(gen_list* node_List,pos_OBU_t* pos_OBU);

float transf_dist_grados(float dist);
float dist_square_int_grados(float dist);
float calc_dist_function(float lat1, float long1,float lat2, float long2);
void Bubble_Sort(float* dists, int num_nodos);
#endif /* APPLICATION_CORE_RPITA_LIBS_CALC_LOCATLIB_H_ */
