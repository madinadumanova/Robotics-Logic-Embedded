#include "nnxt.h"
#include <nnxt_pcf8574lb.h>
#include "timer.h"
#include "event.h"

#define LEFT_EVENT 1
#define RIGHT_EVENT 2
#define TIMER_EVENT 3
#define TIMER 4

volatile uint32_t Frequency = 1000;

void leftClicked()
{
    sensor_touch_clicked_t left, befleft = SensorTouch_released;

    while (1)
    {
        Touch_Clicked(Port_2, &left);
        if (left == SensorTouch_clicked && befleft == SensorTouch_released)
        {
            setEvent(LEFT_EVENT);
        }
        befleft = left;
        Delay(50);
    }
}

void rightClicked()
{
    sensor_touch_clicked_t right, befright = SensorTouch_released;

    while (1)
    {
        Touch_Clicked(Port_0, &right);
        if (right == SensorTouch_clicked && befright == SensorTouch_released)
        {
            setEvent(RIGHT_EVENT);
        }
        befright = right;
        Delay(50);
    }
}

//Rechter Taster -> Frequenz erhöht
//Linker Taster -> Frequenz erniedrigt
void update_frequency()
{
    while (1)
    {
        if (eventIsSet(RIGHT_EVENT))
        {
            taskENTER_CRITICAL();
            if (Frequency < 2000) Frequency += 10;
            clearEvent(RIGHT_EVENT);
            taskEXIT_CRITICAL();
        }
        else if (eventIsSet(LEFT_EVENT))
        {
            taskENTER_CRITICAL();
            if (Frequency > 100) Frequency -= 10;
            clearEvent(LEFT_EVENT);
            taskEXIT_CRITICAL();
        }
        Delay(20);
    }
}

void testRoboter()
{
    static uint8_t led_state = 1;
    DeletePort(Port_1, 0);

    while (1)
    {
        setTimer(TIMER, Frequency, TIMER_EVENT);
        startTimer(TIMER);
        while (!eventIsSet(TIMER_EVENT))
        {
            Delay(10); // Wait for the timer to trigger
        }

        cancelTimer(TIMER);
        clearEvent(TIMER_EVENT);

        if (led_state == 0)
        {
            DeletePort(Port_1, 0);
            led_state = 1;
        }
        else
        {
            WritePort(Port_1, 0);
            led_state = 0;
        }

    }
}

int main()
{
    SensorConfig(Port_0, SensorTouch);
    SensorConfig(Port_2, SensorTouch);

    CreateAndStartTask(leftClicked);
    CreateAndStartTask(rightClicked);
    CreateAndStartTask(update_frequency);
    CreateAndStartTask(testRoboter);
    CreateAndStartTask(timerTask);
    StartScheduler();

    return 0;
}
