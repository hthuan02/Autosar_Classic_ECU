#ifndef IOHWAB_MOTORDRIVER_H
#define IOHWAB_MOTORDRIVER_H

#include "Std_Types.h"

// Cấu trúc cấu hình cho mô-tơ
typedef struct {
    uint8_t Motor_Channel;      // Kênh PWM điều khiển mô-tơ
    uint16_t Motor_MaxTorque;   // Mô-men xoắn tối đa (Nm)
} MotorDriver_ConfigType;

// Prototype khởi tạo mô-tơ
Std_ReturnType IoHwAb_MotorDriver_Init(const MotorDriver_ConfigType* ConfigPtr);

// Prototype điều chỉnh mô-men xoắn của mô-tơ
Std_ReturnType IoHwAb_MotorDriver_SetTorque(float TorqueValue);

#endif /* IOHWAB_MOTORDRIVER_H */
