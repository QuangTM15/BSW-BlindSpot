#include "manager/output_manager.h"

#include "logic/bsw_logic.h"

#include "hardware/led_hw.h"
#include "hardware/buzzer_hw.h"

#include <string.h>

void OutputManager_Init(void)
{
    LedHW_Init();
    BuzzerHW_Init();
}

void OutputManager_Update(const VehicleState_t *state)
{
    BswOutput_t out;

    if (state == NULL)
    {
        return;
    }

    /* Evaluate warning logic */
    BswLogic_Evaluate(state, &out);

    /* =================================================
     * Mirror LEDs
     * ================================================= */
    LedHW_MirrorLeft_Set(out.mirrorLeft);
    LedHW_MirrorRight_Set(out.mirrorRight);

    /* =================================================
     * Turn signal LEDs (optional visual feedback)
     * ================================================= */
    LedHW_TurnLeft_Set(out.turnLeft);
    LedHW_TurnRight_Set(out.turnRight);

    /* =================================================
     * Door warning LEDs
     * ================================================= */
    LedHW_DoorLeft_Set(out.doorLeft);
    LedHW_DoorRight_Set(out.doorRight);

    /* =================================================
     * Reverse warning LED (PWM)
     * ================================================= */
    if (out.reverseActive)
    {
        LedHW_Reverse_SetByDistance(out.reverseDistanceCm);
    }
    else
    {
        LedHW_Reverse_SetByDistance(100U); /* > max range -> LED off */
    }

    /* =================================================
     * Buzzer
     * ================================================= */
    BuzzerHW_Set(out.buzzerOn);
}
