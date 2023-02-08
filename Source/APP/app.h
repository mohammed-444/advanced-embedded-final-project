 /******************************************************************************
 *
 * Layer: app
 *
 * File Name: app.h
 *
 * Description: the main application component
 *
 * Author: Mohammed Alaa
 *
 *******************************************************************************/
#ifndef _APP_H
#define _APP_H
/*******************************************************************************
 *                                  Include                                    *
 *******************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "../MCAL/pwm/pwm.h"
#include "../ECUAL/button/button.h"
#include "../MCAL/EXT_INTERRUPT/EXT_INTTERUPT.h"
#include "avr/io.h"
#include "avr/interrupt.h"


/*******************************************************************************
 *                              Config macros                                  *
 *******************************************************************************/

/*the time to wait before checking on the button again*/
#define BUTTON_SIGNAL_SET_TIME			50
/*the blinking time for the led in the application*/
#define LED_BLINKING_TIME				500
/*the Time the clearing all led task(task1) it take to repeat in the application*/
#define FASTEST_PRESS					100

/*application dependent the button activation state (HIGH , LOW)*/
#define INDICATOR_ACTIVATION		LOGIC_LOW
#define IGNITION_CTIVATION			LOGIC_LOW

/*application dependent to store the previous value of the pin and present state of it */
#define NUM_OF_STATE					2
#define PRESENT_STATE					1
#define PAST_STATE						0

/*application dependent to know the flag position in event groups variable */
#define IGNITION_FLAG					0
#define IDLE_FLAG						1
#define LEFT_FLAG						2
#define RIGHT_FLAG						3
#define ALL_LED_IS_ON_FLAG				4
#define NO_IGNITION_FLAG				5
#define NOT_ALL_LED_IS_ON_FLAG			7

/*******************************************************************************
 *                             Global variable                                 *
 *******************************************************************************/
/*shared resource with external interrupt to know the hazard button state*/
extern uint8 hazard_isPressed;
/* handler for every task in RTOS if needed later*/
extern TaskHandle_t task0ptr;
extern TaskHandle_t task1ptr;
extern TaskHandle_t task2ptr;
extern TaskHandle_t task3ptr;
extern TaskHandle_t task4ptr;
/* event group handler to store the flags value and control the other task execution state*/
extern EventGroupHandle_t xEventGroup;


/*******************************************************************************
 *                          function prototype                                 *
 *******************************************************************************/
/*the observer and the brain of the system it check button state and rise flag of the event group variable
 * depend of the conditions the flags unblock other tasks*/
void Task0(void *pvParameters);
/*idle task which mean no led is on all it does is to turn off all leds*/
void Task1(void *pvParameters);
/*task that control the left led and wait on the specific event group flag to be set to unblock the task*/
void Task2(void *pvParameters);
/*task that control the right led and wait on the specific event group flag to be set to unblock the task*/
void Task3(void *pvParameters);
/*task that blink all the led  led and wait on the specific event group flag to be set to unblock the task*/
void Task4(void *pvParameters);


#endif
