#include "sdk_project_config.h"
#include "state/vehicle_state.h"
#include <stddef.h>
#include <stdbool.h>

static volatile bool leftButtonEvent  = false;
static volatile bool rightButtonEvent = false;
static TurnSignal_t currentTurn = TURN_NONE;

void PORTC_IRQHandler(void)
{
    if (PORTC->ISFR & (1UL << 13))
    {
        PORTC->ISFR = (1UL << 13);
        leftButtonEvent = true;
    }

    if (PORTC->ISFR & (1UL << 12))
    {
        PORTC->ISFR = (1UL << 12);
        rightButtonEvent = true;
    }
}

void TurnInput_Init(void)
{
    leftButtonEvent  = false;
    rightButtonEvent = false;
    currentTurn      = TURN_NONE;
}

void TurnInput_Update(VehicleState_t *state)
{
    if (state == NULL)
    {
        return;
    }

    if (leftButtonEvent)
    {
        leftButtonEvent = false;
        currentTurn = (currentTurn == TURN_LEFT) ? TURN_NONE : TURN_LEFT;
    }

    if (rightButtonEvent)
    {
        rightButtonEvent = false;
        currentTurn = (currentTurn == TURN_RIGHT) ? TURN_NONE : TURN_RIGHT;
    }

    state->turnSignal = currentTurn;
    state->validFlags |= VS_VALID_TURN;
}
