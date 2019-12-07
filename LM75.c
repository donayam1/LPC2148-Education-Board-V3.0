
#include "platform.h"
#include "LM75.h"
#include "I2C0.h"
#include "simpleProtocol.h"

uint16_t currentTemprature = 0x15;
uint8_t tempratureBuffer[2];
uint8_t isReadingTemp=0;

void tempratureReadFinished(void);

uint16_t getCurrentTemprature(){
		return currentTemprature;
}

void readCurrentTemprature(){
	if(isReadingTemp == 0){
		I2CReadRequest req;
	
		req.readBuff = &tempratureBuffer[0];
	  req.readDataLength = 2;
	  req.readingFinishedCallback = tempratureReadFinished;
	  
	
	  req.sendReadAddress = 0;
	  req.readRegAddress = 0;
		req.readAddressLength = 0;

		req.slaveAddress = TEMPRATURE_SENSOR_ADDRESS;
	  enableI2C();
		i2cRead(&req);		
		isReadingTemp = 1;
	 }
}

void tempratureReadFinished(){
	currentTemprature = tempratureBuffer[0]<<8 | tempratureBuffer[1];
	isReadingTemp = 0;
	sendLogMessage((unsigned char *)"\nReading Done",14);
}
