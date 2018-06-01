/*
 * rpita_regLib.c
 *
 *  Created on: 12 ene. 2018
 *      Author: rpita
 */

#include "../althLoc_Libs/regLib.h"

#include "system_api.h"
#include "net_api.h"
#include "time_meas.h"
#include "system_net_api.h"
#include "math.h"
#include "generic_list.h"

gen_list* new_square_area(void){

	return gen_list_init();
}

square* add_squareToArea(gen_list* list,float32_t y_min,float32_t x_min,float32_t y_max,float32_t x_max){

	struct square* square= ytMalloc(sizeof(struct square));

	square->pto_x_max=x_max;
	square->pto_x_min=x_min;
	square->pto_y_max=y_max;
	square->pto_y_min=y_min;
	square->squareList=list;

	gen_list_add(list, (void*) square);

	return square;

}

square* get_square(gen_list *pos){

	return (square*) pos->next->item;


}

void remove_square(gen_list* list,square* square){

	gen_list_remove_and_delete(list, (void*) square);

}

void remove_squareArea(gen_list* list){

	gen_list_remove_all(list);
}

void update_item(gen_list* list,square* square,float32_t y_min,float32_t x_min,float32_t y_max,float32_t x_max){

	square->pto_x_max=x_max;
	square->pto_x_min=x_min;
	square->pto_y_max=y_max;
	square->pto_y_min=y_min;

}




