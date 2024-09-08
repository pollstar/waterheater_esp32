#pragma once

#include "state.h"
#include "button.h"
#include "led.h"
#include "heater.h"
#include "termistor.h"

class Controller 
{
  public:
    static void run(State *state);
    static void stop();
    static void setState(State *state);

    static Button btnDown;
    static Button btnOkMenu;
    static Button btnUp;

    static Led ledCold;
    static Led ledLock;
    static Led ledEco;
    static Led ledComfort;
    static Led ledHeat;
  private:
    Controller() = delete;
    Controller(Controller &) = delete;
    void operator=(const Controller &) = delete;

    static void handleBtDown();
    static void handleBtOkMenu();
    static void handleBtUp();

    static Termistor t1;
    static Termistor t2;

    static void taskRenderScreen(void *pvParameters);
    static void taskReadTermistor(void *pvParameters);

    static Heater* m_heater; 

    static State *m_state;
    static TaskHandle_t m_taskHandle;
    static TaskHandle_t m_taskReadTemp;
};
