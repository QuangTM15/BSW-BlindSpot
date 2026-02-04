#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "state/vehicle_state.h"

void InputManager_Init(void);
void InputManager_Update(VehicleState_t *state);

#endif
