#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
  char character = 0;
  char str[100];
  memset(str, 0, sizeof(str));
  while (character != '\n')
  {
    character = getchar();
    if (character != 0xff)
    {
      str[strlen(str)] = character;
      printf("%c", character);
    }
    // vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  printf("User Entered: %s\n", str);
}