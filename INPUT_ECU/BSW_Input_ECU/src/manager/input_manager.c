#include "manager/input_manager.h"
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

/* INPUT MODULES */
#include "input/ultrasonic_input.h"
#include "input/turn_input.h"

void InputManager_Init(void)
{
    TurnInput_Init();
    UltrasonicInput_Init();
}

void InputManager_Update(VehicleState_t *state)
{
    if (state == NULL)
        return;

    UltrasonicInput_Update(state);
    TurnInput_Update(state);
}
