// Sound.h
// Runs on TM4C123 or LM4F120
// Prototypes for basic functions to play sounds from the
// original Space Invaders.
// Jonathan Valvano
// November 17, 2014

extern int menuSelect_flag;
extern int explosion_flag;
extern int vroom_flag;
extern int menu_flag;
extern int type_flag;
void Delay1ms2(int count);
void Sound_Init(void);
//void SysTick_Handler(void);
void sound_play(void);

