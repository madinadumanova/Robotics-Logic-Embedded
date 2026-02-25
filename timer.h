#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED
#include "event.h"

typedef uint8_t TimerType;

void setTimer(TimerType timer, int time, EventType event);
void startTimer(TimerType timer);
void cancelTimer(TimerType timer);
void timerTask();

#endif  /* TIMER_H_INCLUDED */

