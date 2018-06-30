#include "usart2.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "string.h"


/****定义接收数据flag****/
uint8_t Rx_data_flag=0;
uint8_t Rx_control_flag=0;
uint8_t ucTemp;
uint16_t usRxCount=0;
uint8_t ucaRxBuf[256];
char compare[4]={'$','1','0','0'};
/********************************************************************************************
串口2发送函数
********************************************************************************************/
void Usart2_Send(unsigned char *str)
 {	
	 	
	while(*str != '\0')
	{		
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET);//判断是否发送完成
		USART_SendData(USART2 , *str);
		str++;
	}
}


/********************************************************************************************
端口初始化函数
********************************************************************************************/
void usart2_init(u32 bound)
{		
	GPIO_InitTypeDef GPIO_Usart2;																//定义端口变量
	USART_InitTypeDef USART_Usart2;
	
	NVIC_InitTypeDef NVIC_Usart2;																//设置中断控制器变量 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);							//设置中断优先级
	
	NVIC_Usart2.NVIC_IRQChannel = USART2_IRQn;	 								//设置为串口1全局中断
	NVIC_Usart2.NVIC_IRQChannelPreemptionPriority = 1;					//设置抢占优先级
	NVIC_Usart2.NVIC_IRQChannelSubPriority = 0;									//设置从优先级
	NVIC_Usart2.NVIC_IRQChannelCmd = ENABLE;										//IRQ通道使能
	NVIC_Init(&NVIC_Usart2);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);			//使端口GPIOA时钟生效，使用外设时钟2
		
	//TX   PA2
 	GPIO_Usart2.GPIO_Pin = GPIO_Pin_2 ;													//设置GPIO子端口号	
  GPIO_Usart2.GPIO_Mode = GPIO_Mode_AF_PP;   								  //设置为复用推挽输出
  GPIO_Usart2.GPIO_Speed = GPIO_Speed_50MHz; 									//设置端口输出频率为50MHz
  GPIO_Init(GPIOA, &GPIO_Usart2);		  												//初始化端口
	
	//RX   PA3
	GPIO_Usart2.GPIO_Pin = GPIO_Pin_3;													//设置GPIO子端口号
	GPIO_Usart2.GPIO_Mode = GPIO_Mode_IN_FLOATING;							//浮空输入
	GPIO_Init(GPIOA, &GPIO_Usart2);															//初始化端口
	
	USART_Usart2.USART_BaudRate = bound;													//设置波特率
	USART_Usart2.USART_WordLength = USART_WordLength_8b;				//设置数据位
	USART_Usart2.USART_StopBits = USART_StopBits_1;							//设置停止位
	USART_Usart2.USART_Parity = USART_Parity_No ;								//设置校检位
	USART_Usart2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;			//关闭硬件控制模式
	USART_Usart2.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		//使能
	USART_Init(USART2,&USART_Usart2); 													//初始化串口
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);							//配置接收数据中断
	USART_Cmd(USART2, ENABLE);																	//开启串口一
}


/***********************************
函数功能：串口2 中断服务函数读取发送的指令
发送格式：以$开始以回车结束
***********************************/
void USART2_IRQHandler(void)
{
		if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//进入 接收中断
	  {
		    ucTemp=USART2->DR;//读取接收到的数据
        if(ucTemp=='$')    //接收到开始字符
				{
					 Rx_data_flag=1;
				}
				if(ucTemp=='@')    //接收到开始字符
				{
					 Rx_control_flag=1;
				}
				
		}
		
		if(Rx_data_flag)
		{
			if (usRxCount < sizeof(ucaRxBuf))
			{
				ucaRxBuf[usRxCount++] = ucTemp;
				if(usRxCount==4)
				{
				  if((compare[0]==ucaRxBuf[0])&&(compare[1]==ucaRxBuf[1])&&(compare[2]==ucaRxBuf[2])&&(compare[3]==ucaRxBuf[3]))
						Rx_data_flag=1;
					else 
         {
				    Rx_data_flag=0;  
				    memset( ucaRxBuf, 0, sizeof(ucaRxBuf));}
				 }
			}
			else
			{
				usRxCount = 0;
			}
			
			/* 遇到换行字符，认为接收到一个命令 */
			if (ucTemp == 0x0A && Rx_data_flag)	/* 换行字符 */
			{		
				 Usart2_Send(ucaRxBuf);
         Rx_data_flag=0;
			   usRxCount = 0;
			   memset( ucaRxBuf, 0, sizeof(ucaRxBuf));
			}
		}		

	
	
}



