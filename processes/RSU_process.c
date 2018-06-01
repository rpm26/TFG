/*
 * RSU_process.c
 *
 *  Created on: 12 mar. 2018
 *      Author: rpita
 */


/*
 * OBU_process.c
 *
 *  Created on: 12 mar. 2018
 *      Author: rpita
 */


/*
 * rpita_OBU.c
 *
 *  Created on: 15 nov. 2017
 *      Author: rpita
 */
/*
 * rpita_uc.c
 *
 *  Created on: 12 sept. 2017
 *      Author: rosa
 */


#include "system_api.h"
#include "net_api.h"
#include "time_meas.h"
#include "system_net_api.h"

#include "althLoc_comm.h"
#include "node_info.h"
#include "localization_FRORF.h"

#define USE_OBU_PROCESS	1
#if USE_OBU_PROCESS

#define NET_PORT1	120
#define NET_PORT2	121

/* RSU PROCESS ************************************/
extern YT_PROCESS void RSU_func(void const * argument);
/*---------------------------------------------------------------------------*/


extern YT_PROCESS void RSU_func(void const * argument){

	node_data_t* node_data = (node_data_t*) argument;

	define_addr(node_data->node_id);

	pos_OBU_t* pos_OBU;
	char net_addr[8];
	node_pck_t* node_pck;
	float32_t* rssi;

	while(1){

		pos_OBU=ytMalloc(sizeof(pos_OBU_t));
		node_pck=ytMalloc(sizeof(node_pck_t));
		rssi=ytMalloc(sizeof(float32_t));

		if(RSU_rcv_pck(pos_OBU, rssi,(char*)net_addr,NET_PORT1)){

			node_pck->Lat =node_data->Lat;
			node_pck->Long =node_data->Long;
			node_pck->rssi =rssi[0] ;

			ytDelay(rand()%100);
			set_routes((char*)net_addr);
			RSU_Send_pck(node_pck,(char*) net_addr,NET_PORT2);
			remove_route((char*)net_addr);
		}

		ytFree(pos_OBU);
		ytFree(node_pck);
		ytFree(rssi);

	}

}

#endif
