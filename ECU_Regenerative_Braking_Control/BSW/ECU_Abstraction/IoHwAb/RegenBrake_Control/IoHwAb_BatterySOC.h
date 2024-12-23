#ifndef IOHWAB_BATTERYSOC_H
#define IOHWAB_BATTERYSOC_H

#include "Std_Types.h"

/**
 * Định nghĩa cấu trúc BatterySOC_ConfigType chứa các thông tin về trạng thái Pin (SOC)
 * BatterySOC_MaxValue: Kênh ADC để đọc giá trị từ cảm biến trạng thái Pin
 * BatterySOC_MaxValue: Giá trị Pin SOC tối đa mà cảm biến đọc được (%)
 * BatteryTemp_MaxValue: Giá trị nhiệt độ Pin tối đa cảm biến đọc được (độ C)
 */
typedef struct {
    uint8_t  BatterySOC_Channel;   // Kênh ADC để đọc giá trị từ cảm biến trạng thái pin
    uint16_t BatterySOC_MaxValue;  // Giá trị trạng thái pin tối đa mà cảm biến có thể đọc (100%)
    uint16_t BatteryTemp_MaxValue; // Giá trị nhiệt độ tối đa của pin mà cảm biến đọc được (60độ C)
} BatterySOC_ConfigType;

/**
 * @brief   Prototype cho hàm khởi tạo cảm biến trạng thái pin
 * @param   ConfigPtr   Con trỏ tới cấu trúc cấu hình cảm biến trạng thái Pin
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Khởi tạo thất bại.
 */
Std_ReturnType IoHwAb_BatterySOC_Init(const BatterySOC_ConfigType *ConfigPtr);

/**
 * @brief   Prototype cho hàm đọc giá trị từ cảm biến trạng thái pin
 * @param   BatterySOCValue   Con trỏ để lưu giá trị trạng thái pin (%)
 *          BatteryTempValue  Con trỏ để lưu giá trị nhiệt độ pin (độ C)
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Khởi tạo thất bại.
 */
Std_ReturnType IoHwAb_BatterySOC_Read(float *BatterySOCValue, float *BatteryTempValue);

#endif /* IOHWAB_BATTERYSOC_H */
