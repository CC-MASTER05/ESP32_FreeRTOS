/*
ESP-IDF FreeRTOS Applications
Specification : Vanilla FreeRTOS
Version: V5.0.1

NOTE: The main task is one of multiple tasks that are automatically spawned by ESP-IDF during startup.

*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

BaseType_t xReturn = NULL;
TaskHandle_t TASK1_HANDLE = NULL;
TaskHandle_t TASK2_HANDLE = NULL;
TaskHandle_t TASK3_HANDLE = NULL;

void task1(void *arg);
void task2(void *arg);
void task3(void *arg);

void task1(void *arg)
{
    while (true)
    {
        printf("this is task1\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void task2(void *arg)
{
    while (true)
    {
        xReturn = xTaskCreate(task3, "task3", 4096, NULL, 8, &TASK3_HANDLE);
        if (xReturn == NULL)
        {
            printf("fail to create task3......delete task");
            vTaskDelete(TASK3_HANDLE);
        }
        vTaskDelete(TASK3_HANDLE); // task3 delete
        vTaskDelete(TASK2_HANDLE); // task2 delete
    }
}
void task3(void *arg)
{
    while (true)
    {
        printf("this is task3\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void app_main(void)
{
    xReturn = xTaskCreate(task1, "Task1", 4096, NULL, 10, &TASK1_HANDLE);
    if (xReturn == NULL)
    {
        printf("fail to create task1......delete task");
        vTaskDelete(TASK1_HANDLE);
    }
    xReturn = NULL;
    xReturn = xTaskCreate(task2, "task2", 4096, NULL, 9, &TASK2_HANDLE);
    if (xReturn == NULL)
    {
        printf("Fail to create task2.......delete task delete");
        vTaskDelete(TASK2_HANDLE);
    }
}