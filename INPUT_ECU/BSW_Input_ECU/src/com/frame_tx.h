#ifndef FRAME_TX_H
#define FRAME_TX_H

#include <stdint.h>
#include "state/vehicle_state.h"

/* Frame type */
#define FRAME_TYPE_STATE   0x01

/* Send full vehicle state frame */
void FrameTx_SendVehicleState(const VehicleState_t *state);

#endif /* FRAME_TX_H */
