/*
Software calls all initializations then calls the main menu function.

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
#include "Port_Init.h"
#include "Sound.h"
#include "Detection.h"


int main(void){
  TExaS_Init(); 									 // set system clock to 80 Mhz
  Output_Init();
	ADC_Init();                      // setup slide pot
	PortB_Init();											
	PortC_Init();
	Sound_Init();
	MainMenu();											// Print out main menu screen
	}
