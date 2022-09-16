
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This software/firmware and related documentation ("AutoChips Software") are
  * protected under relevant copyright laws. The information contained herein is
  * confidential and proprietary to AutoChips Inc. and/or its licensors. Without
  * the prior written permission of AutoChips inc. and/or its licensors, any
  * reproduction, modification, use or disclosure of AutoChips Software, and
  * information contained herein, in whole or in part, shall be strictly
  * prohibited.
  *
  * AutoChips Inc. (C) 2022. All rights reserved.
  *
  * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
  * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AUTOCHIPS SOFTWARE")
  * RECEIVED FROM AUTOCHIPS AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
  * ON AN "AS-IS" BASIS ONLY. AUTOCHIPS EXPRESSLY DISCLAIMS ANY AND ALL
  * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
  * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
  * NONINFRINGEMENT. NEITHER DOES AUTOCHIPS PROVIDE ANY WARRANTY WHATSOEVER WITH
  * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
  * INCORPORATED IN, OR SUPPLIED WITH THE AUTOCHIPS SOFTWARE, AND RECEIVER AGREES
  * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
  * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
  * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN AUTOCHIPS
  * SOFTWARE. AUTOCHIPS SHALL ALSO NOT BE RESPONSIBLE FOR ANY AUTOCHIPS SOFTWARE
  * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
  * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AUTOCHIPS'S
  * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE AUTOCHIPS SOFTWARE
  * RELEASED HEREUNDER WILL BE, AT AUTOCHIPS'S OPTION, TO REVISE OR REPLACE THE
  * AUTOCHIPS SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE
  * CHARGE PAID BY RECEIVER TO AUTOCHIPS FOR SUCH AUTOCHIPS SOFTWARE AT ISSUE.
  *
  ******************************************************************************  
  */

/* --------------------------------- Includes -------------------------------*/
#include "main.h"
#include "ac78xx_irq_cb.h"
#include "can.h"
#include "i2c.h"
#include "timer.h"
#include "uart.h"
#include "gpio.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* --------------------------------- Typedefs -------------------------------*/
/* USER CODE BEGIN Typedefs */

/* USER CODE END Typedefs */

/* --------------------------------- Defines --------------------------------*/
/* USER CODE BEGIN Defines */

/* USER CODE END Defines */

/* --------------------------------- Macros ---------------------------------*/
/* USER CODE BEGIN Macros */

/* USER CODE END Macros */

/* --------------------------------- Variables ------------------------------*/

/* USER CODE BEGIN Variables */
uint32_t sum_1=0;
uint32_t sum_2=0;
uint32_t sum_3=0;
uint8_t I2c_Buf_Write[4]={0};
uint8_t I2c_Buf_Read[4]={0};
uint8_t at24c02_ADD=0x50;
/* USER CODE END Variables */

/* --------------------------------- Function Prototypes --------------------*/
void SystemClock_Config(void);
void MSP_Init(void);

/* USER CODE BEGIN Function_Prototypes */

/* USER CODE END Function_Prototypes */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval int
  */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration------------------------------------------------------*/

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */
		InitDelay();
    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    ATC_GPIO_Init();
    ATC_CAN1_Init();
    ATC_UART3_Init();
    ATC_I2C2_Init();
    ATC_CAN2_Init();
    ATC_UART1_Init();
    ATC_TIMER0_Init();
    ATC_TIMER1_Init();

    /* USER CODE BEGIN 2 */
//		I2C_PageWrite(at24c02_ADD,0,I2c_Buf_Write,4);
//		mdelay(1000);
		I2C_PageRead(at24c02_ADD,0,I2c_Buf_Read,4);
		for( int i =0;i<4;i++) //把读取的数据利用for循环赋值给sum
		{
		sum_1 = (sum_1 << 8) + I2c_Buf_Read[3];
		sum_1 = (sum_1 << 8) + I2c_Buf_Read[2];	
		sum_1 = (sum_1 << 8) + I2c_Buf_Read[1];
		sum_1 = (sum_1 << 8) + I2c_Buf_Read[0];
		}	
    /* USER CODE END 2 */

    /* Infinite loop */
    while(1)
    {

        /* USER CODE BEGIN WHILE */
			GPIO_SetPinValue(JDQ_1_Pin,GPIO_LEVEL_HIGH);
			mdelay (1000);
			GPIO_SetPinValue(JDQ_1_Pin,GPIO_LEVEL_LOW);
			LED_1_TOGGLE;
			mdelay (1000);
//			UART_Command_Judge();
        /* USER CODE END WHILE */

    }

    /* USER CODE BEGIN 3 */

    /* USER CODE END 3 */
}

/**
    * @brief System Clock Configuration
    * @retval None
    */
void SystemClock_Config(void)
{
    SPM_EnableXOSC(1);
    SPM_EnablePLL(1);
    CKGEN_SetPLLReference(PLL_REF_EXTERNAL_OSC);
    CKGEN_SetPllPrevDiv(PLL_PREDIV_1);
    CKGEN_SetPllFeedbackDiv(96);
    CKGEN_SetPllPostDiv(PLL_POSDIV_4);
    CKGEN_SetSysclkDiv(SYSCLK_DIVIDER_1);
    CKGEN_SetSysclkSrc(SYSCLK_SRC_PLL_OUTPUT);
    CKGEN_SetAPBClockDivider(APBCLK_DIVIDER_2);
    CKGEN_SetSFlashClock(SFLASH_CLK_SEL_APB, SFLASH_DIVIDER_2);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void Error_Handler(char *file, int line)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to handle the driver error */
    while(1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

/************************ (C) COPYRIGHT AutoChips *****END OF FILE****/
