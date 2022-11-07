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
const uint8_t dummy;
void GPIOInit()
{
//         gpio_config_t io_conf = {};
//    //interrupt of rising edge
//     io_conf.intr_type = GPIO_INTR_DISABLE;
//     //bit mask of the pins, use GPIO4/5 here
//     io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
//     //set as input mode
//     io_conf.mode = GPIO_MODE_INPUT;
//     //enable pull-up mode
//     io_conf.pull_up_en = 1;
//     gpio_config(&io_conf);
      
    gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

}
void DelayMs(int ms)
{


}
void DelayUs(int ms)
{


}
uint32_t  GetEchoPulseDuration(int timeout)
{

return 0;
}
void SetTriggerPin(int value)
{

}
void SetTriggerPinAsOutput()
{


}
void app_main() 
{
GPIOInit();

SRF05_t srf05;
srf05.delay=DelayMs;
srf05.delayMicroseconds=DelayUs;
srf05.GetEchoPulseDuratin=GetEchoPulseDuration;
srf05.SetTriggerPin=SetTriggerPin;
srf05.SetTriggerPinOutput=SetTriggerPinAsOutput;

SRF05Init(srf05);

while (true)
{
    gpio_set_level(BLINK_GPIO, 0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    gpio_set_level(BLINK_GPIO, 1);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}


}