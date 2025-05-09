#include "Adc.h"

// Giả lập ADC hardware với các giá trị cấu hình
static Adc_ConfigType Adc_CurrentConfig;  // Lưu trữ cấu hình hiện tại của ADC

// Hàm khởi tạo ADC với cấu trúc cấu hình
void Adc_Init(const Adc_ConfigType* ConfigPtr) {
    if (ConfigPtr == NULL) {
        printf("Error: Null configuration pointer passed to Adc_Init.\n");
        return;
    }

    // Lưu cấu hình ADC từ ConfigPtr vào biến toàn cục
    Adc_CurrentConfig.Adc_Channel = ConfigPtr->Adc_Channel;
    Adc_CurrentConfig.Adc_SamplingRate = ConfigPtr->Adc_SamplingRate;
    Adc_CurrentConfig.Adc_Resolution = ConfigPtr->Adc_Resolution;

    // Khởi tạo seed cho việc sinh số ngẫu nhiên để mô phỏng ADC
    srand(time(0));

    // In ra thông tin cấu hình ADC
    printf("ADC Initialized with Configuration:\n");
    printf(" - Channel: %d\n", Adc_CurrentConfig.Adc_Channel);
    printf(" - Sampling Rate: %d Hz\n", Adc_CurrentConfig.Adc_SamplingRate);
    printf(" - Resolution: %d-bit\n", Adc_CurrentConfig.Adc_Resolution);
}


// Đọc giá trị từ một kênh ADC cụ thể (với giá trị ngẫu nhiên)
int Adc_ReadChannel(int channel, uint16_t* adcValue) {
    // Giả lập giá trị ADC
    uint16_t adc_value = 0;

    // Gọi hàm delay để mô phỏng thời gian đọc ADC
    Delay(500);  // Tạo độ trễ 500ms để mô phỏng

    // Giả lập giá trị ngẫu nhiên từ 0 đến 1023 (giá trị ADC 10-bit)
    adc_value = rand() % 1024;

    // In giá trị đọc được từ kênh ADC
    printf("Reading ADC Channel %d: Value = %d(random)\n", channel, adc_value);

    // Trả giá trị đọc được thông qua tham chiếu
    *adcValue = adc_value;

    return E_OK;  // Trả về E_OK nếu đọc thành công
}

// Hàm delay để tạo độ trễ mô phỏng (tính theo milliseconds)
void Delay(int milliseconds) {
    usleep(milliseconds * 1000); // Hàm usleep tính theo micro giây, nhân với 1000 để thành mili giây
}
