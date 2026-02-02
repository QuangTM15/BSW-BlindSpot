#ifndef ULTRASONIC_INPUT_H
#define ULTRASONIC_INPUT_H

#include <stdbool.h>
#include <stdint.h>
#include "state/vehicle_state.h"

typedef struct
{
    bool    valid;
    int16_t distance_cm;
    bool    obstacle;
} UltrasonicResult_t;

void UltrasonicInput_Init(void);

bool UltrasonicInput_Get(
    ObstacleFlag_t dir,
    UltrasonicResult_t *result
);

#endif
