
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* --------------------------------- Includes ---------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* --------------------------------- Exported Types ---------------------------------*/
/* USER CODE BEGIN Exported_Types */

/* USER CODE END Exported_Types */

/* --------------------------------- Exported Constants ---------------------------------*/
/********** GPIO Enum ***********/
typedef enum
{
    GPIO_DRIVING_4MA = 0,
    GPIO_DRIVING_8MA,
    GPIO_DRIVING_12MA,
    GPIO_DRIVING_16MA
}GPIO_DrivingType;	
	
typedef enum
{
    GPIO_IN = 0,
    GPIO_OUT
}GPIO_DirType;

/*!< GPIO pin level enumeration */
typedef enum
{
    GPIO_LEVEL_LOW = 0,
    GPIO_LEVEL_HIGH
}GPIO_LevelType;

typedef enum
{
    GPIO_FUN0 = 0,
    GPIO_FUN1,
    GPIO_FUN2,
    GPIO_FUN3
}GPIO_FunType;

/* USER CODE BEGIN Exported_Constants */

/* USER CODE END Exported_Constants */

/* --------------------------------- Exported Macros ---------------------------------*/
/* USER CODE BEGIN Exported_Macros */

/* USER CODE END Exported_Macros */

/* --------------------------------- Defines ---------------------------------*/

#define LED_1_Pin GPIO_PB14
#define JDQ_1_Pin GPIO_PB15

/* USER CODE BEGIN Defines */
#define LED_1_ON					do{GPIO_SetPinBits(GPIO_PB14);}while(0)
#define LED_1_OFF					do{GPIO_ResetPinBits(GPIO_PB14);}while(0)
#define LED_1_TOGGLE			do{if(GPIO_GetPinValue(GPIO_PB14)){LED_1_OFF;}else{LED_1_ON;}}while(0)

/* USER CODE END Defines */

#ifdef __cplusplus
 extern "C" {
#endif
/* --------------------------------- Exported Function Prototypes ---------------------------------*/
/* USER CODE BEGIN Exported_Function_Prototypes */

/* USER CODE END Exported_Function_Prototypes */
void Error_Handler(char *, int);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT AutoChips *****END OF FILE****/
