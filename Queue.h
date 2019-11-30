

#ifndef QUEUE_H
#define QUEUE_H
#include <stdint.h>

#define Max_Buff_Length 200

typedef struct{
  
  uint8_t buffer[Max_Buff_Length];
  uint8_t head;
  uint8_t tail;
  
}Queue;

//__monitor int queue_init(Queue *queue);
 int queue_reinit(Queue *queue);
 int queue_enqueue(Queue *queue, const uint8_t *data);
 int queue_dequeue(Queue *queue, uint8_t *data);
 int queue_size(const Queue *queue);
 int queue_isEmpty(const Queue *queue);
 int queue_isFull(const Queue *queue);
//__monitor void queue_destroy(Queue *queue);

#endif
