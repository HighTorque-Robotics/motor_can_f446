#ifndef _LIVELYBOT_CAN_H
#define _LIVELYBOT_CAN_H

#include "main.h"

/* NAN 表示在电机控制指令中，表示无限 */
#define  INI8_NAN   0x80
#define  INT16_NAN  0x8000
#define  INT32_NAN  0x80000000



uint8_t can_send(CAN_HandleTypeDef *hcan, uint32_t id, uint8_t *msg, uint16_t len);

void motor_control_volt(CAN_HandleTypeDef *hcanx, uint8_t id, int16_t vol);
void motor_control_cur(CAN_HandleTypeDef *hcanx, uint8_t id, int16_t cur);
void motor_control_pos(CAN_HandleTypeDef *hcanx, uint8_t id, int32_t pos, int16_t tqe);
void motor_control_vel(CAN_HandleTypeDef *hcanx, uint8_t id, int16_t vel, int16_t tqe);
void motor_control_tqe(CAN_HandleTypeDef *hcanx, uint8_t id, int32_t tqe);
void motor_control_pos_vel_tqe(CAN_HandleTypeDef *hcanx, uint8_t id, int16_t pos, int16_t vel, int16_t tqe);
void motor_control_vel_acc(FDCAN_HandleTypeDef *hfdcanx, uint8_t id, int16_t vel, int16_t acc);
void motor_control_pos_vel_acc(CAN_HandleTypeDef *hcanx, uint8_t id, int16_t pos, int16_t vel, int16_t acc);
void motor_control_pos_vel_tqe_kp_kd(CAN_HandleTypeDef *hcanx, uint8_t id, int16_t pos, int16_t val, int16_t tqe, int16_t kp, int16_t kd);

void rezero_pos(CAN_HandleTypeDef *hcanx, uint8_t id);
void conf_write(CAN_HandleTypeDef *hcanx, uint8_t id);
void timed_return_motor_status(CAN_HandleTypeDef *hcanx, uint8_t id, int16_t t_ms);
void set_motor_stop(CAN_HandleTypeDef *canHandle, uint8_t id);
void set_motor_brake(CAN_HandleTypeDef *canHandle, uint8_t id);
void motor_read(CAN_HandleTypeDef *hcanx, uint8_t id);
void send_read_motor_version(CAN_HandleTypeDef *hcanx, uint8_t id);


#endif
