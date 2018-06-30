#ifndef __ANO_DT_H
#define __ANO_DT_H 			   
#include "sys.h"  


void nrf_send_ANO(u8 fun,u8*data,u8 len);
void usart_send_ANO(u8 fun,u8*data,u8 len);

void ANO_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw);
void ano_dt(short roll,short pitch,short yaw,int high);

#endif



