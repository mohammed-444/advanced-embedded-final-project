/******************************************
* Module: EXT_INTERRUPT
*
* File Name: EXT_INTERRUPT.h
*
* Description: header file for AVR external interrupt
*
* Author: Mohammed Alaa
*
******************************************/



#ifndef EXT_INTTERUPT_H_
#define EXT_INTTERUPT_H_

#include "../../common_macros.h"
#include "../../std_types.h"
#include "../gpio/gpio.h"


 /*******************************************************************************
 *                              Types Definition                            *
 *******************************************************************************/
 typedef enum
 {
	 LOW_LEVEL_TRIGGER,
	 ANY_LOGIC_CHANGE_TRIGGER,
	 FALLING_EDGE_TRIGGER,
	 RISING_EDGE_TRIGGER
 }EXT_triggerType;



/* Assembly function to Enable Global Interrupt*/
#define sei() __asm__ __volatile__ ("sei" ::: "memory");

/* Assembly function to Disable Global Interrupt*/
#define cli() __asm__ __volatile__ ("cli" ::: "memory");

 /*******************************************************************************
 *                              Functions Prototypes                            *
 *******************************************************************************/
 
/*
* Description:
* call assembly function to enable global interrupt
*/
void GLOBAL_INTERRUPT_ENABLE(void);

/*
* Description:
* call assembly function to disable global interrupt
*/
void GLOBAL_INTERRUPT_DISABLE(void);
 
/*
* Description:
* set type of trigger first then enable EXT interrupt 0
* set pin as input or input pulled up
* @arguement  
* triggerType : conatain type of trigger will make interrupt
* direction : use to make this pin input pin or input pin with internal pull up register
*/
void INT0_init( EXT_triggerType triggerType);


/*
* Description:
* disable EXT interrupt 0
*/
void INT0_deInit(void);


#endif /* EXT_INTTERUPT_H_ */
