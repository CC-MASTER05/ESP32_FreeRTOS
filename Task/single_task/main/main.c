/*
ESP-IDF FreeRTOS Applications
Specification : Vanilla FreeRTOS
Version: V5.0.1

NOTE: The main task is one of multiple tasks that are automatically spawned by ESP-IDF during startup.

*/

#include <stdio.h>
#include "freertos/FreeRTOS.h" 
#include "freertos/task.h" //header for tasking operation
TaskHandle_t task1_HANDLE = NULL;
void task1(void *arg){
    while(true){
        printf("This is task1\n");
        vTaskDelay(1000/portTICK_PERIOD_MS); //portTICK_PERIOD_MS is cpu frequency
        //vTaskDelay in (v) meaning this function not return (void type)
    }
}
void app_main(void){
    xTaskCreate(task1,"task1",4096,NULL,10,&task1_HANDLE); //xTaskCreate in (x) meaning this function return something

    // xTaskCreate(function name , function messgae for printing , task size , argument pass if any, task priority,task handle for task various operation like hold - resume - delete)

}