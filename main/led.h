#pragma once
#include <Arduino.h>
#include <list>

#define LED_DEFAULT_PERIOD 500

class Led {
  public:
    Led(uint8_t pin);
    ~Led();

    void on();
    void off();

    uint8_t getState() {return _state;};
    
    void blink();
    void blink(uint32_t period);
    void blink(uint32_t period_on, uint32_t period_off);

  private:
    uint8_t   _pin;
    uint32_t  _period_on    = LED_DEFAULT_PERIOD;
    uint32_t  _period_off   = LED_DEFAULT_PERIOD;
    uint32_t  _next_switch  = 0;
    uint8_t   _state        = LOW;

    void blinkOff();
    void resetPeriod();

    static void taskHandler(void *pvParameters);

    static TaskHandle_t m_taskHandle;
    static std::list<Led *> listBlinkPin;
    static uint32_t tickMS;
};
