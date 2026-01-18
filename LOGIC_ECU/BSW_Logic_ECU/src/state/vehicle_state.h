#ifndef VEHICLE_STATE_H
#define VEHICLE_STATE_H

#include <stdint.h>
#include <stdbool.h>

/* ================= ENUM================= */

//MOTOR STATE
typedef enum
{
    MOTOR_STOP = 0,
    MOTOR_RUN
} MotorRunState_t;

//HUONG CHUYEN DONG
typedef enum
{
    MOTION_STOP = 0,
    MOTION_FORWARD,
    MOTION_BACKWARD
} VehicleMotion_t;

//VAT CAN
typedef enum
{
    OBS_NONE  = 0x00,
    OBS_FRONT = 0x01,
    OBS_REAR  = 0x02,
    OBS_LEFT  = 0x04,
    OBS_RIGHT = 0x08
} ObstacleFlag_t;

//XI NHAN
typedef enum
{
    TURN_NONE  = 0,
    TURN_LEFT  = 1,
    TURN_RIGHT = 2
} TurnSignal_t;

//VALID DATA
typedef enum
{
    VS_VALID_NONE       = 0x00, //NONE VALID
    VS_VALID_MOTOR      = 0x01,
    VS_VALID_SPEED      = 0x02, //DATA IS VALID
    VS_VALID_ULTRASONIC = 0x04,
    VS_VALID_TURN       = 0x08
} VehicleStateValidFlag_t;

/* ================= MAIN STATE ================= */

typedef struct
{
	//SEND/RECIVE SIGNAL
    uint32_t seq; //number
    uint32_t lastUpdate_ms; //time
    uint8_t validFlags; //valid

    /* ----------MOTOR---------- */
    MotorRunState_t motorRun; //isRun
    VehicleMotion_t motion;

    /* ---------- SPEED ---------- */
    uint16_t speed_kmh;

    /* ---------- VAT CAN ---------- */
    uint8_t obstacleFlags;

    /* ---------- XI NHAN ---------- */
    TurnSignal_t turnSignal;

} VehicleState_t;

//GLOBAL STATE
extern VehicleState_t gVehicleState;

#endif /* VEHICLE_STATE_H */
