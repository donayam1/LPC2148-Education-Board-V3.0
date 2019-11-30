#ifndef __SIM_PRO_H__
#define __SIM_PRO_H__
#include <stdint.h>

#define  Max_Buff_Length  100
#define RECIVING_HEADER 1
#define RECIVING_BODY 2


//message type definations 
#define LED1ON 5
#define LED1OFF 6
#define LED2ON 7
#define LED2OFF 8
#define GET_ADC_READING 20
#define ADC_RESULT 21


typedef struct{
	uint8_t startChar; //start character
	uint16_t length; //total message length 
	uint8_t messageType; //the message type -> 
	
}SimpleMessageHeader;

typedef struct{
  SimpleMessageHeader header;
  uint8_t body[Max_Buff_Length];
	uint16_t crc;
  uint8_t head;
  uint8_t tail;
  
}SimpleMessage;

void errorByteRecived(void);
void restartFrameReading(void);
void byteRecived(uint8_t byte);
extern void processFrame(SimpleMessage *frame);
#endif 