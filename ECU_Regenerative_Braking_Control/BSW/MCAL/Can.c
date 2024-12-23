#include "Can.h"

// Khởi tạo CAN
void Can_Init(void) {
    printf("CAN Initialized.\n");
}

// Gửi một thông điệp CAN
void Can_SendMessage(Can_MessageType* message) {
    int i;

    // Gọi hàm delay để mô phỏng thời gian gửi CAN
    Can_Delay(200);  // Tạo độ trễ 200ms để mô phỏng

    // In ra thông tin thông điệp được gửi
    printf("CAN Message Sent:\n");
    printf("ID: %d, Data Length: %d, Data: [", message->id, message->length);
    for (i = 0; i < message->length; i++) {
        printf("%d", message->data[i]);
        if (i < message->length - 1) printf(", ");
    }
    printf("]\n");
}

// Nhận một thông điệp CAN (giả lập ngẫu nhiên)
Can_MessageType Can_ReceiveMessage(void) {
    Can_MessageType message;
    int i;

    // Gọi hàm delay để mô phỏng thời gian nhận CAN
    Can_Delay(300);  // Tạo độ trễ 300ms để mô phỏng

    // Giả lập dữ liệu ngẫu nhiên cho thông điệp CAN
    message.id = rand() % 2048;  // Giả lập ID ngẫu nhiên (0 - 2047)
    message.length = rand() % 9; // Giả lập độ dài dữ liệu (0 - 8)
    for ( i = 0; i < message.length; i++) {
        message.data[i] = rand() % 256;  // Giả lập dữ liệu ngẫu nhiên (0 - 255)
    }

    // In ra thông tin thông điệp nhận được
    printf("CAN Message Received:\n");
    printf("ID: %d, Data Length: %d, Data: [", message.id, message.length);
    for (i = 0; i < message.length; i++) {
        printf("%d", message.data[i]);
        if (i < message.length - 1) printf(", ");
    }
    printf("]\n");

    return message;
}

// Hàm delay để tạo độ trễ mô phỏng (tính theo milliseconds)
void Can_Delay(int milliseconds) {
    usleep(milliseconds * 1000); // Hàm usleep tính theo micro giây, nhân với 1000 để thành mili giây
}
