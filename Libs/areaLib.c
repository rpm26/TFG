/*
 * rpita_areaLib.c
 *
 *  Created on: 23 ene. 2018
 *      Author: rpita
 */

#include "system_api.h"
#include "net_api.h"
#include "time_meas.h"
#include "system_net_api.h"
#include "math.h"
#include "../althLoc_Libs/regLib.h"



uint8_t areas_intersection_function(float32_t y_min,float32_t x_min,float32_t y_max,float32_t x_max,float32_t y_min2,float32_t x_min2,float32_t y_max2,float32_t x_max2){

	if(((y_min< y_min2) && (y_min2 <y_max)) || ((y_min< y_max2) && (y_max2 <y_max)) || ((y_max< y_max2) && (y_min2 <y_min))){

		if(((x_min< x_min2) && (x_min2 <x_max)) || ((x_min< x_max2) && (x_max2 <x_max)) || ((x_max< x_max2) && (x_min2 <x_min))){

			return 1;
		}

	}else if(((y_min< y_min2) && (y_min2 <y_max)) || ((y_min< y_max2) && (y_max2 <y_max)) ||((y_max>y_max2) && (y_min<y_min2)) ){

		if(((x_min< x_min2) && (x_min2 <x_max)) || ((x_min< x_max2) && (x_max2 <x_max)) || ((x_max>x_max2) && (x_min<x_min2))){

			return 1;
		}
	}

	return 0;

}

uint8_t comp_ptos_function(float32_t pto1,float32_t pto2){

	if(pto1>pto2){return 1;}

	return 0;
}


uint8_t areas_pos_fuction(float32_t y_min,float32_t x_min,float32_t y_max,float32_t x_max,float32_t y_min2,float32_t x_min2,float32_t y_max2,float32_t x_max2){

	uint8_t array[]= {0,0,0,0};

	//Intersección ambos lados

	if((((y_min< y_min2) && (y_min2 <y_max)) || ((y_min< y_max2) && (y_max2 <y_max))) && (((x_min< x_min2) && (x_min2 <x_max)) || ((x_min< x_max2) && (x_max2 <x_max)))){

		array[3]=0;
		array[2]=0;
		array[1]= comp_ptos_function(y_max,y_max2);
		array[0]= comp_ptos_function(x_max,x_max2);
	}

	//Intersección de un lado (area1 en el interior)

	if((((y_min< y_min2) && (y_min2 <y_max)) || ((y_min< y_max2) && (y_max2 <y_max))) && ((x_max< x_max2) && (x_min2 <x_min)) ){

		array[3]=0;
		array[2]=1;
		array[1]=1;//h
		array[0]= comp_ptos_function(y_max,y_max2);
	}

	if((((x_min< x_min2) && (x_min2 <x_max)) || ((x_min< x_max2) && (x_max2 <x_max))) && ((y_max< y_max2) && (y_min2 <y_min))){

		array[3]=0;
		array[2]=1;
		array[1]=0;//v
		array[0]= comp_ptos_function(x_max,x_max2);
	}

	//Intersección de un lado (area2 en el interior)

	if((((y_min< y_min2) && (y_min2 <y_max)) || ((y_min< y_max2) && (y_max2 <y_max))) && ((x_max> x_max2) && (x_min2 >x_min)) ){

		array[3]=1;
		array[2]=0;
		array[1]=1;//h
		array[0]= comp_ptos_function(y_max,y_max2);
	}

	if((((x_min< x_min2) && (x_min2 <x_max)) || ((x_min< x_max2) && (x_max2 <x_max))) && ((y_max> y_max2) && (y_min2 >y_min)) ){

		array[3]=1;
		array[2]=0;
		array[1]=0;//v
		array[0]= comp_ptos_function(x_max,x_max2);
	}

	// Area1 dentro de Area2
	if( ((y_max> y_max2) && (y_min2 >y_min)) && ((x_max> x_max2) && (x_min2 >x_min)) ){

		array[3]=1;
		array[2]=1;
		array[1]=0;
		array[0]=0;
	}

	// Area1 cubierta por Area2
	if(((y_max< y_max2) && (y_min2 <y_min)) && ((x_max< x_max2) && (x_min2 <x_min))){

		array[3]=1;
		array[2]=1;
		array[1]=1;
		array[0]=1;
	}

	return ((array[0])+(2*array[1])+(4*array[2])+(8*array[3]));
}

void square_div_function(gen_list* list,int pos,square* square,float32_t y_min2,float32_t x_min2,float32_t y_max2,float32_t x_max2){

	float x_min = square->pto_x_min;
	float y_min = square->pto_y_min;
	float x_max = square->pto_x_max;
	float y_max = square->pto_y_max;

	switch( pos ){

	case 0:

		update_item(list,square,y_min,x_min, y_min2,x_max);
		add_squareToArea(list,y_min2,x_min, y_max,x_min2);

		break;

	case 1:

		update_item(list,square,y_min,x_min, y_min2,x_max);
		add_squareToArea(list,y_min2,x_max2, y_max,x_max);

		break;

	case 2:

		update_item(list,square,y_max2,x_min, y_max,x_max);
		add_squareToArea(list,y_min,x_min, y_max2,x_min2);

		break;

	case 3:

		update_item(list,square,y_max2,x_min, y_max,x_max);
		add_squareToArea(list,y_min,x_max2, y_max2,x_max);

		break;

	case 4:

		update_item(list,square,y_min,x_min, y_max,x_min2);

		break;

	case 5:

		update_item(list,square,y_min,x_max2, y_max,x_max);

		break;

	case 6:

		update_item(list,square,y_min,x_min, y_min2,x_max);

		break;

	case 7:

		update_item(list,square,y_max2,x_min, y_max,x_max);

		break;

	case 8:

		update_item(list,square,y_min,x_min, y_max,x_min2);
		add_squareToArea(list,y_max2,x_min2, y_max,x_max);
		add_squareToArea(list,y_min,x_min2, y_min2,x_max);

		break;

	case 9:

		update_item(list,square,y_min,x_max2, y_max,x_max);
		add_squareToArea(list,y_max2,x_min, y_max,x_max2);
		add_squareToArea(list,y_min,x_min, y_min2,x_max2);

		break;

	case 10:

		update_item(list,square,y_min,x_min, y_min2,x_max);
		add_squareToArea(list,y_min2,x_min, y_max,x_min2);
		add_squareToArea(list,y_min2,x_max2, y_max,x_max);

		break;

	case 11:

		update_item(list,square,y_max2,x_min,y_max,x_max);
		add_squareToArea(list,y_min,x_min, y_max2,x_min2);
		add_squareToArea(list,y_min,x_max2, y_max2,x_max);

		break;

	case 12:

		update_item(list,square,y_min,x_max2, y_max,x_max);
		add_squareToArea(list,y_min,x_min, y_max,x_min2);
		add_squareToArea(list,y_max2,x_min2, y_max,x_max2);
		add_squareToArea(list,y_min,x_min2, y_min2,x_max2);

		break;

	case 15:

		remove_square(list,square);

		break;

	default: ;

	}
}


int get_area_function(gen_list* list,square* square,float32_t y_min2,float32_t x_min2,float32_t y_max2,float32_t x_max2){

	float x_min = square->pto_x_min;
	float y_min = square->pto_y_min;
	float x_max = square->pto_x_max;
	float y_max = square->pto_y_max;

	if(areas_intersection_function(y_min,x_min,y_max,x_max,y_min2,x_min2,y_max2,x_max2)){

		int pos = areas_pos_fuction(y_min,x_min,y_max,x_max,y_min2,x_min2,y_max2,x_max2);

		square_div_function(list,pos,square,y_min2,x_min2,y_max2,x_max2);

		return pos;
	}

	return 16;

}
