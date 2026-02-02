#include "frame_tx.h"

#include "uart_tx_polling.h"
#include "peripherals_lpuart_2.h"

/* ================= FRAME CONSTANT ================= */

#define FRAME_SOF1   0xAA
#define FRAME_SOF2   0x55
#define FRAME_VER    0x01

/* ================= CRC ================= */

static uint8_t Frame_CalcCRC(const uint8_t *data, uint8_t len)
{
    uint8_t crc = 0U;

    for (uint8_t i = 0; i < len; i++)
    {
        crc ^= data[i];
    }

    return crc;
}

/* ================= TX ================= */

void FrameTx_SendVehicleState(const VehicleState_t *state)
{
    uint8_t payload[32];
    uint8_t idx = 0U;

    if (state == NULL)
        return;

    /* Build payload */
    payload[idx++] = (uint8_t)state->motorRun;
    payload[idx++] = (uint8_t)state->motion;

    payload[idx++] = (uint8_t)(state->speed_kmh & 0xFF);
    payload[idx++] = (uint8_t)(state->speed_kmh >> 8);

    payload[idx++] = state->obstacleFlags;

    payload[idx++] = (uint8_t)(state->us_front_cm & 0xFF);
    payload[idx++] = (uint8_t)(state->us_front_cm >> 8);

    payload[idx++] = (uint8_t)(state->us_rear_cm & 0xFF);
    payload[idx++] = (uint8_t)(state->us_rear_cm >> 8);

    payload[idx++] = (uint8_t)state->turnSignal;

    uint8_t payloadLen = idx;

    /* Header */
    uint8_t header[6];
    header[0] = FRAME_SOF1;
    header[1] = FRAME_SOF2;
    header[2] = FRAME_VER;
    header[3] = FRAME_TYPE_STATE;
    header[4] = payloadLen;
    header[5] = (uint8_t)(state->seq & 0xFF);

    /* CRC calculation */
    uint8_t crcBuf[64];
    uint8_t crcLen = 0U;

    crcBuf[crcLen++] = header[2];
    crcBuf[crcLen++] = header[3];
    crcBuf[crcLen++] = header[4];
    crcBuf[crcLen++] = header[5];

    for (uint8_t i = 0; i < payloadLen; i++)
    {
        crcBuf[crcLen++] = payload[i];
    }

    uint8_t crc = Frame_CalcCRC(crcBuf, crcLen);

    /* Send frame */
    UART_TxPolling_SendByte(header[0]);
    UART_TxPolling_SendByte(header[1]);

    for (uint8_t i = 2; i < 6; i++)
    {
        UART_TxPolling_SendByte(header[i]);
    }

    UART_TxPolling_SendBuffer(payload, payloadLen);
    UART_TxPolling_SendByte(crc);
}

