 /******************************************************************************
 *
 * Module: button
 *
 * File Name: button_PBcfg.c
 *
 * Description: Header file for the AVR button driver
 *
 * Author: Mohamed Alaa
 *
 *******************************************************************************/
#include "button.h"

/*from the id we can get the port and pin num*/
const BUTTON_config button_lookup_table[NUM_OF_BUTTON] = {

		{HAZARD_BUTTON_PORT , HAZARD_BUTTON_PIN},
		{LEFT_INDEICATOR_PORT , LEFT_INDEICATOR_PIN},
		{RIGHT_INDEICATOR_PORT , RIGHT_INDEICATOR_PIN},
		{IGNITION_BUTTON_PORT , IGNITION_BUTTON_PIN}
};
