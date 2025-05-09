#include "IoHwAb_TorqueSensor.h"
#include "Adc.h"   // Gọi API từ MCAL để đọc giá trị từ ADC
#include <stdio.h>
#include <stdlib.h>

// Giả lập cấu hình của cảm biến mô-men xoắn
static TorqueSensor_ConfigType TorqueSensor_CurrentConfig;

// Hàm khởi tạo cảm biến mô-men xoắn với cấu hình
Std_ReturnType IoHwAb_TorqueSensor_Init(const TorqueSensor_ConfigType* ConfigPtr) {
    if (ConfigPtr == NULL) {
        printf("Error: Null configuration pointer passed to IoHwAb_TorqueSensor_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cấu hình cảm biến mô-men xoắn vào biến toàn cục
    TorqueSensor_CurrentConfig.TorqueSensor_Channel = ConfigPtr->TorqueSensor_Channel;
    TorqueSensor_CurrentConfig.TorqueSensor_MaxValue = ConfigPtr->TorqueSensor_MaxValue;

    // // Gọi API từ MCAL để khởi tạo ADC
    // Adc_ConfigType adcConfig;
    // adcConfig.Adc_Channel = TorqueSensor_CurrentConfig.TorqueSensor_Channel;
    // Adc_Init(&adcConfig);

    // In ra thông tin cấu hình của cảm biến mô-men xoắn
    printf("Torque Sensor Initialized with Configuration:\n");
    printf(" - ADC Channel: %d\n", TorqueSensor_CurrentConfig.TorqueSensor_Channel);
    printf(" - Max Torque Value: %d Nm\n", TorqueSensor_CurrentConfig.TorqueSensor_MaxValue);

    return E_OK;
}

// Hàm đọc giá trị từ cảm biến mô-men xoắn
Std_ReturnType IoHwAb_TorqueSensor_Read(float* TorqueValue) {
    if (TorqueValue == NULL) {
        return E_NOT_OK;  // Kiểm tra con trỏ NULL
    }

    // Đọc giá trị ADC từ MCAL
    uint16_t adcValue = 0;
    if (Adc_ReadChannel(TorqueSensor_CurrentConfig.TorqueSensor_Channel, &adcValue) != E_OK) {
        printf("Error: Failed to read ADC value.\n");
        return E_NOT_OK;
    }

    // Chuyển đổi giá trị ADC sang mô-men xoắn (giả lập)
    *TorqueValue = ((float)adcValue / 1023.0f) * TorqueSensor_CurrentConfig.TorqueSensor_MaxValue;

    // In ra giá trị mô-men xoắn
    printf("Reading Torque Sensor (ADC Channel %d): Torque = %.2f Nm\n",
           TorqueSensor_CurrentConfig.TorqueSensor_Channel, *TorqueValue);

    return E_OK;
}
