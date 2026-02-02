#include "sdk_project_config.h"
#include "state/vehicle_state.h"
#include <stddef.h>
#include <stdbool.h>
#include "utils/pinConfig.h"

/* Button event flags set in IRQ */
static volatile bool leftButtonEvent  = false;
static volatile bool rightButtonEvent = false;

/* Current turn state */
static TurnSignal_t currentTurn = TURN_NONE;

/* Button interrupt handler */
void PORTC_IRQHandler(void)
{
    if (PORTC->ISFR & (1UL << BTN_LEFT_PIN))
    {
        PORTC->ISFR = (1UL << BTN_LEFT_PIN);
        leftButtonEvent = true;
    }

    if (PORTC->ISFR & (1UL << BTN_RIGHT_PIN))
    {
        PORTC->ISFR = (1UL << BTN_RIGHT_PIN);
        rightButtonEvent = true;
    }
}

void TurnInput_Init(void)
{
    leftButtonEvent  = false;
    rightButtonEvent = false;
    currentTurn      = TURN_NONE;
}

bool TurnInput_Update(TurnSignal_t *turn_out)
{
    bool changed = false;

    if (leftButtonEvent)
    {
        leftButtonEvent = false;
        currentTurn = (currentTurn == TURN_LEFT) ? TURN_NONE : TURN_LEFT;
        changed = true;
    }

    if (rightButtonEvent)
    {
        rightButtonEvent = false;
        currentTurn = (currentTurn == TURN_RIGHT) ? TURN_NONE : TURN_RIGHT;
        changed = true;
    }

    if (changed && turn_out != NULL)
    {
        *turn_out = currentTurn;
    }

    return changed;
}
