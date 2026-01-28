#include "input/ultrasonic_input.h"
#include "utils/ultrasonic_hw.h"
#include "state/vehicle_state.h"
#include <stddef.h>
#include <stdbool.h>

#define OBSTACLE_THRESHOLD_CM 10U
#define US_INVALID_DISTANCE   0xFFFFU

void UltrasonicInput_Init(void)
{
    UltrasonicHW_Init();
}

void UltrasonicInput_Update(VehicleState_t *state)
{
    if (state == NULL)
        return;

    /* Clear ultrasonic flags */
    state->obstacleFlags &=
        ~(OBS_LEFT | OBS_RIGHT | OBS_FRONT | OBS_REAR);

    uint16_t dist;

    /* ================= LEFT ================= */
    dist = UltrasonicHW_GetDistanceCm(OBS_LEFT);
    if (dist != US_INVALID_DISTANCE && dist <= OBSTACLE_THRESHOLD_CM)
    {
        state->obstacleFlags |= OBS_LEFT;
    }

    /* ================= RIGHT ================= */
    dist = UltrasonicHW_GetDistanceCm(OBS_RIGHT);
    if (dist != US_INVALID_DISTANCE && dist <= OBSTACLE_THRESHOLD_CM)
    {
        state->obstacleFlags |= OBS_RIGHT;
    }


    /* ================= FRONT ================= */
      dist = UltrasonicHW_GetDistanceCm(OBS_FRONT);
      if (dist != US_INVALID_DISTANCE)
      {
          state->us_front_cm = dist;
          if (dist <= OBSTACLE_THRESHOLD_CM)
          {
              state->obstacleFlags |= OBS_FRONT;
          }
      }
      else
      {
          state->us_front_cm = -1;
      }

      /* ================= REAR ================= */
      dist = UltrasonicHW_GetDistanceCm(OBS_REAR);
      if (dist != US_INVALID_DISTANCE)
      {
          state->us_rear_cm = dist;
          if (dist <= OBSTACLE_THRESHOLD_CM)
          {
              state->obstacleFlags |= OBS_REAR;
          }
      }
      else
      {
          state->us_rear_cm = -1;
      }
    state->validFlags |= VS_VALID_ULTRASONIC;
}
