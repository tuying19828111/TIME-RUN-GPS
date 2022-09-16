/**
  ******************************************************************************
  * File Name          : CAN.c
  * Description        : This file provides code for the configuration
  *                      of the CAN instances.
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
#include "ac78xx_can.h"
#include "can.h"

extern void Error_Handler(char *, int);

void MSP_CAN_Init(CAN_Type* CANx);

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* CAN1 init function */
void ATC_CAN1_Init(void)
{
    CAN_Config canConfig;
    memset(&canConfig, 0, sizeof(canConfig));
    CAN_BaudrateConfig baudrate;
    memset(&baudrate, 0, sizeof(baudrate));

    CAN_SetEventCallBack(CAN1, CAN1_IRQHandler_Callback);
    MSP_CAN_Init(CAN1);
    canConfig.canMode = CAN_MODE_NORMAL;
    canConfig.clockSrc = CAN_CLKSRC_AHB;
    canConfig.interruptEnable = ENABLE;
    canConfig.autoReset = ENABLE;
    canConfig.TPSS = DISABLE;
    canConfig.TSSS = DISABLE;
    canConfig.TSMODE = 0;
    canConfig.ROM = 0;
    baudrate.S_PRESC = 7;
    baudrate.S_SEG_1 = 16;
    baudrate.S_SEG_2 = 5;
    baudrate.S_SJW = 3;

    CAN_Initialize(CAN1, &canConfig, &baudrate);
    CAN_Standby(CAN1, DISABLE);

}
/* CAN2 init function */
void ATC_CAN2_Init(void)
{
    CAN_Config canConfig;
    memset(&canConfig, 0, sizeof(canConfig));
    CAN_BaudrateConfig baudrate;
    memset(&baudrate, 0, sizeof(baudrate));

    CAN_SetEventCallBack(CAN2, CAN2_IRQHandler_Callback);
    MSP_CAN_Init(CAN2);
    canConfig.canMode = CAN_MODE_NORMAL;
    canConfig.clockSrc = CAN_CLKSRC_AHB;
    canConfig.interruptEnable = ENABLE;
    canConfig.autoReset = ENABLE;
    canConfig.TPSS = DISABLE;
    canConfig.TSSS = DISABLE;
    canConfig.TSMODE = 0;
    canConfig.ROM = 0;
    baudrate.S_PRESC = 7;
    baudrate.S_SEG_1 = 16;
    baudrate.S_SEG_2 = 5;
    baudrate.S_SJW = 3;

    CAN_Initialize(CAN2, &canConfig, &baudrate);
    CAN_Standby(CAN2, DISABLE);

}

void MSP_CAN_Init(CAN_Type* CANx)
{

    if (CANx == CAN1)
    {
        /* USER CODE BEGIN MSP_CAN1_Init 0 */

        /* USER CODE END MSP_CAN1_Init 0 */
    
        /**
        GPIO Configuration for CAN1        
        PA4         --> CAN1_RX
        PA5         --> CAN1_TX 
        */
        GPIO_SetFunc(GPIO_PA4, GPIO_FUN2);

        GPIO_SetFunc(GPIO_PA5, GPIO_FUN2);

        /* CAN1 interrupt Init */
        NVIC_SetPriority(CAN1_IRQn, 3);
        NVIC_EnableIRQ(CAN1_IRQn);

        /* USER CODE BEGIN MSP_CAN1_Init 1 */

        /* USER CODE END MSP_CAN1_Init 1 */
    }
    else if (CANx == CAN2)
    {
        /* USER CODE BEGIN MSP_CAN2_Init 0 */

        /* USER CODE END MSP_CAN2_Init 0 */
    
        /**
        GPIO Configuration for CAN2        
        PC10         --> CAN2_TX
        PC11         --> CAN2_RX 
        */
        GPIO_SetFunc(GPIO_PC10, GPIO_FUN1);

        GPIO_SetFunc(GPIO_PC11, GPIO_FUN1);

        /* CAN2 interrupt Init */
        NVIC_SetPriority(CAN2_IRQn, 2);
        NVIC_EnableIRQ(CAN2_IRQn);

        /* USER CODE BEGIN MSP_CAN2_Init 1 */

        /* USER CODE END MSP_CAN2_Init 1 */
    }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT AutoChips *****END OF FILE****/
