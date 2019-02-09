/**************************************************************************
 *
 * Copyright (C) 2011 Steve Karg <skarg@users.sourceforge.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *
 * Some changes Copyright (C) 2017 BACnet Interoperability Testing Services, Inc.
 *
 *  July 1, 2017    BITS    Modifications to this file have been made in compliance
 *                          to original licensing.
 *
 *  This file contains changes made by BACnet Interoperability Testing
 *  Services, Inc. These changes are subject to the permissions,
 *  warranty terms and limitations above.
 *  
 *  For more information: info@bac-test.com
 *  
 *  For access to source code:  
 *          info@bac-test.com
 *              or      
 *          www.github.com/bacnettesting/bacnet-stack
 *
 **************************************************************************
 *
 *  Module Description:
 *
 *************************************************************************/

#include <stdint.h>
#include "timerCommon.h"
#include "led.h"
// #include "stm32f4xx_hal_gpio.h"
// #include "main.h"

static struct itimer ledTimers[MX_LED];

//static bool Rx_State;
//static bool Tx_State;
//static bool LD3_State;

void led_on(LED led)
{
    switch (led)
    {
    case RX_LED_GREEN:
        // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);   
        break;
    case TX_LED_BLUE:
        // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);   
        break;
    case OPERATING_ORANGE:
        // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET );  // Middle - Orange
        break;
    case ERROR_LED_RED:
        // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);   // Middle - Red
        break;
    case SPARE_LED_USB_RED:
        // HAL_GPIO_WritePin(GPIOD, Red_LED_by_CN5_Pin, GPIO_PIN_RESET);     // Middle - Red
        break;
    }
}

void led_off(LED led)
{
    switch (led)
    {
    case RX_LED_GREEN:
        // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);   
        break;
    case TX_LED_BLUE:
        // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);   
        break;
    case OPERATING_ORANGE:
        // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);    // Middle - Orange
        break;
    case ERROR_LED_RED:
        // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);     // Middle - Red
        break;
    case SPARE_LED_USB_RED:
        // HAL_GPIO_WritePin(GPIOD, Red_LED_by_CN5_Pin, GPIO_PIN_SET);       // Middle - Red
        break;
    }
}

///*************************************************************************
//* Description: Activate the LED
//* Returns: nothing
//* Notes: none
//**************************************************************************/
//void led_tx_on(
//    void)
//{
//    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET );   
//    timer_interval_no_expire(&Off_Delay_Timer_Tx);
//    Tx_State = true;
//}
//
///*************************************************************************
//* Description: Activate the LED
//* Returns: nothing
//* Notes: none
//**************************************************************************/
//void led_rx_on(
//    void)
//{
//    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);   
//    timer_interval_no_expire(&Off_Delay_Timer_Rx);
//    Rx_State = true;
//}
//
///*************************************************************************
//* Description: Deactivate the LED
//* Returns: nothing
//* Notes: none
//**************************************************************************/
//void led_tx_off(
//    void)
//{
//    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);   
//    timer_interval_no_expire(&Off_Delay_Timer_Tx);
//    Tx_State = false;
//}
//
///*************************************************************************
//* Description: Deactivate the LED
//* Returns: nothing
//* Notes: none
//**************************************************************************/
//void led_rx_off(
//    void)
//{
//    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);   
//    timer_interval_no_expire(&Off_Delay_Timer_Rx);
//    Rx_State = false;
//}

///*************************************************************************
//* Description: Get the state of the LED
//* Returns: true if on, false if off.
//* Notes: none
//*************************************************************************/
//bool led_rx_state(
//    void)
//{
//    return Rx_State;
//}
//
///*************************************************************************
//* Description: Get the state of the LED
//* Returns: true if on, false if off.
//* Notes: none
//*************************************************************************/
//bool led_tx_state(
//    void)
//{
//    return Tx_State;
//}
//
///*************************************************************************
//* Description: Toggle the state of the LED
//* Returns: none
//* Notes: none
//*************************************************************************/
//void led_tx_toggle(
//    void)
//{
//    if (led_tx_state()) {
//        led_tx_off();
//    } else {
//        led_tx_on();
//    }
//}

///*************************************************************************
//* Description: Toggle the state of the LED
//* Returns: none
//* Notes: none
//*************************************************************************/
//void led_rx_toggle(
//    void)
//{
//    if (led_rx_state()) {
//        led_rx_off();
//    } else {
//        led_rx_on();
//    }
//}

///*************************************************************************
//* Description: Delay before going off to give minimum brightness.
//* Returns: none
//* Notes: none
//*************************************************************************/
//void led_rx_off_delay(
//    uint32_t delay_ms)
//{
//    timer_interval_start(&Off_Delay_Timer_Rx, delay_ms);
//}
//
///*************************************************************************
//* Description: Delay before going off to give minimum brightness.
//* Returns: none
//* Notes: none
//*************************************************************************/
//void led_tx_off_delay(
//    uint32_t delay_ms)
//{
//    timer_interval_start(&Off_Delay_Timer_Tx, delay_ms);
//}
//
/*************************************************************************
* Description: Turn on, and delay before going off.
* Returns: none
* Notes: none
*************************************************************************/
void led_on_interval(LED led, uint16_t delay_ms)
{
    led_on(led);
//    timer_interval_start(&ledTimers[led], delay_ms);
}

void led_rx_on_interval(
    uint16_t interval_ms)
{
    led_on_interval(RX_LED_GREEN, interval_ms);
    //    led_rx_on();
    //    timer_interval_start(&Off_Delay_Timer_Rx, interval_ms);
}

void led_rx_error(
    uint16_t interval_ms)
{
    led_on_interval(ERROR_LED_RED, interval_ms);
}

void led_rx_data_frame(
    uint16_t interval_ms)
{
    led_on_interval(OPERATING_ORANGE, interval_ms);
}

/*************************************************************************
* Description: Turn on, and delay before going off.
* Returns: none
* Notes: none
*************************************************************************/
void led_tx_on_interval(
    uint16_t interval_ms)
{
    led_on_interval(TX_LED_BLUE, interval_ms);
    //    led_tx_on();
    //    timer_interval_start(&Off_Delay_Timer_Tx, interval_ms);
}

/*************************************************************************
* Description: Task for blinking LED
* Returns: none
* Notes: none
*************************************************************************/
void led_task(
    void)
{
    //for (int i = 0; i < MX_LED; i++)
    //{
    //    if (timer_interval_expired(&ledTimers[i]))
    //    {
    //        timer_interval_no_expire(&ledTimers[i]);
    //        led_off((LED) i);
    //    }
    //}
}

///*************************************************************************
//* Description: Activate the LED
//* Returns: nothing
//* Notes: none
//**************************************************************************/
//void led_ld4_on(
//    void)
//{
//    // GPIO_WriteBit(GPIOC, GPIO_Pin_8, Bit_SET);
//}
//
///*************************************************************************
//* Description: Deactivate the LED
//* Returns: nothing
//* Notes: none
//**************************************************************************/
//void led_ld4_off(
//    void)
//{
//    // GPIO_WriteBit(GPIOC, GPIO_Pin_8, Bit_RESET);
//}
//
///*************************************************************************
//* Description: Activate the LED
//* Returns: nothing
//* Notes: none
//**************************************************************************/
//void led_ld3_on(
//    void)
//{
//    // GPIO_WriteBit(GPIOC, GPIO_Pin_9, Bit_SET);
//    LD3_State = true;
//}
//
///*************************************************************************
//* Description: Deactivate the LED
//* Returns: nothing
//* Notes: none
//**************************************************************************/
//void led_ld3_off(
//    void)
//{
//    // GPIO_WriteBit(GPIOC, GPIO_Pin_9, Bit_RESET);
//    LD3_State = false;
//}
//
///*************************************************************************
//* Description: Get the state of the LED
//* Returns: true if on, false if off.
//* Notes: none
//*************************************************************************/
//bool led_ld3_state(
//    void)
//{
//    return LD3_State;
//}
//
///*************************************************************************
//* Description: Toggle the state of the LED
//* Returns: none
//* Notes: none
//*************************************************************************/
//void led_ld3_toggle(
//    void)
//{
//    if (led_ld3_state()) {
//        led_ld3_off();
//    } else {
//        led_ld3_on();
//    }
//}

/*************************************************************************
* Description: Initialize the LED hardware
* Returns: none
* Notes: none
*************************************************************************/
void led_init(
    void)
{
    //    GPIO_InitTypeDef GPIO_InitStructure;
    //
    //    GPIO_StructInit(&GPIO_InitStructure);
    //    /* Configure the Receive LED on MS/TP board */
    //    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    //    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    //    GPIO_Init(GPIOB, &GPIO_InitStructure);
    //    /* Configure the Transmit LED on MS/TP board */
    //    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    //    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    //    GPIO_Init(GPIOB, &GPIO_InitStructure);
    //    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    //    /* Configure the LD4 on Discovery board */
    //    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    //    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    //    GPIO_Init(GPIOC, &GPIO_InitStructure);
    //    /* Configure the LD3 on Discovery board */
    //    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    //    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    //    GPIO_Init(GPIOC, &GPIO_InitStructure);
    //    /* Enable the GPIO_LED Clock */
    //    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    for(int i = 0 ; i < MX_LED ; i++)
    {
        led_on_interval((LED)i, 500);
    }
    //    led_tx_on();
    //    led_rx_on();
    //    led_ld3_on();
    //    led_ld4_on();
}
