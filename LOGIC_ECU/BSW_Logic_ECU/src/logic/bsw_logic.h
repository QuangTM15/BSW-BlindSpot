#ifndef BSW_LOGIC_H
#define BSW_LOGIC_H

#include <stdbool.h>
#include <stdint.h>
#include "state/vehicle_state.h"

typedef struct
{
    /* Mirror warning */
    bool mirrorLeft;
    bool mirrorRight;

    /* Door warning */
    bool doorLeft;
    bool doorRight;

    /* Turn indicator (for output display if needed) */
    bool turnLeft;
    bool turnRight;

    /* Reverse warning */
    bool reverseActive;
    uint8_t reverseDistanceCm;

    /* Buzzer */
    bool buzzerOn;

} BswOutput_t;

void BswLogic_Evaluate(const VehicleState_t *state,
                       BswOutput_t *out);

#endif /* BSW_LOGIC_H */
