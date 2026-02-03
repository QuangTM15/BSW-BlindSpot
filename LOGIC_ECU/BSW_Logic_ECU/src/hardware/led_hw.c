#include "hardware/led_hw.h"
#include "utils/pinConfig.h"
#include "pins_driver.h"
#include "pin_mux.h"
#include "peripherals_flexTimer_pwm_1.h"

/* Distance and PWM configuration */
#define REVERSE_DETECT_MAX_CM   20U
#define REVERSE_DETECT_MIN_CM   2U

#define REVERSE_PWM_MIN_DUTY    1U
#define REVERSE_PWM_MAX_DUTY    100U

//active high led
#define LED_ON(port, pin)   PINS_DRV_SetPins(port, 1U << pin)
#define LED_OFF(port, pin)  PINS_DRV_ClearPins(port, 1U << pin)

void LedHW_Init(void)
{
    LedHW_MirrorLeft_Set(false);
    LedHW_MirrorRight_Set(false);
    LedHW_TurnLeft_Set(false);
    LedHW_TurnRight_Set(false);
    LedHW_DoorLeft_Set(false);
    LedHW_DoorRight_Set(false);
    LedHW_Reverse_SetByDistance(100U);
}

/* Mirror LEDs */
void LedHW_MirrorLeft_Set(bool on)
{
    on ? LED_ON(PIN_MIRROR_LEFT_PORT, PIN_MIRROR_LEFT_PIN)
       : LED_OFF(PIN_MIRROR_LEFT_PORT, PIN_MIRROR_LEFT_PIN);
}

void LedHW_MirrorRight_Set(bool on)
{
    on ? LED_ON(PIN_MIRROR_RIGHT_PORT, PIN_MIRROR_RIGHT_PIN)
       : LED_OFF(PIN_MIRROR_RIGHT_PORT, PIN_MIRROR_RIGHT_PIN);
}

/* Turn LEDs */
void LedHW_TurnLeft_Set(bool on)
{
    on ? LED_ON(PIN_TURN_LEFT_PORT, PIN_TURN_LEFT_PIN)
       : LED_OFF(PIN_TURN_LEFT_PORT, PIN_TURN_LEFT_PIN);
}

void LedHW_TurnRight_Set(bool on)
{
    on ? LED_ON(PIN_TURN_RIGHT_PORT, PIN_TURN_RIGHT_PIN)
       : LED_OFF(PIN_TURN_RIGHT_PORT, PIN_TURN_RIGHT_PIN);
}

/* Door LEDs */
void LedHW_DoorLeft_Set(bool on)
{
    on ? LED_ON(PIN_DOOR_LEFT_PORT, PIN_DOOR_LEFT_PIN)
       : LED_OFF(PIN_DOOR_LEFT_PORT, PIN_DOOR_LEFT_PIN);
}

void LedHW_DoorRight_Set(bool on)
{
    on ? LED_ON(PIN_DOOR_RIGHT_PORT, PIN_DOOR_RIGHT_PIN)
       : LED_OFF(PIN_DOOR_RIGHT_PORT, PIN_DOOR_RIGHT_PIN);
}

/* Reverse LED PWM */
void LedHW_Reverse_SetByDistance(uint8_t distanceCm)
{
    uint16_t ticks;
    if (distanceCm > REVERSE_DETECT_MAX_CM)
    {
        ticks = 0U;
    }
    else if (distanceCm <= REVERSE_DETECT_MIN_CM)
    {
        ticks = 32768U;
    }
    else
    {
        ticks =
            (uint16_t)(
                (REVERSE_DETECT_MAX_CM - distanceCm) *
                32768U /
                (REVERSE_DETECT_MAX_CM - REVERSE_DETECT_MIN_CM)
            );
    }

    FTM_DRV_UpdatePwmChannel(
        INST_FLEXTIMER_PWM_1,
        2U,
        FTM_PWM_UPDATE_IN_TICKS,
        ticks,
        0U,
        true
    );
}

