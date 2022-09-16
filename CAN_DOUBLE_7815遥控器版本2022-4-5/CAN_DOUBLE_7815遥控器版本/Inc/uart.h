/**
  ******************************************************************************
  * File Name          : UART.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __uart_H
#define __uart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* --------------------------------- Includes ---------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

typedef enum {
    UART_DMA_TXRX_NONE = 0, /*!< UART DMA TX and RX: all disable */
    UART_DMA_RX_EN,         /*!< UART DMA RX enable */
    UART_DMA_TX_EN,         /*!< UART DMA TX enable */
    UART_DMA_TXRX_EN        /*!< UART DMA TX and RX: all enable */
}UART_DmaEnType;

typedef enum {
    UART_SMP_CNT0 = 0,      /*!< SAM_CNT0: based on 16*baud_pulse, baud_rate = APB CLOCK/16/{DLH, DLL} */
    UART_SMP_CNT1,          /*!< SAM_CNT1: based on 8*baud_pulse, baud_rate = APB CLOCK/8/{DLH, DLL} */
    UART_SMP_CNT2,          /*!< SAM_CNT2: based on 4*baud_pulse, baud_rate = APB CLOCK/4/{DLH, DLL} */
    UART_SMP_CNT3           /*!< SAM_CNT3: based on sampe_count*baud_pulse, baud_rate = APB CLOCK/16/{DLM, DLL} */
}UART_SampleCntType;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

extern void Error_Handler(char *, int);

void ATC_UART1_Init(void);
void ATC_UART3_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ uart_H */

/************************ (C) COPYRIGHT AutoChips *****END OF FILE****/
