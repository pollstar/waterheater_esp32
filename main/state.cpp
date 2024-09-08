#include "state.h"
#include "controller.h"
#include "parameters.h"

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
  m_screen = new ScreenMain();
  // Controller::ledHeat.on();
}

StateMainHeat::~StateMainHeat()
{
}

void StateMainHeat::handleBtDown()
{
  Controller::setState(new Statetemp());
}

void StateMainHeat::handleBtOkMenu()
{
  Controller::setState(new StateSelectMode());
}

void StateMainHeat::handleBtUp()
{
  Controller::setState(new Statetemp());
}

//--------------------------------------------------
Statetemp::Statetemp()
{
  m_screen = new ScreenSetTemp();
}

Statetemp::~Statetemp()
{
  // Controller::ledHeat.off();
}

void Statetemp::handleBtDown()
{
  Parameters::set()->temp(Parameters::get()->temp() - 1);
}

void Statetemp::handleBtOkMenu()
{
  Controller::setState(new StateMainHeat());
}

void Statetemp::handleBtUp()
{
  Parameters::set()->temp(Parameters::get()->temp() + 1);
}
//------------------------------------------------------
StateSelectMode::StateSelectMode()
{
  m_screen = new ScreenSelectMode();
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
  Controller::setState(new StateDiagMode());
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
  Controller::setState(new StateMainHeat());
}

void StateDiagMode::handleBtUp()
{
  m_currentScreen++;
  m_screen = StateDiagMode::m_screens[m_currentScreen%2];
}

std::array<Screen*, 2> StateDiagMode::m_screens = {new ScreenDiag1(), new ScreenDiag2()};


