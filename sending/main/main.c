/*	TWAI Network simple sending data Example

	This example code is in the Public Domain (or CC0 licensed, at your option.)

	Unless required by applicable law or agreed to in writing, this
	software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
	CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/twai.h" // Update from V4.2

static const char *TAG = "SENDING";

static const twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

#if CONFIG_CAN_BITRATE_25
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_25KBITS();
#define BITRATE "Bitrate is 25 Kbit/s"
#elif CONFIG_CAN_BITRATE_50
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_50KBITS();
#define BITRATE "Bitrate is 50 Kbit/s"
#elif CONFIG_CAN_BITRATE_100
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_100KBITS();
#define BITRATE "Bitrate is 100 Kbit/s"
#elif CONFIG_CAN_BITRATE_125
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_125KBITS();
#define BITRATE "Bitrate is 125 Kbit/s"
#elif CONFIG_CAN_BITRATE_250
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_250KBITS();
#define BITRATE "Bitrate is 250 Kbit/s"
#elif CONFIG_CAN_BITRATE_500
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
#define BITRATE "Bitrate is 500 Kbit/s"
#elif CONFIG_CAN_BITRATE_800
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_800KBITS();
#define BITRATE "Bitrate is 800 Kbit/s"
#elif CONFIG_CAN_BITRATE_1000
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_1MBITS();
#define BITRATE "Bitrate is 1 Mbit/s"
#endif

static const twai_general_config_t g_config =
	TWAI_GENERAL_CONFIG_DEFAULT(CONFIG_CTX_GPIO, CONFIG_CRX_GPIO, TWAI_MODE_NORMAL);

static void twai_sending_task(void *arg)
{
	ESP_LOGI(pcTaskGetName(0),"task start");

	twai_message_t tx_msg;
	twai_status_info_t status_info;
	tx_msg.extd = 1;
	tx_msg.ss = 1;
	tx_msg.self = 0;
	tx_msg.dlc_non_comp = 0;
	tx_msg.identifier = 0x32;
	tx_msg.data_length_code = 8;
	for (int i=0;i<tx_msg.data_length_code;i++) {
		tx_msg.data[i] = i;
	}

	while (1) {
		twai_get_status_info(&status_info);
		if (status_info.state != TWAI_STATE_RUNNING) {
			ESP_LOGE(TAG, "TWAI driver not running %d", status_info.state);
			continue;
		}
	
		esp_err_t ret = twai_transmit(&tx_msg, 0);
		if (ret == ESP_OK) {
			ESP_LOGI(TAG, "twai_transmit success");
		} else {
			ESP_LOGE(TAG, "twai_transmit Fail %s", esp_err_to_name(ret));
		}
		vTaskDelay(100);
	}

	// Never reach here
	vTaskDelete(NULL);
}

void app_main()
{
	// Install and start TWAI driver
	ESP_LOGI(TAG, "%s",BITRATE);
	ESP_LOGI(TAG, "CTX_GPIO=%d",CONFIG_CTX_GPIO);
	ESP_LOGI(TAG, "CRX_GPIO=%d",CONFIG_CRX_GPIO);

	ESP_ERROR_CHECK(twai_driver_install(&g_config, &t_config, &f_config));
	ESP_LOGI(TAG, "Driver installed");
	ESP_ERROR_CHECK(twai_start());
	ESP_LOGI(TAG, "Driver started");

	// Start task
	xTaskCreate(twai_sending_task, "TWAI", 1024*4, NULL, 2, NULL);
}
