 /******************************************************************************
 *
 * Module: led
 *
 * File Name: led_cfg.h
 *
 * Description: Header file for the AVR led driver
 *
 * Author: Mohammed Alaa
 *
 *******************************************************************************/

#ifndef _LED_CFG_
#define _LED_CFG_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUM_OF_PORTS           ((uint8)4)
#define NUM_OF_PINS_PER_PORT   ((uint8)8)
#define TOTAL_PINS_NUM		   ((uint8)32)
#define NUM_CHANNEL_ID	   		((uint8)4)

#define PORTA_ID               ((uint8)0)
#define PORTB_ID               ((uint8)1)
#define PORTC_ID               ((uint8)2)
#define PORTD_ID               ((uint8)3)

#define PIN0_ID                ((uint8)0)
#define PIN1_ID                ((uint8)1)
#define PIN2_ID                ((uint8)2)
#define PIN3_ID                ((uint8)3)
#define PIN4_ID                ((uint8)4)
#define PIN5_ID                ((uint8)5)
#define PIN6_ID                ((uint8)6)
#define PIN7_ID                ((uint8)7)


/*******************************************************************************
 *                                Configuration                                 *
 *******************************************************************************/
/*any change here make sure that it is logical in button_PBcfg.c especially the id*/

#define NUM_OF_LED			0


#define LED1_ID				0
#define LED1_PORT			PORTA_ID
#define LED1_PIN			PIN0_ID
/*---------------------------------------*/



#endif

