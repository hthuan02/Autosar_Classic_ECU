#ifndef IOHWAB_LOADSENSOR_H
#define IOHWAB_LOADSENSOR_H

#include "Std_Types.h"

// Cấu hình cho cảm biến tải trọng (Load Sensor)
typedef struct {
    uint8_t LoadSensor_Channel;   // Kênh ADC để đọc giá trị từ cảm biến
    uint16_t LoadSensor_MaxValue; // Giá trị tải trọng tối đa mà cảm biến có thể đọc
} LoadSensor_ConfigType;

// Khởi tạo cảm biến tải trọng
Std_ReturnType IoHwAb_LoadSensor_Init(const LoadSensor_ConfigType* ConfigPtr);

// Đọc giá trị từ cảm biến tải trọng
Std_ReturnType IoHwAb_LoadSensor_Read(float* LoadValue);

#endif /* IOHWAB_LOADSENSOR_H */
