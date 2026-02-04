#include "motor_input.h"

/* ===== SDK ===== */
#include "sdk_project_config.h"
#include <string.h>
#include <stdbool.h>

/* ===== project ===== */
#include "hardware/motor_hw.h"
#include "state/vehicle_state.h"
#include "input/input_cmd.h"

#define MOTOR_UART_INST INST_LPUART_1
#define ACK_TIMEOUT     100U

static VehicleMotion_t lastMotion = MOTION_STOP;

static void Motor_SendAck(const char *s)
{
    (void)LPUART_DRV_SendDataBlocking(
        MOTOR_UART_INST,
        (uint8_t *)s,
        strlen(s),
        ACK_TIMEOUT
    );
}

void Motor_Input_Init(void)
{
    lastMotion = MOTION_STOP;
    MotorHW_Stop();

    gVehicleState.motorRun = MOTOR_STOP;
    gVehicleState.motion   = MOTION_STOP;
    gVehicleState.validFlags |= VS_VALID_MOTOR;
}

void Motor_Input_Update(void)
{
    InputCmd_t cmd;
    VehicleMotion_t newMotion = lastMotion;

    if (!InputCmd_Get(&cmd))
        return;

    switch (cmd)
    {
        case CMD_MOTOR_FORWARD:  newMotion = MOTION_FORWARD;  break;
        case CMD_MOTOR_BACKWARD: newMotion = MOTION_BACKWARD; break;
        case CMD_MOTOR_STOP:     newMotion = MOTION_STOP;     break;
        default: return;
    }

    if (newMotion == lastMotion)
        return;

    switch (newMotion)
    {
        case MOTION_FORWARD:
            MotorHW_Forward();
            gVehicleState.motorRun = MOTOR_RUN;
            gVehicleState.motion   = MOTION_FORWARD;
            Motor_SendAck("ACK FORWARD\r\n");
            break;

        case MOTION_BACKWARD:
            MotorHW_Reverse();
            gVehicleState.motorRun = MOTOR_RUN;
            gVehicleState.motion   = MOTION_BACKWARD;
            Motor_SendAck("ACK BACKWARD\r\n");
            break;

        case MOTION_STOP:
        default:
            MotorHW_Stop();
            gVehicleState.motorRun = MOTOR_STOP;
            gVehicleState.motion   = MOTION_STOP;
            Motor_SendAck("ACK STOP\r\n");
            break;
    }

    gVehicleState.seq++;
    gVehicleState.validFlags |= VS_VALID_MOTOR;
    lastMotion = newMotion;
}
