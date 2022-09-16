/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2022 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "can.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include <string.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t hello[] = "hello world!\r\n";//串口测试用
char DataBuff[30] = {0};
uint8_t RxBuff;
uint8_t RxLine=0;           //接收到的数据长度
uint8_t Rx_flag=0;					//接受到数据标志
char DataBuff_1[30] = {0};
uint8_t RxBuff_1;
uint8_t RxLine_1=0;           //接收到的数据长度
uint8_t Rx_flag_1=0;					//接受到数据标志

#define       CAN_SEND_DATA_ID501 	  	(0x00000501)//锁车、解锁
//一级锁车 First level locking{0x46, 0x69, 0x72, 0x73, 0x74, 0x20, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x20, 0x6C, 0x6F, 0x63, 0x6B, 0x69, 0x6E, 0x67}
char 	  			UART_RrcvDataBuf_1        []= "First level locking";
uint8_t				CAN_TecvDataBuf_1         [8] = {0x00, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};//一级锁车
//二级锁车 Secondary locking{0x53, 0x65, 0x63, 0x6F, 0x6E, 0x64, 0x61, 0x72, 0x79, 0x20, 0x6C, 0x6F, 0x63, 0x6B, 0x69, 0x6E, 0x67}
char   		   UART_RrcvDataBuf_2        []= "Secondary locking";
uint8_t				CAN_TecvDataBuf_2         [8] = {0x00, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00};//二级锁车
//解除锁车 Release the lock{0x52, 0x65, 0x6C, 0x65, 0x61, 0x73, 0x65, 0x20, 0x74, 0x68, 0x65, 0x20, 0x6C, 0x6F, 0x63, 0x6B}
char			  	UART_RrcvDataBuf_UN       []= "Release the lock";
uint8_t				CAN_TecvDataBuf_UN        [8] = {0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};//解锁

#define       CAN_SEND_DATA_ID504			  (0x00000504)//锁车、解锁反馈
uint8_t				CAN_RecvDataBuf_2_return  [8] = {0x00, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00};//二级锁车反馈
uint8_t				CAN_RecvDataBuf_1_return  [8] = {0x00, 0x05, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};//一级锁车反馈
uint8_t				CAN_RecvDataBuf_UN_return [8] = {0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};//解锁反馈

#define       CAN_SEND_DATA_ID502		  	(0x00000502)//关闭、打开GPS监控
//开启监控 Turn on monitoring { 0x54, 0x75, 0x72, 0x6E, 0x20, 0x6F, 0x6E, 0x20, 0x6D, 0x6F, 0x6E, 0x69, 0x74, 0x6F, 0x72, 0x69, 0x6E, 0x67}
char			  	UART_RrcvDataBuf_ON_gps   []= "Turn on monitoring";
uint8_t				CAN_TecvDataBuf_ON_gps    [8] = {0x02, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00};//打开GPS
//关闭监控 Turn off monitoring { 0x54, 0x75, 0x72, 0x6E, 0x20, 0x6F, 0x66, 0x66, 0x20, 0x6D, 0x6F, 0x6E, 0x69, 0x74, 0x6F, 0x72, 0x69, 0x6E, 0x67} 
char					UART_RrcvDataBuf_OFF_gps  []= "Turn off monitoring";
uint8_t				CAN_TecvDataBuf_OFF_gps   [8] = {0x01, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};//关闭GPS

#define       CAN_SEND_DATA_ID503			  (0x00000503)//关闭、打开GPS反馈
uint8_t				CAN_RecvDataBuf_ON_return [8] = {0x02, 0x03, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00};//打开GPS反馈
uint8_t				CAN_RecvDataBuf_OFF_return[8] = {0x01, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00};//关闭GPS反馈

char					UART_RrcvDataBuf_Run   []= "LC:AE457467\r\n";//开启跑表功能
char					UART_RrcvDataBuf_Stop  []= "LC:AE45786B\r\n";//关闭跑表功能
char					UART_RrcvDataBuf_Run1  []= "LC:E9157472\r\n";//开启跑表功能
char					UART_RrcvDataBuf_Stop1 []= "LC:E9157876\r\n";//关闭跑表功能
uint8_t can_1=0;
uint8_t can_2=0;
uint8_t can_UN=0;
uint8_t can_ON=0;
uint8_t can_OFF=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN1_Init();
  MX_CAN2_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_I2C2_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
	CAN_Confing();
	HAL_UART_Receive_IT(&huart1, &RxBuff, 1); //打开串口中断接收
	HAL_UART_Receive_IT(&huart2, &RxBuff_1, 1); //打开串口中断接收
	HAL_TIM_Base_Start_IT(&htim5);//开启指示灯定时器
	HAL_TIM_Base_Start_IT(&htim6);//开启串口缓冲时间定时器
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		HAL_Delay(400);
//		printf("微信公众号：果果小师弟\n");
		Data_buff_Comparison();
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /**Configure the Systick interrupt time
    */
  __HAL_RCC_PLLI2S_ENABLE();

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
/***
  * 函数功能: CAN中断转发服务函数
  * 输入参数: CAN_HandleTypeDef* hcan
  * 返 回 值: 无
  * 说    明: 无
  */
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan)
{  
	//CAN1转发到CAN2端口
	if(hcan==&hcan1)//判断是否CAN1收到消息
		{
			if(hcan->pRxMsg->ExtId==0x00000504)
				{
					if((hcan->pRxMsg->Data[1]==0x05)&&(hcan->pRxMsg->Data[2]==0x01))
					{
						can_1=2;
						__HAL_TIM_SET_AUTORELOAD(&htim5, 4999);
					}
				}
				
			if(hcan->pRxMsg->ExtId==0x00000504)
			{
				if((hcan->pRxMsg->Data[1]==0x05)&&(hcan->pRxMsg->Data[2]==0x02))
				{
					can_2=3;
					__HAL_TIM_SET_AUTORELOAD(&htim5, 4999);
				}
			}
			if(hcan->pRxMsg->ExtId==0x00000504)
			{
				if((hcan->pRxMsg->Data[1]==0x08)&&(hcan->pRxMsg->Data[2]==0x00))
				{
					can_UN=4;
					__HAL_TIM_SET_AUTORELOAD(&htim5, 4999);
				}
			}	
			if(hcan->pRxMsg->ExtId==0x00000503)
			{
				if((hcan->pRxMsg->Data[1]==0x02)&&(hcan->pRxMsg->Data[2]==0x03))
				{
					can_OFF=5;
					__HAL_TIM_SET_AUTORELOAD(&htim5, 4999);
				}
			}		
			if(hcan->pRxMsg->ExtId==0x00000503)
			{
				if((hcan->pRxMsg->Data[1]==0x03)&&(hcan->pRxMsg->Data[2]==0x05))
				{
					can_ON=6;
					__HAL_TIM_SET_AUTORELOAD(&htim5, 4999);
				}
			}			

		}
	//CAN2转发到CAN1端口
	if(hcan==&hcan2)//如果CAN2收到数据
		{
			if(hcan->pRxMsg->ExtId==0x00000504)
				{
					if((hcan->pRxMsg->Data[1]==0x05)&&(hcan->pRxMsg->Data[2]==0x01))
					{
						can_1=2;
						__HAL_TIM_SET_AUTORELOAD(&htim5, 4999);
					}
				}
				
			if(hcan->pRxMsg->ExtId==0x00000504)
			{
				if((hcan->pRxMsg->Data[1]==0x05)&&(hcan->pRxMsg->Data[2]==0x02))
				{
					can_2=3;
					__HAL_TIM_SET_AUTORELOAD(&htim5, 4999);
				}
			}
			if(hcan->pRxMsg->ExtId==0x00000504)
			{
				if((hcan->pRxMsg->Data[1]==0x08)&&(hcan->pRxMsg->Data[2]==0x00))
				{
					can_UN=4;
					__HAL_TIM_SET_AUTORELOAD(&htim5, 4999);
				}
			}	
			if(hcan->pRxMsg->ExtId==0x00000503)
			{
				if((hcan->pRxMsg->Data[1]==0x02)&&(hcan->pRxMsg->Data[2]==0x03))
				{
					can_OFF=5;
					__HAL_TIM_SET_AUTORELOAD(&htim5, 4999);
				}
			}		
			if(hcan->pRxMsg->ExtId==0x00000503)
			{
				if((hcan->pRxMsg->Data[1]==0x03)&&(hcan->pRxMsg->Data[2]==0x05))
				{
					can_ON=6;
					__HAL_TIM_SET_AUTORELOAD(&htim5, 4999);
				}
			}
		}
}

//DataBuff数据对比函数 
void Data_buff_Comparison(void )
{
	if(strcmp(DataBuff_1, UART_RrcvDataBuf_1) == 0)//一级锁车
	{
		while (can_1 <2)
		{		
			hcan1.pTxMsg->ExtId =CAN_SEND_DATA_ID502;
			for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
			{hcan1.pTxMsg->Data[i] =CAN_TecvDataBuf_1[i];}
			HAL_CAN_Transmit(&hcan1, 10);//CAN2发送数据
			__HAL_CAN_ENABLE_IT(&hcan1,CAN_IT_FMP0);//重新开启FIF00消息挂号中断	
			
			hcan2.pTxMsg->ExtId =CAN_SEND_DATA_ID502;
			for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
			{hcan2.pTxMsg->Data[i] =CAN_TecvDataBuf_1[i];}
			HAL_CAN_Transmit(&hcan2, 10);//CAN2发送数据
			__HAL_CAN_ENABLE_IT(&hcan2,CAN_IT_FMP0);//重新开启FIF00消息挂号中断
			
			__HAL_TIM_SET_AUTORELOAD(&htim5, 999);
			HAL_Delay (100);
		}
	}
	if (strcmp(DataBuff_1, UART_RrcvDataBuf_2) == 0)//一级锁车
	{
		while (can_2<3)
		{		
			hcan1.pTxMsg->ExtId =CAN_SEND_DATA_ID501;
			for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
			{hcan1.pTxMsg->Data[i] =CAN_TecvDataBuf_2[i];}
			HAL_CAN_Transmit(&hcan1, 10);//CAN2发送数据
			__HAL_CAN_ENABLE_IT(&hcan1,CAN_IT_FMP0);//重新开启FIF00消息挂号中断	
			
			hcan2.pTxMsg->ExtId =CAN_SEND_DATA_ID501;
			for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
			{hcan2.pTxMsg->Data[i] =CAN_TecvDataBuf_2[i];}
			HAL_CAN_Transmit(&hcan2, 10);//CAN2发送数据
			__HAL_CAN_ENABLE_IT(&hcan2,CAN_IT_FMP0);//重新开启FIF00消息挂号中断
			
			__HAL_TIM_SET_AUTORELOAD(&htim5, 999);
			HAL_Delay (100);		
		}
	}
	if (strcmp(DataBuff_1, UART_RrcvDataBuf_UN) == 0)//解锁
	{
		while (can_UN<4)
		{		
			hcan1.pTxMsg->ExtId =CAN_SEND_DATA_ID501;
			for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
			{hcan1.pTxMsg->Data[i] =CAN_TecvDataBuf_UN[i];}
			HAL_CAN_Transmit(&hcan1, 10);//CAN2发送数据
			__HAL_CAN_ENABLE_IT(&hcan1,CAN_IT_FMP0);//重新开启FIF00消息挂号中断	
			
			hcan2.pTxMsg->ExtId =CAN_SEND_DATA_ID501;
			for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
			{hcan2.pTxMsg->Data[i] =CAN_TecvDataBuf_UN[i];}
			HAL_CAN_Transmit(&hcan2, 10);//CAN2发送数据
			__HAL_CAN_ENABLE_IT(&hcan2,CAN_IT_FMP0);//重新开启FIF00消息挂号中断
			
			__HAL_TIM_SET_AUTORELOAD(&htim5, 999);
			HAL_Delay (100);		
		}
	}
	if (strcmp(DataBuff_1, UART_RrcvDataBuf_ON_gps) == 0)//打开GPS
	{
		while (can_ON<6)
		{		
			hcan1.pTxMsg->ExtId =CAN_SEND_DATA_ID502;
			for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
			{hcan1.pTxMsg->Data[i] =CAN_TecvDataBuf_ON_gps[i];}
			HAL_CAN_Transmit(&hcan1, 10);//CAN2发送数据
			__HAL_CAN_ENABLE_IT(&hcan1,CAN_IT_FMP0);//重新开启FIF00消息挂号中断	
			
			hcan2.pTxMsg->ExtId =CAN_SEND_DATA_ID502;
			for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
			{hcan2.pTxMsg->Data[i] =CAN_TecvDataBuf_ON_gps[i];}
			HAL_CAN_Transmit(&hcan2, 10);//CAN2发送数据
			__HAL_CAN_ENABLE_IT(&hcan2,CAN_IT_FMP0);//重新开启FIF00消息挂号中断
			
			__HAL_TIM_SET_AUTORELOAD(&htim5, 999);
			HAL_Delay (100);		
		}
	}
	if (strcmp(DataBuff_1, UART_RrcvDataBuf_OFF_gps) == 0)//关闭GPS
	{
		while (can_OFF<5)
		{		
			hcan1.pTxMsg->ExtId =CAN_SEND_DATA_ID502;
			for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
			{hcan1.pTxMsg->Data[i] =CAN_TecvDataBuf_OFF_gps[i];}
			HAL_CAN_Transmit(&hcan1, 10);//CAN2发送数据
			__HAL_CAN_ENABLE_IT(&hcan1,CAN_IT_FMP0);//重新开启FIF00消息挂号中断	
			
			hcan2.pTxMsg->ExtId =CAN_SEND_DATA_ID502;
			for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
			{hcan2.pTxMsg->Data[i] =CAN_TecvDataBuf_OFF_gps[i];}
			HAL_CAN_Transmit(&hcan2, 10);//CAN2发送数据
			__HAL_CAN_ENABLE_IT(&hcan2,CAN_IT_FMP0);//重新开启FIF00消息挂号中断
			
			__HAL_TIM_SET_AUTORELOAD(&htim5, 999);
			HAL_Delay (100);		
		}
	}
	if (strcmp(DataBuff, UART_RrcvDataBuf_Run) == 0||strcmp(DataBuff, UART_RrcvDataBuf_Run1) == 0)//开启跑表功能
	{
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Base_Start_IT(&htim4);
		__HAL_TIM_SET_AUTORELOAD(&htim5, 4999);
		HAL_GPIO_WritePin(GPIOC, JQ_1_Pin,GPIO_PIN_SET);
	}	
	if (strcmp(DataBuff, UART_RrcvDataBuf_Stop) == 0||strcmp(DataBuff, UART_RrcvDataBuf_Stop1) == 0)//开启跑表功能
	{
		HAL_TIM_Base_Stop_IT(&htim2);
    HAL_TIM_Base_Stop_IT(&htim3);
    HAL_TIM_Base_Stop_IT(&htim4);
		__HAL_TIM_SET_AUTORELOAD(&htim5, 9999);
		HAL_GPIO_WritePin(GPIOC, JQ_1_Pin,GPIO_PIN_RESET);
	}
//	HAL_Delay(1000);
  memset(DataBuff,0,sizeof(DataBuff));  //清空缓存数组
	memset(DataBuff_1,0,sizeof(DataBuff_1));  //清空缓存数组
	RxLine=0;	RxLine_1=0;
	can_1=0;can_2=0;can_UN=0;can_ON=0;can_OFF=0;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
