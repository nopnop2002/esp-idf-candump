typedef enum {SPP_SRV_OPEN_EVT, SPP_CLOSE_EVT, SPP_ERROR_EVT, SPP_RECEIVE_EVT} COMMAND;

#define PAYLOAD_SIZE 256

typedef struct {
    TaskHandle_t taskHandle;
	uint32_t spp_handle;
	uint16_t spp_event_id;
	size_t length;
	uint8_t payload[PAYLOAD_SIZE];
} CMD_t;

