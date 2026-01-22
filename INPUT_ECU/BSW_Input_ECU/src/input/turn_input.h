/*
 * turn_input.h
 *
 *  Created on: Jan 22, 2026
 *      Author: -Asus
 */

#ifndef INPUT_TURN_INPUT_H_
#define INPUT_TURN_INPUT_H_

#include "state/vehicle_state.h"

void TurnInput_Init(void);
void TurnInput_Update(VehicleState_t *state);

#endif /* INPUT_TURN_INPUT_H_ */
