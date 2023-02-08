/******************************************
* Module: EXT_INTERRUPT
*
* File Name: EXT_INTERRUPT.c
*
* Description: source file for AVR external interrupt
*
* Author: Mohammed Alaa
*
******************************************/

#include "EXT_INTTERUPT.h"
#include "avr/io.h"


void GLOBAL_INTERRUPT_ENABLE(void)
{
	sei();
}

void GLOBAL_INTERRUPT_DISABLE(void)
{
	cli();
}

void INT0_init( EXT_triggerType triggerType)
{

	MCUCR = (MCUCR & 0xFC) | triggerType;/*set type of trigger*/
	SET_BIT(GICR ,6); /*enable INT0*/
}



void INT0_deInit(void)
{
	CLEAR_BIT(GICR ,6);
}

