#include "output/output_logic.h"
#include "output/output_hw.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdbool.h>

void OutputLogic_Update(const VehicleState_t *state)
{
    if (state == NULL)
    {
        return;
    }

    bool buzzerOn = false;

    /* =================================================
     * TURN INDICATOR (ONBOARD LED)
     * ================================================= */
    switch (state->turnSignal)
    {
        case TURN_LEFT:
            OutputHW_TurnLeft_On();
            OutputHW_TurnRight_Off();
            break;

        case TURN_RIGHT:
            OutputHW_TurnRight_On();
            OutputHW_TurnLeft_Off();
            break;

        case TURN_NONE:
        default:
            OutputHW_TurnLeft_Off();
            OutputHW_TurnRight_Off();
            break;
    }

    /* =================================================
     * WARNING - LEFT SIDE
     * ================================================= */
    if (state->obstacleFlags & OBS_LEFT)
    {
        OutputHW_WarnLeft_On();

        /* Obstacle + same side turn => buzzer */
        if (state->turnSignal == TURN_LEFT)
        {
            buzzerOn = true;
        }
    }
    else
    {
        OutputHW_WarnLeft_Off();
    }

    /* =================================================
     * WARNING - RIGHT SIDE
     * ================================================= */
    if (state->obstacleFlags & OBS_RIGHT)
    {
        OutputHW_WarnRight_On();

        /* Obstacle + same side turn => buzzer */
        if (state->turnSignal == TURN_RIGHT)
        {
            buzzerOn = true;
        }
    }
    else
    {
        OutputHW_WarnRight_Off();
    }

    /* =================================================
     * BUZZER
     * ================================================= */
    if (buzzerOn)
    {
        OutputHW_Buzzer_On();
    }
    else
    {
        OutputHW_Buzzer_Off();
    }
}
