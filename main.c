#include "platform.h"
#include "pll.h"
#include "leds.h"
#include "uart.h"
#include "simpleProtocol.h"
#include "main.h"

void sendTestMessage(){
	SimpleMessage msg;
	msg.header.startChar = '$';
	msg.header.messageType = 10;
	msg.header.length = 9;
	msg.body[0] = 'A';
  msg.body[1] = 'B';
	msg.crc = 0;
	sendMessage(&msg);
}


int main(){
	initPll();
	initLeds();
	intUART0();
	
	//startTransmission();
	//outputdata('c');
	//outputdata('B');
	//outputdata('c');
	//endTransmission();
	//sendTestMessage();
	
	while(1){
		/*TurnOffLed1;
		TurnOnLed2;
		for(int i=0;i<6000000;i++);
		TurnOnLed1;
		TurnOffLed2;
		for(int i=0;i<6000000;i++);*/
	}
	
	
}

void processFrame(SimpleMessage *frame){
	switch(frame->header.messageType)
	{
		case LED1ON:
			TurnOnLed1;
			break;
		case LED1OFF:
			TurnOffLed1;
			break;
		case LED2ON:
			TurnOnLed2;
			break;
		case LED2OFF:
			TurnOffLed2;
			break;
		case GET_ADC_READING:
			
			break;
		case SEND_TEST_MESSAGE:
			sendTestMessage();
			break;
		//case turn on led1
		//case turn off led1
		//case turn on led2
		//case turn off led2
		//case get adc readding
		
	}
}
