#pragma once
#include <TFT_eSPI.h> // Hardware-specific library
#include <functional>

class Screen {
  public:
    virtual void draw(TFT_eSprite *face) = 0;
};

class ScreenMain: public Screen
{
  public:
    void draw(TFT_eSprite *face) override;
};

class ScreenSetTemp: public Screen
{
  public:
    void draw(TFT_eSprite *face) override;
};

class ScreenSelectMode: public Screen
{
  public:
    void draw(TFT_eSprite *face) override;
};

class ScreenDiag1: public Screen
{
  public:
    void draw(TFT_eSprite *face) override;

};

class ScreenDiag2: public Screen
{
  public:
    void draw(TFT_eSprite *face) override;
};