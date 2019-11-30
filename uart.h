
#ifndef __UART_H__
#define __UART_H__
#include <stdint.h>

void intUART0(void );
void outputdata(uint8_t data);

void startTransmission(void);
void endTransmission(void);

extern void byteRecived(uint8_t data);
extern void errorByteRecived(void);
#endif 
