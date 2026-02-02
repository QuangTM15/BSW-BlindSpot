#ifndef COM_TX_H
#define COM_TX_H

/* Init communication layer */
void ComTx_Init(void);

/* Send current vehicle state */
void ComTx_SendVehicleState(void);

#endif /* COM_TX_H */
