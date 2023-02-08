 /******************************************************************************
 *
 * Module: pwm
 *
 * File Name: pwm.h
 *
 * Description: to generate analog signal
 *
 * Author: Mohammed Alaa
 *
 *******************************************************************************/


#ifndef SOURCE_PWM_H_
#define SOURCE_PWM_H_

#include "../../std_types.h"
#include "../../common_macros.h"
#include "pwm_cfg.h"

/*this macro define the start position of prescalers bits and the size of the interval*/
#define PRESCALER_INTERVAL_SIZE 	3
#define PRESCALER_START_POSITION	0
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/************************************************************************************
* Service Name: PWM_Timer0_Start
* Sync/Async: Synchronous
* Parameters Non
* Parameters (input): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize and start the PWM for timer0 Driver module.
************************************************************************************/
void PWM_Timer0_Start();

/************************************************************************************
* Service Name: PWM_Timer2_Start
* Sync/Async: Synchronous
* Parameters Non
* Parameters (input): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize and start the PWM for timer2 Driver module.
************************************************************************************/
void PWM_Timer2_Start();
/************************************************************************************
* Service Name: PWM_Timer0_Stop
* Sync/Async: Synchronous
* Parameters Non
* Parameters (input): None
* Parameters (out): None
* Return value: None
* Description: Function to stop the PWM for timer0 Driver module.
************************************************************************************/
void PWM_Timer0_Stop();

/************************************************************************************
* Service Name: PWM_Timer2_Stop
* Sync/Async: Synchronous
* Parameters Non
* Parameters (input): None
* Parameters (out): None
* Return value: None
* Description: Function to stop the PWM for timer2 Driver module.
************************************************************************************/
void PWM_Timer2_Stop();

#endif /* SOURCE_PWM_H_ */
