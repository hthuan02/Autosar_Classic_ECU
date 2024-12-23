#ifndef ADC_H
#define ADC_H

#include <stdio.h>
#include <stdlib.h>  // Thư viện hỗ trợ tạo giá trị ngẫu nhiên
#include <time.h>    // Thư viện hỗ trợ thời gian (sử dụng cho random)
#include <unistd.h>  // Thư viện hỗ trợ hàm sleep (sử dụng cho delay)
#include "Std_Types.h"

// Cấu trúc chứa thông tin cấu hình của ADC
typedef struct {
    uint8_t Adc_Channel;       // Kênh ADC cần khởi tạo
    uint32_t Adc_SamplingRate; // Tần số lấy mẫu
    uint8_t Adc_Resolution;    // Độ phân giải ADC (ví dụ: 8, 10, 12 bit)
} Adc_ConfigType;

// Khởi tạo ADC
// Hàm khởi tạo ADC
void Adc_Init(const Adc_ConfigType* ConfigPtr);

// Đọc giá trị từ ADC kênh cụ thể
int Adc_ReadChannel(int channel, uint16_t* adcValue);


// Hàm tạo độ trễ (delay)
void Delay(int milliseconds);

#endif // ADC_H
