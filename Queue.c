
#include "Queue.h"
#include <stdlib.h>



 int queue_reinit(Queue *queue)
{
  queue->tail = 0;
  queue->head = 0;
  return 1;
}
 int queue_enqueue(Queue *queue, const uint8_t *data)
{
  
  if(queue_isFull(queue) == 1)
  {
    return -1;
  }
  else
  {

      queue->tail += 1;
      if(queue->tail>=Max_Buff_Length)
         queue->tail = 0;
    
    queue->buffer[queue->tail]= *data;
    return 1;
  }
}

 int queue_dequeue(Queue *queue, uint8_t *data)
{
  if(queue_isEmpty(queue) == 1)
  {
    return -1;
  }
  else
  {
    queue->head += 1;
    if(queue->head >= Max_Buff_Length)
      queue->head = 0;
    
    *data = queue->buffer[queue->head];

    return 1;
  }
}
 int queue_isFull(const Queue *queue)
{
   if(queue->head < queue->tail)
   {
     int x = queue->tail - queue->head;
     if(x == Max_Buff_Length-1)
       return 1;
     else 
       return -1;
   }
   else
   {
     if(queue->tail == (queue->head-1))
       return 1;
     else 
       return -1;       
   } 
}

 int queue_isEmpty(const Queue *queue)
{
   if(queue->head == queue->tail)
     return 1;
   return -1;
  
}
