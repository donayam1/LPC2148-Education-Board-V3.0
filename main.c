#include <stdint.h>
#include "platform.h"
#include "pll.h"
#include "leds.h"
#include "uart.h"
#include "simpleProtocol.h"
#include "main.h"
#include "adc.h"
#include "I2C0.h"
#include "LM75.h"
#include "TC47.h"

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
void sendAdcReading(){
	SimpleMessage msg;
	msg.header.startChar = '$';
	msg.header.messageType = ADC_RESULT;
	msg.header.length = 9;
	uint16_t res = getAdc0Res();
	msg.body[0] = res&0xff;
  msg.body[1] = (res>>8) & 0x3;
	msg.crc = 0;
	sendMessage(&msg);
}
void sendTempratureReading(){
	SimpleMessage msg;
	msg.header.startChar = '$';
	msg.header.messageType = GET_TEMP_RESULT;
	msg.header.length = 9;
	uint16_t res = getCurrentTemprature();
	msg.body[0] = res&0xff;
  msg.body[1] = (res>>8) & 0x3;
	msg.crc = 0;
	sendMessage(&msg);
}

int main(){
	initPll();
	initLeds();
	intUART0();
	initAdc();
	initI2C0Interface();
	//startTransmission();
	//outputdata('c');
	//outputdata('B');
	//outputdata('c');
	//endTransmission();
	//sendTestMessage();
	readCurrentTemprature();
	//readCurrentTemprature2();
	
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
			sendAdcReading();
			break;
		case SEND_TEST_MESSAGE:
			sendTestMessage();
			break;
		case GET_TEMPRATURE:
			readCurrentTemprature();
			sendTempratureReading();
			break;
		//case turn on led1
		//case turn off led1
		//case turn on led2
		//case turn off led2
		//case get adc readding
		
	}
}
