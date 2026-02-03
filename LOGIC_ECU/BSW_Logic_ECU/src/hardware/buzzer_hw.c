#include "hardware/buzzer_hw.h"
#include "utils/pinConfig.h"
#include "pins_driver.h"

/* Active LOW */
#define BUZZER_ON()   PINS_DRV_ClearPins(PIN_BUZZER_PORT, 1U << PIN_BUZZER_PIN)
#define BUZZER_OFF()  PINS_DRV_SetPins(PIN_BUZZER_PORT, 1U << PIN_BUZZER_PIN)

void BuzzerHW_Init(void)
{
    BuzzerHW_Set(false);
}

void BuzzerHW_Set(bool on)
{
    on ? BUZZER_ON() : BUZZER_OFF();
}
