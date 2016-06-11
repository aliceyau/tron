/* 
Software holds all port initialization routines

Program by Alice Yau (yau.alice1@utexas.edu) & Justin DuPont (justindpnt@gmail.com)
Created: April 2016 for EE319K: Intro to Embedded Systems Course 
Instructor: Yerraballi 
Last Modified: June 9th, 2016
Runs on LM4F120/TM4C123

*/
#include <stdint.h>
	#include "tm4c123gh6pm.h"	
	#include "ST7735.h"
	#include "Random.h"
	#include "TExaS.h"
	#include "ADC.h"
	#include "MainMenu.h"
	#include "Timer1.h"
	#include "Port_Init.h"
void EnableInterrupts(void);

void PortB_Init(void) {
	volatile uint32_t delayB;          			 
	SYSCTL_RCGCGPIO_R |= 0x00000002;			 		// Turn on port B 
	delayB = SYSCTL_RCGCGPIO_R;            
	GPIO_PORTB_DIR_R 			&= ~0x1F;						// PB0-4 are inputs for controller.
	GPIO_PORTB_DEN_R 			|= 0x1F;						
	GPIO_PORTB_AFSEL_R 		&= ~0x1F;						
}
void PortC_Init(void) {
	volatile uint32_t delayC;           
	SYSCTL_RCGCGPIO_R |= 0x00000004;			    // Turn on port C
	delayC = SYSCTL_RCGCGPIO_R;           
	GPIO_PORTC_DIR_R 			&= ~0xF0;						// PC5-8 are inputs for controller.
	GPIO_PORTC_DEN_R 			|= 0xF0;							
	GPIO_PORTC_AFSEL_R 		&= ~0xF0;							
}
void PortF_Init(void){
	volatile uint32_t delayF;           
	SYSCTL_RCGCGPIO_R |= 0x00000020;			 		// Turn on port F
	delayF = SYSCTL_RCGCGPIO_R;            
	GPIO_PORTF_DIR_R &= 0x08;          				// PF3 input
	GPIO_PORTF_DEN_R |= 0x08; 				 
	GPIO_PORTF_AFSEL_R &= ~0x08;       
}

void PolledButtons_Init(void){             //Hardware interrupt initializations
	volatile uint32_t delayPoll;           
	SYSCTL_RCGCGPIO_R |=0x06; 
	delayPoll = SYSCTL_RCGCGPIO_R;
	delayPoll = SYSCTL_RCGCGPIO_R;
	
	GPIO_PORTB_AMSEL_R &= ~0x0F;
	GPIO_PORTB_PCTL_R &= 0x0000FFFF;
	GPIO_PORTB_DIR_R &= ~0x0F;
	GPIO_PORTB_AFSEL_R &= ~0x0F;
	GPIO_PORTB_DEN_R |= 0x0F;
	GPIO_PORTB_IS_R &= ~0x0F;
	GPIO_PORTB_IBE_R &= ~0x0F;
	GPIO_PORTB_IEV_R |= 0x0F;
	GPIO_PORTB_ICR_R = 0x0F;
	GPIO_PORTB_IM_R |= 0x0F;
	NVIC_PRI0_R = (NVIC_PRI0_R & 0xFFFF00FF)|0x00000040;    //PRIORITY 2
	
	
	GPIO_PORTC_AMSEL_R &= ~0xF0;
	GPIO_PORTC_PCTL_R &= ~0xFFFF0000;
	GPIO_PORTC_DIR_R &= ~0xF0;
	GPIO_PORTC_AFSEL_R &= ~0xF0;
	GPIO_PORTC_DEN_R |= 0xF0;
	GPIO_PORTC_IS_R &= ~0xF0;
	GPIO_PORTC_IBE_R &= ~0xF0;
	GPIO_PORTC_IEV_R |= 0xF0;
	GPIO_PORTC_ICR_R = 0xF0;
	GPIO_PORTC_IM_R |= 0xF0;
	NVIC_PRI0_R = (NVIC_PRI0_R & 0xFF00FFFF)|0x00400000;    //PRIORITY 2
	NVIC_EN0_R = 0x06;
	EnableInterrupts();
}



