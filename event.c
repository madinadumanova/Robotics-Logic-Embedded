#include "event.h"

volatile uint16_t eventFlags = 0;

void setEvent(EventType event) {
    taskENTER_CRITICAL();
    eventFlags |= (1 << event);
    taskEXIT_CRITICAL();
}

uint8_t eventIsSet(EventType event) {
    uint8_t result = (eventFlags & (1 << event)) != 0;
    return result;
}

void clearEvent(EventType event) {
    taskENTER_CRITICAL();
    eventFlags &= ~(1 << event);
    taskEXIT_CRITICAL();
}
