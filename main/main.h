#pragma once

#include "Arduino.h"

#define TERMISTOR1_PIN      32       
#define TERMISTOR2_PIN      33

#define HEATER1_PIN         12
#define HEATER2_PIN         21

#define LED_LOCK            13
#define LED_COLD            15
#define LED_ECO             2
#define LED_COMFORT         17
#define LED_HEAT            22

#define TERMISTOR_ON        25

#define BUTTON_TASK_PRIORITY      5
#define BUTTON_TICK_PERIOD        10
#define BUTTON_TASK_STACK_SIZE    2048

#define TERMOSTAT_TASK_PRIORITY   4
#define TERMOSTAT_TICK_PERIOD     1000
#define TERMOSTAT_TASK_STACK_SIZE 2048

#define LED_TASK_PRIORITY         5
#define LED_TICK_PERIOD           10
#define LED_TASK_STACK_SIZE       1024
