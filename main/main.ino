#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library

#include "parameters.h"
#include "screen.h"
#include "controller.h"

TFT_eSPI tft = TFT_eSPI();

void setup() {

  Serial.begin(115200);
  Serial.println("Begin");

  tft.init();
  tft.setRotation(1);

  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);

  Parameters::set()->tft(&tft);
  Controller::run(&stateMainHeat);
}

void loop() {
}
