#ifndef __TC47_H__
#define __TC47_H__
#include <stdint.h>

#define TEMPRATURE_SENSOR_ADDRESS2 0b10011010

uint16_t getCurrentTemprature2(void);
void readCurrentTemprature2(void);

#endif
