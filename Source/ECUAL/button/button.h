 /******************************************************************************
 *
 * Module: button
 *
 * File Name: button.h
 *
 * Description: Header file for the AVR button driver
 *
 * Author: Mohammed Alaa
 *
 *******************************************************************************/
#ifndef _BUTTON_H
#define _BUTTON_H

#include "../../MCAL/gpio/gpio.h"
#include "button_cfg.h"


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	TRI_STATE,PULL_UP
}BUTTON_DefualtInputType;

typedef struct
{
	uint8 port_num;
	uint8 pin_num;
}BUTTON_config;

/*******************************************************************************
 *                               Extern Variable                            	*
 *******************************************************************************/
/*from the id we can get the port and pin num*/
extern const BUTTON_config button_lookup_table[NUM_OF_BUTTON] ;
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Setup the direction of the required button to  input.
 * Setup the pull up or tri state
 * If the input port number or pin number are not correct, The function will not handle the request.
 */

/*if you used gpio_init() you do not need to use this function*/
void button_init(uint8 button_id,BUTTON_DefualtInputType DefualtInput);

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 read_button(uint8 button_id);


#endif
