#include <list>
#include "led.h"

#define LED_TICK_PERIOD 10

Led::Led(uint8_t pin): _pin(pin) {
  pinMode(this->_pin, OUTPUT);
  digitalWrite(this->_pin, LOW);
};

Led::~Led() {
  Led::off();

  if (Led::listBlinkPin.empty() && Led::m_taskHandle) {
    vTaskDelete(Led::m_taskHandle);
    Led::m_taskHandle = nullptr;
  }
};

void Led::on() {
    digitalWrite(this->_pin, HIGH);
    this->_state = HIGH;
};

void Led::off() {
  this->blinkOff();

  digitalWrite(this->_pin, LOW);
  this->_state = LOW;
};

void Led::blink(){ 
  if (std::find(Led::listBlinkPin.begin(), Led::listBlinkPin.end(), this)  == Led::listBlinkPin.end()) {
    Led::listBlinkPin.push_back(this);
  }

  if (Led::m_taskHandle == nullptr) {
    xTaskCreate(Led::taskHandler, "", 1024, nullptr, 5, &Led::m_taskHandle);

  } else {
    vTaskResume(Led::m_taskHandle);
  }
};

void Led::blink(uint32_t period) {
  this->_period_on = this->_period_off = LED_TICK_PERIOD > period ? LED_TICK_PERIOD * 2 : period;
  this->blink();
};

void Led::blink(uint32_t period_on, uint32_t period_off) {
  this->_period_on = LED_TICK_PERIOD > period_on ? LED_TICK_PERIOD * 2 : period_on;
  this->_period_off = LED_TICK_PERIOD > period_off ? LED_TICK_PERIOD * 2 : period_off;
  this->blink();
};

void Led::blinkOff() {

  auto it = std::find(Led::listBlinkPin.begin(), Led::listBlinkPin.end(), this);

  if (it == Led::listBlinkPin.end()) {
    return;
  }
  
  Led::listBlinkPin.erase(it);

  if (Led::listBlinkPin.empty() && Led::m_taskHandle) {
    vTaskSuspend(Led::m_taskHandle);
  }

  this->resetPeriod();
};

void Led::taskHandler(void *pvParameters) {
  while(1) {
    Led::tickMS += LED_TICK_PERIOD;

    for (auto led: listBlinkPin) {
      if (led->_next_switch < Led::tickMS) {
        if (led->_state == LOW) {
          led->_next_switch += led->_period_on;
          led->_state = HIGH;
        } else {
          led->_next_switch += led->_period_off;
          led->_state = LOW;
        }
        digitalWrite(led->_pin, led->_state);
      }
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  };

  vTaskDelete(nullptr);
};

void Led::resetPeriod() {
    this->_period_on = LED_DEFAULT_PERIOD;
    this->_period_off = LED_DEFAULT_PERIOD;      
};


TaskHandle_t      Led::m_taskHandle = nullptr;
std::list<Led *>  Led::listBlinkPin;
uint32_t          Led::tickMS = 0;
