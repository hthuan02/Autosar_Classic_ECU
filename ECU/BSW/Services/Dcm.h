#ifndef DCM_H
#define DCM_H

#include <stdio.h>
#include <string.h>

// Định nghĩa các dịch vụ chẩn đoán (Diagnostic Services)
#define DIAGNOSTIC_SESSION_CONTROL 0x10
#define ECU_RESET 0x11
#define READ_DTC 0x19
#define CLEAR_DTC 0x14

// Cấu trúc mô phỏng một gói tin chẩn đoán
typedef struct {
    int service_id;     // Mã dịch vụ chẩn đoán
    char data[50];      // Dữ liệu kèm theo
} Dcm_MessageType;

// Khởi tạo hệ thống DCM
void Dcm_Init(void);

// Xử lý yêu cầu chẩn đoán từ bên ngoài
void Dcm_ProcessRequest(Dcm_MessageType* request);

// Gửi phản hồi chẩn đoán đến thiết bị kiểm tra
void Dcm_SendResponse(int service_id, const char* response);

#endif // DCM_H
