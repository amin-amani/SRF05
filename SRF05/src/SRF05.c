#include "SRF05.h"
static uint8_t _trigger = 0;
static uint8_t _echo = 0;
static uint8_t _out = 0;
static uint8_t _mode = 0;


  static uint8_t  _count = 1;
  static float    _alpha = 1.0;
  static float    _value = 0;
  static float    _correctionFactor = 1;
  static uint8_t  _triggerLength    = 10;
  static float    _speedOfSound     = 340; 

void (*SetEchoPinInput)(void);
void (*SetTriggerPinOutput)(void);
void (*SetTriggerPin)(int value);
void (*delay)(int ms);
void (*delayMicroseconds)(int us);
void SRF05Init(const uint8_t trigger, const uint8_t echo, const uint8_t out)
{
    _trigger = trigger;
    _echo = echo;
    _out = out;
    _mode = 0;
    SetEchoPinInput();
    SetTriggerPinOutput();
    SetTriggerPin(1);

    // pinMode(_trigger, OUTPUT);
    // digitalWrite(_trigger, LOW);
    // pinMode(_echo, INPUT);
}
void setSpeedOfSound(float sos)
{
  _speedOfSound = sos;
}
float getSpeedOfSound()
{
  return _speedOfSound;
}

//////////////////////////////////////////////////

void setModeSingle()
{
  _mode  = 0x00;
  _count = 1;
}


void setModeAverage(uint8_t count)
{
  _mode  = 0x01;
  _count = count;
}


void setModeMedian(uint8_t count)
{
  _mode  = 0x02;
  _count = count;
  if (_count < 3)  _count = 3;
  if (_count > 15) _count = 15;
}


void setModeRunningAverage(float alpha)
{
  _mode  = 0x03;
  _count = 1;
  _alpha = alpha;
}


uint8_t getOperationalMode()
{
  return _mode;
}

uint32_t _read()
{
  SetTriggerPin(1);
  delayMicroseconds(_triggerLength);
   SetTriggerPin(0);
   uint32_t duration =2;
 //#TODO  what is pulse in func
 // uint32_t duration = pulseIn(_echo, 1, 300000);
  if (_correctionFactor == 1)
  {
     return duration;
  }
  return round(duration * _correctionFactor);
}


void _insertSort(uint32_t * array, uint8_t size)
{
  uint8_t t, z;
  uint32_t temp;
  for (t = 1; t < size; t++) 
  {
    z = t;
    temp = array[z];
    while( (z > 0) && (temp < array[z - 1] )) 
    {
      array[z] = array[z - 1];
      z--;
    }
    array[z] = temp;
    //#todo what is yield
    // yield();
  }
}
//////////////////////////////////////////////////

uint32_t getTime()
{
  switch(_mode)
  {
    default:
    case 0x00:
      return _read();

    case 0x01:
    {
      float sum = 0;
      for (uint8_t s = 0; s < _count; s++)
      {
        sum += _read();
        delay(1);
      }
      return round(sum / _count);
    }
    case 0x02:
    {
      uint32_t samples[15];
      for (uint8_t s = 0; s < _count; s++)
      {
        samples[s] = _read();
        delay(1);
      }
      _insertSort(samples, _count);
      if (_count & 0x01) return samples[_count / 2];
      return (samples[(_count + 1) / 2] + samples[_count / 2]) / 2;
    }
    case 0x03:
      _value = (1 - _alpha) * _value + _alpha * _read();
      return _value;
  }
}


uint32_t getMillimeter()
{
  return _speedOfSound * getTime() * 0.5e-3;
}


float getCentimeter()
{
  return _speedOfSound * getTime() * 0.5e-4;
}


float getMeter()
{
  return _speedOfSound * getTime() * 0.5e-6;
}


float getInch()
{
  return _speedOfSound * getTime() * 1.9685e-5;
}


float getFeet()
{
  return _speedOfSound * getTime() * 1.64042e-6;
}


// assumes a distance of 1.00 meter
// typically use 100 or 500 meter for distance to calibrate
float determineSpeedOfSound(uint16_t distance)
{
  float sum = 0;
  for (uint16_t i = 0; i < distance; i++)
  {
    sum += _read();
    delay(1);
  }
  float sos = 2e6 * distance / sum;
  return sos;
}
