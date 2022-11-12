#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "driver/uart.h"
#include "driver/adc.h"
#include "esp_log.h"
#include "esp_adc_cal.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "SRF05.h"

#define BLINK_GPIO 2
#define ECHO  13
#define TRIGGER 12 
const uint8_t dummy;
//==============================================================================================
void GPIOInit()
{
    gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

}
//==============================================================================================
void DelayMs(int ms)
{
vTaskDelay(ms / portTICK_PERIOD_MS);

}
//==============================================================================================

void DelayUs(uint32_t us)
{
    esp_rom_delay_us(us);
}
//==============================================================================================
uint64_t  GetEchoPulseDuration(uint64_t usTimeout)
{
 uint64_t microseconds=0;
  uint64_t startTime=esp_timer_get_time();
 while(gpio_get_level(ECHO)==1)
 {

if((esp_timer_get_time()-startTime)>usTimeout)
return usTimeout;
 }
while(gpio_get_level(ECHO)==0)
{
if((esp_timer_get_time()-startTime)>usTimeout)
return usTimeout;
}
 microseconds = (uint64_t)esp_timer_get_time();
while(gpio_get_level(ECHO)==1)
{
    if((esp_timer_get_time()-startTime)>usTimeout)
return usTimeout;
}
return (esp_timer_get_time() - microseconds);
}
//==============================================================================================
void SetTriggerPin(int value)
{
 gpio_set_level(TRIGGER, value);
}
//==============================================================================================

void SetTriggerPinAsOutput()
{
    
    gpio_pad_select_gpio(TRIGGER);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(TRIGGER, GPIO_MODE_OUTPUT);


}
void SetEchoPinInput()
{

        gpio_config_t io_conf = {};
   //interrupt of rising edge
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //bit mask of the pins, use GPIO4/5 here
    io_conf.pin_bit_mask = ECHO;
    //set as input mode
    io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
}
void app_main() 
{


SRF05_t srf05;
srf05.delay=DelayMs;
srf05.delayMicroseconds=DelayUs;
srf05.GetEchoPulseDuratin=GetEchoPulseDuration;
srf05.SetTriggerPin=SetTriggerPin;
srf05.SetTriggerPinOutput=SetTriggerPinAsOutput;
srf05.SetEchoPinInput=SetEchoPinInput;

SRF05Init(srf05);
GPIOInit();
  setCorrectionFactor(1.035);
while (true)
{
    printf("d=%f\n", getMeter());
    gpio_set_level(BLINK_GPIO, 0);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    gpio_set_level(BLINK_GPIO, 1);
     vTaskDelay(300 / portTICK_PERIOD_MS);
}


}