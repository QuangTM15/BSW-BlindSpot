#ifndef UART_RX_POLLING_H
#define UART_RX_POLLING_H

#include <stdint.h>
#include <stdbool.h>

/* Poll RX, return true if one byte received */
bool UART_RxPolling_ReadByte(uint8_t *outByte);

#endif /* UART_RX_POLLING_H */
