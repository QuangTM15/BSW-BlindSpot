#include "board/board_init.h"

/* ================= SDK ================= */
#include "sdk_project_config.h"
#include "clock_manager.h"
#include "pins_driver.h"
#include "pin_mux.h"

/* ================= UART ================= */
#include "peripherals_lpuart_1.h"
#include "peripherals_lpuart_2.h"
#include "lpuart_hw_access.h"

/* =================================================
 * BOARD INIT – ECU_INPUT
 * ================================================= */
void Board_Init(void)
{
    /* ---------- CLOCK ---------- */
    CLOCK_SYS_Init(
        g_clockManConfigsArr,
        CLOCK_MANAGER_CONFIG_CNT,
        g_clockManCallbacksArr,
        CLOCK_MANAGER_CALLBACK_CNT
    );
    CLOCK_SYS_UpdateConfiguration(
        0U,
        CLOCK_MANAGER_POLICY_AGREEMENT
    );

    /* ---------- PIN MUX ---------- */
    PINS_DRV_Init(
        NUM_OF_CONFIGURED_PINS0,
        g_pin_mux_InitConfigArr0
    );

    /* ---------- UART1 : RX FROM HERCULES ---------- */
    LPUART_DRV_Init(
        INST_LPUART_1,
        &lpUartState1,
        &lpuart_1_InitConfig0
    );
    LPUART_SetReceiverCmd(LPUART1, true);

    /* ---------- UART2 : TX TO LOGIC ECU ---------- */
    LPUART_DRV_Init(
        INST_LPUART_2,
        &lpUartState2,
        &lpuart_2_InitConfig0
    );
    LPUART_SetTransmitterCmd(LPUART2, true);

    /* ---------- CLEAR PORT INTERRUPTS (BUTTON) ---------- */
    PORTC->ISFR = 0xFFFFFFFFU;
    INT_SYS_EnableIRQ(PORTC_IRQn);
}
