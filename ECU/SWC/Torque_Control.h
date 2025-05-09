/**********************************************************************************
 * @file    Torque_Control.h
 * @brief   Khai báo các hàm và cấu trúc liên quan đến điều khiển moment xoắn 
 *          động cơ
 * @details File này cung cấp giao diện cho việc điều khiển moment xoắn động cơ 
 *          bao gồm khởi tạo và cập nhật moment xoắn động cơ
 * @version 1.0
 * @date    2024-12-2
 * @author  Huỳnh Minh Thuận
 *********************************************************************************/
#ifndef TORQUE_CONTROL_H
#define TORQUE_CONTROL_H

// Định nghĩa mô-men xoắn tối đa và tối thiểu
#define MAX_TORQUE 100.0f
#define MIN_TORQUE 0.0f

// Khai báo các hàm chính cho Torque Control
void TorqueControl_Init(void);   // Hàm khởi tạo hệ thống điều khiển mô-men xoắn
void TorqueControl_Update(void); // Hàm cập nhật hệ thống điều khiển mô-men xoắn

#endif // TORQUE_CONTROL_H
