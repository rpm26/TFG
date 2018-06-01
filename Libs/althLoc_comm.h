/*
 * rpita_comm.h
 *
 *  Created on: 9 mar. 2018
 *      Author: rpita
 */

#ifndef APPLICATION_CORE_RPITA_LIBS_RPITA_COMM_H_
#define APPLICATION_CORE_RPITA_LIBS_RPITA_COMM_H_


#include "system_api.h"
#include "net_api.h"
#include "system_net_api.h"
#include "math.h"

#define BUF_SIZE	24

typedef struct __packed node_pck_t {

	float32_t Lat;
	float32_t Long;
	float32_t rssi;

}node_pck_t;

typedef struct __packed pos_OBU {

	float32_t Lat;
	float32_t Long;

}pos_OBU_t;

int RSU_rcv_pck(pos_OBU_t* OBU_pck, float32_t* rssi, char* net_addr, uint8_t Port);
int OBU_rcv_pck(node_pck_t* node_pck, char* net_addr, uint8_t Port);

void OBU_Send_pck(pos_OBU_t* OBU_pck, char* net_addr, uint8_t Port);
void RSU_Send_pck(node_pck_t* node_pck, char* net_addr, uint8_t Port);

void set_routes(char* dest_addr);
void remove_route(char* node_addr);
void define_addr(char* node_addr);


#endif /* APPLICATION_CORE_RPITA_LIBS_RPITA_COMM_H_ */
