#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "Arduino.h"
#include "src/grbl/hal.h"
#include "clearcore.h"

#define console Serial
#define BAUD_RATE 115200

void execute_realtime(sys_state_t state);
void settings_changed (settings_t *settings);
bool driver_setup(settings_t *settings);
void limitsEnable (bool on, bool homing);


uint_fast16_t spindleGetPWM (float rpm);
void spindleUpdateRPM (float rpm);
void spindle_set_speed (uint_fast16_t pwm_value);
void stepperGoIdle (bool clear_signals);
void driver_delay_ms (uint32_t ms, void (*callback)(void));
control_signals_t systemGetState (void);
void spindleSetState (spindle_state_t state, float rpm);
void coolantSetState (coolant_state_t mode);






#endif

