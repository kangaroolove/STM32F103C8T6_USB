/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include "usb_lib.h"
#include "usb_pwr.h"
#include "hw_config.h"

void testGPIO(void);
void initWWDG(void);

int main()
{
	Set_System();
	USB_Interrupts_Config();
	Set_USBClock();
	USB_Init();
	
	//initWWDG();
	
	
	while (1);
		
		/* Update WWDG counter */
	    //WWDG_SetCounter(127);
}

void initWWDG()
{
  /* WWDG configuration */
  /* Enable WWDG clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

/* On Value line devices, WWDG clock counter = (PCLK1 (24MHz)/4096)/8 = 732 Hz (~1366 us)  */
/* On other devices, WWDG clock counter = (PCLK1(36MHz)/4096)/8 = 1099 Hz (~910 us)  */
  WWDG_SetPrescaler(WWDG_Prescaler_8);

  /* Set Window value to 80; WWDG counter should be refreshed only when the counter
    is below 80 (and greater than 64) otherwise a reset will be generated */
  WWDG_SetWindowValue(80);

  /* - On Value line devices,
    Enable WWDG and set counter value to 127, WWDG timeout = ~1366 us * 64 = 87.42 ms 
    In this case the refresh window is: ~1366us * (127-80) = 64.20 ms < refresh window < ~1366us * 64 = 87.42ms
     - On other devices
    Enable WWDG and set counter value to 127, WWDG timeout = ~910 us * 64 = 58.25 ms 
    In this case the refresh window is: ~910 us * (127-80) = 42.77 ms < refresh window < ~910 us * 64 = 58.25ms     
  */
  WWDG_Enable(127);
}

void testGPIO(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef initStructure;
	initStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	initStructure.GPIO_Speed = GPIO_Speed_50MHz;
	initStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &initStructure);

	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
