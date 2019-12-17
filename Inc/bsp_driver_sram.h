/**
 ******************************************************************************
  * @file    bsp_driver_sram.h (based on stm32469i_eval_sram.h)
  * @brief   This file contains the common defines and functions prototypes for  
  *          the bsp_driver_sram.c driver.
  ******************************************************************************  
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4_SRAM_H
#define __STM32F4_SRAM_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_sram.h"

/* USER CODE BEGIN 0 */

/** 
  * @brief  SRAM status structure definition  
  */     
#define SRAM_OK            ((uint8_t)0x00)
#define SRAM_ERROR         ((uint8_t)0x01)

#define SRAM_DEVICE_ADDR   ((uint32_t)0x64000000)
#define SRAM_DEVICE_SIZE   ((uint32_t)0x200000)  /* SRAM device size in MBytes */  

#define SRAM_MEMORY_WIDTH  FMC_NORSRAM_MEM_BUS_WIDTH_16
 
/* Other defines, such as the ones for SRAM DMA transfer, can be added here */

/* Exported functions --------------------------------------------------------*/
uint8_t BSP_SRAM_Init(void);
uint8_t BSP_SRAM_ReadData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
uint8_t BSP_SRAM_ReadData_DMA(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
uint8_t BSP_SRAM_WriteData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
uint8_t BSP_SRAM_WriteData_DMA(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
void BSP_SRAM_DMA_IRQHandler(void);

/* USER CODE END 0 */
   
#ifdef __cplusplus
}
#endif

#endif /* __STM32F4_SRAM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
