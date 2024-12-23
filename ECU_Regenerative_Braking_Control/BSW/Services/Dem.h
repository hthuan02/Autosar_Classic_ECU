#ifndef DEM_H
#define DEM_H

#include <stdio.h>
#include <string.h>

// Số lượng sự kiện chẩn đoán tối đa có thể theo dõi
#define MAX_DIAGNOSTIC_EVENTS 10

// Cấu trúc mô phỏng sự kiện chẩn đoán
typedef struct {
    int event_id;
    char event_description[50];
    int is_active;  // 1: active (có lỗi), 0: inactive (không có lỗi)
} Dem_EventType;

// Khởi tạo hệ thống quản lý sự kiện chẩn đoán
void Dem_Init(void);

// Kích hoạt sự kiện chẩn đoán
void Dem_ReportErrorStatus(int event_id, const char* description);

// Xóa bỏ sự kiện chẩn đoán (hết lỗi)
void Dem_ClearErrorStatus(int event_id);

// Kiểm tra trạng thái sự kiện chẩn đoán
int Dem_CheckErrorStatus(int event_id);

// In toàn bộ danh sách sự kiện chẩn đoán
void Dem_PrintEventList(void);

#endif // DEM_H
