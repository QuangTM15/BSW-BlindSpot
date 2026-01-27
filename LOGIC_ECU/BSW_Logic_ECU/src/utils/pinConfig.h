#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

#include "sdk_project_config.h"

/* =========================================================
 * OUTPUT - LED MIRROR (Blind Spot Warning)
 * ========================================================= */
#define LED_MIRROR_LEFT_GPIO     PTD
#define LED_MIRROR_LEFT_PIN      8U //GPIO8

#define LED_MIRROR_RIGHT_GPIO    PTD
#define LED_MIRROR_RIGHT_PIN     9U //GPIO7

/* =========================================================
 * OUTPUT - LED DOOR (Safe Exit Warning)
 * ========================================================= */
#define LED_DOOR_LEFT_GPIO       PTD
#define LED_DOOR_LEFT_PIN        10U //GPIO6

#define LED_DOOR_RIGHT_GPIO      PTD
#define LED_DOOR_RIGHT_PIN       11U //GPIO5

/* =========================================================
 * OUTPUT - BUZZER
 * ========================================================= */
#define BUZZER_GPIO              PTD
#define BUZZER_PIN               12U //GPIO4

/* =========================================================
 * OUTPUT - REVERSE LED (PWM)
 * =========================================================
 * PWM brightness increases when distance decreases
 * Controlled by FTM
 */
#define LED_REVERSE_PWM_FTM      FTM0
#define LED_REVERSE_PWM_CHANNEL  0U
#define LED_REVERSE_PWM_PIN      15U   /* PTD15 */  //RED LED

/* =========================================================
 * COMMON MACROS
 * ========================================================= */
#define GPIO_PIN_MASK(pin)       (1U << (pin))

/* =========================================================
 * INPUT - TURN SIGNAL
 * ========================================================= */
#define TURN_LEFT_GPIO           PTD
#define TURN_LEFT_PIN            16U   /* PTD16 */ //LED BLUE

#define TURN_RIGHT_GPIO          PTD
#define TURN_RIGHT_PIN           0U    /* PTD0 */ //LED GREEN

#endif /* PIN_CONFIG_H */
