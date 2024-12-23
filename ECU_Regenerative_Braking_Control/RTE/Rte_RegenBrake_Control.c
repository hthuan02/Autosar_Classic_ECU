#include "Rte_RegenBrake_Control.h"
#include "IoHwAb_SpeedAccess.h"             // API IoHwAb để đọc cảm biến tốc độ
#include "IoHwAb_BatterySOC.h"              // API IoHwAb để đọc cảm biến trạng thái pin (SOC- State of Charge)
#include "IoHwAb_InclinationSensor.h"       // API IoHwAb để đọc cảm biến góc nghiêng
#include "IoHwAb_LoadAccess.h"              // API IoHwAb để đọc cảm biến tải trọng
#include "Std_Types.h"                      // Thư viện định nghĩa kiểu dữ liệu có kích thước cụ thể

// API khởi tạo cảm biến tốc độ
Std_ReturnType Rte_Call_RpSpeedAccess_Init(void) {
    // Cấu hình cho cảm biến tốc độ
    SpeedAccess_ConfigType speedAccessConfig = {
        .SpeedAccess_Channel = 0,        // Kênh ADC cho cảm biến tốc độ
        .SpeedAccess_MaxValue = 200      // Tốc độ tối đa giả lập (200 km/h)
    };
    return IoHwAb_SpeedAccess_Init(&speedAccessConfig);  // Gọi API từ IoHwAb để khởi tạo cảm biến tốc độ
}

// API khởi tạo cảm biến đo trạng tái pin (Sate of charge)
Std_ReturnType Rte_Call_RpBatterySOC_Init(void) {
    // Cấu hình cho cảm biến đo trạng thái pin
    BatterySOC_ConfigType batterySOCConfig = {
        .BatterySOC_Channel = 1,        // Kênh ADC cho cảm biến trạng thái pin
        .BatterySOC_MaxValue = 100,     // Trạng thái pin tối đa (100%)
        .BatteryTemp_MaxValue = 50      // Nhiệt độ pin tối đa (50 độ)
    };
    return IoHwAb_BatterySOC_Init(&batterySOCConfig);  // Gọi API từ IoHwAb để khởi tạo cảm biến trạng thái pin
}

// API khởi tạo cảm biến góc nghiêng
Std_ReturnType Rte_Call_RpInclinationSensor_Init(void){
    InclinationSensor_ConfigType inclinationConfig = {
        .InclinationSensor_Channel = 2,     // Kênh ADC cho cảm biến góc nghiêng
        .InclinationSensor_MaxValue = 30    // Góc nghiêng tối đa (30 độ) 
    };
    return IoHwAb_InclinationSensor_Init(&inclinationConfig);  // Gọi API từ IoHwAb để khởi tạo cảm biến góc nghiêng
}

// API khởi tạo cảm biến tải trọng
Std_ReturnType Rte_Call_RpLoadAccess_Init(void) {
    // Cấu hình cho cảm biến tốc độ
    LoadAccess_ConfigType loadAccessConfig = {
        .LoadAccess_Channel = 3,        // Kênh ADC cho cảm biến tải trọng
        .LoadAccess_MaxValue = 800      // Tải trọng giả lập (800 kg)
    };
    return IoHwAb_LoadAccess_Init(&loadAccessConfig);  // Gọi API từ IoHwAb để khởi tạo cảm biến tải trọng
}

// API đọc dữ liệu cảm biến tốc độ
Std_ReturnType Rte_Read_RpSpeedAccess_Speed(float *Speed) {
    if (Speed == NULL) {
        return E_NOT_OK;
    }
    return IoHwAb_SpeedAccess_Read(Speed);
}

// API đọc dữ liệu từ cảm biến trạng thái pin (SOC-Sate of Charge)
Std_ReturnType Rte_Read_RpBatterySOC_BatterySOC(float *BatterySOC, float *BatteryTemp) {
    if (BatterySOC == NULL) {
        return E_NOT_OK;
    }
    return IoHwAb_BatterySOC_Read(BatterySOC, BatteryTemp);
}

// API đọc dữ liệu cảm biến góc nghiêng
Std_ReturnType Rte_Read_RpInclinationSensor_Inclination(float *Inclination) {
    if(Inclination == NULL) {
        return E_NOT_OK;
    }
    return IoHwAb_InclinationSensor_Read(Inclination);
}

// API đọc dữ liệu cảm biến tải trọng
Std_ReturnType Rte_Read_RpLoadAccess_Load(float *Load) {
    if (Load == NULL) {
        return E_NOT_OK;
    }
    return IoHwAb_LoadAccess_Read(Load);
}