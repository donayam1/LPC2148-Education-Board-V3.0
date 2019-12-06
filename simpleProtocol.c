#include "simpleProtocol.h"
#include <stdint.h>
//simple frame format 
// $ Ll LH MT BBBBB Cl CH $
//
//

int state=0;
int lengthCount=0;
int bodyLength = 0;
int bodyCount = 0;
int crcCount=0;
SimpleMessage message;

void restartFrameReading(){
	state = 0;
	lengthCount = 0;
	bodyLength = 0;
	bodyCount =0;
	crcCount = 0;
}
void errorByteRecived(){
	restartFrameReading();
}

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
					 bodyLength = message.header.length -7; //subtract start,stop,2length,2crc
					 state = 2;
					 
				 }
				break;			
		  case 2: //receiving message type;
				message.header.messageType = byte;
				if(bodyLength>0)
					state=3;
				else
					state =4;
			  break;		
			case 3: // receiving body
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
		  case 5: //receiving end character 
				restartFrameReading();
				if(byte == '$')
				 {											
						processFrame(&message);					
				 }				
				break;	
		}	
}


void sendMessage(SimpleMessage *msg){
	AddToTxBuffer(msg->header.startChar);
	AddToTxBuffer(msg->header.length & 0xff);
	AddToTxBuffer((msg->header.length>>8) & 0xff);
	AddToTxBuffer(msg->header.messageType);
	int bodyLength = msg->header.length - 7;
	for(int i=0;i<bodyLength;i++){
		AddToTxBuffer(msg->body[i]);		
	}
	
	AddToTxBuffer(0);
	AddToTxBuffer(0);
	
	AddToTxBuffer(msg->header.startChar);
	
	Start_SendBuffer();	
}
