#include "Pwm.h"
#include <stdio.h>

// Giả lập khởi tạo PWM
void Pwm_Init(const Pwm_ConfigType* ConfigPtr) {
    printf("PWM Initialized for Channel %d with Period %d ms and Duty Cycle %d%%\n", 
           ConfigPtr->Pwm_Channel, ConfigPtr->Pwm_Period, ConfigPtr->Pwm_DutyCycle);
}

// Giả lập cài đặt tỷ lệ nhiệm vụ của PWM
void Pwm_SetDutyCycle(uint8_t Channel, uint16_t DutyCycle) {
    printf("PWM Channel %d set to Duty Cycle: %d%%\n", Channel, DutyCycle);
}
