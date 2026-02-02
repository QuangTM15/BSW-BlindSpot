#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <stdbool.h>

/* Init all input modules */
void InputManager_Init(void);

/*
 * Update all inputs and vehicle state
 * @return true if vehicle state changed
 */
bool InputManager_Update(void);

#endif /* INPUT_MANAGER_H */
