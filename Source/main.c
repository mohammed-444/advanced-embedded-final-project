#include "APP/app.h"

int main(int argc, char **argv);




int main(int argc, char **argv)
{

	GPIO_Init();
	GLOBAL_INTERRUPT_ENABLE();
	INT0_init(RISING_EDGE_TRIGGER);

	xEventGroup = xEventGroupCreate();

	xTaskCreate(Task0 , "observer" , configMINIMAL_STACK_SIZE,NULL ,  2 , &task0ptr);
	xTaskCreate(Task1 , "idle state" , configMINIMAL_STACK_SIZE,NULL ,  1 , &task1ptr);
	xTaskCreate(Task2 , "left led" , configMINIMAL_STACK_SIZE,NULL ,  1 , &task2ptr);
	xTaskCreate(Task3 , "right led" , configMINIMAL_STACK_SIZE,NULL ,  1 , &task3ptr);
	xTaskCreate(Task4 , "all led is on" , configMINIMAL_STACK_SIZE,NULL ,  1 , &task4ptr);

	vTaskStartScheduler();



	return 0;
}
