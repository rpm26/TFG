/*
 * rpita_comm.c
 *
 *  Created on: 9 mar. 2018
 *      Author: rpita
 */

#include "althLoc_comm.h"

int RSU_rcv_pck(pos_OBU_t* OBU_pck, float32_t* rssi, char* net_addr, uint8_t Port){

	ytNetAddr_t net_addr_t=new_net_addr("22222", 'D');

	ytUrOpen(Port);

	//Recepción
	if(ytUrRcv(Port, net_addr_t,(uint8_t*) OBU_pck, BUF_SIZE)){

		ytNetAddrToString(net_addr_t, net_addr, 'D');
		rssi[0]=ytUrGetSignalLevel(Port);

		delete_net_addr(net_addr_t);

		ytUrClose(Port);

		return 1;
	}

	delete_net_addr(net_addr_t);

	ytUrClose(Port);

	return 0;

}
int OBU_rcv_pck(node_pck_t* node_pck, char* net_addr, uint8_t Port){

	ytNetAddr_t net_addr_t=new_net_addr("22222", 'D');

	ytUrOpen(Port);

	//Recepción
	if(ytUrRcv(Port, net_addr_t,(uint8_t*) node_pck, BUF_SIZE)){

		ytNetAddrToString(net_addr_t, net_addr, 'D');
		delete_net_addr(net_addr_t);

		ytUrClose(Port);

		return 1;
	}

	delete_net_addr(net_addr_t);

	ytUrClose(Port);

	return 0;

}

void OBU_Send_pck(pos_OBU_t* OBU_pck, char* net_addr, uint8_t Port){

	ytUrOpen(Port);	//Abro el puerto

	ytNetAddr_t net_addr_t = new_net_addr(net_addr, 'D');

	ytUrSend(Port, net_addr_t,(uint8_t*) OBU_pck, sizeof(pos_OBU_t));

	ytUrClose(Port);
	delete_net_addr(net_addr_t);
}

void RSU_Send_pck(node_pck_t* node_pck, char* net_addr, uint8_t Port){

	ytUrOpen(Port);	//Abro el puerto

	ytNetAddr_t net_addr_t  = new_net_addr(net_addr, 'D');

	ytUrSend(Port, net_addr_t,(uint8_t*) node_pck, sizeof(node_pck_t));

	ytUrClose(Port);
	delete_net_addr(net_addr_t);
}

void set_routes(char* dest_addr){

	ytNetAddr_t net_addr;
	ytNetAddr_t next_addr;

	/* Set node Routes */
	net_addr = new_net_addr(dest_addr, 'D');		//Dest adress
	next_addr = new_net_addr(dest_addr, 'D');		//Next adress
	net_add_route(net_addr, next_addr, 0);
	delete_net_addr(net_addr);
	delete_net_addr(next_addr);
}

void define_addr(char* node_addr){

	ytNetAddr_t net_addr;

	/* Set node Addr */
	net_addr = new_net_addr(node_addr, 'D');	//Node adress
	net_add_node_addr(net_addr);
	delete_net_addr(net_addr);

}

void remove_route(char* node_addr){

	ytNetAddr_t net_addr;

	/*node Addr */
	net_addr = new_net_addr(node_addr, 'D');	//Node adress
	ytNetRemoveRoute(net_addr, net_addr, 0);
	delete_net_addr(net_addr);

}
