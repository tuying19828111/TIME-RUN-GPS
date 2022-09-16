/**
  ******************************************************************************
  * File Name          : I2C.c
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
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
#include "ac78xx_i2c.h"
#include "i2c.h"

extern void Error_Handler(char *, int);

void MSP_I2C_Init(I2C_Type* I2Cx);

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* I2C2 init function */
void ATC_I2C2_Init(void)
{
    I2C_ConfigType i2cConfig;
    memset(&i2cConfig, 0, sizeof(i2cConfig));

    MSP_I2C_Init(I2C2);
    i2cConfig.sampleCNT = 11;
    i2cConfig.stepCNT = 19;
    i2cConfig.sclAdj = 0;
    i2cConfig.setting.i2cEn = ENABLE;
    i2cConfig.setting.intEn = DISABLE;
    i2cConfig.setting.master = I2C_MASTER;
    i2cConfig.setting.wakeUpEn = DISABLE;
    i2cConfig.setting.swRst = 0;
    i2cConfig.setting.gcaEn = DISABLE;
    i2cConfig.setting.addressExt = DISABLE;
    i2cConfig.setting.syncEn = DISABLE;
    i2cConfig.setting.arbEn = DISABLE;
    i2cConfig.setting.strEn = DISABLE;
    i2cConfig.setting.mntEn = DISABLE;
    i2cConfig.setting.mntIE = DISABLE;
    i2cConfig.setting.dmaRxEn = DISABLE;
    i2cConfig.setting.dmaTxEn = DISABLE;
    i2cConfig.setting.SSIE = DISABLE;
    i2cConfig.setting.rxOFIntEn = DISABLE;
    i2cConfig.setting.txUFIntEn = DISABLE;
    i2cConfig.setting.nackIntEn = DISABLE;
    i2cConfig.addr1 = 127;
    I2C_Initialize(I2C2, &i2cConfig);

}

void MSP_I2C_Init(I2C_Type* I2Cx)
{

    if (I2Cx == I2C2)
    {
    /* USER CODE BEGIN MSP_I2C2_Init 0 */

    /* USER CODE END MSP_I2C2_Init 0 */
    
    /**
    GPIO Configuration for I2C2    
    PC5     --> I2C2_SCL
    PC6     --> I2C2_SDA 
    */
    GPIO_SetFunc(GPIO_PC5, GPIO_FUN1);

    GPIO_SetFunc(GPIO_PC6, GPIO_FUN1);

    /* USER CODE BEGIN MSP_I2C2_Init 1 */

    /* USER CODE END MSP_I2C2_Init 1 */
    }
}

/* USER CODE BEGIN 1 */
void I2C_WriteByte(unsigned char dev_addr, unsigned int addr,const unsigned char Byte)
{
    uint32_t timeout = 0;
    uint32_t errorStatus = 0;

    while ((((I2C2)->STATUS_1.STATUS_1_Byte & 0x28) != I2C_STATUS_1_READY_MASK) && (timeout < I2C_READY_STATUS_TIMEOUT))
    {
        timeout ++;
    }
    if (timeout >= I2C_READY_STATUS_TIMEOUT)
    {
        errorStatus |= I2C_ERROR_START_NO_BUSY_FLAG;
    }
    errorStatus |= I2C_Start(I2C2);
    errorStatus |= I2C_WriteOneByte(I2C2, ((uint8_t)dev_addr << 1) | I2C_WRITE);
    if (errorStatus == I2C_ERROR_NULL)
    {
		errorStatus |= I2C_WriteOneByte(I2C2, (uint8_t)(addr&0xff));
        if (errorStatus == I2C_ERROR_NULL)
        {
			errorStatus |= I2C_WriteOneByte(I2C2, Byte);  
			if (errorStatus != I2C_ERROR_NULL) {}
        }
    }
    errorStatus |= I2C_Stop(I2C2);
        
}

unsigned char I2C_ReadByte(unsigned char dev_addr, unsigned int addr)
{
    uint32_t timeout = 0;
    uint32_t errorStatus = 0;
	uint8_t		byte_ch;

    while (((I2C2->STATUS_1.STATUS_1_Byte & 0x28) != I2C_STATUS_1_READY_MASK) && (timeout < I2C_READY_STATUS_TIMEOUT))
    {
        timeout ++;
    }
    if (timeout >= I2C_READY_STATUS_TIMEOUT)
    {
        errorStatus |= I2C_ERROR_START_NO_BUSY_FLAG;
    }
    errorStatus |= I2C_Start(I2C2);
	errorStatus |= I2C_WriteOneByte(I2C2, ((uint8_t)dev_addr << 1) | I2C_WRITE);
	if (errorStatus == I2C_ERROR_NULL)
    {
		errorStatus |= I2C_WriteOneByte(I2C2, (uint8_t)(addr&0xff));
        if (errorStatus == I2C_ERROR_NULL)
        {
			errorStatus |= I2C_Restart(I2C2);	
			errorStatus |= I2C_WriteOneByte(I2C2, ((uint8_t)dev_addr << 1) | I2C_READ);	
			//dummy read one byte to switch to Rx mode */
			I2C_ReadOneByte(I2C2, &byte_ch, I2C_SEND_NACK);   /* NACK will influence next transmission. */			
			if (errorStatus == I2C_ERROR_NULL)
			{
				errorStatus |= I2C_ReadLastOneByte(I2C2, &byte_ch, I2C_SEND_NACK);
			}
		}
    }
    errorStatus |= I2C_Stop(I2C2);

    return byte_ch;
}

uint32_t I2C_PageWrite(unsigned char dev_addr,unsigned int addr,unsigned char *str,unsigned int num)
{
    uint32_t i = 0,timeout = 0;
    uint32_t errorStatus = 0;

    while (((I2C2->STATUS_1.STATUS_1_Byte & 0x28) != I2C_STATUS_1_READY_MASK) && (timeout < I2C_READY_STATUS_TIMEOUT))
    {
        timeout ++;
    }
    if (timeout >= I2C_READY_STATUS_TIMEOUT)
    {
        errorStatus |= I2C_ERROR_START_NO_BUSY_FLAG;
    }
    errorStatus |= I2C_Start(I2C2);
    errorStatus |= I2C_WriteOneByte(I2C2, ((uint8_t)dev_addr << 1) | I2C_WRITE);
    if (errorStatus == I2C_ERROR_NULL)
    {
		errorStatus |= I2C_WriteOneByte(I2C2, (uint8_t)(addr&0xff));
        if (errorStatus == I2C_ERROR_NULL)
        {
			for (i = 0; i < num; i++)
			{
				errorStatus |= I2C_WriteOneByte(I2C2, str[i]);
				if (errorStatus != I2C_ERROR_NULL)
				{
					break;
				}
			}               
        }
    }
    errorStatus |= I2C_Stop(I2C2);
	
	return     errorStatus;
}

uint32_t I2C_PageRead(unsigned char dev_addr,unsigned int addr,unsigned char *str,unsigned int num)
{
    uint32_t i = 0,timeout = 0;
    uint32_t errorStatus = 0;

    while (((I2C2->STATUS_1.STATUS_1_Byte & 0x28) != I2C_STATUS_1_READY_MASK) && (timeout < I2C_READY_STATUS_TIMEOUT))
    {
        timeout ++;
    }
    if (timeout >= I2C_READY_STATUS_TIMEOUT)
    {
        errorStatus |= I2C_ERROR_START_NO_BUSY_FLAG;
    }
    errorStatus |= I2C_Start(I2C2);
	errorStatus |= I2C_WriteOneByte(I2C2, ((uint8_t)dev_addr << 1) | I2C_WRITE);
	if (errorStatus == I2C_ERROR_NULL)
    {
		errorStatus |= I2C_WriteOneByte(I2C2, (uint8_t)(addr&0xff));
        if (errorStatus == I2C_ERROR_NULL)
        {
			errorStatus |= I2C_Restart(I2C2);	
			errorStatus |= I2C_WriteOneByte(I2C2, ((uint8_t)dev_addr << 1) | I2C_READ);	
			//dummy read one byte to switch to Rx mode */
			if (num == 1)
			{
				I2C_ReadOneByte(I2C2, &str[0], I2C_SEND_NACK);   /* NACK will influence next transmission. */
			}else
			{
				I2C_ReadOneByte(I2C2, &str[0], I2C_SEND_ACK);
			}
			
			if (errorStatus == I2C_ERROR_NULL)
			{
				if (num == 1)
				{
					errorStatus |= I2C_ReadLastOneByte(I2C2, &str[0], I2C_SEND_NACK);
				}
				else
				{
					for (i = 0; i < num - 2; i++)
					{
						errorStatus |= I2C_ReadOneByte(I2C2, &str[i], I2C_SEND_ACK);
						if (errorStatus != I2C_ERROR_NULL)
						{
							break;
						}
					}
					errorStatus |= I2C_ReadOneByte(I2C2, &str[i++], I2C_SEND_NACK);
					errorStatus |= I2C_ReadLastOneByte(I2C2, &str[i], I2C_SEND_NACK);
				}
			}
		}
    }
    errorStatus |= I2C_Stop(I2C2);

    return errorStatus;    
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT AutoChips *****END OF FILE****/
