 /******************************************************************************
 *
 * Module: LED
 *
 * File Name: LED.C
 *
 * Description: Header file for the AVR LED driver
 *
 * Author: Mohammed Alaa
 *
 *******************************************************************************/
#include "led.h"

/*
 * Description :
 * turn on the led
 */


void led_on(uint8 led_id)
{
	GPIO_writePin(led_lookup_table[led_id].port_num, led_lookup_table[led_id].pin_num, LOGIC_HIGH);
}

/*
 * Description :
 * turn off the led
 */
void led_off(uint8 led_id)
{
	GPIO_writePin(led_lookup_table[led_id].port_num, led_lookup_table[led_id].pin_num, LOGIC_LOW);
}


/*
 * Description :
 * toggle the led state
 */
void led_toggle(uint8 led_id)
{
	GPIO_togglePin(led_lookup_table[led_id].port_num, led_lookup_table[led_id].pin_num);
}
