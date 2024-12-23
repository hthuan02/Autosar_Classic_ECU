#include "Pdu_Router.h"

// Khởi tạo hệ thống PDU Router
void PduR_Init(void) {
    printf("PDU Router Initialized.\n");
}

// Định tuyến PDU dựa trên giao thức
void PduR_RoutePdu(Pdu_Type* pdu) {
    printf("Routing PDU: Protocol ID = 0x%x, Data = %s, Length = %d\n", pdu->protocol_id, pdu->data, pdu->length);

    switch (pdu->protocol_id) {
        case PROTOCOL_CAN:
            PduR_CanHandler(pdu);
            break;

        case PROTOCOL_LIN:
            PduR_LinHandler(pdu);
            break;

        case PROTOCOL_ETHERNET:
            PduR_EthernetHandler(pdu);
            break;

        default:
            printf("Unknown protocol ID: 0x%x\n", pdu->protocol_id);
            break;
    }
}

// Xử lý PDU cho giao thức CAN
void PduR_CanHandler(Pdu_Type* pdu) {
    printf("Handling CAN PDU: Data = %s, Length = %d\n", pdu->data, pdu->length);
    // Xử lý dữ liệu theo giao thức CAN
}

// Xử lý PDU cho giao thức LIN
void PduR_LinHandler(Pdu_Type* pdu) {
    printf("Handling LIN PDU: Data = %s, Length = %d\n", pdu->data, pdu->length);
    // Xử lý dữ liệu theo giao thức LIN
}

// Xử lý PDU cho giao thức Ethernet
void PduR_EthernetHandler(Pdu_Type* pdu) {
    printf("Handling Ethernet PDU: Data = %s, Length = %d\n", pdu->data, pdu->length);
    // Xử lý dữ liệu theo giao thức Ethernet
}
