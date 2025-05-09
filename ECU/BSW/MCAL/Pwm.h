#ifndef PWM_H
#define PWM_H

#include "Std_Types.h"

// Cấu trúc cấu hình cho PWM
typedef struct {
    uint8_t Pwm_Channel;       // Kênh PWM
    uint16_t Pwm_Period;       // Chu kỳ PWM
    uint16_t Pwm_DutyCycle;    // Tỷ lệ nhiệm vụ (duty cycle) của PWM
} Pwm_ConfigType;

// Prototype cho hàm khởi tạo PWM
void Pwm_Init(const Pwm_ConfigType* ConfigPtr);

// Prototype cho hàm cài đặt tỷ lệ nhiệm vụ (duty cycle)
void Pwm_SetDutyCycle(uint8_t Channel, uint16_t DutyCycle);

#endif /* PWM_H */
