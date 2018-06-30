/***************************************
             数据处理程序
****************************************/



#include "data_handle.h"
#include "usart.h"	
#include "string.h"
#include <string.h>


extern char ID1;
extern char ID2 ;

/*************************
函数名：int2str
函数功能：将整数转化为字符串
函数参数：n整数，字符串指针
函数返回值：无

考虑使用sprintf函数，或者itoa函数
**************************/

void int2str(int n, char *str)
{
    char buf[10] = "";
    int i = 0;
    int len = 0;
    int temp = n < 0 ? -n: n;  // temp为n的绝对值
  
    if (str == NULL)
   {
       return;
   }
   while(temp)
   {
       buf[i++] = (temp % 10) + '0';  //把temp的每一位上的数存入buf
       temp = temp / 10;
   }
 
   len = n < 0 ? ++i: i;  //如果n是负数，则多需要一位来存储负号
   str[i] = 0;            //末尾是结束符0
   while(1)
   {
       i--;
       if (buf[len-i-1] ==0)
       {
           break;
       }
       str[i] = buf[len-i-1];  //把buf数组里的字符拷到字符串
   }
   if (i == 0 )
   {
        str[i] = '-';          //如果是负数，添加一个负号
   }
 }

 
 /*************************
函数名：data_pack
函数功能：将搜集到的数据打包
函数参数：整数指针以此为：温度，加速度，频率，打包好的字符串指针
函数返回值：无

考虑使用strcat函数，字符串拼接函数
 
itoa函数不是标准库的函数
 **************************/
 
 void data_pack(short *temp,short *acc,short *fre,char *pack)
 { 
    char s_temp[10]={0};
    char s_acc[10]={0};
    char s_fre[10]={0};
    char s_id1[10]={0};
    char s_id2[10]={0};
		
	  int2str(ID1, s_id1);
		int2str(ID2, s_id2);
	 	int2str(*(temp+0), s_temp);
		int2str(*(acc+0), s_acc);
		int2str(*(fre+0), s_fre);
		

		strcat (pack,"$>");
		strcat (pack,"I1");
	  strcat (pack,s_id2);
		strcat (pack,"I2");
	  strcat (pack,s_id2);
		strcat (pack,"t");
		strcat (pack,s_temp);
		strcat (pack,"g");
		strcat (pack,s_acc);
	  strcat (pack,"f");
		strcat (pack,s_fre);
    strcat (pack,"<$");
 
 }
 

