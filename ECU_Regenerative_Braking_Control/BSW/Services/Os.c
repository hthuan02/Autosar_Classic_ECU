#include "Os.h"

// Biến lưu trữ luồng
#define MAX_TASKS 9
pthread_t task_threads[MAX_TASKS];
int task_count = 0;

// Khởi tạo hệ điều hành
void Os_Init(void) {
    printf("OS Initialized.\n"); 

    // Mỗi lần có task tạo ra thì biến đếm tăng lên 
    task_count = 0; // Biến đếm số lượng task đang chạy
}

// Tạo và khởi động một luồng
void Os_CreateTask(void* (*task_func)(void*), const char* task_name) {
    if (task_count >= MAX_TASKS) {
        printf("Cannot create more tasks. Maximum task count reached.\n");
        return;
    }
    
    printf("Creating task: %s\n", task_name);

    // Hàm tạo ra 1 task
    pthread_create(&task_threads[task_count], NULL, task_func, NULL);
    task_count++;
}

// Hàm delay để dừng luồng trong một khoảng thời gian
void Os_Delay(int milliseconds) {
    usleep(milliseconds * 1000); // Sử dụng usleep cho delay tính theo mili giây
}

// Kết thúc hệ điều hành và chờ các luồng kết thúc
void Os_Shutdown(void) {
    printf("Shutting down OS and waiting for tasks to finish...\n");
    int i;
    for (i = 0; i < task_count; i++) {
        pthread_join(task_threads[i], NULL); // Chờ các luồng kết thúc
    }
    printf("All tasks have completed. OS Shutdown.\n");
}
