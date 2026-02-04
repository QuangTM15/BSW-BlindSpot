#ifndef INPUT_ULTRASONIC_INPUT_H_
#define INPUT_ULTRASONIC_INPUT_H_

#include "state/vehicle_state.h"

void UltrasonicInput_Init(void);
void UltrasonicInput_Update(VehicleState_t *state);

#endif
