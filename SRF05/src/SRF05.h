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
void (*delayMicroseconds)(uint32_t us);
uint64_t (*GetEchoPulseDuratin)(uint64_t timeout);
}SRF05_t;
void setCorrectionFactor(float factor ) ;
float getMeter();
void SRF05Init(SRF05_t srf);
#endif