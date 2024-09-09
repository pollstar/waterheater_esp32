#include "controller.h"
#include "parameters.h"

#define TERMISTOR1        32       
#define TERMISTOR2        33
#define TERMISTOR_ON      25

void Controller::run(State *state)
{
  pinMode(TERMISTOR_ON, OUTPUT);
  Controller::setState(state);

  if (!Controller::m_taskReadTemp) {
    xTaskCreate(taskReadTermistor, "2", 1024, nullptr, 5, &Controller::m_taskReadTemp);
  }

  if (!Controller::m_heater) {
    Controller::m_heater = Heater::getHeater();
  }
}

void Controller::stop()
{
  if (Controller::m_state != nullptr) {
    Controller::btnDown.removeOnTouchCallback();
    Controller::btnOkMenu.removeOnTouchCallback();
    Controller::btnUp.removeOnTouchCallback();

    delete Controller::m_state;
    Controller::m_state = nullptr;
  }

  if (Controller::m_taskHandle) {
    vTaskDelete(Controller::m_taskHandle);
    Controller::m_taskHandle = nullptr;
  }  
  
  if (Controller::m_taskReadTemp) {
    vTaskDelete(Controller::m_taskReadTemp);
    Controller::m_taskReadTemp = nullptr;
  }
}

void Controller::setState(State *state)
{
  if (state == nullptr) return;

  Controller::stop();
  Controller::m_state = state;

  if (!Controller::m_taskHandle) {
    xTaskCreate(Controller::taskRenderScreen, "1", 3048, nullptr, 5, &Controller::m_taskHandle);
  }

  Controller::btnDown.registerOnTouchCallback(Controller::handleBtDown);
  Controller::btnOkMenu.registerOnTouchCallback(Controller::handleBtOkMenu);
  Controller::btnUp.registerOnTouchCallback(Controller::handleBtUp);
}

void Controller::handleBtDown()
{
  if (Controller::m_state != nullptr) {
    Controller::m_state->handleBtDown();
  }
}

void Controller::handleBtOkMenu()
{
  if (Controller::m_state != nullptr) {
    Controller::m_state->handleBtOkMenu();
  }
}

void Controller::handleBtUp()
{
  if (Controller::m_state != nullptr) {
    Controller::m_state->handleBtUp();
  }
}

void Controller::taskRenderScreen(void *pvParameters)
{
  while (1) {
    Controller::m_state->getScreen()->draw();
    vTaskDelay(pdMS_TO_TICKS(200));
  }
  vTaskDelete(nullptr);
}

void Controller::taskReadTermistor(void *pvParameters)
{
  while(1) {
    digitalWrite(TERMISTOR_ON, HIGH);
    vTaskDelay(pdMS_TO_TICKS(50));

    Parameters::set()->setT1(Controller::t1.getTemp());
    Parameters::set()->setT2(Controller::t2.getTemp());
    Parameters::set()->setValueT1(Controller::t1.getValue());
    Parameters::set()->setValueT2(Controller::t2.getValue());
    digitalWrite(TERMISTOR_ON, LOW);

    vTaskDelay(pdMS_TO_TICKS(450));
  }
  vTaskDelete(nullptr);
}


Button Controller::btnDown(BTN_DOWN);
Button Controller::btnOkMenu(BTN_OK_MENU);
Button Controller::btnUp(BTN_UP);

Led Controller::ledCold(LED_COLD);
Led Controller::ledLock(LED_LOCK);
Led Controller::ledEco(LED_ECO);
Led Controller::ledComfort(LED_COMFORT);
Led Controller::ledHeat(LED_HEAT);

State *Controller::m_state{nullptr};
TaskHandle_t Controller::m_taskHandle{nullptr};
TaskHandle_t Controller::m_taskReadTemp{nullptr};
Heater *Controller::m_heater{nullptr}; 
    
Termistor Controller::t1(TERMISTOR1);
Termistor Controller::t2(TERMISTOR2);

