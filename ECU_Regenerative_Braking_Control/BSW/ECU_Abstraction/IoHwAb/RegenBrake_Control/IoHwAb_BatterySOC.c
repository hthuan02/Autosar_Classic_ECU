#include "IoHwAb_BatterySOC.h"
#include "Adc.h"   // Gọi API từ MCAL để đọc giá trị từ ADC
#include <stdio.h>
#include <stdlib.h>

// Giả lập cấu hình của cảm biến trạng thái pin
static BatterySOC_ConfigType BatterySOC_CurrentConfig;

/**
 * @brief   Hàm khởi tạo cảm biến trạng thái pin
 * @details Hàm này nhận một cấu trúc cấu hình, lưu lại cấu hình cho cảm biến trạng
 *          thái pin gồm: Khởi tạo kênh ADC và giá trị tối đa cảm biến trạng thái pin 
 *          & nhiệt độ pin. 
 * @param   ConfigPtr   Con trỏ tới cấu trúc cấu hình cảm biến trạng thái Pin
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Có lỗi trong quá trình khởi tạo (con trỏ NULL).
 */
Std_ReturnType IoHwAb_BatterySOC_Init(const BatterySOC_ConfigType* ConfigPtr) {
    if (ConfigPtr == NULL) {
        printf("Error: Null configuration pointer passed to IoHwAb_BatterySOC_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cấu hình cảm biến trạng thái pin vào biến toàn cục
    BatterySOC_CurrentConfig.BatterySOC_Channel = ConfigPtr->BatterySOC_Channel;
    BatterySOC_CurrentConfig.BatterySOC_MaxValue = ConfigPtr->BatterySOC_MaxValue;
    BatterySOC_CurrentConfig.BatteryTemp_MaxValue = ConfigPtr->BatteryTemp_MaxValue;

    // In ra thông tin cấu hình cảm biến trạng thái pin
    printf("Battery Sate of Charge Initialized with Configuration:\n");
    printf(" - ADC Channel: %d\n", BatterySOC_CurrentConfig.BatterySOC_Channel);
    printf(" - Max Battery State of Charge: %d%%\n", BatterySOC_CurrentConfig.BatterySOC_MaxValue);
    printf(" - Max Battery Temperature: %d\u00b0C\n", BatterySOC_CurrentConfig.BatteryTemp_MaxValue);


    return E_OK;
}

/**
 * @brief   Hàm đọc giá trị từ cảm biến trạng thái pin và nhiệt độ pin
 * @details Hàm này đọc giá trị từ cảm biến tốc độ (từ ADC) và chuyển đổi 
 *          giá trị ADC sang trạng thái pin và nhiệt độ pin (giả lập). 
 * @param   BatterySOCValue   Con trỏ để lưu giá trị trạng thái pin (%)
 *          BatteryTempValue  Con trỏ để lưu giá trị nhiệt độ pin (độ C)
 * @return  Std_ReturnType
 *          - E_OK: Đọc thành công và trả về giá trị tốc độ.
 *          - E_NOT_OK: Lỗi trong quá trình đọc (con trỏ NULL hoặc lỗi ADC).
 */
Std_ReturnType IoHwAb_BatterySOC_Read(float* BatterySOCValue, float *BatteryTempValue) {
    if (BatterySOCValue == NULL) {
        return E_NOT_OK; // Kiểm tra con trỏ NULL
    }

    // Đọc giá trị từ kênh ADC
    uint16_t batterySOC_adc_value =0;
    if (Adc_ReadChannel(BatterySOC_CurrentConfig.BatterySOC_Channel, &batterySOC_adc_value) != E_OK) {
        printf("Error: Failed to read ADC value.\n");
        return E_NOT_OK;
    }

    // Chuyển đổi giá trị ADC sang trạng thái và nhiệt độ pin (giả lập)
    *BatterySOCValue = ((float)batterySOC_adc_value / 1023.0f) * BatterySOC_CurrentConfig.BatterySOC_MaxValue;
    *BatteryTempValue = ((float)batterySOC_adc_value / 1023.0f) * BatterySOC_CurrentConfig.BatteryTemp_MaxValue;

    // In ra kênh ADC
    printf("Reading Sate of Charge(ADC Channel: %d)\n", BatterySOC_CurrentConfig.BatterySOC_Channel);
    

    float Celsius_To_Fahrenheit = (*BatteryTempValue * 9.0f / 5.0f) +32.0f;
    // In ra trạng thái và nhiệt độ pin
    printf("- Battery Sate of Charge: %.0f%%\n", *BatterySOCValue);
    printf("- Battery Temperature: %.2f\u00b0C (%.2f\u00b0F)\n", *BatteryTempValue, Celsius_To_Fahrenheit);

    return E_OK;
}