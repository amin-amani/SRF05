#ifndef __SRF05_H__
#define __SRF05_H__
#include "stdint.h"
#include "math.h"

void SRF05Init(const uint8_t trigger, const uint8_t echo, const uint8_t out);
#endif