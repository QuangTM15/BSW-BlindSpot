#ifndef OUTPUT_MANAGER_H
#define OUTPUT_MANAGER_H

#include "state/vehicle_state.h"

/* Initialize output hardware */
void OutputManager_Init(void);

/* Update outputs based on latest vehicle state */
void OutputManager_Update(const VehicleState_t *state);

#endif /* OUTPUT_MANAGER_H */
