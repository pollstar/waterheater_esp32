#include "esp32-hal-gpio.h"
#include "button.h"

#define BUTTON_TICK_PERIOD 10
#define BUTTON_TASK_STACK_SIZE 2048
#define BUTTON_TASK_PRIORITY   5

Button::Button(uint8_t pin): m_pin(pin) {
	pinMode(this->m_pin, INPUT);
}

Button::~Button() {
  std::lock_guard<std::mutex> lock(m_mutex);
  removeOnPressedCallback();
  removeOnReleasedCallback();
  removeOnTouchCallback();
  removeOnLongTouchCallback();

  auto it = std::find(Button::m_buttonList.begin(), Button::m_buttonList.end(), this);

  if (it == Button::m_buttonList.end()) {
    return;
  }
  
  Button::m_buttonList.erase(it);

  if (Button::m_buttonList.empty() && Button::m_taskHandle) {
    vTaskDelete(Button::m_taskHandle);
    Button::m_taskHandle = nullptr;
  }
}

void Button::startHandler(Button *btn) {

  if (std::find(Button::m_buttonList.begin(), Button::m_buttonList.end(), btn)  == Button::m_buttonList.end()) {
    Button::m_buttonList.push_back(btn);
  }

  if (Button::m_taskHandle == nullptr) {
    xTaskCreate(Button::taskHandler, "", 
              BUTTON_TASK_STACK_SIZE, nullptr, BUTTON_TASK_PRIORITY, &Button::m_taskHandle);
  }
}

void Button::taskHandler(void *pvParameters) {
  while(1) {
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto btn: m_buttonList) {
      int tmp_state = digitalRead(btn->m_pin);

      if (btn->m_currentState != tmp_state) {
        if(!btn->timePressDuration_) {
          btn->timePressDuration_ = CONFIG_BUTTON_DEBOUNCE_TIME_MS;
        } else {
          btn->timePressDuration_ -=10;
        }

        if (btn->timePressDuration_ <= 0) {
          btn->m_currentState = tmp_state;
          btn->timePressDuration_ = 0;

          if (btn->m_currentState == LOW && btn->onPressedCallback) {
            btn->onPressedCallback();
            btn->timeLongPressDuration = CONFIG_BUTTON_LONG_PRESS_MS;
          } 
          else if (btn->m_currentState == HIGH) {
            if (btn->onReleasedCallback) {
              btn->onReleasedCallback();
            }

            if (btn->onTouchCallback) {
              btn->onTouchCallback();
            }

            // if (timeLongPressDuration <= 0 && onLongTouchCallback_) {
            //   onLongTouchCallback_();
            //   timeLongPressDuration = CONFIG_BUTTON_LONG_PRESS_MS;
            // } 
          }
        }
      }
    }

    vTaskDelay(pdMS_TO_TICKS(10));
  }

  vTaskDelete(nullptr);
};

TaskHandle_t        Button::m_taskHandle = nullptr;
std::list<Button *> Button::m_buttonList;
std::mutex          Button::m_mutex;