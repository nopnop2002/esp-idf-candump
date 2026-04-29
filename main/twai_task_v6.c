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
#include "freertos/queue.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_twai.h"
#include "esp_twai_onchip.h"

#define TWAI_LISTENER_TX_GPIO	-1	// Listen only node doesn't need TX pin
#define TWAI_LISTENER_RX_GPIO	CONFIG_CRX_GPIO

static const char *TAG = "TWAI_V6";

// Error callback
static bool IRAM_ATTR twai_listener_on_error_callback(twai_node_handle_t handle, const twai_error_event_data_t *edata, void *user_ctx)
{
	ESP_EARLY_LOGW(TAG, "bus error: 0x%x", edata->err_flags.val);
	return false;
}

// Node state
static bool IRAM_ATTR twai_listener_on_state_change_callback(twai_node_handle_t handle, const twai_state_change_event_data_t *edata, void *user_ctx)
{
	const char *twai_state_name[] = {"error_active", "error_warning", "error_passive", "bus_off"};
	ESP_EARLY_LOGI(TAG, "state changed: %s -> %s", twai_state_name[edata->old_sta], twai_state_name[edata->new_sta]);
	return false;
}

// TWAI receive callback - store data and signal
static bool IRAM_ATTR twai_listener_rx_callback(twai_node_handle_t handle, const twai_rx_done_event_data_t *edata, void *user_ctx)
{
	QueueHandle_t xQueueDevice = (QueueHandle_t)user_ctx;
	ESP_EARLY_LOGD(TAG, "xQueueDevice=%p", xQueueDevice);

	uint8_t recv_buff[8];
	twai_frame_t rx_frame = {
		.buffer = recv_buff,
		.buffer_len = sizeof(recv_buff),
	};
	if (twai_node_receive_from_isr(handle, &rx_frame) == ESP_OK) {
		BaseType_t ret = xQueueSendFromISR(xQueueDevice, &rx_frame, NULL);
		ESP_EARLY_LOGD(TAG, "xQueueSendFromISR ret=%d", ret);
		if (ret == pdPASS) return true;
	}
	return false;
}

// Format and print the twai message
void twai_print_frame(twai_frame_t frame) {
	int ext = frame.header.ide;
	int rtr = frame.header.rtr;

	if (ext == 0) {
		printf("Standard ID: 0x%03"PRIx32"%*s", frame.header.id, 5, "");
	} else {
		printf("Extended ID: 0x%08"PRIx32, frame.header.id);
	}
	printf("  DLC: %d Data: ", frame.header.dlc);

	if (rtr == 0) {
		for (int i = 0; i < frame.header.dlc; i++) {
			printf("0x%02x ", frame.buffer[i]);
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

	// Create queue for receive notification
	QueueHandle_t xQueueDevice = xQueueCreate(10, sizeof(twai_frame_t));
	configASSERT(xQueueDevice);
	ESP_LOGD(TAG, "xQueueDevice=%p", xQueueDevice);

	// Configure TWAI node
	twai_onchip_node_config_t node_config = {
		.io_cfg = {
			.tx = TWAI_LISTENER_TX_GPIO,
			.rx = TWAI_LISTENER_RX_GPIO,
			.quanta_clk_out = -1,
			.bus_off_indicator = -1,
		},
		.bit_timing.bitrate = CONFIG_TWAI_BITRATE,
		.flags.enable_listen_only = true,
	};

	// Create TWAI node
	twai_node_handle_t node_hdl;
	ESP_ERROR_CHECK(twai_new_node_onchip(&node_config, &node_hdl));
	ESP_LOGI(TAG, "TWAI node created");

	// Register callbacks
	twai_event_callbacks_t callbacks = {
		.on_rx_done = twai_listener_rx_callback,
		.on_error = twai_listener_on_error_callback,
		.on_state_change = twai_listener_on_state_change_callback,
	};
	ESP_ERROR_CHECK(twai_node_register_event_callbacks(node_hdl, &callbacks, xQueueDevice));

	// Enable TWAI node
	ESP_ERROR_CHECK(twai_node_enable(node_hdl));
	ESP_LOGI(TAG, "TWAI start listening...");

	// Main loop - Process all data registered in the queue.
	while (1) {
		twai_frame_t frame;
		if (xQueueReceive(xQueueDevice, &frame, portMAX_DELAY)) {
			twai_print_frame(frame);
		} else {
			ESP_LOGE(TAG, "xQueueReceive fail");
			break;
		}
	} // end while

	// Never reach here
	ESP_ERROR_CHECK(twai_node_disable(node_hdl));
	ESP_ERROR_CHECK(twai_node_delete(node_hdl));
	vTaskDelete(NULL);
}
