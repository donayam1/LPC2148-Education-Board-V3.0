
#include "platform.h"
#include "TC47.h"
#include "I2C0.h"

uint16_t currentTemprature2 = 0;
uint8_t tempratureBuffer2[2];
uint8_t isReadingTemp2=0;

void tempratureReadFinished2(void);

uint16_t getCurrentTemprature2(){
		return currentTemprature2;
}

void readCurrentTemprature2(){
	if(isReadingTemp2 == 0){
		I2CReadRequest req;
	
		req.readBuff = tempratureBuffer2;
	  req.readDataLength = 1;
	  req.readingFinishedCallback = tempratureReadFinished2;
	  
	
	  req.sendReadAddress = 1;
	  req.readRegAddress = 0;
		req.readAddressLength = 1;

		req.slaveAddress = TEMPRATURE_SENSOR_ADDRESS2;
		i2cRead(&req);
		isReadingTemp2 = 1;
	 }
}

void tempratureReadFinished2(){
	currentTemprature2 = tempratureBuffer2[0]<<8 | tempratureBuffer2[1];
	isReadingTemp2 = 0;
}
