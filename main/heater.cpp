#include <stdint.h>
#include "esp32-hal-gpio.h"
#include "heater.h"
#include "parameters.h"

class Controller;

#define REL1 12
#define REL2 21

Heater::Heater()
{
  pinMode(REL1, OUTPUT);
  pinMode(REL2, OUTPUT);
  digitalWrite(REL1, LOW);
  digitalWrite(REL2, LOW);

  xTaskCreate(Heater::taskHeater, "5", 2048, nullptr, 5, &Heater::m_taskHandle);
}

Heater::~Heater()
{
  vTaskDelete(Heater::m_taskHandle);
}

Heater* Heater::getHeater()
{
  static Heater heater;
  return &heater;
}

void Heater::on()
{
  digitalWrite(REL1, HIGH);
  digitalWrite(REL2, HIGH);
  Controller::ledHeat.on();
}

void Heater::halfOn()
{
  static uint8_t relay = REL1;
  digitalWrite (relay, HIGH);
  relay = relay == REL1 ? REL2 : REL1; //for rotation
  Controller::ledHeat.blink(500);
}

void Heater::off()
{
  digitalWrite(REL1, LOW);
  digitalWrite(REL2, LOW);
  Controller::ledHeat.off();
}

void Heater::taskHeater(void *pvParameters)
{
  static bool heaterFirstOn = false;
  static bool heaterSecondOn = false;

  while(1)
  {
    int t1 = Parameters::get()->getT1();
    int t2 = Parameters::get()->getT2();

    if (t1 > 0 && t2 > 0) { 
      int t = Parameters::get()->temp();
      int diff = Parameters::get()->diff();

      if (t1 <  t - diff && !heaterFirstOn) {
        heaterFirstOn = true;
        Heater::getHeater()->on();
      } 
      else if (t1 >= t + diff && heaterFirstOn) {
        heaterFirstOn = false;
        Heater::getHeater()->off();
      }
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
  }

  vTaskDelete(nullptr);
}

TaskHandle_t Heater::m_taskHandle;
