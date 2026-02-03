#include "logic/bsw_logic.h"
#include <string.h>

/* Obstacle flag helpers */
#define HAS_LEFT(obs)   ((obs) & OBS_LEFT)
#define HAS_RIGHT(obs)  ((obs) & OBS_RIGHT)
#define HAS_FRONT(obs)  ((obs) & OBS_FRONT)
#define HAS_REAR(obs)   ((obs) & OBS_REAR)

void BswLogic_Evaluate(const VehicleState_t *state,
                       BswOutput_t *out)
{
    /* Clear output */
    memset(out, 0, sizeof(BswOutput_t));

    /* =================================================
     * PRIORITY 1: REVERSE WARNING
     * ================================================= */
    if (state->motion == MOTION_BACKWARD)
    {
        if (state->us_rear_cm > 0)
        {
            out->reverseActive     = true;
            out->reverseDistanceCm = (uint8_t)state->us_rear_cm;

            if (state->us_rear_cm <= 2)
            {
                out->buzzerOn = true;
            }
        }
        return;
    }

    /* =================================================
     * PRIORITY 2: VEHICLE STOP – DOOR WARNING
     * ================================================= */
    if (state->motion == MOTION_STOP)
    {
        if (HAS_LEFT(state->obstacleFlags))
        {
            out->doorLeft = true;
        }

        if (HAS_RIGHT(state->obstacleFlags))
        {
            out->doorRight = true;
        }

        if (HAS_FRONT(state->obstacleFlags) ||
            HAS_REAR(state->obstacleFlags))
        {
            out->doorLeft  = true;
            out->doorRight = true;
        }
        return;
    }

    /* =================================================
     * PRIORITY 3: BLIND SPOT WARNING (MOVING)
     * ================================================= */
    if (HAS_LEFT(state->obstacleFlags))
    {
        out->mirrorLeft = true;

        if (state->turnSignal == TURN_LEFT)
        {
            out->buzzerOn = true;
        }
    }

    if (HAS_RIGHT(state->obstacleFlags))
    {
        out->mirrorRight = true;

        if (state->turnSignal == TURN_RIGHT)
        {
            out->buzzerOn = true;
        }
    }
}
