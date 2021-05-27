#include "Arduino.h"
#include "driver.h"
#include "serial.h"

#ifdef __cplusplus
extern "C" {
#endif

bool driver_init() {
    hal.info = "SAME53";
    hal.driver_version = __DATE__;

    serialInit();
    hal.stream.write = serialWriteS;
    hal.stream.write_all = serialWriteS;
    hal.stream.write_char = serialPutC;

    hal.settings_changed = settings_changed;

    grbl.on_execute_realtime = execute_realtime;
    return 1;
}

void settings_changed (settings_t *settings){
    serialWriteS("settings_changed\n");
}


void execute_realtime(sys_state_t state) {
    char b[20];
    sprintf(b,"%d\n",millis());
    serialWriteS(b);
}

#ifdef __cplusplus
}
#endif
