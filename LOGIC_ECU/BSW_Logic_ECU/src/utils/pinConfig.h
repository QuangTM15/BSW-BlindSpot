#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

#include "sdk_project_config.h"

/* =================================================
 * MIRROR WARNING LED
 * ================================================= */
#define PIN_MIRROR_LEFT_PORT     PTD
#define PIN_MIRROR_LEFT_PIN      17U //GPIO1

#define PIN_MIRROR_RIGHT_PORT    PTD
#define PIN_MIRROR_RIGHT_PIN     14U //GPIO2

/* =================================================
 * TURN SIGNAL LED
 * ================================================= */
#define PIN_TURN_LEFT_PORT       PTD
#define PIN_TURN_LEFT_PIN        9U //GPIO7

#define PIN_TURN_RIGHT_PORT      PTD
#define PIN_TURN_RIGHT_PIN       8U //GPIO8

/* =================================================
 * DOOR WARNING LED
 * ================================================= */
#define PIN_DOOR_LEFT_PORT       PTD
#define PIN_DOOR_LEFT_PIN        11U //GPIO5

#define PIN_DOOR_RIGHT_PORT      PTD
#define PIN_DOOR_RIGHT_PIN       13U //GPIO3

/* =================================================
 * REVERSE WARNING LED (PWM)
 * ================================================= */
#define PIN_REVERSE_LED_PORT     PTD
#define PIN_REVERSE_LED_PIN      12U //FTM2 Ch2 GPIO4
/* =================================================
 * BUZZER
 * ================================================= */
#define PIN_BUZZER_PORT          PTD
#define PIN_BUZZER_PIN           10U //GPIO6

#endif /* PIN_CONFIG_H */
