#include "sdk_project_config.h"

/* ===== STATE ===== */
#include "state/vehicle_state.h"

/* ===== INPUT ===== */
#include "input/turn_input.h"
#include "input/ultrasonic_input.h"

/* ===== UART ===== */
#include "peripherals_lpuart_1.h"
#include "lpuart_driver.h"

#include <stdio.h>
#include <string.h>

#include "utils/ultrasonic_hw.h"   // DEBUG ONLY

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

    UART_SendString("\r\n====================================\r\n");
    UART_SendString("  BSW INPUT ECU - ULTRASONIC TEST    \r\n");
    UART_SendString("====================================\r\n");

    /* ================= GLOBAL STATE INIT ================= */
    gVehicleState.validFlags    = VS_VALID_NONE;
    gVehicleState.obstacleFlags = OBS_NONE;
    gVehicleState.turnSignal    = TURN_NONE;

    /* ================= INTERRUPTS ================= */
    INT_SYS_EnableIRQ(PORTC_IRQn);   /* Turn buttons */
    /* PORTD IRQ NOT needed for ultrasonic (FTM IC) */

    /* ================= INPUT INIT ================= */
    TurnInput_Init();
    UltrasonicInput_Init();

    UART_SendString("Init done. Measuring LEFT & RIGHT...\r\n\r\n");

    /* ================= MAIN LOOP ================= */
    while (1)
    {
        /* Update ultrasonic input → cập nhật state */
        UltrasonicInput_Update(&gVehicleState);

        /* ===== DEBUG FLAGS ===== */
        if (gVehicleState.obstacleFlags & OBS_LEFT)
        {
            UART_SendString("[FLAG] LEFT  : OBSTACLE\r\n");
        }
        else
        {
            UART_SendString("[FLAG] LEFT  : CLEAR\r\n");
        }

        if (gVehicleState.obstacleFlags & OBS_RIGHT)
        {
            UART_SendString("[FLAG] RIGHT : OBSTACLE\r\n");
        }
        else
        {
            UART_SendString("[FLAG] RIGHT : CLEAR\r\n");
        }

        UART_SendString("------------------------------------\r\n");

        DelayMs(300);
    }
}
