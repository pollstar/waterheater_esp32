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
      onPressedCallback_ = cb;
      Button::startHandler(this);
    };
  inline void registerOnReleasedCallback(ButtonCallback cb)
    {
      onReleasedCallback_ = cb;
      Button::startHandler(this);
    };
  inline void registerOnTouchCallback(ButtonCallback cb)
    {
      onTouchCallback_ = cb;
      Button::startHandler(this);
    };
  inline void registerOnLongTouchCallback(ButtonCallback cb)
    {
      onLongTouchCallback_ = cb;
      Button::startHandler(this);
    };

  inline void removeOnPressedCallback()
    {onPressedCallback_ = nullptr;};
  inline void removeOnReleasedCallback()
    {onReleasedCallback_ = nullptr;};
  inline void removeOnTouchCallback()
    {onTouchCallback_ = nullptr;};
  inline void removeOnLongTouchCallback()
    {onLongTouchCallback_ = nullptr;};

  enum State{RELASE, PRESSED, LONG_PRESSED};
  
private:
    uint8_t pin_;
    State state_;
    uint8_t currentState_ = HIGH;

    ButtonCallback onPressedCallback_ = nullptr;
    ButtonCallback onReleasedCallback_ = nullptr;
    ButtonCallback onTouchCallback_ = nullptr;
    ButtonCallback onLongTouchCallback_ = nullptr;
  
    int16_t timePressDuration_ = 0;
    int16_t timePressedDuration_ = 0;
    int16_t timeReleaseDuration = 0;
    int16_t timeLongPressDuration = 0;
  
    static void taskHandler(void *pvParameters);
    static void startHandler(Button *btn);

    static TaskHandle_t m_taskHandle;
    static std::list<Button*> m_buttonList;
    static std::mutex m_mutex;
};
