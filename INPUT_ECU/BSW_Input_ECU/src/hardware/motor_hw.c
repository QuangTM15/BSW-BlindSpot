#include "motor_hw.h"

/* SDK */
#include "sdk_project_config.h"

/* Project config */
#include "utils/pinConfig.h"

/* ================= INTERNAL DELAY ================= */
static void motor_hw_delay_us(uint32_t us)
{
    volatile uint32_t i;
    while (us--)
    {
        for (i = 0; i < 10U; i++)
        {
            __asm("nop");
        }
    }
}

/* ================= LOW LEVEL ================= */

static inline void motor_hw_disable(void)
{
    /* IN3 = 0, IN4 = 0  -> STOP */
    PINS_DRV_ClearPins(
        MOTOR_FWD_PWM_PORT,
        (1U << MOTOR_FWD_PWM_PIN) | (1U << MOTOR_REV_PWM_PIN)
    );
}

/* ================= PUBLIC API ================= */

void MotorHW_Init(void)
{
    motor_hw_disable();
}

void MotorHW_Forward(void)
{
    motor_hw_disable();
    motor_hw_delay_us(50);

    /* Forward: FWD=1, REV=0 */
    PINS_DRV_SetPins  (MOTOR_FWD_PWM_PORT, 1U << MOTOR_FWD_PWM_PIN);
    PINS_DRV_ClearPins(MOTOR_REV_PWM_PORT, 1U << MOTOR_REV_PWM_PIN);
}

void MotorHW_Reverse(void)
{
    motor_hw_disable();
    motor_hw_delay_us(50);

    /* Reverse: FWD=0, REV=1 */
    PINS_DRV_ClearPins(MOTOR_FWD_PWM_PORT, 1U << MOTOR_FWD_PWM_PIN);
    PINS_DRV_SetPins  (MOTOR_REV_PWM_PORT, 1U << MOTOR_REV_PWM_PIN);
}

void MotorHW_Stop(void)
{
    motor_hw_disable();
}
