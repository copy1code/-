/***************
*�ļ�����main.c
*�༭�ߣ���־��
*ʱ�䣺2018-5-14
***************/


#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "gprs.h"
#include "usart2.h"
#include  "oled.h"
#include  "dev.h"
#include  "dtp.h"
#include  "ds18b20.h"
#include  "mpu6050.h"
#include  "bsp_i2c.h"
#include  "ano_dt.h"
#include "data_handle.h"
#include "bsp_GeneralTIM.h" 




/****�����豸ID****/
const char ID1 = 100;
const char ID2 = 100;





/****����60s��������****/
uint16_t timer_count=0;

/****�������ݰ�****/
char pack[255];

int main(void)
{
    short Accel[3];
    short accel[1];
	  short temp[1];
	  short fre[1]; 

    delay_init();
    uart_init(9600);
	  
	  /****����1ms�����ж�****/
	  GENERAL_TIMx_Configuration();
	  /****��ʼ��mpu6050****/
	  i2c_CfgGpio(); 
		MPU6050_Init();
		/****MPU6050�Լ�****/
		if(MPU6050ReadID() == 0)
		{	
		  	while(1);
		}
		
		/****��ʼ�����Լ��¶ȴ�����****/
		if(DS18B20_Init() == 1)
		{
        while(1);  
		}
		
		/****��ʼ�����Լ�����������****/	

	  while(1)
    {
			
        //ANO_send_data(Accel[0]*196/32767,Accel[1]*196/32767,Accel[2]*196/32767,Gyro[0],Gyro[1],Gyro[2],0,0,0);
        if(timer_count == 1000)
        {
            timer_count = 0;
					  MPU6050ReadAcc(Accel);
					  temp[0]= DS18B20_Get_Temp();
					
					
					  //�ɼ�������Ϣ 
					  //�����ݴ������������յ�����ָ������ݷ�����������
					  data_pack(temp,accel,fre,pack);
        }

	  }

} 
 



