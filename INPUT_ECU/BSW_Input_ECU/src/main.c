#include "board/board_init.h"
#include "manager/input_manager.h"
#include "com/com_tx.h"

int main(void)
{
    Board_Init();

    InputManager_Init();
    ComTx_Init();

    while (1)
    {
        if (InputManager_Update())
        {
            ComTx_SendVehicleState();
        }
    }
}
