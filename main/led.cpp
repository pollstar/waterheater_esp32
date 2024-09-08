#include <list>
#include "main.h"
#include "led.h"

#if !defined(LED_TASK_PRIORITY)
#define LED_TASK_PRIORITY         5
#endif

#if !defined(LED_TICK_PERIOD)
#define LED_TICK_PERIOD           10
#endif

#if !defined(LED_TASK_STACK_SIZE)
#define LED_TASK_STACK_SIZE       1024
#endif

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
    xTaskCreate(Led::taskHandler, "Led_task", LED_TASK_STACK_SIZE,
      nullptr, LED_TASK_PRIORITY, &Led::m_taskHandle);

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
    vTaskDelay(pdMS_TO_TICKS(LED_TICK_PERIOD));
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

