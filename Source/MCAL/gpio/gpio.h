 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.h
 *
 * Description: Header file for the AVR GPIO driver
 *
 * Author: Mohamed Alaa
 *
 *******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "../../std_types.h"
#include "../../common_macros.h" /* To use the macros like SET_BIT */
#include "gpio_cfg.h"



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef uint8 GPIO_PinType;
typedef uint8 GPIO_PortType;
typedef enum
{
	PIN_INPUT=0U,
	PIN_OUTPUT=1U
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT=0U,
	PORT_OUTPUT=0xFFU
}GPIO_PortDirectionType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
	GPIO_OFF = 0U,
	GPIO_PULL_UP = 1U
}GPIO_InternalResistor;

typedef enum
{
	GPIO_PIN_LEVEL_LOW = 0U,
	GPIO_PIN_LEVEL_HIGH = 1U
}GPIO_PinLevelValue;

typedef struct{
uint8 no_of_channels;
uint8 group_ids[NUM_CHANNEL_ID];
}ChannelGroupType;

typedef struct
{
	GPIO_PortType port_num;			/* PORTA...PORTD*/
	GPIO_PinType pin_num;				/* PORT_Pin0, PORT_Pin1, ... , PORT_Pin38, PORT_Pin39*/
	GPIO_PinDirectionType direction;	/* PORT_PIN_IN, PORT_PIN_OUT 	*/
	GPIO_InternalResistor resistor;		/* OFF,PULL_UP 							*/
	GPIO_PinLevelValue initial_value;	/* GPIO_PinLevelValue,PORT_PIN_LEVEL_HIGH 			*/

}GPIO_ConfigType;

/*******************************************************************************
 *                               EXTERNAL VARIABLE                            *
 *******************************************************************************/
extern const GPIO_ConfigType GPIO_ConfigPin[TOTAL_PINS_NUM];
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * configure every pin in the gpio.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_Init(void);
/*
 *  Description :
 *  write in a group of of pin
 */
void GPIO_ChannelGroupWrite(ChannelGroupType* ChannelID ,uint8 dataPtr[]);
/*
 *  Description :
 *  read in a group of of pin
 */
void GPIO_ChannelGroupRead(ChannelGroupType* ChannelID ,uint8 dataPtr[]);
/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);
/*
 * Description :
 * Read and return the value for the required pin, then toggle the value of the pin
 */
void GPIO_togglePin(uint8 port_num, uint8 pin_num);
/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num, uint8 direction);

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value);

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num);

#endif /* GPIO_H_ */
