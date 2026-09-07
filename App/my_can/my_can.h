#ifndef _MY_CAN_H
#define _MY_CAN_H

#include "main.h"
#include "can.h"
#include <string.h>

/* Helper to convert between data size and CAN DLC values (0-8) */
uint32_t get_fdcan_dlc(uint16_t size);
uint16_t get_fdcan_data_size(uint32_t dlc);

/* Use CAN interface types to be consistent with the project (CAN_HandleTypeDef/CAN_TxHeaderTypeDef) */
void can_filter_init(CAN_HandleTypeDef *hcan);
uint8_t can_send(CAN_HandleTypeDef *hcan, uint32_t id, uint8_t *msg, uint16_t len);

#endif
