/*
 * calc_LocatLib.c
 *
 *  Created on: 9 mar. 2018
 *      Author: rpita
 */

#include "calc_LocatLib.h"
#include "localization_FRORF.h"
#include "generic_list.h"
#include "system_api.h"
#include "net_api.h"
#include "time_meas.h"
#include "system_net_api.h"
#include "math.h"
#include "althLoc_comm.h"
#include "areaLib.h"
#include "node_info.h"
#include "regLib.h"


void calc_dist_RSU(gen_list* node_List){

	int i;
	int j;
	int num_nodos=ListLength(node_List);
	node_info* node_p;
	node_info* node_s;

	for(i=0;i<num_nodos;i++){


		node_p=getNodeInfo(node_List,i);
		node_p->distToRsu = ytMalloc(num_nodos*sizeof(float));

		for(j=0;j<num_nodos;j++){

			node_s=getNodeInfo(node_List,j);
			node_p->distToRsu[j]=calc_dist_function(node_p->Lat, node_p->Long,node_s->Lat, node_s->Long);
		}

		Bubble_Sort(node_p->distToRsu,num_nodos);
	}

}
void Bubble_Sort(float* dists, int num_nodos){

	int i;
	int j;

	float temp=0;  //Variable temporal.

	for (i=1;i<num_nodos;i++){
		for (j=0; j < num_nodos-i ;j++){

			if (dists[j] > dists[j+1]){ //Condicion mayor-menor

				temp=dists[j];
				dists[j]=dists[j+1];
				dists[j+1]=temp;
			}
		}
	}
}

void calc_dist_OBU(gen_list* node_List){

	int j;
	int num_nodos=ListLength(node_List);
	node_info* node;

	for(j=0;j<num_nodos;j++){// darle una vuelta

		node=getNodeInfo(node_List,j);
		node->dist_OBU=(float)((((V_LUZ *pow(10,((POT_433_dbm - (node->rssi))/(10*LOSS_EXP))))/(4*M_PI*FREC_433)))-B)/A ; //AJUSTADA
	}

}

void calc_region_OBU(gen_list* node_List){

	int i,j,temp;
	int num_nodos=ListLength(node_List);
	node_info* node;

	for(i=0;i<num_nodos;i++){

		temp=0;
		node=getNodeInfo(node_List,i);

		for(j=0;j<num_nodos;j++){

			if((node->dist_OBU <= node->distToRsu[j]) && temp==0){

				node->reg=j;
				temp=1;
			}
		}

		if(temp==0){node->reg=j;}
	}

}

void calc_COG(gen_list* node_List,pos_OBU_t* pos_OBU){

	int j=0;
	int pos1=0;
	int pos2=0;
	float acc_x=0;
	float acc_y=0;
	int n=0;
	int out_pos=0;

	float32_t x_pos,x_neg,x_pos2,x_neg2,x_max,x_min;
	float32_t y_pos,y_neg,y_pos2,y_neg2,y_max,y_min;

	gen_list* square_area= new_square_area();

	int num_nodos=ListLength(node_List);

	node_info* node;

	//Cálculo de la región con los límites exteriores

	for(j=0;j<num_nodos;j++){

		node=getNodeInfo(node_List,j);

		if(node->reg!=num_nodos){

			x_pos=node->Long+transf_dist_grados(node->distToRsu[node->reg]);
			x_neg=node->Long-transf_dist_grados(node->distToRsu[node->reg]);

			if(pos1==0){
				x_max=x_pos;
				x_min=x_neg;
				pos1=1;
			}

			if(x_max>x_pos){x_max=x_pos;}
			if(x_min<x_neg){x_min=x_neg;}

			y_pos=node->Lat+transf_dist_grados(node->distToRsu[node->reg]);
			y_neg=node->Lat-transf_dist_grados(node->distToRsu[node->reg]);

			if(pos2==0){
				y_max=y_pos;
				y_min=y_neg;
				pos2=1;
			}

			if(y_max>y_pos){y_max=y_pos;}
			if(y_min<y_neg){y_min=y_neg;}

		}else{

			out_pos++;

		}
	}


	add_squareToArea(square_area,y_min,x_min,y_max,x_max);

	//Cálculo de las intersecciones entre el area exterior y las interiores

	for(j=0;j<num_nodos;j++){

		node=getNodeInfo(node_List,j);

		if(node->reg!=1 && node->reg!=0){

			//CÁLCULO DE LOS LÍMITES INTERIORES DE LA LONGITUD

			x_pos2=node->Long+transf_dist_grados(node->distToRsu[(node->reg)-1]);
			x_neg2=node->Long-transf_dist_grados(node->distToRsu[(node->reg)-1]);

			//CÁLCULO DE LOS LÍMITES INTERIORES DE LA LATITUD

			y_pos2=node->Lat+transf_dist_grados(node->distToRsu[(node->reg)-1]);
			y_neg2=node->Lat-transf_dist_grados(node->distToRsu[(node->reg)-1]);

			//Cálculo del número de posiciones de la lista

			gen_list* current = square_area;
			int count=0;

			while(current->next!= NULL){
				current = current->next;
				count++;
			}

			//Cálculo de las distintas areas que forman la region
			current = square_area;
			int i=0;

			for(i=0;i<count;i++){

				int pos =get_area_function(square_area,get_square(current),y_neg2,x_neg2,y_pos2,x_pos2);
				current = current->next;

				if(pos==15){//hay que volver a recorrer la lista al borrar porque se pierde la referencia
					i=0;
					count--;
					current = square_area;
				}
			}
		}
	}

	//Cálculo del centro de gravedad

	square* square;
	gen_list* current1 = square_area;

	while(current1->next != NULL){

		square=get_square(current1);
		current1 = current1->next;
		acc_x= acc_x+((square->pto_x_min)+(((square->pto_x_max)-(square->pto_x_min))/2));
		acc_y= acc_y+((square->pto_y_min)+(((square->pto_y_max)-(square->pto_y_min))/2));
		n++;
	}

	remove_squareArea(square_area);

	if(out_pos==num_nodos || n==0){

		pos_OBU->Long=-100;
		pos_OBU->Lat=-100;

	}else{

		pos_OBU->Long=acc_x/n;
		pos_OBU->Lat=acc_y/n;
	}

	out_pos=0;

}

void get_PosOBU(gen_list* node_List,pos_OBU_t* pos_OBU){

	if(ListLength(node_List)>1){

		calc_dist_RSU(node_List);
		calc_dist_OBU(node_List);
		calc_region_OBU(node_List);
		calc_COG(node_List,pos_OBU);

	}else{

		pos_OBU->Lat = -100;
		pos_OBU->Long = -100;
	}

	set_pos_FRORF(pos_OBU);

}

float transf_dist_grados(float dist){

	return (float)(dist*360)/(2*PI*6371000);
}

float dist_square_int_grados(float dist){

	return (float)(sqrt(2)/2)*(dist*360)/(2*PI*6371000);
}

float calc_dist_function(float lat1, float long1,float lat2, float long2){//devuelve la distancia entre los dos puntos geográficos

	return (float) (PI*6371000/90)*asin( sqrt ( sin((lat1-lat2)/2)*sin((lat1-lat2)/2)+ cos(lat1)*cos(lat2)*sin((long1-long2)/2)*sin((long1-long2)/2)));
}
