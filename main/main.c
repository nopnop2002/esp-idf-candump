/*	TWAI Network receive all data Example

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

static const char *TAG = "MAIN";

void twai_receive_task(void* pvParameters);

void app_main()
{
	// Start TWAI task
	xTaskCreate(twai_receive_task, "TWAI", 1024*4, NULL, 2, NULL);
}
