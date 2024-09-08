#pragma once

#include <Arduino.h>

class Heater
{
  public:
    ~Heater();
    static Heater* getHeater();

    void on();
    void halfOn();
    void off();


  private:
    Heater();
    Heater(const Heater&) = delete;
    Heater & operator =(const Heater &) = delete;

    static void taskHeater(void *pvParameters);

    static TaskHandle_t m_taskHandle;
};