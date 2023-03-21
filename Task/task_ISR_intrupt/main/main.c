/*
ESP-IDF FreeRTOS Applications
Specification : Vanilla FreeRTOS
Version: V5.0.1

NOTE: The main task is one of multiple tasks that are automatically spawned by ESP-IDF during startup.

*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h" //header for tasking operation
#include "driver/gpio.h"

// Define GPIO PINS
#define ESP_INT_FLAH_DEFAULT 0
#define CONFIG_BUTTON_PIN 0
#define CONFIG_LED_PIN GPIO_NUM_38
TaskHandle_t ISR = NULL;
void IRAM_ATTR button_isr_handler(void *arg)
{
    xTaskResumeFromISR(ISR);
}
void button_task(void *arg)
{
    bool led_status = false;
    while (true)
    {
        vTaskSuspend(NULL);
        led_status = !led_status;
        gpio_set_level(CONFIG_LED_PIN, led_status);
        printf("Button Pressed!\n");
    }
}
void app_main(void)
{
    esp_rom_gpio_pad_select_gpio(CONFIG_BUTTON_PIN);
    esp_rom_gpio_pad_select_gpio(CONFIG_LED_PIN);

    // set the correct direction
    gpio_set_direction(CONFIG_BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(CONFIG_LED_PIN, GPIO_MODE_OUTPUT);

    // enable intrupt on falling(1->0) edge for button pin
    gpio_set_intr_type(CONFIG_BUTTON_PIN, GPIO_INTR_NEGEDGE);

    // Install the driver's GPIO ISR handler service, which allows per-pin GPIO intrupt handlers
    // Install ISR service with default configuration
    gpio_install_isr_service(ESP_INT_FLAH_DEFAULT);

    // attach the intrrupt service routing
    gpio_isr_handler_add(CONFIG_BUTTON_PIN, button_isr_handler, NULL);

    // create and start stats task
    xTaskCreate(button_task, "button task", 4096, NULL, 10, &ISR);
}