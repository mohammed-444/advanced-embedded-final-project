 /******************************************************************************
 *
 * Module: pwm
 *
 * File Name: pwm.c
 *
 * Description: to generate analog signal
 *
 * Author: Mohammed Alaa
 *
 *******************************************************************************/
#include "avr/io.h"
#include "avr/iom323.h"
#include "pwm.h"


/************************************************************************************
* Service Name: PWM_Timer0_Start
* Sync/Async: Synchronous
* Parameters Non
* Parameters (input): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the PWM for timer0 Driver module.
************************************************************************************/
void PWM_Timer0_Start(){
	/*
	 * FOC0=0 PWM MODE
	 * PWM2 & CTC2 =1 FAST PWM
	 * COM01 =1 NON INVERTING MODE
	 * */
	TCCR0 = (1<<PWM0)|(1<<CTC0)|(1<<COM01);

	/*mask the first 3 bit and make them 0*/
	TCCR0 = TCCR0 & (0xFF<<PRESCALER_INTERVAL_SIZE);
	/*putting  the new value for the first 3 bits*/
	TCCR0 = TCCR0 |(TIMER_0_PRESCALER_VALUE);

	/*write the compare value to decide the duty cycle*/
	OCR0 = (uint8) (((float32) TIMER_0_DUTY_CYCLE * 255) / (float32)100);

}


/************************************************************************************
* Service Name: PWM_Timer2_Start
* Sync/Async: Synchronous
* Parameters Non
* Parameters (input): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the PWM for timer2 Driver module.
************************************************************************************/
void PWM_Timer2_Start(){

	/*
	 * FOC0=0 PWM MODE
	 * PWM2 & CTC2 =1 FAST PWM
	 * COM21 =1 NON INVERTING MODE
	 * */
	TCCR2 = (1<<PWM2)|(1<<CTC2)|(1<<COM21);
	/*mask the first 3 bit and make them 0*/
	TCCR2 = TCCR2 & (0xFF<<PRESCALER_INTERVAL_SIZE);
	/*putting  the new value for the first 3 bits*/
	TCCR2 = TCCR2 |(TIMER_2_PRESCALER_VALUE);


	/*write the compare value to decide the duty cycle*/
	OCR2 = (uint8) (((float32) TIMER_2_DUTY_CYCLE * 255) / (float32)100);

}
/************************************************************************************
* Service Name: PWM_Timer0_Stop
* Sync/Async: Synchronous
* Parameters Non
* Parameters (input): None
* Parameters (out): None
* Return value: None
* Description: Function to stop the PWM for timer0 Driver module.
************************************************************************************/
void PWM_Timer0_Stop()
{
	/*mask the first 3 bit and make them 0 which mean no clock*/
	TCCR0 = 0;
}

/************************************************************************************
* Service Name: PWM_Timer2_Stop
* Sync/Async: Synchronous
* Parameters Non
* Parameters (input): None
* Parameters (out): None
* Return value: None
* Description: Function to stop the PWM for timer2 Driver module.
************************************************************************************/
void PWM_Timer2_Stop()
{
	/*mask the first 3 bit and make them 0 which mean no clock*/
	TCCR2 = 0;
}
