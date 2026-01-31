#ifndef INPUT_CMD_H
#define INPUT_CMD_H

#include <stdbool.h>

typedef enum
{
    CMD_NONE = 0,
    CMD_MOTOR_FORWARD,
    CMD_MOTOR_BACKWARD,
    CMD_MOTOR_STOP
} InputCmd_t;

/* Init command input */
void InputCmd_Init(void);

void InputCmd_Update(void);

bool InputCmd_Get(InputCmd_t *cmd);

#endif /* INPUT_CMD_H */
