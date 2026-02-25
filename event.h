#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED
#include "nnxt.h"
#include <stdio.h>

typedef uint8_t EventType;                  // Event ID type
volatile uint16_t eventFlags;

void setEvent(EventType event);
uint8_t eventIsSet(EventType event);
void clearEvent(EventType event);


#endif  /* EVENT_H_INCLUDED */
