/*
 * localization_FRORF.c
 *
 *  Created on: 11 abr. 2018
 *      Author: rpita
 */
#include "localization_FRORF.h"

static pos_OBU_t* pos ;
static uint16_t rsuProcId;
static uint16_t obuProcId;

YT_PROCESS void RSU_func(void const * argument);
YT_PROCESS void OBU_func(void const * argument);

pos_OBU_t* get_pos_FRORF(void){

	return pos;
}
void set_pos_FRORF(pos_OBU_t* pos_t){

	pos->Lat=pos_t->Lat;
	pos->Long=pos_t->Long;
}

void init_FRORF(node_data_t* node_data, uint8_t type){

	pos = ytMalloc(sizeof(pos));

	if(type==1){

		ytStartProcess("OBU_process", OBU_func, DEFAULT_PROCESS, 256, &obuProcId,(void*) node_data);
	}

	if(type==2){
		ytStartProcess("RSU_process", RSU_func, DEFAULT_PROCESS, 256, &rsuProcId,(void*) node_data);
	}

}
