#include "screen.h"
#include "parameters.h"
#include "controller.h"

bool Screen::checkFace()
{
  if (this->m_face == nullptr) {
    this->m_face = Parameters::get()->face();
  }

  return this->m_face != nullptr;
}

//----------------------------------------------------------

void ScreenMain::draw()
{
  if (!Screen::checkFace()) {
    return;
  }

  this->m_face->createSprite(240, 135);
  this->m_face->setTextColor(TFT_WHITE,TFT_BLACK); 
  this->m_face->setTextSize(2);
  
  char buff[30];
  
  this->m_face->fillSprite(TFT_GREEN);
  this->m_face->setCursor(3, 3, 2);
    
  this->m_face->setTextColor(TFT_WHITE,TFT_BLUE); 

  snprintf(buff, 30, " t = %d C", Parameters::get()->getT1()); 
  this->m_face->println(buff);

  snprintf(buff, 30, " set = %d C", Parameters::get()->mode()->temp()); 
  this->m_face->println(buff);

  this->m_face->pushSprite(0, 0, TFT_TRANSPARENT);
}

//----------------------------------------------------------

void ScreenSetTemp::draw()
{
  if (!Screen::checkFace()) {
    return;
  }

  this->m_face->createSprite(240, 135);
  this->m_face->setTextColor(TFT_WHITE,TFT_BLACK); 
  this->m_face->setTextSize(2);
  
  char buff[30];
  
  this->m_face->fillSprite(TFT_BLUE);
  this->m_face->setCursor(3, 3, 2);
    
  this->m_face->setTextColor(TFT_WHITE,TFT_BLUE); 
  snprintf(buff, 30, " t1 = %d", Parameters::get()->temp()); 
  this->m_face->println(buff);
  
  this->m_face->pushSprite(0, 0, TFT_TRANSPARENT);}
//-----------------------------------------------------------

void ScreenSelectMode::draw()
{
  if (!Screen::checkFace()) {
    return;
  }

  this->m_face->createSprite(240, 135);
  this->m_face->setTextColor(TFT_WHITE,TFT_BLACK); 
  this->m_face->setTextSize(2);
  
  char buff[30];
  
  this->m_face->fillSprite(TFT_RED);
  this->m_face->setCursor(3, 3, 2);
    
  this->m_face->setTextColor(TFT_WHITE,TFT_RED); 
  this->m_face->println("MODE:");

  auto currentMode = Parameters::get()->mode();
  
  for(const auto mode : modes) {
    if (mode == nullptr)
      continue;

    if (mode == currentMode)
    {
      this->m_face->setTextColor(TFT_RED,TFT_WHITE); 
    }
    else
    {
      this->m_face->setTextColor(TFT_WHITE,TFT_RED); 
    }
    this->m_face->println(mode->name());
  }
  
  this->m_face->pushSprite(0, 0, TFT_TRANSPARENT); 
}
//----------------------------------------------------

void ScreenDiag1::draw()
{
  if (!Screen::checkFace()) {
    return;
  }

  this->m_face->createSprite(240, 135);
  this->m_face->setTextColor(TFT_WHITE,TFT_BLACK); 
  this->m_face->setTextSize(2);
  
  char buff[30];
  
  this->m_face->fillSprite(TFT_GREEN);
  this->m_face->setCursor(3, 3, 2);
    
  this->m_face->setTextColor(TFT_WHITE,TFT_BLUE); 

  snprintf(buff, 30, " t1 = %d", Parameters::get()->getT1()); 
  this->m_face->println(buff);
  snprintf(buff, 30, " t1 value = %d", Parameters::get()->getValueT1()); 
  this->m_face->println(buff);
  
  snprintf(buff, 30, " t2 = %d", Parameters::get()->getT2()); 
  this->m_face->println(buff);
  snprintf(buff, 30, " t2 value = %d", Parameters::get()->getValueT2()); 
  this->m_face->println(buff);

  this->m_face->pushSprite(0, 0, TFT_TRANSPARENT);
}
//----------------------------------------------------

void ScreenDiag2::draw()
{
  if (!Screen::checkFace()) {
    return;
  }

  this->m_face->createSprite(240, 135);
  this->m_face->setTextColor(TFT_WHITE,TFT_BLACK); 
  this->m_face->setTextSize(2);
  
  char buff[30];
  
  this->m_face->fillSprite(TFT_PINK);
  this->m_face->setCursor(3, 3, 2);
    
  this->m_face->setTextColor(TFT_BLACK,TFT_PINK); 

  snprintf(buff, 30, " DIAG2", Parameters::get()->getT2()); 
  this->m_face->println(buff);

  this->m_face->pushSprite(0, 0, TFT_TRANSPARENT);
}