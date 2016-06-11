/* DAC.c
This software configures DAC Output

TRON
By Justin DuPont (justindpnt@gmail.com) & Alice Yau (yau.alice1@utexas.edu)
Created: April 2016 for the course EE319K: Intro to Embedded Systems
Course Instructor: Yerraballi
Last Modified: June 9th, 2016

Special Thanks to Texas Instruments for their hardware, and Jonathan Valvano for the instruction and textbook.

Reference: 
"Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014

   "Embedded Systems: Introduction to Arm Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2014
	 
Runs on LM4F120/TM4C123

Free to edit or run this file.
For any questions or comments, feel free to email the creators (Emails above).

~NOTICE~
Authors have removed sound files and image files that were not originally theirs, in respect to orignal content creators
For the removed files, we've placed the comment "REPLACE" next to it and also added the sizing of the files for easy 
editing of this program. 
*/

#include <stdint.h>
#include "tm4c123gh6pm.h"
// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

// **************DAC_Init*********************
// Initialize 4-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){
	SYSCTL_RCGCGPIO_R |= 0X08;    							  //Turn on PORT D clock
	volatile uint32_t delay = SYSCTL_RCGC2_R;			 							// Wait
	
	GPIO_PORTD_AFSEL_R &= ~ 0x0F;
	GPIO_PORTD_DIR_R |= 0x0F;   									//PD0-3 are outputs 
	GPIO_PORTD_DEN_R |= 0x0F;
	
}

// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(uint32_t data){
	
	GPIO_PORTD_DATA_R = (data);										 // shift left to get data to PD
}
