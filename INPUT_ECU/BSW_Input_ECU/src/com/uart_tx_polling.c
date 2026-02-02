#include "uart_tx_polling.h"

#include "sdk_project_config.h"
#include "lpuart_hw_access.h"
#include "peripherals_lpuart_2.h"

/* ================= CONFIG ================= */
#define UART_TX_BASE   LPUART2
/* ========================================== */

void UART_TxPolling_Init(void)
{
    LPUART_SetTransmitterCmd(UART_TX_BASE, true);
}

void UART_TxPolling_SendByte(uint8_t b)
{
    while (!LPUART_GetStatusFlag(UART_TX_BASE,
    		LPUART_TX_DATA_REG_EMPTY))
    {
    }

    UART_TX_BASE->DATA = b;
}

void UART_TxPolling_SendBuffer(const uint8_t *buf, uint16_t len)
{
    if (buf == NULL || len == 0)
        return;

    for (uint16_t i = 0; i < len; i++)
    {
        UART_TxPolling_SendByte(buf[i]);
    }
}
