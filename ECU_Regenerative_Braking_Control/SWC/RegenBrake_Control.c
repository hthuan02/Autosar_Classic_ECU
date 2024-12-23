/****************************************************************************
 * @file    RegenBrake_Control.c
 * @brief   Định nghĩa các hàm quản lý phanh tái sinh
 * @details File này chứa các hàm quản lý phanh tái sinh bao gồm hàm khởi và 
 *          cập nhật các giá trị như: cảm biến tốc độ, cảm biến đo trạng thái
 *          pin, cảm biến đo góc nghiêng, cảm biến tải trọng và điều chỉnh lực
 *          phanh tái sinh.   
 * @version 1.0
 * @date    2024-12-2
 * @author  Huỳnh Minh Thuận 
 ****************************************************************************/
#include "Rte_RegenBrake_Control.h"   // Bao gồm interface của RTE cho Regenerative Braking Control
#include "RegenBrake_Control.h"       
#include <stdio.h>                    // Thư viện cho printf
#include <stdbool.h>                  // Thư viện sử dụng hàm bool (0 1)
#include <stdlib.h>                   // Thư viện tạo các số ngẫu nhiên

/**************************************************************************
 * @brief   Hàm khởi tạo hệ thống quản lý phanh tái sinh
 * @param   void
 * @return  void
 **************************************************************************/
void RegenBrakeControl_Init(void) {
    Std_ReturnType status;

    printf("--------------- Khởi tạo hệ thống Torque Control... ---------------\n");
    // Khởi tạo cảm biến tốc độ
    status = Rte_Call_RpSpeedAccess_Init();
    if (status == E_OK) {
        printf("Cảm biến tốc độ đã khởi tạo thành công.\n");
    } else {
        printf("Lỗi khi khởi tạo cảm biến tốc độ.\n");
        return;
    }

    // Khởi tạo cảm biến trạng thái pin
    status = Rte_Call_RpBatterySOC_Init();
    if (status == E_OK) {
        printf("Cảm biến trạng thái pin khởi tạo thành công.\n");
    } else {
        printf("Lỗi khi khởi tạo cảm biến trạng thái pin.\n");
        return;
    }

    // Khởi tạo cảm biến góc nghiêng
    status = Rte_Call_RpInclinationSensor_Init();
    if (status == E_OK) {
        printf("Cảm biến góc nghiêng khởi tạo thành công.\n");
    } else {
        printf("Lỗi khi khởi tạo cảm biến góc nghiêng.\n");
        return;
    }

    // Khởi tạo cảm biến tải trọng
    status = Rte_Call_RpLoadAccess_Init();
    if (status == E_OK) {
        printf("Cảm biến tải trọng đã khởi tạo thành công.\n");
    } else {
        printf("Lỗi khi khởi tạo cảm biến tải trọng.\n");
        return;
    }

    printf("=============== Hệ thống Regenerative Braking đã sẵn sàng! ===============\n");
}

/**************************************************************************
 * @brief   Hàm cập nhật quản lý phanh tái sinh 
 * @param   void
 * @return  void
 **************************************************************************/
void RegenBrakeControl_Update(void) {
    float current_speed = 0.0f;                     // Biến tốc độ hiện tại (km/h)
    float regen_power = 0.0f;                       // Biến công suất tái sinh (W)
    float regenbrake_force = 0.0f;                  // Biến lực phanh tái sinh (N)
    float regen_energy = 0.0f;                      // Biến năng lượng tái sinh (Wh)
    float delta_SOC = 0.0f;                         // Biến chuyển đổi năng lượng sang trạng thái pin(%)
    float battery_soc = 0.0f;                       // Biến trạng thái Pin (SOC-Sate of Charge)
    float battery_temp = 0.0f;                      // Biến nhiệt độ Pin (độ C)
    bool accelerator_released = (rand() % 2 == 0);  // Biến trạng thái bàn đạp ga nhả
    bool brake_pressed = (rand() % 2 == 0);         // Biến trạng thái nhấn phanh
    bool regenbrake_active = false;                 // Biến trạng thái phanh tái sinh
    float inclination_angle = 0.0f;                 // Biến góc nghiêng (độ)
    float adjusted_brakeforce = 0.0f;               // Biến điều chỉnh lực phanh tái sinh (N)
    float vehicle_weight = 0.0f;                    // Biến tải trọng của xe
    
    // Đọc dữ liệu từ cảm biến tốc độ
    if (Rte_Read_RpSpeedAccess_Speed(&current_speed) == E_OK) {
        printf("- Tốc độ xe hiện tại: %.2f km/h\n", current_speed);
    } else {
        printf("Lỗi khi đọc cảm biến tốc độ!\n");
    }

    // Tính lực phanh tái sinh (N)
    regenbrake_force = (current_speed - SPEED_THRESHOLD) * BRAKE_COEFFICIENT;

    // Tính công suất tái sinh (W)
    regen_power = regenbrake_force * current_speed * KINETIC_CONVERSION_EFF;

    // Tính năng lượng tái sinh trong thời gian phanh (Wh)
    regen_energy = regen_power * (TIME_REGEN / 3600.0f) * CHARGING_EFFICIENCY;

    // Kiểm tra bàn đạp ga được nhả hoặc phanh được nhấn và tốc độ đủ lớn (giả lập hàm bool nhấn ga hoặc đạp phanh)
    if ((accelerator_released || brake_pressed) && current_speed > SPEED_THRESHOLD) {
        regenbrake_active = true;
        printf("- Kích hoạt phanh tái sinh: %.2f N\n", regenbrake_force);
        printf("- Công suất tái sinh từ lực phanh tái sinh: %.2f W\n",regen_power);
        printf("- Năng lượng tái sinh trong %.0f giây: %.2f Wh\n", TIME_REGEN, regen_energy);
        
    } else {
        regenbrake_active = false; 
        printf("%s\n", current_speed <= SPEED_THRESHOLD ? "- Không có phanh tái sinh vì tốc độ quá thấp." :
                                                          "- Không có phanh tái sinh do không nhả ga hoặc không nhấn phanh.");

    }

    // Chuyển đổi năng lượng tái sinh thành % pin nạp vào
    delta_SOC = (regen_energy / BATTERY_CAPACITY) * 100;

    // Đọc dữ liệu từ cảm biến đo trạng thái và nhiệt độ Pin
    if (Rte_Read_RpBatterySOC_BatterySOC(&battery_soc, &battery_temp) == E_OK) {
        if (battery_temp < MAX_BATTERY_TEMP) {
            if(regenbrake_active == true){
                printf("Nhiệt độ Pin ổn định và có lực phanh tái sinh. Tiến hành tái nạp...\n");
                printf("Phần trăm pin được nạp thêm: %.3f%%\n", delta_SOC);
                printf("Hoàn tất quá trình tái nạp!\n");

            } else {
                printf("Không thể tái nạp, vì không có lực tái sinh\n");
            }

        } else {
            printf("Nhiệt độ Pin quá cao! Tạm dừng tái nạp.\n");
        }
    }

    // Đọc dữ liệu từ cảm biến góc nghiêng
    if (Rte_Read_RpInclinationSensor_Inclination(&inclination_angle) == E_OK) {
        printf("- Góc nghiêng hiện tại của xe: %.2f\u00b0\n", inclination_angle);
    } else {
        printf("Lỗi khi đọc cảm biến góc nghiêng!\n");
    }

    // Đọc dữ liệu từ cảm biến tải trọng
    if (Rte_Read_RpLoadAccess_Load(&vehicle_weight) == E_OK) {
        printf("- Tải trọng của xe hiện tại: %.2f kg\n", vehicle_weight);
    } else {
        printf("Lỗi khi đọc cảm biến tải trọng!\n");
    }

    // Điều chỉnh lực phanh tái sinh theo góc nghiêng
    adjusted_brakeforce = regenbrake_force * (1.0f + (inclination_angle / 100.0f));

    // Điều chỉnh lực phanh tái sinh theo góc nghiêng (lên dốc - xuống dốc - mặt phẳng)
    printf("Tiến hành điều chỉnh lực phanh tái sinh...\n");
    if (inclination_angle > INCLINATION_THRESHOLD) {
        // Xe đang lên dốc
        adjusted_brakeforce *= 1.2f; // Tăng 20 lực phanh tái sinh khi lên dốc
        printf("- Xe đang lên dốc...\n");

        // Điều chỉnh theo tải trọng
        if (vehicle_weight > 400.0f) {
            adjusted_brakeforce *= 1.1f; // Tăng thêm lực phanh cho xe nặng
            printf("- Tải trọng nặng. Tăng thêm lực phanh tái sinh: %.2f N\n", adjusted_brakeforce);
        } else {
            printf("- Tải trọng nhẹ. Tăng Lực phanh tái sinh phù hợp: %.2f N\n", adjusted_brakeforce);
        }

    } else if (inclination_angle < -INCLINATION_THRESHOLD) {
        // Xe đang xuống dốc
        adjusted_brakeforce *= 0.8f; // Giảm 20% lực phanh tái sinh khi xuống dốc
        printf("- Xe đang xuống dốc...\n");

        // Điều chỉnh theo tải trọng
        if (vehicle_weight > 400.0f) {
            adjusted_brakeforce *= 1.05f; // Xe nặng vẫn cần giữ phanh tái sinh
            printf("- Tải trọng nặng. Giảm lực phanh một chút nhưng vẫn duy trì: %.2f N\n", adjusted_brakeforce);
        } else {
            printf("- Tải trọng nhẹ. Giảm lực phanh tái sinh nhẹ hơn: %.2f N\n", adjusted_brakeforce);
        }

    } else {
        // Xe di chuyển trên mặt phẳng
        printf("- Xe đang di chuyển trên mặt phẳng...\n");

        // Điều chỉnh theo tải trọng
        if (vehicle_weight > 400.0f) {
            adjusted_brakeforce *= 1.05f; // Xe nặng cần lực phanh mạnh hơn
            printf("- Tải trọng nặng. Tăng lực phanh tái sinh: %.2f N\n", adjusted_brakeforce);
        } else {
            printf("- Tải trọng nhẹ. Lực phanh tái sinh bình thường: %.2f N\n", adjusted_brakeforce);
        }
    }

    printf("=============== Hoàn tất quá trình cập nhật hệ thống Regenerative Braking! ===============\n");
}