#ifndef OS_H
#define OS_H

#include <stdio.h>
#include <pthread.h> // Giả lập OS -> 9 task chạy song song
#include <unistd.h>

// Khởi tạo hệ điều hành (OS)
void Os_Init(void);

// Tạo và khởi động một luồng (thread)
void Os_CreateTask(void* (*task_func)(void*), const char* task_name);

// Hàm delay để mô phỏng việc ngừng luồng trong một thời gian nhất định
void Os_Delay(int milliseconds);

// Hàm kết thúc hệ điều hành (OS) và chờ các luồng kết thúc
void Os_Shutdown(void);

#endif // OS_H
