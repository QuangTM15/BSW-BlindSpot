#include "input_cmd.h"
#include "sdk_project_config.h"
#include <stdbool.h>
#include "lpuart_hw_access.h"


#define UART_BASE LPUART1

static volatile InputCmd_t g_cmd = CMD_NONE;
static volatile bool g_cmdReady = false;

void InputCmd_Init(void)
{
    g_cmd = CMD_NONE;
    g_cmdReady = false;
}

void InputCmd_Update(void)
{

    if (LPUART_GetStatusFlag(UART_BASE, LPUART_RX_OVERRUN))
    {
        LPUART_ClearStatusFlag(UART_BASE, LPUART_RX_OVERRUN);
    }

    if (LPUART_GetStatusFlag(UART_BASE, LPUART_FRAME_ERR))
    {
        LPUART_ClearStatusFlag(UART_BASE, LPUART_FRAME_ERR);
    }

    if (LPUART_GetStatusFlag(UART_BASE, LPUART_NOISE_DETECT))
    {
        LPUART_ClearStatusFlag(UART_BASE, LPUART_NOISE_DETECT);
    }

    /* ===== Poll RX ===== */

    while (LPUART_GetStatusFlag(UART_BASE, LPUART_RX_DATA_REG_FULL))
    {
        uint8_t b = (uint8_t)UART_BASE->DATA;

        if (b == '\r' || b == '\n')
            continue;

        switch (b)
        {
            case 'f': case 'F':
                g_cmd = CMD_MOTOR_FORWARD;
                g_cmdReady = true;
                break;

            case 'r': case 'R':
                g_cmd = CMD_MOTOR_BACKWARD;
                g_cmdReady = true;
                break;

            case 's': case 'S':
                g_cmd = CMD_MOTOR_STOP;
                g_cmdReady = true;
                break;
        }
    }
}

bool InputCmd_Get(InputCmd_t *cmd)
{
    if (!g_cmdReady)
        return false;

    *cmd = g_cmd;
    g_cmdReady = false;
    return true;
}
