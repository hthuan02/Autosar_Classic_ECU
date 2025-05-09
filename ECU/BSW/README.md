# Tầng Bassic Software (BSW)

- Là nền tảng hỗ trợ thực hiện các task SWC.

- Nằm ở dưới tầng trung gian RTE

- Gồm 3 tầng nhỏ: Services,

## Services
(Tầng cao nhất trong BSW)

- Cung cấp hệ điều hành (OS), Quản lý thời giân thực và chuẩn đoán lỗi

VD: stm32 -> RTOS

    window -> Pthread: Thư viện giả lập

## ECU - Abstraction layer
(Tầng ở giữa trong BSW)

- Cung cấp giao diện trừu tượng để truy cập đến các ngoại vi.

VD: Các hàm đọc dữ liệu, ghi dữ liệu -> Ở tầng Abstraction-ECU

-> Là các hàm return trong RTE

```c
Std_ReturnType Rte_Read_RpThrottleSensor_ThrottlePosition(float* ThrottlePosition) {
    if (ThrottlePosition == NULL) {
        return E_NOT_OK;  // Trả về lỗi nếu con trỏ NULL
    }
    
    /**************************************************
     * Vì RTE là tầng trung gian SWC và BSW
     * ->> Sau khi RTE thực hiện xong phải return lại
     *     gọi hàm tầng BSW
     * 
     **************************************************/

    // Hardware abstraction của BSW
    return IoHwAb_ThrottleSensor_Read(ThrottlePosition);  // Gọi API từ IoHwAb để đọc giá trị từ cảm biến
}
```
## Macro controller abstraction layer (MCAL)
(Tầng thấp nhất trong BSW)

- Giao tiếp với những cảm biến: ADC, CAN,...

- Cấu hình những thông số cho nó.

-> Không đụng đến tầng MCAL, Services.

-> Chỉ sử dụng ECU(tầng giữa BSW) để giao tiếp với tầng SWC.
 
- ECU -> code IO hardware ở tầng BSW và SWC.

- Gọi API từ MCAL, cấu hình ADC -> không đụng đến cho comment hết.