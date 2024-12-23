#include "IoHwAb_LoadAccess.h"
#include "Adc.h"   // Gọi API từ MCAL để đọc giá trị từ ADC
#include <stdio.h>

// Giả lập cấu hình của cảm biến tải trọng
static LoadAccess_ConfigType LoadAccess_CurrentConfig;

/**
 * @brief   Hàm khởi tạo cảm biến tải trọng
 * @details Hàm này nhận một cấu trúc cấu hình cho cảm biến tải trọng
 *          bao gồm: Khởi tạo kênh ADC và giá tị tối đa cảm biến tải trọng. 
 * @param   ConfigPtr  Con trỏ đến cấu trúc cấu hình của cảm biến tải trọng
 * @return  Std_ReturnType
 *          - E_OK: Khởi tạo thành công.
 *          - E_NOT_OK: Có lỗi trong quá trình khởi tạo (con trỏ NULL).
 */
Std_ReturnType IoHwAb_LoadAccess_Init(const LoadAccess_ConfigType* ConfigPtr) {
    if (ConfigPtr == NULL) {
        printf("Error: Null configuration pointer passed to IoHwAb_LoadAccess_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cấu hình cảm biến tải trọng vào biến toàn cục
    LoadAccess_CurrentConfig.LoadAccess_Channel = ConfigPtr->LoadAccess_Channel;
    LoadAccess_CurrentConfig.LoadAccess_MaxValue = ConfigPtr->LoadAccess_MaxValue;    

    // In ra thông tin cấu hình cảm biến tải trọng
    printf("Load Sensor Initialized with Configuration:\n");
    printf(" - ADC Channel: %d\n", LoadAccess_CurrentConfig.LoadAccess_Channel);
    printf(" - Max Load Value: %d kg\n", LoadAccess_CurrentConfig.LoadAccess_MaxValue);

    return E_OK;
}

/**
 * @brief   Hàm đọc giá trị từ cảm biến tải trọng 
 * @details Hàm này đọc giá trị từ cảm biến tải trọng (từ ADC) và chuyển đổi 
 *          giá trị ADC sang tải trọng hiện tại (giả lập). 
 * @param   LoadAccessValue  Con trỏ lưu giá trị tải trọng đọc được từ cảm biến (kg)
 * @return  Std_ReturnType
 *          - E_OK: Đọc thành công và trả về giá trị tốc độ.
 *          - E_NOT_OK: Lỗi trong quá trình đọc (Con trỏ NULL hoặc lỗi từ ADC).
 */
Std_ReturnType IoHwAb_LoadAccess_Read(float* LoadAccessValue) {
    if (LoadAccessValue == NULL) {
        return E_NOT_OK;
    }

    // Đọc giá trị từ kênh ADC
    uint16_t adcLoadValue = 0;
    if (Adc_ReadChannel(LoadAccess_CurrentConfig.LoadAccess_Channel, &adcLoadValue) != E_OK) {
        printf("Error: Failed to read ADC value.\n");
        return E_NOT_OK;
    }

    // Chuyển đổi giá trị ADC sang tải trọng (giả lập)
    *LoadAccessValue = ((float)adcLoadValue / 1023.0f) * LoadAccess_CurrentConfig.LoadAccess_MaxValue;

    // In ra tải trọng hiện tại
    printf("Reading Load Access(ADC Channel: %d) Load = %.2f kg\n",
            LoadAccess_CurrentConfig.LoadAccess_Channel, *LoadAccessValue);
   
    return E_OK;
}