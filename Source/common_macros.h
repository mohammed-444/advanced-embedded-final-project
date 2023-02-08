 /******************************************************************************
 *
 * Module: Common - Macros
 *
 * File Name: Common_Macros.h
 *
 * Description: Commonly used Macros
 *
 * Author: Mohamed Alaa
 *
 *******************************************************************************/

#ifndef COMMON_MACROS
#define COMMON_MACROS

#define REG_SIZE  8			/*depend on microcontroller*/
#define MASK      0xFF
#define BIT_INTERVAL_SIZE  1
typedef unsigned char  REG_TYPE;/*depend on microcontroller*/

/* This macro write in a region without affecting the other region
* Parameters (reg): the register that will be written in
* Parameters (interval_size): the size that will be written in
* Parameters (start_position): the start position that will be written from
* Parameters (value): the value that will be written in
* */
#define WRITE_REGION(reg,interval_size,start_position,value)	reg=(((reg)&(~((MASK<<((REG_SIZE)-(interval_size)))>>((REG_SIZE)-(interval_size)-(start_position)))))\
																|((((REG_TYPE)(value))<<((REG_SIZE)-(interval_size)))>>((REG_SIZE)-(interval_size)-(start_position))))
/* This macro read a region without affecting the other region
* Parameters (reg): the register that will be read from
* Parameters (interval_size): the size that will be read from
* Parameters (start_position): the start position that will be read from
* */
#define READ_REGION(reg,interval_size,start_position)			(((reg)&((MASK<<((REG_SIZE)-(interval_size)))>>((REG_SIZE)-(interval_size)-(start_position))))>>(start_position))

/* This macro return the value after shifting the 1 n time
*/
#define BIT(n)						( 1 << (n) )
/* Turn an address to variable of type unsigned long
 * Note: Change depend on register size */
#define REG(addr)		(*((volatile REG_TYPE*)addr))

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) ((REG)|=(1<<(BIT)))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) ((REG)&=(~(1<<(BIT))))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) ((REG)^=(1<<(BIT)))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( (REG) = ((REG)>>(num)) | ((REG)<<(8-(num))) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( (REG) = ((REG)<<(num)) | ((REG)>>(8-(num))) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( (REG) & (1<<(BIT)) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !((REG) & (1<<(BIT))) )

#endif
