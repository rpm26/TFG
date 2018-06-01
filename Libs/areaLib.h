/*
 * rpita_areaLib.h
 *
 *  Created on: 23 ene. 2018
 *      Author: rpita
 */

#ifndef APPLICATION_USER_BSP_YETIMOTE_PROCESSES_RPITA_AREALIB_H_
#define APPLICATION_USER_BSP_YETIMOTE_PROCESSES_RPITA_AREALIB_H_


#include "system_api.h"
#include "net_api.h"
#include "time_meas.h"
#include "system_net_api.h"
#include "math.h"
#include "../althLoc_Libs/regLib.h"


//Devuelve 1 si el area 2 intersecta con el area 1 sino devuelve 0
uint8_t areas_intersection_function(float32_t y_min,float32_t x_min,float32_t y_max,float32_t x_max,float32_t y_min2,float32_t x_min2,float32_t y_max2,float32_t x_max2);

/*Devuelve el "codigo" correspondiente a la posición del area2 con respecto al area1
 *
 * Códigos de posiciones:
 *
 * (0,0,0,0) -> 0 (arriba a la derecha)
 * (0,0,0,1) -> 1 (arriba a la izquierda)
 * (0,0,1,0) -> 2 (abajo a la derecha)
 * (0,0,1,1) -> 3 (abajo a la izquierda)
 * (0,1,0,0) -> 4 (vertical fuera a la derecha)
 * (0,1,0,1) -> 5 (vertical fuera a la izquierda)
 * (0,1,1,0) -> 6 (horizontal fuera arriba)
 * (0,1,1,1) -> 7 (horizontal fuera abajo)
 * (1,0,0,0) -> 8 (vertical dentro a la derecha)
 * (1,0,0,1) -> 9 (vertical dentro a la izquierda)
 * (1,0,1,0) -> 10 (horizontal dentro arriba)
 * (1,0,1,1) -> 11 (horizontal dentro abajo)
 * (1,1,0,0) -> 12 (area2 en el interior)
 * (1,1,1,1) -> 15 (completamente cubierto)
 *
 *  */
uint8_t areas_pos_fuction(float32_t y_min,float32_t x_min,float32_t y_max,float32_t x_max,float32_t y_min2,float32_t x_min2,float32_t y_max2,float32_t x_max2);
uint8_t comp_ptos_function(float32_t pto_max1,float32_t pto_max2);
void square_div_function(gen_list* list,int pos,square* square,float32_t y_min2,float32_t x_min2,float32_t y_max2,float32_t x_max2);
uint8_t get_area_function(gen_list* list,square* square,float32_t y_min2,float32_t x_min2,float32_t y_max2,float32_t x_max2);
#endif /* APPLICATION_USER_BSP_YETIMOTE_PROCESSES_RPITA_AREALIB_H_ */
