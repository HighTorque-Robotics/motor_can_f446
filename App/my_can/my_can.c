#include "my_can.h"

CAN_TxHeaderTypeDef tx_header;

void can_filter_init(CAN_HandleTypeDef *hcan)
{
    CAN_FilterTypeDef can_filter_st;
    can_filter_st.FilterActivation = ENABLE;
    can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;
    can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT;
    can_filter_st.FilterIdHigh = 0x0000;
    can_filter_st.FilterIdLow = 0x0000;
    can_filter_st.FilterMaskIdHigh = 0x0000;
    can_filter_st.FilterMaskIdLow = 0x0000;
    can_filter_st.FilterBank = 0;
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
    HAL_CAN_ConfigFilter(hcan, &can_filter_st);
    HAL_CAN_Start(hcan);
    HAL_CAN_DeactivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);

    can_filter_st.SlaveStartFilterBank = 14;
    can_filter_st.FilterBank = 14;
    HAL_CAN_ConfigFilter(hcan, &can_filter_st);
    HAL_CAN_Start(hcan);
    HAL_CAN_DeactivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

uint32_t can_size2dlc(uint16_t size)
{
    if (size > 8)
    {
        size = 8;
    }
    return size;
}

uint16_t can_dlc2size(uint32_t dlc)
{
    if (dlc > 8)
    {
        return 8; // 最大8字节
    }
    return (uint16_t)dlc;
}

void can_send(CAN_HandleTypeDef *hcan, uint32_t id, uint8_t *msg, uint16_t len)
{
    uint32_t tx_mailbox = 0;

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

    /* 末参必须是"真实 uint32_t 变量的地址"(HAL 会回写所选邮箱号),
     * 不能传 CAN_TX_MAILBOX0/1/2 —— 那是邮箱编号常量(1/2/4), 会被当成指针写入非法地址 */
    if (HAL_CAN_AddTxMessage(hcan, &tx_header, msg, &tx_mailbox) != HAL_OK)
    {
        if (HAL_CAN_AddTxMessage(hcan, &tx_header, msg, &tx_mailbox) != HAL_OK)
        {
            HAL_CAN_AddTxMessage(hcan, &tx_header, msg, &tx_mailbox);
        }
    }
}
