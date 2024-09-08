#pragma once

#include "led.h"

constexpr int m_minTemp = 20;
constexpr int m_maxTemp = 80;

class Mode
{
  public:
    virtual int temp() const { return m_temp; };
    virtual int temp(int t) { return m_temp; };

    inline int diff() { return m_tDiff; };
    inline int diff(int diff) {
      m_tDiff = diff; 
      return m_tDiff; 
    };

    inline char *name() const {return m_name;};
    inline Led *led() const {return m_led;}

  private:
  protected:
    Mode() {};
    int m_tDiff = 1;
    int m_temp;
    char *m_name;
    Led *m_led;
};

class ModeNormal : public Mode
{
  public:
    ModeNormal()
    {
      m_name = "normal";
      m_led = &Controller::ledComfort;
      m_temp = 45;
    };

    int temp(int t) override 
    {
      if (t >= m_minTemp && t <= m_maxTemp) {
        m_temp = t;
      }
      return m_temp;
    }
};

class ModeCold : public Mode
{
  public:
    ModeCold()
    {
      m_name = "cold";
      m_led = &Controller::ledCold;
      m_temp = 7;
    };
};

class ModeEco : public Mode
{
  public:
    ModeEco()
    {
      m_name = "eco";
      m_led = &Controller::ledEco;
      m_temp = 50;
    };
};