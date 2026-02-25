#include "timer.h"

#define MAX_TIMERS 5

typedef struct
{
    uint8_t active;
    int endTime;
    EventType eventToTrigger;
    int duration;
} Timer;

volatile Timer timers[MAX_TIMERS];

void setTimer(TimerType timer, int duration, EventType event)
{
    timers[timer].eventToTrigger = event;
    timers[timer].active = 0;
    timers[timer].duration = duration;
}

void startTimer(TimerType timer)
{
    timers[timer].active = 1;
    timers[timer].endTime = GetSysTime() + timers[timer].duration;
}

void cancelTimer(TimerType timer)
{
    timers[timer].active = 0;
}

//task zur abfrage aller timer
void timerTask()
{
    while (1)
    {
        taskENTER_CRITICAL();

        for (int i = 0; i < MAX_TIMERS; i++)    // Changed 5 to MAX_TIMERS for scalability
        {
            if (timers[i].active && GetSysTime() >= (timers[i].endTime))
            {
                setEvent(timers[i].eventToTrigger);
                timers[i].active = 0;  // Changed from 0 to false for clarity
            }
        }

        taskEXIT_CRITICAL();
        Delay(10);
    }
}
