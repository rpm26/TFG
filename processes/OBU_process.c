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

#include "calc_LocatLib.h"
#include "node_info.h"

#include "localization_FRORF.h"

#define USE_OBU_PROCESS	1

#if USE_OBU_PROCESS

#define BC_DEST_ADDR		"65535"

#define NET_PORT1	120
#define NET_PORT2	121

static gen_list* nodeList;
static uint8_t recv=0;

/* OBU PROCESS ************************************/
extern YT_PROCESS void OBU_func(void const * argument);
YT_PROCESS void send_func(void const * argument);
YT_PROCESS void recv_func(void const * argument);

/*---------------------------------------------------------------------------*/


extern YT_PROCESS void OBU_func(void const * argument){

	node_data_t* node_data = (node_data_t*) argument;

	define_addr(node_data->node_id);

	static uint16_t sendProcessId;
	static uint16_t recvProcessId;

	ytStartProcess("send_process", send_func, DEFAULT_PROCESS, 256,  &sendProcessId,NULL);
	ytStartProcess("recv_process", recv_func, DEFAULT_PROCESS, 256,  &recvProcessId,NULL);

	nodeList = new_nodes_List();

	while(1){

		ytDelay(1000);

	}

}


YT_PROCESS void send_func(void const * argument){


	while(1){

		pos_OBU_t* pos_OBU=ytMalloc(sizeof(pos_OBU_t));
		get_PosOBU(nodeList,pos_OBU);

		remove_AllPositions(nodeList);


		OBU_Send_pck(pos_OBU, BC_DEST_ADDR,NET_PORT1);
		ytFree(pos_OBU);

		recv=1;
		ytDelay(110);
		recv=0;
	}
}


YT_PROCESS void recv_func(void const * argument){

	node_pck_t* node_pck;

	while(1){

		node_pck=ytMalloc(sizeof(node_pck_t));

		char* net_addr=ytMalloc(8*sizeof(char));

		if(OBU_rcv_pck(node_pck, (char*)net_addr,NET_PORT2)){

			if(recv){

			addNodeInfo(nodeList,node_pck->Lat,node_pck->Long,node_pck->rssi,(char*)net_addr);

			}
		}

		ytFree(net_addr);
		ytFree(node_pck);

	}
}

#endif
