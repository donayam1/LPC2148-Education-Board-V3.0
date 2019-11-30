#ifndef __LEDS_H__
#define __LEDS_H__

#include "platform.h"

#define LED1DIR IO0DIR
#define LED2DIR IO0DIR

#define LED1PIN IO0PIN
#define LED2PIN IO0PIN

#define LED1BIT 8
#define LED2BIT 9


#define LED1OUTPUT LED1DIR |=1<<LED1BIT;
#define LED2OUTPUT LED2DIR |=1<<LED2BIT;

#define TurnOnLed1 LED1PIN &= ~(1<<LED1BIT);
#define TurnOffLed1 LED1PIN |= 1<<LED1BIT;

#define TurnOnLed2 LED2PIN &= ~(1<<LED2BIT);
#define TurnOffLed2 LED2PIN |= 1<<LED2BIT;



void initLeds(void);




#endif 
