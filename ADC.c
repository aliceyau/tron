// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0
// Last Modified: 3/6/2015 
// Student names: Alice Yau & Justin DuPont
// Last modification date: 4/11/2016

#include <stdint.h>
#include "tm4c123gh6pm.h"

// ADC initialization function 
// Input: none
// Output: none
void ADC_Init(void){ 
	volatile uint32_t delay;
	SYSCTL_RCGCGPIO_R |= 0x00000010; 		//turn on Port E on Clock
	delay = SYSCTL_RCGCGPIO_R;						// Stabilize clock
	GPIO_PORTE_DIR_R &= ~0x04; 				//PE2 is input
	GPIO_PORTE_AFSEL_R |= 0x04; 			//ENABLE alt functions on PE2
	GPIO_PORTE_AMSEL_R |= 0x04; 			//ENABLE analog functions on PE2
	GPIO_PORTE_DEN_R &= ~ 0x04; 			//DISABLE digital functions on PE2
	SYSCTL_RCGCADC_R |= 0x01;         //Enable ADC clock: ADC0
	delay = SYSCTL_RCGCADC_R;					
	delay = SYSCTL_RCGCADC_R;
	delay = SYSCTL_RCGCADC_R;
	delay = SYSCTL_RCGCADC_R;
	
	ADC0_PC_R = 0x01;                //configure for 125k conversion speed
	ADC0_SSPRI_R = 0x0123;          	// Sequencer 3 is highest priority
	ADC0_ACTSS_R &= ~0x0008;        	// Disable sample sequencer 3.
	ADC0_EMUX_R &= ~0xF000;        	  // Seq3 is software trigger.
	ADC0_SSMUX3_R &= ~0x000F;       	// Clear SS3 field.
	ADC0_SSMUX3_R = (ADC0_SSMUX3_R&0xFFFFFFF0)+1;        // Set channel Ain1 (PE2).
  ADC0_SSCTL3_R = 0x0006;        											 // No TS0 D0, yes IE0 END0.
	ADC0_IM_R &=~0x0008;																	// Disable interrupts
	ADC0_ACTSS_R |= 0x0008;         											// Enable sample sequencer 3
}

//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
uint32_t ADC_In(void){  
	uint32_t result;
	 ADC0_PSSI_R |= 0x0008;            // 1) initiate SS3
	 while((ADC0_RIS_R&0x08)==0){};   // 2) wait for conversion done
   result = ADC0_SSFIFO3_R&0xFFF;   // 3) read result
   ADC0_ISC_R = 0x0008;             // 4) acknowledge completion
   return result;
}


