#include "vehicle_state.h"

VehicleState_t gVehicleState =
{
    .seq = 0,
    .lastUpdate_ms = 0,
    
    .validFlags = VS_VALID_NONE,

    .motorRun = MOTOR_STOP,
    .motion = MOTION_STOP,
    .speed_kmh = 0,
    .obstacleFlags = OBS_NONE,
    .turnSignal = TURN_NONE
};   