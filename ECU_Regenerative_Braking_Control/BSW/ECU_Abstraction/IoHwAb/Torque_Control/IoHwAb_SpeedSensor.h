#ifndef IOHWAB_SPEEDSENSOR_H
#define IOHWAB_SPEEDSENSOR_H

#include "Std_Types.h"

// Cấu hình cho cảm biến tốc độ
typedef struct {
    uint8_t SpeedSensor_Channel;   // Kênh ADC để đọc giá trị từ cảm biến tốc độ
    uint16_t SpeedSensor_MaxValue; // Giá trị tốc độ tối đa mà cảm biến có thể đọc (km/h)
} SpeedSensor_ConfigType;

// Prototype cho hàm khởi tạo cảm biến tốc độ
Std_ReturnType IoHwAb_SpeedSensor_Init(const SpeedSensor_ConfigType* ConfigPtr);

// Prototype cho hàm đọc giá trị từ cảm biến tốc độ
Std_ReturnType IoHwAb_SpeedSensor_Read(float* SpeedValue);

#endif /* IOHWAB_SPEEDSENSOR_H */
