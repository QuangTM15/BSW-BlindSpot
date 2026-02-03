#ifndef LED_HW_H
#define LED_HW_H

#include <stdbool.h>
#include <stdint.h>

void LedHW_Init(void);

void LedHW_MirrorLeft_Set(bool on);
void LedHW_MirrorRight_Set(bool on);

void LedHW_TurnLeft_Set(bool on);
void LedHW_TurnRight_Set(bool on);

void LedHW_DoorLeft_Set(bool on);
void LedHW_DoorRight_Set(bool on);

/* Reverse warning */
void LedHW_Reverse_SetByDistance(uint8_t distanceCm);

#endif /* LED_HW_H */
