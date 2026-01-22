/******************************************************************************
 * @file speed_input.c
 * @brief Vehicle speed input module
 *
 * Functionality:
 *  - Measure vehicle speed using encoder or speed sensor
 *  - Update speed information into VehicleState
 ******************************************************************************/

#include "state/vehicle_state.h"

/**
 * @brief Initialize speed measurement hardware
 *
 * Function:
 *  - Prepare hardware resources required for speed measurement
 *
 * What this function MUST do:
 *  - Configure encoder input pins
 *  - Configure timer or interrupt for pulse counting
 *
 * What this function MUST NOT do:
 *  - Read speed data
 *  - Modify VehicleState
 *
 * VehicleState impact:
 *  - NONE
 */
void SpeedInput_Init(void)
{
    /* To be implemented */
}

/**
 * @brief Update vehicle speed
 *
 * Function:
 *  - Read raw speed sensor data
 *  - Convert raw data into km/h
 *
 * What this function MUST do:
 *  - Read encoder pulse count or raw speed value
 *  - Calculate vehicle speed in km/h
 *  - Update VehicleState
 *
 * VehicleState fields updated:
 *  - state->speed_kmh
 *  - state->validFlags |= VS_VALID_SPEED
 *
 * What this function MUST NOT do:
 *  - Reconfigure hardware
 *  - Perform system or BSW logic
 */
void SpeedInput_Update(VehicleState_t *state)
{
    (void)state;
    /* To be implemented */
}
