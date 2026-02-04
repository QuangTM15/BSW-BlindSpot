#include <stdint.h>
#include <string.h>

/* ================= BOARD ================= */
#include "board/board_init.h"

/* ================= INPUT ================= */
#include "manager/input_manager.h"

/* ================= COM ================= */
#include "com/uart_tx_polling.h"
#include "com/frame_tx.h"

/* ================= STATE ================= */
#include "state/vehicle_state.h"

/* ================= DELAY ================= */
static void DelayMs(uint32_t ms)
{
    for (volatile uint32_t i = 0; i < ms * 8000U; i++)
    {
        __asm("nop");
    }
}
int main(void)
{
    /* ---------- BOARD INIT ---------- */
    Board_Init();

    /* ---------- INPUT INIT ---------- */
    InputManager_Init();

    /* ---------- TX INIT ---------- */
    UART_TxPolling_Init();

    /* ---------- CLEAR STATE ---------- */
    memset(&gVehicleState, 0, sizeof(gVehicleState));

    gVehicleState.seq = 0;

    while (1)
    {
        /* Read all input modules */
        InputManager_Update(&gVehicleState);

        /* Send current vehicle state to LOGIC_ECU */
        FrameTx_SendVehicleState(&gVehicleState);
        gVehicleState.seq++;

        /* Small delay to avoid flooding UART */
        DelayMs(50);
    }
}
