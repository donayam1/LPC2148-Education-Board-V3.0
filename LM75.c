
#include "platform.h"
#include "LM75.h"
#include "I2C0.h"

uint16_t currentTemprature = 0;
uint8_t tempratureBuffer[2];
uint8_t isReadingTemp=0;

void tempratureReadFinished(void);

uint16_t getCurrentTemprature(){
		return currentTemprature;
}

void readCurrentTemprature(){
	if(isReadingTemp == 0){
		I2CReadRequest req;
	
		req.readBuff = tempratureBuffer;
	  req.readDataLength = 2;
	  req.readingFinishedCallback = tempratureReadFinished;
	  
	
	  req.sendReadAddress = 0;
	  req.readRegAddress = 0;
		req.readAddressLength = 0;

		req.slaveAddress = TEMPRATURE_SENSOR_ADDRESS;
		i2cRead(&req);
		isReadingTemp = 1;
	 }
}

void tempratureReadFinished(){
	currentTemprature = tempratureBuffer[0]<<8 | tempratureBuffer[1];
	isReadingTemp = 0;
}
