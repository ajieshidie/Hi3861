#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#define LED 18 // 定义输出引脚
void LED_Task(void *pvParameter)
{
    gpio_pad_select_gpio(LED);                 // 选择芯片引脚
    gpio_set_direction(LED, GPIO_MODE_OUTPUT); // 设置该引脚为输出模式
    while (1)
    {
        gpio_set_level(LED, 0);                // 电平为低
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 延迟1S
        gpio_set_level(LED, 1);                // 电平为高
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 延迟1S
    }
}
void app_main() // 主函数
{
    xTaskCreate(&LED_Task, "LED_Task", configMINIMAL_STACK_SIZE, NULL, 5, NULL); // 新建一个任务
}
