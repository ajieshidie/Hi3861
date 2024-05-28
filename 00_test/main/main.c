#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include "esp_log.h"
#include "esp_adc_cal.h"
#include "esp_system.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "sdkconfig.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "driver/dac.h"
#include "driver/uart.h"
#include "rom/gpio.h"

void app_main(void)
{

    uint8_t output_data = 0;
    esp_err_t r;
    gpio_num_t dac_gpio_num;
    r = data_pad_get_io_num(DAC_CHANNEL_2, &dac_gpio_num);
    assert(r == ESP_OK);
    printf("DAC channel %d @ GPIO %d.\n", DAC_CHANNEL_2, dac_gpio_num);
    dac_output_enable(DAC_CHANNEL_2);
    vTaskDelay(2 * portTICK_PERIOD_MS);
    printf("start conversion.\n");
    while (1)
    {
        dac_output_voltage(DAC_CHANNEL_2, output_data++);
        printf("output_data %d @ GPIO %d.\n", output_data, dac_gpio_num);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}