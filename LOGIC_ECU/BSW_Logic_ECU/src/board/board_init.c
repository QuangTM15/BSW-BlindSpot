#include "board/board_init.h"

/* SDK */
#include "sdk_project_config.h"
#include "clock_config.h"
#include "pin_mux.h"

/* Peripherals */
#include "peripherals_lpuart_2.h"
#include "peripherals_flexTimer_pwm_1.h"
#include "lpuart_hw_access.h"

ftm_state_t ftm2State;

void Board_Init(void)
{
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

    FTM_DRV_Init(
        INST_FLEXTIMER_PWM_1,
        &flexTimer_pwm_1_InitConfig,
        &ftm2State
    );
    FTM_DRV_InitPwm(
        INST_FLEXTIMER_PWM_1,
        &flexTimer_pwm_1_PwmConfig
    );

}
