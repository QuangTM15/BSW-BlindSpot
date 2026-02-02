#ifndef UART_TX_POLLING_H
#define UART_TX_POLLING_H

#include <stdint.h>
#include <stddef.h>

void UART_TxPolling_Init(void);

void UART_TxPolling_SendByte(uint8_t b);

void UART_TxPolling_SendBuffer(const uint8_t *buf, uint16_t len);

#endif /* UART_TX_POLLING_H */
