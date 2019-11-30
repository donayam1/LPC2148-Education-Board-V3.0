#include "simpleProtocol.h"
#include <stdint.h>


int state=0;
int lengthCount=0;
int bodyLength = 0;
int bodyCount = 0;
int crcCount=0;
void errorByteRecived(void){
	restartFrameReading();
}
void restartFrameReading(){
	state = 0;
	lengthCount = 0;
	bodyLength = 0;
	bodyCount =0;
	crcCount = 0;
}

SimpleMessage message;


void byteRecived(uint8_t byte){
		switch(state)
		{
			case 0: // waiting for start charactor
					if(byte == '$')
					{
						 message.header.startChar = byte;
						 state =1;						
					}				
				break;
			case 1: // receiving message length
				 if(lengthCount ==0){
						message.header.length = byte; 
					  lengthCount = 1;
				 }else if(lengthCount == 1){
						message.header.length |= byte<<8;
					 bodyLength = message.header.length -6; //subtract start,stop,2length,2crc
					 state = 2;
					 
				 }
				break;			
		  case 2: //reciving message type;
				message.header.messageType = byte;
			  state=3;
			  break;		
			case 3: // receving body
				message.body[bodyCount] = byte;
				bodyCount ++;
				if(bodyCount == bodyLength)
					state = 4;
			  break;				
			case 4: // recive 2 byte crc
				 if(crcCount == 0){
					message.crc = byte;
					 crcCount++;					
				 }else if(crcCount == 1){
					 message.crc |= byte<<8;
					 state=5;
					 //TODO do crc check 
				 }
				break;
		  case 5:
				restartFrameReading();
				if(byte == '$')
				 {											
						processFrame(&message);					
				 }				
				break;	
		}	
}


