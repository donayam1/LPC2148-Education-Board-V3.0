#ifndef __SPI_H__
#define __SPI_H__
#include "platform.h"
#include <stdint.h>

#define SSEL 15
#define selectLedMatrix IO0DIR |= 1<<SSEL //make the slave selct output 
												
#define releaseLedMatrix IO0DIR &= ~(1<<SSEL)

void initSPI(void);
void write_spi(uint16_t data);
#endif 
