#include "esp_gatts_api.h"

//typedef enum {SPP_CONNECT_EVT, SPP_AUTH_EVT, SPP_WRITE_EVT, SPP_DISCONNECT_EVT, SPP_SUBSCRIBE_EVT, SPP_PUBLISHE_EVT} COMMAND;
typedef enum {SPP_CONNECT_EVT, SPP_AUTH_EVT, SPP_WRITE_EVT, SPP_DISCONNECT_EVT, SPP_RECEIVE_EVT} COMMAND;

#define PAYLOAD_SIZE 128

typedef struct {
	TaskHandle_t taskHandle;
	int32_t mqtt_event_id;
	uint16_t spp_conn_id;
	esp_gatt_if_t spp_gatts_if;
	uint16_t spp_event_id;
	size_t length;
	uint8_t payload[PAYLOAD_SIZE];
} CMD_t;
