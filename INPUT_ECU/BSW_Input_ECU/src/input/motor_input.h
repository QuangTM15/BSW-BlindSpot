#ifndef MOTOR_INPUT_H
#define MOTOR_INPUT_H

#include "state/vehicle_state.h"
#include <stdbool.h>

void Motor_Input_Init(void);

bool Motor_Input_Update(VehicleMotion_t *motion_out,MotorRunState_t *run_out);

#endif
