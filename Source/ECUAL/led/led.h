 /******************************************************************************
 *
 * Module: led
 *
 * File Name: led.h
 *
 * Description: Header file for the AVR led driver
 *
 * Author: Mohammed Alaa
 *
 *******************************************************************************/
#ifndef _LED_H_
#define _LED_H_

#include "../../MCAL/gpio/gpio.h"
#include "led_cfg.h"
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef struct
{
	uint8 port_num;
	uint8 pin_num;
}LED_config;
/*******************************************************************************
 *                               Extern Variable                            	*
 *******************************************************************************/
/*from the id we can get the port and pin num*/
extern const LED_config led_lookup_table[NUM_OF_LED];
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * turn on the led
 */


void led_on(uint8 led_id);

/*
 * Description :
 * turn off the led
 */
void led_off(uint8 led_id);


/*
 * Description :
 * toggle the led state
 */
void led_toggle(uint8 led_id);




#endif
