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
    hal.stream.read = serialGetC;
    hal.stream.get_rx_buffer_available = serialRxFree;
    hal.stream.reset_read_buffer = serialRxFlush;
    hal.stream.cancel_read_buffer = serialRxCancel;
    hal.stream.suspend_read = serialSuspendInput;

    hal.stream.write = serialWriteS;
    hal.stream.write_all = serialWriteS;
    hal.stream.write_char = serialPutC;




    hal.driver_cap.variable_spindle = On;
    hal.driver_cap.mist_control = On;
    hal.driver_cap.software_debounce = On;
    hal.driver_cap.step_pulse_delay = On;                                                                             
    hal.driver_cap.amass_level = 3;
    hal.driver_cap.control_pull_up = On;
    hal.driver_cap.limits_pull_up = On;
    hal.driver_cap.probe_pull_up = On;

    hal.spindle.get_pwm = spindleGetPWM;
    hal.spindle.update_pwm = spindle_set_speed;                                                                       

    hal.driver_cap.amass_level = 3;                                                                                   

    hal.settings_changed = settings_changed;
    hal.driver_setup = driver_setup;


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

bool driver_setup(settings_t *settings) {
    return 1;
}

uint_fast16_t spindleGetPWM (float rpm) {
    // return spindle_compute_pwm_value(&spindle_pwm, rpm, false);
    return 0;
}

void spindleUpdateRPM (float rpm) {
    // spindle_set_speed(spindle_compute_pwm_value(&spindle_pwm, rpm, false));
}

void spindle_set_speed (uint_fast16_t pwm_value) {
}



#ifdef __cplusplus
}
#endif
