#include "uart_rx_polling.h"

#include "sdk_project_config.h"
#include "lpuart_hw_access.h"
#include "peripherals_lpuart_2.h"

bool UART_RxPolling_ReadByte(uint8_t *outByte)
{
    if (outByte == NULL)
        return false;

    if (!LPUART_GetStatusFlag(LPUART2,
                              LPUART_RX_DATA_REG_FULL))
    {
        return false;
    }

    *outByte = (uint8_t)LPUART2->DATA;
    return true;
}
