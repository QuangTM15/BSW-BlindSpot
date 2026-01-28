#include "vehicle_state.h"

VehicleState_t gVehicleState =
{
    /* ---------- META ---------- */
    .seq = 0,
    .lastUpdate_ms = 0,
    .validFlags = VS_VALID_NONE,

    /* ---------- MOTOR / MOTION ---------- */
    .motorRun = MOTOR_STOP,
    .motion = MOTION_STOP,

    /* ---------- SPEED ---------- */
    .speed_kmh = 0,

    /* ---------- ULTRASONIC ---------- */
    .obstacleFlags = OBS_NONE,
    .us_front_cm = -1,
    .us_rear_cm  = -1,

    /* ---------- TURN ---------- */
    .turnSignal = TURN_NONE
};