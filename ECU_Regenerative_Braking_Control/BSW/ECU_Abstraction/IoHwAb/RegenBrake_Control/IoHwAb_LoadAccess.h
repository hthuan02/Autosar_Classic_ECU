#ifndef IOHWAB_LOADACCESS_H
#define IOHWAB_LOADACCESS_H

#include "Std_Types.h"

/**
 * Định nghĩa cấu trúc LoadAccess_ConfigType chứa các thông tin về tải trọng
 * LoadAccess_Channel: Kênh ADC để đọc giá trị từ cảm biến tải trọng
 * LoadAccess_MaxValue: Giá trị tải trọng tối đa mà cảm biến đọc được
 */
typedef struct {
    uint8_t LoadAccess_Channel;   // Kênh ADC để đọc giá trị từ cảm biến tải trọng
    uint16_t LoadAccess_MaxValue; // Giá trị tải trọng tối đa mà cảm biến có thể đọc (km/h)
} LoadAccess_ConfigType;

/**
 * @brief   Prototype cho hàm khởi tạo cảm biến tải trọng
 * @param   ConfigPtr   Con trỏ tới cấu trúc cấu hình cảm biến tải trọng
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Khởi tạo thất bại.
 */
Std_ReturnType IoHwAb_LoadAccess_Init(const LoadAccess_ConfigType* ConfigPtr);

/**
 * @brief   Prototype cho hàm đọc giá trị cảm biến tải trọng
 * @param   LoadAccessValue   Con trỏ lưu giá trị tải trọng đọc được (kg)
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Khởi tạo thất bại.
 */
Std_ReturnType IoHwAb_LoadAccess_Read(float* LoadAccessValue);

#endif /* IOHWAB_LOADACCESS_H */
