#ifndef _LIVELYBOT_CAN_H
#define _LIVELYBOT_CAN_H


#include "main.h"
#include "convert.h"


/* CAN ID 帧头 (接收端 bit[15]=0; 发送控制帧由 fdcan_send 自动置 bit[15]=1) */
/* bits[18]=CAN MIT, bits[17:16]=数据类型(与 data_type_t 枚举值一致), bit[15]=控制/返回区分 */

/* ---- 数据类型 (由 convert.h 的 data_type_t 枚举左移16位派生, 只改枚举即可同步) ---- */
#define  ID_PREFIX_TINT16_NOHDR     ((uint32_t)TINT16_NOHDR << 16)  // bits[17:16]=00
#define  ID_PREFIX_TINT16           ((uint32_t)TINT16       << 16)  // bits[17:16]=01
#define  ID_PREFIX_TINT32           ((uint32_t)TINT32       << 16)  // bits[17:16]=10
#define  ID_PREFIX_TFLOAT           ((uint32_t)TFLOAT       << 16)  // bits[17:16]=11

/* 经典 CAN (bxCAN) 单帧数据区上限 8 字节, 超过 8 字节的控制模式(int32/float 及普通 MIT 帧)不移植 */
#define  CAN_CLASSIC_DATA_MAX       8

/* CAN MIT 模式: CAN ID bit[18]=1 (见 FDCan_Protocol.md 表1), MIT 发送标题 = 0x58000 = ID_MIT_FLAG | ID_PREFIX_TINT16
 * 8 字节位打包, 参数顺序 pos(16bit) -> vel(12bit) -> tqe前馈(12bit) -> Kp(12bit) -> Kd(12bit) */
#define  ID_MIT_FLAG                (0x01u << 18)


/* 底层发送: 自动置 bit[15]=1 (控制帧方向), >0x7FF 自动扩展帧 */
void fdcan_send(CAN_HandleTypeDef *hcan, uint32_t id, uint8_t *data, uint16_t size);


/* dq 电压模式 (d=0, q=实际电压) */
void hightorque_dq_volt_int16(CAN_HandleTypeDef *hcan, uint8_t id, int16_t d, int16_t q);

/* dq 电流模式 (d=0, q=实际电流) */
void hightorque_dq_current_int16(CAN_HandleTypeDef *hcan, uint8_t id, int16_t d, int16_t q);

/* 力矩控制 */
void hightorque_torque_int16(CAN_HandleTypeDef *hcan, uint8_t id, int16_t torque);

/* 位置控制 */
void hightorque_pos_int16(CAN_HandleTypeDef *hcan, uint8_t id, int16_t pos);

/* 速度控制 */
void hightorque_vel_int16(CAN_HandleTypeDef *hcan, uint8_t id, int16_t vel);

/* 位置、速度和力矩控制 */
void hightorque_pos_vel_tqe_int16(CAN_HandleTypeDef *hcan, uint8_t id, int16_t pos, int16_t vel, int16_t torque);

/* 速度、加速度控制 */
void hightorque_vel_acc_int16(CAN_HandleTypeDef *hcan, uint8_t id, int16_t vel, int16_t acc);

/* 位置、速度、加速度限制（梯形控制） */
void hightorque_pos_vel_acc_int16(CAN_HandleTypeDef *hcan, uint8_t id, int16_t pos, int16_t vel_max, int16_t acc);

/* MIT 运控模式 (预留接口, CAN MIT: CAN ID bit[18]=1, 8字节位打包适配经典 CAN,
 * 缩放与位排布均已由厂家参考代码核对确认, 可直接使用) */
void hightorque_pos_vel_tqe_kp_kd_int16(CAN_HandleTypeDef *hcan, uint8_t id,
                                        int16_t pos, int16_t vel, int16_t tqe, int16_t kp, int16_t kd);


/* 电机停止 */
void hightorque_stop_int16(CAN_HandleTypeDef *hcan, uint8_t id);

/* 电机刹车 */
void hightorque_brake_int16(CAN_HandleTypeDef *hcan, uint8_t id);

/* 读取电机状态 (查询码 0x0E: 返回帧 8 字节) */
void hightorque_request_state_int16(CAN_HandleTypeDef *hcan, uint8_t id);

/* 查询电机固件版本 */
void hightorque_request_fw_version(CAN_HandleTypeDef *hcan, uint8_t id);

/* 查询电机型号 */
void hightorque_request_model(CAN_HandleTypeDef *hcan, uint8_t id);

/* 查询电机硬件版本号 */
void hightorque_request_hw_version(CAN_HandleTypeDef *hcan, uint8_t id);


/* 周期请求电机状态返回 (TINT16 发送: 0x03 0x00 0x05 <查询码> + 4字节微秒, t_us=0 停止周期返回) */
void hightorque_request_timed_return(CAN_HandleTypeDef *hcan, uint8_t id, uint32_t t_us);

/* 重设零点 */
void hightorque_pos_rezero(CAN_HandleTypeDef *hcan, uint8_t id);

/* 保存设置 */
void hightorque_conf_write(CAN_HandleTypeDef *hcan, uint8_t id);

/* 重启电机 */
void hightorque_reset(CAN_HandleTypeDef *hcan, uint8_t id);

/* 更改电机ID */
void hightorque_id(CAN_HandleTypeDef *hcan, uint8_t old_id, uint8_t new_id);


#endif
