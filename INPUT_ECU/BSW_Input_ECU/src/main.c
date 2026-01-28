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

    UART_SendString("\r\n=== ULTRASONIC DEBUG: DIST + FLAG ===\r\n");

    /* ================= STATE INIT ================= */
    gVehicleState.obstacleFlags = OBS_NONE;
    gVehicleState.validFlags    = VS_VALID_NONE;
    gVehicleState.us_front_cm   = -1;
    gVehicleState.us_rear_cm    = -1;

    /* ================= ULTRASONIC INIT ================= */
    UltrasonicInput_Init();

    /* ================= MAIN LOOP ================= */
    while (1)
    {
        /* -------- READ ULTRASONIC -------- */
        UltrasonicInput_Update(&gVehicleState);

        /* -------- PRINT DISTANCE -------- */
        if (gVehicleState.us_front_cm > 0 &&
            gVehicleState.us_rear_cm > 0)
        {
            sprintf(
                uartBuf,
                "FRONT: %ld cm | REAR: %ld cm\r\n",
                gVehicleState.us_front_cm,
                gVehicleState.us_rear_cm
            );
        }
        else if (gVehicleState.us_front_cm > 0)
        {
            sprintf(
                uartBuf,
                "FRONT: %ld cm | REAR: No echo\r\n",
                gVehicleState.us_front_cm
            );
        }
        else if (gVehicleState.us_rear_cm > 0)
        {
            sprintf(
                uartBuf,
                "FRONT: No echo | REAR: %ld cm\r\n",
                gVehicleState.us_rear_cm
            );
        }
        else
        {
            sprintf(
                uartBuf,
                "FRONT: No echo | REAR: No echo\r\n"
            );
        }

        UART_SendString(uartBuf);

        /* -------- TEST FLAGS -> LED (ACTIVE LOW) -------- */

        /* REAR obstacle -> PTD15 */
        if (gVehicleState.obstacleFlags & OBS_REAR)
            PINS_DRV_ClearPins(PTD, (1UL << 15)); // LED ON
        else
            PINS_DRV_SetPins(PTD, (1UL << 15));   // LED OFF

        /* FRONT obstacle -> PTD16 */
        if (gVehicleState.obstacleFlags & OBS_FRONT)
            PINS_DRV_ClearPins(PTD, (1UL << 16)); // LED ON
        else
            PINS_DRV_SetPins(PTD, (1UL << 16));   // LED OFF

        /* HC-SR04 safe interval */
        DelayMs(120);
    }
}
