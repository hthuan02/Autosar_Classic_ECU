#ifndef DIO_H
#define DIO_H

#include <stdio.h>
#include <stdlib.h>  // Thư viện hỗ trợ tạo giá trị ngẫu nhiên
#include <time.h>    // Thư viện hỗ trợ thời gian (sử dụng cho random)
#include <unistd.h>  // Thư viện hỗ trợ hàm sleep (sử dụng cho delay)

// Các trạng thái của DIO
typedef enum {
    DIO_LOW = 0,    // Trạng thái thấp (0V)
    DIO_HIGH = 1    // Trạng thái cao (5V)
} Dio_LevelType;

// Khởi tạo DIO
void Dio_Init(void);

// Đọc giá trị từ chân DIO
Dio_LevelType Dio_ReadChannel(int channel);

// Ghi giá trị cho chân DIO
void Dio_WriteChannel(int channel, Dio_LevelType level);

// Hàm tạo độ trễ (delay)
void Dio_Delay(int milliseconds);

#endif // DIO_H
