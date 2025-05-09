#ifndef CAN_H
#define CAN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Thư viện hỗ trợ hàm sleep (sử dụng cho delay)

// Cấu trúc mô phỏng một CAN message
typedef struct {
    int id;             // ID của thông điệp CAN
    int data[8];        // Dữ liệu CAN (tối đa 8 byte)
    int length;         // Độ dài dữ liệu (tối đa 8 byte)
} Can_MessageType;

// Khởi tạo CAN
void Can_Init(void);

// Gửi một thông điệp CAN
void Can_SendMessage(Can_MessageType* message);

// Nhận một thông điệp CAN (giả lập nhận ngẫu nhiên)
Can_MessageType Can_ReceiveMessage(void);

// Hàm tạo độ trễ (delay)
void Can_Delay(int milliseconds);

#endif // CAN_H
