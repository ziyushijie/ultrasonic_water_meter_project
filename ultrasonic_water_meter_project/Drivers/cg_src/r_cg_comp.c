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
* File Name    : r_cg_comp.c
* Version      : Applilet4 for R7F0C019 V1.00.02.01 [30 Nov 2017]
* Device(s)    : R7F0C019L
* Tool-Chain   : CCRL
* Description  : This file implements device driver for COMP module.
* Creation Date: 2021/5/7
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_comp.h"
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
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_COMP_Create
* Description  : This function initializes the comparator module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_COMP_Create(void)
{
    CMPEN = 1U;   /* supply comparator clock */
    C0ENB = 0U;   /* disable comparator 0 operation */
    C1ENB = 0U;   /* disable comparator 1 operation */
    CMPMK0 = 1U;  /* disable INTCMP0 operation */
    CMPIF0 = 0U;  /* clear INTCMP0 interrupt flag */
    CMPMK1 = 1U;  /* disable INTCMP1 operation */
    CMPIF1 = 0U;  /* clear INTCMP1 interrupt flag */
    /* The reset status of ADPC is analog input, so it's unnecessary to set. */
    /* Set IVCMP0 pin */
    PMC4 |= 0x10U;
    PM4 |= 0x10U; 
    /* Set IVREF0 pin */
    PFSEG3 |= 0x04U;
    PMC4 |= 0x20U;
    PM4 |= 0x20U; 
    SPDMD = 0U;   /* low speed */
    COMPMDR = _00_COMP0_MODE_NORMAL | _00_COMP0_REF_VOLTAGE_IVREF0;
    COMPFIR = _00_COMP0_RISING_INTERRUPT | _00_COMP0_ONE_EDGE_INTERRUPT;
    COMPOCR |= _01_COMP0_INTERRPUT_ENABLE;
    /* Set INTCMP0 low priority */
    CMPPR00 = 1U;
    CMPPR10 = 1U;
}
/***********************************************************************************************************************
* Function Name: R_COMP0_Start
* Description  : This function starts the comparator 0.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_COMP0_Start(void)
{
    volatile uint16_t w_count;

    C0ENB = 1U;     /* enable comparator 0 operation */
    
    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count < COMP_WAIT_TIME; w_count++)
    {
        NOP();  
    }

    CMPIF0 = 0U;    /* clear INTCMP0 interrupt flag */
    CMPMK0 = 0U;    /* enable INTCMP0 interrupt */
}
/***********************************************************************************************************************
* Function Name: R_COMP0_Stop
* Description  : This function stops the comparator 0.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_COMP0_Stop(void)
{
    C0ENB = 0U;     /* disable comparator 0 operation */
    CMPMK0 = 1U;    /* disable INTCMP0 interrupt */
    CMPIF0 = 0U;    /* clear INTCMP0 interrupt flag */  
}


/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
