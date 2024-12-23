#include "Dio.h"

// Khởi tạo DIO
void Dio_Init(void) {
    // Khởi tạo seed cho random số ngẫu nhiên
    srand(time(0));
    printf("DIO Initialized.\n");
}

// Đọc giá trị từ chân DIO (giá trị ngẫu nhiên)
Dio_LevelType Dio_ReadChannel(int channel) {
    Dio_LevelType dio_value;

    // Gọi hàm delay để mô phỏng thời gian đọc DIO
    Dio_Delay(200);  // Tạo độ trễ 200ms để mô phỏng

    // Giả lập trạng thái ngẫu nhiên của DIO (0 hoặc 1)
    dio_value = (rand() % 2) ? DIO_HIGH : DIO_LOW;

    // In trạng thái đọc được từ kênh DIO
    printf("Reading DIO Channel %d: Value = %d\n", channel, dio_value);

    return dio_value;
}

// Ghi giá trị cho chân DIO
void Dio_WriteChannel(int channel, Dio_LevelType level) {
    // Gọi hàm delay để mô phỏng thời gian ghi DIO
    Dio_Delay(100);  // Tạo độ trễ 100ms để mô phỏng

    // In trạng thái được ghi vào kênh DIO
    printf("Writing DIO Channel %d: Value = %d\n", channel, level);
}

// Hàm delay để tạo độ trễ mô phỏng (tính theo milliseconds)
void Dio_Delay(int milliseconds) {
    usleep(milliseconds * 1000); // Hàm usleep tính theo micro giây, nhân với 1000 để thành mili giây
}
