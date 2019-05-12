/* CAN Network Listen Only Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/can.h"

/* --------------------- Definitions and static variables ------------------ */
//Example Configuration
#define RX_TASK_PRIO                    9
#define TX_GPIO_NUM                     21
#define RX_GPIO_NUM                     22
#define EXAMPLE_TAG                     "CANDUMP"

static const can_filter_config_t f_config = CAN_FILTER_CONFIG_ACCEPT_ALL();
//static const can_timing_config_t t_config = CAN_TIMING_CONFIG_25KBITS();
static const can_timing_config_t t_config = CAN_TIMING_CONFIG_250KBITS();
//Set TX queue length to 0 due to listen only mode
static const can_general_config_t g_config = {.mode = CAN_MODE_LISTEN_ONLY,
                                              .tx_io = TX_GPIO_NUM, .rx_io = RX_GPIO_NUM,
                                              .clkout_io = CAN_IO_UNUSED, .bus_off_io = CAN_IO_UNUSED,
                                              .tx_queue_len = 0, .rx_queue_len = 5,
                                              .alerts_enabled = CAN_ALERT_NONE,
                                              .clkout_divider = 0};

/* --------------------------- Tasks and Functions -------------------------- */

static void can_receive_task(void *arg)
{
    ESP_LOGI(pcTaskGetTaskName(0),"can_receive_task start");

    while (1) {
        can_message_t rx_msg;
        can_receive(&rx_msg, portMAX_DELAY);
        ESP_LOGI(pcTaskGetTaskName(0),"can_receive identifier=0x%x flags=0x%x data_length_code=%d",
                 rx_msg.identifier, rx_msg.flags, rx_msg.data_length_code);
    	for (int i = 0; i < rx_msg.data_length_code; i++) {
        	printf("%02x ", rx_msg.data[i]);
    	}
        printf("\n");
    }

	// never reach
    vTaskDelete(NULL);
}

void app_main()
{
    //Install and start CAN driver
    ESP_ERROR_CHECK(can_driver_install(&g_config, &t_config, &f_config));
    ESP_LOGI(EXAMPLE_TAG, "Driver installed");
    ESP_ERROR_CHECK(can_start());
    ESP_LOGI(EXAMPLE_TAG, "Driver started");

    xTaskCreate(can_receive_task, "CAN_rx", 4096, NULL, RX_TASK_PRIO, NULL);
}
