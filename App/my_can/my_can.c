#include "my_can.h"
CAN_TxHeaderTypeDef tx_header;

uint32_t get_fdcan_dlc(uint16_t size)
{

    if (size > 8)
    {
        size = 8;
    }
    return size;
}

uint16_t get_fdcan_data_size(uint32_t dlc)
{
    if (dlc > 8)
    {
        return 8; // 最大8字节
    }
    return (uint16_t)dlc;
}

uint8_t can_send(CAN_HandleTypeDef *hcan, uint32_t id, uint8_t *msg, uint16_t len)
{
    if (id > 0x7FF)
    {
        tx_header.IDE = CAN_ID_EXT;
        tx_header.ExtId = id;
    }
    else
    {
        tx_header.IDE = CAN_ID_STD;
        tx_header.StdId = id;
    }
    tx_header.RTR = CAN_RTR_DATA;
    tx_header.DLC = len;
    if (HAL_CAN_AddTxMessage(hcan, &tx_header, msg, (uint32_t *)CAN_TX_MAILBOX0) != HAL_OK) //
    {
        if (HAL_CAN_AddTxMessage(hcan, &tx_header, msg, (uint32_t *)CAN_TX_MAILBOX1) != HAL_OK)
        {
            HAL_CAN_AddTxMessage(hcan, &tx_header, msg, (uint32_t *)CAN_TX_MAILBOX2);
        }
    }
    return 0;
}
