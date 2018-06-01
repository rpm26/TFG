/*
 * node_info.c
 *
 *  Created on: 9 mar. 2018
 *      Author: rpita
 */

#include "node_info.h"

#include "generic_list.h"


gen_list* new_nodes_List(void){

	return gen_list_init();
}


uint8_t addNodeInfo(gen_list* node_List,float32_t Lat,float32_t Long,float32_t rssi,char* addr){

	if(containNode(node_List,addr)==0){

		node_info* node= ytMalloc(sizeof(node_info));
		node->address =ytMalloc(8*sizeof(char));

		node->node_id=ListLength(node_List);
		node->Lat=Lat;
		node->Long =Long;
		node -> rssi=rssi;
		strcpy(node->address,addr);

		node-> node_List=node_List;

		gen_list_add(node_List, (void*) node);

		return 1;

	}

	return 0;
}

node_info* getNodeInfo(gen_list* node_List, uint8_t node_id){

	gen_list* current = node_List;
	node_info* node;

	while(current->next!= NULL){

		current = current->next;

		node=current->item;

		if(node->node_id == node_id){

			return node;
		}


	}
	return node;
}

uint8_t containNode(gen_list* node_List,char* addr){

	gen_list* current = node_List;
	node_info* node;

	while(current->next!= NULL){

		current = current->next;
		node=current->item;

		if(node->address == addr){

			return 1;
		}


	}
	return 0;

}

void setLat(gen_list* node_List, float32_t Lat, uint8_t node_id){

	gen_list* current = node_List;
	node_info* node;

	while(current->next!= NULL){

		current = current->next;
		node=current->item;

		if(node->node_id == node_id){

			node->Lat=Lat;
		}

	}


}


void setLong(gen_list* node_List, float32_t Long, uint8_t node_id){

	gen_list* current = node_List;
	node_info* node;

	while(current->next!= NULL){

		current = current->next;
		node=current->item;

		if(node->node_id == node_id){

			node->Long=Long;
		}


	}
}

void setRssi(gen_list* node_List, float32_t rssi, uint8_t node_id){

	gen_list* current = node_List;
	node_info* node;

	while(current->next!= NULL){

		current = current->next;
		node=current->item;

		if(node->node_id == node_id){

			node->rssi=rssi;
		}


	}
}

void setDistToRSU(gen_list* node_List, float32_t* distToRsu, uint8_t node_id){

	gen_list* current = node_List;
	node_info* node;

	while(current->next!= NULL){

		current = current->next;
		node=current->item;

		if(node->node_id == node_id){

			node->distToRsu=distToRsu;
		}


	}
}

void setDistToOBU(gen_list* node_List, float32_t distToOBU, uint8_t node_id){

	gen_list* current = node_List;
	node_info* node;

	while(current->next!= NULL){

		current = current->next;
		node=current->item;

		if(node->node_id == node_id){

			node->dist_OBU=distToOBU;
		}


	}
}

void setReg(gen_list* node_List, uint8_t reg, uint8_t node_id){

	gen_list* current = node_List;
	node_info* node;

	while(current->next!= NULL){

		current = current->next;
		node=current->item;

		if(node->node_id == node_id){

			node->reg=reg;
		}

	}

}

uint8_t ListLength(gen_list* node_List){

	gen_list* current = node_List;
	uint8_t count=0;

	while(current->next!= NULL){

		count++;
		current = current->next;

	}
	return count;
}


void remove_Node(gen_list* node_List, uint8_t node_id){

	gen_list* current = node_List;
	node_info* node;

	while(current->next!= NULL){

		current = current->next;
		node=current->item;

		if(node->node_id == node_id){

			gen_list_remove(node_List, (void*) node);
		}

	}


}


void remove_AllPositions(gen_list* node_List){

	gen_list* current = node_List;
	node_info* node;
	uint8_t Length = ListLength(current);

	while(current->next!= NULL){

		current = current->next;
		node=current->item;
		ytFree(node->address);

		if(Length>1){

			ytFree(node->distToRsu);
		}

		gen_list_remove_and_delete(node_List, (void*) node);

	}
}

void remove_NodeList(gen_list* node_List){

	gen_list_remove_all(node_List);
}
