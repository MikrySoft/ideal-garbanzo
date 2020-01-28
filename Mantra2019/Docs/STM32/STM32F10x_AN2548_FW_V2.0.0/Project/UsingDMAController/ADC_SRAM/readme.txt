/**
  @page ADC_SRAM AN2548 ADC_SRAM Readme file
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file ADC_SRAM/readme.txt 
  * @author   MCD Application Team
  * @version  V2.0.0
  * @date     04/27/2009
  * @brief    Description of the AN2548 Application note's ADC_SRAM.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
   @endverbatim

@par Description 

This example describes how  to use the ADC and DMA to transfer continuously 
converted data from ADC to a data buffer. The data is used for internal computation
(peak value is computed and data is normalized - a simple Automatic Gain Control 
algorithm) and then transfered through a high speed SPI, using another DMA channel.

The ADC is configured to converts continuously ADC1 channel14.
Each time an end of conversion occurs the DMA transfers, in circular mode, the
converted data from ADC1 DR register to the ADC_ConvertedValue data array.
The ADC1 clock is set to 14 MHz.

When half of the data buffer is available, we parses the array and normalises 
the values in the array (the peak value is set to 0xFFFF). Once the normalisation
is completed, the SPI is used to send the results externally. 


@par Directory contents 

  - ADC_SRAM/inc/stm32f10x_conf.h  Library Configuration file
  - ADC_SRAM/src/stm32f10x_it.c    Interrupt handlers
  - ADC_SRAM/inc/stm32f10x_it.h    Interrupt handlers header file
  - ADC_SRAM/src/main.c            Main program

 
@par Hardware and Software environment  

  - This example runs on STM32F10x High-Density, STM32F10x Medium-Density and
    STM32F10x Low-Density Devices.
  
  - This example has been tested with STMicroelectronics STM3210B-EVAL  evaluation 
    boards and can be easily tailored to any other supported device and development 
    board. 
  
  - STM3210B-EVAL Set-up 
    - Connect a variable power supply 0-3.3V to ADC1 Channel14 mapped on pin PC.04
     (potentiometer RV1 on STM3210B-EVAL board) 
         
         
@par How to use it ? 

In order to load the ADC_SRAM code, you have do the following:

 - EWARM: 
    - Open the ADC_SRAM.eww workspace
    - In the workspace toolbar select the project config:
        - STM3210B-EVAL: to configure the project for STM32 High-density devices
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)

 - RIDE 
    - Open the ADC_SRAM.rprj project
    - In the configuration toolbar(Project->properties) select the project config:
        - STM3210B-EVAL: to configure the project for STM32 High-density devices
    - Rebuild all files: Project->build project
    - Load project image: Debug->start(ctrl+D)
    - Run program: Debug->Run(ctrl+F9)

 - RVMDK 
    - Open the ADC_SRAM.Uv2 project
    - In the build toolbar select the project config:  
        - STM3210B-EVAL: to configure the project for STM32 High-density devices
    - Rebuild all files: Project->Rebuild all target files
    - Load project image: Debug->Start/Stop Debug Session
    - Run program: Debug->Run (F5)

@note
 - Low-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 16 and 32 Kbytes.
 - Medium-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 32 and 128 Kbytes.
 - High-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 256 and 512 Kbytes.


 * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
 */
