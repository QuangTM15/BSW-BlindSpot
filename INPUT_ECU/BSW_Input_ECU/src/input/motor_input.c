/******************************************************************************
 * @file motor_input.c
 * @brief Motor input module
 *
 * Functionality:
 *  - Read motor-related hardware signals
 *  - Update motor run state and vehicle motion into VehicleState
 *
 * This module is responsible ONLY for collecting motor input data.
 * It MUST NOT perform any system or BSW decision logic.
 ******************************************************************************/

#include "state/vehicle_state.h"

/**
 * @brief Initialize motor input hardware
 *
 * Function:
 *  - Prepare all hardware resources required to read motor inputs
 *
 * What this function MUST do:
 *  - Configure GPIO pins related to motor enable and direction
 *  - Configure timers or peripherals if required
 *
 * What this function MUST NOT do:
 *  - Read motor signals
 *  - Modify VehicleState
 *
 * VehicleState impact:
 *  - NONE
 */
void MotorInput_Init(void)
{
    /* To be implemented */
}

/**
 * @brief Update motor state
 *
 * Function:
 *  - Read motor control or feedback signals
 *  - Determine motor run status and motion direction
 *
 * What this function MUST do:
 *  - Read motor enable signal
 *  - Read motor direction signal(s)
 *  - Determine:
 *      + Motor running or stopped
 *      + Vehicle motion: FORWARD / BACKWARD / STOP
 *  - Update VehicleState fields
 *
 * VehicleState fields updated:
 *  - state->motorRun
 *  - state->motion
 *  - state->validFlags |= VS_VALID_MOTOR
 *
 * What this function MUST NOT do:
 *  - Reconfigure hardware
 *  - Perform system or BSW logic
 */
void MotorInput_Update(VehicleState_t *state)
{
    (void)state;
    /* To be implemented */
}
