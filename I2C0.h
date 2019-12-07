#ifndef __I2C0_H__
#define __I2C0_H__
#include <stdint.h>


#define MASTER_TX 0
#define MASTER_RX 1

typedef struct {
	uint8_t slaveAddress;
	
	uint8_t sendReadAddress;  //
	uint8_t readAddressLength; //
	uint32_t readRegAddress;
	uint8_t *readBuff;
	uint16_t readDataLength;
	void (*readingFinishedCallback)();
	
}I2CReadRequest;

extern uint16_t currentTemprature;
void disableI2C(void);
void enableI2C(void);
void 	initI2C0Interface(void);
void i2cRead(I2CReadRequest *req);
void generateStartCondition(void);
void generateStopCondition(void);
void enableSendingACK(void);
void disableSendingACK(void);
#endif 
