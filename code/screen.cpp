#include "screen.h"
#include "parameters.h"
#include "controller.h"

void ScreenMain::draw(TFT_eSprite *face) 
{
  char buff[30];
  
  face->fillSprite(TFT_GREEN);
  face->setCursor(3, 3, 2);
    
  face->setTextColor(TFT_WHITE,TFT_BLUE); 

  snprintf(buff, 30, " t = %d C", Parameters::get()->getT1()); 
  face->println(buff);

  snprintf(buff, 30, " set = %d C", Parameters::get()->mode()->temp()); 
  face->println(buff);

  face->pushSprite(0, 0, TFT_TRANSPARENT);
}

//----------------------------------------------------------

void ScreenSetTemp::draw(TFT_eSprite *face) 
{
  char buff[30];
  
  face->fillSprite(TFT_BLUE);
  face->setCursor(3, 3, 2);
    
  face->setTextColor(TFT_WHITE,TFT_BLUE); 
  snprintf(buff, 30, " t1 = %d", Parameters::get()->temp()); 
  face->println(buff);
  
  face->pushSprite(0, 0, TFT_TRANSPARENT);
}

//-----------------------------------------------------------

void ScreenSelectMode::draw(TFT_eSprite *face)
{
  char buff[30];
  
  face->fillSprite(TFT_RED);
  face->setCursor(3, 3, 2);
    
  face->setTextColor(TFT_WHITE,TFT_RED); 
  face->println("MODE:");

  auto currentMode = Parameters::get()->mode();
  
  for(const auto mode : modes) {
    if (mode == nullptr)
      continue;

    if (mode == currentMode)
    {
      face->setTextColor(TFT_RED,TFT_WHITE); 
    }
    else
    {
      face->setTextColor(TFT_WHITE,TFT_RED); 
    }
    face->println(mode->name());
  }
  
  face->pushSprite(0, 0, TFT_TRANSPARENT); 
}

//----------------------------------------------------

void ScreenDiag1::draw(TFT_eSprite *face) 
{
  char buff[30];
  
  face->fillSprite(TFT_GREEN);
  face->setCursor(3, 3, 2);
    
  face->setTextColor(TFT_WHITE,TFT_BLUE); 

  snprintf(buff, 30, " t1 = %d", Parameters::get()->getT1()); 
  face->println(buff);
  snprintf(buff, 30, " t1 value = %d", Parameters::get()->getValueT1()); 
  face->println(buff);
  
  snprintf(buff, 30, " t2 = %d", Parameters::get()->getT2()); 
  face->println(buff);
  snprintf(buff, 30, " t2 value = %d", Parameters::get()->getValueT2()); 
  face->println(buff);

  face->pushSprite(0, 0, TFT_TRANSPARENT);
}

//----------------------------------------------------

void ScreenDiag2::draw(TFT_eSprite *face) 
{
  char buff[30];
  
  face->fillSprite(TFT_PINK);
  face->setCursor(3, 3, 2);
    
  face->setTextColor(TFT_BLACK,TFT_PINK); 

  snprintf(buff, 30, " DIAG2", Parameters::get()->getT2()); 
  face->println(buff);

  face->pushSprite(0, 0, TFT_TRANSPARENT);
}