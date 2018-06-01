/*
 * node_info.h
 *
 *  Created on: 9 mar. 2018
 *      Author: rpita
 */

#ifndef APPLICATION_CORE_RPITA_LIBS_NODE_INFO_H_
#define APPLICATION_CORE_RPITA_LIBS_NODE_INFO_H_

#include "generic_list.h"
#include "system_api.h"
#include "net_api.h"
#include "time_meas.h"
#include "system_net_api.h"

typedef struct node_info {

	gen_list* node_List;

	float32_t Lat;
	float32_t Long;
	float32_t rssi;
	float32_t* distToRsu;
	float32_t dist_OBU;
	uint8_t reg;
	uint8_t node_id;
	char* address;

}node_info;

gen_list* new_nodes_List(void);

node_info* create_node(gen_list* node_List,uint8_t node_id);

void setLat(gen_list* node_List, float32_t Lat, uint8_t node_id);
void setLong(gen_list* node_List, float32_t Long, uint8_t node_id);
void setRssi(gen_list* node_List, float32_t rssi, uint8_t node_id);
void setDistToRSU(gen_list* node_List, float32_t* distToRsu, uint8_t node_id);
void setDistToOBU(gen_list* node_List, float32_t distToOBU, uint8_t node_id);
void setReg(gen_list* node_List, uint8_t reg, uint8_t node_id);

uint8_t addNodeInfo(gen_list* node_List,float32_t Lat,float32_t Long,float32_t rssi,char*addr);

node_info* getNodeInfo(gen_list* node_List, uint8_t node_id);
uint8_t ListLength(gen_list* node_List);
uint8_t containNode(gen_list* node_List,char* addr);

void remove_AllPositions(gen_list* node_List);
void remove_Node(gen_list* node_List, uint8_t node_id);
void remove_NodeList(gen_list* node_List);

#endif /* APPLICATION_CORE_RPITA_LIBS_NODE_INFO_H_ */
