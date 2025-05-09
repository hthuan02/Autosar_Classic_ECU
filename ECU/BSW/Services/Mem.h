#ifndef MEM_H
#define MEM_H

#include <stdio.h>
#include <stdlib.h>

// Khởi tạo hệ thống quản lý bộ nhớ
void Mem_Init(void);

// Cấp phát một vùng bộ nhớ
void* Mem_Alloc(size_t size);

// Giải phóng một vùng bộ nhớ
void Mem_Free(void* ptr);

// Kiểm tra vùng bộ nhớ có hợp lệ hay không
int Mem_Check(void* ptr);

#endif // MEM_H
