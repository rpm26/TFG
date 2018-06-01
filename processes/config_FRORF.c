/*
 * config_FRORF.c
 *
 *  Created on: 11 abr. 2018
 *      Author: rpita
 */

#include "localization_FRORF.h"

//#define NODE1 1
//#define NODE2 1
//#define NODE3 1
//#define NODE4 1
//#define NODE5 1
//#define NODE6 1
#define NODE7 1


extern void config_FRORF(){

#if NODE1

	node_data_t* node_data = ytMalloc(sizeof(node_data_t));
	node_data->node_id="1";

	init_FRORF(node_data,1);

	ytFree(node_data);

#endif

#if NODE2

	node_data_t* node_data = ytMalloc(sizeof(node_data_t));
	node_data->node_id="2";
	node_data ->Lat= 40.453511;
	node_data -> Long = -3.727350;

	init_FRORF(node_data,2);

#endif

#if NODE3

	node_data_t* node_data = ytMalloc(sizeof(node_data_t));
	node_data->node_id="3";
	node_data ->Lat=  40.453521 ;
	node_data -> Long = -3.727245 ;

	init_FRORF(node_data,2);

#endif

#if NODE4

	node_data_t* node_data = ytMalloc(sizeof(node_data_t));
	node_data->node_id="4";
	node_data ->Lat= 40.453432 ;
	node_data -> Long =-3.727334;

	init_FRORF(node_data,2);

#endif

#if NODE5

	node_data_t* node_data = ytMalloc(sizeof(node_data_t));
	node_data->node_id="5";
	node_data ->Lat=40.453444 ;
	node_data -> Long = -3.727232 ;

	init_FRORF(node_data,2);

#endif

#if NODE6

	node_data_t* node_data = ytMalloc(sizeof(node_data_t));
	node_data->node_id="6";
	node_data ->Lat=40.453601 ;
	node_data -> Long = -3.727260 ;

	init_FRORF(node_data,2);

#endif

#if NODE7

	node_data_t* node_data = ytMalloc(sizeof(node_data_t));
	node_data->node_id="7";
	node_data ->Lat=40.453592 ;
	node_data -> Long = -3.727365 ;

	init_FRORF(node_data,2);

#endif

}
