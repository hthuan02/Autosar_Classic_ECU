#ifndef IOHWAB_SPEEDACCESS_H
#define IOHWAB_SPEEDACCESS_H

#include "Std_Types.h"

/**
 * Định nghĩa cấu trúc SpeedAccess_ConfigType chứa các thông tin về tốc độ
 * SpeedAccess_Channel: Kênh ADC để đọc giá trị từ cảm biến tốc độ
 * SpeedAccess_MaxValue: Giá trị tốc độ tối đa mà cảm biến đọc được
 */
typedef struct {
    uint8_t SpeedAccess_Channel;   // Kênh ADC để đọc giá trị từ cảm biến tốc độ
    uint16_t SpeedAccess_MaxValue; // Giá trị tốc độ tối đa mà cảm biến có thể đọc (km/h)
} SpeedAccess_ConfigType;

/**
 * @brief   Prototype cho hàm khởi tạo cảm biến tốc độ
 * @param   ConfigPtr   Con trỏ tới cấu trúc cấu hình cảm biến tốc độ.
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Khởi tạo thất bại.
 */
Std_ReturnType IoHwAb_SpeedAccess_Init(const SpeedAccess_ConfigType* ConfigPtr);

/**
 * @brief   Prototype cho hàm đọc giá trị từ cảm biến tốc độ
 * @param   SpeedAccessValue   Con trỏ để lưu giá trị tốc độ đọc được (km/h)
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Khởi tạo thất bại.
 */
Std_ReturnType IoHwAb_SpeedAccess_Read(float* SpeedAccessValue);

#endif /* IOHWAB_SPEEDACCESS_H */
