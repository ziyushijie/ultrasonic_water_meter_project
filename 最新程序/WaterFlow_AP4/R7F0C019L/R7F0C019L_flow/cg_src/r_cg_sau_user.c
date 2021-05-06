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
* File Name    : r_cg_sau_user.c
* Version      : Applilet4 for R7F0C019 V1.00.02.01 [30 Nov 2017]
* Device(s)    : R7F0C019L
* Tool-Chain   : CCRL
* Description  : This file implements device driver for SAU module.
* Creation Date: 2021/5/5
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_sau.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_uart1_interrupt_send(vect=INTST1)
#pragma interrupt r_uart1_interrupt_receive(vect=INTSR1)
#pragma interrupt r_uart1_interrupt_error(vect=INTSRE1)
#pragma interrupt r_csi00_interrupt(vect=INTCSI00)
#pragma interrupt r_uart2_interrupt_send(vect=INTST2)
#pragma interrupt r_uart2_interrupt_receive(vect=INTSR2)
#pragma interrupt r_uart2_interrupt_error(vect=INTSRE2)
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t * gp_uart1_tx_address;         /* uart1 send buffer address */
extern volatile uint16_t  g_uart1_tx_count;            /* uart1 send data number */
extern volatile uint8_t * gp_uart1_rx_address;         /* uart1 receive buffer address */
extern volatile uint16_t  g_uart1_rx_count;            /* uart1 receive data number */
extern volatile uint16_t  g_uart1_rx_length;           /* uart1 receive data length */
extern volatile uint8_t * gp_csi00_rx_address;         /* csi00 receive buffer address */
extern volatile uint16_t  g_csi00_rx_length;           /* csi00 receive data length */
extern volatile uint16_t  g_csi00_rx_count;            /* csi00 receive data count */
extern volatile uint8_t * gp_csi00_tx_address;         /* csi00 send buffer address */
extern volatile uint16_t  g_csi00_send_length;         /* csi00 send data length */
extern volatile uint16_t  g_csi00_tx_count;            /* csi00 send data count */
extern volatile uint8_t * gp_uart2_tx_address;         /* uart2 send buffer address */
extern volatile uint16_t  g_uart2_tx_count;            /* uart2 send data number */
extern volatile uint8_t * gp_uart2_rx_address;         /* uart2 receive buffer address */
extern volatile uint16_t  g_uart2_rx_count;            /* uart2 receive data number */
extern volatile uint16_t  g_uart2_rx_length;           /* uart2 receive data length */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_uart1_interrupt_receive
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_uart1_interrupt_receive(void)
{
    uint8_t rx_data;
    
    rx_data = RXD1;

    if (g_uart1_rx_length > g_uart1_rx_count)
    {
        *gp_uart1_rx_address = rx_data;
        gp_uart1_rx_address++;
        g_uart1_rx_count++;

        if (g_uart1_rx_length == g_uart1_rx_count)
        {
            r_uart1_callback_receiveend();
        }
    }
    else
    {
        r_uart1_callback_softwareoverrun(rx_data);
    }
}
/***********************************************************************************************************************
* Function Name: r_uart1_interrupt_error
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_uart1_interrupt_error(void)
{
    uint8_t err_type;

    *gp_uart1_rx_address = RXD1;
    err_type = (uint8_t)(SSR03 & 0x0007U);
    SIR03 = (uint16_t)err_type;
    r_uart1_callback_error(err_type);
}
/***********************************************************************************************************************
* Function Name: r_uart1_interrupt_send
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_uart1_interrupt_send(void)
{
    if (g_uart1_tx_count > 0U)
    {
        TXD1 = *gp_uart1_tx_address;
        gp_uart1_tx_address++;
        g_uart1_tx_count--;
    }
    else
    {
        r_uart1_callback_sendend();
    }
}
/***********************************************************************************************************************
* Function Name: r_uart1_callback_receiveend
* Description  : This function is a callback function when UART1 finishes reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_uart1_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_uart1_callback_softwareoverrun
* Description  : This function is a callback function when UART1 receives an overflow data.
* Arguments    : rx_data -
*                    receive data
* Return Value : None
***********************************************************************************************************************/
static void r_uart1_callback_softwareoverrun(uint16_t rx_data)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_uart1_callback_sendend
* Description  : This function is a callback function when UART1 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_uart1_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_uart1_callback_error
* Description  : This function is a callback function when UART1 reception error occurs.
* Arguments    : err_type -
*                    error type value
* Return Value : None
***********************************************************************************************************************/
static void r_uart1_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_csi00_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_csi00_interrupt(void)
{
    uint8_t err_type;
    volatile uint8_t sio_dummy;

    err_type = (uint8_t)(SSR00 & _0001_SAU_OVERRUN_ERROR);
    SIR00 = (uint16_t)err_type;

    if (1U == err_type)
    {
        r_csi00_callback_error(err_type);    /* overrun error occurs */
    }
    else
    {
        if (g_csi00_tx_count > 0U)
        {
            if (0U != gp_csi00_rx_address)
            {
                *gp_csi00_rx_address = SIO00;
                gp_csi00_rx_address++;
            }
            else
            {
                sio_dummy = SIO00;
            }

            if (0U != gp_csi00_tx_address)
            {
                SIO00 = *gp_csi00_tx_address;
                gp_csi00_tx_address++;
            }
            else
            {
                SIO00 = 0xFFU;
            }

            g_csi00_tx_count--;
        }
        else 
        {
            if (0U == g_csi00_tx_count)
            {
                if (0U != gp_csi00_rx_address)
                {
                    *gp_csi00_rx_address = SIO00;
                }
                else
                {
                    sio_dummy = SIO00;
                }
            }

            r_csi00_callback_sendend();    /* complete send */
            r_csi00_callback_receiveend();    /* complete receive */
        }
    }
}
/***********************************************************************************************************************
* Function Name: r_csi00_callback_receiveend
* Description  : This function is a callback function when CSI00 finishes reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_csi00_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_csi00_callback_error
* Description  : This function is a callback function when CSI00 reception error occurs.
* Arguments    : err_type -
*                    error type value
* Return Value : None
***********************************************************************************************************************/
static void r_csi00_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_csi00_callback_sendend
* Description  : This function is a callback function when CSI00 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_csi00_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_uart2_interrupt_receive
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_uart2_interrupt_receive(void)
{
    uint8_t rx_data;
    
    rx_data = RXD2;

    if (g_uart2_rx_length > g_uart2_rx_count)
    {
        *gp_uart2_rx_address = rx_data;
        gp_uart2_rx_address++;
        g_uart2_rx_count++;

        if (g_uart2_rx_length == g_uart2_rx_count)
        {
            r_uart2_callback_receiveend();
        }
    }
    else
    {
        r_uart2_callback_softwareoverrun(rx_data);
    }
}
/***********************************************************************************************************************
* Function Name: r_uart2_interrupt_error
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_uart2_interrupt_error(void)
{
    uint8_t err_type;

    *gp_uart2_rx_address = RXD2;
    err_type = (uint8_t)(SSR11 & 0x0007U);
    SIR11 = (uint16_t)err_type;
    r_uart2_callback_error(err_type);
}
/***********************************************************************************************************************
* Function Name: r_uart2_interrupt_send
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_uart2_interrupt_send(void)
{
    if (g_uart2_tx_count > 0U)
    {
        TXD2 = *gp_uart2_tx_address;
        gp_uart2_tx_address++;
        g_uart2_tx_count--;
    }
    else
    {
        r_uart2_callback_sendend();
    }
}
/***********************************************************************************************************************
* Function Name: r_uart2_callback_receiveend
* Description  : This function is a callback function when UART2 finishes reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_uart2_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_uart2_callback_softwareoverrun
* Description  : This function is a callback function when UART2 receives an overflow data.
* Arguments    : rx_data -
*                    receive data
* Return Value : None
***********************************************************************************************************************/
static void r_uart2_callback_softwareoverrun(uint16_t rx_data)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_uart2_callback_sendend
* Description  : This function is a callback function when UART2 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_uart2_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_uart2_callback_error
* Description  : This function is a callback function when UART2 reception error occurs.
* Arguments    : err_type -
*                    error type value
* Return Value : None
***********************************************************************************************************************/
static void r_uart2_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
