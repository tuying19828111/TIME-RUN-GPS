/**
  ******************************************************************************
  * @file    ac78xx_irq_cb.c
  * @brief   IRQ callback.
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
#include "ac78xx_timer.h"
#include "ac78xx_can.h"
/* USER CODE BEGIN Includes */
#include "main.h"
#include "i2c.h"
/* USER CODE END Includes */

/* --------------------------------- Typedefs ----------------------------------*/
/* USER CODE BEGIN Typedefs */

/* USER CODE END Typedefs */

/* --------------------------------- Defines -----------------------------------*/
/* USER CODE BEGIN Defines */
 
/* USER CODE END Defines */

/* --------------------------------- Macros ------------------------------------*/
/* USER CODE BEGIN Macros */

/* USER CODE END Macros */

/* --------------------------------- Variables ---------------------------------*/
/* USER CODE BEGIN Variables */
CAN_MSG_INFO  CAN1_TecvCANMsg;
CAN_MSG_INFO  CAN1_RecvCANMsg;
CAN_MSG_INFO  CAN2_TecvCANMsg;
CAN_MSG_INFO  CAN2_RecvCANMsg;
uint8_t i,j;
char 		DataBuff[28];
uint32_t		RxLine=0;
uint8_t 		Rx_flag=0;
extern uint32_t sum_1;
extern uint32_t sum_2;
extern uint32_t sum_3;
extern uint8_t  I2c_Buf_Write[4];
extern uint8_t at24c02_ADD;
char 		Time_Plus_1	    [28]= "LC:40CD2835\r\n";//减0.1H
char 		Time_reduce_1   [28]= "LC:40CD2431\r\n";//减0.1H
char		Time_Plus_10    [28]= "LC:40CD2835\r\nLC:40CD2835\r\n";//加20H
char		Time_reduce_10  [28]= "LC:40CD2431\r\nLC:40CD2431\r\n";//减20H
char		Time_Clear  [28]= "LC:40CD2C39\r\n";//清零
//uint8_t		Time_Plus_1   	  [26]= {0x4C,0x43,0x3A,0x34,0x30,0x43,0x44,0x32,0x38,0x33,0x35,0x0D,0x0A};//加0.1H
//uint8_t		Time_reduce_1     [26]= {0x4C,0x43,0x3A,0x34,0x30,0x43,0x44,0x32,0x34,0x33,0x31,0x0D,0x0A};
//uint8_t		Time_Plus_10			[26]= {0x4C,0x43,0x3A,0x34,0x30,0x43,0x44,0x32,0x38,0x33,0x35,0x0D,0x0A,0x4C,0x43,0x3A,0x34,0x30,0x43,0x44,0x32,0x38,0x33,0x35,0x0D,0x0A};
//uint8_t		Time_reduce_10		[26]= {0x4C,0x43,0x3A,0x34,0x30,0x43,0x44,0x32,0x34,0x33,0x31,0x0D,0x0A,0x4C,0x43,0x3A,0x34,0x30,0x43,0x44,0x32,0x34,0x33,0x31,0x0D,0x0A};
//uint8_t		Time_Clear   		  [26]= {0x4C,0x43,0x3A,0x34,0x30,0x43,0x44,0x32,0x43,0x33,0x39,0x0D,0x0A};
	
/* USER CODE END Variables */

/* --------------------------------- Function Prototypes -----------------------*/
/* USER CODE BEGIN Function_Prototypes */

/* USER CODE END Function_Prototypes */

/* --------------------------------- User Code ---------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/******************************************************************************/
/* ac78xx Peripheral Interrupt Handlers callbacks                             */
/******************************************************************************/

/**
* @brief This function handle UART1 interrupt.
* @return 0: success, other: error value
*/
int32_t UART1_IRQHandler_Callback(uint8_t port, uint32_t lsr0, uint32_t lsr1)
{
    if ((UART1->UARTn_IER.ERXNE == 1) && (lsr0 & LSR0_DR))
    {
        /* USER CODE BEGIN UART1 RECEIVE DATA */
				Rx_flag=1;
				DataBuff[RxLine++] = UART_ReceiveData(UART1);
				UART_SetRxIntEn(UART1, ENABLE);
			if(RxLine>0x1A)
			{
				memset(DataBuff,0,sizeof(DataBuff));  //清空缓存数组
				RxLine=0;	
			}
        /* USER CODE END UART1 RECEIVE DATA */
    }
    if ((UART1->UARTn_IER.ETXE == 1) && (lsr0 & LSR0_THRE))
    {
        /* USER CODE BEGIN UART1 SEND DATA */

        /* USER CODE END UART1 SEND DATA */
    }

    /* USER CODE BEGIN UART1_IRQHandler_Callback*/

    /* USER CODE END UART1_IRQHandler_Callback*/
    return 0;
}

/**
* @brief This function handle UART3 interrupt.
* @return 0: success, other: error value
*/
int32_t UART3_IRQHandler_Callback(uint8_t port, uint32_t lsr0, uint32_t lsr1)
{
    if ((UART3->UARTn_IER.ERXNE == 1) && (lsr0 & LSR0_DR))
    {
        /* USER CODE BEGIN UART3 RECEIVE DATA */

        /* USER CODE END UART3 RECEIVE DATA */
    }
    if ((UART3->UARTn_IER.ETXE == 1) && (lsr0 & LSR0_THRE))
    {
        /* USER CODE BEGIN UART3 SEND DATA */

        /* USER CODE END UART3 SEND DATA */
    }

    /* USER CODE BEGIN UART3_IRQHandler_Callback*/

    /* USER CODE END UART3_IRQHandler_Callback*/
    return 0;
}

/**
* @brief This function handle Timer 0 interrupt.
* @param[in] arg: timer callback argument
* @return none
*/
void TIMER0_IRQHandler_Callback(uint8_t arg)
{
    TIMER_ClrIntFlag(TIMER_GetTimerCtrl(arg));

    /* USER CODE BEGIN TIMER0_IRQHandler_Callback*/
//			LED_1_TOGGLE;
    /* USER CODE END TIMER0_IRQHandler_Callback*/
}

/**
* @brief This function handle Timer 1 interrupt.
* @param[in] arg: timer callback argument
* @return none
*/
void TIMER1_IRQHandler_Callback(uint8_t arg)
{
    TIMER_ClrIntFlag(TIMER_GetTimerCtrl(arg));

    /* USER CODE BEGIN TIMER1_IRQHandler_Callback*/
		if(Rx_flag==1)
			{
				UART_Command_Judge();
				Rx_flag=0;	
			}
    /* USER CODE END TIMER1_IRQHandler_Callback*/
}

/**
* @brief This function handle CAN 1 interrupt.
* @param[in] event: can event
* @param[in] wparam: reserved
* @param[in] lparam: reserved
* @return 0: success, other: error value
*/
int32_t CAN1_IRQHandler_Callback(uint32_t event, uint32_t wparam, uint32_t lparam)
{
    if (event & CAN_EVENT_RECVMSG)
    {
        /* USER CODE BEGIN CAN1 EVENT RECEIVE MESSAGE */
			if (CAN_IsMsgInReceiveBuf((CAN_Type*)lparam))
        {
            CAN_MessageRead((CAN_Type*)lparam, &CAN1_RecvCANMsg);
						if(CAN1_RecvCANMsg.ID==0x18FEE500)
							{
							CAN2_TecvCANMsg .ID =0x18FEE500;
							CAN2_TecvCANMsg .IDE=CAN1_RecvCANMsg.IDE;
							CAN2_TecvCANMsg .RTR=CAN1_RecvCANMsg.RTR;
							CAN2_TecvCANMsg .DLC=CAN1_RecvCANMsg.DLC;
																 j=CAN1_RecvCANMsg.DLC;
							for( i =0;i<4;i++) //把读取的数据利用for循环赋值给sum
								{
									sum_2 = (sum_2 << 8) + CAN1_RecvCANMsg .Data[3];
									sum_2 = (sum_2 << 8) + CAN1_RecvCANMsg .Data[2];	
									sum_2 = (sum_2 << 8) + CAN1_RecvCANMsg .Data[1];
									sum_2 = (sum_2 << 8) + CAN1_RecvCANMsg .Data[0];
								}	
							if(sum_1>0x7FFFFFFF)
								{sum_3=sum_2-(0xFFFFFFFF-sum_1+1);}
							if(sum_1<0x7FFFFFFF)
								{
								sum_3=sum_1+sum_2;
								}
//							if(sum_3>0x7FFFFFFF)
//								{sum_3=0X00000000;}
							for (i=0;i<4;i++)//循环4次将sum1数据赋值给I2c_Buf_Write数组
								{
									CAN1_RecvCANMsg .Data[0]=(sum_3)& 0xFF;
									CAN1_RecvCANMsg .Data[1]=(sum_3>>8)& 0xFF;
									CAN1_RecvCANMsg .Data[2]=(sum_3>>16)& 0xFF;
									CAN1_RecvCANMsg .Data[3]=(sum_3>>24)& 0xFF;
								}  
								for(i=0;i<j;i++)//8次循环将CAN1收到的数据赋值给CAN2
								{
									CAN2_TecvCANMsg .Data[i] =CAN1_RecvCANMsg .Data[i];
								}
								CAN_MessageSend(CAN2, &CAN2_TecvCANMsg, TRANSMIT_PRIMARY);
							}
					else//如果CAN2收到的ID不是0x18FEE500
						{
							CAN2_TecvCANMsg .ID =CAN1_RecvCANMsg.ID;
							CAN2_TecvCANMsg .IDE=CAN1_RecvCANMsg.IDE;
							CAN2_TecvCANMsg .RTR=CAN1_RecvCANMsg.RTR;
							CAN2_TecvCANMsg .DLC=CAN1_RecvCANMsg.DLC;
																 j=CAN1_RecvCANMsg.DLC;
							for(i=0;i<j;i++)//8次循环将CAN1收到的数据赋值给CAN2
							{
								CAN2_TecvCANMsg .Data[i]=CAN1_RecvCANMsg .Data[i];
							}
							CAN_MessageSend(CAN2,&CAN2_TecvCANMsg, TRANSMIT_PRIMARY);
						}
					}
        /* USER CODE END CAN1 EVENT RECEIVE MESSAGE */
    }

    /* USER CODE BEGIN CAN1_IRQHandler_Callback*/

    /* USER CODE END CAN1_IRQHandler_Callback*/
    return 0;
}

/**
* @brief This function handle CAN 2 interrupt.
* @param[in] event: can event
* @param[in] wparam: reserved
* @param[in] lparam: reserved
* @return 0: success, other: error value
*/
int32_t CAN2_IRQHandler_Callback(uint32_t event, uint32_t wparam, uint32_t lparam)
{
    if (event & CAN_EVENT_RECVMSG)
    {
        /* USER CODE BEGIN CAN2 EVENT RECEIVE MESSAGE */
			if (CAN_IsMsgInReceiveBuf((CAN_Type*)lparam))
        {
            CAN_MessageRead((CAN_Type*)lparam, &CAN2_RecvCANMsg);
						if(CAN2_RecvCANMsg.ID==0x18FEE500)
							{
							CAN1_TecvCANMsg .ID =0x18FEE500;
							CAN1_TecvCANMsg .IDE=CAN2_RecvCANMsg.IDE;
							CAN1_TecvCANMsg .RTR=CAN2_RecvCANMsg.RTR;
							CAN1_TecvCANMsg .DLC=CAN2_RecvCANMsg.DLC;
																 j=CAN2_RecvCANMsg.DLC;
							for( i =0;i<4;i++) //把读取的数据利用for循环赋值给sum
								{
									sum_2 = (sum_2 << 8) + CAN2_RecvCANMsg .Data[3];
									sum_2 = (sum_2 << 8) + CAN2_RecvCANMsg .Data[2];	
									sum_2 = (sum_2 << 8) + CAN2_RecvCANMsg .Data[1];
									sum_2 = (sum_2 << 8) + CAN2_RecvCANMsg .Data[0];
								}	
							if(sum_1>0x7FFFFFFF)
								{sum_3=sum_2-(0xFFFFFFFF-sum_1+1);}
							if(sum_1<0x7FFFFFFF)
								{
								sum_3=sum_1+sum_2;
								}
//							if(sum_3>0x7FFFFFFF)
//								{sum_3=0X00000000;}
							for (i=0;i<4;i++)//循环4次将sum1数据赋值给I2c_Buf_Write数组
								{
									CAN2_RecvCANMsg .Data[0]=(sum_3)& 0xFF;
									CAN2_RecvCANMsg .Data[1]=(sum_3>>8)& 0xFF;
									CAN2_RecvCANMsg .Data[2]=(sum_3>>16)& 0xFF;
									CAN2_RecvCANMsg .Data[3]=(sum_3>>24)& 0xFF;
								}  
								for(i=0;i<j;i++)//8次循环将CAN1收到的数据赋值给CAN2
								{
									CAN1_TecvCANMsg .Data[i] =CAN2_RecvCANMsg .Data[i];
								}
								CAN_MessageSend(CAN1, &CAN1_TecvCANMsg, TRANSMIT_PRIMARY);
							}
					else//如果CAN2收到的ID不是0x18FEE500
						{
							CAN1_TecvCANMsg .ID =CAN2_RecvCANMsg.ID;
							CAN1_TecvCANMsg .IDE=CAN2_RecvCANMsg.IDE;
							CAN1_TecvCANMsg .RTR=CAN2_RecvCANMsg.RTR;
							CAN1_TecvCANMsg .DLC=CAN2_RecvCANMsg.DLC;
																 j=CAN2_RecvCANMsg.DLC;
							for(i=0;i<j;i++)//8次循环将CAN1收到的数据赋值给CAN2
							{
								CAN1_TecvCANMsg .Data[i]=CAN2_RecvCANMsg .Data[i];
							}
							CAN_MessageSend(CAN1,&CAN1_TecvCANMsg, TRANSMIT_PRIMARY);
						}
					}
        /* USER CODE END CAN2 EVENT RECEIVE MESSAGE */
    }

    /* USER CODE BEGIN CAN2_IRQHandler_Callback*/

    /* USER CODE END CAN2_IRQHandler_Callback*/
    return 0;
}

/* USER CODE BEGIN 1 */
void UART_Command_Judge(void )
{
	if(strcmp(DataBuff, Time_Plus_1) == 0)//单击加
		{
			sum_1 =sum_1 +2;	
			memset(DataBuff,0,sizeof(DataBuff));  //清空缓存数组
			RxLine=0;	
		}
	if(strcmp(DataBuff, Time_reduce_1) == 0)//单击减
		{
			sum_1 =sum_1 -2;
			memset(DataBuff,0,sizeof(DataBuff));  //清空缓存数组
			RxLine=0;	
		}
	if(strcmp(DataBuff, Time_Plus_10) == 0)//双击加
		{
			sum_1 =sum_1 +20;	
			memset(DataBuff,0,sizeof(DataBuff));  //清空缓存数组
			RxLine=0;	
		}
	if(strcmp(DataBuff, Time_reduce_10) == 0)//双击减
		{
			sum_1 =sum_1 -20;
			memset(DataBuff,0,sizeof(DataBuff));  //清空缓存数组
			RxLine=0;	
		}
	if(strcmp(DataBuff, Time_Clear) == 0)//清零
		{
			sum_1 =0;
			memset(DataBuff,0,sizeof(DataBuff));  //清空缓存数组
			RxLine=0;	
		}	
	else 
		{
			memset(DataBuff,0,sizeof(DataBuff));  //清空缓存数组
			RxLine=0;	
		}
	for (int i=0;i<4;i++)//循环4次将sum1数据赋值给I2c_Buf_Write数组
    {
			I2c_Buf_Write[0]=(sum_1)& 0xFF;
			I2c_Buf_Write[1]=(sum_1>>8)& 0xFF;
			I2c_Buf_Write[2]=(sum_1>>16)& 0xFF;
			I2c_Buf_Write[3]=(sum_1>>24)& 0xFF;
    }  
	for(int i=0;i<4;i+=4)
		{
			I2C_PageWrite(at24c02_ADD,0,I2c_Buf_Write,4);//将I2c_Buf_Write写入AT24C02
			mdelay(5);// 短延时不能少
    }
		
}
/* USER CODE END 1 */
/************************ (C) COPYRIGHT AutoChips *****END OF FILE****/
