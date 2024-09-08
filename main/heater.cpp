#include "heater.h"

Heater::Heater(uint8_t pin)
  : m_pin(pin) {
  pinMode(m_pin, OUTPUT);
  digitalWrite(m_pin, LOW);
}

void Heater::on(void) {
  digitalWrite(m_pin, HIGH);
}

void Heater::off(void) {
  digitalWrite(m_pin, LOW);
}

Heater heater1(HEATER1_PIN);
Heater heater2(HEATER2_PIN);