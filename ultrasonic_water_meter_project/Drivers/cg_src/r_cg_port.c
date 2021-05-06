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
* File Name    : r_cg_port.c
* Version      : Applilet4 for R7F0C019 V1.00.02.01 [30 Nov 2017]
* Device(s)    : R7F0C019L
* Tool-Chain   : CCRL
* Description  : This file implements device driver for Port module.
* Creation Date: 2021/5/4
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
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
* Function Name: R_PORT_Create
* Description  : This function initializes the Port I/O.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PORT_Create(void)
{
	PFSEG0 = _80_PFSEG07_SEG | _40_PFSEG06_SEG | _30_PFSEG0_DEFAULT;
	PFSEG1 = _10_PFSEG12_SEG | _08_PFSEG11_SEG | _01_PFSEG08_SEG | _E6_PFSEG1_DEFAULT;
	PFSEG2 = _80_PFSEG23_SEG | _40_PFSEG22_SEG | _20_PFSEG21_SEG | _10_PFSEG20_SEG | _08_PFSEG19_SEG |
		_04_PFSEG18_SEG | _02_PFSEG17_SEG | _01_PFSEG16_SEG;
	PFSEG3 = _40_PFSEG29_SEG | _BB_PFSEG3_DEFAULT | _00_PFDEG_PORT;
	PFSEG4 = _80_PFSEG38_SEG | _40_PFSEG37_SEG | _20_PFSEG36_SEG | _10_PFSEG35_SEG | _08_PFSEG34_SEG |
		_04_PFSEG33_SEG | _03_PFSEG4_DEFAULT;
	PFSEG5 = _00_PFSEG46_PORT | _40_PFSEG45_SEG | _20_PFSEG44_SEG | _10_PFSEG43_SEG | _08_PFSEG42_SEG |
		_04_PFSEG41_SEG | _00_PFSEG40_PORT | _00_PFSEG39_PORT;
	PFSEG6 = _08_PFSEG50_SEG | _04_PFSEG49_SEG | _02_PFSEG48_SEG | _01_PFSEG47_SEG;
	ISCLCD = _02_ISCVL3_VALID;
	P1 = _00_Pn4_OUTPUT_0 | _00_Pn5_OUTPUT_0;
	P4 = _10_Pn4_OUTPUT_1 | _20_Pn5_OUTPUT_1;
	P12 = _00_Pn7_OUTPUT_0;
	PU0 = _08_PUn3_PULLUP_ON;
	PU4 = _01_PUn0_PULLUP_ON;
	PM1 = _01_PMn0_NOT_USE | _02_PMn1_NOT_USE | _04_PMn2_NOT_USE | _08_PMn3_NOT_USE | _00_PMn4_MODE_OUTPUT |
		_00_PMn5_MODE_OUTPUT | _40_PMn6_NOT_USE | _80_PMn7_NOT_USE;
	PM4 = _01_PMn0_NOT_USE | _04_PMn2_NOT_USE | _08_PMn3_NOT_USE | _00_PMn4_MODE_OUTPUT | _00_PMn5_MODE_OUTPUT |
		_C2_PM4_DEFAULT;
	PM12 = _20_PMn5_NOT_USE | _40_PMn6_NOT_USE | _00_PMn7_MODE_OUTPUT | _1F_PM12_DEFAULT;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
