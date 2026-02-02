#include "sdk_project_config.h"
#include "clock_manager.h"
#include "pins_driver.h"

#include "peripherals_lpuart_2.h"
#include "lpuart_hw_access.h"

#include "com/uart_rx_polling.h"
#include "com/frame_rx.h"

#include "state/vehicle_state.h"


int main(void)
{
    uint8_t rxByte;

    /* Clock init */
    CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
                   g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
    CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

    /* Pin mux init */
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

    /* UART2 init */
    LPUART_DRV_Init(INST_LPUART_2, &lpUartState2, &lpuart_2_InitConfig0);

    /* Enable RX */
    LPUART_SetReceiverCmd(LPUART2, true);

    /* Turn LED off initially (SET = OFF) */
    PINS_DRV_SetPins(PTD, (1u << 15));
    PINS_DRV_SetPins(PTD, (1u << 16));
    PINS_DRV_SetPins(PTD, (1u << 0));

    /* Init state */
    gVehicleState.turnSignal = TURN_NONE;

    while (1)
    {
        /* Poll RX */
        if (UART_RxPolling_ReadByte(&rxByte))
        {
            FrameRx_PushByte(rxByte);
        }

        /* Frame received */
        if (FrameRx_IsFrameReady())
        {
            FrameRx_GetVehicleState(&gVehicleState);
            /* TURN */
            if (gVehicleState.turnSignal == TURN_RIGHT)
                PINS_DRV_SetPins(PTD, (1u << 15));
            else
            	PINS_DRV_ClearPins(PTD, (1u << 15));

            /* MOTOR */
            if (gVehicleState.motorRun == MOTOR_RUN)
            	PINS_DRV_SetPins(PTD, (1u << 16));
            else
            	PINS_DRV_ClearPins(PTD, (1u << 16));

            /* OBSTACLE FRONT */
            if (gVehicleState.obstacleFlags & OBS_FRONT)
            	PINS_DRV_SetPins(PTD, (1u << 0));
            else
            	PINS_DRV_ClearPins(PTD, (1u << 0));
        }
    }
}
