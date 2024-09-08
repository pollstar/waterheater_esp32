#pragma once
#include <Arduino.h>

class Termistor
{
public:
  Termistor(uint8_t pin);
  int getValue();
  int getValue(int v);
  float getTemp();
private:
  uint8_t m_pin;
};