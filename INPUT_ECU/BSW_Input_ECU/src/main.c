#include "sdk_project_config.h"

/* ===== STATE ===== */
#include "state/vehicle_state.h"

/* ===== INPUT ===== */
#include "manager/input_manager.h"
#include "input/turn_input.h"

/* ===== OUTPUT ===== */
#include "output/output_hw.h"
#include "output/output_logic.h"

/* ===== UART ===== */
#include "peripherals_lpuart_1.h"
#include "lpuart_driver.h"

#include <stdio.h>
#include <string.h>

/* =========================================================
 * UART DEBUG
 * ========================================================= */
static void UART_SendString(const char *str)
{
    LPUART_DRV_SendDataBlocking(
        1,
        (uint8_t *)str,
        strlen(str),
        1000
    );
}

/* =========================================================
 * CRUDE DELAY (DEBUG ONLY)
 * ========================================================= */
static void DelayMs(uint32_t ms)
{
    for (volatile uint32_t i = 0; i < ms * 8000U; i++)
    {
        __asm("nop");
    }
}

/* =========================================================
 * MAIN
 * ========================================================= */
int main(void)
{
    char uartBuf[128];

    /* ================= SYSTEM INIT ================= */
    CLOCK_SYS_Init(
        g_clockManConfigsArr,
        CLOCK_MANAGER_CONFIG_CNT,
        g_clockManCallbacksArr,
        CLOCK_MANAGER_CALLBACK_CNT
    );
    CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

    PINS_DRV_Init(
        NUM_OF_CONFIGURED_PINS0,
        g_pin_mux_InitConfigArr0
    );

    /* ================= UART INIT ================= */
    LPUART_DRV_Init(
        1,
        &lpUartState1,
        &lpuart_1_InitConfig0
    );


    /* ================= GLOBAL STATE INIT ================= */
    gVehicleState.validFlags    = VS_VALID_NONE;
    gVehicleState.obstacleFlags = OBS_NONE;
    gVehicleState.turnSignal    = TURN_NONE;

    /* ================= INTERRUPTS ================= */
    INT_SYS_EnableIRQ(PORTC_IRQn);   /* Turn buttons */

    /* ================= MODULE INIT ================= */
    InputManager_Init();     /* Ultrasonic + Turn input */
    OutputHW_Init();         /* Set all output OFF */


    /* ================= MAIN LOOP ================= */
    while (1)
    {
        /* 1. Read all inputs -> update state */
        InputManager_Update(&gVehicleState);

        /* 2. Handle all outputs based on state */
        OutputLogic_Update(&gVehicleState);
    }
}
