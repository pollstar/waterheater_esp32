#include "parameters.h"
#include <EEPROM.h>

std::array<Mode*, INDEX_MODE_MAX> modes = {new ModeCold(), new ModeEco(), new ModeNormal()};
//Parameters Parameters::m_instance;

Parameters::Parameters() {
  this->loadParameters();
};

int Parameters::temp() const
{
  if (m_currentMode)
    return m_currentMode->temp();
  return 0;
};

int Parameters::temp(int t) 
{
  if (m_currentMode) {
    m_currentMode->temp(t);
    this->saveParameters();
    return m_currentMode->temp();
  }
  return 0;
};

int Parameters::diff() const 
{ 
  if (m_currentMode)
    return m_currentMode->diff(); 
  return 0;
};

int Parameters::diff(int diff)
{
  if (m_currentMode)
    return m_currentMode->diff(diff);
  return 0; 
};

Screen* Parameters::screen() const 
{
  return m_currentScreen;
};

Screen* Parameters::screen(Screen* screen) {
  m_currentScreen = screen;
  return m_currentScreen;
};
  
TFT_eSprite* Parameters::face() const {
  return m_face;
};

TFT_eSprite* Parameters::face(TFT_eSprite *face) {
  m_face = face;
  return m_face;
};

Mode* Parameters::mode() const {
  return m_currentMode;
};

Mode* Parameters::mode(Mode *mode)
{
  if (m_currentMode) 
    m_currentMode->led()->off();
  
  m_currentMode = mode;
  
  if (m_currentMode) {
    m_currentMode->led()->on();
    this->saveParameters();
    //Parameters::set()->temp(m_currentMode->temp());
  }

  return m_currentMode;
};

void Parameters::saveParameters(void) {
  uint8_t indexCurrentMode = 0;
  uint8_t temp;

  for (auto const mode: modes) {
    if (mode == m_currentMode) {
      break;
    }
    indexCurrentMode++;
  }

  if (indexCurrentMode >= INDEX_MODE_MAX) 
    indexCurrentMode = INDEX_MODE_NORMAL;

  temp = modes[INDEX_MODE_NORMAL]->temp();

  EEPROM.begin(2);
  EEPROM.write(0, indexCurrentMode);
  EEPROM.write(1, temp);
  EEPROM.commit();
  EEPROM.end();
};

void Parameters::loadParameters(void) {
  EEPROM.begin(2);
  uint8_t indexMode = EEPROM.read(0);
  uint8_t temp  = EEPROM.read(1);
  EEPROM.end();

  if (indexMode >= INDEX_MODE_MAX) {
    indexMode = INDEX_MODE_NORMAL;
  }

  if (temp < 20 || temp > 90) {
    temp = 40;
  }

  if (!modes.empty()) {
    this->mode(modes[indexMode]);
    modes[INDEX_MODE_NORMAL]->temp(temp);
  }
  else
    m_currentMode = nullptr;

};
