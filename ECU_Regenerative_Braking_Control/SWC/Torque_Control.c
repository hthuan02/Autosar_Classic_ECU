/****************************************************************************
 * @file    Torque_Control.c
 * @brief   Định nghĩa các hàm điều khiển moment xoắn
 * @details File này chứ các phần điều khiển tốc độ động cơ, bao gồm khởi tạo
 *          và cập nhật giá trị bàn đạp ga, tốc độ, tải trọng, moment thực tế
 *          và moment xoắn yêu cầu
 * @version 1.0
 * @date    2024-12-2
 * @author  Huỳnh Minh Thuận 
 ****************************************************************************/
#include "Rte_TorqueControl.h"   // Bao gồm interface của RTE cho Torque Control
#include "Torque_Control.h"
#include <stdio.h>  // Thư viện cho printf

// Hàm khởi tạo hệ thống điều khiển mô-men xoắn
void TorqueControl_Init(void) {
    // Khởi tạo các cảm biến bàn đạp ga, tốc độ và tải trọng
    Std_ReturnType status;

    printf("--------------- Khởi tạo hệ thống Torque Control... ---------------\n");

    // Khởi tạo cảm biến bàn đạp ga
    status = Rte_Call_RpThrottleSensor_Init();
    if (status == E_OK) {
        printf("Cảm biến bàn đạp ga đã khởi tạo thành công.\n");
    } else {
        printf("Lỗi khi khởi tạo cảm biến bàn đạp ga.\n");
        return;
    }

    // Khởi tạo cảm biến tốc độ
    status = Rte_Call_RpSpeedSensor_Init();
    if (status == E_OK) {
        printf("Cảm biến tốc độ đã khởi tạo thành công.\n");
    } else {
        printf("Lỗi khi khởi tạo cảm biến tốc độ.\n");
        return;
    }

    // Khởi tạo cảm biến tải trọng
    status = Rte_Call_RpLoadSensor_Init();
    if (status == E_OK) {
        printf("Cảm biến tải trọng đã khởi tạo thành công.\n");
    } else {
        printf("Lỗi khi khởi tạo cảm biến tải trọng.\n");
        return;
    }

    // Khởi tạo cảm biến mô-men xoắn thực tế
    status = Rte_Call_RpTorqueSensor_Init();
    if (status == E_OK) {
        printf("Cảm biến mô-men xoắn thực tế đã khởi tạo thành công.\n");
    } else {
        printf("Lỗi khi khởi tạo cảm biến mô-men xoắn.\n");
        return;
    }

    // Khởi tạo bộ điều khiển mô-men xoắn (có thể là PWM hoặc module điều khiển động cơ)
    status = Rte_Call_PpMotorDriver_Init();
    if (status == E_OK) {
        printf("Bộ điều khiển mô-men xoắn đã khởi tạo thành công.\n");
    } else {
        printf("Lỗi khi khởi tạo bộ điều khiển mô-men xoắn.\n");
        return;
    }

    printf("=============== Hệ thống Torque Control đã sẵn sàng! ===============\n");
}

// Hàm cập nhật hệ thống điều khiển mô-men xoắn
void TorqueControl_Update(void) {
    float throttle_input = 0.0f;
    float current_speed = 0.0f;
    float load_weight = 0.0f;
    float actual_torque = 0.0f;
    float desired_torque = 0.0f;

    // Đọc dữ liệu từ cảm biến bàn đạp ga
    if (Rte_Read_RpThrottleSensor_ThrottlePosition(&throttle_input) == E_OK) {
        printf("Giá trị bàn đạp ga: %.2f%%\n", throttle_input * 100);
    } else {
        printf("Lỗi khi đọc cảm biến bàn đạp ga!\n");
    }

    // Đọc dữ liệu từ cảm biến tốc độ
    if (Rte_Read_RpSpeedSensor_Speed(&current_speed) == E_OK) {
        printf("Tốc độ xe hiện tại: %.2f km/h\n", current_speed);
    } else {
        printf("Lỗi khi đọc cảm biến tốc độ!\n");
    }

    // Đọc dữ liệu từ cảm biến tải trọng
    if (Rte_Read_RpLoadSensor_LoadWeight(&load_weight) == E_OK) {
        printf("Tải trọng hiện tại: %.2f kg\n", load_weight);
    } else {
        printf("Lỗi khi đọc cảm biến tải trọng!\n");
    }

    // Đọc mô-men xoắn thực tế để so sánh với mô-men xoắn yêu cầu
    if (Rte_Read_RpTorqueSensor_ActualTorque(&actual_torque) == E_OK) {
        printf("Mô-men xoắn thực tế: %.2f Nm\n", actual_torque);
    } else {
        printf("Lỗi khi đọc mô-men xoắn thực tế!\n");
    }
    
    // Tính toán mô-men xoắn yêu cầu
    desired_torque = throttle_input * MAX_TORQUE;
    if (current_speed > 50.0f) {
        desired_torque *= 0.8f;  // Giảm mô-men xoắn nếu tốc độ cao
    }
    if (load_weight > 500.0f) {
        desired_torque += 10.0f;  // Tăng mô-men xoắn nếu tải trọng lớn
    }

    // Giới hạn mô-men xoắn trong phạm vi an toàn
    if (desired_torque > MAX_TORQUE) {
        desired_torque = MAX_TORQUE;
    } else if (desired_torque < MIN_TORQUE) {
        desired_torque = MIN_TORQUE;
    }

    // In ra mô-men xoắn yêu cầu
    printf("Mô-men xoắn yêu cầu: %.2f Nm\n", desired_torque);

    // Ghi mô-men xoắn yêu cầu tới bộ điều khiển động cơ
    if (Rte_Write_PpMotorDriver_SetTorque(desired_torque) == E_OK) {
        printf("Đã gửi mô-men xoắn yêu cầu tới động cơ.\n");
    } else {
        printf("Lỗi khi gửi mô-men xoắn tới động cơ!\n");
    }

    // So sánh và điều chỉnh nếu có sự sai lệch giữa mô-men xoắn thực tế và yêu cầu
    if (actual_torque < desired_torque) {
        printf("=============== Tăng mô-men xoắn để đạt mức yêu cầu. ===============\n");
    } else if (actual_torque > desired_torque) {
        printf("=============== Giảm mô-men xoắn để đạt mức yêu cầu. ===============\n");
    }
}
