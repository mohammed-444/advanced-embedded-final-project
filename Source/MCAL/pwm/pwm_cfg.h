 /******************************************************************************
 *
 * Module: pwm
 *
 * File Name: pwm_cfg.h
 *
 * Description: to generate analog signal
 *
 * Author: Mohammed Alaa
 *
 *******************************************************************************/
#ifndef _PWM_CONFIG_
#define _PWM_CONFIG_



/*the range of the macro from 0% to 100% for pin PD7*/
#define TIMER_2_DUTY_CYCLE	100


/*the range of the macro from 0% to 100% for pin PB3*/
#define TIMER_0_DUTY_CYCLE	100


/*--------------------------------------------------*/
#define NO_CLOCK			0x00
#define DIVIDE_BY_1			0x01
#define DIVIDE_BY_8			0x02
#define DIVIDE_BY_64		0x03
#define DIVIDE_BY_256		0x04
#define DIVIDE_BY_1024		0x05

/*choose the prescaler value from the above macros*/
#define TIMER_0_PRESCALER_VALUE		DIVIDE_BY_1

#define TIMER_2_PRESCALER_VALUE		DIVIDE_BY_1



#endif
