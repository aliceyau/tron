#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "TExaS.h"
#include "ADC.h"
#include "MainMenu.h"
#include "Timer1.h"
#include "Port_Init.h"
#include "Sound.h"


void DrawWalls(void);
void TwoPlayer(int);
void SysTick_Init(void);
void SysTick_Handler(void);
void choosespeed(int c2);
void GPIOPortB_Handler(void);
void GPIOPortC_Handler(void);
void Versus(void);
void Versuss(void);
void endgame(void);						//initiates end game
void DrawWalls(void);        // Draws the walls
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(uint32_t count); // time delay in 0.1 seconds
void Up(void);								// Function to go up
void Right(void);							// Function to go right
void Down(void);							// Function to go down
void Left(void);							// Function to go left
void Storearray(int x, int y);	//
void Storearrayy(int xx, int yy);
void tiegame(void);
int collisionDetection(int x, int y);
void endgame2(void);
int collisionDetectionn(int x, int y);
void howto(void);



