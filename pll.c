
#include "platform.h"
#include "pll.h"

#ifdef USE_BOARD
/*
 Initialize system to run at 60MHZ
*/
void initPll(){
	
	//FCCO = CCLK � 2 � P or FCCO = FOSC � M � 2 � P
	//CCLK = M � FOSC
	//0 PSEL=5:6=(2)-1 MSEL = 4:0=(5)-1, 
	PLL0CFG = 0b00100100;
	PLL0CON = 0x1; //Enable
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	while((PLL0STAT &(1<<10)) == 0);
	
	PLL0CON = 0x3; //Connect and Enable
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	
	VPBDIV = 00;//1/4 01;//same 
	
}
#else
/*
 Initialize system to run at 60MHZ
*/
void initPll(){
	
	//FCCO = CCLK � 2 � P or FCCO = FOSC � M � 2 � P
	//CCLK = M � FOSC
	//0 PSEL=5:6=(2)-1 MSEL = 4:0=(5)-1, 
	PLLCFG = 0b00100100;
	PLLCON = 0x1; //Enable
	PLLFEED = 0xAA;
	PLLFEED = 0x55;
	while((PLLSTAT &(1<<10)) == 0);
	
	PLLCON = 0x3; //Connect and Enable
	PLLFEED = 0xAA;
	PLLFEED = 0x55;
	
	VPBDIV = 00;//1/4 01;//same 
	
}
#endif 
