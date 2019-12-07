#include "platform.h"
#include "I2C0.h"
#include "simpleProtocol.h"

uint8_t i2cStatus;
uint8_t i2cMode; //Master transmit = 0
							   //Master recive = 1


uint8_t readDataLength = 0;

I2CReadRequest *currReq;
int recivedDataCounter = 0;
int sentAddressByteCounter = 0;

__irq void i2c0ISR(void);



void initI2C0Interface(){
	
	PINSEL0 |= (1<<6)|(1<<4); //SDA,SCL
	//PINSEL0 |= 1<<6; //SDA
	
	I2C0SCLH = 0;
	I2C0SCLL = 150; //set it to run at 100Khz, b/c min time is 2.5usec = 400Khz 
	I2C0CONCLR =0;// 1<<2 | 1<<3 | 1<<5; //Clear AA,SI and STA bits
	I2C0CONSET = 1<<6; //enable the I2C module => set I2CEN bit 
	
	//enable interrupt 
	VICVectAddr3 = (unsigned int)i2c0ISR;//ISR
	VICIntSelect &= ~(1<<9); //IRQ
	//VICDefVectAddr =(unsigned int)DefInterrupt; //
	VICVectCntl3 =  (1<<5)|9;//IRQslot_en,for interrupt 9, I2C0
	VICIntEnable |= (1<<9);//I2C0 interrupt 
	
	
}


void i2cRead(I2CReadRequest *req){
	currReq = req;		
	sendLogMessage((unsigned char *)"\nStart I2C",11);
	generateStartCondition();
	
}

void generateStartCondition(){
	I2C0CONSET = 1<<5;
}
void clearStartCondition(){
	I2C0CONCLR = 1<<5;
}
void generateStopCondition(){
	I2C0CONSET = 1<<4;
}
void enableSendingACK(){
	I2C0CONSET = 1<<2;
}
void disableSendingACK(){
	I2C0CONCLR = 1<<2;
}
void disableI2C(){
	I2C0CONCLR = 1<<6;
}
void enableI2C(){
	I2C0CONCLR = 0;
	I2C0CONSET = 1<<6;
}


__irq void i2c0ISR(){
	
	i2cStatus = I2C0STAT;
	sendLogMessage((unsigned char *)"\nISR",4);
	switch(i2cStatus)
	{
		case 0x08: //start condition has been transmitted	 
			sendLogMessage((unsigned char *)"\nCase 0x08",11);
			if(currReq->sendReadAddress == 0)			{ //no need to send read address pointer, so set it to read mode
				I2C0DAT = (currReq->slaveAddress) | 1;			
				//clearStartCondition();
			}
			else{ //read address pointer needs to be sent, so set it to write mode 
				I2C0DAT = (currReq->slaveAddress) | 1; 
			}
			
			clearStartCondition();
			break;
		case 0x10://repeated start condition has been transmitted	
			sendLogMessage((unsigned char *)"\nCase 0x10",11);
			I2C0DAT = (currReq->slaveAddress) | 1;	//no need to send read address pointer, so set it to read mode
		  clearStartCondition();
			break;
	  case 0x18: //SLA+W has been tx & ACK received
		//case 0x20:
				//send the register address to read  
		    sendLogMessage((unsigned char *)"\nCase 0x18",11);
				I2C0DAT = currReq->readRegAddress & 0xFF;
				sentAddressByteCounter++;
				if(sentAddressByteCounter < currReq->readAddressLength){
					currReq->readRegAddress >>=8;
				}
				else{
					generateStartCondition(); // repated start condtion
				}
				
		
		  break;
		case 0x20: //SLA+W has been tx & NoAck received 
			sendLogMessage((unsigned char *)"\nCase 0x20",11);
		break;
		case 0x28: //Data byte in I2DATA tx & ACK recived
			//case 0x30: //Data byte in I2DATA tx & NoACK recived
		 sendLogMessage((unsigned char *)"\nCase 0x28",11);
			if(sentAddressByteCounter < currReq->readAddressLength){
				I2C0DAT= (currReq->readRegAddress) &0xff;
				currReq->readRegAddress >>= 8;
				sentAddressByteCounter ++;
			}else{
				generateStartCondition();
			}
			break;
		case 0x30: //Data byte in I2DATA tx & NoACK recived
			sendLogMessage((unsigned char *)"\nCase 0x30",11);
		  //currReq->readingFinishedCallback();
			//disableI2C();
			//currReq = 0;
		break;
		case 0x38: //Arbitration lost 
			
			break;
		
		
		case 0x40: //SLA+R tx & ACK rx
		//case 0x48: //SLA+R tx & NoACK rx,TODO remove this block
	    sendLogMessage((unsigned char *)"\nCase 0x40",11);
			if(currReq->readDataLength>1){
					enableSendingACK();
				}else{
					disableSendingACK();
				}
			break;
		case 0x48: //SLA+R tx & NoACK rx,TODO remove this block
			sendLogMessage((unsigned char *)"\nCase 0x48",11);
			break;
		case 0x50: //Data received and ACK returned 
			sendLogMessage((unsigned char *)"\nCase 0x50",11);
			recivedDataCounter++;
			*currReq->readBuff++ = I2C0DAT;				
			if(recivedDataCounter < currReq->readDataLength-1 ){
					enableSendingACK();
			}else{
				  disableSendingACK();
			}					
			break;
		case 0x58: //Data recived and NoACK tx
			sendLogMessage((unsigned char *)"\nCase 0x58",11);
			recivedDataCounter++;
		  *currReq->readBuff++ = I2C0DAT;
			//if(recivedDataCounter == currReq->readAddressLength){ // final byte recived 
			generateStopCondition();
			currReq->readingFinishedCallback();
			disableI2C();
			currReq = 0;	
			//}
			break;
		default:
			sendLogMessage((unsigned char *)"default case",13);
			break;
	}
	
	I2C0CONCLR = (1<<3); //clear the SI flag 
	VICVectAddr = 0;
}
