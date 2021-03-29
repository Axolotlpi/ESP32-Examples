/*
ESP IDF Blink example turned into a FreeRTOS task example.
For ESP32.

Refer to origional blink example, this is two of those placed into tasks,
and running (sort of) simultaneously.
For a high level overview on how FreeRTOS multitasks:
https://www.freertos.org/implementation/a00002.html
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_task.h"

#define BLINK_GPIO 2
#define BLINK_GPIO_B 16
#define STACK_SIZE 2048 //Overestimated value refer to FreeRTOS for more info
#define DELAY 1000
#define SMALL_DELAY 500

void blink(void *pvParameter);
void fast_blink(void *pvParameter);

void app_main() {
    //API docs: https://www.freertos.org/a00125.html
    TaskHandle_t blink_handle;
    TaskHandle_t fast_blink_handle;
    xTaskCreate(blink, "Blinking1", STACK_SIZE, NULL, 2, &blink_handle);
    xTaskCreate(fast_blink, "Blinking2", STACK_SIZE, NULL, 2, &fast_blink_handle);
}

void blink(void *pvParameter){
    gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    while(1) {
        /* Blink off (output low) */
	printf("Turning off the LED #1\n");
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(DELAY / portTICK_PERIOD_MS);
        /* Blink on (output high) */
	printf("Turning on the LED #1\n");
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(DELAY / portTICK_PERIOD_MS);
    }
}

void fast_blink(void *pvParameter){
    gpio_pad_select_gpio(BLINK_GPIO_B);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO_B, GPIO_MODE_OUTPUT);

    while(1) {
        /* Blink off (output low) */
	printf("Turning off the LED #2\n");
        gpio_set_level(BLINK_GPIO_B, 0);
        vTaskDelay(SMALL_DELAY / portTICK_PERIOD_MS);
        /* Blink on (output high) */
	printf("Turning on the LED #2\n");
        gpio_set_level(BLINK_GPIO_B, 1);
        vTaskDelay(SMALL_DELAY / portTICK_PERIOD_MS);
    }
}