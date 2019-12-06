#ifndef __LM75_H__
#define __LM75_H__
#include <stdint.h>

#define TEMPRATURE_SENSOR_ADDRESS 0x90

uint16_t getCurrentTemprature(void);
void readCurrentTemprature(void);

#endif
