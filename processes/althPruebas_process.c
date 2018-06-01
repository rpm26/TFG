
/*
 * pruebasAlth.c
 *
 *  Created on: 16 mar. 2018
 *      Author: rpita
 */


#include "system_api.h"
#include "net_api.h"
#include "calc_LocatLib.h"
#include "node_info.h"
#include "localization_FRORF.h"

#define USE_ALTH_TEST	1

#if USE_ALTH_TEST

uint16_t althTestProcId;

/* TBASIC EST PROCESS ************************************/
YT_PROCESS void alth_test_func(void const * argument);

void config_FRORF();

ytInitProcess(alth_test_proc, alth_test_func, DEFAULT_PROCESS, 256, &althTestProcId, NULL);


YT_PROCESS void alth_test_func(void const * argument){

	config_FRORF();
	int n = 0;
	float Lat=0;
	float Long = 0;
	int error=0;

	while(1){

	/*	pos_OBU_t* pos = get_pos_FRORF();

		if((n<100) &&( pos->Lat != -100) && (pos->Long!=-100)){

			Lat = Lat + pos->Lat;
			Long = Long +pos->Long;
			n++;

		}else if(n>=100){

			ytPrintf("\r\n");
			char* str = ytMalloc(48*sizeof(char));
			sprintf(str, "Lat: %.6f; Long: %.6f ; error:%i ",Lat/n, Long/n, error );
			ytPrintf(str);
			ytFree(str);
			n=0;
			Lat=0;
			Long=0;
			error = 0;
		}else{
			error++;
		}*/

		ytDelay(110);
	}
}


#endif


