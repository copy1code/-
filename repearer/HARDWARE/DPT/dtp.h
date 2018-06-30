#ifndef  __DTP_H_
#define  __DTP_H_
#include "stm32f10x.h"
#include "sys.h"

#define DEV_GPIO    GPIOB
#define DEV_CLK     RCC_APB2Periph_GPIOB
#define INC_Pin     GPIO_Pin_13
#define UD_Pin      GPIO_Pin_14
#define CS_Pin      GPIO_Pin_15
#define read_pin    GPIO_Pin_12
#define INC_1       GPIO_SetBits(DEV_GPIO,INC_Pin)
#define INC_0       GPIO_ResetBits(DEV_GPIO,INC_Pin)
#define UD_1        GPIO_SetBits(DEV_GPIO,UD_Pin)
#define UD_0        GPIO_ResetBits(DEV_GPIO,UD_Pin)
#define CS_1        GPIO_SetBits(DEV_GPIO,CS_Pin)
#define CS_0        GPIO_ResetBits(DEV_GPIO,CS_Pin)

void dtp_init(void);
void dtp_plus(u8 num);
void dtp_minus(u8 num);
int frequency(u32* f);

#endif


