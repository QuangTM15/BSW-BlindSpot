#include "sdk_project_config.h"
#include "state/vehicle_state.h"
#include "input/turn_input.h"


int main(void)
{
    /* Clock init */
    CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
                   g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
    CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

    /* Pin mux init */
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

    /* Init state */
    gVehicleState.turnSignal = TURN_NONE;
    gVehicleState.validFlags = VS_VALID_NONE;

    /* Init turn input */
    TurnInput_Init();

    /* Enable PORTC interrupt (PTC12 / PTC13) */
    INT_SYS_EnableIRQ(PORTC_IRQn);

    for (;;)
    {
        /* Update turn input */
        TurnInput_Update(&gVehicleState);

        /* ===== TEST OUTPUT (NOT REAL LOGIC) ===== */
        switch (gVehicleState.turnSignal)
        {
            case TURN_LEFT:
                PINS_DRV_SetPins(PTD, (1UL << 15));
                PINS_DRV_ClearPins(PTD, (1UL << 16));
                break;

            case TURN_RIGHT:
                PINS_DRV_SetPins(PTD, (1UL << 16));
                PINS_DRV_ClearPins(PTD, (1UL << 15));
                break;

            case TURN_NONE:
            default:
                PINS_DRV_SetPins(PTD, (1UL << 15));
                PINS_DRV_SetPins(PTD, (1UL << 16));
                break;
        }
    }
}
