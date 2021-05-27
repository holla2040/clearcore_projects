#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "Arduino.h"
#include "src/grbl/hal.h"

#define console Serial
#define BAUD_RATE 115200

void execute_realtime(sys_state_t state);
void settings_changed (settings_t *settings);




#endif

