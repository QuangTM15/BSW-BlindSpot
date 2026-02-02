#ifndef FRAME_RX_H
#define FRAME_RX_H

#include <stdint.h>
#include <stdbool.h>

#include "../state/vehicle_state.h"

/* Push one byte into RX state machine */
void FrameRx_PushByte(uint8_t b);

/* Check if a full frame is received */
bool FrameRx_IsFrameReady(void);

/* Copy received state, return true if available */
bool FrameRx_GetVehicleState(VehicleState_t *outState);

/* Reset RX state machine */
void FrameRx_Reset(void);

#endif /* FRAME_RX_H */
