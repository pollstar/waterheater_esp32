#pragma once

#include "main.h"

class Heater {
public:
  Heater(uint8_t pin);

  void on(void);
  void off(void);
  
private:
  uint8_t m_pin;
};

extern Heater heater1;
extern Heater heater2;