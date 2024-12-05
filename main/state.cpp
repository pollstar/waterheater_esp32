#include "state.h"
#include "controller.h"
#include "parameters.h"
#include "screen.h"

#define FILL_BTN_DOWN_PRESS     TFT_WHITE 
#define FILL_BTN_OK_MENU_PRESS  TFT_PINK
#define FILL_BTN_UP_PRESS       TFT_BLUE
#define FILL_UNPRESS            TFT_GREEN

class Controller;

State::~State()
{
  if (m_screen != nullptr) {
    delete m_screen;
  }
}

StateMainHeat::StateMainHeat()
{
  m_screen = &screenMain;
  // Controller::ledHeat.on();
}

StateMainHeat::~StateMainHeat()
{
}

void StateMainHeat::handleBtDown()
{
  Controller::setState(&stateTemp);
}

void StateMainHeat::handleBtOkMenu()
{
  Controller::setState(&stateSelectMode);
}

void StateMainHeat::handleBtUp()
{
  Controller::setState(&stateTemp);
}

//--------------------------------------------------
StateTemp::StateTemp()
{
  m_screen = &screenSetTemp;
}

StateTemp::~StateTemp()
{
  // Controller::ledHeat.off();
}

void StateTemp::handleBtDown()
{
  Parameters::set()->temp(Parameters::get()->temp() - 1);
}

void StateTemp::handleBtOkMenu()
{
  Controller::setState(&stateMainHeat);
}

void StateTemp::handleBtUp()
{
  Parameters::set()->temp(Parameters::get()->temp() + 1);
}
//------------------------------------------------------
StateSelectMode::StateSelectMode()
{
  m_screen = &screenSelectMode;
}

StateSelectMode::~StateSelectMode()
{
  // Controller::ledHeat.off();
}

void StateSelectMode::handleBtDown()
{
  for (auto i = 0; i < modes.size(); ++i)
  {
    if (Parameters::get()->mode() == modes[i])
    {
      i = i < modes.size() - 1 ? i + 1 : 0;
      Parameters::set()->mode(modes[i]);
      break;
    }
  }
}

void StateSelectMode::handleBtOkMenu()
{
  Controller::setState(&stateDiagMode);
}

void StateSelectMode::handleBtUp()
{
  for (auto i = 0; i < modes.size(); ++i)
  {
    if (Parameters::get()->mode() == modes[i])
    {
      i = i > 0 ? i - 1 : modes.size() - 1;
      Parameters::set()->mode(modes[i]);
      break;
    }
  }
}

//------------------------------------------------------
StateDiagMode::StateDiagMode()
{
  m_screen = StateDiagMode::m_screens[m_currentScreen%2];
}

StateDiagMode::~StateDiagMode()
{
  // Controller::ledHeat.off();
}

void StateDiagMode::handleBtDown()
{
  m_currentScreen--;
  m_screen = StateDiagMode::m_screens[m_currentScreen%2];
}

void StateDiagMode::handleBtOkMenu()
{
  Controller::setState(&stateMainHeat);
}

void StateDiagMode::handleBtUp()
{
  m_currentScreen++;
  m_screen = StateDiagMode::m_screens[m_currentScreen%2];
}

std::array<Screen*, 2> StateDiagMode::m_screens =  {&screenDiag1, &screenDiag2};

StateMainHeat stateMainHeat;
StateSelectMode stateSelectMode;
StateDiagMode stateDiagMode;
StateTemp stateTemp;

