#include "platform.h"
#include "pll.h"
#include "leds.h"
#include "uart.h"
#include "simpleProtocol.h"
#include "main.h"


int main(){
	initPll();
	initLeds();
	intUART0();
	
	startTransmission();
	outputdata('c');
	//outputdata('B');
	//outputdata('c');
	//endTransmission();
	while(1){
		TurnOffLed1;
		TurnOnLed2;
		for(int i=0;i<6000000;i++);
		TurnOnLed1;
		TurnOffLed2;
		for(int i=0;i<6000000;i++);
	}
	
	
}

void processFrame(SimpleMessage *frame){
	switch(frame->header.messageType)
	{
		case LED1ON:
			break;
		case LED1OFF:
			break;
		case LED2ON:
			break;
		case LED2OFF:
			break;
		case GET_ADC_READING:
			
			break;
		//case turn on led1
		//case turn off led1
		//case turn on led2
		//case turn off led2
		//case get adc readding
		
	}
}
