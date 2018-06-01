/*
 * localization_FRORF.h
 *
 *  Created on: 11 abr. 2018
 *      Author: rpita
 */

#ifndef APPLICATION_LIBS_ALTHLOC_LIBS_LOCALIZATION_FRORF_H_
#define APPLICATION_LIBS_ALTHLOC_LIBS_LOCALIZATION_FRORF_H_


#include "system_api.h"
#include "net_api.h"
#include "system_net_api.h"
#include "althLoc_comm.h"

typedef struct node_data{

	char* node_id;
	float32_t Lat;
	float32_t Long;

}node_data_t;

YT_PROCESS void RSU_func(void const * argument);
YT_PROCESS void OBU_func(void const * argument);

pos_OBU_t* get_pos_FRORF(void);
void set_pos_FRORF(pos_OBU_t* pos);
void init_FRORF(node_data_t* node_data, uint8_t type);
#endif /* APPLICATION_LIBS_ALTHLOC_LIBS_LOCALIZATION_FRORF_H_ */
