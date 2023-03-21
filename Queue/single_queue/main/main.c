/*
ESP-IDF FreeRTOS Applications
Specification : Vanilla FreeRTOS
Version: V5.0.1

NOTE: The main task is one of multiple tasks that are automatically spawned by ESP-IDF during startup.

*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
TaskHandle_t myTask1 = NULL;
TaskHandle_t myTask2 = NULL;
QueueHandle_t queue1;
void task1(void *arg)
{
    char txBuff[50];
    /*
    uxQueueLength: 	The maximum number of items the queue can hold at any one time.
    uxItemSize   :	The size, in bytes, required to hold each item in the queue.

    Items are queued by copy, not by reference, so this is the number of bytes that will be copied for each queued item. Each item in the queue must be the same size.

    xQueueCreate(uxQueueLength,uxItemSize)
    */
    queue1 = xQueueCreate(5, sizeof(txBuff)); // create queue
    if (queue1 == NULL)
    {
        printf("Queue1 create fail");
    }
    sprintf(txBuff, "Hello World 1");
    xQueueSend(queue1, (void *)txBuff, (TickType_t)0); // withoutany delay send data

    sprintf(txBuff, "Hello World 2");
    xQueueSend(queue1, (void *)txBuff, (TickType_t)0); // withoutany delay send data

    sprintf(txBuff, "Hello World 3");
    xQueueSend(queue1, (void *)txBuff, (TickType_t)0); // withoutany delay send data

    sprintf(txBuff, "Hello World 4");
    xQueueSend(queue1, (void *)txBuff, (TickType_t)0); // withoutany delay send data
    while (true)
    {
        // printf("Data waiting to be read: %d available space: %d \n", uxQueueMessagesWaiting(queue1), uxQueueSpacesAvailable(queue1));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void task2(void *arg)
{
    char rxBuff[50];
    while (true)
    {
        xQueueReceive(queue1, (void *)rxBuff, (TickType_t)5); // always need to add delay to save over writing or overlapping
        printf("Received data: %s \n", rxBuff);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    xTaskCreate(task1, "Task1", 4096, NULL, 10, &myTask1); //task1 for queue send
    xTaskCreate(task2, "Task2", 4096, NULL, 9, &myTask2);  //task2 for queue receive
}
