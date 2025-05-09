#include "IoHwAb_InclinationSensor.h"
#include "Adc.h"   // Gọi API từ MCAL để đọc giá trị từ ADC
#include <stdio.h>
#include <stdlib.h>

// Giả lập cấu hình của cảm biến góc nghiêng
static InclinationSensor_ConfigType InclinationSensor_CurrentConfig;

/**
 * @brief   Hàm khởi tạo cảm biến góc nghiêng
 * @details Hàm này nhận một cấu trúc cấu hình cho cảm biến góc nghiêng bao gồm: 
 *          Khởi tạo kênh ADC và giá trị tối đa cảm biến góc nghiêng. 
 * @param   ConfigPtr  Con trỏ đến cấu trúc cấu hình của cảm biến góc nghiêng
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Có lỗi trong quá trình khởi tạo (Con trỏ NULL).
 */
Std_ReturnType IoHwAb_InclinationSensor_Init(const InclinationSensor_ConfigType* ConfigPtr) {
    if (ConfigPtr == NULL) {
        printf("Error: Null configuration pointer passed to IoHwAb_InclinationSensor_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cấu hình cảm biến tốc độ vào biến toàn cục
    InclinationSensor_CurrentConfig.InclinationSensor_Channel = ConfigPtr->InclinationSensor_Channel;
    InclinationSensor_CurrentConfig.InclinationSensor_MaxValue = ConfigPtr->InclinationSensor_MaxValue;

    // In ra thông tin cấu hình cảm biến tốc độ
    printf("Inclination Sensor Initialized with Configuration:\n");
    printf(" - ADC Channel: %d\n", InclinationSensor_CurrentConfig.InclinationSensor_Channel);
    printf(" - Max Inclination Value: %d\u00b0\n", InclinationSensor_CurrentConfig.InclinationSensor_MaxValue);

    return E_OK;
}

/**
 * @brief   Hàm đọc giá trị từ cảm biến góc nghiêng
 * @details Hàm này đọc giá trị từ cảm biến góc nghiêng (từ ADC) và chuyển đổi 
 *          giá trị ADC sang góc nghiêng hiện tại (giả lập). 
 * @param   InclinationValue  Con trỏ lưu giá trị góc nghiêng đọc được từ cảm biến (độ).
 * @return  Std_ReturnType
 *          - E_OK: Đọc thành công và trả về giá trị tốc độ.
 *          - E_NOT_OK: Lỗi trong quá trình đọc (con trỏ NULL hoặc lỗi ADC).
 */
Std_ReturnType IoHwAb_InclinationSensor_Read(float *InclinationValue) {
    if (InclinationValue == NULL) {
        return E_NOT_OK; // Kiểm tra con trỏ NULL
    }

    // Đọc giá trị từ kênh ADC
    uint16_t inclination_adc_value =0;
    if (Adc_ReadChannel(InclinationSensor_CurrentConfig.InclinationSensor_Channel, &inclination_adc_value) != E_OK) {
        printf("Error: Failed to read ADC value.\n");
        return E_NOT_OK;
    }
    
    // Chuyển đổi giá trị ADC sang góc nghiêng (giả lập)
    *InclinationValue = ((float)inclination_adc_value / 1023.0f) * InclinationSensor_CurrentConfig.InclinationSensor_MaxValue;

    // In ra góc nghiêng hiện tại
    printf("Reading Inclination Value(ADC Channel: %d) Inclination = %.2f\u00b0\n",
            InclinationSensor_CurrentConfig.InclinationSensor_Channel, *InclinationValue);

    return E_OK;  
}
