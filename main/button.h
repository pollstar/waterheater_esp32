#pragma once
#include <Arduino.h>
#include <list>
#include <functional>
#include <mutex>

#define CONFIG_BUTTON_DEBOUNCE_TIME_MS 50
#define CONFIG_PIR_DEBOUNCE_TIME_MS    100
#define CONFIG_BUTTON_LONG_PRESS_MS    1000

typedef std::function<void()> ButtonCallback;

#define BTN_DOWN    36
#define BTN_OK_MENU 37
#define BTN_UP      38

class Button {
public:
  Button(uint8_t pin);
  ~Button();

  inline void registerOnPressedCallback(ButtonCallback cb)
    {
      this->onPressedCallback = cb;
      Button::startHandler(this);
    };
  inline void registerOnReleasedCallback(ButtonCallback cb)
    {
      this->onReleasedCallback = cb;
      Button::startHandler(this);
    };
  inline void registerOnTouchCallback(ButtonCallback cb)
    {
      this->onTouchCallback = cb;
      Button::startHandler(this);
    };
  inline void registerOnLongTouchCallback(ButtonCallback cb)
    {
      onLongTouchCallback_ = cb;
      Button::startHandler(this);
    };

  inline void removeOnPressedCallback()
    {this->onPressedCallback = nullptr;};
  inline void removeOnReleasedCallback()
    {this->onReleasedCallback = nullptr;};
  inline void removeOnTouchCallback()
    {this->onTouchCallback = nullptr;};
  inline void removeOnLongTouchCallback()
    {onLongTouchCallback_ = nullptr;};

  enum State{RELASE, PRESSED, LONG_PRESSED};
  
private:
    uint8_t m_pin;
    uint8_t m_currentState = HIGH;

    ButtonCallback onPressedCallback = nullptr;
    ButtonCallback onReleasedCallback = nullptr;
    ButtonCallback onTouchCallback = nullptr;
    ButtonCallback onLongTouchCallback_ = nullptr;
  
    int16_t timePressDuration_ = 0;
    int16_t timePressedDuration = 0;
    int16_t timeReleaseDuration = 0;
    int16_t timeLongPressDuration = 0;
  
    static void taskHandler(void *pvParameters);
    static void startHandler(Button *btn);

    static TaskHandle_t m_taskHandle;
    static std::list<Button*> m_buttonList;
    static std::mutex m_mutex;
};
