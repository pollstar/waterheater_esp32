#pragma once
#include <TFT_eSPI.h> // Hardware-specific library
#include <functional>

class Screen {
  public:
    virtual void draw() = 0;
  protected:
    bool checkTft();
    TFT_eSPI *m_tft {nullptr};
};

class ScreenMain: public Screen
{
  public:
    void draw() override;
};

class ScreenSetTemp: public Screen
{
  public:
    void draw() override;
};

class ScreenSelectMode: public Screen
{
  public:
    void draw() override;
};

class ScreenDiag1: public Screen
{
  public:
    void draw() override;
};

class ScreenDiag2: public Screen
{
  public:
    void draw() override;
};