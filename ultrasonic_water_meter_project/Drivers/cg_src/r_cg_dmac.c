/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2016, 2017 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_dmac.c
* Version      : Applilet4 for R7F0C019 V1.00.02.01 [30 Nov 2017]
* Device(s)    : R7F0C019L
* Tool-Chain   : CCRL
* Description  : This file implements device driver for DMAC module.
* Creation Date: 2021/5/4
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_dmac.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t g_Dmac0[1024];         /* dmac0 RAM address symbol */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_DMAC0_Create
* Description  : This function initializes the DMA0 transfer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC0_Create(void)
{
    DRC0 = _80_DMA_OPERATION_ENABLE;
    NOP();
    NOP();
    DMAMK0 = 1U; /* disable INTDMA0 interrupt */
    DMAIF0 = 0U; /* clear INTDMA0 interrupt flag */
    /* Set INTDMA0 low priority */
    DMAPR10 = 1U;
    DMAPR00 = 1U;
    DMC0 = _00_DMA_TRANSFER_DIR_SFR2RAM | _00_DMA_DATA_SIZE_8 | _00_DMA_TRIGGER_SOFTWARE;
    DSA0 = _1E_DMA0_SFR_ADDRESS;
    DRA0 = (uint16_t)g_Dmac0;
    DBC0 = _0000_DMA0_BYTE_COUNT;
    DEN0 = 0U; /* disable DMA0 operation */
}
/***********************************************************************************************************************
* Function Name: R_DMAC0_Start
* Description  : This function enables DMA0 transfer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC0_Start(void)
{
    DMAIF0 = 0U; /* clear INTDMA0 interrupt flag */
    DMAMK0 = 0U; /* enable INTDMA0 interrupt */
    DEN0 = 1U;
    DST0 = 1U;
}
/***********************************************************************************************************************
* Function Name: R_DMAC0_Stop
* Description  : This function disables DMA0 transfer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC0_Stop(void)
{
    if (DST0 != 0U)
    {
        DST0 = 0U;
    }
    
    NOP();
    NOP();
    DEN0 = 0U; /* disable DMA0 operation */
    DMAMK0 = 1U; /* disable INTDMA0 interrupt */
    DMAIF0 = 0U; /* clear INTDMA0 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: R_DMAC0_Set_SoftwareTriggerOn
* Description  : This function sets DMA0 software trigger on.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC0_Set_SoftwareTriggerOn(void)
{
    STG0 = 1U; /* start DMA0 software trigger */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
