#include "com_tx.h"

/* Project */
#include "state/vehicle_state.h"

/* Communication */
#include "com/frame_tx.h"
#include "com/uart_tx_polling.h"

void ComTx_Init(void)
{
    UART_TxPolling_Init();
}

void ComTx_SendVehicleState(void)
{
    FrameTx_SendVehicleState(&gVehicleState);
}
