#ifndef VEHICLE_STATE_H
#define VEHICLE_STATE_H

#include <stdint.h>
#include <stdbool.h>

/* ================= ENUM ================= */

/* MOTOR STATE */
typedef enum
{
    MOTOR_STOP = 0,
    MOTOR_RUN
} MotorRunState_t;

/* VEHICLE MOTION */
typedef enum
{
    MOTION_STOP = 0,
    MOTION_FORWARD,
    MOTION_BACKWARD
} VehicleMotion_t;

/* OBSTACLE FLAG (BITMASK) */
typedef enum
{
    OBS_NONE  = 0x00,
    OBS_FRONT = 0x01,
    OBS_REAR  = 0x02,
    OBS_LEFT  = 0x04,
    OBS_RIGHT = 0x08
} ObstacleFlag_t;

/* TURN SIGNAL */
typedef enum
{
    TURN_NONE  = 0,
    TURN_LEFT  = 1,
    TURN_RIGHT = 2
} TurnSignal_t;

/* VALID FLAG */
typedef enum
{
    VS_VALID_NONE       = 0x00,
    VS_VALID_MOTOR      = 0x01,
    VS_VALID_SPEED      = 0x02,
    VS_VALID_ULTRASONIC = 0x04,
    VS_VALID_TURN       = 0x08
} VehicleStateValidFlag_t;

/* ================= MAIN VEHICLE STATE ================= */

typedef struct
{
    /* ---------- META ---------- */
    uint32_t seq;               // update counter
    uint32_t lastUpdate_ms;     // timestamp
    uint8_t  validFlags;        // VehicleStateValidFlag_t

    /* ---------- MOTOR / MOTION ---------- */
    MotorRunState_t motorRun;
    VehicleMotion_t motion;

    /* ---------- SPEED ---------- */
    uint16_t speed_kmh;

    /* ---------- ULTRASONIC FLAGS ---------- */
    uint8_t obstacleFlags;      // ObstacleFlag_t (bitmask)

    /* ---------- ULTRASONIC DISTANCE (cm) ---------- */
    int16_t us_front_cm;        // front distance
    int16_t us_rear_cm;         // rear distance (USED FOR REVERSE)

    /* ---------- TURN SIGNAL ---------- */
    TurnSignal_t turnSignal;

} VehicleState_t;

/* GLOBAL VEHICLE STATE */
extern VehicleState_t gVehicleState;

#endif /* VEHICLE_STATE_H */
