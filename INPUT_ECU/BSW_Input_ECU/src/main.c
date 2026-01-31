#include "sdk_project_config.h"

/* ===== INPUT ===== */
#include "input/motor_input.h"
#include "input/input_cmd.h"

/* ===== HARDWARE ===== */
#include "hardware/motor_hw.h"

/* ===== UART ===== */
#include "peripherals_lpuart_1.h"
#include "lpuart_driver.h"

#include <string.h>
#include "lpuart_hw_access.h"
#include "state/vehicle_state.h"

/* =========================================================
 * UART BOOT MESSAGE
 * ========================================================= */
static void UART_SendString(const char *str)
{
    LPUART_DRV_SendDataBlocking(
        INST_LPUART_1,
        (uint8_t *)str,
        strlen(str),
        1000U
    );
}

int main(void)
{
    /* ===== SYSTEM INIT ===== */
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

    LPUART_DRV_Init(
        INST_LPUART_1,
        &lpUartState1,
        &lpuart_1_InitConfig0
    );
    LPUART_SetReceiverCmd(LPUART1, true);

    MotorHW_Init();
    InputCmd_Init();
    Motor_Input_Init();

    UART_SendString("\r\n=== MOTOR TEST MODE ===\r\n");
    UART_SendString("Send: f / r / s\r\n");

    while (1)
    {
        InputCmd_Update();
        Motor_Input_Update();

        /* ===== LED TEST DIRECT ===== */
        PINS_DRV_SetPins(PTD, (1U << 15) | (1U << 16) | (1U << 0));

        switch (gVehicleState.motion)
        {
            case MOTION_FORWARD:
                PINS_DRV_ClearPins(PTD, 1U << 15);
                break;

            case MOTION_BACKWARD:
                PINS_DRV_ClearPins(PTD, 1U << 16);
                break;

            case MOTION_STOP:
            default:
                PINS_DRV_ClearPins(PTD, 1U << 0);
                break;
        }
    }
}
