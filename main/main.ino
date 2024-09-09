#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library

#include "parameters.h"
#include "screen.h"
#include "controller.h"


int t1Temp, t2Temp;
int t1Value;

uint32_t current_fill = TFT_GREEN;

TFT_eSPI tft = TFT_eSPI();  
TFT_eSprite face = TFT_eSprite(&tft);



void setup() {
  tft.init();
  tft.setRotation(1);

  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);
 
  Parameters::set()->face(&face);
  Controller::run(new StateMainHeat());
}

void loop() {
  // put your main code here, to run repeatedly:

}
