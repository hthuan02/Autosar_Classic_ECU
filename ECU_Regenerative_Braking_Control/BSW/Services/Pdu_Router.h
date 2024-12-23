#ifndef PDU_ROUTER_H
#define PDU_ROUTER_H

#include <stdio.h>
#include <string.h>

// Các giao thức truyền thông giả lập
#define PROTOCOL_CAN 0x01
#define PROTOCOL_LIN 0x02
#define PROTOCOL_ETHERNET 0x03

// Cấu trúc mô phỏng một PDU (Protocol Data Unit)
typedef struct {
    int protocol_id;  // Giao thức của PDU (CAN, LIN, Ethernet, ...)
    char data[50];    // Dữ liệu của PDU
    int length;       // Độ dài dữ liệu
} Pdu_Type;

// Khởi tạo hệ thống PDU Router
void PduR_Init(void);

// Định tuyến PDU dựa trên giao thức
void PduR_RoutePdu(Pdu_Type* pdu);

// Xử lý PDU cho giao thức CAN
void PduR_CanHandler(Pdu_Type* pdu);

// Xử lý PDU cho giao thức LIN
void PduR_LinHandler(Pdu_Type* pdu);

// Xử lý PDU cho giao thức Ethernet
void PduR_EthernetHandler(Pdu_Type* pdu);

#endif // PDU_ROUTER_H
