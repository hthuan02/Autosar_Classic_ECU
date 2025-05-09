#include "Dem.h"

// Mảng để lưu trữ các sự kiện chẩn đoán
Dem_EventType diagnostic_events[MAX_DIAGNOSTIC_EVENTS];
int event_count = 0;

// Khởi tạo hệ thống quản lý sự kiện chẩn đoán
void Dem_Init(void) {
    int i;
    printf("Diagnostic Event Manager (DEM) Initialized.\n");
    for (i = 0; i < MAX_DIAGNOSTIC_EVENTS; i++) {
        diagnostic_events[i].event_id = -1;
        diagnostic_events[i].is_active = 0;
        strcpy(diagnostic_events[i].event_description, "");
    }
    event_count = 0;
}

// Kích hoạt một sự kiện chẩn đoán
void Dem_ReportErrorStatus(int event_id, const char* description) {
    if (event_count >= MAX_DIAGNOSTIC_EVENTS) {
        printf("Cannot report more events. Maximum diagnostic events reached.\n");
        return;
    }

    // Kiểm tra xem sự kiện đã tồn tại chưa
    int i;
    for (i = 0; i < event_count; i++) {
        if (diagnostic_events[i].event_id == event_id) {
            diagnostic_events[i].is_active = 1;
            printf("Event ID %d already exists. Updating its status to active.\n", event_id);
            return;
        }
    }

    // Thêm sự kiện mới
    diagnostic_events[event_count].event_id = event_id;
    diagnostic_events[event_count].is_active = 1;
    strncpy(diagnostic_events[event_count].event_description, description, sizeof(diagnostic_events[event_count].event_description) - 1);
    event_count++;

    printf("New diagnostic event reported: ID = %d, Description = %s\n", event_id, description);
}

// Xóa bỏ một sự kiện chẩn đoán (tức là lỗi đã được giải quyết)
void Dem_ClearErrorStatus(int event_id) {
    int i;
    for (i = 0; i < event_count; i++) {
        if (diagnostic_events[i].event_id == event_id) {
            diagnostic_events[i].is_active = 0;
            printf("Event ID %d cleared (no longer active).\n", event_id);
            return;
        }
    }
    printf("Event ID %d not found.\n", event_id);
}

// Kiểm tra trạng thái của một sự kiện chẩn đoán
int Dem_CheckErrorStatus(int event_id) {
    int i;
    for (i = 0; i < event_count; i++) {
        if (diagnostic_events[i].event_id == event_id) {
            if (diagnostic_events[i].is_active) {
                printf("Event ID %d is active.\n", event_id);
                return 1;
            } else {
                printf("Event ID %d is inactive.\n", event_id);
                return 0;
            }
        }
    }
    printf("Event ID %d not found.\n", event_id);
    return -1;  // Sự kiện không tồn tại
}

// In danh sách toàn bộ các sự kiện chẩn đoán
void Dem_PrintEventList(void) {
    printf("Diagnostic Events List:\n");
    int i;
    for (i = 0; i < event_count; i++) {
        printf("ID: %d, Description: %s, Status: %s\n",
               diagnostic_events[i].event_id,
               diagnostic_events[i].event_description,
               diagnostic_events[i].is_active ? "Active" : "Inactive");
    }
}
