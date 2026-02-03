#include <stdint.h>
#include <stdbool.h>

/* ================= BOARD ================= */
#include "board/board_init.h"

#include "com/uart_rx_polling.h"
#include "com/frame_rx.h"

#include "state/vehicle_state.h"

#include "manager/output_manager.h"
#include "hardware/led_hw.h"


/* =================================================
 * MAIN
 * ================================================= */
int main(void)
{
    Board_Init();
    LedHW_Init();
    BuzzerHW_Init();

    while (1)
    {
    	LedHW_Reverse_SetByDistance(15);
    }
}
