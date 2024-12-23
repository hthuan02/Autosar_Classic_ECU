#include "IoHwAb_SpeedAccess.h"
#include "Adc.h"   // Gọi API từ MCAL để đọc giá trị từ ADC
#include "Dio.h"
#include <stdio.h>
#include <stdlib.h>

// Giả lập cấu hình của cảm biến tốc độ
static SpeedAccess_ConfigType SpeedAccess_CurrentConfig;

/**
 * @brief   Hàm khởi tạo cảm biến tốc độ với cấu hình
 * @details Hàm này nhận một cấu trúc cấu hình cho cảm biến tốc độ bao gồm:
 *          Khởi tạo kênh ADC và giá trị tối đa từ cảm biến tốc độ. 
 * @param   ConfigPtr  Con trỏ đến cấu trúc cấu hình của cảm biến tốc độ
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Có lỗi trong quá trình khởi tạo (con trỏ NULL).
 */
Std_ReturnType IoHwAb_SpeedAccess_Init(const SpeedAccess_ConfigType* ConfigPtr) {
    if (ConfigPtr == NULL) {
        printf("Error: Null configuration pointer passed to IoHwAb_SpeedAccess_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cấu hình cảm biến tốc độ vào biến toàn cục
    SpeedAccess_CurrentConfig.SpeedAccess_Channel = ConfigPtr->SpeedAccess_Channel;
    SpeedAccess_CurrentConfig.SpeedAccess_MaxValue = ConfigPtr->SpeedAccess_MaxValue;

    // In ra thông tin cấu hình cảm biến tốc độ
    printf("Speed Sensor Initialized with Configuration:\n");
    printf(" - ADC Channel: %d\n", SpeedAccess_CurrentConfig.SpeedAccess_Channel);
    printf(" - Max Speed Value: %d km/h\n", SpeedAccess_CurrentConfig.SpeedAccess_MaxValue);

    return E_OK;
}

/**
 * @brief   Hàm đọc giá trị từ cảm biến tốc độ 
 * @details Hàm này đọc giá trị từ cảm biến tốc độ (từ ADC) và chuyển đổi 
 *          giá trị ADC sang tốc độ hiện tại (giả lập). 
 * @param   SpeedAccessValue  Con trỏ lưu giá trị tốc độ đọc được từ cảm biến (km/h).
 * @return  Std_ReturnType
 *          - E_OK: Đọc thành công và trả về giá trị tốc độ.
 *          - E_NOT_OK: Lỗi trong quá trình đọc (con trỏ NULL hoặc lỗi ADC).
 */
Std_ReturnType IoHwAb_SpeedAccess_Read(float *SpeedAccessValue) {
    if (SpeedAccessValue == NULL) {
        return E_NOT_OK; // Kiểm tra con trỏ NULL
    }

    // Đọc giá trị từ kênh ADC
    uint16_t speed_adc_value =0;
    if (Adc_ReadChannel(SpeedAccess_CurrentConfig.SpeedAccess_Channel, &speed_adc_value) != E_OK) {
        printf("Error: Failed to read ADC value.\n");
        return E_NOT_OK;
    }
    
    // Chuyển đổi giá trị ADC sang tốc độ (giả lập)
    *SpeedAccessValue = ((float)speed_adc_value / 1023.0f) * SpeedAccess_CurrentConfig.SpeedAccess_MaxValue;

    // In ra tốc độ hiện tại
    printf("Reading Speed Access(ADC Channel: %d) Speed = %.2f km/h\n",
            SpeedAccess_CurrentConfig.SpeedAccess_Channel, *SpeedAccessValue);

    return E_OK;

}