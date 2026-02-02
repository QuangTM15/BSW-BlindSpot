#include "manager/input_manager.h"

/* Project state */
#include "state/vehicle_state.h"

/* Input modules */
#include "input/motor_input.h"
#include "input/turn_input.h"
#include "input/ultrasonic_input.h"
#include "input/input_cmd.h"

static const ObstacleFlag_t s_ultraDirs[] =
{
    OBS_LEFT,
    OBS_RIGHT,
    OBS_FRONT,
    OBS_REAR
};

void InputManager_Init(void)
{
    /* Init vehicle state */
    gVehicleState.seq           = 0;
    gVehicleState.validFlags    = VS_VALID_NONE;
    gVehicleState.obstacleFlags = OBS_NONE;
    gVehicleState.us_front_cm   = -1;
    gVehicleState.us_rear_cm    = -1;

    /* Init input modules */
    InputCmd_Init();
    Motor_Input_Init();
    TurnInput_Init();
    UltrasonicInput_Init();
}

bool InputManager_Update(void)
{
    bool stateChanged = false;

    /* ===== MOTOR ===== */
    {
        VehicleMotion_t motion;
        MotorRunState_t run;

        if (Motor_Input_Update(&motion, &run))
        {
            gVehicleState.motion   = motion;
            gVehicleState.motorRun = run;
            gVehicleState.validFlags |= VS_VALID_MOTOR;
            stateChanged = true;
        }
    }

    /* ===== TURN SIGNAL ===== */
    {
        TurnSignal_t turn;

        if (TurnInput_Update(&turn))
        {
            gVehicleState.turnSignal = turn;
            gVehicleState.validFlags |= VS_VALID_TURN;
            stateChanged = true;
        }
    }

    /* ===== ULTRASONIC ===== */
    {
        UltrasonicResult_t res;

        /* Clear obstacle flags each cycle */
        gVehicleState.obstacleFlags &=
            ~(OBS_LEFT | OBS_RIGHT | OBS_FRONT | OBS_REAR);

        for (uint32_t i = 0; i < (sizeof(s_ultraDirs) / sizeof(s_ultraDirs[0])); i++)
        {
            ObstacleFlag_t dir = s_ultraDirs[i];

            if (!UltrasonicInput_Get(dir, &res))
                continue;

            if (res.valid)
            {
                /* Store distance for front and rear */
                if (dir == OBS_FRONT)
                    gVehicleState.us_front_cm = res.distance_cm;
                else if (dir == OBS_REAR)
                    gVehicleState.us_rear_cm = res.distance_cm;

                /* Set obstacle flag */
                if (res.obstacle)
                    gVehicleState.obstacleFlags |= dir;
            }
        }

        gVehicleState.validFlags |= VS_VALID_ULTRASONIC;
        stateChanged = true;
    }

    /* ===== UPDATE SEQUENCE ===== */
    if (stateChanged)
    {
        gVehicleState.seq++;
    }

    return stateChanged;
}
