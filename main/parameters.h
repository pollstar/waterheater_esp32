#pragma once

#include <TFT_eSPI.h> // Hardware-specific library
#include <array>
#include "controller.h"
#include "mode.h"

class Screen;

enum ModeEnum {
  INDEX_MODE_COLD,
  INDEX_MODE_ECO,
  INDEX_MODE_NORMAL,
  INDEX_MODE_MAX
};

extern std::array<Mode*, INDEX_MODE_MAX> modes;

class Parameters {
  public:
    Parameters(const Parameters&) = delete;
    Parameters& operator=(const Parameters&) = delete;

    static Parameters* get()
    {
      return getInstance();
    };

    static Parameters* set()
    {
      return getInstance();
    };

    inline int getT1() const {return m_t1;};
    inline int getT2() const {return m_t2;};
    inline int getValueT1() const {return m_t1Value;};
    inline int getValueT2() const {return m_t2Value;};

    inline void setT1(int t) {m_t1 = t;};
    inline void setT2(int t) {m_t2 = t;};
    inline void setValueT1(int t) {m_t1Value = t;};
    inline void setValueT2(int t) {m_t2Value = t;};
  
    int temp() const;
    int temp(int t);

    int diff() const;
    int diff(int diff);

    Screen* screen() const;
    Screen* screen(Screen* screen);
  
    TFT_eSprite* face() const;
    TFT_eSprite* face(TFT_eSprite *face);

    Mode* mode() const;
    Mode* mode(Mode *mode);

    void saveParameters(void);
    void loadParameters(void);

  private:
    Parameters();

    static Parameters* getInstance()
    {
      static Parameters m_instance;
      return &m_instance;
    };

    int m_t1;
    int m_t2;
    int m_t1Value;
    int m_t2Value;

    Mode* m_currentMode;

    Screen *m_currentScreen = nullptr;
    TFT_eSprite *m_face{nullptr};

};

