#include <hardware/ultrasonic_hw.h>
#include "input/ultrasonic_input.h"
#include "state/vehicle_state.h"
#include <stddef.h>
#include <stdbool.h>

#define OBSTACLE_THRESHOLD_CM  20U
#define US_INVALID_DISTANCE    0xFFFFU

void UltrasonicInput_Init(void)
{
    UltrasonicHW_Init();
}

bool UltrasonicInput_Get(
    ObstacleFlag_t dir,
    UltrasonicResult_t *result
)
{
    uint16_t dist;

    if (result == NULL)
        return false;

    /* Read distance from hardware */
    dist = UltrasonicHW_GetDistanceCm(dir);

    if (dist == US_INVALID_DISTANCE)
    {
        result->valid       = false;
        result->distance_cm = -1;
        result->obstacle    = false;
        return true;
    }

    result->valid       = true;
    result->distance_cm = (int16_t)dist;
    result->obstacle    = (dist <= OBSTACLE_THRESHOLD_CM);

    return true;
}
