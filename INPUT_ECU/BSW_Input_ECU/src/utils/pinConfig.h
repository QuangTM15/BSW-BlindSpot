#ifndef PIN_CFG_H
#define PIN_CFG_H

/* =================================================
 * ULTRASONIC SENSORS (4x)
 * - Shared TRIG (OUTPUT)
 * - Separate ECHO (INPUT)
 * ================================================= */

/* Shared TRIG (LEFT / RIGHT) */
#define US_TRIG_PORT PTE // GPIO 0 OUTPUT
#define US_TRIG_PIN 0U
/* FB TRIG */
#define US_FB_TRIG_PORT PTD
#define US_FB_TRIG_PIN 10U // GPIO 6 //OUTPUT

/* ECHO signals */
#define US_FRONT_ECHO_PORT PTD
#define US_FRONT_ECHO_PIN 11U // GPIO 5 Input

#define US_REAR_ECHO_PORT PTD
#define US_REAR_ECHO_PIN 14U // GPIO 2 Input

#define US_LEFT_ECHO_PORT PTD
#define US_LEFT_ECHO_PIN 13U // GPIO 3 Input FTM2 Ch4

#define US_RIGHT_ECHO_PORT PTD // GPIO 4 Input FTM2 Ch2
#define US_RIGHT_ECHO_PIN 12U

/* =================================================
 * TURN SIGNAL BUTTONS (ON-BOARD)
 * ================================================= */
#define BTN_LEFT_PORT PTC
#define BTN_LEFT_PIN 12U

#define BTN_RIGHT_PORT PTC
#define BTN_RIGHT_PIN 13U

/* =================================================
 * SPEED SENSOR (1 CHANNEL)
 * ================================================= */
#define SPEED_SENSOR_PORT PTD
#define SPEED_SENSOR_PIN 17U // GPIO1

/* =================================================
 * MOTOR CONTROL
 * - Two PWM outputs
 *   + Forward PWM
 *   + Reverse PWM
 * ================================================= */

/* Forward (Move Ahead) */
#define MOTOR_FWD_PWM_PORT PTD // FTM1 ch4
#define MOTOR_FWD_PWM_PIN 8U   // GPIO 8

/* Reverse (Move Backward) */
#define MOTOR_REV_PWM_PORT PTD // FTM1 ch5
#define MOTOR_REV_PWM_PIN 9U   // GPIO 7

#endif /* PIN_CFG_H */