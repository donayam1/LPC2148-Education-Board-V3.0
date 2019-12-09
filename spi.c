#include "platform.h"
#include "spi.h"
#include <stdint.h>
#include "simpleProtocol.h"

uint8_t spiStatus;
uint8_t spiFalg;

__irq void spiISR(void);

const uint16_t diagonal[] = {
  0x7f7f,
	0xbfbf,
	0xdfdf,
	0xefef,
	0xf7f7,
	0xfbfb,
	0xfdfd,
	0xfefe,
};


void initSPI()
{
	selectLedMatrix;
	IO0CLR |=1<<SSEL ;
		//sends or recives specified bits, master mode,enable interrupt, send 16 bits 0000
	S0SPCR = 1<<2|1<<5 |1<<7 ;
	S0SPCCR = 100; //spi runs at 150khz 
	
	
	
	PINSEL0 |= 1<<8|1<<10 | 1<<12 | 1<14; //enable the spi pins
	
	//enable interrupt on address 4
	VICVectAddr4 = (unsigned int)spiISR;//ISR
	VICIntSelect &= ~(1<<10); //IRQ	
	VICVectCntl4 =  (1<<5)|10;//IRQslot_en,for interrupt 6, SPI0
	VICIntEnable |= (1<<10);//SPI0 interrupt 
}

void write_spi(uint16_t data)
{
	S0SPDR = data;
}
int i=0;
__irq void spiISR(){
	spiStatus = S0SPSR;
	spiFalg = (spiStatus)&(1<<7);	
	if(spiFalg ==1<<7){ //write and read has finished 
		//write_spi(0xff00);
		//sendLogMessage((unsigned char *)"\nS",3);
		write_spi(diagonal[i]);
		i++;
		if(i==8)
			i=0;
		
		//TOGGEL is required to drive the OE pin
		IOPIN0 |=1<<15;
		//for(int i=0;i<100;i++);
		IOPIN0 &=~(1<<15);
		
	}
	//TODO check for errors
	
	
	VICVectAddr =0;
	S0SPINT = 1;//clear the spi interrupt 
}
