#include "manager/input_manager.h"
#include <stddef.h>

/* ================= INPUT MODULES ================= */
#include "input/input_cmd.h"
#include "input/turn_input.h"
#include "input/ultrasonic_input.h"
#include "input/motor_input.h"

/* =================================================
 * INIT
 * ================================================= */
void InputManager_Init(void)
{
    InputCmd_Init();        /* UART1 command */
    TurnInput_Init();       /* Button */
    UltrasonicInput_Init(); /* Sensor */
    Motor_Input_Init();     /* Motor HW safe state */
}

/* =================================================
 * UPDATE
 * ================================================= */
void InputManager_Update(VehicleState_t *state)
{
    if (state == NULL)
        return;

    InputCmd_Update();

    TurnInput_Update(state);

    UltrasonicInput_Update(state);

    Motor_Input_Update();
}
