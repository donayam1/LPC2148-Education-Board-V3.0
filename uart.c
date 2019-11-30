
#include "platform.h"
#include "uart.h"

__irq void uart0ISR(void);
void enableUART0Interrupt(void);


//#include "simpleProtocol.h"
/*PLCK is 15MHZ 
	baude rate 9600
	16xH+L=90s	
	M=12
	D=1, 
*/
void intUART0(){
	PINSEL0 |= (0x1<<2) | 1; //Set the pins to UART, P0.0 T0D, P0.1 R0D
	
 //1characters raises interrupt,Enable FIFO bufers	
	U0FCR = (0<<6)|0x1;
	//odd parity ,8 bit send and recive
	U0LCR = (1<<3)|3;  //
	
	//bit 7 is DLAB , set to 9600 with 0.0064% error
	U0LCR |= (1<<7); // enable the DLAB bit then set the divisors 
	U0DLL = 90;//93;
	U0DLM = 0;
	U0FDR =  (12<<4)| 1;// MULVAL = 1, DIVADDVAL = 1
	U0LCR &=~(1<<7); // clear the DLAB bit 
	//
	U0IER |= 3;//1//RECIVE interrupt is enabled,
	U0TER &= !(1<<7); // disable the transmitter 
	
	enableUART0Interrupt();
}

void startTransmission(){
	U0TER |= (1<<7); // enable the transmitter 
	U0IER |= 2;////enable tx buffer,	
}

void endTransmission(){
	U0IER &= ~2;//
	U0TER &= ~(1<<7); // enable the transmitter 
}

void enableUART0Interrupt(void)
{
	VICVectAddr1 = (unsigned int)uart0ISR;//ISR
	VICIntSelect &= ~(1<<6); //IRQ
	//VICDefVectAddr =(unsigned int)DefInterrupt; //
	VICVectCntl1 =  (1<<5)|6;//IRQslot_en,for interrupt 6, UART0
	VICIntEnable = (1<<6);//UART0 interrupt 
}

	uint8_t data;
int reciveBeffer[4];
__irq void uart0ISR(){
	
	int y = U0IIR;
	int z = U0LSR;

	if( (y & 1) == 1) // no interrupt
	{
		return;
	}
	int theInt = (y>>1) & 7;
	switch(theInt){ // data is avaiable
		/*case 3: //Receive Line Status (RLS)
			 z = U0LSR;
			break;*/
		case 2:
		  if((z&(1<<7))==(1<<7))//check for any error before reading data
			{
				errorByteRecived();
			}else{
				data = U0RBR;
				outputdata(data);
				while((U0LSR&0x40)==0);
				//byteRecived(data);
			}
			break;
		/*case 6://Character Time-out Indicator (CTI).
			break;*/
		case 1: //THRE Interrupt
			//U0THR = 5;
				//outputdata('k');
		    endTransmission();
			break;		
	}
	
	VICVectAddr =0;
}



void outputdata(uint8_t data)
{
  //if((U0LSR & (1<<5)) != 0) // empty tx buffer 
  {
		startTransmission();
		U0THR = data;
	}
}
