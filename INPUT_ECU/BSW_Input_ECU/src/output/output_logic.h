#ifndef OUTPUT_LOGIC_H
#define OUTPUT_LOGIC_H

#include "state/vehicle_state.h"

/* =================================================
 * OUTPUT LOGIC
 * - Handle warning LED
 * - Handle buzzer
 * - Handle turn indicator LED
 * ================================================= */

/**
 * @brief Update all output logic based on vehicle state
 *
 * @param state Pointer to VehicleState
 */
void OutputLogic_Update(const VehicleState_t *state);

#endif /* OUTPUT_LOGIC_H */
