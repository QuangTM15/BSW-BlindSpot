#include "output/output_hw.h"
#include "sdk_project_config.h"

/* =================================================
 * TEMP PIN DEFINE (LOGIC TEST ONLY)
 * ================================================= */

/* External warning LEDs (ACTIVE LOW) */
#define WARN_LEFT_PORT    PTD
#define WARN_LEFT_PIN     10U

#define WARN_RIGHT_PORT   PTD
#define WARN_RIGHT_PIN    9U

/* Buzzer (ASSUME ACTIVE HIGH) */
#define BUZZER_PORT       PTD
#define BUZZER_PIN        8U

/* On-board turn indicator LEDs (ACTIVE LOW) */
#define TURN_LEFT_PORT    PTD
#define TURN_LEFT_PIN     15U

#define TURN_RIGHT_PORT   PTD
#define TURN_RIGHT_PIN    16U

/* =================================================
 * INIT (set all OFF)
 * ================================================= */
void OutputHW_Init(void)
{
    OutputHW_WarnLeft_Off();
    OutputHW_WarnRight_Off();
    OutputHW_Buzzer_Off();
    OutputHW_TurnLeft_Off();
    OutputHW_TurnRight_Off();
}

/* =================================================
 * WARNING LED (ACTIVE LOW)
 * ================================================= */
void OutputHW_WarnLeft_On(void)
{
    /* Clear = LED ON */
    PINS_DRV_ClearPins(WARN_LEFT_PORT, (1UL << WARN_LEFT_PIN));
}

void OutputHW_WarnLeft_Off(void)
{
    /* Set = LED OFF */
    PINS_DRV_SetPins(WARN_LEFT_PORT, (1UL << WARN_LEFT_PIN));
}

void OutputHW_WarnRight_On(void)
{
    PINS_DRV_ClearPins(WARN_RIGHT_PORT, (1UL << WARN_RIGHT_PIN));
}

void OutputHW_WarnRight_Off(void)
{
    PINS_DRV_SetPins(WARN_RIGHT_PORT, (1UL << WARN_RIGHT_PIN));
}

/* =================================================
 * BUZZER (ACTIVE HIGH)
 * ================================================= */
void OutputHW_Buzzer_On(void)
{
    PINS_DRV_SetPins(BUZZER_PORT, (1UL << BUZZER_PIN));
}

void OutputHW_Buzzer_Off(void)
{
    PINS_DRV_ClearPins(BUZZER_PORT, (1UL << BUZZER_PIN));
}

/* =================================================
 * TURN INDICATOR (ACTIVE LOW)
 * ================================================= */
void OutputHW_TurnLeft_On(void)
{
    PINS_DRV_ClearPins(TURN_LEFT_PORT, (1UL << TURN_LEFT_PIN));
}

void OutputHW_TurnLeft_Off(void)
{
    PINS_DRV_SetPins(TURN_LEFT_PORT, (1UL << TURN_LEFT_PIN));
}

void OutputHW_TurnRight_On(void)
{
    PINS_DRV_ClearPins(TURN_RIGHT_PORT, (1UL << TURN_RIGHT_PIN));
}

void OutputHW_TurnRight_Off(void)
{
    PINS_DRV_SetPins(TURN_RIGHT_PORT, (1UL << TURN_RIGHT_PIN));
}
