#include "motor_input.h"

/* ===== SDK ===== */
#include "sdk_project_config.h"
#include <stdbool.h>

/* ===== project ===== */
#include "hardware/motor_hw.h"
#include "input/input_cmd.h"

static VehicleMotion_t lastMotion = MOTION_STOP;

void Motor_Input_Init(void)
{
    lastMotion = MOTION_STOP;
    MotorHW_Stop();
}

bool Motor_Input_Update( VehicleMotion_t *motion_out, MotorRunState_t *run_out)
{
    InputCmd_t cmd;
    VehicleMotion_t newMotion = lastMotion;

    if (!InputCmd_Get(&cmd))
        return false;

    switch (cmd)
    {
        case CMD_MOTOR_FORWARD:
            newMotion = MOTION_FORWARD;
            break;

        case CMD_MOTOR_BACKWARD:
            newMotion = MOTION_BACKWARD;
            break;

        case CMD_MOTOR_STOP:
            newMotion = MOTION_STOP;
            break;

        default:
            return false;
    }

    if (newMotion == lastMotion)
        return false;

    /* ==== Apply to hardware immediately ==== */
    switch (newMotion)
    {
        case MOTION_FORWARD:
            MotorHW_Forward();
            *run_out = MOTOR_RUN;
            break;

        case MOTION_BACKWARD:
            MotorHW_Reverse();
            *run_out = MOTOR_RUN;
            break;

        case MOTION_STOP:
        default:
            MotorHW_Stop();
            *run_out = MOTOR_STOP;
            break;
    }

    *motion_out = newMotion;
    lastMotion  = newMotion;

    return true;
}
