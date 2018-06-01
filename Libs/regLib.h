/*
 * rpita_regLib.h
 *
 *  Created on: 15 ene. 2018
 *      Author: rpita
 */

#ifndef APPLICATION_USER_BSP_YETIMOTE_PROCESSES_RPITA_REGLIB_H_
#define APPLICATION_USER_BSP_YETIMOTE_PROCESSES_RPITA_REGLIB_H_

#include "system_api.h"
#include "net_api.h"
#include "time_meas.h"
#include "system_net_api.h"
#include "math.h"
#include "generic_list.h"

typedef struct square {

	gen_list* squareList;

	float32_t pto_y_min;
	float32_t pto_x_min;
	float32_t pto_y_max;
	float32_t pto_x_max;

}square;

gen_list* new_square_area(void);
square* add_squareToArea(gen_list* list,float32_t y_min,float32_t x_min,float32_t y_max,float32_t x_max);
void remove_square(gen_list* list,square* square);
void remove_squareArea(gen_list* list);
square* get_square(gen_list *pos);
void update_item(gen_list* list,square* square,float32_t y_min,float32_t x_min,float32_t y_max,float32_t x_max);

#endif /* APPLICATION_USER_BSP_YETIMOTE_PROCESSES_RPITA_REGLIB_H_ */
