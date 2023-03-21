/*
 * LCD.c
 *
 *  Created on: Mar 21, 2023
 *      Author: Afeez
 */


#include "LCD.h"

/** @addtogroup BSP
  * @{
  */

/** @defgroup STM32L152C_DISCOVERY STM32L152C-Discovery
  * @brief This file provides firmware functions to manage Leds and push-buttons
  *        available on STM32L152C discovery board from STMicroelectronics.
  * @{
  */

/** @defgroup STM32L152C_Discovery_Common Common
  * @{
  */

/** @defgroup STM32L152C_DISCOVERY_Private_Defines Private Defines
  * @{
  */

/**
* @brief STM32L152C-Discovery BSP Driver version number
*/
#define __STM32L152C_DISCO_BSP_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __STM32L152C_DISCO_BSP_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __STM32L152C_DISCO_BSP_VERSION_SUB2   (0x05) /*!< [15:8]  sub2 version */
#define __STM32L152C_DISCO_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __STM32L152C_DISCO_BSP_VERSION         ((__STM32L152C_DISCO_BSP_VERSION_MAIN << 24)\
                                             |(__STM32L152C_DISCO_BSP_VERSION_SUB1 << 16)\
                                             |(__STM32L152C_DISCO_BSP_VERSION_SUB2 << 8 )\
                                             |(__STM32L152C_DISCO_BSP_VERSION_RC))
/**
  * @}
  */


/** @defgroup STM32L152C_DISCOVERY_Private_Variables Private Variables
  * @{
  */
GPIO_TypeDef* GPIO_PORT[LEDn] = {LED3_GPIO_PORT,
                                 LED4_GPIO_PORT};

const uint16_t GPIO_PIN[LEDn] = {LED3_PIN,
                                 LED4_PIN};


GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {USER_BUTTON_GPIO_PORT};
const uint16_t BUTTON_PIN[BUTTONn] = {USER_BUTTON_PIN};
const uint8_t BUTTON_IRQn[BUTTONn] = {USER_BUTTON_EXTI_IRQn};

/**
  * @}
  */

/** @defgroup STM32L152C_DISCOVERY_Exported_Functions Exported Functions
  * @{
  */

/**
  * @brief  This method returns the STM32L152C-Discovery BSP Driver revision
  * @retval version : 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __STM32L152C_DISCO_BSP_VERSION;
}

/** @defgroup STM32152C_DISCOVERY_LED_Functions LED Functions
  * @{
  */

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured.
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void BSP_LED_Init(Led_TypeDef Led)
{
  GPIO_InitTypeDef  gpioinitstruct = {0};

  /* Enable the GPIO_LED Clock */
  LEDx_GPIO_CLK_ENABLE(Led);

  /* Configure the GPIO_LED pin */
  gpioinitstruct.Pin   = GPIO_PIN[Led];
  gpioinitstruct.Mode  = GPIO_MODE_OUTPUT_PP;
  gpioinitstruct.Pull  = GPIO_NOPULL;
  gpioinitstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIO_PORT[Led], &gpioinitstruct);

  /* Reset PIN to switch off the LED */
  HAL_GPIO_WritePin(GPIO_PORT[Led],GPIO_PIN[Led], GPIO_PIN_RESET);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on.
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void BSP_LED_On(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_SET);
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off.
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void BSP_LED_Off(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET);
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled.
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void BSP_LED_Toggle(Led_TypeDef Led)
{
  HAL_GPIO_TogglePin(GPIO_PORT[Led], GPIO_PIN[Led]);
}
