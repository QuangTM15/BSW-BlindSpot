#include "input/ultrasonic_input.h"
#include "utils/ultrasonic_hw.h"
#include "state/vehicle_state.h"
#include <stddef.h>
#include <stdbool.h>

#define OBSTACLE_THRESHOLD_CM 20U

void UltrasonicInput_Init(void)
{
    UltrasonicHW_Init();
}

void UltrasonicInput_Update(VehicleState_t *state)
{
    if (state == NULL)
        return;

    /* Clear ultrasonic flags */
    state->obstacleFlags &= ~(OBS_LEFT | OBS_RIGHT);

    uint16_t dist;

    /* LEFT */
    dist = UltrasonicHW_GetDistanceCm(OBS_LEFT);
    if (dist < OBSTACLE_THRESHOLD_CM)
    {
        state->obstacleFlags |= OBS_LEFT;
    }

    /* RIGHT */
    dist = UltrasonicHW_GetDistanceCm(OBS_RIGHT);
    if (dist < OBSTACLE_THRESHOLD_CM)
    {
        state->obstacleFlags |= OBS_RIGHT;
    }

    state->validFlags |= VS_VALID_ULTRASONIC;
}
