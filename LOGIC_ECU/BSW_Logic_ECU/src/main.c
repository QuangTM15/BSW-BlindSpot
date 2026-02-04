#include <stdint.h>
#include <stdbool.h>

/* ================= BOARD ================= */
#include "board/board_init.h"

/* ================= COM ================= */
#include "com/uart_rx_polling.h"
#include "com/frame_rx.h"

/* ================= STATE ================= */
#include "state/vehicle_state.h"

/* ================= OUTPUT ================= */
#include "manager/output_manager.h"

/* =================================================
 * MAIN
 * ================================================= */
int main(void)
{
    uint8_t rxByte;

    /* Init board: clock, pinmux, UART, PWM */
    Board_Init();

    /* Init output hardware */
    OutputManager_Init();

    /* Reset RX state machine */
    FrameRx_Reset();

    while (1)
    {
        /* ---------- UART RX ---------- */
        if (UART_RxPolling_ReadByte(&rxByte))
        {
            FrameRx_PushByte(rxByte);
        }

        /* ---------- FRAME READY ---------- */
        if (FrameRx_IsFrameReady())
        {
            FrameRx_GetVehicleState(&gVehicleState);

            /* Run logic + update hardware */
            OutputManager_Update(&gVehicleState);
        }
    }
}
