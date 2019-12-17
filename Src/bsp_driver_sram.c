/* USER CODE BEGIN Header */
/**
 ******************************************************************************
  * @file    bsp_driver_sram.c for F4 (based on stm32469i_eval_sram.c)
  * @brief   This file includes a generic SRAM driver.
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
/* USER CODE END Header */

#ifdef OLD_CODE
/* Kept to avoid issue when migrating old projects (as some user sections were renamed/changed). */
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
#else

/* Includes ------------------------------------------------------------------*/
#include "bsp_driver_sram.h"

/* Extern variables ----------------------------------------------------------*/
extern SRAM_HandleTypeDef hsram1;

/* USER CODE BEGIN Init */
/**
  * @brief  Initializes the SRAM device.
  * @retval SRAM status
  */
uint8_t BSP_SRAM_Init(void)
{ 
  uint8_t sramstatus = SRAM_OK;
  
  /* place for user code */
  
  return sramstatus;
}
/* USER CODE END Init */

/* USER CODE BEGIN BeforeReadSection */
/* can be used to modify / undefine following code or add code */
/* USER CODE END BeforeReadSection */

/**
  * @brief  Reads an amount of data from the SRAM device in polling mode.
  * @param  uwStartAddress: Read start address
  * @param  pData: Pointer to data to be read
  * @param  uwDataSize: Size of read data from the memory
  * @retval SRAM status
  */
uint8_t BSP_SRAM_ReadData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize)
{ 
  uint8_t sramstatus = SRAM_OK;

  if(HAL_SRAM_Read_16b(&hsram1, (uint32_t *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    sramstatus = SRAM_ERROR;
  }

  return sramstatus;
}

/**
  * @brief  Reads an amount of data from the SRAM device in DMA mode.
  * @param  uwStartAddress: Read start address
  * @param  pData: Pointer to data to be read
  * @param  uwDataSize: Size of read data from the memory
  * @retval SRAM status
  */
uint8_t BSP_SRAM_ReadData_DMA(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize)
{
  uint8_t sramstatus = SRAM_OK;
  
  if(HAL_SRAM_Read_DMA(&hsram1, (uint32_t *)uwStartAddress, (uint32_t *)pData, uwDataSize) != HAL_OK)
  {
    sramstatus = SRAM_ERROR;
  }

  return sramstatus;
}

/* USER CODE BEGIN BeforeWriteSection */
/* can be used to modify / undefine following code or add code */
/* USER CODE END BeforeWriteSection */

/**
  * @brief  Writes an amount of data from the SRAM device in polling mode.
  * @param  uwStartAddress: Write start address
  * @param  pData: Pointer to data to be written
  * @param  uwDataSize: Size of written data from the memory   
  * @retval SRAM status
  */
uint8_t BSP_SRAM_WriteData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize) 
{
  uint8_t sramstatus = SRAM_OK;
  
  if(HAL_SRAM_Write_16b(&hsram1, (uint32_t *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    sramstatus = SRAM_ERROR;
  }

  return sramstatus;
}

/**
  * @brief  Writes an amount of data from the SRAM device in DMA mode.
  * @param  uwStartAddress: Write start address
  * @param  pData: Pointer to data to be written
  * @param  uwDataSize: Size of written data from the memory
  * @retval SRAM status
  */
uint8_t BSP_SRAM_WriteData_DMA(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize)
{
  uint8_t sramstatus = SRAM_OK;
  
  if(HAL_SRAM_Write_DMA(&hsram1, (uint32_t *)uwStartAddress, (uint32_t *)pData, uwDataSize) != HAL_OK)
  {
    sramstatus = SRAM_ERROR;
  }

  return sramstatus;
}

/**
  * @brief  Handles SRAM DMA transfer interrupt request.
  */
void BSP_SRAM_DMA_IRQHandler(void)
{
  HAL_DMA_IRQHandler(hsram1.hdma);
}

/* USER CODE BEGIN AdditionalCode */
/* user code can be inserted here */
/* USER CODE END AdditionalCode */

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
