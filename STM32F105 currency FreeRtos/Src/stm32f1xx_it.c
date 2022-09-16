/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
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
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "stm32f1xx_it.h"

/* USER CODE BEGIN 0 */
#include "main.h"

////跑表部分变量
#define CAN_SEND_DATA_ID200			(0x00000200)
#define CAN_SEND_DATA_ID201			(0x00000201)
#define CAN_SEND_DATA_ID202			(0x00000202)
#define CAN_SEND_DATA_ID203			(0x00000203)
#define CAN_SEND_DATA_ID204			(0x00000204)
#define CAN_SEND_DATA_IDF20			(0x00000F20)
#define CAN_SEND_DATA_IDF30			(0x00000F30)
#define CAN_SEND_DATA_IDF99			(0x00000F99)

uint8_t					CAN_RECVDataBuf_200[8] = {0x28, 0x01, 0x31, 0x00, 0xE8, 0x03, 0xE8, 0x03};
uint8_t					CAN_RECVDataBuf_201[8] = {0x89, 0x00, 0x01, 0x00, 0x9f, 0x00, 0x00, 0x00};
uint8_t					CAN_RECVDataBuf_202[8] = {0x46, 0x00, 0x35, 0x00, 0xA9, 0x00, 0xC6, 0x00};
uint8_t					CAN_RECVDataBuf_203[8] = {0x31, 0x00, 0x46, 0x00, 0x4A, 0x00, 0x1E, 0x00};
uint8_t					CAN_RECVDataBuf_204[8] = {0xB8, 0x27, 0x7D, 0x00, 0x8C, 0x07, 0x84, 0x00};
uint8_t					CAN_RECVDataBuf_F20[8] = {0x04, 0x05, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t					CAN_RECVDataBuf_F30[8] = {0x66, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t					CAN_RECVDataBuf_F31[8] = {0xAA, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t					CAN_RECVDataBuf_F99[8] = {0x22, 0x16, 0x0A, 0x21, 0x01, 0x21, 0x01, 0x02};
static uint8_t F_30=0;
#define LED_Delay1s   96000000-1
#define LED_Delay500m 48000000-1
#define LED_Delay250m 24000000-1
#define LED_Delay100m 9600000-1
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

/******************************************************************************/
/*            Cortex-M3 Processor Interruption and Exception Handlers         */
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Prefetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles CAN1 RX0 interrupt.
*/
void CAN1_RX0_IRQHandler(void)
{
  /* USER CODE BEGIN CAN1_RX0_IRQn 0 */

  /* USER CODE END CAN1_RX0_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan1);
  /* USER CODE BEGIN CAN1_RX0_IRQn 1 */

  /* USER CODE END CAN1_RX0_IRQn 1 */
}

/**
* @brief This function handles TIM2 global interrupt.
*/
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */
	if(F_30<3)
	{
		hcan1.pTxMsg->ExtId  =CAN_SEND_DATA_IDF30;
		for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
		{hcan1.pTxMsg->Data[i]=CAN_RECVDataBuf_F30[i];}
		HAL_CAN_Transmit(&hcan1, 10);//CAN2发
	
		hcan2.pTxMsg->ExtId  =CAN_SEND_DATA_IDF30;
		for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
		{hcan2.pTxMsg->Data[i]=CAN_RECVDataBuf_F30[i];}
		HAL_CAN_Transmit(&hcan2, 10);//CAN2发
		F_30=5;
	}
	else 
	{
		hcan1.pTxMsg->ExtId  =CAN_SEND_DATA_IDF30;
		for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
		{hcan1.pTxMsg->Data[i]=CAN_RECVDataBuf_F31[i];}
		HAL_CAN_Transmit(&hcan1, 10);//CAN2发
	
		hcan2.pTxMsg->ExtId  =CAN_SEND_DATA_IDF30;
		for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
		{hcan2.pTxMsg->Data[i]=CAN_RECVDataBuf_F31[i];}
		HAL_CAN_Transmit(&hcan2, 10);//CAN2发
		F_30=2;
	}
  /* USER CODE END TIM2_IRQn 1 */
}

/**
* @brief This function handles TIM3 global interrupt.
*/
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */
	hcan1.pTxMsg->ExtId  =CAN_SEND_DATA_ID200;
	for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
	{hcan1.pTxMsg->Data[i]=CAN_RECVDataBuf_200[i];}
	HAL_CAN_Transmit(&hcan1, 10);//CAN2发
	hcan2.pTxMsg->ExtId  =CAN_SEND_DATA_ID200;
	for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
	{hcan2.pTxMsg->Data[i]=CAN_RECVDataBuf_200[i];}
	HAL_CAN_Transmit(&hcan2, 10);//CAN2发
	
	hcan1.pTxMsg->ExtId  =CAN_SEND_DATA_ID201;
	for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
	{hcan1.pTxMsg->Data[i]=CAN_RECVDataBuf_201[i];}
	HAL_CAN_Transmit(&hcan1, 10);//CAN2发
	hcan2.pTxMsg->ExtId  =CAN_SEND_DATA_ID201;
	for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
	{hcan2.pTxMsg->Data[i]=CAN_RECVDataBuf_201[i];}
	HAL_CAN_Transmit(&hcan2, 10);//CAN2发
	
	hcan1.pTxMsg->ExtId  =CAN_SEND_DATA_ID202;
	for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
	{hcan1.pTxMsg->Data[i]=CAN_RECVDataBuf_202[i];}
	HAL_CAN_Transmit(&hcan1, 10);//CAN2发
	hcan2.pTxMsg->ExtId  =CAN_SEND_DATA_ID202;
	for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
	{hcan2.pTxMsg->Data[i]=CAN_RECVDataBuf_202[i];}
	HAL_CAN_Transmit(&hcan2, 10);//CAN2发
	
	hcan1.pTxMsg->ExtId  =CAN_SEND_DATA_ID203;
	for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
	{hcan1.pTxMsg->Data[i]=CAN_RECVDataBuf_203[i];}
	HAL_CAN_Transmit(&hcan1, 10);//CAN2发
	hcan2.pTxMsg->ExtId  =CAN_SEND_DATA_ID203;
	for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
	{hcan2.pTxMsg->Data[i]=CAN_RECVDataBuf_203[i];}
	HAL_CAN_Transmit(&hcan2, 10);//CAN2发
	
	hcan1.pTxMsg->ExtId  =CAN_SEND_DATA_ID204;
	for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
	{hcan1.pTxMsg->Data[i]=CAN_RECVDataBuf_204[i];}
	HAL_CAN_Transmit(&hcan1, 10);//CAN2发
	hcan2.pTxMsg->ExtId  =CAN_SEND_DATA_ID204;
	for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
	{hcan2.pTxMsg->Data[i]=CAN_RECVDataBuf_204[i];}
	HAL_CAN_Transmit(&hcan2, 10);//CAN2发
  /* USER CODE END TIM3_IRQn 1 */
}

/**
* @brief This function handles TIM4 global interrupt.
*/
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */

  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */
	hcan1.pTxMsg->ExtId  =CAN_SEND_DATA_IDF99;
	for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
	{hcan1.pTxMsg->Data[i]=CAN_RECVDataBuf_F99[i];}
	HAL_CAN_Transmit(&hcan1, 10);//CAN2发
	hcan2.pTxMsg->ExtId  =CAN_SEND_DATA_IDF99;
	for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
	{hcan2.pTxMsg->Data[i]=CAN_RECVDataBuf_F99[i];}
	HAL_CAN_Transmit(&hcan2, 10);//CAN2发
	
	 /* USER CODE BEGIN TIM4_IRQn 1 */
	hcan1.pTxMsg->ExtId  =CAN_SEND_DATA_IDF20;
	for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
	{hcan1.pTxMsg->Data[i]=CAN_RECVDataBuf_F20[i];}
	HAL_CAN_Transmit(&hcan1, 10);//CAN2发
	hcan2.pTxMsg->ExtId  =CAN_SEND_DATA_IDF20;
	for(uint8_t i=0;i<8;i++)//8次循环将CAN1收到的数据赋值给CAN2
	{hcan2.pTxMsg->Data[i]=CAN_RECVDataBuf_F20[i];}
	HAL_CAN_Transmit(&hcan2, 10);//CAN2发
  /* USER CODE END TIM4_IRQn 1 */
}

/**
* @brief This function handles USART1 global interrupt.
*/
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
* @brief This function handles USART2 global interrupt.
*/
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
* @brief This function handles TIM5 global interrupt.
*/
void TIM5_IRQHandler(void)
{
  /* USER CODE BEGIN TIM5_IRQn 0 */

  /* USER CODE END TIM5_IRQn 0 */
  HAL_TIM_IRQHandler(&htim5);
  /* USER CODE BEGIN TIM5_IRQn 1 */
  HAL_GPIO_TogglePin(GPIOC, LED_1_Pin|JQ_1_Pin);
  /* USER CODE END TIM5_IRQn 1 */
}

/**
* @brief This function handles TIM6 global interrupt.
*/
void TIM6_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_IRQn 0 */

  /* USER CODE END TIM6_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_IRQn 1 */
//	Data_buff_Comparison();
  /* USER CODE END TIM6_IRQn 1 */
}

/**
* @brief This function handles CAN2 RX0 interrupt.
*/
void CAN2_RX0_IRQHandler(void)
{
  /* USER CODE BEGIN CAN2_RX0_IRQn 0 */

  /* USER CODE END CAN2_RX0_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan2);
  /* USER CODE BEGIN CAN2_RX0_IRQn 1 */
	
  /* USER CODE END CAN2_RX0_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
