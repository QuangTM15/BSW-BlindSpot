#ifndef TURN_INPUT_H
#define TURN_INPUT_H

#include <stdbool.h>
#include "state/vehicle_state.h"

void TurnInput_Init(void);

bool TurnInput_Update(TurnSignal_t *turn_out);

#endif /* TURN_INPUT_H */
