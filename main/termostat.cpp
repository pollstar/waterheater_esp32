#include <stdint.h>
#include "main.h"
#include "esp32-hal-gpio.h"
#include "termostat.h"
#include "parameters.h"

#if !defined(TERMOSTAT_TASK_PRIORITY)
#define TERMOSTAT_TASK_PRIORITY   5
#endif

class Controller;

Termostat::Termostat(Termistor* t1, Termistor* t2, Heater* h1, Heater* h2)
  : m_t1(t1), m_t2(t2), m_heater1(h1), m_heater2(h2) {

  if (Termostat::m_taskHandle == nullptr) {
    xTaskCreate(Termostat::taskTermostat, "5", 2048, nullptr, TERMOSTAT_TASK_PRIORITY, &Termostat::m_taskHandle);
  }

  Termostat::termostats.push_back(this);
}

void Termostat::on() {
  m_heater1->on();
  m_heater2->on();
  Controller::ledHeat.on();
}

void Termostat::halfOn() {
  static Heater* heater = m_heater1;
  heater->on();

  heater = heater == m_heater1 ? m_heater2 : m_heater1;  //for rotation

  Controller::ledHeat.blink(500);
}

void Termostat::off() {
  m_heater1->off();
  m_heater2->off();
  Controller::ledHeat.off();
}

void Termostat::taskTermostat(void* pvParameters) {

  while (1) {
    for (auto termostat : Termostat::termostats) {
      int t1 = termostat->m_t1->getTemp();
      int t2 = termostat->m_t2->getTemp();

      if (t1 > 0 && t2 > 0) {
        int t = Parameters::get()->temp();
        int diff = Parameters::get()->diff();

        if (t1 < t - diff && !termostat->termostatFirstOn) {
          termostat->termostatFirstOn = true;
          termostat->on();
        } else if (t1 >= t + diff && termostat->termostatFirstOn) {
          termostat->termostatFirstOn = false;
          termostat->off();
        }
      }
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
  }

  vTaskDelete(nullptr);
}

TaskHandle_t Termostat::m_taskHandle{ nullptr };
std::vector<Termostat*> Termostat::termostats;
Termostat termostat(&t1, &t2, &heater1, &heater2);
