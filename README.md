# Robotics-Logic-Embedded

Industrial Automation: Real-Time Frequency Control (RTOS)

Academic Project: Robotics \& Digital Design



🎯 Project Overview

Designed a multi-tasking control system for an autonomous robot using an RTOS architecture. Built a responsive interface enabling real-time actuator/LED frequency adjustment via touch sensors, ensuring zero-latency input handling.



🛠️ Technical Implementation

Implemented an event-driven architecture, replacing a super-loop with 5 concurrent tasks:



Task 1 \& 2 (Interrupt Handling): Touch sensor monitoring with software debouncing for signal integrity.



Task 3 (Global Logic Controller): Dynamic frequency updates from asynchronous events.



Task 4 (Actuator Task): Hardware port toggling at the set frequency.



Task 5 (Timer Task): RTOS heartbeat and task scheduling.



💻 Key Engineering Concepts



Concurrency \& Synchronization: Protected global variables from race conditions using taskENTER\_CRITICAL() / taskEXIT\_CRITICAL().



Resource Management: Applied the StartScheduler() pattern for CPU time allocation across tasks.



I/O Logic: Implemented bounded frequency control (100ms–2000ms) with increment/decrement logic and crash protection.

