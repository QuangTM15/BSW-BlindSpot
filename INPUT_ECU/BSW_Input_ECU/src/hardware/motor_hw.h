#ifndef MOTOR_HW_H
#define MOTOR_HW_H

#include <stdint.h>

/* ================= MOTOR HW API ================= */

/* Init motor hardware (GPIO safe state) */
void MotorHW_Init(void);

/* Motor direction control */
void MotorHW_Forward(void);
void MotorHW_Reverse(void);
void MotorHW_Stop(void);

#endif /* MOTOR_HW_H */
