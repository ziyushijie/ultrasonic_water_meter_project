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
* File Name    : r_cg_lvd.h
* Version      : Applilet4 for R7F0C019 V1.00.02.01 [30 Nov 2017]
* Device(s)    : R7F0C019L
* Tool-Chain   : CCRL
* Description  : This file implements device driver for LVD module.
* Creation Date: 2021/5/4
***********************************************************************************************************************/
#ifndef LVD_H
#define LVD_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Voltage detection register (LVIM)
*/
/* LVIS register rewrite enable/disable control (LVISEN) */
#define _00_LVD_REWRITE_LVIS_DISABLE    (0x00U) /* disabling rewriting */
#define _80_LVD_REWRITE_LVIS_ENABLE     (0x80U) /* enabling rewriting */
/* LVD output mask status flag (LVIOMSK) */
#define _00_LVD_MASK_INVALIDITY         (0x00U) /* mask is invalid */
#define _02_LVD_MASK_VALIDITY           (0x02U) /* mask is valid */
/* Voltage detection flag (LVIF) */
#define _00_LVD_FLAG_OVER               (0x00U) /* VDD >= VLVD, or when LVD operation is disabled */
#define _01_LVD_FLAG_LESS               (0x01U) /* VDD < VLVD */

/*
    Voltage detection level register (LVIS)
*/
/* Operation mode of voltage detection (LVIMD) */
#define _00_LVD_MODE_INT                (0x00U) /* interrupt mode */
#define _80_LVD_MODE_RESET              (0x80U) /* reset mode */
/* LVD detection level (LVILV) */
#define _00_LVD_LEVEL_INT               (0x00U) /* high-voltage detection level (VLVDH) */
#define _01_LVD_LEVEL_RESET             (0x01U) /* low-voltage detection level (VLVDL) */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_LVD_Create(void);
void R_LVD_InterruptMode_Start(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
