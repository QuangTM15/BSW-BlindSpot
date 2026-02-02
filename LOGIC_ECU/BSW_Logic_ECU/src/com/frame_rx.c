#include "frame_rx.h"

#include <string.h>

/* ================= FRAME CONST ================= */

#define FRAME_SOF1   0xAA
#define FRAME_SOF2   0x55
#define FRAME_VER    0x01
#define FRAME_TYPE_STATE  0x01

#define MAX_PAYLOAD_LEN   32

/* ================= RX STATE ================= */

typedef enum
{
    RX_WAIT_SOF1 = 0,
    RX_WAIT_SOF2,
    RX_WAIT_VER,
    RX_WAIT_TYPE,
    RX_WAIT_LEN,
    RX_WAIT_SEQ,
    RX_WAIT_PAYLOAD,
    RX_WAIT_CRC
} RxState_t;

/* ================= LOCAL DATA ================= */

static RxState_t rxState = RX_WAIT_SOF1;

static uint8_t payloadBuf[MAX_PAYLOAD_LEN];
static uint8_t payloadLen = 0;
static uint8_t payloadIdx = 0;

static uint8_t crcCalc = 0;
static uint8_t rxCrc = 0;

static VehicleState_t rxStateBuf;
static bool frameReady = false;

/* ================= CRC ================= */

static void CRC_Reset(void)
{
    crcCalc = 0;
}

static void CRC_Update(uint8_t b)
{
    crcCalc ^= b;
}

/* ================= API ================= */

void FrameRx_Reset(void)
{
    rxState = RX_WAIT_SOF1;
    payloadIdx = 0;
    payloadLen = 0;
    CRC_Reset();
}

void FrameRx_PushByte(uint8_t b)
{
    switch (rxState)
    {
        case RX_WAIT_SOF1:
            if (b == FRAME_SOF1)
                rxState = RX_WAIT_SOF2;
            break;

        case RX_WAIT_SOF2:
            if (b == FRAME_SOF2)
                rxState = RX_WAIT_VER;
            else
                rxState = RX_WAIT_SOF1;
            break;

        case RX_WAIT_VER:
            if (b != FRAME_VER)
            {
                FrameRx_Reset();
                break;
            }
            CRC_Update(b);
            rxState = RX_WAIT_TYPE;
            break;

        case RX_WAIT_TYPE:
            if (b != FRAME_TYPE_STATE)
            {
                FrameRx_Reset();
                break;
            }
            CRC_Update(b);
            rxState = RX_WAIT_LEN;
            break;

        case RX_WAIT_LEN:
            if (b > MAX_PAYLOAD_LEN)
            {
                FrameRx_Reset();
                break;
            }
            payloadLen = b;
            payloadIdx = 0;
            CRC_Update(b);
            rxState = RX_WAIT_SEQ;
            break;

        case RX_WAIT_SEQ:
            CRC_Update(b);
            rxState = (payloadLen > 0) ? RX_WAIT_PAYLOAD : RX_WAIT_CRC;
            break;

        case RX_WAIT_PAYLOAD:
            payloadBuf[payloadIdx++] = b;
            CRC_Update(b);

            if (payloadIdx >= payloadLen)
                rxState = RX_WAIT_CRC;
            break;

        case RX_WAIT_CRC:
            rxCrc = b;

            if (rxCrc == crcCalc)
            {
                /* Deserialize payload to VehicleState */
                uint8_t i = 0;

                rxStateBuf.motorRun = (MotorRunState_t)payloadBuf[i++];
                rxStateBuf.motion   = (VehicleMotion_t)payloadBuf[i++];

                rxStateBuf.speed_kmh =
                    (uint16_t)payloadBuf[i] |
                    ((uint16_t)payloadBuf[i + 1] << 8);
                i += 2;

                rxStateBuf.obstacleFlags = payloadBuf[i++];

                rxStateBuf.us_front_cm =
                    (int16_t)payloadBuf[i] |
                    ((int16_t)payloadBuf[i + 1] << 8);
                i += 2;

                rxStateBuf.us_rear_cm =
                    (int16_t)payloadBuf[i] |
                    ((int16_t)payloadBuf[i + 1] << 8);
                i += 2;

                rxStateBuf.turnSignal = (TurnSignal_t)payloadBuf[i++];

                frameReady = true;
            }

            FrameRx_Reset();
            break;

        default:
            FrameRx_Reset();
            break;
    }
}

bool FrameRx_IsFrameReady(void)
{
    return frameReady;
}

bool FrameRx_GetVehicleState(VehicleState_t *outState)
{
    if (!frameReady || outState == NULL)
        return false;

    memcpy(outState, &rxStateBuf, sizeof(VehicleState_t));
    frameReady = false;
    return true;
}
