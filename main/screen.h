#pragma once
#include <TFT_eSPI.h> // Hardware-specific library
#include <functional>

class Screen {
  public:
    Screen();
    ~Screen();

    virtual void draw() = 0;
  protected:
    TFT_eSprite *m_face {nullptr};
};

class ScreenMain: public Screen
{
  public:
    // ScreenMain() : Screen() {};
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

extern ScreenMain screenMain;
extern ScreenSetTemp screenSetTemp;
extern ScreenSelectMode screenSelectMode;
extern ScreenDiag1 screenDiag1;
extern ScreenDiag2 screenDiag2;