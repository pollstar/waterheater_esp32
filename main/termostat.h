#pragma once

#include <Arduino.h>
#include <vector>
#include <memory>

#include "heater.h"
#include "termistor.h"

class Termostat {
public:
  Termostat(Termistor* t1, Termistor* t2, Heater* h1, Heater* h2);
  void start(void);
  void stop(void);

private:
  Termostat(const Termostat&) = delete;
  Termostat& operator=(const Termostat&) = delete;

  void on();
  void halfOn();
  void off();

  static void taskTermostat(void* pvParameters);
  static TaskHandle_t m_taskHandle;
  static std::vector<Termostat*> termostats; 

  Termistor* m_t1{ nullptr };
  Termistor* m_t2{ nullptr };

  Heater* m_heater1{ nullptr };
  Heater* m_heater2{ nullptr };

  bool termostatFirstOn = false;
  bool termostatSecondOn = false;
};

extern Termostat termostat;