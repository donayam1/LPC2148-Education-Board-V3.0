
#include <stdint.h>
#include "platform.h"
#include "adc.h"


__irq void ADCDoneISR(void);
uint16_t adc0Res =0x24;

void initAdc(){
//  opperational,burst mode,60/4/4(3.75Mhz),AD0.1
	AD0CR= (1<<21)|(1<<16)|(0x3<<8)|(0x2);//10
	//Pin analoge input
	PINSEL1 |= (1<<24);//|(1<<26);
	
	AD0INTEN = 2;		
	
	VICIntEnable |= (1<<18);
	VICIntSelect &= ~(1<<18); //IRQ
	VICVectCntl2 =  (1<<5)|18;
	VICVectAddr2 = (unsigned)ADCDoneISR;
}

__irq void ADCDoneISR(){		
	#ifdef USE_BOARD
	  int x= AD0DR1;//dummy read to clear interrupt flags
	#endif 
		adc0Res = (AD0GDR>>6)&(0x3ff);
	  VICVectAddr = 0;
}

uint16_t getAdc0Res(){
	return adc0Res;
}

