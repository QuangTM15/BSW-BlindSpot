#ifndef OUTPUT_HW_H
#define OUTPUT_HW_H

/* ===== INIT ===== */
void OutputHW_Init(void);

/* ===== WARNING LED (EXTERNAL) ===== */
void OutputHW_WarnLeft_On(void);
void OutputHW_WarnLeft_Off(void);

void OutputHW_WarnRight_On(void);
void OutputHW_WarnRight_Off(void);

/* ===== BUZZER ===== */
void OutputHW_Buzzer_On(void);
void OutputHW_Buzzer_Off(void);

/* ===== TURN INDICATOR (ONBOARD LED) ===== */
void OutputHW_TurnLeft_On(void);
void OutputHW_TurnLeft_Off(void);

void OutputHW_TurnRight_On(void);
void OutputHW_TurnRight_Off(void);

#endif /* OUTPUT_HW_H */
