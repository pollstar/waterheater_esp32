#include "termistor.h"
#include <vector>

std::vector<std::pair<int, int>> convertTable = { 
    {440,0},    {550,5},    {650,10},   {790,15},
    {990,20},   {1150,25},  {1360,30},  {1600,35},
    {1790,40},  {1970,45},  {2180,50},  {2380,55},
    {2560,60},  {2700,65},  {2870,70},  {2980,75},
    {3120,80},  {3250,85},  {3380,90},  {3480,95},
    {3595,100}
};

#define ERROR_VALUE_TEMP 0

Termistor::Termistor(uint8_t pin) :
  m_pin(pin)
{
  pinMode(m_pin, INPUT);
//  adcAttachPin(m_pin);
//  analogSetPinAttenuation(m_pin, ADC_0db);
}

int Termistor::getValue()
{
  // Serial.printf("Read pin %d\n", m_pin);
  return analogRead(m_pin) + ERROR_VALUE_TEMP;
}

int Termistor::getValue(int v)
{
  return v;
}

float Termistor::getTemp()
{
  int value = this->getValue();

  if (value < convertTable[0].first || value > convertTable[convertTable.size() - 1].first)
  {
     return -200.00f;
  }

  for(auto i = convertTable.size()-2; i >= 0; --i)
  {
    if (value > convertTable[i].first)
    {
      float v1 = convertTable[i].first;
      float v2 = convertTable[i+1].first;
      float t1 = convertTable[i].second;
      float t2 = convertTable[i+1].second;
      return (float)(t1+(value-v1)*(t2-t1)/(v2-v1));
    }
  }
}
