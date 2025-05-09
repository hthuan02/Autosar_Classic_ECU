#ifndef RTE_REGENBRAKE_CONTROL_H
#define RTE_REGENBRAKE_CONTROL_H

#include "Std_Types.h"  // Bao gồm các kiểu dữ liệu tiêu chuẩn
#include <stddef.h>     // Định nghĩa NULL

/*API các hàm khởi tạo*/
// API để khởi tạo cảm biến tốc độ
Std_ReturnType Rte_Call_RpSpeedAccess_Init(void);

// API để khởi tạo cảm biến đo trạng thái pin (SOC-Sate of charge)
Std_ReturnType Rte_Call_RpBatterySOC_Init(void);

// API để khởi tạo cảm biến góc nghiêng
Std_ReturnType Rte_Call_RpInclinationSensor_Init(void);

// API để khởi tạo cảm biến tải trọng
Std_ReturnType Rte_Call_RpLoadAccess_Init(void);

/*API các hàm kiểm tra và đọc dữ liệu*/
// API đọc dữ liệu từ cảm biến tốc độ
Std_ReturnType Rte_Read_RpSpeedAccess_Speed(float *Speed);

// API đọc dữ liệu từ cảm biến đo trạng thái pin (SOC-Sate of charge)
Std_ReturnType Rte_Read_RpBatterySOC_BatterySOC(float *BatterySOC, float *BatteryTemp);
 
// API đọc dữ liệu từ cảm biến góc nghiêng
Std_ReturnType Rte_Read_RpInclinationSensor_Inclination(float *Inclination);

// API đọc dữ liệu cảm biến tải trọng
Std_ReturnType Rte_Read_RpLoadAccess_Load(float *Load);

#endif /* RTE_TORQUECONTROL_H*/
