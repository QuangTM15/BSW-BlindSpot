/******************************************************************************
 * @file turn_input.c
 * @brief Turn signal input module
 *
 * Functionality:
 *  - Read turn signal inputs
 *  - Update turn signal state into VehicleState
 ******************************************************************************/

#include "vehicle_state.h"

/**
 * @brief Initialize turn signal input hardware
 *
 * Function:
 *  - Prepare hardware resources required to read turn signal inputs
 *
 * What this function MUST do:
 *  - Configure GPIO pins for turn signal buttons or switches
 *
 * What this function MUST NOT do:
 *  - Read turn signal inputs
 *  - Modify VehicleState
 *
 * VehicleState impact:
 *  - NONE
 */
void TurnInput_Init(void)
{
    /* To be implemented */
}

/**
 * @brief Update turn signal state
 *
 * Function:
 *  - Read turn signal input values
 *  - Translate raw input values into logical turn signal state
 *
 * What this function MUST do:
 *  - Read left and right turn signal inputs
 *  - Determine active turn signal:
 *      + TURN_LEFT
 *      + TURN_RIGHT
 *      + TURN_NONE
 *  - Update VehicleState
 *
 * VehicleState fields updated:
 *  - state->turnSignal
 *  - state->validFlags |= VS_VALID_TURN
 *
 * What this function MUST NOT do:
 *  - Reconfigure hardware
 *  - Perform system or BSW logic
 */
void TurnInput_Update(VehicleState_t *state)
{
    (void)state;
    /* To be implemented */
}
