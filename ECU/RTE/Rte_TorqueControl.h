#ifndef RTE_TORQUECONTROL_H
#define RTE_TORQUECONTROL_H

#include "Std_Types.h"  // Bao gồm các kiểu dữ liệu tiêu chuẩn
#include <stddef.h>  // Định nghĩa NULL


// API để đọc dữ liệu từ cảm biến bàn đạp ga
Std_ReturnType Rte_Read_RpThrottleSensor_ThrottlePosition(float *ThrottlePosition);

// API để đọc dữ liệu từ cảm biến tốc độ
Std_ReturnType Rte_Read_RpSpeedSensor_Speed(float *Speed);

// API để đọc dữ liệu từ cảm biến tải trọng
Std_ReturnType Rte_Read_RpLoadSensor_LoadWeight(float *LoadWeight);

// API để đọc mô-men xoắn thực tế từ cảm biến mô-men xoắn
Std_ReturnType Rte_Read_RpTorqueSensor_ActualTorque(float *ActualTorque);

// API để ghi dữ liệu mô-men xoắn yêu cầu tới bộ điều khiển động cơ
Std_ReturnType Rte_Write_PpMotorDriver_SetTorque(float TorqueValue);

// API khởi tạo cảm biến bàn đạp ga
Std_ReturnType Rte_Call_RpThrottleSensor_Init(void);

// API khởi tạo cảm biến tốc độ
Std_ReturnType Rte_Call_RpSpeedSensor_Init(void);

// API khởi tạo cảm biến tải trọng
Std_ReturnType Rte_Call_RpLoadSensor_Init(void);

// API khởi tạo cảm biến mô-men xoắn
Std_ReturnType Rte_Call_RpTorqueSensor_Init(void);

// API khởi tạo bộ điều khiển mô-men xoắn
Std_ReturnType Rte_Call_PpMotorDriver_Init(void);

#endif // RTE_TORQUECONTROL_H
