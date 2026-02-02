#include "board_init.h"

#include "sdk_project_config.h"

/* Clock */
#include "clock_manager.h"

/* Pins */
#include "pins_driver.h"

/* Peripherals */
#include "peripherals_lpuart_1.h"
#include "peripherals_lpuart_2.h"
#include "peripherals_flexTimer_ic_1.h"
#include "peripherals_lpit_config_1.h"
#include "lpuart_hw_access.h"
#include "interrupt_manager.h"

void Board_Init(void)
{
    /* Clock init */
    CLOCK_SYS_Init(
        g_clockManConfigsArr,
        CLOCK_MANAGER_CONFIG_CNT,
        g_clockManCallbacksArr,
        CLOCK_MANAGER_CALLBACK_CNT
    );
    CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

    /* Pin mux init */
    PINS_DRV_Init(
        NUM_OF_CONFIGURED_PINS0,
        g_pin_mux_InitConfigArr0
    );

    /* UART2 init */
    LPUART_DRV_Init(INST_LPUART_2, &lpUartState2, &lpuart_2_InitConfig0);
    LPUART_DRV_Init(
        INST_LPUART_1,
        &lpUartState1,
        &lpuart_1_InitConfig0
    );
    LPUART_SetReceiverCmd(LPUART1, true);
    /* Enable TX */
    LPUART_SetTransmitterCmd(LPUART2, true);

    /* FTM Input Capture init */
    FTM_DRV_Init(
        INST_FLEXTIMER_IC_1,
        &flexTimer_ic_1_InitConfig,
        NULL
    );
    FTM_DRV_InitInputCapture(
        INST_FLEXTIMER_IC_1,
        &flexTimer_ic_1_InputCaptureConfig
    );

    /* LPIT init (if used) */
    LPIT_DRV_Init(
        INST_LPIT_CONFIG_1,
        &lpit1_InitConfig
    );
    /* Enable PORTC interrupt (turn buttons) */
    INT_SYS_EnableIRQ(PORTC_IRQn);

    /* Enable FTM2 interrupts (input capture) */
    INT_SYS_EnableIRQ(FTM2_Ch2_Ch3_IRQn);
    INT_SYS_EnableIRQ(FTM2_Ch4_Ch5_IRQn);
}
