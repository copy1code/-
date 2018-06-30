#ifndef _GPRS_H_
#define _GPRS_H_
#include "stm32f10x.h"

void GPRS_Init(void);
void GPRS_LinkAndSend(u8 *ipaddr,u8 *ipport,u8 id,u8 temperature,u8 humidity);
void GPRS_Connect (u8 *ipaddr,u8 *ipport,u8 id,u8 temperature,u8 humidity);
void send_message(int num);
void call(void);

#endif


