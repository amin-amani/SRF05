#ifndef __SRF05_H__
#define __SRF05_H__
#include "stdint.h"
#include "math.h"
typedef struct 
{
void (*SetEchoPinInput)(void);
void (*SetTriggerPinOutput)(void);
void (*SetTriggerPin)(int value);
void (*delay)(int ms);
void (*delayMicroseconds)(int us);
uint32_t (*GetEchoPulseDuratin)(int timeout);
}SRF05_t;

void SRF05Init(SRF05_t srf);
#endif