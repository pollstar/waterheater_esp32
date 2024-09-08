#pragma once

#include <array>
#include "screen.h"
#include "button.h"

class State
{
  public:
    virtual ~State();

    virtual void handleBtDown() = 0;
    virtual void handleBtOkMenu() = 0;
    virtual void handleBtUp() = 0;
    
    inline Screen* getScreen() {return m_screen;};

  protected:
    Screen *m_screen;
};

class StateMainHeat : public State
{
  public:
    StateMainHeat();
    ~StateMainHeat() override;

    void handleBtDown() override;
    void handleBtOkMenu() override;
    void handleBtUp() override;
};

class Statetemp : public State
{
  public:
    Statetemp();
    ~Statetemp() override;

    void handleBtDown() override;
    void handleBtOkMenu() override;
    void handleBtUp() override;
};

class StateSelectMode : public State
{
  public:
    StateSelectMode();
    ~StateSelectMode() override;

    void handleBtDown() override;
    void handleBtOkMenu() override;
    void handleBtUp() override;
};

class StateDiagMode : public State
{
  public:
    StateDiagMode();
    ~StateDiagMode() override;

    void handleBtDown() override;
    void handleBtOkMenu() override;
    void handleBtUp() override;
  private:
    static std::array<Screen*, 2> m_screens;
    uint8_t m_currentScreen = 0;

};