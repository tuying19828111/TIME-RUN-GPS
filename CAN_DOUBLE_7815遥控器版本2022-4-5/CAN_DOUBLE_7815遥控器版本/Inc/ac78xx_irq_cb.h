/**
  ******************************************************************************
  * @file    ac78xx_irq_cb.h
  * @brief   This file contains the headers of the irq callback.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AC78XX_IRQ_CB_H
#define __AC78XX_IRQ_CB_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* --------------------------------- Includes ---------------------------------*/
#include "ac78xx.h"
#include "ac78xx_gpio.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* --------------------------------- Exported Types ---------------------------------*/
/* USER CODE BEGIN Exported_Types */

/* USER CODE END Exported_Types */

/* --------------------------------- Exported Constants ---------------------------------*/
/* USER CODE BEGIN Exported_Constants */

/* USER CODE END Exported_Constants */

/* --------------------------------- Exported Macros ---------------------------------*/
/* USER CODE BEGIN Exported_Macros */
void UART_Command_Judge(void );
/* USER CODE END Exported_Macros */

/* --------------------------------- Exported Function Prototypes ---------------------------------*/
int32_t UART1_IRQHandler_Callback(uint8_t port, uint32_t lsr0, uint32_t lsr1);
int32_t UART3_IRQHandler_Callback(uint8_t port, uint32_t lsr0, uint32_t lsr1);
void TIMER0_IRQHandler_Callback(uint8_t arg);
void TIMER1_IRQHandler_Callback(uint8_t arg);
int32_t CAN1_IRQHandler_Callback(uint32_t event, uint32_t wparam, uint32_t lparam);
int32_t CAN2_IRQHandler_Callback(uint32_t event, uint32_t wparam, uint32_t lparam);

#ifdef __cplusplus
}
#endif

#endif /* __AC78XX_IRQ_CB_H */

/************************ (C) COPYRIGHT AutoChips *****END OF FILE****/
