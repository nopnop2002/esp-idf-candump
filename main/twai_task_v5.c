/*	TWAI Network receive Example

	This example code is in the Public Domain (or CC0 licensed, at your option.)

	Unless required by applicable law or agreed to in writing, this
	software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
	CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/twai.h" // Update from V4.2

static const char *TAG = "TWAI_V5";

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

// Format and print the twai message
void twai_print_frame(twai_message_t frame) {
	int ext = frame.extd;
	int rtr = frame.rtr;

	if (ext == 0) {
		printf("Standard ID: 0x%03"PRIx32"%*s", frame.identifier, 5, "");
	} else {
		printf("Extended ID: 0x%08"PRIx32, frame.identifier);
	}
	printf("  DLC: %d Data: ", frame.data_length_code);

	if (rtr == 0) {
		for (int i = 0; i < frame.data_length_code; i++) {
			printf("0x%02x ", frame.data[i]);
		}
	} else {
		printf("REMOTE REQUEST FRAME");
	}
	printf("\n");
}

void twai_receive_task(void *arg)
{
	ESP_LOGI(TAG, "Start");
    ESP_LOGI(TAG, "TWAI_BITRATE=%d",CONFIG_TWAI_BITRATE);
    ESP_LOGI(TAG, "CTX_GPIO=%d",CONFIG_CTX_GPIO);
    ESP_LOGI(TAG, "CRX_GPIO=%d",CONFIG_CRX_GPIO);

	ESP_ERROR_CHECK(twai_driver_install(&g_config, &t_config, &f_config));
	ESP_LOGI(TAG, "Driver installed");
	ESP_ERROR_CHECK(twai_start());
	ESP_LOGI(TAG, "Driver started");

	while (1) {
		twai_message_t rx_msg;
		twai_receive(&rx_msg, portMAX_DELAY);
		ESP_LOGD(TAG,"twai_receive identifier=0x%"PRIx32" flags=0x%"PRIx32" extd=0x%x rtr=0x%x data_length_code=%d",
			rx_msg.identifier, rx_msg.flags, rx_msg.extd, rx_msg.rtr, rx_msg.data_length_code);
		twai_print_frame(rx_msg);
	} // end while

	// Never reach here
	vTaskDelete(NULL);
}
