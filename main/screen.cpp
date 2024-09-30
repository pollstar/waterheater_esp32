#include "screen.h"
#include "parameters.h"
#include "controller.h"

Screen::Screen() {
  // if (Parameters::get()->tft() == nullptr) {
  //   return;
  // }

  // m_face = new TFT_eSprite(Parameters::get()->tft());
  // m_face.createSprite(180, 110);
};

 Screen::~Screen() {
  // if (m_face != nullptr) {
  //   delete m_face;
  // }
};

//----------------------------------------------------------

void ScreenMain::draw()
{
  if (Parameters::get()->tft() == nullptr) {
    return;
  }

  TFT_eSprite m_face{TFT_eSprite(Parameters::get()->tft())};
  
  // if (m_face == nullptr)
  // {
  //   return;
  // }

  m_face.createSprite(180, 110);
  m_face.fillScreen(TFT_BLACK);
  m_face.setTextColor(TFT_WHITE,TFT_BLACK); 

  char buff[30];
      
  snprintf(buff, 30, "%d", Parameters::get()->getT1());
  m_face.setTextSize(2); 
  int16_t w = m_face.textWidth(buff, 7);
  int16_t h = m_face.fontHeight(7);

  m_face.drawString (buff, (180-w)/2, (110-h)/2, 7);

  m_face.pushSprite(20, 0);
}

//----------------------------------------------------------

void ScreenSetTemp::draw()
{
  if (Parameters::get()->tft() == nullptr) {
    return;
  }

  TFT_eSprite m_face {TFT_eSprite(Parameters::get()->tft())};
  
  m_face.createSprite(180, 110);
  m_face.setTextColor(TFT_RED,TFT_YELLOW); 

  m_face.fillRect(0, 0, 180, 109, TFT_YELLOW);

  char buff[30];
      
  snprintf(buff, 30, "%d", Parameters::get()->temp());
  m_face.setTextSize(2); 
  int16_t w = m_face.textWidth(buff, 6);
  m_face.drawString (buff, (180-w)/2, 0, 6);

  m_face.setTextSize(2); 
  snprintf(buff, 30, "SET TEMP", w); 
  w = m_face.textWidth(buff, 2);
  int16_t h = m_face.fontHeight(2);
  m_face.drawString (buff, (180-w)/2, 109-h, 2);

  m_face.pushSprite(20, 0);
}
//-----------------------------------------------------------

void ScreenSelectMode::draw()
{
  
  if (Parameters::get()->tft() == nullptr) {
    return;
  }

  TFT_eSprite m_face{TFT_eSprite(Parameters::get()->tft())};
  
  m_face.createSprite(180, 110);
  m_face.fillRect(0, 0, 180, 109, TFT_WHITE);
  m_face.setTextColor(TFT_BLUE,TFT_WHITE); 

  char buff[30];
      
  snprintf(buff, 30, "%d", Parameters::get()->mode()->temp());
  m_face.setTextSize(2); 
  int16_t w = m_face.textWidth(buff, 6);
  m_face.drawString (buff, (180-w)/2, 0, 6);

  m_face.setTextSize(2); 
  constexpr int8_t font = 4;
  snprintf(buff, 30, "%s", Parameters::get()->mode()->name()); 
  w = m_face.textWidth(buff, font);
  int16_t h = m_face.fontHeight(font);
  m_face.drawString (buff, (180-w)/2, 73, font);

  m_face.pushSprite(20, 0);
  
}
//----------------------------------------------------

void ScreenDiag1::draw()
{
  if (Parameters::get()->tft() == nullptr) {
    return;
  }

  TFT_eSprite m_face{TFT_eSprite(Parameters::get()->tft())};
  
  m_face.createSprite(180, 110);
  m_face.fillRect(0, 0, 180, 109, TFT_BLUE);
  m_face.setTextColor(TFT_GREEN,TFT_BLUE); 

  char buff[30];
  
  m_face.setTextSize(1); 
  constexpr int8_t font = 4;
  m_face.setTextFont(font);

  snprintf(buff, 30, " t1 = %d", Parameters::get()->getT1()); 
  m_face.println(buff);
  snprintf(buff, 30, " t2 = %d", Parameters::get()->getT2()); 
  m_face.println(buff);
  snprintf(buff, 30, " v1 = %d", Parameters::get()->getValueT1()); 
  m_face.println(buff);
  snprintf(buff, 30, " v2 = %d", Parameters::get()->getValueT2()); 
  m_face.println(buff);
    
  m_face.pushSprite(20, 0);
  }
//----------------------------------------------------

void ScreenDiag2::draw()
{
    if (Parameters::get()->tft() == nullptr) {
    return;
  }

  TFT_eSprite m_face{TFT_eSprite(Parameters::get()->tft())};
  
  m_face.createSprite(180, 110);
  m_face.fillRect(0, 0, 180, 109, TFT_BLUE);
  m_face.setTextColor(TFT_GREEN,TFT_BLUE); 

  char buff[30];
  
  m_face.setTextSize(1); 
  constexpr int8_t font = 4;
  m_face.setTextFont(font);

  snprintf(buff, 30, " t1 = %d", Parameters::get()->getT1()); 
  m_face.println(buff);
  snprintf(buff, 30, " t2 = %d", Parameters::get()->getT2()); 
  m_face.println(buff);
  snprintf(buff, 30, " v1 = %d", Parameters::get()->getValueT1()); 
  m_face.println(buff);
  snprintf(buff, 30, " v2 = %d", Parameters::get()->getValueT2()); 
  m_face.println(buff);
    
  m_face.pushSprite(20, 0);
}