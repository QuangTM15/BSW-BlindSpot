#ifndef ULTRASONIC_HW_H
#define ULTRASONIC_HW_H

#include <stdint.h>
#include "state/vehicle_state.h"


void UltrasonicHW_Init(void);

uint16_t UltrasonicHW_GetDistanceCm(ObstacleFlag_t direction);

#endif
