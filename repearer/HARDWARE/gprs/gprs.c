 /*******************
*文件名字：gprs.c
*文件描述：GPRS链接服务器并发送数据到服务器
*编辑时间：2018-5-14
*******************/


#include "gprs.h"
#include "stm32f10x.h"
#include "delay.h"
#include "stdio.h"
#include "usart.h"

void GPRS_Init(void)
{
	printf("AT\r\n");//测试
	delay_ms(1000);  //模块响应时间
	
	printf("AT&F\r\n");//恢复出厂设置 -- 波特率9600
	delay_ms(1000);
	
	printf("AT+CGCLASS=\"B\"\r\n");//设置移动台类别
	delay_ms(1000);
	
	//设置移动网络接入点
	printf("AT+CGDCONT=1,\"IP\",\"CMNET\"\r\n");
	delay_ms(1000);
	//选择GPRS作为网络服务
	printf("AT+CGATT=1\r\n");
	delay_ms(1000);
	
	//设置本地的TCP端口号
	printf("AT+CLPORT=\"TCP\",\"2000\"\r\n");
	delay_ms(1000);
}

/*
ipaddr -- ip地址
ipport -- IP的端口号
id     -- 组号
temperature -- 温度值
hudimity -- 湿度值
*/
//GPRS_LinkAndSend("123.207.17.225","5555",25,t,h);
void GPRS_LinkAndSend(u8 *ipaddr,u8 *ipport,u8 id,u8 temperature,u8 humidity)
{
	//建立TCP/IP连接
	printf("AT+CIPSTART=\"TCP\",\"%s\",\"%s\"\r\n",ipaddr,ipport);
	delay_ms(3000);
	
	//发送发送数据指令
	printf("AT+CIPSEND\r\n");
	delay_ms(5000);
	//发送数据：协议格式 # 设备号 温度值 湿度值
	printf("#");
	printf("%c",id);
	printf("%c",temperature);
	printf("%c",humidity);
	printf("%c",0x1a);
	delay_ms(2000);
	//关闭TCP/IP连接
	printf("AT+CIPCLOSE=1\r\n");
	delay_ms(1000);
	//关闭移动场景
	printf("AT+CIPSHUT\r\n");
	delay_ms(2000);
}


//无延时的GPRS连接函数
//本函数执行时不带任何delay函数
//由外部提供时间间隔
//内部只是计数执行不同的GSM命令
//TTL电平：GSM模块的TX接开发板的RX，GSM模块的RX接开发板的TX
void GPRS_Connect (u8 *ipaddr,u8 *ipport,u8 id,u8 temperature,u8 humidity)
{
	static u32 i = 0, State = 0, StateDelay = 2;
	i++;
	
	//每产生5次计数执行一次GSM命令
	if (i == StateDelay)
	{
		switch (State)
		{
			case 0:
				printf("AT\r\n");//测试
				StateDelay ++;
				break;
			case 1:
				printf("AT&F\r\n");//恢复出厂设置 -- 波特率9600
				StateDelay ++;
				break;
			case 2:
				printf("AT+CGCLASS=\"B\"\r\n");//设置移动台类别
				StateDelay ++;
				break;
			case 3:
				printf("AT+CGDCONT=1,\"IP\",\"CMNET\"\r\n");//设置移动网络接入点
				StateDelay ++;
				break;
			case 4:
				printf("AT+CGATT=1\r\n");//选择GPRS作为网络服务
				StateDelay ++;
				break;
			case 5:
				printf("AT+CLPORT=\"TCP\",\"2000\"\r\n");//设置本地的TCP端口号
				StateDelay ++;
				break;
			case 6:
				printf("AT+CIPSTART=\"TCP\",\"%s\",\"%s\"\r\n",ipaddr,ipport);//建立TCP/IP连接
				StateDelay += 3;
				break;
			case 7:
				printf("AT+CIPSEND\r\n");//发送发送数据指令
				StateDelay += 5;
				break;
			case 8:
				//发送数据：协议格式 # 设备号 温度值 湿度值
				printf("#");
				printf("%c",id);
				printf("%c",temperature);
				printf("%c",humidity);
				printf("%c",0x1a);
				StateDelay += 2;
				break;
			case 9:
				printf("AT+CIPCLOSE=1\r\n");//关闭TCP/IP连接
				StateDelay ++;
				break;
			case 10:
				printf("AT+CIPSHUT\r\n");//关闭移动场景
				StateDelay += 2;
				break;
			default:
				break;
		}
		State ++;
		if (State > 10) State = 6;//初始化相关的GSM命令不再重复发送，只在开机发送一次
	}
}

void send_message(int num)
{
	printf("AT+CSCS=\"GSM\"\r\n");
	delay_ms(500);
	printf("AT+CMGF=1\r\n");
	delay_ms(500);	
	printf("AT+CMGS=\"15001923517\"\r\n");
	delay_ms(500);
	if(num==0){printf("Temperature Warning!\x1A\r\n");}
	if(num==1){printf("Invade Warning!\x1A\r\n");}
	if(num==2){printf("Gas Warning!\x1A\r\n");}
	delay_ms(500);
}

void call(void)
{
	//while(1)
	{
	printf("AT\r\n");
	delay_ms(500);
	printf("ATD1xxxxxxxxxx;\r\n");
	delay_ms(500);
	}
}





