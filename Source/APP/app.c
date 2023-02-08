 /******************************************************************************
 *
 * Layer: app
 *
 * File Name: app.c
 *
 * Description: the main application component
 *
 * Author: Mohammed Alaa
 *
 *******************************************************************************/


/*******************************************************************************
 *                                  Include                                    *
 *******************************************************************************/
#include "app.h"

/*******************************************************************************
 *                             Global variable                                 *
 *******************************************************************************/

/*shared resource with external interrupt to know the hazard button state*/
uint8 hazard_isPressed = LOGIC_LOW;

/* handler for every task in RTOS if needed later*/
TaskHandle_t task0ptr;
TaskHandle_t task1ptr;
TaskHandle_t task2ptr;
TaskHandle_t task3ptr;
TaskHandle_t task4ptr;

/* event group handler to store the flags value and control the other task execution state*/
EventGroupHandle_t xEventGroup;

/*******************************************************************************
 *                       function implementation                               *
 *******************************************************************************/



/****************************************************************
 *                             task0                            *
 ***************************************************************/

/*the observer and the brain of the system it check button state and rise flag of the event group variable
 * depend of the conditions the flags unblock other tasks*/

void Task0(void *pvParameters)
{
	/****************************************************************
	 *                     local variable                         *
	 ***************************************************************/

	/*store the left led state ,it its on if the two consequcitive read is equal INDICATOR_ACTIVATION*/
	uint8 left_flag = LOGIC_LOW;
	/*store the right led state, it its on if the two consequcitive read is equal INDICATOR_ACTIVATION*/
	uint8 right_flag = LOGIC_LOW;
	/*array to store the past read and present read of button to do some condition */
	uint8 btn_ingit_state[NUM_OF_STATE] = {LOGIC_HIGH , LOGIC_HIGH};
	uint8 btn_left_state[NUM_OF_STATE] = {LOGIC_HIGH , LOGIC_HIGH};
	uint8 btn_right_state[NUM_OF_STATE] = {LOGIC_HIGH , LOGIC_HIGH};



	/*super loop*/
	while(1)
	{
		/*read the current state of the button and store it on variable*/
		btn_ingit_state[PRESENT_STATE] = read_button(IGNITION_BUTTON_ID);
		btn_left_state[PRESENT_STATE] = read_button(LEFT_INDEICATOR_ID);
		btn_right_state[PRESENT_STATE] = read_button(RIGHT_INDEICATOR_ID);


		/*check the past state and present state of the ignition button if it active or not */
		if( (btn_ingit_state[PRESENT_STATE] == IGNITION_CTIVATION) && (btn_ingit_state[PAST_STATE] == IGNITION_CTIVATION) )
		{
			/*if active set the ignition button flag in the event group to enable task 2,3,4
			 * and clear no ignition flag in the event group*/
			xEventGroupSetBits(xEventGroup,  BIT(IGNITION_FLAG));
			xEventGroupClearBits(xEventGroup,  BIT(NO_IGNITION_FLAG));

		}
		else
		{
			/*if not active clear the ignition button flag in the event group to disable task 2,3,4
			 * and set no ignition flag in the event group to enable task1*/
			xEventGroupClearBits(xEventGroup,  BIT(IGNITION_FLAG));
			xEventGroupSetBits(xEventGroup,  BIT(NO_IGNITION_FLAG));
			/*if the ignition button is not on ,clear the hazard state so it do not keep the history of the button when the ignition is on again*/
			hazard_isPressed = LOGIC_LOW;

		}


		/*check the past state and present state of the left button if it active or not */
		if( (btn_left_state[PRESENT_STATE] == INDICATOR_ACTIVATION) && (btn_left_state[PAST_STATE] == INDICATOR_ACTIVATION) )
		{
			/*if active set the left button flag in the event group to enable task2*/
			xEventGroupSetBits(xEventGroup,  BIT(LEFT_FLAG));
			left_flag = LOGIC_HIGH;
		}
		else
		{
			/*if not active clear the left button flag in the event group to disable task2*/
			xEventGroupClearBits(xEventGroup,  BIT(LEFT_FLAG));
			left_flag = LOGIC_LOW;
		}



		/*check the past state and present state of the right button if it active or not */
		if( (btn_right_state[PRESENT_STATE] == INDICATOR_ACTIVATION) && (btn_right_state[PAST_STATE] == INDICATOR_ACTIVATION) )
		{
			/*if active set the right button flag in the event group to enable task3*/
			xEventGroupSetBits(xEventGroup,  BIT(RIGHT_FLAG));
			right_flag = LOGIC_HIGH;
		}
		else
		{
			/*if not active clear the right button flag in the event group to disable task3*/
			xEventGroupClearBits(xEventGroup,  BIT(RIGHT_FLAG));
			right_flag = LOGIC_LOW;
		}



		/*check if the to consequse read is not active in both button left and right*/
		 if( (right_flag == LOGIC_LOW)   &&    ( left_flag == LOGIC_LOW) &&  (hazard_isPressed == LOGIC_LOW))
		{
			 /* if the condition is true set the idle flag to enable task1 */
			xEventGroupSetBits(xEventGroup,  BIT(IDLE_FLAG));
		}
		else
		{
			/* if the condition is false set the idle flag to disable task1 */
			xEventGroupClearBits(xEventGroup,  BIT(IDLE_FLAG));
		}



		 /*check if the hazard button is pressed */
		if (hazard_isPressed == LOGIC_HIGH)
		{
			/*if true set ALL_LED_IS_ON_FLAG to enable task4*/
			xEventGroupSetBits(xEventGroup,  BIT(ALL_LED_IS_ON_FLAG));
			/*if true clear NOT_ALL_LED_IS_ON_FLAG to disable task 2,3*/
			xEventGroupClearBits(xEventGroup,  BIT(NOT_ALL_LED_IS_ON_FLAG));

		}
		else
		{
			/*if false clear ALL_LED_IS_ON_FLAG to disable task4*/
			xEventGroupClearBits(xEventGroup,  BIT(ALL_LED_IS_ON_FLAG));
			/*if false set NOT_ALL_LED_IS_ON_FLAG to enable task 2,3*/
			xEventGroupSetBits(xEventGroup,  BIT(NOT_ALL_LED_IS_ON_FLAG));
		}


		/*after the task end store the present state to use it as past state in the next round*/
		btn_ingit_state[PAST_STATE] = btn_ingit_state[PRESENT_STATE];
		btn_left_state[PAST_STATE] = btn_left_state[PRESENT_STATE];
		btn_right_state[PAST_STATE] = btn_right_state[PRESENT_STATE];

		/*the time to block the task 50ms */
		vTaskDelay(BUTTON_SIGNAL_SET_TIME);
	}
}


/****************************************************************
 *                             task1                            *
 ***************************************************************/

/*idle task which mean no led is on all it does is to turn off all leds*/

void Task1(void *pvParameters)
{
	/*super loop*/
	while(1)
	{
		/************************************************************************************
		* Parameters : the event group variable
		* Parameters : the bit position to wait on
		* Parameters : to clear the flags when the function return
		* Parameters : and logic (true)   , or logic (false)
		* Return value: the event group variable
		* Description: wait on the specified flags to set to run the task.
		************************************************************************************/
		xEventGroupWaitBits( xEventGroup , BIT(IDLE_FLAG) | BIT(NO_IGNITION_FLAG) , pdFALSE , pdFALSE ,  portMAX_DELAY );
		/*turn off all leds*/
		PWM_Timer0_Stop();
		PWM_Timer2_Stop();
		/*the time to block the task 100ms*/
		vTaskDelay(FASTEST_PRESS);

	}
}
/****************************************************************
 *                             task2                            *
 ***************************************************************/
void Task2(void *pvParameters)
{
	/*local variable to toggle the led*/
	uint8 local_flag = LOGIC_LOW;
	while(1)
	{
		/************************************************************************************
		* Parameters : the event group variable
		* Parameters : the bit position to wait on
		* Parameters : to clear the flags when the function return
		* Parameters : and logic (true)   , or logic (false)
		* Return value: the event group variable
		* Description: wait on the specified flags to set to run the task.
		************************************************************************************/
		xEventGroupWaitBits(xEventGroup, BIT(LEFT_FLAG)|BIT(IGNITION_FLAG)|BIT(NOT_ALL_LED_IS_ON_FLAG) , pdFALSE, pdTRUE , portMAX_DELAY);


		/*turn of the right led*/
		PWM_Timer0_Stop();

		/*the code below used to toggle the led*/
		if(local_flag == LOGIC_LOW)
		{

			PWM_Timer2_Start();
			local_flag = LOGIC_HIGH;
		}
		else
		{

			PWM_Timer2_Stop();
			local_flag = LOGIC_LOW;
		}

		/*the time to block the task 500ms*/
		vTaskDelay(LED_BLINKING_TIME);

	}
}
/****************************************************************
 *                             task3                            *
 ***************************************************************/
void Task3(void *pvParameters)
{
	/*local variable to toggle the led*/
	uint8 local_flag = LOGIC_LOW;
	while(1)
	{
		/************************************************************************************
		* Parameters : the event group variable
		* Parameters : the bit position to wait on
		* Parameters : to clear the flags when the function return
		* Parameters : and logic (true)   , or logic (false)
		* Return value: the event group variable
		* Description: wait on the specified flags to set to run the task.
		************************************************************************************/
		xEventGroupWaitBits( xEventGroup , BIT(RIGHT_FLAG)|BIT(IGNITION_FLAG)|BIT(NOT_ALL_LED_IS_ON_FLAG) , pdFALSE , pdTRUE , portMAX_DELAY);


		/*turn of the left led*/
		PWM_Timer2_Stop();

		/*the code below used to toggle the led*/
		if(local_flag == LOGIC_LOW)
		{

			PWM_Timer0_Start();
			local_flag = LOGIC_HIGH;
		}
		else
		{

			PWM_Timer0_Stop();
			local_flag = LOGIC_LOW;
		}

		/*the time to block the task 500ms*/
		vTaskDelay(LED_BLINKING_TIME);
	}
}
/****************************************************************
 *                             task4                            *
 ***************************************************************/
void Task4(void *pvParameters)
{
	/*local variable to toggle the led*/
	uint8 local_flag = LOGIC_LOW;
	while(1)
	{
		/************************************************************************************
		* Parameters : the event group variable
		* Parameters : the bit position to wait on
		* Parameters : to clear the flags when the function return
		* Parameters : and logic (true)   , or logic (false)
		* Return value: the event group variable
		* Description: wait on the specified flags to set to run the task.
		************************************************************************************/
		 xEventGroupWaitBits( xEventGroup , BIT(ALL_LED_IS_ON_FLAG)|BIT(IGNITION_FLAG) , pdFALSE, pdTRUE , portMAX_DELAY );


		 /*the code below used to toggle all the led*/
		if(local_flag == LOGIC_LOW)
		{
			PWM_Timer2_Start();
			PWM_Timer0_Start();
			local_flag = LOGIC_HIGH;
		}
		else
		{

			PWM_Timer2_Stop();
			PWM_Timer0_Stop();
			local_flag = LOGIC_LOW;
		}

		/*the time to block the task 500ms*/
		vTaskDelay(LED_BLINKING_TIME);

	}
}




/****************************************************************
 *              interrupt implementation                        *
 ***************************************************************/

/*toggle the state with every interrupt*/
ISR(INT0_vect)
{
	if(hazard_isPressed == LOGIC_HIGH)
	{
		hazard_isPressed = LOGIC_LOW;
	}
	else
	{
		hazard_isPressed = LOGIC_HIGH;
	}
}
