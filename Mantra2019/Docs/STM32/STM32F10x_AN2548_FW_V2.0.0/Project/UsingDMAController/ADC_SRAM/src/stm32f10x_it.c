/**
  ******************************************************************************
  * @file ADC_SRAM/src/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version  V2.0.0
  * @date  04/27/2009
  * @brief  Main Interrupt Service Routines.
  *         This file provides template for all exceptions handler and 
  *         peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"


/** @addtogroup ADC_SRAM
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint16_t ADC_ConvertedValue[512];
extern __IO uint16_t peak_Value;
extern __IO uint32_t buffer_ptr;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param:  None
  * @retval: None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param:  None
  * @retval: None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param:  None
  * @retval: None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param:  None
  * @retval: None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param:  None
  * @retval: None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param:  None
  * @retval: None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param:  None
  * @retval: None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param:  None
  * @retval: None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param:  None
  * @retval: None
  */
void SysTick_Handler(void)
{
}

/**
  * @brief  This function handles DMA1Channel1 interrupt request.
  * @param: None
  * @retval: None
  */

void DMA1_Channel1_IRQHandler(void)
{
  /* DMA1 channel used for ADC continous conversion */
  
  uint16_t half_buffer = 0, i = 0, temp = 0;
  
  /* Test on DMA Channel1 Transfer Complete interrupt */
  if(DMA_GetITStatus(DMA1_IT_TC1) || DMA_GetITStatus(DMA1_IT_HT1) )
  {
    if(DMA_GetITStatus(DMA1_IT_HT1))
    {
      half_buffer = 0;
    }
    
    if(DMA_GetITStatus(DMA1_IT_TC1))
    {
      half_buffer = 1;
    }
    
    /* Clear DMA Channel6 Half Transfer, Transfer Complete and Global interrupt pending bits */
    DMA_ClearITPendingBit(DMA1_IT_GL1);
    
    /* Start data normalisation when half ADC buffer is full */
    peak_Value = peak_Value - 4 ;  /* peak value decay in time */
    temp = 0x8000 / peak_Value;

    for(i = 256*half_buffer; i < (256*(1+half_buffer)); i++)
    {  
      if(peak_Value < (2 * ADC_ConvertedValue[i]))
      {
        peak_Value = ADC_ConvertedValue[i];  /* update peak value */
        temp = 0x8000 / peak_Value;
      }
      
      ADC_ConvertedValue[i] = temp * ADC_ConvertedValue[i];
    }
    
    /* Start SPI transfer when data is available */
    SPI_Cmd(SPI1, ENABLE); 
  }
}

/**
  * @brief  This function handles DMA1Channel3 interrupt request.
  * @param: None
  * @retval: None
  */

void DMA1_Channel3_IRQHandler(void)
{ 
  /* DMA3 channel used by SPI TX */
  
  /* Test on DMA Channel3 Transfer Complete or Half Transfer interrupt */
  if(DMA_GetITStatus(DMA1_IT_TC3) || DMA_GetITStatus(DMA1_IT_HT3))
  {
    /* Clear DMA Channel1 Half Transfer, Transfer Complete and Global interrupt pending bits */
    DMA_ClearITPendingBit(DMA1_IT_GL3);
    /* Stop SPI data transmision when half buffer is empty, waiting for
       half buffer full on Channel 1 - ADC */
    SPI_Cmd(SPI1, DISABLE);	 
  }
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param:  None
  * @retval: None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
