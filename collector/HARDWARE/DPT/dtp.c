/***************************************
          数字电位器驱动程序
****************************************/


#include "dtp.h"
#include "delay.h"



static u8 add=0;
/*************************
函数名：blank
函数功能：空白函数，延时作用
函数参数：无
函数返回值：无
**************************/
void blank(void)
{
}


/*************************
函数名：read_init
函数功能：初始化读取鉴频器输出引脚
函数参数：无
函数返回值：无
**************************/

void read_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

	  RCC_APB2PeriphClockCmd(DEV_CLK	, ENABLE );	  //使能ADC1通道时钟
                       
	  GPIO_InitStructure.GPIO_Pin = read_pin;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//模拟输入引脚
	  GPIO_Init(DEV_GPIO, &GPIO_InitStructure);	

    //GPIO_SetBits(DEV_GPIO, read_pin);

}



/*************************
函数名：dtp_init
函数功能：初始化控制引脚，并强制将电位器置零
函数参数：无
函数返回值：无
**************************/
void dtp_init(void)
{   
	  u8 i=0;
	  GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(DEV_CLK	, ENABLE );	  //使能ADC1通道时钟、
	
	  
                       
	  GPIO_InitStructure.GPIO_Pin = INC_Pin|UD_Pin|CS_Pin;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//模拟输入引脚
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
	  GPIO_Init(DEV_GPIO, &GPIO_InitStructure);	
	  INC_1;
	  CS_0;
	  UD_0;
	  
    blank();
	
		for(i=100;i>0;i--)
		{
			 INC_0;
       delay_ms(1);
			 INC_1;		
		}
		//INC(0);
		CS_1;
		
		read_init();
}





/*************************
函数名：dtp_plus
函数功能：增加指定电阻，增大电位器阻值量=num*1010R
函数参数：num
函数返回值：无
**************************/
void dtp_plus(u8 num)
{  
   int i;
	 CS_0;
	 UD_1;	
	 blank();
	 for(i=num;i>0;i--)
   {
			INC_0;
      delay_ms(1);
			INC_1;
		}
	// INC(0);
	 CS_1;
			
	 add = add + num; 
	
}





/*************************
函数名：dtp_minus
函数功能：减小指定电阻，减小电位器阻值量=num*1010R
函数参数：num
函数返回值：无
**************************/
void dtp_minus(u8 num)
{
	 int i;
	 CS_0;
	 UD_0;	
	 blank();
	 for(i=num;i>0;i--)
	 {
			INC_0;
      delay_ms(1);
			INC_1;
		}
	 // INC(0);
		CS_1;
		add = add - num; 
  
}



/*************************
函数名：frequency
函数功能：减小指定电阻，减小电位器阻值量=num*1010R
函数参数：num
函数返回值：1或0 1表示在这个频率 0表示不在这个频率
**************************/
int frequency(u32* f)
{  
	 *(f+0) = (int)11000000/(add*1010);
	 if(GPIO_ReadInputDataBit(DEV_GPIO, read_pin)==0) return 1;
   else return 0;
}


