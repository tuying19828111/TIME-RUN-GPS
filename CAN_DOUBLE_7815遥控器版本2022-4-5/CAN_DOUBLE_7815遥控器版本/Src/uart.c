/**
  ******************************************************************************
  * File Name          : UART.c
  * Description        : This file provides code for the configuration
  *                      of the UART instances.
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

/* --------------------------------- Includes ---------------------------------*/
#include "ac78xx.h"
#include "ac78xx_irq_cb.h"
#include "ac78xx_uart.h"
#include "uart.h"

extern void Error_Handler(char *, int);

void MSP_UART_Init(UART_Type* UARTx);

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* UART1 init function */
void ATC_UART1_Init(void)
{
    UART_SettingType uartConfig;
    memset(&uartConfig, 0, sizeof(uartConfig));

    UART_SetEventCallback(UART1, UART1_IRQHandler_Callback);
    MSP_UART_Init(UART1);
    uartConfig.baudrate = 9600;
    uartConfig.dataBits = BIT8;
    uartConfig.stopBits = STOP_1BIT;
    uartConfig.parity = NOPARITY;
    uartConfig.fifoByte = ENABLE;
    uartConfig.dmaEn = UART_DMA_TXRX_NONE;
    uartConfig.rateStep = UART_SMP_CNT0;
    UART_Init(UART1, &uartConfig);
    UART_SetRxIntEn(UART1, ENABLE);

}
/* UART3 init function */
void ATC_UART3_Init(void)
{
    UART_SettingType uartConfig;
    memset(&uartConfig, 0, sizeof(uartConfig));

    UART_SetEventCallback(UART3, UART3_IRQHandler_Callback);
    MSP_UART_Init(UART3);
    uartConfig.baudrate = 115200;
    uartConfig.dataBits = BIT8;
    uartConfig.stopBits = STOP_1BIT;
    uartConfig.parity = NOPARITY;
    uartConfig.fifoByte = ENABLE;
    uartConfig.dmaEn = UART_DMA_TXRX_NONE;
    uartConfig.rateStep = UART_SMP_CNT0;
    UART_Init(UART3, &uartConfig);
    UART_SetRxIntEn(UART3, ENABLE);

}

void MSP_UART_Init(UART_Type* UARTx)
{

    if (UARTx == UART1)
    {
        /* USER CODE BEGIN MSP_UART1_Init 0 */

        /* USER CODE END MSP_UART1_Init 0 */
    
        /**
        GPIO Configuration for UART1        
        PB5         --> UART1_TX
        PB6         --> UART1_RX 
        */
        GPIO_SetFunc(GPIO_PB5, GPIO_FUN1);

        GPIO_SetFunc(GPIO_PB6, GPIO_FUN1);

        /* UART1 interrupt Init */
        NVIC_SetPriority(UART1_IRQn, 2);
        NVIC_EnableIRQ(UART1_IRQn);

        /* USER CODE BEGIN MSP_UART1_Init 1 */

        /* USER CODE END MSP_UART1_Init 1 */
    }
    else if (UARTx == UART3)
    {
        /* USER CODE BEGIN MSP_UART3_Init 0 */

        /* USER CODE END MSP_UART3_Init 0 */
    
        /**
        GPIO Configuration for UART3        
        PA11         --> UART3_RX
        PA12         --> UART3_TX 
        */
        GPIO_SetFunc(GPIO_PA11, GPIO_FUN3);

        GPIO_SetFunc(GPIO_PA12, GPIO_FUN3);

        /* UART3 interrupt Init */
        NVIC_SetPriority(UART3_IRQn, 2);
        NVIC_EnableIRQ(UART3_IRQn);

        /* USER CODE BEGIN MSP_UART3_Init 1 */

        /* USER CODE END MSP_UART3_Init 1 */
    }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT AutoChips *****END OF FILE****/
