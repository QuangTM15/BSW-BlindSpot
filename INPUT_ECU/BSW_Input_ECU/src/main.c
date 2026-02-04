#include "sdk_project_config.h"

#include "clock_manager.h"
#include "pins_driver.h"

#include "peripherals_lpuart_2.h"
#include "lpuart_hw_access.h"

#include "state/vehicle_state.h"
#include "com/uart_tx_polling.h"
#include "com/frame_tx.h"

#include <string.h>
#include <stdint.h>

/* ================= DELAY ================= */

static void DelayMs(uint32_t ms)
{
    for (volatile uint32_t i = 0; i < ms * 8000U; i++)
    {
        __asm("nop");
    }
}

/* ================= MAIN ================= */

int main(void)
{
    CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
                   g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
    CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

    /* UART2 init */
    LPUART_DRV_Init(INST_LPUART_2, &lpUartState2, &lpuart_2_InitConfig0);

    /* Enable TX */
    LPUART_SetTransmitterCmd(LPUART2, true);

    /* Init TX polling */
    UART_TxPolling_Init();

    /* Init vehicle state */
    memset(&gVehicleState, 0, sizeof(gVehicleState));

    gVehicleState.seq = 0;
    gVehicleState.speed_kmh = 10;
    gVehicleState.us_front_cm = 80;
    gVehicleState.us_rear_cm  = 120;

    while (1)
    {
        /* -------- TURN -------- */
        if (gVehicleState.turnSignal == TURN_NONE)
            gVehicleState.turnSignal = TURN_RIGHT;
        else
            gVehicleState.turnSignal = TURN_NONE;

        /* -------- MOTOR -------- */
        if (gVehicleState.motorRun == MOTOR_STOP)
            gVehicleState.motorRun = MOTOR_RUN;
        else
            gVehicleState.motorRun = MOTOR_STOP;

        /* -------- OBSTACLE -------- */
        if (gVehicleState.obstacleFlags == OBS_NONE)
            gVehicleState.obstacleFlags = OBS_FRONT | OBS_LEFT;
        else
            gVehicleState.obstacleFlags = OBS_NONE;

        /* -------- SPEED / DISTANCE (optional) -------- */
        gVehicleState.speed_kmh += 5;
        if (gVehicleState.speed_kmh > 60)
            gVehicleState.speed_kmh = 10;

        gVehicleState.us_front_cm -= 10;
        if (gVehicleState.us_front_cm < 20)
            gVehicleState.us_front_cm = 80;

        /* Update seq */
        gVehicleState.seq++;

        /* Send full frame */
        FrameTx_SendVehicleState(&gVehicleState);

        DelayMs(500);
    }
}
