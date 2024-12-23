#ifndef IOHWAB_INCLINATIONSENSOR_H
#define IOHWAB_INCLINATIONSENSOR_H

#include "Std_Types.h"

/**
 * Định nghĩa cấu trúc InclinationSensor_ConfigType chứa các thông tin về góc nghiêng
 * InclinationSensor_Channel: Kênh ADC để đọc giá trị từ cảm biến góc nghiêng
 * InclinationSensor_MaxValue: Giá trị góc nghiêng tối đa mà cảm biến đọc được
 */
typedef struct {
    uint8_t  InclinationSensor_Channel;   // Kênh ADC để đọc giá trị từ cảm biến góc nghiêng
    uint16_t InclinationSensor_MaxValue; // Giá trị góc nghiêng tối đa mà cảm biến có thể đọc (độ)
} InclinationSensor_ConfigType;

/**
 * @brief   Prototype cho hàm khởi tạo cảm biến góc nghiêng
 * @param   ConfigPtr   Con trỏ tới cấu trúc cấu hình cảm biến góc nghiêng
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Khởi tạo thất bại.
 */
Std_ReturnType IoHwAb_InclinationSensor_Init(const InclinationSensor_ConfigType* ConfigPtr);

/**
 * @brief   Prototype cho hàm đọc giá trị từ cảm biến tải trọng
 * @param   InclinationValue   Con trỏ để lưu giá trị góc nghiêng (độ)
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Khởi tạo thất bại.
 */
Std_ReturnType IoHwAb_InclinationSensor_Read(float* InclinationValue);

#endif /* IOHWAB_INCLINATIONSENSOR_H */
