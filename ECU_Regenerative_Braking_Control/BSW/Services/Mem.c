#include "Mem.h"

// Mảng giả lập để theo dõi các vùng bộ nhớ đã cấp phát
#define MAX_ALLOCATIONS 100
void* allocated_blocks[MAX_ALLOCATIONS];
int allocation_count = 0;

// Khởi tạo hệ thống quản lý bộ nhớ
void Mem_Init(void) {
    printf("Memory Management System Initialized.\n");
    int i;
    for (i = 0; i < MAX_ALLOCATIONS; i++) {
        allocated_blocks[i] = NULL;
    }
    allocation_count = 0;
}

// Cấp phát một vùng bộ nhớ
void* Mem_Alloc(size_t size) {
    if (allocation_count >= MAX_ALLOCATIONS) {
        printf("Memory allocation failed: Maximum allocation count reached.\n");
        return NULL;
    }

    void* ptr = malloc(size);
    if (ptr == NULL) {
        printf("Memory allocation failed: Not enough memory.\n");
        return NULL;
    }

    allocated_blocks[allocation_count++] = ptr;
    printf("Memory allocated: %zu bytes at address %p\n", size, ptr);
    return ptr;
}

// Giải phóng một vùng bộ nhớ
void Mem_Free(void* ptr) {
    if (ptr == NULL) {
        printf("Memory free failed: Null pointer provided.\n");
        return;
    }

    int i;
    for (i = 0; i < allocation_count; i++) {
        if (allocated_blocks[i] == ptr) {
            free(ptr);
            allocated_blocks[i] = NULL;
            printf("Memory freed successfully.\n");
            // printf("Memory freed at address %p\n", ptr);
            return;
        }
    }

    printf("Memory free failed: Invalid pointer %p\n", ptr);
}

// Kiểm tra vùng bộ nhớ có hợp lệ hay không
int Mem_Check(void* ptr) {
    int i;
    for (i = 0; i < allocation_count; i++) {
        if (allocated_blocks[i] == ptr) {
            printf("Memory check: Valid pointer %p\n", ptr);
            return 1;  // Vùng nhớ hợp lệ
        }
    }
    printf("Memory check: Invalid pointer %p\n", ptr);
    return 0;  // Vùng nhớ không hợp lệ
}
