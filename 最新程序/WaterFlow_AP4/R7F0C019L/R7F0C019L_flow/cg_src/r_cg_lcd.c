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
* File Name    : r_cg_lcd.c
* Version      : Applilet4 for R7F0C019 V1.00.02.01 [30 Nov 2017]
* Device(s)    : R7F0C019L
* Tool-Chain   : CCRL
* Description  : This file implements device driver for LCD module.
* Creation Date: 2021/5/5
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_lcd.h"
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
* Function Name: R_LCD_Create
* Description  : This function initializes the LCD module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Create(void)
{
    LCDON = 0U;    /* disable LCD clock operation */
    LCDM0 = _00_LCD_DISPLAY_WAVEFORM_A | _0D_LCD_DISPLAY_MODE1;
    LCDM0 |= _00_LCD_VOLTAGE_MODE_EXTERNAL;
    /* Set segment pins */
    PU1 &= 0xF0U;
    PU2 &= 0x3FU;
    PU3 &= 0xF0U;
    PU5 &= 0x67U;
    PU7 &= 0x0EU;
    POM5 &= 0xE7U;
    PIM5 &= 0xF7U;
    PFSEG0 |= 0xB0U;
    PFSEG1 |= 0xFFU;
    PFSEG2 |= 0xFFU;
    PFSEG3 |= 0xBBU;
    PFSEG4 |= 0xFFU;
    PMC1 &= 0xF0U;
    P1 &= 0xF0U;
    PM1 &= 0xF0U;
    PMC2 &= 0x3FU;
    P2 &= 0x3FU;
    PM2 &= 0x3FU;
    P3 &= 0xF0U;
    PM3 &= 0xF0U;
    P5 &= 0x67U;
    PM5 &= 0x67U;
    P7 &= 0x0EU;
    PM7 &= 0x0EU;
    LCDM1 |= _00_LCD_DISPLAY_PATTERN_A;
    LCDC0 = _05_LCD_CLOCK_FSUB_FIL_6;
}
/***********************************************************************************************************************
* Function Name: R_LCD_Start
* Description  : This function enables the LCD display.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Start(void)
{
    LCDON = 1U;
}
/***********************************************************************************************************************
* Function Name: R_LCD_Stop
* Description  : This function disables the LCD display.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Stop(void)
{
    LCDON = 0U;
}
/***********************************************************************************************************************
* Function Name: R_LCD_Voltage_On
* Description  : This function enables voltage boost circuit or capacitor split circuit.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Voltage_On(void)
{
    SCOC = 1U;
}
/***********************************************************************************************************************
* Function Name: R_LCD_Voltage_Off
* Description  : This function disables voltage boost circuit or capacitor split circuit.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Voltage_Off(void)
{
    SCOC = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
