#include "dev.h"
#include "stm32f10x_gpio.h"
#include "delay.h"

void dev_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA	, ENABLE );	  //使能ADC1通道时钟
                       
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//模拟输入引脚
	  GPIO_Init(GPIOA, &GPIO_InitStructure);	

    GPIO_SetBits(GPIOA, GPIO_Pin_11|GPIO_Pin_12);

}


void scan_key(char* num)
{
   

			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)==0)
			{
				 delay_ms(20);
			   if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)==0) *(num+0) = 0;  
			}
			
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)==1)
			{
				 delay_ms(20);
			   if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)==1) *(num+0) = 1;  
			}
	 
    

 
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)==1)
			{
				 delay_ms(20);
				 if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)==1) *(num+1) = 1;  
			}
			
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)==0)
			{
				 delay_ms(20);
					if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)==0) *(num+1) = 0;  

			}
	 
    
}

