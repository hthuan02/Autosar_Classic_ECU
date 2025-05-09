/****************************************************************************
 * @file    RegenBrake_Control.h
 * @brief   Khai báo các hàm và cấu trúc đến quản lý phanh tái sinh 
 * @details File này cung cấp giao diện cho việc quản lý phanh tái sinh bao
 *          gồm hàm khởi tạo, hàm cập nhật và gồm các marco định nghĩa các
 *          hệ số đặc biệt
 * @version 1.0
 * @date    2024-12-2
 * @author  Huỳnh Minh Thuận 
 ****************************************************************************/
#ifndef REGENBRAKE_CONTROL_H
#define REGENBRAKE_CONTROL_H

#define CHARGING_EFFICIENCY 0.85f        // Hiệu suất sạc pin (85%)
#define KINETIC_CONVERSION_EFF 0.8f      // Hiệu suất chuyển đổi động năng (80%)
#define BATTERY_CAPACITY 50000.0f        // Dung lượng pin (Wh)
#define TIME_REGEN 5.0f                  // Thời gian tái sinh (giây)

#define SPEED_THRESHOLD 10.0f            // Ngưỡng tốc độ phanh tái sinh (dưới ngưỡng không hoạt động)
#define BRAKE_COEFFICIENT 0.5f           // Hệ số phanh tái sinh 
#define MAX_BATTERY_TEMP 50.0f           // Nhiệt độ tối da khi nạp pin (50 độ C)

#define INCLINATION_THRESHOLD 15.0f      // Ngưỡng góc nghiêng khi điều chỉnh lực phanh tái sinh


// Khai báo các hàm chính cho Torque Control
void RegenBrakeControl_Init(void);   // Hàm khởi tạo hệ thống điều khiển phanh tái sinh
void RegenBrakeControl_Update(void); // Hàm cập nhật hệ thống điều khiển phanh tái sinh

#endif // REGENBRAKE_CONTROL_H
