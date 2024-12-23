#include "IoHwAb_ThrottleSensor.h"
#include "Adc.h"   // Gọi API từ MCAL để đọc giá trị từ ADC
#include "Dio.h"   // Gọi API từ MCAL để kiểm tra trạng thái DIO nếu cần
#include <stdio.h>
#include <stdlib.h>

// Địa chỉ hoặc kênh của cảm biến bàn đạp ga sử dụng ADC
#define THROTTLE_SENSOR_ADC_CHANNEL 0  // Giả sử cảm biến bàn đạp ga sử dụng kênh ADC 0

// Định nghĩa phạm vi giá trị của cảm biến bàn đạp ga (giá trị thô)
#define THROTTLE_SENSOR_MIN_RAW_VALUE 0    // Giá trị ADC tối thiểu
#define THROTTLE_SENSOR_MAX_RAW_VALUE 1023 // Giá trị ADC tối đa

// Định nghĩa phạm vi giá trị của bàn đạp ga sau khi chuyển đổi
#define THROTTLE_POSITION_MIN 0.0f  // Bàn đạp ga hoàn toàn thả
#define THROTTLE_POSITION_MAX 1.0f  // Bàn đạp ga hoàn toàn nhấn

// Giả lập cấu hình của cảm biến bàn đạp ga
static ThrottleSensor_ConfigType ThrottleSensor_CurrentConfig;

// Hàm khởi tạo cảm biến bàn đạp ga với cấu hình
Std_ReturnType IoHwAb_ThrottleSensor_Init(const ThrottleSensor_ConfigType* ConfigPtr) {
    if (ConfigPtr == NULL) {
        printf("Error: Null configuration pointer passed to IoHwAb_ThrottleSensor_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cấu hình cảm biến bàn đạp ga vào biến toàn cục
    ThrottleSensor_CurrentConfig.ThrottleSensor_Channel = ConfigPtr->ThrottleSensor_Channel;

    // Gọi API từ MCAL để khởi tạo ADC
    Adc_ConfigType adcConfig;
    adcConfig.Adc_Channel = ThrottleSensor_CurrentConfig.ThrottleSensor_Channel;
   
    Adc_Init(&adcConfig);

    // Gọi API từ MCAL để khởi tạo DIO nếu cần
    //Dio_Init();

    // In ra thông tin cấu hình của cảm biến bàn đạp ga
    printf("Throttle Sensor Initialized with ADC Channel %d\n", ThrottleSensor_CurrentConfig.ThrottleSensor_Channel);

    return E_OK;
}

// Hàm đọc giá trị bàn đạp ga
Std_ReturnType IoHwAb_ThrottleSensor_Read(float* ThrottlePosition) {
    if (ThrottlePosition == NULL) {
        return E_NOT_OK;  // Kiểm tra con trỏ NULL
    }

    // Đọc giá trị ADC từ kênh cảm biến bàn đạp ga
    uint16_t raw_adc_value = 0;
    if (Adc_ReadChannel(ThrottleSensor_CurrentConfig.ThrottleSensor_Channel, &raw_adc_value) != E_OK) {
        printf("Error: Failed to read ADC value.\n");
        return E_NOT_OK;
    }

    // Chuyển đổi giá trị thô của ADC sang phạm vi từ 0.0 đến 1.0
    *ThrottlePosition = ((float)(raw_adc_value - THROTTLE_SENSOR_MIN_RAW_VALUE) / 
                        (THROTTLE_SENSOR_MAX_RAW_VALUE - THROTTLE_SENSOR_MIN_RAW_VALUE));

    // Đảm bảo giá trị nằm trong phạm vi từ 0.0 đến 1.0
    if (*ThrottlePosition < THROTTLE_POSITION_MIN) {
        *ThrottlePosition = THROTTLE_POSITION_MIN;
    } else if (*ThrottlePosition > THROTTLE_POSITION_MAX) {
        *ThrottlePosition = THROTTLE_POSITION_MAX;
    }

    // In ra giá trị bàn đạp ga sau khi chuyển đổi
    printf("Reading Throttle Sensor (ADC Channel %d): Throttle Position = %.2f\n",
           ThrottleSensor_CurrentConfig.ThrottleSensor_Channel, *ThrottlePosition);

    return E_OK;
}
