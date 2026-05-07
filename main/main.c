#include <stdio.h>

#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "firebeetle";

/* FireBeetle ESP32-E onboard user LED (DFR0478) */
#define LED_GPIO_NUM GPIO_NUM_2

void app_main(void)
{
    ESP_LOGI(TAG, "Boot OK — FireBeetle ESP32-E minimal (serial + GPIO2 blink)");

    gpio_config_t io = {
        .pin_bit_mask = 1ULL << LED_GPIO_NUM,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&io));

    int level = 0;
    while (1) {
        gpio_set_level(LED_GPIO_NUM, level);
        level = !level;
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
