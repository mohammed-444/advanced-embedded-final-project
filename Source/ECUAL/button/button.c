 /******************************************************************************
 *
 * Module: button
 *
 * File Name: button.c
 *
 * Description: Header file for the AVR button driver
 *
 * Author: Mohamed Alaa
 *
 *******************************************************************************/
#include "button.h"

/*
 * Description :
 * Setup the direction of the required button to  input.
 * Setup the pull up or tri state
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void button_init(uint8 button_id,BUTTON_DefualtInputType DefualtInput){


	GPIO_setupPinDirection( button_lookup_table[button_id].port_num,  button_lookup_table[button_id].pin_num, PIN_INPUT);

	if(DefualtInput == PULL_UP){
		GPIO_writePin( button_lookup_table[button_id].port_num,  button_lookup_table[button_id].pin_num, LOGIC_HIGH);
	}
	else
	{
		GPIO_writePin( button_lookup_table[button_id].port_num,  button_lookup_table[button_id].pin_num, LOGIC_LOW);
	}
}


/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 read_button(uint8 button_id){

	uint8 pin_value = LOGIC_LOW;

	pin_value = GPIO_readPin( button_lookup_table[button_id].port_num,  button_lookup_table[button_id].pin_num);

	return pin_value;

}




