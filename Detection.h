#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "TExaS.h"
#include "ADC.h"
#include "MainMenu.h"
#include "Port_Init.h"
#include "Sound.h"


struct Tail
{
	uint8_t x;												//x coordinate
	uint8_t y;												//y coordinate
};

typedef struct Tail Tail_t;

 extern Tail_t blueTail[500];
 extern  Tail_t orangeTail[500];
