#include "utils/ultrasonic_hw.h"
#include "sdk_project_config.h"
#include "peripherals_flexTimer_ic_1.h"
#include "utils/pinConfig.h"
#include "state/vehicle_state.h"

#define US_INVALID_DISTANCE   0xFFFFU
#define TICKS_TO_CM_DIV       330U

ftm_state_t state0;

/* Trigger HC-SR04 */
static void UltrasonicHW_Trigger(void)
{
    PINS_DRV_SetPins(US_TRIG_PORT, (1UL << US_TRIG_PIN));
    for (volatile int i = 0; i < 200; i++); // ~10us
    PINS_DRV_ClearPins(US_TRIG_PORT, (1UL << US_TRIG_PIN));
}
//Delay minute
static void UltrasonicHW_DelayMs(uint32_t ms)
{
    volatile uint32_t i;
    while (ms--)
        for (i = 0; i < 8000; i++) __asm("nop");
}
static uint8_t UltrasonicHW_GetChannel(ObstacleFlag_t dir)
{
    switch (dir)
    {
        case OBS_LEFT:  return 4U; // FTM2 CH4
        case OBS_RIGHT: return 2U; // FTM2 CH2
        default:        return 0xFF;
    }
}

void UltrasonicHW_Init(void)
{
    FTM_DRV_Init(
        INST_FLEXTIMER_IC_1,
        &flexTimer_ic_1_InitConfig,
        &state0
    );

    FTM_DRV_InitInputCapture(
        INST_FLEXTIMER_IC_1,
        &flexTimer_ic_1_InputCaptureConfig
    );
}

static void UltrasonicHW_DelayUs(uint32_t us)
{
    volatile uint32_t i;
    while (us--)
        for (i = 0; i < 8; i++) __asm("nop");
}

static inline void UltrasonicHW_TriggerFB(void)
{
    PINS_DRV_SetPins(US_FB_TRIG_PORT, (1UL << US_FB_TRIG_PIN));
    UltrasonicHW_DelayUs(10);
    PINS_DRV_ClearPins(US_FB_TRIG_PORT, (1UL << US_FB_TRIG_PIN));
}

static uint16_t UltrasonicHW_MeasureEchoCm(GPIO_Type *gpio, uint32_t pin)
{
    uint32_t time_us = 0;
    uint32_t timeout = 30000;

    /* wait echo HIGH */
    while (!(PINS_DRV_ReadPins(gpio) & (1UL << pin)))
    {
        if (--timeout == 0)
            return US_INVALID_DISTANCE;
        UltrasonicHW_DelayUs(1);
    }

    timeout = 30000;
    /* measure HIGH width */
    while (PINS_DRV_ReadPins(gpio) & (1UL << pin))
    {
        UltrasonicHW_DelayUs(1);
        time_us++;
        if (--timeout == 0)
            break;
    }

    return (uint16_t)((time_us * 3U) / 58U);
}

uint16_t UltrasonicHW_GetDistanceCm(ObstacleFlag_t direction)
{
    /* ===== FRONT / REAR : GPIO polling ===== */
    if (direction == OBS_FRONT)
    {
        UltrasonicHW_TriggerFB();
        return UltrasonicHW_MeasureEchoCm(
            US_FRONT_ECHO_PORT,
            US_FRONT_ECHO_PIN
        );
    }

    if (direction == OBS_REAR)
    {
        UltrasonicHW_TriggerFB();
        return UltrasonicHW_MeasureEchoCm(
            US_REAR_ECHO_PORT,
            US_REAR_ECHO_PIN
        );
    }

    uint8_t channel = UltrasonicHW_GetChannel(direction);
    if (channel == 0xFF)
        return US_INVALID_DISTANCE;

    FTM_DRV_StartNewSignalMeasurement(
        INST_FLEXTIMER_IC_1,
        channel
    );

    UltrasonicHW_Trigger();

    UltrasonicHW_DelayMs(40);

    uint16_t ticks =
        FTM_DRV_GetInputCaptureMeasurement(
            INST_FLEXTIMER_IC_1,
            channel
        );

    if (ticks == 0)
        return US_INVALID_DISTANCE;

    return ticks / TICKS_TO_CM_DIV;
}
